# initialize_subgame

Live source map for `initialize_subgame @ 0x4374b0`.

Current match:

- `100.00%`, `396/396` candidate/target instructions, prefix `396/396`.
- All `85` masked operands resolve cleanly, with no unresolved or mismatched
  operands. The function is proof-grade.

The helper clears the runtime track-cell activity lanes, seeds the front-end
score/time widgets, copies the active level-record timer data, initializes the
static segment/runtime anchors, and dispatches the first subgame state into the
galaxy, challenge-setup, or reset path.

The broad root remains sparse, but every ownership boundary proven by this
function and its teardown consumers now uses a shared type. Unproven gaps stay
raw rather than being assigned speculative owners.

Recovered structure:

- clears 3200 groups of eight runtime cells, zeroing the four directional
  fringe handles at `TrackRowCell +0x44..+0x50` in each `0x54`-byte lane;
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

Ownership recovered:

- The four cell fringe pointers are non-owning handles to `FringeManager`
  allocations. Initialization clears the handles; it does not free through
  the cells.
- `HighScoreBank` is embedded in `SubgameRuntime`. Its `active_record_bank`
  pointer borrows one of the bank's embedded postal, survival, or time-trial
  arrays; `active_level_score` and `active_level_timer` are separate embedded
  display snapshots copied from that record.
- Gameplay score/life widgets are `BorderManager` pool handles retained by the
  subgame. `destroy_subgame` returns them through `kill_border()`; the pointer
  fields do not own inline widget storage.
- The player, warning actor, challenge setup controller, and galaxy route are
  embedded subobjects. `Player::game` is a borrowed backlink to the containing
  subgame, while `cached_camera_target_world` is player-owned state initialized
  from the player's live position.

2026-06-20 switch-table audit: `initialize_subgame_level_mode_bottom_hud_jump_table`
(`0x437adc`) and `initialize_subgame_level_mode_startup_jump_table`
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

2026-07-10 ownership and source-shape pass:

- Duplicating the real mode `0`/`1` score cases and spelling the selected bank
  records through `HighScoreBank` recovered the native control-flow layout.
- Storing each border allocation directly in the subgame handle field, rather
  than extending its lifetime through a local pointer, recovered native's
  manager-handle reload pattern.
- Modeling the opening as an intrinsic 16-byte `memset` of each cell's four
  fringe handles recovered the complete nested clear loop. This is the
  field-level operation evidenced by `TrackRowCell +0x44..+0x50`, not a
  byte-shaped matching shim.
- Typing the embedded player reset recovered the native position-to-camera
  vector copy and warning initialization. Spelling `++level_mode_arg` directly
  recovered the final missing instruction.
- Together these changes raise the function from `63.25%` (`385/396`, prefix
  `1/396`) to `100.00%` (`396/396`, prefix `396/396`). No padding, unreachable
  branches, inline assembly, or register-forcing constructs were introduced.

2026-07-11 jump-table provenance closure:

- Raw target callsites prove the five-entry table at `0x437adc` dispatches the
  bottom HUD, while the eight-entry table at `0x437af0` dispatches startup; the
  previous semantic names were reversed and are now corrected.
- The VC6 object originally emitted those tables as `$L4668` and `$L4669`.
  Adding the recovered blink methods to `SubgameRuntime` renumbered the current
  compiler-local labels to `$L4670` and `$L4671` without changing a single
  instruction or table entry. Both generations remain aliases so the matcher
  can compare bounded table contents rather than trusting names alone.
- Focused matching is now proof-grade at `100.00%`, `396/396`, prefix
  `396/396`, with `85 ok / 0 unresolved / 0 mismatch` masked operands.

2026-07-11 root-bootstrap header refresh:

- Promoting the complete `Overlay`, `SegmentCatalog`, and shared startup-owner
  views renumbered the same VC6 tables again to `$L4685`/`$L4686`.
- COFF symbols place `$L4685` at object `+0x62c` and `$L4686` at `+0x640`.
  Their 5-entry and 8-entry relocation sequences match the already curated
  target tables exactly. Registering both aliases restores the bounded content
  audit; it does not accept the operands by label identity.

2026-07-11 star-manager header refresh:

- Adding the recovered vector in-place scale operator renumbered the same two
  object-local tables to `$L4689`/`$L4690` with no instruction change.
- COFF again places them at object `+0x62c` and `+0x640`; the first has five
  relocations and the second eight, with the same destination sequences as the
  curated bottom-HUD and startup tables. Both aliases are content-bounded by
  their tracked `0x14`/`0x20` sizes.
