# update_invincible_shell @ 0x444b50

First source-shaped scratch for the runner-owned invincible-shell controller.

Recovered behavior:

- state 0 either starts the shell while the player invincible bit
  `g_game_base+0x4300b4 & 0x80` is active, or clears the shell render bit
  `g_game_base+0x433f98 & ~0x20`;
- state 1 fades in to `1.0` and moves to state 2, but drops to state 3 as soon
  as the invincible bit clears;
- state 2 waits for that bit to clear;
- state 3 fades out, restores base snail skin slot 0 at zero, and returns to
  state 0 once the fade goes below zero;
- active states advance `spin_phase`, apply invincible skin slot 2, write white
  color with alpha `fade_progress * 0.80000001`, copy the live snail matrix
  from `g_game_base+0x432738`, then rotates it around world Y by
  `spin_phase * 6.2831855`.

Focused Wibo result: exact 100%, 98/98 insns, 98/98 prefix, and 28 clean masked
operands. The exact match required inlining the `g_game_base+0x4300b4` bit tests;
a helper function was source-clean but introduced calls and an extra saved
register, regressing to 68.39%.
