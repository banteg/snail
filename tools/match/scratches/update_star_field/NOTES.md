# update_star_field @ 0x4346f0

Small lifecycle state machine around render-feature bit `0x04`:

- state `0`: closed; feature-on initializes and starts fade-in state `2`.
- state `1`: fully visible; feature-off starts fade-out state `3`.
- state `2`: fading in; reaches state `1` after `fade > 1.0`.
- state `3`: fading out; feature-on returns to state `2`, otherwise destroys
  the star field after `fade < 0.0`.

`fade_step` is the literal `0.020833334f`.

Current match is byte-for-byte 100%. The switch jump-table operand now resolves
through `update_star_field_jump_table` at `0x4347e8`, matching VC6's local
`$L529` table symbol, so the masked operand audit is clean.
