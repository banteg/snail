# tVector::Normalize() @ 0x44cca0

Exact match: 100.00%, 29/29 instructions.

This helper normalizes one `Vec3` in place by calling the exact `dot_vectors`
and `square_root` helpers, returning the pre-normalization length or zero for a
zero vector. It is used by path construction, collision probes, projectile
steering, sprite-facing math, and presentation systems.

2026-07-14 owner promotion: the exact body first defined the shared vector
method directly. Windows passes the vector in `ECX`, exact neighboring math
callers use member syntax, and Android independently retains
`tVector::Normalize()`.

The analysis contract is now the actual float-returning `__thiscall` member,
not the stale double `__fastcall` prototype. ECX receiver setup, four-byte
consumer stores, and the mobile symbol agree; the exact body remains 29/29
with all five masked operands clean.

## 2026-07-28 authored tVector surface

Android and iOS recover the primary class name `tVector` plus the exact
`operator*`, `Dot`, `operator*=`, `Rotate`, `Normalize`, `Magnitude`, and
`Cross` family. The shared Windows type now uses `struct tVector` as its owner
and retains `Vector3` only as a compatibility typedef, with an explicit
`0x0c` size assertion. All nine verified method bodies target their
owner-qualified VC6 symbols and remain exact at 248/248 instructions.

Downstream callers use the authored method names where their source shape is
closed. Low-progress path and object-normal callers that still pass Cross
operands as pointers retain the documented pointer-shaped compatibility view;
they are not presented as evidence for a second authored overload. Windows also
retains `TransformMatrix` in these declarations until the separate `tMatrix`
owner promotion is validated. The complete 662-scratch rebuild remains
byte-identical at 532 proof-grade functions and 79.11% overall fuzzy match.
