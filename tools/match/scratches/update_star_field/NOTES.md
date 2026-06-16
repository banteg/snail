# update_star_field @ 0x4346f0

Small lifecycle state machine around render-feature bit `0x04`:

- state `0`: closed; feature-on initializes and starts fade-in state `2`.
- state `1`: fully visible; feature-off starts fade-out state `3`.
- state `2`: fading in; reaches state `1` after `fade > 1.0`.
- state `3`: fading out; feature-on returns to state `2`, otherwise destroys
  the star field after `fade < 0.0`.

`fade_step` is the literal `0.020833334f`.

Current match is byte-for-byte 100%, but the switch jump-table operand is still
reported as one unresolved masked operand (`$L...` candidate table versus the
native table at `0x4347e8`). Treat the state-machine source as established, but
do not count it as proof-grade until that relocation audit is resolved.
