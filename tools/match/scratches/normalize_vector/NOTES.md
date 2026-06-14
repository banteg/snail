# normalize_vector @ 0x44cca0

Exact match: 100.00%, 29/29 instructions.

This helper normalizes one `Vec3` in place by calling the exact `dot_vectors`
and `square_root` helpers, returning the pre-normalization length or zero for a
zero vector. It is used by path construction, collision probes, projectile
steering, sprite-facing math, and presentation systems.
