# cross_vectors @ 0x44cd40

Exact match: 100.00%, 40/40 instructions.

This helper computes a 3D cross product into the destination vector through the
native function-local static `Vec3` temporary. The `scratch.conf` end is pinned
to `0x44cdc3` because the manifest extent otherwise includes the adjacent
uncurated static-destructor stub at `0x44cdd0`.

The static guard at `data_777f38` and `result.z` at `data_77ff88` overlap the
synthetic one-float-before trigonometry init bases named for
`initialize_trigonometry_tables`; the masked audit should keep treating them as
compiler-generated static-local operands in this scratch.

It is used by path-template basis construction, matrix orthogonalization, object
normals, and track/fringe geometry.
