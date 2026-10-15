#!/bin/sh
# ---------------------------------------------------------------------------
# Demo of an "external" app: an ordinary executable that the desktop spawns
# with QProcess. Replace the body with your own demo binary and point
# config/apps.json at it, e.g.
#
#   { "id": "my-app", "name": "我的应用", "icon": "resources/icons/app_settings.png",
#     "type": "external", "exec": "/opt/demo/my_app" }
#
# On the desktop dev machine a GUI app would simply open its own window; on the
# board (EGLFS) it would take over the framebuffer / a separate layer.
# ---------------------------------------------------------------------------
LOG=/tmp/terminalapp_external.log

echo "[$(date '+%F %T')] external demo app started (pid $$)" >> "$LOG"
echo "external demo app: see $LOG"

# Keep alive briefly so the launcher's "running" bookkeeping is observable.
sleep 2
exit 0
