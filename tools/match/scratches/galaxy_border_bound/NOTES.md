# galaxy_border_bound @ 0x40a0c0

Exact scratch for the small galaxy-route bounds helper called by
`open_galaxy_route`.

Match status: 100.00%, 63/63 instructions, with two masked operands resolved.

Semantics:

- The first four arguments are in/out bounds: `min_x`, `max_x`, `min_y`,
  `max_y`.
- The fifth argument is a `FrontendWidget*`. The helper reads `layout_x +0x238`,
  `layout_y +0x23c`, `layout_width +0x248`, `layout_height +0x24c`, and
  `layout_mode +0x25c`.
- Normal mode expands the aggregate bounds to include the widget rectangle.
- Mode `2` has a special horizontal clamp/centering path before the vertical
  bound expansion.
- The callsites set `ecx` to the galaxy route object, so this is spelled as a
  `Galaxy` member even though the helper only uses stack arguments.
- The mode-2 centering path needs a scoped `width` local for the second
  adjustment. Without that, MSVC emits an equivalent shorter `fsubr mem`
  sequence instead of the native `fld width; fld max; fsub; fsubp` x87 shape.

`open_galaxy_route` independently uses the same widget geometry fields plus the
frame rect at `+0x4c..+0x58` and `layout_center_x +0x260`, so those offsets now
live in `frontend_widget.h` rather than a scratch-local duplicate view.

Android retains the exact 63/63 member as `cRGalaxy::BorderBound(...)`; the
parent rename is codegen-neutral.

## 2026-07-15 Binary Ninja lifecycle replay

Live readback now preserves the true `Galaxy*` receiver, four float in/out
bounds, and the `FrontendWidget*` client. Matching remains exact at 63/63 with
two clean operands.
