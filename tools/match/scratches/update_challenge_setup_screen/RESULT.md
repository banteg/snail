# `update_challenge_setup_screen` match result

## Score

| Metric | Starter | Final |
|---|---:|---:|
| Match | 0.28% | **80.68%** |
| Target instructions | 355 | 355 |
| Candidate instructions | 1 | 354 |
| Common prefix | 0 / 355 | **8 / 355** |
| Masked operands | none | **35 clean, 0 unresolved, 0 mismatched** |

The inclusive highest route index and both challenge slider sources now resolve
through the shared `RuntimeConfig`; there are no unresolved or mismatched
operands.

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
