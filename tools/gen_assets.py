#!/usr/bin/env python3
"""
Generate the placeholder artwork used by TerminalApp.

Everything produced here is meant to be REPLACED by your own images: just drop
a file with the same name into resources/ and the app will pick it up at
runtime, without recompiling.

Usage:
    python3 tools/gen_assets.py
"""

import math
import os

from PIL import Image, ImageDraw

HERE = os.path.dirname(os.path.abspath(__file__))
RES = os.path.normpath(os.path.join(HERE, "..", "resources"))
SS = 4  # supersampling factor for crisp edges


# ---------------------------------------------------------------------------
# helpers
# ---------------------------------------------------------------------------
def canvas(size):
    return Image.new("RGBA", (size * SS, size * SS), (0, 0, 0, 0))


def finish(img, size):
    return img.resize((size, size), Image.LANCZOS)


def rounded_gradient(size, c1, c2, radius_frac=0.24):
    """Rounded square filled with a diagonal two-colour gradient."""
    S = size * SS
    small = Image.new("RGBA", (64, 64))
    for y in range(64):
        for x in range(64):
            t = (x + y) / 126.0
            small.putpixel((x, y), (
                int(c1[0] + (c2[0] - c1[0]) * t),
                int(c1[1] + (c2[1] - c1[1]) * t),
                int(c1[2] + (c2[2] - c1[2]) * t),
                255,
            ))
    grad = small.resize((S, S), Image.BILINEAR)

    mask = Image.new("L", (S, S), 0)
    ImageDraw.Draw(mask).rounded_rectangle(
        [0, 0, S - 1, S - 1], radius=int(S * radius_frac), fill=255)

    out = Image.new("RGBA", (S, S), (0, 0, 0, 0))
    out.paste(grad, (0, 0), mask)
    return out


def lw(S, frac):
    return max(2, int(S * frac))


# ---------------------------------------------------------------------------
# glyphs drawn in a normalised 0..1 box on top of an image
# ---------------------------------------------------------------------------
def g_camera(d, S, c):
    w = lw(S, 0.075)
    d.rounded_rectangle([0.16 * S, 0.32 * S, 0.84 * S, 0.80 * S],
                        radius=0.10 * S, outline=c, width=w)
    d.polygon([(0.38 * S, 0.32 * S), (0.44 * S, 0.22 * S),
               (0.56 * S, 0.22 * S), (0.62 * S, 0.32 * S)], fill=c)
    d.ellipse([0.37 * S, 0.43 * S, 0.63 * S, 0.69 * S], outline=c, width=w)


def g_play(d, S, c):
    d.polygon([(0.34 * S, 0.24 * S), (0.34 * S, 0.76 * S),
               (0.76 * S, 0.50 * S)], fill=c)


def g_record(d, S, c):
    d.ellipse([0.26 * S, 0.26 * S, 0.74 * S, 0.74 * S], outline=c, width=lw(S, 0.075))
    d.ellipse([0.38 * S, 0.38 * S, 0.62 * S, 0.62 * S], fill=c)


def g_chip(d, S, c):
    w = lw(S, 0.07)
    d.rounded_rectangle([0.28 * S, 0.28 * S, 0.72 * S, 0.72 * S],
                        radius=0.06 * S, outline=c, width=w)
    d.rectangle([0.42 * S, 0.42 * S, 0.58 * S, 0.58 * S], outline=c, width=w)
    for i in (0.38, 0.5, 0.62):
        d.line([i * S, 0.28 * S, i * S, 0.16 * S], fill=c, width=w)
        d.line([i * S, 0.72 * S, i * S, 0.84 * S], fill=c, width=w)
        d.line([0.28 * S, i * S, 0.16 * S, i * S], fill=c, width=w)
        d.line([0.72 * S, i * S, 0.84 * S, i * S], fill=c, width=w)


def g_gear(d, S, c):
    w = lw(S, 0.07)
    cx, cy, r = 0.5 * S, 0.5 * S, 0.22 * S
    d.ellipse([cx - r, cy - r, cx + r, cy + r], outline=c, width=w)
    d.ellipse([cx - 0.08 * S, cy - 0.08 * S, cx + 0.08 * S, cy + 0.08 * S],
              outline=c, width=w)
    for k in range(8):
        a = k * math.pi / 4
        d.line([cx + math.cos(a) * r, cy + math.sin(a) * r,
                cx + math.cos(a) * (r + 0.12 * S),
                cy + math.sin(a) * (r + 0.12 * S)], fill=c, width=w)


