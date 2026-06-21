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
- Some data-address operands remain symbolic in the scratch (builtins table,
  config max).
- The two large switch tables have the right mode semantics but not native
  table placement/code layout yet.

2026-06-20 switch-table audit: `initialize_subgame_level_mode_startup_jump_table`
(`0x437adc`) and `initialize_subgame_level_mode_bottom_hud_jump_table`
(`0x437af0`) are now content-audited. Focused matcher remains `63.25%`; masked
audit is now `66 ok / 0 unresolved / 8 mismatch`. The built-in segment
definition table push now resolves as `g_builtin_segment_definitions`; both
mode-switch tables remain classified as real layout mismatches.

2026-06-20 type cleanup: the member-style time-trial formatter receiver moved
to `include/time_trial_string_formatter.h`, matching the same call shape used by
`update_challenge_setup_screen` and `update_subgame`. This removes a duplicate
method-only type row; the focused matcher stayed at 63.25%.

2026-06-20 literal cleanup: replaced the stale scratch-only aliases for the
`"0"`, `"SnailMail.cfg"`, and `"Unknown game mode"` literals with direct string
literals, matching BN's decompile and the target string references. Focused
match remains `63.25%`, but the masked audit improves from `66 ok / 8 mismatch`
to `71 ok / 3 mismatch`. The remaining mismatches are the two switch-table
labels and the known mode-HUD alignment miss where the target's
`border_add_text_number` call aligns against the candidate time-trial formatter
call.

2026-06-21 receiver cleanup: the scratch now defines
`SubgameRuntime::initialize_subgame` directly instead of carrying a method-only
local `Game` shell. Focused Wibo remains `63.25%`, 385/396 candidate
instructions, prefix 1/396, with the same `71 ok / 3 mismatch` masked audit.
`update_frontend_state_machine` was rechecked and remains exact. The type
census now reports `partial-compatible Game: 4`, with this scratch removed from
the remaining generic owner list.
