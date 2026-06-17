# update_jetpack_gauge @ 0x43a390

Source-shaped partial scratch for the jetpack countdown/warning controller.

Current match: 85.82% (`130` candidate instructions vs `131` target,
`34` clean masked operands).

Recovered behavior:

- native treats state `0` and non-`1` states as immediate returns; only state
  `1` advances `progress` by `progress_step`;
- it ends hover and clears the controller when progress exceeds 1.0 or the
  player passes `game->completion_row_start - 5`;
- it ramps warning intensity at the start, holds it through the middle range,
  and fades it out after `0.94`;
- while in the middle range it samples the current runtime row through
  `get_track_runtime_cell_at_world_z(game+0x74618, game+0x42fde4)` and forces
  `progress = 0.94` when `BYTE1(row->flags) & 0x80` is set, i.e. the 32-bit
  flag mask is `0x8000`;
- once active, it updates wobble x/y/alpha and calls the `spawn_track_speedup`
  no-op thunk with the player position and raw progress bits.

Important corrections made during matching:

- inactive state `0` does not call `end_jetpack_hover`; it returns before any
  cleanup;
- the `0.94` middle/fade branch is naturally expressed as `> 0.94` first, then
  the middle hold branch;
- the empty `spawn_track_speedup` target is `ret 8`, but both known callers set
  `ecx` before the call. This scratch uses a local thiscall-shaped caller to
  recover the native call sequence without promoting the callee's owner yet.

Known residuals:

- VC6 still delays the `xor edi, edi` zero initialization instead of placing it
  before the state switch like native;
- the native state dispatch is `sub eax, edi; je return; dec eax; jne return`,
  while the clean `switch(state)` source recovers the `dec/jne` part but not the
  early zero register setup;
- `game`/`player` loads around the completion-row check use different registers,
  though the field offsets and behavior are aligned.
