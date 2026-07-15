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
- `SubHighScore` is embedded in `SubgameRuntime`. Its `active_record_bank`
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

2026-07-14 final initializer ownership cleanup: the remaining raw receiver
offsets now use `SubgameRuntime::pause_fade_step`, embedded `TimesUp::state`,
and `FrontendWidget::texture_layer` for the two retained HUD handles. This
removes the scratch-local byte view entirely while preserving exact 396/396
output and all 85 clean operands.

2026-06-20 switch-table audit: `initialize_subgame_level_mode_bottom_hud_jump_table`
(`0x437adc`) and `initialize_subgame_level_mode_startup_jump_table`
(`0x437af0`) are now content-audited. Focused matcher remains `63.25%`; masked
audit is now `66 ok / 0 unresolved / 8 mismatch`. The built-in segment
definition table push now resolves as `g_builtin_segment_definitions`; both
mode-switch tables remain classified as real layout mismatches.

2026-06-20 type cleanup: the member-style time-trial formatter receiver moved
to `include/time_trial.h`, matching the same call shape used by
`update_challenge_setup_screen` and `update_subgame`. This removes a duplicate
method-only type row; the focused matcher stayed at 63.25%.

2026-07-11 TimeTrial ownership: the three HUD calls now target the embedded
`time_trial` object directly. Its +0xff25e0 placement and 0x330 extent are fixed
by the following PathManager and size ledger; focused matching remains exact at
396/396 instructions.

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
  records through `SubHighScore` recovered the native control-flow layout.
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

2026-07-11 shared-root-header alias replay: the manager inheritance headers
renumber the current object tables to `$L4716`/`$L4717` without changing any
instruction. COFF symbols and relocations place `$L4716` at object offset
`0x62c` with five entries through `0x63c`, and `$L4717` at `0x640` with eight
entries through `0x65c`; those bounded sizes reassign the bottom-HUD/startup
aliases respectively and restore the 85 clean operands.

2026-07-11 root-bootstrap header refresh:

- Promoting the complete `Overlay`, `SMTracks`, and shared startup-owner
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
- Promoting the paired vector-add operator advances only the compiler-local
  labels to `$L4693`/`$L4694`; their object offsets and bounded relocation
  contents remain identical, so this generation is registered as well.

2026-07-11 frame-renderer header refresh:

- Promoting the shared sprite depth workspace advances the two local labels to
  `$L4712`/`$L4713`, while their object offsets remain `+0x62c`/`+0x640`.
- The five bottom-HUD destinations and eight startup destinations remain
  byte-for-byte identical to the curated target-relative sequences. Registering
  these aliases restores bounded content proof without touching the exact
  function body.

2026-07-11 presentation-owner header refresh:

- Naming the player presentation constructor and its callback fields advances
  the same local labels to `$L4715`/`$L4716`; the tables remain at object
  `+0x62c`/`+0x640`.
- Their five- and eight-entry relocation targets are unchanged and still equal
  the curated target-relative sequences, so both aliases remain content-audited
  rather than trusted by spelling.

2026-07-11 contact-target header refresh:

- Promoting the real contact registry advances the two table labels again to
  `$L4718`/`$L4719`; their object offsets stay `+0x62c`/`+0x640`.
- The matcher content audit confirms the same five bottom-HUD and eight startup
  destination sequences. Both aliases are recorded, restoring 396/396 exact
  proof with 85 clean masked operands and no source-body change.

2026-07-11 border-owner header refresh:

- Adding the recovered `FrontendWidget::border_mouse_test()` declaration moves
  the same tables to `$L4719`/`$L4720`, still at object `+0x62c`/`+0x640`.
- `$L4719` is reassigned from its prior startup-table spelling to the current
  bottom-HUD table, avoiding an ambiguous local-label alias. The bounded five-
  and eight-entry contents remain identical and restore 85 clean masked
  operands without changing the exact 396-instruction method body.

2026-07-11 shared-device header refresh:

- Expanding the common IDirect3DDevice8 vtable advances the two compiler-local
  labels to `$L4782`/`$L4783`, still at object `+0x62c`/`+0x640`.
- Their five bottom-HUD and eight startup relocations remain identical to the
  bounded target tables. Registering these contents restores 396/396 exact
  proof with all 85 operands clean; no source instruction changed.

2026-07-11 runtime-config header refresh:

