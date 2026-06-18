# update_frontend_transition_overlay

Frontend fade overlay state machine on `g_game_base + 0x24`.

- `state == 0`: idle, returns before queueing the overlay quad.
- `state == 1`: fade out to transparent, then idle.
- `state == 2`: fade in to opaque, then hold.
- `state == 3`: advance the hold timer.
- `state == 4`: hand back to fade-out.

The final draw guard is `alpha > 0.01f`, matching the same overlay-quad
threshold used by `draw_frontend_overlay_color_lerp`.

Exact match: 100.00%, 62/62 instructions, with 9 masked operands OK and no
unresolved or mismatched operands. The jump-table displacement is audited
through `update_frontend_transition_overlay_jump_table` at `0x40acd4`.
