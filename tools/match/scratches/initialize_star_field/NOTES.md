# initialize_star_field

- Source-shaped initializer for the star-field entries and backing sprites.
- The final call is the first vtable slot on the star-field object; the scratch
  models that slot as `update_star_field_callback()` while the named
  `update_star_field()` body remains the concrete callback at `0x4346f0`.
- First pass: 34.74%, 179/247 candidate/target instructions, 25 masked
  operands ok. The main residual is source shape, not unknown behavior: native
  keeps a `0x60` stack frame with many explicit x87 temporaries for camera
  position and phase/speed deltas, while the readable source collapses those
  calculations into direct entry/sprite stores.
- A native-shaped offset rewrite was rejected because it regressed to 25.11%
  and introduced a constant-reference mismatch. Keep the readable partial until
  a focused stack-temporary pass can improve it without fake padding.
