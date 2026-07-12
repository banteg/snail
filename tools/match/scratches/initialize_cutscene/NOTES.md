# initialize_cutscene @ 0x4428d0

First structural scratch for the per-frame presentation/cutscene setup path.
This function ties together the fields promoted on the exact authored `Snail`:

- exact authored `cRSnailSkin` child `snail_skin` at `+0x1938`
- `live_matrix` at `+0x38` and `cached_cutscene_matrix` at `+0xc0`
- channel `live_matrix` at `+0x38` and `release_step` at `+0x3d0`
- `snail_hotspot_source_matrix_a`/`b`, then `update_snail_skin`
- embedded authored `cRCutScene` at `+0x1958`

The first version is meant to be an honest source-shaped baseline for matching
and layout validation, not a final register-perfect reconstruction.

Current focused result:

- 98.82% fuzzy match, 339 candidate insns / 339 native insns
- prefix 110/339
- masked comparison: 43 ok, 0 unresolved, 0 mismatch

Remaining known shape issues:

- The native and candidate stack frames are both `0x15c`; all local value
  lifetimes and the instruction count now agree.
- `Player +0x38` is closed through the shared `Player::live_transform()`
  accessor. `Player::position` remains the overlapping field view at `+0x68`.
- 2026-06-18 source-shape correction: the early persistent `Player* player` /
  `player_matrix` assumption was wrong for this function. Native reloads
  `owner_player` through the pitch/exit gates, then uses short-lived player
  matrix and cached-camera-target views in the steady path. Spelling those
  lifetimes in source raises the match from 64.05% to 73.95% and clears the
  previous masked constant mismatch.
- A destination-position pointer probe compiled identically at 73.95%, so the
  scratch keeps the simpler direct `live_matrix.position` and
  `snail_hotspot_source_matrix_b.position` assignments.

2026-07-11 pause-owner closure: the early pause gate now reads
`GameRoot::subgame.subgame_pause_gate`; removing the synthetic `GamePauseView`
is codegen-neutral at 73.95%, 329/339 instructions, prefix 1/339, and 42 clean
masked operands.

2026-07-11 cross-port owner correction: this function is the Windows
counterpart of `cRSnail::AIGoldy()`, not `cRCutScene::Init`. Android's authored
method has the same per-frame call family: snail-skin AI, matrix interpolation,
hotspot construction, hover jets, animation dispatch, and the embedded
`cRCutScene::AI`. The tiny exact `initialize_cutscene_ai @0x446130` is the real
CutScene initializer. The corrected `cRSnail::AIGoldy` prototype is `void`,
matching the scratch and the fact that every per-frame caller ignores the
incidental exit register.

2026-07-12 live-transform and vector source-shape pass:

- All four raw `Player +0x38` casts now use `Player::live_transform()`. The
  steady camera path borrows one short-lived `Player*`, matching native's
  single owner load for the live transform and cached camera target.
- Whole `Vector3` assignments recover the authored position copies into the
  live and hotspot-source matrices. The lift is the chained expression
  `(basis_up * lift_sine) * 0.03f`; its two real returned vectors recover the
  missing pair of 12-byte temporaries and the exact native `0x15c` frame.
- Passing the roll sine expression directly into `rotate_matrix_world_z`
  removes the non-native scalar spill. These source-shaped changes improve the
  focused result from 73.95% (329/339, prefix 1) to 98.82% (339/339, prefix
  110), with all 43 masked operands clean.
- The only residuals are independent instruction scheduling: the up-basis FPU
  comparison overlaps the following position copy, and the cached-matrix copy
  overlaps the invincible-roll comparison. No artificial local or reordered
  control flow is retained to force those schedules.
