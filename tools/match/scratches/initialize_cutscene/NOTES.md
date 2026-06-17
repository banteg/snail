# initialize_cutscene @ 0x4428d0

First structural scratch for the per-frame presentation/cutscene setup path.
This function ties together the fields promoted on `PlayerPresentationController`:

- `snail_skin_transition` at `+0x1938`
- `live_matrix` at `+0x38` and `cached_cutscene_matrix` at `+0xc0`
- channel `live_matrix` at `+0x38` and `release_step` at `+0x3d0`
- `snail_hotspot_source_matrix_a`/`b`, then `update_snail_skin`
- embedded `cutscene_ai` at `+0x1958`

The first version is meant to be an honest source-shaped baseline for matching
and layout validation, not a final register-perfect reconstruction.

Current focused result:

- 64.05% fuzzy match, 323 candidate insns / 339 native insns
- prefix 1/339
- masked comparison: 39 ok, 1 mismatch

Remaining known shape issues:

- native stack frame is `0x15c`; current candidate frame is `0x14c`
- the pitch-cycle compare still schedules differently near the first masked mismatch
- `Player` still needs a careful `live_matrix` promotion at `+0x38`; this scratch
  uses a pointer view to avoid breaking existing `Player::position` users