def g_gallery(d, S, c):
    w = lw(S, 0.07)
    d.rounded_rectangle([0.16 * S, 0.24 * S, 0.84 * S, 0.76 * S],
                        radius=0.09 * S, outline=c, width=w)
    d.ellipse([0.26 * S, 0.32 * S, 0.38 * S, 0.44 * S], fill=c)
    d.polygon([(0.24 * S, 0.72 * S), (0.46 * S, 0.50 * S),
               (0.64 * S, 0.72 * S)], fill=c)
    d.polygon([(0.52 * S, 0.72 * S), (0.66 * S, 0.58 * S),
               (0.80 * S, 0.72 * S)], fill=c)


def g_serial(d, S, c):
    w = lw(S, 0.07)
    d.line([0.18 * S, 0.36 * S, 0.82 * S, 0.36 * S], fill=c, width=w)
    d.line([0.18 * S, 0.64 * S, 0.82 * S, 0.64 * S], fill=c, width=w)
    d.ellipse([0.16 * S, 0.30 * S, 0.28 * S, 0.42 * S], fill=c)
    d.ellipse([0.72 * S, 0.58 * S, 0.84 * S, 0.70 * S], fill=c)


def g_wifi(d, S, c):
    w = lw(S, 0.075)
    for r in (0.34, 0.22, 0.10):
        d.arc([0.5 * S - r * S, 0.62 * S - r * S, 0.5 * S + r * S, 0.62 * S + r * S],
              start=215, end=325, fill=c, width=w)
    d.ellipse([0.45 * S, 0.66 * S, 0.55 * S, 0.76 * S], fill=c)


def g_music(d, S, c):
    w = lw(S, 0.07)
    d.line([0.44 * S, 0.24 * S, 0.44 * S, 0.66 * S], fill=c, width=w)
    d.line([0.44 * S, 0.24 * S, 0.74 * S, 0.30 * S], fill=c, width=w)
    d.line([0.74 * S, 0.30 * S, 0.74 * S, 0.58 * S], fill=c, width=w)
    d.ellipse([0.28 * S, 0.60 * S, 0.46 * S, 0.76 * S], fill=c)
    d.ellipse([0.58 * S, 0.52 * S, 0.76 * S, 0.68 * S], fill=c)


def g_radio(d, S, c):
    w = lw(S, 0.07)
    d.ellipse([0.24 * S, 0.24 * S, 0.64 * S, 0.64 * S], outline=c, width=w)
    d.ellipse([0.39 * S, 0.39 * S, 0.49 * S, 0.49 * S], fill=c)
    for r in (0.10, 0.18):
        d.arc([0.64 * S - r * S, 0.44 * S - r * S, 0.64 * S + r * S, 0.44 * S + r * S],
              start=300, end=60, fill=c, width=w)


def g_home(d, S, c):
    w = lw(S, 0.085)
    d.line([0.5 * S, 0.20 * S, 0.16 * S, 0.48 * S], fill=c, width=w)
    d.line([0.5 * S, 0.20 * S, 0.84 * S, 0.48 * S], fill=c, width=w)
    d.line([0.25 * S, 0.44 * S, 0.25 * S, 0.80 * S], fill=c, width=w)
    d.line([0.75 * S, 0.44 * S, 0.75 * S, 0.80 * S], fill=c, width=w)
    d.line([0.25 * S, 0.80 * S, 0.75 * S, 0.80 * S], fill=c, width=w)


def g_nav(d, S, c):
    w = lw(S, 0.08)
    d.polygon([(0.5 * S, 0.18 * S), (0.80 * S, 0.80 * S),
               (0.5 * S, 0.64 * S), (0.20 * S, 0.80 * S)], outline=c, width=w)


