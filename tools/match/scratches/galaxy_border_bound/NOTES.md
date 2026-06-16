# galaxy_border_bound @ 0x40a0c0

Exact scratch for the small galaxy-route bounds helper called by
`open_galaxy_route`.

Match status: 100.00%, 63/63 instructions, with two masked operands resolved.

Semantics:

- The first four arguments are in/out bounds: `min_x`, `max_x`, `min_y`,
  `max_y`.
- The fifth argument is a frontend-widget-like record. The helper reads
  `x +0x238`, `y +0x23c`, `width +0x248`, `height +0x24c`, and `mode +0x25c`.
- Normal mode expands the aggregate bounds to include the widget rectangle.
- Mode `2` has a special horizontal clamp/centering path before the vertical
  bound expansion.
- The callsites set `ecx` to the galaxy route object, so this is spelled as a
  `GalaxyRoute` member even though the helper only uses stack arguments.
- The mode-2 centering path needs a scoped `width` local for the second
  adjustment. Without that, MSVC emits an equivalent shorter `fsubr mem`
  sequence instead of the native `fld width; fld max; fsub; fsubp` x87 shape.

The widget rect view is intentionally scratch-local. `frontend_widget.h`
currently has some nearby layout fields but does not yet have enough
cross-function evidence to name/promote these exact offsets globally.
