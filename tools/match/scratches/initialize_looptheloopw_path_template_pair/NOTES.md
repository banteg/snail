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

## 2026-07-17 live owner and ABI closure

Live Binary Ninja inspection found the same stale four-stack-argument
`PathTemplate*` prototype as the non-W sibling. The native `ret 0x18` and
refreshed world-initializer callsites prove the shared six-argument stack ABI:
`curve_source`, `width_cells_`, `side_exit`, two surface textures, and the cap
texture.

The guarded repair accepts only the observed legacy parameters, the exact
stack-20 `arg5` annotation, and the missing stack-24 slot, then recreates the
function as a void `Path*` owner. Direct readback confirms all seven parameters
including `this`, and decompilation now ends with an ordinary finalizer call.
As in the sibling, `side_exit` and `cap_texture` are uniform constructor inputs
that this body does not consume; their ownership is established by cleanup and
callsites rather than fabricated source references.

The source is unchanged by the metadata repair. Focused Wibo remains 63.27%
(728/745), with a 10-instruction exact prefix and 51 masked operands ok,
0 unresolved, 0 mismatch.

## 2026-07-20 path-lifetime ownership replay

The W-loop body independently proves the same eleven canonical lifetimes as
its non-W sibling: initialized and reloaded basis-right vectors for both path
halves, two terminal deltas, the primary mesh sample, ordinary and terminal
vertices, and both complete facequads. Transactional preview turned every
member access into the corresponding `Vec3`, `PathTemplateSample`, or
`ObjectFaceQuad` field without introducing an `__offset` expression.

The guarded replay records this constructor's distinct SSA indices and checks
the canonical owner layouts before mutation. The source remains untouched, so
the honest 63.27% focused match and its remaining compiler-scheduling residuals
are preserved.

## 2026-07-26 complete mesh ownership

The W-loop independently preserves the same complete mesh value graph at
`0x41c256..0x41c361`: ordinary lateral offset and generated position, plus a
terminal lateral offset, raised endpoint, generated position, and branch-local
destination vertex. Its face tail at `0x41c434..0x41c591` also owns distinct
front and back `ObjectFaceQuad` records through their final UV lanes, rather
than one pointer hoisted across the branch.

Recovering that coupled owner set raises focused matching from 63.27%
(728/745) to 65.73% (746/745). The masked audit improves from 51 to 52 clean
operands with no unresolved or mismatched entries, the ten-instruction exact
prefix remains intact, and the candidate retains the native `0x60` frame.

## 2026-07-27 authored boolean ABI

The exact Android and iOS symbols independently spell the third argument as
`bool`. The shared matcher declaration, guarded Binary Ninja refinement, IDA
type replay, and repair fallback now agree on `bool side_exit` instead of a
generic `int32_t`. The parameter is unused in this body, so the correction is
code-generation neutral and focused matching remains honestly at 65.73%.

Windows still cleans six stack arguments and its callers supply one trailing
texture beyond the five-argument mobile method. That platform-specific input
is retained rather than deleting a proven Windows ABI slot.

## 2026-07-28 mobile-backed control ownership

The exact Android
`analysis/decompile/android/functions/00058158-_ZN6cRPath17BuildLoopTheLoopWEfibPcS0_.c`
and iOS
`analysis/decompile/ios/functions/00052d7c-_ZN6cRPath17BuildLoopTheLoopWEfibPcS0_.c`
bodies independently preserve the portable builder graph through
`CalcLengthZ`: derived curve count and radius, fixed seven-sample lead and tail
passes, the circular sample pass, the W-roll expression
`sin(angle * 0.5) * sin(angle * 8.0) * (pi / 8)`, and the delta-normalization
pass. Neither mobile body contains the later Windows strip-mesh and facequad
construction.

Windows machine code remains authoritative for every exact address and
lifetime. Transactional Binary Ninja replay separates 41 MLIL definitions into
fourteen logical owners: wiggle, derived counts/radius, lead and tail
index/byte-offset pairs, terminal sample offset, curve index/offset, and delta
index/offset. Seven independently bounded scalar homes recover the floating
curve count, lead sample Z, secondary radius, angle, half-angle, roll-wave
sine, and final roll. In particular, the old anonymous local named `angle`
at `0x41be7d` is the value consumed by both local-Z rotations and is now
correctly owned as `roll`.

