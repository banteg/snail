# initialize_galaxy @ 0x408cf0

First structural scratch for the galaxy/star-map screen initializer. This uses
the shared `Galaxy` layout while reusing established frontend-widget,
color, star-field, backdrop, landscape-bank, and mouse cursor helpers.

The scratch is intentionally relationship-first. Widget post-init lanes use
the shared `FrontendWidget` owner wherever exact sibling consumers establish
their meaning.

2026-06-20 proof result: 100.00%, 338/338 candidate/target instructions,
prefix 338/338, and 74 masked operands clean.

2026-06-19 retained result: 97.92%, 336/338 candidate/target instructions,
prefix 113/338, and 74 masked operands clean. The residual was two branch
families where VC6 hoisted the `tColour` stack receiver setup before the
Exit/Back and Play/Deliver branches.

Recovered ownership:

- `data_4a2128` is the main-menu music path passed to `cache_music_file`.
- `data_4df9bc` is reused as the selected galaxy route/backdrop selector for
  route modes 0 and 2.
- `Galaxy::level_progress_base` is a borrowed backlink to the enclosing
  `SubgameRuntime`. The initializer reads `level_mode`, `level_mode_arg`, and
  `subgame_rebuild_selector` directly through that owner; it does not consult
  a separate progress allocation.
- `data_4a20f4` and `data_4a20ec` are the Exit and Back widget labels.
- The bounds frame selects border texture `152`, seeds its `frame_x`,
  `frame_y`, `frame_width`, and `frame_height`, and forces its hot fill color
  to opaque white. `open_galaxy_route` later recomputes those same four frame
  fields from the selected widgets' measured bounds.

Scoped-color proof:

- Branch-local `tColour*` aliases and `tColour&` references are codegen-neutral
  and still hoist `lea ecx, [esp+0x24]` before the branch.
- True branch-local `tColour` objects fix the branch-local receiver setup but
  grow the frame to `0x20`, so that shape is not native.
- Splitting the one long-lived `tColour color` into short non-overlapping
  scopes lets VC6 reuse the same 0x10 stack slot while keeping the receiver
setup inside the Exit/Back and Play/Deliver arms. This matches the native
duplicated branch receivers and proves the initializer.

2026-07-11 authored owner: this exact 338/338 member maps to
`cRGalaxy::Init()`. `sizeof(Galaxy) == 0x10fa8` closes the embedded owner at
`SubgameRuntime +0x1270fc8`; the final dword remains conservatively unnamed.

2026-07-12 void contract: every caller consumes initialization side effects and
discards the tail-forwarded route-card pointer. Mobile `cRGalaxy::Init()` and
its final `BoxOn` handoff likewise establish no semantic return. Promoting both
Windows members to void is codegen-neutral and keeps this initializer exact at
338/338 instructions with 74 clean operands.

2026-07-13 root-owner cleanup: star field, landscape bank, backdrop, border
pool, player-zero mouse, and render-skip countdown now use their canonical
`GameRoot` members. The screen-local `GalaxyBorderManager` pseudo-type is
removed. Exact output remains 338/338 with all 74 operands clean.

2026-07-14 route-slot ownership: the two-dword reset cursor now starts at
`GalaxyRouteSlot::record.highlight_target_bits`; its preceding dword is the
adjacent `route_tint_alpha_bits`, and its step derives from
`sizeof(GalaxyRouteSlot)`. This removes the raw `this + 0x2c` base and literal
168-dword stride while preserving the exact 338/338 function and all 74 clean
operands.

2026-07-14 widget-field ownership: five title, detail, description, and replay
scale stores now use `FrontendWidget::font_scale`. The field is independently
used by frontend-widget initialization, subgame HUD setup, text layout, and the
thanks screen; exact output remains 338/338 with all 74 operands clean.

2026-07-14 bounds-frame ownership: the final six raw widget offsets now use
`FrontendWidget::hot_fill_color`, `border_texture_id`, and the four `frame_*`
members. The exact `open_galaxy_route` consumer independently overwrites and
reads the same bounds fields after measuring the route-card stack. Focused Wibo
remains exact at 338/338 instructions with all 74 operands clean.

## 2026-07-15 Binary Ninja lifecycle replay

Live readback now records `void __thiscall initialize_galaxy(Galaxy*)`. The
focused export retains the enclosing `SubgameRuntime*` backlink, all nine
widget owners, and the final typed `open_galaxy_route(galaxy,
galaxy->selected_index)` handoff. Matching remains exact at 338/338 with 74
clean operands.
