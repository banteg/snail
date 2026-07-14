# look_at_point @ 0x44d4e0

Exact match: 100.00%, 22/22 instructions, one masked operand clean.

## Semantics

Thiscall member on `TransformMatrix` (ret 0x4). It builds a direction vector
from the matrix position to the supplied target point, then hands it to the
exact thiscall member `set_matrix_z_direction` (`0x44d410`), which rebuilds the
forward basis (and right/up) from that direction:

```cpp
void TransformMatrix::look_at_point(const Vector3& target)
{
    Vector3 delta = target - position;
    set_matrix_z_direction(delta);
}
```

`position` is the shared `TransformMatrix::position` lane at `+0x30`. The
reference lowers to `&delta` on the stack (`ret 0x4` callee cleanup is owned by
`set_matrix_z_direction`).

## Source-shape evidence: the two-object frame

The native frame is `0x18` (six dwords), not the `0x0c` a single
component-assigned `Vector3 delta;` produces. The layout is:

- `[esp..0x8]` — the inlined `operator-` result temporary,
- `[esp+0xc..0x14]` — the address-taken `delta` local, copied dword-by-dword
  from the temp before `&delta` is pushed.

That two-object stack (compute-into-temp, then copy-into-escaping-local) is the
codegen signature of `Vector3 delta = *target - position;` with a by-value
`operator-` returning a `Vector3`. A standalone probe confirmed the
component-assignment spelling collapses the frame to `0x0c` (one object, fstp
straight into the local) and scores 52.63%, while the operator spelling
reproduces the native frame, the temp-to-local dword copies, the interleaved
`fstp [esp+0x8]` scheduling, and the final `push &delta; mov [esp+0x18]; call`
sequence exactly.

The `operator-` is therefore recovered, not invented: the two-object frame is
independent evidence that the original `Vector3` had a by-value subtraction
operator. It is kept scratch-local for now (not promoted to `vector3.h`) until
a second scratch agrees on the operator signature, per the shared-header
promotion policy.

## Call target

The single masked operand is the `call set_matrix_z_direction@0x44d410`,
resolved cleanly against the shared header declaration. No unresolved or
mismatched references.

## Callers

Six call sites (`0x44676c`, `0x44680a`, `0x446a19`, `0x446aee`, `0x446d1b`,
`0x446dce`) — all in the cameraman/update-camera family, consistent with
`look_at_point` being the shared "aim a transform's forward axis at a world
point" helper.

2026-07-14 ownership closure: both mobile ports preserve
`tMatrix::LookAt(tVector const&)`. The shared method and all owned cutscene
callers now use the const-reference surface directly while remaining exact.
