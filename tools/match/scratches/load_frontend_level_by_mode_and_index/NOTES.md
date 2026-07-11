# load_frontend_level_by_mode_and_index @ 0x443650

Initial shape:

- Formats a level definition filename into a 128-byte stack buffer from the
  frontend mode and level index.
- The receiver is the same `SubTracks` object that owns
  `load_level_definition_file`; symbol-preserving iOS builds name the authored
  class `cRSubTracks` and this method `Load(int, int)`.
- Mode `0` is postal/arcade. Indexes `0..50` format as `Arcade%03i.txt`; index
  `51` uses `ArcadeExtra000.txt`.
- Mode `1` loads `Challenge000.txt`; modes `2` and `3` load `Arcade000.txt`;
  mode `4` is time-trial, using `TimeTrialExtra%03i.txt` above index `50`;
  mode `7` loads `Tutorial.txt`.
- Native falls through to `load_level_definition_file(path)` even for default
  modes and for mode `0` indexes above `51`, so the scratch preserves the
  uninitialized stack-buffer behavior instead of adding a guard.

Status:

- 2026-06-18: 81.36%, 57 target instructions vs 61 candidate instructions.
  Masked operands are clean except the switch jump-table displacement, which
  the matcher currently reports as the native table bytes at `0x44370c` versus
  the scratch-local `$L319` table.
- The remaining body residual is VC6 tail sharing around the two indexed
  `sprintf` calls: native shares part of the `Arcade%03i.txt` and
  `TimeTrialExtra%03i.txt` setup, while the clean source emits one extra direct
  call block. An explicit shared-label probe made the function much worse, so
  keep this as a documented source-shaped partial until there is a better
  idiom lead.

2026-06-21 argument-order follow-up: `sprintf(&path[0], ...)`, a reusable
`char* path_ptr`, and declaring that pointer immediately before the switch are
all codegen-neutral at 81.36% and leave the same indexed-call tail sharing
residual. A volatile path pointer collapses the prologue and regresses to
31.67%. Keep the direct `sprintf(path, ...)` calls; argument spelling alone does
not recover native's shared path/call tail.

2026-07-09 shared-tail campaign: format-pointer locals, combined case 0/4,
post-switch format dispatch, if-ladder mode selection, and goto-shared
indexed/`plain` sprintf epilogues all failed to recover native's
`push index; push format; jmp shared_lea_path` merge between arcade and
time-trial-extra. Best remains 81.36% with the direct switch + call shape.
The jump-table masked mismatch is still the local `$L` vs image table pair
while body block sizes differ.

2026-07-11 cross-port owner promotion: the shared class is now `SubTracks`,
backed by all four iOS member symbols (`Load`, both `Init` overloads, and
`ImportSegment`). Renaming the owner and header preserves the focused 81.36%
result; the remaining Windows gap is still only VC6 tail sharing and the
resulting local jump-table label.
