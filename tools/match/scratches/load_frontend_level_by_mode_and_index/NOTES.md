# load_frontend_level_by_mode_and_index @ 0x443650

Initial shape:

- Formats a level definition filename into a 128-byte stack buffer from the
  frontend mode and level index.
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
