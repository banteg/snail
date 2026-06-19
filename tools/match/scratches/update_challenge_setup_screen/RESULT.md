# `update_challenge_setup_screen` match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.28% | **80.68%** |
| Target instructions | 355 | 355 |
| Candidate instructions | 1 | 354 |
| Common prefix | 0 / 355 | **8 / 355** |
| Masked operands | none | **33 clean, 2 unresolved, 0 mismatched** |

The two unresolved operands are `data_4df9b8`, the inclusive highest route index
already used by the galaxy scratches. There are no masked mismatches.

## Accepted source-shape changes

- Added the real `ChallengeSetupScreen::update_challenge_setup_screen` member
  declaration to the shared challenge setup header.
- Modeled the dispatch as a sparse `switch` with `case 4` first; this recovers
  the native `sub/dec/sub` mode comparison chain and physical mode-4 fallthrough.
- Reused the member-style `TimeTrialStringFormatter` call shape from
  `update_subgame`, preserving the native `ecx = game +0xff25e0` setup.
- Loaded the selected Time Trial replay active flag separately from the later
  Replay-click record pointer store, matching the native pointer lifetime.

## Remaining work

- Candidate is one instruction shorter, leaving the top branch labels off by
  one target label even though the main mode-4 body lines up closely.
- Mode-4 replay-tail pointer math and challenge-slider register ownership still
  schedule differently from native.
- `data_4df9b8` should be resolved through the curated reference manifest when
  the galaxy route-limit symbol is promoted.
