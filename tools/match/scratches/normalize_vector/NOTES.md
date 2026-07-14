# Vector3::normalize_vector @ 0x44cca0

Exact match: 100.00%, 29/29 instructions.

This helper normalizes one `Vec3` in place by calling the exact `dot_vectors`
and `square_root` helpers, returning the pre-normalization length or zero for a
zero vector. It is used by path construction, collision probes, projectile
steering, sprite-facing math, and presentation systems.

2026-07-14 owner promotion: the exact body now defines the shared `Vector3`
method directly. Windows passes the vector in `ECX`, exact neighboring math
callers use member syntax, and Android independently retains
`tVector::Normalize()`.

The analysis contract is now the actual float-returning `__thiscall` member,
not the stale double `__fastcall` prototype. ECX receiver setup, four-byte
consumer stores, and the mobile symbol agree; the exact body remains 29/29
with all five masked operands clean.
