# `initialize_looptheloopw_path_template_pair` starter

This is an honest semantic starter for the path-template initializer at
`0x41bb40`.

It follows the loop-the-loop family shape and adds the recovered W-loop roll
term, `sin(angle * 0.5) * sin(angle * 8.0) * 0.39269909`, before building
deltas, strip vertices, facequads, and finalizing the template.

Residuals are expected around stack layout, x87 scheduling, and face-loop
control flow. No toolchain flags or fakematching tricks are used.

2026-07-03 ABI cleanup: focused diff shows the native tail is `ret 0x18`, so
the constructor uses the same six-argument stack cleanup as the surrounding path
template callsites. Updating the scratch and shared declaration from the stale
four-argument prototype moves focused Wibo from 27.96% (664/745) to 28.11%
(664/745), with masked operands unchanged at 21 ok, 0 unresolved, 1 mismatch.

2026-07-04 W-roll schedule: the curved-body loop now computes the W-loop roll
scalar immediately after `angle` instead of just before the two
`rotate_matrix_world_z` calls. Focused Wibo moves from 28.11% (664/745) to
30.56% (662/745). This is a score and source-schedule win, not a clean audit:
masked operands move from 21 ok, 0 unresolved, 1 mismatch to 40 ok,
0 unresolved, 2 mismatch. The remaining mismatches pair a native
`normalize_vector` with candidate `rotate_matrix_world_z`, and a mesh allocation
call pairing; keep those residuals explicit.

Rejected neighbor: swapping strip-mesh allocation to facequads-before-vertices
moved focused Wibo from 30.56% (662/745) to 30.85% (662/745), but worsened the
masked audit from 40 ok, 0 unresolved, 2 mismatch to 40 ok, 0 unresolved,
3 mismatch by explicitly pairing native `request_object_vertices` with
candidate `request_object_facequads` and native `request_object_facequads` with
candidate `request_object_vertices`. The small fuzzy bump is source-false, so
the W-loop scratch keeps vertices-first order.

## 2026-07-15 shared builder ownership recovery

The source-backed ownership recovered in the adjacent LoopTheLoop builder also
holds for its W-roll sibling. The fixed approach and departure runs now perform
their indexed `AttachmentSample` initialization directly, including transform
identity, primary-center propagation, the secondary `0.49f` Y offset, and unit
delta lengths. The circular run owns its two-step center update and constructs
right/up/forward basis members in place before applying the independently
recovered W-roll scalar.

The strip mesh now uses an actual `Vector3` temporary and the expression
`basis_right * lateral + position`. This recovers the native `0x60` stack frame
and confirms that the larger frame than LoopTheLoop's `0x54` belongs to the
W-roll lifetimes, not an unrelated hidden field. The face grid keeps the shared
do/while column traversal and parity-controlled duplicate texture branches
that are visible in the target and the Cage2 source-family member.

Ordering `kind = 0` before the zero initialization of `loop_wiggle` recovers one
more native prologue instruction. Focused Wibo improves from 30.56% (662/745)
to 63.27% (728/745), with a 10-instruction exact prefix and 51 masked operands
ok, 0 unresolved, and 0 mismatch. The direct-texture simplification reached
64.75%, but was rejected because it removes proven authored control flow. The
remaining delta is compiler scheduling and register/local allocation; no
volatile padding or other fakematching is warranted.
