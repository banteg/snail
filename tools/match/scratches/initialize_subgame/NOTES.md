# initialize_subgame

First scratch for `initialize_subgame @ 0x4374b0`.

The helper clears the runtime track-cell activity lanes, seeds the front-end
score/time widgets, copies the active level-record timer data, initializes the
static segment/runtime anchors, and dispatches the first subgame state into the
galaxy, challenge-setup, or reset path.

This scratch intentionally keeps the broad `Game` layout as raw offsets while
using shared front-end, color, backdrop, timer, and landscape-script helper
types where those are already cross-checked by smaller scratches.

Recovered structure:

- clears 3200 groups of eight runtime cells, zeroing the first four dwords of
  each 0x54-byte lane;
- selector `1`/`2` reloads the main-menu music, menu backdrop, and centered
  border state;
- level modes `0`, `1`, and `4` copy the active level record pointer, score,
  and 0x18-byte timer counters into the runtime slots;
- the HUD setup allocates the top/bottom score widgets plus the mode-0 life
  icon and nine life markers;
- bottom-score dispatch matches the decompiler: modes `0` and `1` add the
  copied score, modes `2` and `3` hide both widgets, and mode `4` formats the
  copied timer counters;
- final dispatch routes selector-backed startup into galaxy, challenge setup,
  replay speed, or reset paths.

Known partials:

- The opening clear loop still differs in register allocation from native
  (`edi` active cell / `edx` outer count in native).
- Several string and data-address operands remain symbolic in the scratch
  (`"0"`, `SnailMail.cfg`, `Unknown game mode`, builtins table, config max).
- The two large switch tables have the right mode semantics but not native
  table placement/code layout yet.

2026-06-20 type cleanup: the member-style time-trial formatter receiver moved
to `include/time_trial_string_formatter.h`, matching the same call shape used by
`update_challenge_setup_screen` and `update_subgame`. This removes a duplicate
method-only type row; the focused matcher stayed at 63.25%.
