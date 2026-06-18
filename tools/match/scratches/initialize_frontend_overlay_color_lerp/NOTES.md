# initialize_frontend_overlay_color_lerp

Small overlay-color initializer at 0x40ab00. The paired draw helper proves the
layout: `target` lives at `+0x04`, and `current` lives at `+0x14`. The
initializer stores the state word, seeds `target` to white/transparent, and
returns the matching `current` store.

Exact match: 100.00%, 18/18 instructions, with both store_color4f call operands
resolved.
