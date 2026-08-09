# initialize_frontend_overlay_color_lerp / cRFlash::Init(int)

Small overlay-color initializer at 0x40ab00. The paired draw helper proves the
layout: `target` lives at `+0x04`, and `current` lives at `+0x14`. The
initializer stores the state word, seeds `target` to white/transparent, and
returns the matching `current` store.

Exact match: 100.00%, 18/18 instructions, with both store_color4f call operands
resolved.

Android independently names the same 0x24-byte owner and identical body
`cRFlash::Init(int)`. That provenance closes `target` and `current` as the
canonical `tColour` owner rather than a frame-local lookalike.

## 2026-08-09 authored-owner promotion

The exact Windows leaf now uses primary authored `cRFlash::Init(int)` with
`FrontendOverlayColorLerp` retained as compatibility vocabulary. The stable
matcher target remains `initialize_frontend_overlay_color_lerp`, and the exact
MSVC symbol is `?Init@cRFlash@@QAEXH@Z`.

Live raw Windows xrefs show one static call at `0x41016c` inside
`initialize_game_assets_and_world`, on the `cRFlash` embedded in each
initialized player. Matching remains exact at 18/18 instructions with both
references clean. No frontend-state or shared-caller score lane was reopened.
