# update_player_movement_flags @ 0x43a1a0

Source-shaped match: 69.77%, 38/64 instruction prefix.

This helper maps the player movement selector at `+0x308` onto the
`movement_flags` mask at `+0x338` and the fire cadence step at `+0x2734`.
When the mask changes from `previous_movement_flags`, it refreshes the
presentation controller at `+0x2984` through `set_snail_weapon`.

Recovered selector table:

- selectors 0, 1, and 2 produce masks `1`, `2`, and `4` with step
  `0.074074075f`;
- selectors 3, 4, and 8 produce masks `8`, `16`, and `144` with step
  `0.111111104f`;
- selectors 6 and 7 produce masks `64` and `192` with step `0.13333334f`;
- selector 5 produces mask `32` with step `0.06666667f`; and
- out-of-range selectors produce mask `129` with step `0.06666667f`.

Residual:

- Native keeps a separate equal-mask block after the changed-mask return,
  reloading `movement_flags` into `ecx` before storing
  `previous_movement_flags`. VC6 tail-merges the equal branch into the changed
  branch's final `mov [previous], eax; pop; ret` sequence for the clean C++
  spelling.
- The target extent also includes the inline switch-table bytes after the final
  `ret`; the object-side table is not emitted in the same text extent, so the
  matcher disassembles padding there. Do not force table bytes or disable
  optimization solely to hide this residual.
- 2026-06-16 shared-`Player` probe: the offsets now exist in `player.h`, but
  including it here changed the switch-table relocation audit from `2 ok` to
  `1 ok, 1 mismatch` (`$L441` instead of
  `update_player_movement_flags_jump_table`). Keep the compact local shell until
  that symbol-shape issue has a targeted fix.