- Replacing three independent config globals with the recovered aggregate moves
  the bottom-HUD table's compiler-local label to `$L4825`; its instruction site
  and bounded five-entry target table are unchanged.
- The aggregate also makes the `+0xa0` highest-route update, the `+0xa4`
  landscape selector, and the exact `0xc4` save extent explicit. Registering
  the table's new local spelling restores 396/396 proof with all 85 operands
  clean and no generated instruction change.

2026-07-11 level-definition scratch ownership:

- The built-in reset now targets the embedded
  `level_definition_scratch +0x1b01ec` rather than an oversized standalone
  slot-store cast. The exact constructor and startup enumeration prove this is
  the second complete `0x1a5978` `SubTracks` in `SubgameRuntime`.
- The shared header change renumbers the unchanged five- and eight-entry switch
  tables to `$L4812`/`$L4813`. COFF places them at the same object offsets
  `+0x62c`/`+0x640`; their bounded relocation sequences are unchanged. With
  those aliases registered, the function remains exact at 396/396 with all 85
  operands clean.

2026-07-11 group-head header refresh:

- Expanding the ten exact `BodBase` group-head fields advances the same tables
  to `$L4818`/`$L4819`. COFF still places them at `+0x62c`/`+0x640`, with the
  same five and eight bounded relocation destinations. Registering this proven
  generation restores all 85 clean operands; the 396 instructions are unchanged.

2026-07-11 landscape-manager header refresh:

- The landscape receiver at `SubgameRuntime +0xff7c00` is now the complete
  exact-size `LandscapeManager`, not overlapping active-entry and script-bank
  views. The menu-background record is reached through its `scripts[]` member.
- Consolidating the shared header renumbers the unchanged five- and
  eight-entry COFF tables to `$L4797`/`$L4798`. They remain at
  `+0x62c`/`+0x640` with the same bounded relocation sequences, restoring
  396/396 with all 85 operands clean.

2026-07-11 SMTrack height-field header refresh:

- Adding the exact embedded height-field animator and Object-derived
  `FrameSequence` advances the unchanged tables to `$L4834`/`$L4835`.
- COFF still places them at `+0x62c`/`+0x640`; the five- and eight-entry
  relocation sequences remain identical to the bounded curated tables. Both
  content aliases restore 396/396 with all 85 operands clean.

2026-07-11 GalaxyRoute slot header refresh:

- Replacing the overlapping route-record views with 101 exact slots renumbers
  the same tables to `$L4796`/`$L4797`, still at `+0x62c`/`+0x640` with the
  same five and eight bounded relocations.
- `$L4797` is reassigned from the earlier bottom-HUD generation to the current
  startup table to keep aliases unambiguous. The exact method remains 396/396
  with all 85 operands clean.

2026-07-11 SubTracks owner promotion:

- Promoting the shared `cRSubTracks` owner changes VC6's compiler-local name
  for the existing five-entry bottom-HUD table to `$L4814`.
- Registering that alias against the bounded `0x14` target table re-audits
  identical entry content and keeps the method exact at 396/396 with all 85
  operands clean; no target or candidate instruction changes.

2026-07-11 SubSegmentRaw header refresh:

- Correcting the built-in initializer to the symbol-proven `void
  cRSubTracks::Init(cRSubSegmentRaw**)` signature advances the same five-entry
  bottom-HUD table to `$L4816` at object `+0x62c`.
- Its bounded relocation sequence remains identical to the target table.
  Registering the content alias restores 396/396 with all 85 operands clean;
  the caller instructions are unchanged.

2026-07-12 cRIntro header refresh:

- Promoting the root menu controller from the synthetic `NewGameMenu` name to
  the symbol-proven `Intro` owner advances the same compiler-local tables to
  `$L5001`/`$L5002` without changing the 396-instruction function.
- COFF places `$L5001` at object `+0x62c` with five relocations through
  `+0x63c`, and `$L5002` at `+0x640` with eight relocations through `+0x65c`.
  Those bounded destination sequences are unchanged from the curated
  bottom-HUD and startup tables, so both aliases remain content-audited rather
  than accepted by label identity.

2026-07-11 SubSegment owner refresh:

- Promoting the Windows destination to `SubSegment` and correcting all three
  SubTracks methods to their cross-port-proven void contracts renumbers the
  unchanged five-entry bottom-HUD table to `$L4809` at object `+0x62c`.