def g_volume(d, S, c):
    w = lw(S, 0.08)
    d.polygon([(0.24 * S, 0.40 * S), (0.40 * S, 0.40 * S), (0.56 * S, 0.24 * S),
               (0.56 * S, 0.76 * S), (0.40 * S, 0.60 * S), (0.24 * S, 0.60 * S)],
              fill=c)
    for r in (0.14, 0.24):
        d.arc([0.56 * S - r * S, 0.5 * S - r * S, 0.56 * S + r * S, 0.5 * S + r * S],
              start=300, end=60, fill=c, width=w)


def g_fan(d, S, c):
    w = lw(S, 0.07)
    cx = cy = 0.5 * S
    for k in range(3):
        a = k * 2 * math.pi / 3
        bx = cx + math.cos(a) * 0.20 * S
        by = cy + math.sin(a) * 0.20 * S
        r = 0.16 * S
        d.ellipse([bx - r, by - r, bx + r, by + r], outline=c, width=w)
    d.ellipse([cx - 0.07 * S, cy - 0.07 * S, cx + 0.07 * S, cy + 0.07 * S], fill=c)


def g_mic(d, S, c):
    w = lw(S, 0.10)
    d.rounded_rectangle([0.38 * S, 0.16 * S, 0.62 * S, 0.56 * S],
                        radius=0.12 * S, outline=c, width=w)
    d.arc([0.26 * S, 0.36 * S, 0.74 * S, 0.72 * S], start=200, end=340, fill=c, width=w)
    d.line([0.5 * S, 0.70 * S, 0.5 * S, 0.84 * S], fill=c, width=w)


def g_avatar(d, S, c):
    w = lw(S, 0.10)
    d.ellipse([0.34 * S, 0.18 * S, 0.66 * S, 0.50 * S], outline=c, width=w)
    d.arc([0.16 * S, 0.50 * S, 0.84 * S, 1.06 * S], start=0, end=180, fill=c, width=w)


def g_signal(d, S, c):
    w = lw(S, 0.14)
    for i, h in enumerate((0.28, 0.46, 0.64, 0.82)):
        x = (0.22 + i * 0.19) * S
        d.line([x, (0.86 - h) * S, x, 0.86 * S], fill=c, width=w)


# ---------------------------------------------------------------------------
# asset tables
# ---------------------------------------------------------------------------
APP_ICONS = {
    "app_camera.png":   ((0x5A, 0x73, 0x8C), (0x33, 0x45, 0x59), g_camera),
    "app_media.png":    ((0x3E, 0xC8, 0xF0), (0x1E, 0x8F, 0xD8), g_play),
    "app_record.png":   ((0xF5, 0x6B, 0x6B), (0xD8, 0x35, 0x4B), g_record),
    "app_device.png":   ((0x8B, 0x7C, 0xF0), (0x5B, 0x4B, 0xD8), g_chip),
    "app_settings.png": ((0x8E, 0x9A, 0xAB), (0x5C, 0x68, 0x7A), g_gear),
    "app_gallery.png":   ((0xF2, 0xA5, 0x4B), (0xE0, 0x74, 0x2B), g_gallery),
    "app_serial.png":   ((0x4B, 0xD8, 0xB0), (0x22, 0xA8, 0x86), g_serial),
    "app_network.png":  ((0x5A, 0x7C, 0xFF), (0x2E, 0x4F, 0xD8), g_wifi),
    "app_music.png":    ((0xB0, 0x6B, 0xF0), (0x7A, 0x3B, 0xD8), g_music),
    "app_radio.png":    ((0xFF, 0x9A, 0x5B), (0xE0, 0x5A, 0x2B), g_radio),
}

DOCK_ICONS = {
    "dock_home.png":     g_home,
    "dock_nav.png":      g_nav,
    "dock_volume.png":   g_volume,
    "dock_fan.png":      g_fan,
    "dock_settings.png": g_gear,
}

STATUS_ICONS = {
    "status_mic.png":    (18, g_mic),
    "status_avatar.png": (28, g_avatar),
    "status_wifi.png":   (20, g_wifi),
    "status_signal.png": (20, g_signal),
}

WHITE = (255, 255, 255, 235)


