# update_backdrop @ 0x4112f0

Current scratch: 72.18% (67 target insns, 66 candidate insns), clean masks.

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

Open source-shape issue: native keeps the updated phase in a stack local before
storing it back to the cell (`fst [esp+0x10]; fstp [esi]; fld [esp+0x10]`),
which gives the function an 8-byte stack frame. The clean source keeps that
value live on the x87 stack and produces a 4-byte frame. Do not close this with
`volatile`; the remaining gap needs a real source idiom for the phase temporary.
