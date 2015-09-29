WAYLAND_GFX_ENABLE ?= "0"

BBMASK .= "|libegl|libgbm|wayland-kms|wayland-wsegl"
BBMASK .= "|meta-renesas/meta-rzg1/recipes-graphics/mesa"
BBMASK .= "|meta-renesas/meta-rzg1/recipes-graphics/cogl"
