# open_galaxy_route @ 0x409c50

Relationship-first scratch for the galaxy route panel opener.

Current local field evidence:
- `+0x04` is a route/menu mode checked against `2` before showing the continue
  widget.
- `+0x08` is the route panel state; opening writes `1`, while
  `close_galaxy_route` clears it.
- Selected route slots stride `0x2a0` from `this +0x10`; each owns a four-byte
  prefix followed by its record at slot `+0x04` (`this +0x14` for slot zero).
  Known record fields are `route_name_index +0x00`, `map_x/map_y +0x08/+0x0c`,
  detail text `+0x1c`, and description text `+0x9c`.
- `+0x10930` is a `0xa0`-stride route-name string table.
- `+0x10f70` is a borrowed backlink to the enclosing `SubgameRuntime`, not an
  independently owned progress table. Its native `+0x944150` route-record
  base resolves exactly to `SubgameRuntime::sub_high_score +0x2b8c88`, the
  owned `time_trial_route_records[]` bank; its `0x1fac0` stride is
  `sizeof(SubSolution)`.
- `+0x10f80` caches the selected record index.
- `+0x10f8c..+0x10fa0` are the frame/title/detail/description/back/continue
  widget pointers also used by `close_galaxy_route`.
- `open_galaxy_route` and `galaxy_border_bound` now agree on frontend-widget
  geometry fields at `+0x4c..+0x58`, `+0x238..+0x260`, so these are promoted
  into `frontend_widget.h` instead of being accessed through raw casts.

The `Galaxy` layout is now promoted after agreement with
`load_galaxy_layout`, `initialize_galaxy`, `update_galaxy`, and
`close_galaxy_route`; this opener keeps the alternate widget names used by the
route-card source through shared header aliases.

The corrected 101-slot ownership, `0x29c` record body, and typed enclosing
subgame backlink remain codegen-neutral: focused matching stays exact at
266/266 with all 41 operands clean.

Android/iOS retain this member as `cRGalaxy::BoxOn(int)`; their bodies perform
the same selected-card text, widget stacking, replay-control gate, bounds pass,
and reposition loop. Mobile `cRGalaxy::Open(int)` instead contains the authored
galaxy-file bootstrap recovered at Windows `load_galaxy_layout`.

The authored BoxOn contract is `void`. Every Windows callsite discards the
result except exact `initialize_galaxy`, which only tail-forwarded the same
incidental widget pointer; its caller also discards it. Promoting both members
to void is codegen-neutral: this function remains exact at 266/266 with 41
clean operands, and `initialize_galaxy` remains exact at 338/338 with 74 clean
operands. The complete Galaxy parent extent remains 0x10fa8.

## 2026-07-15 Binary Ninja lifecycle replay

Live readback now records
`void __thiscall open_galaxy_route(Galaxy*, int32_t selected_level_index)`.
The focused export retains route-slot/name ownership, the borrowed subgame
backlink, every route-card widget, and the typed bounds-helper calls. Matching
remains exact at 266/266 with 41 clean operands.
