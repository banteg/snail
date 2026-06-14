# cross_vectors @ 0x44cd40

Exact match: 100.00%, 40/40 instructions.

This helper computes a 3D cross product into the destination vector through the
native function-local static `Vec3` temporary. The `scratch.conf` end is pinned
to `0x44cdc3` because the manifest extent otherwise includes the adjacent
uncurated static-destructor stub at `0x44cdd0`.

It is used by path-template basis construction, matrix orthogonalization, object
normals, and track/fringe geometry.
