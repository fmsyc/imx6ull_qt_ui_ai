#!/bin/sh
# ---------------------------------------------------------------------------
# Run the desktop shell on the board.
#
# Usage:  ./run.sh                       -> linuxfb (/dev/fb0, no X needed)
#         QT_QPA_PLATFORM=xcb ./run.sh   -> inside the image's X server (xcb)
#         ./run.sh --fullscreen
#
# NOTE: this SDK (fsl-imx-x11 4.1.15-2.1.0) ships only the linuxfb and xcb
# platform plugins - there is NO eglfs plugin in it, so QT_QPA_PLATFORM=eglfs
# just aborts with "This application failed to start because no Qt platform
# plugin could be initialized".
# ---------------------------------------------------------------------------
set -e

APP_DIR=$(cd "$(dirname "$0")" && pwd)
APP="$APP_DIR/TerminalApp"

if [ ! -x "$APP" ]; then
    echo "run.sh: $APP not found or not executable" >&2
    exit 1
fi

# --- Qt platform -------------------------------------------------------------
export QT_QPA_PLATFORM="${QT_QPA_PLATFORM:-linuxfb}"

case "$QT_QPA_PLATFORM" in
    linuxfb)
        # pick the framebuffer explicitly; override with QT_QPA_FBDEV
        [ -n "$QT_QPA_FBDEV" ] && export QT_QPA_FBDEV
        export QT_QPA_FB_DRM="${QT_QPA_FB_DRM:-0}"
        ;;
    eglfs)
        echo "run.sh: warning - this SDK has no eglfs plugin, falling back to linuxfb" >&2
        export QT_QPA_PLATFORM=linuxfb
        ;;
esac

# --- fonts -------------------------------------------------------------------
# Point Qt at the fonts installed on the target rootfs.
if [ -d /usr/share/fonts ]; then
    export QT_QPA_FONTDIR=/usr/share/fonts
fi

# --- plugins -----------------------------------------------------------------
# Yocto Qt5 installs its plugins in /usr/lib/plugins (NOT /usr/lib/qt5/plugins).
# Resolve the real directory first; if none exists, leave Qt's compiled-in
# default untouched instead of pointing it at a path that does not exist.
if [ -z "$QT_PLUGIN_PATH" ]; then
    for _p in /usr/lib/plugins /usr/lib/qt5/plugins /usr/local/lib/plugins; do
        if [ -d "$_p/platforms" ]; then
            export QT_PLUGIN_PATH="$_p"
            break
        fi
    done
fi

# Keep extra plugins next to the app so it runs from any directory.
if [ -d "$APP_DIR/plugins" ]; then
    export QT_PLUGIN_PATH="$APP_DIR/plugins${QT_PLUGIN_PATH:+:$QT_PLUGIN_PATH}"
fi

# The platform plugin directory must follow the resolved QT_PLUGIN_PATH.
_first_plugin_dir="${QT_PLUGIN_PATH%%:*}"
if [ -n "$_first_plugin_dir" ] && [ -d "$_first_plugin_dir/platforms" ]; then
    export QT_QPA_PLATFORM_PLUGIN_PATH="$_first_plugin_dir/platforms"
fi

# --- shared libraries ---------------------------------------------------------
# The shell links Qt Mqtt (libQt5Mqtt.so.5).  Board rootfs images that were
# built without the qt-mqtt package will fail to start with
#   "error while loading shared libraries: libQt5Mqtt.so.5"
# Detect it here and explain instead of letting the loader print a bare error.
if command -v ldd >/dev/null 2>&1; then
    if ldd "$APP" 2>/dev/null | grep -q "libQt5Mqtt.so.5 => not found"; then
        echo "run.sh: libQt5Mqtt.so.5 not found on this rootfs." >&2
        echo "run.sh: install the qt-mqtt package, or copy libQt5Mqtt.so.5* into " >&2
        echo "run.sh: the same directory as the app and set LD_LIBRARY_PATH=. " >&2
        exit 127
    fi
fi

exec "$APP" "$@"