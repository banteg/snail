# change_backdrop_real @ 0x410dc0

Exact match: 30/30 instructions, clean masks.

Commits the pending backdrop state staged by `change_backdrop`.

Recovered `Backdrop` fields:

- `pending_primary_texture_id +0x40` is the zero/non-zero gate.
- `active_primary_texture_id +0x3c` and `active_secondary_texture_id +0x44`
  are updated when the pending primary texture changes.
- `progress_fraction +0x6c8` resets before rebuilding distortion.
- `active_flip +0x55` and `active_split_backdrop_pair +0x38` mirror the
  pending fields after every call.
