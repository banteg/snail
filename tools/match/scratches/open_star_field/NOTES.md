# open_star_field @ 0x4342c0

Allocates `count * 0x2c` star entries under the `StarField` allocation label.
If render feature bit `0x04` is already enabled, opens directly into state `1`
and initializes sprites; otherwise leaves the lifecycle state at `0`.