- Its relocation targets are object offsets `+0x419`, `+0x42d`, `+0x46b`,
  `+0x46b`, and `+0x441`, exactly matching target addresses `0x4378c9`,
  `0x4378dd`, `0x43791b`, `0x43791b`, and `0x4378f1` relative to
  `initialize_subgame`. Registering the bounded alias restores all 85 clean
  operands without changing the exact 396-instruction body.

2026-07-11 PathManager owner refresh:

- Promoting the one-byte `cRPathManager` owner at `SubgameRuntime +0xff2910`
  renumbers the unchanged bottom-HUD table to `$L4824` at object `+0x62c`.
- Its five relocations still target object offsets `+0x419`, `+0x42d`,
  `+0x46b`, `+0x46b`, and `+0x441`, exactly matching the bounded target table.
  Registering that content-proven alias restores all 85 operands without any
  source-body change.

2026-07-12 frontend ownership refresh:

- The shared `FrontendWidget` input-lane recovery advances the unchanged
  bottom-HUD and startup tables to `$L4996`/`$L4997`, still at object
  `+0x62c`/`+0x640`.
- Their bounded five- and eight-entry relocation sequences match the curated
  target tables. Registering the refreshed aliases restores exact 396/396
  proof with all 85 operands clean; no source-body instruction changed.

2026-07-12 tip ownership refresh:

- Promoting the shared `TipData` and `Tip` authored names advances the same two
  compiler-local tables to `$L4998`/`$L4999` without changing the 396-instruction
  body.
- COFF still places the tables at object `+0x62c` and `+0x640`. The first has
  five relocations to `+0x419`, `+0x42d`, `+0x46b`, `+0x46b`, and `+0x441`;
  the second retains the same eight-entry startup sequence as the bounded
  target table. Registering these content-proven aliases restores all 85 clean
  operands; the local label spellings themselves are not trusted.

2026-07-12 segment-row capacity refresh:

- Replacing the synthetic final `SegmentCatalogEntry` tail with the proven
  256th authored row renumbers the unchanged mode tables to `$L5000`/`$L5001`.
- COFF places `$L5000` at object `+0x62c` with five relocations to `+0x419`,
  `+0x42d`, `+0x46b`, `+0x46b`, and `+0x441`; `$L5001` remains at `+0x640`
  with the established eight-entry startup sequence. The bounded contents
  match the curated target tables, so `$L5001` is reassigned from its previous
  bottom-HUD generation to the current startup table and `$L5000` becomes the
  current bottom-HUD alias. The exact method body is unchanged.

2026-07-12 backdrop-grid header refresh:

- Exposing the fixed backdrop distortion cells as an owned 8x8 grid advances
  the unchanged mode tables to `$L5009`/`$L5010`, still at object
  `+0x62c`/`+0x640`.
- `$L5009` retains the five relocations to `+0x419`, `+0x42d`, `+0x46b`,
  `+0x46b`, and `+0x441`; `$L5010` retains the established eight-entry startup
  sequence. Both aliases remain bounded by the curated `0x14`/`0x20` table
 sizes, so the audit compares their contents rather than trusting local-label
 identity. The exact 396-instruction method body is unchanged.

2026-07-12 cRBorder layout refresh:

- Closing the shared `FrontendWidget` declaration at its exact 0x724-byte
  boundary first renumbers the unchanged mode tables to `$L5138`/`$L5139`;
  preserving the proven `current_padding`/`active_padding` source alias makes
  the final checked-in generation `$L5147`/`$L5148`.
- COFF still places them at object `+0x62c`/`+0x640`. `$L5147` retains the
  five relocations to `+0x419`, `+0x42d`, `+0x46b`, `+0x46b`, and `+0x441`;
  `$L5148` retains the established eight-entry startup sequence through
  `+0x65c`. Registering these bounded content aliases restores all 85 clean
  operands without changing any of the exact 396 instructions.

2026-07-13 subgame row-window header refresh:

- Naming `SubgameRuntime +0x20/+0x24` as the rolling runtime-row scan window
  advances the unchanged mode-table labels once more: `$L5148` is now the
  five-entry bottom-HUD table at object `+0x62c`, and `$L5149` is the
  eight-entry startup table at `+0x640`.
