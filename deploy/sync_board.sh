#!/bin/sh
# ---------------------------------------------------------------------------
# Sync the built shell + its runtime data to the board.
#
# Usage:
#   deploy/sync_board.sh root@192.168.1.20:/opt/terminalApp
#
# It copies the executable, config/ and resources/ (NOT the build tree), so
# changing an image or config/apps.json on the board needs no rebuild.
# ---------------------------------------------------------------------------
set -e

DEST="${1:?usage: sync_board.sh user@host:/remote/dir}"
BUILD_DIR="${BUILD_DIR:-build}"

if [ ! -d "$BUILD_DIR" ]; then
    echo "sync_board.sh: '$BUILD_DIR' not found - build first" >&2
    exit 1
fi

APP="$BUILD_DIR/TerminalApp"
if [ ! -x "$APP" ]; then
    echo "sync_board.sh: $APP not found in $BUILD_DIR" >&2
    exit 1
fi

echo ">>> syncing to $DEST"
ssh "${DEST%%:*}" "mkdir -p '${DEST#*:}'"
rsync -av --delete \
      "$APP" \
      "$BUILD_DIR/config" \
      "$BUILD_DIR/resources" \
      "${DEST}/"

echo ">>> done. On the board:"
echo "    cd ${DEST#*:} && ./run.sh"
