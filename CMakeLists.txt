cmake_minimum_required(VERSION 3.16)

project(TerminalApp
        VERSION 1.0.0
        DESCRIPTION "Qt Widgets desktop shell for embedded Linux (i.MX6ULL)"
        LANGUAGES CXX)

# ---------------------------------------------------------------------------
# Global settings
# ---------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# ---------------------------------------------------------------------------
# Qt: dual support
#   - board (i.MX6ULL): Qt 5.12.9  (Yocto/FSL SDK, see cmake/toolchain-board.cmake)
#   - desktop dev:      Qt 6.x
# ---------------------------------------------------------------------------
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets Sql Network)
message(STATUS "TerminalApp: building against Qt ${QT_VERSION}")

# ---------------------------------------------------------------------------
# Qt Mqtt (used by src/apps/mqtt)
#   - board (i.MX6ULL): the Yocto/FSL SDK ships Qt5Mqtt  -> found automatically
#   - desktop dev (Qt6): Qt Mqtt is an optional add-on module and is normally
#     NOT installed by the Qt6 online installer.  When it is missing we build
#     WITHOUT the mqtt page instead of failing, so `make` keeps working on a
#     plain Qt6 kit.  Install "Qt Mqtt" in the Qt Maintenance Tool to enable
#     the page locally too.
#   Never hard-code sysroot include/lib paths here: they are only valid inside
#   the cross sysroot and silently break the host build.
#
#   The actual APP_SOURCES/link wiring happens after set(APP_SOURCES ...) below,
#   because that call would otherwise overwrite the list built here.
# ---------------------------------------------------------------------------
find_package(Qt${QT_VERSION_MAJOR} QUIET COMPONENTS Mqtt)
set(HAVE_QT_MQTT OFF)
if(TARGET Qt${QT_VERSION_MAJOR}::Mqtt)
    set(HAVE_QT_MQTT ON)
endif()

# ---------------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------------
set(APP_SOURCES
    src/main.cpp

    # core (pure logic, no UI)
    src/core/AppEntry.h
    src/core/AppRegistry.h            src/core/AppRegistry.cpp
    src/core/AppLauncher.h            src/core/AppLauncher.cpp
    src/core/ResourceLocator.h        src/core/ResourceLocator.cpp
    src/core/IconUtil.h               src/core/IconUtil.cpp
    src/core/Compat.h

    # app interface + factory
    src/apps/IAppPage.h
    src/apps/AppFactory.h             src/apps/AppFactory.cpp

    # shell (desktop UI, every visual piece is a .ui)
    src/shell/DesktopWindow.h         src/shell/DesktopWindow.cpp        src/shell/DesktopWindow.ui
    src/shell/StatusBar.h             src/shell/StatusBar.cpp            src/shell/StatusBar.ui
    src/shell/DockBar.h               src/shell/DockBar.cpp              src/shell/DockBar.ui
    src/shell/AppTile.h               src/shell/AppTile.cpp              src/shell/AppTile.ui
    src/shell/AppPage.h               src/shell/AppPage.cpp              src/shell/AppPage.ui
    src/shell/PagerWidget.h           src/shell/PagerWidget.cpp
    src/shell/PageIndicator.h         src/shell/PageIndicator.cpp

    # built-in demo apps (templates to be replaced by the user's own apps)
    src/apps/placeholder/PlaceholderPage.h src/apps/placeholder/PlaceholderPage.cpp src/apps/placeholder/PlaceholderPage.ui
    src/apps/camera/CameraPage.h      src/apps/camera/CameraPage.cpp      src/apps/camera/CameraPage.ui

    # NOTE: the mqtt page is appended just below, and only when Qt Mqtt is available.
)

# --- optional MQTT page (see the Qt Mqtt block above) -------------------------
if(HAVE_QT_MQTT)
    list(APPEND APP_SOURCES
        src/apps/mqtt/mqtt_client.h
        src/apps/mqtt/mqtt_client.cpp
        src/apps/mqtt/mqtt_client.ui)
    message(STATUS "TerminalApp: Qt Mqtt found -> MQTT page enabled")
else()
    # Keeps app id "mqtt" registered, so the shell never falls through to the
    # external-process launcher on kits without Qt Mqtt.
    list(APPEND APP_SOURCES src/apps/mqtt/MqttUnavailablePage.cpp)
    message(WARNING "TerminalApp: Qt${QT_VERSION_MAJOR}::Mqtt NOT found -> "
                    "building WITHOUT the MQTT page (see src/apps/mqtt/)")
endif()

add_executable(${PROJECT_NAME} ${APP_SOURCES} resources/resources.qrc)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Network
    #Qt${QT_VERSION_MAJOR}::multimediawidgets
)

if(HAVE_QT_MQTT)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Mqtt)
    # Tells src/apps/AppFactory.cpp to include + register the real mqtt page.
    target_compile_definitions(${PROJECT_NAME} PRIVATE HAVE_QT_MQTT)
endif()

# Embedded builds: keep the binary small (dead-code removal) and strip it.
if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${PROJECT_NAME} PRIVATE -Os -ffunction-sections -fdata-sections)
        target_link_options(${PROJECT_NAME} PRIVATE -Wl,--gc-sections)
    endif()

    # Cross builds ship to the board: drop the symbol table so the executable
    # stays small (Qt dev images often ship a non-stripped toolchain default).
    if(CMAKE_CROSSCOMPILING AND CMAKE_STRIP)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_STRIP} --strip-unneeded $<TARGET_FILE:${PROJECT_NAME}>
            COMMENT "Stripping ${PROJECT_NAME}")
    endif()
endif()

# ---------------------------------------------------------------------------
# Runtime data (config/ + resources/) must sit next to the executable so that
# images and apps.json can be replaced WITHOUT recompiling.
#
# This is an always-run target (not POST_BUILD) on purpose: editing
# config/apps.json does not relink the binary, so a POST_BUILD hook would keep
# serving the stale copy.
# ---------------------------------------------------------------------------
add_custom_target(${PROJECT_NAME}_runtime ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/config"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/config"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/resources"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources"
    COMMENT "Syncing runtime config/ + resources/ next to the executable"
    VERBATIM)
add_dependencies(${PROJECT_NAME}_runtime ${PROJECT_NAME})

# ---------------------------------------------------------------------------
# Install / deployment layout  ->  <prefix>/bin/{terminalApp,config/,resources/}
# ---------------------------------------------------------------------------
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
install(DIRECTORY config/    DESTINATION bin)
install(DIRECTORY resources/ DESTINATION bin)
install(PROGRAMS deploy/run.sh DESTINATION bin)