- The method remains instruction-exact at 396/396. Reassigning the current
  `$L5148` generation and registering `$L5149` restores all 85 clean operands;
  the aliases remain bounded by the curated `0x14`/`0x20` table sizes.

2026-07-13 Player Golb-bank header refresh:

- Replacing the opaque `Player +0x450..+0x2730` interval with twelve complete
  `GolbShot` owners advances the same local labels to `$L5346`/`$L5347`.
- COFF still places the five-entry bottom-HUD table at object `+0x62c` and the
  eight-entry startup table at `+0x640`. The method remains instruction-exact
  at 396/396; registering those bounded aliases restores all 85 operands.

2026-07-13 level-build owner header refresh:

- Naming the shared `track_state_latch` and `selected_speed` sentinel view
  advances the unchanged mode tables to `$L5356`/`$L5357`.
- COFF still places the bounded five-entry bottom-HUD table at object `+0x62c`
  and the eight-entry startup table at `+0x640`. The method remains
  instruction-exact at 396/396; registering those content-proven aliases
  restores all 85 operands.

2026-07-13 SubSegment visited-latch refresh:

- Correcting `SubSegment +0x08` from an integer to a byte latch plus padding
  advances the unchanged mode tables to `$L5357`/`$L5358`.
- COFF still places the bottom-HUD and startup tables at object `+0x62c` and
  `+0x640`; `$L5357` is therefore reassigned to the former and `$L5358` names
  the latter. The method remains instruction-exact at 396/396 with all 85
  operands clean.

## 2026-07-14 exact root and fixed-pool ownership

Landscape loading, backdrop selection, border allocation, and center
justification now use the canonical `GameRoot* g_game` and its embedded
owners. Root `+0x30d` and `+0x310` are now the established
`players[0].high_score_entry_pending` latch and
`players[0].selected_high_score_rank`, matching their exact initialization,
high-score producer, and teardown siblings.

The grid reset derives its 3,200-row and eight-lane bounds from
`runtime_cells`; the four borrowed fringe handles are cleared through the
field-first view up to `next_cell`; and the HUD life-stock loop derives its
nine handles from `life_stock_widgets`. The complete method remains exact at
396/396 instructions with all 85 operands clean.

## 2026-07-14 replay-suppression owner closure

The root byte at `+0x4f2e0` is `GameRoot::intro.hide_for_replay_latch`, not an
anonymous startup flag. Exact `Intro::update_new_game_menu` owns both writes,
and `update_subgame` consumes the same member while releasing attract-mode HUD
suppression. Naming that path here preserves the exact 396-instruction method
and all 85 clean operands.

2026-07-13 root BOD-list owner refresh:

- Retiring the duplicate sub-lazer and garbage list-anchor typedefs advances
  the unchanged mode tables to `$L5355`/`$L5356`.
- COFF still places the bounded bottom-HUD and startup tables at object
  `+0x62c`/`+0x640`. `$L5356` is reassigned to the current startup table, and
  the instruction-exact 396/396 body retains all 85 clean operands.

2026-07-13 SegmentCache backlink refresh:

- Retiring the synthetic `TrackRenderGrid` header view advances the same
  compiler-local tables to `$L5345`/`$L5346` without changing code.
- COFF still places their bounded five- and eight-entry relocation sequences
  at object `+0x62c`/`+0x640`. `$L5346` is reassigned to the current startup
  table; the instruction-exact 396/396 body retains all 85 clean operands.

2026-07-13 animation-owner header refresh:

- Replacing the stale presentation animation pointer/padding names with the
  proven Snail/weapon `AnimManager` bindings and owned donor-slot arrays
  advances the unchanged tables to `$L5378`/`$L5379`.
- COFF still places the five-entry table at object `+0x62c`, with relocation
  targets `+0x419`, `+0x42d`, `+0x46b`, `+0x46b`, and `+0x441`; the eight-entry
  table remains at `+0x640`, targeting `+0x56f`, `+0x5c6`, `+0x5f2`, `+0x5f2`,
  `+0x5ac`, `+0x5f2`, `+0x5f2`, and `+0x5e0`. Those sequences exactly match the
  native tables at `0x437adc`/`0x437af0`, so the content-bounded aliases restore
  all 85 clean operands without changing the 396-instruction body.

2026-07-13 text-editor owner header refresh:

