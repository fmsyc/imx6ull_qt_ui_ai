#pragma once
//
// Loads an icon from the runtime resources, scaling it to the requested
// logical size and honouring the device pixel ratio. When the image is
// missing a neutral placeholder is returned, so the UI never shows a hole.
//
#include <QPixmap>
#include <QString>

namespace IconUtil {

// relative : path relative to the runtime root, e.g. "resources/icons/x.png"
// logicalPx: target size in logical pixels (square)
QPixmap load(const QString &relative, int logicalPx, const QString &fallbackText = QString());

// Build a gradient rounded-square placeholder.
QPixmap placeholder(const QString &text, int px);

} // namespace IconUtil