The replay previewed and rolled back before applying, saved the database, and
was fully idempotent on a second run. Strict Binary Ninja/IDA 9.4 export
reported zero symbol mismatches and all 1,142 decompile health checks passed.
The IDA refresh also replaces the tracked artifact's stale five-argument
`PathTemplate` view with the proven seven-argument Windows `Path*` ABI.

The candidate source and masks are intentionally unchanged: focused matching
remains 65.73% (745 target / 746 candidate instructions), prefix 10/745, with
55 clean masked operands and no unresolved, mismatched, or unaudited operands.
Repository validation is 497 tests passed, exact-only masked audit clean,
extern lint clean, and generated status deterministic.

## 2026-07-30 shared delta-loop recovery

The exact Windows and mobile bodies use one positive `segment_count - 1` guard
followed by a do/while delta-normalization pass. Replacing the shared
guarded-`for` spelling removes the redundant candidate precheck.

Focused matching rises from 65.73% (`746/745`) to **66.62%** (`744/745`) with
the `10/745` prefix and clean `55/0/0/0` reference audit unchanged. Every
other skeleton consumer recompiles byte-identically, so this is a bounded
shared-family recovery rather than a variant-specific schedule tradeoff.

## 2026-07-29 W-roll call-order recovery

The Windows body finishes the primary basis and immediately applies its
`RotLocalZ(roll)` before constructing the secondary basis. Only after the
secondary cross product does it apply the secondary rotation. The shared
skeleton had deferred both rotations until after both bases were complete,
which changed observable call order as well as compiler lifetimes.

Moving only the primary W rotation to its native position raises focused
matching from 66.62% (`744/745`) to **67.29%** (`744/745`). The
`10/745` exact prefix and clean `55/0/0/0` reference audit remain unchanged.
The non-W LoopTheLoop consumer recompiles byte-identically at 70.64%, proving
the recovery is isolated to `PATH_VARIANT == 1`.

The corrected region still differs in address-register selection and stack
homes, but its semantic basis/call sequence now matches the target. Those
remaining allocation residuals are not evidence for another source rewrite.

## 2026-07-30 paired delta expression ownership

The shared primary and secondary `Vector3` subtraction operators raise focused
matching from **67.29%** to **69.40%**. Candidate size moves from `744` to
`745` instructions, exactly matching the target, while the `10/745` prefix and
clean `55/0/0/0` reference audit remain unchanged.

Either operator in isolation reaches only **67.43%** at `744/745`
instructions. The exact-parity improvement depends on retaining both lanes as
one coupled expression-owner recovery.

## 2026-07-30 mesh arithmetic boundary

The W-roll builder independently exercises the shared-skeleton mesh switches.
Its complete lateral-owner sweep matches the plain sibling's negative
evidence: `double` loses 34.22 weighted bytes, split float is byte-neutral, the
expression-only double form loses 38.01 weighted bytes and adds reference
debt, and volatile float collapses the prefix. The authored owner remains
`float`.

Across all 35 vector-operator interactions, the unique minimal improvement is
again the ordinary generated-position addition through
`Vector3::operator+`. Either operand order is byte-identical; both scales are
individually neutral, and the terminal addition degrades. Retaining the
position-first spelling adds 3.66 weighted bytes and raises focused matching
from 69.40% to **69.53%**, while preserving the exact 745/745 instruction
count, prefix 10/745, and all 55 clean references.

The new ledger contains two complete sweeps and 39 unique variants. Its result
also explains the older whole-mesh operator regression: coupling both neutral
scale spellings is sharply negative even though the ordinary addition alone
is a clean win.

## 2026-07-30 face index ownership

The W native shares the plain builder's face-tail boundary: it materializes
`face_index + 2 * (row * width + column)` before selecting the first or second
face layout. Keeping that integer common while leaving each branch to form its
own pointer adds 38.34 weighted bytes and raises focused matching from
**69.53%** (`745/745`) to **70.94%** (`738/745`). The `10/745` exact prefix and
clean `55/0/0/0` reference audit remain unchanged.

The commuted index expression is byte-identical. A common pointer is not: it
loses 41 weighted bytes and falls to 68.02%. The nearby lead-progress split
loses 58-62 weighted bytes, while reversing the redundant checkerboard texture
condition is byte-neutral. These bounded results isolate the common integer
owner as the only retained face-control recovery, with the seven-instruction
count deficit recorded as an explicit tradeoff rather than hidden.
