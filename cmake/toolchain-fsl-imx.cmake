# ---------------------------------------------------------------------------
# CMake toolchain: NXP/Freescale Yocto SDK  (fsl-imx-x11 4.1.15-2.1.0)
#                  i.MX6ULL / Cortex-A7, armv7ve hard-float, Qt 5.12.9
# ---------------------------------------------------------------------------
# Kept for backwards compatibility with older build scripts.  All of the logic
# now lives in cmake/toolchain-board.cmake -- this file only pins the SDK root
# that it used to hard-code.
#
#   make board
#
# or manually:
#
#   cmake -S . -B build-board \
#         -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-fsl-imx.cmake \
#         -DSDK_ROOT=/opt/fsl-imx-x11/4.1.15-2.1.0
#   cmake --build build-board -j
# ---------------------------------------------------------------------------

if(NOT DEFINED SDK_ROOT)
    set(SDK_ROOT "/opt/fsl-imx-x11/4.1.15-2.1.0" CACHE PATH "Yocto SDK install root")
endif()

include("${CMAKE_CURRENT_LIST_DIR}/toolchain-board.cmake")
