# update_thanks_for_playing_screen

- Void thiscall state-machine updater for the thanks-for-playing screen.
- `message_progress` at `+0x0c` is an x87 float accumulator; the stale `eax`
  return is just compare/call residue.
- The click/key path only starts fade-out once message state is at least `2`
  and the frontend fade state at `g_game_base + 0x24` is idle.
