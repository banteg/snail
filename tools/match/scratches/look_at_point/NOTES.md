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
operator. It was initially kept scratch-local pending a second agreeing
consumer; the promotion evidence is recorded below.

## 2026-07-16 shared Vector3 arithmetic ownership

Ten subtraction consumers and sixteen addition consumers had independently
recovered the same `const Vector3&` binary signatures. Exact
`look_at_point`, `request_object_animation`, `update_track_parcel`,
`update_vapour`, `get_path_position_at_node`, and attachment projection
callers agree on the explicit result-object implementation, so `operator+`
and `operator-` now belong to shared `vector3.h` rather than being copied into
individual scratches.

The promotion preserves every pre-existing exact consumer and makes
`update_star_positions` exact (99.06% to 100.00%, 106/106 instructions).
It also improves `build_track_fringe_mesh` from 89.31% to 90.25%, its
supertramp sibling from 92.87% to 94.54%, and the worm template from 72.28% to
72.32%. The old constructor-return copies happened to score slightly higher
in two non-exact callers (`initialize_star_field`, 98.38% to 97.57%, and the
loop-the-loop template, 64.75% to 64.47%), but retaining per-caller arithmetic
implementations would contradict the now-closed shared owner. Overall proof
grade gains one 378-byte function and fuzzy coverage rises; no per-scratch
operator fakematches remain.

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
