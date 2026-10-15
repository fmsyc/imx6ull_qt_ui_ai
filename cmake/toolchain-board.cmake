# ---------------------------------------------------------------------------
# CMake toolchain: 正点原子 i.MX6ULL  (Cortex-A7 / armv7ve / hard-float)
# ---------------------------------------------------------------------------
# This is the ONE cross toolchain file the project uses.  It understands two
# kinds of setups and picks the right one automatically:
#
#   1) Yocto / FSL SDK  (the SDK that ships with the board image)
#         /opt/fsl-imx-x11/4.1.15-2.1.0          -> Qt 5.12.9, sysroot, host moc/uic/rcc
#      Detected as soon as <SDK_ROOT>/sysroots/<host>/usr/bin/<prefix>-gcc and
#      <SDK_ROOT>/sysroots/<machine> exist.  Nothing has to be sourced in the
#      shell -- having `environment-setup-*` sourced is also fine.
#
#   2) plain cross toolchain (no Yocto SDK, e.g. a Linaro gcc)
#         -DCROSS_PREFIX=arm-linux-gnueabihf- \
#         -DBOARD_SYSROOT=/path/to/rootfs -DBOARD_QT_ROOT=/path/to/qt/cmake
#
# Usage (nothing else in the project has to change):
#
#   cmake -S . -B build-board \
#         -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-board.cmake \
#         -DSDK_ROOT=/opt/fsl-imx-x11/4.1.15-2.1.0
#   cmake --build build-board -j
#
#   # or simply
#   make board
# ---------------------------------------------------------------------------

# --- 1. which SDK? -----------------------------------------------------------
# Default matches the SDK shipped with the board image.  Override on the command
# line (-DSDK_ROOT=...) or through the environment; set it to "" to force the
# plain-toolchain path below.
if(NOT DEFINED SDK_ROOT AND DEFINED ENV{SDK_ROOT})
    set(SDK_ROOT "$ENV{SDK_ROOT}")
endif()
if(NOT DEFINED SDK_ROOT)
    set(SDK_ROOT "/opt/fsl-imx-x11/4.1.15-2.1.0")
endif()

set(SDK_MACHINE       "cortexa7hf-neon-poky-linux-gnueabi" CACHE STRING "Yocto SDK target tuple")
set(SDK_HOST_ARCH     "x86_64-pokysdk-linux"               CACHE STRING "Yocto SDK host tuple")
set(SDK_TARGET_PREFIX "arm-poky-linux-gnueabi"             CACHE STRING "Yocto cross tool prefix")

set(_sdk_native "${SDK_ROOT}/sysroots/${SDK_HOST_ARCH}")
set(_sdk_target "${SDK_ROOT}/sysroots/${SDK_MACHINE}")
set(_sdk_bin    "${_sdk_native}/usr/bin/${SDK_TARGET_PREFIX}")

set(_use_yocto FALSE)
if(SDK_ROOT)
    if(EXISTS "${_sdk_bin}/${SDK_TARGET_PREFIX}-gcc" AND EXISTS "${_sdk_target}/usr/include")
        set(_use_yocto TRUE)
    endif()
endif()

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# --- 2. Yocto / FSL SDK ------------------------------------------------------
if(_use_yocto)
    message(STATUS "Toolchain: Yocto SDK  ${SDK_ROOT}  (sysroot=${SDK_MACHINE})")

    set(CMAKE_SYSROOT "${_sdk_target}")

    set(CMAKE_C_COMPILER   "${_sdk_bin}/${SDK_TARGET_PREFIX}-gcc")
    set(CMAKE_CXX_COMPILER "${_sdk_bin}/${SDK_TARGET_PREFIX}-g++")
    set(CMAKE_AR           "${_sdk_bin}/${SDK_TARGET_PREFIX}-ar")
    set(CMAKE_RANLIB       "${_sdk_bin}/${SDK_TARGET_PREFIX}-ranlib")
    set(CMAKE_STRIP        "${_sdk_bin}/${SDK_TARGET_PREFIX}-strip")
    set(CMAKE_READELF      "${_sdk_bin}/${SDK_TARGET_PREFIX}-readelf")

    # Yocto's Qt5Config.cmake is a *template*: it only creates the
    # Qt5::moc / Qt5::uic / Qt5::rcc imported targets when the host tool
    # directory is announced through these OE_QMAKE_* variables.  Without them
    # CMake aborts with:
    #   "Could not find moc executable target Qt5::moc"
    #   "Skipping because OE_QMAKE_PATH_EXTERNAL_HOST_BINS is not defined"
    set(OE_QMAKE_PATH_HOST_BINS          "${_sdk_native}/usr/bin" CACHE PATH   "SDK host Qt tools")
    set(OE_QMAKE_PATH_EXTERNAL_HOST_BINS "${_sdk_native}/usr/bin" CACHE PATH   "SDK host Qt tools (external)")
    set(OE_QMAKE_BIN_SUFFIX              ""                         CACHE STRING "Qt tool name suffix")

    # tuning must match the ABI of the board rootfs (see environment-setup-*)
    set(_arch "-march=armv7ve -mtune=cortex-a7 -mfpu=neon -mfloat-abi=hard")

    # Programs (moc/uic/rcc) run on the host -> NEVER look inside the sysroot.
    # Headers/libraries/packages must come from the sysroot only.
    set(CMAKE_FIND_ROOT_PATH "${_sdk_target}")
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# --- 3. plain cross toolchain (no Yocto SDK) ---------------------------------
else()
    if(NOT CROSS_PREFIX)
        if(DEFINED ENV{CROSS_PREFIX})
            set(CROSS_PREFIX "$ENV{CROSS_PREFIX}")
        else()
            set(CROSS_PREFIX "arm-linux-gnueabihf-")
        endif()
    endif()
    message(STATUS "Toolchain: plain cross compiler '${CROSS_PREFIX}' (no Yocto SDK at '${SDK_ROOT}')")

    set(CMAKE_C_COMPILER   "${CROSS_PREFIX}gcc")
    set(CMAKE_CXX_COMPILER "${CROSS_PREFIX}g++")
    set(CMAKE_STRIP        "${CROSS_PREFIX}strip")

    # Optional target sysroot ("/usr/include" + "/usr/lib" of the rootfs).
    set(BOARD_SYSROOT "" CACHE PATH "Target sysroot containing /usr/include and /usr/lib")
    if(BOARD_SYSROOT)
        set(CMAKE_SYSROOT "${BOARD_SYSROOT}")
        set(CMAKE_FIND_ROOT_PATH "${BOARD_SYSROOT}")
    endif()

    # Directory that holds Qt5Config.cmake, e.g. <sysroot>/usr/lib/cmake
    set(BOARD_QT_ROOT "" CACHE PATH "Directory containing Qt5Config.cmake")
    if(BOARD_QT_ROOT)
        list(APPEND CMAKE_PREFIX_PATH "${BOARD_QT_ROOT}")
        list(APPEND CMAKE_FIND_ROOT_PATH "${BOARD_QT_ROOT}")
    endif()

    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    if(CMAKE_FIND_ROOT_PATH)
        set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
        set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
        set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
    endif()

    set(_arch "-march=armv7ve -mtune=cortex-a7 -mfpu=neon -mfloat-abi=hard")
endif()

# --- 4. arch flags for every translation unit --------------------------------
set(CMAKE_C_FLAGS_INIT   "${_arch} -O2 -pipe")
set(CMAKE_CXX_FLAGS_INIT "${_arch} -O2 -pipe")

set(CMAKE_INSTALL_PREFIX "/opt/terminalApp" CACHE PATH "on-board install prefix")
