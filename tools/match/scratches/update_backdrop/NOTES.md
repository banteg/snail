# update_backdrop @ 0x4112f0

Current scratch: 88.24% (67 target insns, 69 candidate insns), clean masks.

Advances the active backdrop distortion grid and dispatches the split or warped
draw path.

Recovered layout:

- the distortion update iterates columns first, rows second: outer stride
  `+0x18`, inner stride `+0xc0` (`8 * sizeof(BackdropDistortCell)`).
- `BackdropDistortCell::current_x_offset +0x10` is `sin(phase) * x_offset`.
- `BackdropDistortCell::current_y_offset +0x14` is `cos(phase) * y_offset`.
- `backdrop_change_queued +0x4c` is consumed here by calling
  `change_backdrop_real()` and then clearing the byte.
- rendering runs only when `active_primary_texture_id != -1` and
  `backdrop_refresh_pending == 1`; `active_split_backdrop_pair` selects
  `draw_split_backdrop()` vs `render_backdrop()`.

Open source-shape issue: the bit-shadowed phase local recovers the native
8-byte frame and stack compare without using `volatile`, but VC6 still spills
with `fstp [esp+0x10]` followed by integer moves into the cell. Native emits the
tighter `fst [esp+0x10]; fstp [esi]; fld [esp+0x10]` sequence and stores the
sine-derived `current_x_offset` before preparing the cosine argument.

2026-06-21 phase-temporary sweep: address-taken locals, one-element arrays,
struct/union float holders, extra float copies, and explicit x/y offset locals
were neutral at 72.18% because VC6 scalar-replaced the temporary back onto the
x87 stack. A direct bit-shadowed cell store improves the focused score to
88.24% with one additional clean masked operand; the remaining gap is the
float-store scheduling above, not the frame shape.