# ---------------------------------------------------------------------------
# background
# ---------------------------------------------------------------------------
def make_background(w=1024, h=576):
    """Ambient desktop wallpaper.

    Everything is computed on a coarse grid and then enlarged with BILINEAR so
    the light is perfectly smooth: no visible ellipse edge, no colour banding,
    and no dark rectangles (the previous version used two hard-edged L masks).

    Layers, bottom to top:
      1. vertical gradient       (top #1B2740 -> bottom #090E18)
      2. soft radial glow        (upper-left-ish, cool blue)
      3. warm counter glow        (lower-right, keeps the middle from going flat)
      4. smooth vignette          (darkens only the far corners)
      5. fine dither              (kills gradient banding on 24-bit panels)
    """
    gw, gh = 128, 72                      # coarse grid -> smooth after resize
    top, bottom = (0x1B, 0x27, 0x40), (0x09, 0x0E, 0x18)

    bg = Image.new("RGB", (gw, gh))
    px = bg.load()
    for y in range(gh):
        t = y / (gh - 1.0)
        # Slight ease-out so the darkening happens mostly near the bottom.
        te = t * t * (3.0 - 2.0 * t)
        te = 0.65 * t + 0.35 * te
        row = (int(top[0] + (bottom[0] - top[0]) * te),
               int(top[1] + (bottom[1] - top[1]) * te),
               int(top[2] + (bottom[2] - top[2]) * te))
        for x in range(gw):
            px[x, y] = row

    # --- smooth radial lights ---------------------------------------------
    def radial(cx, cy, radius, strength, color):
        """Additive light: strength * (1 - d/radius)^2, clamped at 0."""
        for y in range(gh):
            fy = (y + 0.5) / gh - cy
            for x in range(gw):
                fx = (x + 0.5) / gw - cx
                d = math.hypot(fx, fy) / radius
                if d >= 1.0:
                    continue
                k = (1.0 - d) ** 2 * strength
                r, g, b = px[x, y]
                px[x, y] = (min(255, int(r + color[0] * k)),
                            min(255, int(g + color[1] * k)),
                            min(255, int(b + color[2] * k)))

    radial(0.42, 0.20, 0.72, 0.30, (0x44, 0x66, 0xAF))   # main cool glow
    radial(0.82, 0.86, 0.55, 0.14, (0x3A, 0x4A, 0x7A))   # faint bottom-right lift

    # --- smooth vignette (only the corners get dark) -----------------------
    rmax = math.hypot(0.5, 0.5)
    for y in range(gh):
        fy = (y + 0.5) / gh - 0.5
        for x in range(gw):
            fx = (x + 0.5) / gw - 0.5
            d = math.hypot(fx, fy) / rmax
            k = max(0.0, (d - 0.45) / 0.55) ** 1.6 * 0.42
            if k <= 0.0:
                continue
            r, g, b = px[x, y]
            f = 1.0 - k
            px[x, y] = (int(r * f), int(g * f), int(b * f))

    bg = bg.resize((w, h), Image.BILINEAR)

    # --- dither to remove banding -----------------------------------------
    bg = bg.convert("RGB")
    noise = Image.effect_noise((w, h), 6.0).point(lambda v: int(v * 0.5))
    bg = Image.blend(bg, Image.merge("RGB", (noise, noise, noise)), 0.030)
    return bg


# ---------------------------------------------------------------------------
# main
# ---------------------------------------------------------------------------
def main():
    icons_dir = os.path.join(RES, "icons")
    bg_dir = os.path.join(RES, "background")
    os.makedirs(icons_dir, exist_ok=True)
    os.makedirs(bg_dir, exist_ok=True)

    for name, (c1, c2, glyph) in APP_ICONS.items():
        size = 160
        img = rounded_gradient(size, c1, c2)
        d = ImageDraw.Draw(img)
        glyph(d, size * SS, WHITE)
        finish(img, size).save(os.path.join(icons_dir, name))
        print("wrote", name)

    for name, glyph in DOCK_ICONS.items():
        size = 80
        img = canvas(size)
        glyph(ImageDraw.Draw(img), size * SS, WHITE)
        finish(img, size).save(os.path.join(icons_dir, name))
        print("wrote", name)

    for name, (size, glyph) in STATUS_ICONS.items():
        img = canvas(size)
        glyph(ImageDraw.Draw(img), size * SS, WHITE)
        finish(img, size).save(os.path.join(icons_dir, name))
        print("wrote", name)

    make_background().save(os.path.join(bg_dir, "desktop.png"))
    print("wrote desktop.png")


if __name__ == "__main__":
    main()