- Promoting the seven `FrontendWidget` text-editor fields advances the same
  compiler-local mode tables to `$L5384`/`$L5385` without changing the exact
  instruction stream.
- COFF still places them at object `+0x62c`/`+0x640`. The five-entry table
  targets `+0x419`, `+0x42d`, `+0x46b`, `+0x46b`, and `+0x441`; the eight-entry
  table targets `+0x56f`, `+0x5c6`, `+0x5f2`, `+0x5f2`, `+0x5ac`, `+0x5f2`,
  `+0x5f2`, and `+0x5e0`. These are identical to the bounded native tables, so
  the aliases restore all 85 clean operands by content, not by label spelling.

2026-07-13 extended-sprite owner header refresh:

- Promoting the contextual `FrontendWidget` sprite aliases advances the same
  compiler-local mode tables to `$L5413`/`$L5414` without changing the exact
  instruction stream.
- COFF still places the bounded tables at object `+0x62c`/`+0x640`. Their
  relocation targets remain `+0x419`, `+0x42d`, `+0x46b`, `+0x46b`, `+0x441`
  and `+0x56f`, `+0x5c6`, `+0x5f2`, `+0x5f2`, `+0x5ac`, `+0x5f2`, `+0x5f2`,
  `+0x5e0`, respectively. These content-bounded aliases preserve the exact
  `396/396` body and all 85 clean operands.

2026-07-13 stable local-table audit: the matcher now derives a compiler-local
symbol's byte extent from the next COFF symbol before reading its relocated
entries. The exact five- and eight-entry tables therefore remain content-
verified when unrelated header declarations renumber them (currently
`$L5454/$L5455`). The accumulated `$L####` alias lists for these two tables
have been removed; `initialize_subgame` remains 396/396 with all 85 operands
clean, without trusting private label spelling.

2026-07-13 canonical Binary Ninja replay: the authoritative path-template
header now supplies the complete `SubgameRuntime` owner map used by this exact
source. Older Binary Ninja databases pin a separate user-defined `Game*`
named-type identity; both ordinary prototype and local-retype attempts are
restored by analysis. The sync reports that exact stale state honestly and
points to the guarded initializer repair instead of claiming a mutation that
analysis rejected. The matching source remains the ownership authority and
stays exact at 396/396 with all 85 operands clean.

2026-07-14 Player renderable inheritance: subgame reset initializes the
embedded Player's inherited transform and copies its position into the
Player-owned cached camera target. The separate Snail, Cameraman, and CutScene
matrices keep their established owners. This method remains exact at 396/396
instructions with all 85 operands clean.

## 2026-07-14 times-up lifecycle ownership

Subgame initialization now resets the adjacent tail owner through
`TIMES_UP_STATE_INACTIVE`. The direct enum constant is codegen-identical and
the function remains exact at 396/396 instructions with all 85 operands clean.

## 2026-07-14 analysis receiver closure

The live Binary Ninja `Game*` receiver was not evidence for another aggregate:
it was a stale named-type identity with the same `0x1272838` extent as
`SubgameRuntime`. Ordinary prototype and local-variable setters rejected the
identity-only correction. Recreating this one function with the registered
`SubgameRuntime` type collapses 96 raw receiver offsets into the existing
runtime-cell, score-bank, HUD, player, GUI, galaxy, and lifecycle owners; only
the still-unproved early `+0x0c/+0x10` pair remains raw.

Function removal/recreation is not fully covered by Binary Ninja's undo API,
so it is not part of the broad ownership replay. The opt-in
`repair_initialize_subgame_owner.py --apply` path checks the exact address,
name, stale/current prototype, `SubgameRuntime` extent, comments, tags, and
user-defined variables first, preserves the receiver and `tColour` workspace,
verifies readback, saves explicitly, and has a manual rollback path. Its
default mode is read-only, and apply mode is a no-op once the database is
current.

IDA had a different persistence layer: the function prototype was already
correct, but a saved Hex-Rays `int this` lvar overrode it. The type sync now
repairs and verifies the `SubgameRuntime *game` receiver for initializer,
update, teardown, and BOD-removal lifecycle functions, invalidates cached
pseudocode, and is idempotent across IDA's optional `struct` spelling. The
tracked BN and IDA artifacts now expose the same initializer owner graph.

No matcher source changed in this analysis-only closure. The native function
remains proof-grade at 396/396 instructions with all 85 operands clean.
