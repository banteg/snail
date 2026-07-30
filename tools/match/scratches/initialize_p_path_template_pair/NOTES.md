# initialize_p_path_template_pair

Honest starter scratch for `initialize_p_path_template_pair @ 0x425a40`.

The constructor callsite shows nine explicit stack arguments and the target tail
is `ret 0x24`. The first argument selects runtime kinds `0x21..0x23`; the body
uses the width, endpoint X positions, segment count, and two track textures.

The scratch builds the endpoint samples, fills the three P-family curve formulas
seen in the decompile, derives orientation and deltas, generates the strip mesh,
and finalizes the template. Residuals are expected.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 10.58% (134/679
candidate/target instructions) to 18.55% (561/679), with masked operands
improving from 6 ok, 0 unresolved, 8 mismatch to 19 ok, 0 unresolved, 6
mismatch.

2026-07-03 path-template count/radius sweep: materialized the endpoint
`last_index = curve_segments + 1` and allocation `sample_count = last_index + 1`
spelling used by the native constructor, then kept the radius sign check on an
x87 temporary before storing the float radius. Focused Wibo moved from 18.55%
(561/679) to 19.22% (559/679), with masked operands unchanged at 19 ok, 0
unresolved, 6 mismatch. Rejected adjacent probes: reloading primary/secondary X
from `primary->center_x`, reloading secondary Y from the primary transform, and
branching on `kind - 0x21`; all reduced the focused score.

2026-07-03 Z-index helper spelling: keep the pair helper Z input as an integer
sample index and perform the int-to-float conversion inside the inlined helper
after primary identity. Focused Wibo moves from 19.22% (559/679) to 19.26%
(557/679), with masked operands unchanged at 19 ok, 0 unresolved, 6 mismatch.

2026-07-03 radius compare probe rejected: collapsing the radius sign check from
the double temporary to a float local made the visible compare use a dword
operand, but focused Wibo regressed from 19.26% (557/679) to 19.19% (561/679).
Masked operands stayed at 19 ok, 0 unresolved, 6 mismatch, so the native-shaped
temporary remains the retained spelling.

2026-07-03 mesh request order probe rejected: swapping the strip-mesh requests
to facequads-before-vertices was neutral in focused Wibo at 19.26% (557/679),
but simply flipped the remaining mesh call mismatch from target vertices vs
candidate facequads to target facequads vs candidate vertices. Masked operands
stayed at 19 ok, 0 unresolved, 6 mismatch, so the shared vertices-first helper
remains retained until the earlier loop/call alignment debt moves.

2026-07-03 mesh-face loop probe rejected: replacing the direct `a`/`b` face
writes with the two-iteration `face_index` loop regressed focused Wibo from
19.26% (557/679) to 18.14% (567/679). Masked operands dropped from 19 ok, 0
unresolved, 6 mismatch to 16 ok, 0 unresolved, 6 mismatch, so the direct face
writer stays retained for now.

2026-07-03 endpoint expansion probe rejected: flattening the first and terminal
sample setup out of `initialize_pair_sample`, matching the decompile's direct
endpoint writes and `center_x` reloads, regressed focused Wibo from 19.26%
(557/679) to 18.61% (557/679), with masked operands unchanged at 19 ok,
0 unresolved, 6 mismatch. Splitting the probe was also negative: first sample
only dropped to 18.28% and worsened the masked audit to 16 ok, 0 unresolved,
6 mismatch; terminal sample only matched the full regression at 18.61%. The
endpoint helper calls remain retained until the earlier loop/call alignment
debt moves.

2026-07-03 mesh-vertex staging probe rejected: unlike `start` and
`supertramp`, routing the strip-mesh vertex calculation through a local
`Vector3 generated_position` before assigning `*vertex` regressed focused Wibo
from 19.26% (557/679) to 13.01% (566/679). Masked operands dropped from 19 ok,
0 unresolved, 6 mismatch to 14 ok, 0 unresolved, 5 mismatch, so the `p` scratch
keeps direct component writes for now.

2026-07-04 loop-counter probe rejected: rewriting the curved body as a
zero-based counter with `sample_index = i + 1` regressed focused Wibo from
19.26% (557/679) to 18.74% (559/679). Masked operands dropped from 19 ok,
0 unresolved, 6 mismatch to 16 ok, 0 unresolved, 6 mismatch, so the current
one-based loop with `(i - 1)` angle ownership stays retained.

2026-07-04 retained orientation scheduling expansion: expanding the curved-body
orientation helper calls in place matches the native shape that builds both lane
orientations inside the loop and keeps the `i <= 1` identity branch together.
Focused Wibo moves from 19.26% (557/679) to 19.40% (558/679). This is not a
masked-audit cleanup: masked operands worsen from 19 ok, 0 unresolved,
6 mismatch to 19 ok, 0 unresolved, 9 mismatch, so the new residual call
pairings remain explicit.

Post-orientation mesh request-order retest: swapping strip-mesh requests to
facequads-before-vertices stayed neutral at 19.40% (558/679), with masked
operands unchanged at 19 ok, 0 unresolved, 9 mismatch, and only flipped the
remaining mesh allocation call pairing. The vertices-first order remains
retained.

Post-orientation branch-shape retest: rewriting the curved center selection as
independent `kind == 0x21` / `0x22` / `0x23` branches, matching the decompiler's
surface spelling, regressed focused Wibo from 19.40% (558/679) to 19.31%
(564/679). Masked operands stayed at 19 ok, 0 unresolved, 9 mismatch, so the
retained source keeps the `else if` branch chain.

2026-07-15 ownership cascade: flattening the delta producer into the constructor
and indexing `primary_samples` / `secondary_samples` directly recovered the
native owner and moved focused Wibo from 19.40% to 25.72%. Expanding the two
endpoint samples then improved the masked call audit from 21 ok, 7 mismatch to
24 ok, 5 mismatch and nudged Wibo to 25.83%.

Flattening curved-sample initialization was the main unlock: focused Wibo moved
to 38.76%, with 26 masked operands correct and one mismatch. Recovering the
native zero-based angle counter plus one-based sample index then moved Wibo to
40.81% and cleared the masked audit. Finally, direct center stores in an
explicit three-case `switch` recovered the target's `0x21..0x23` dispatch and
unknown-kind fallthrough, moving focused Wibo to 44.05% (615/679 candidate/
target instructions), with 33 masked operands correct and no unresolved or
mismatched operands.

The target also proves that face headers are initialized as a 16-bit word, so
the retained direct mesh writer now uses `header_word`. This ownership change
is score-neutral. The native two-face loop and checkerboard-shaped redundant
texture branches remain documented family structure, but are not retained yet:
the simple face loop regressed Wibo to 22.05%, while the fuller shared-family
loop reached 36.46% (37.47% with explicit terminal vertex branches), both below
the 40.81% pre-dispatch baseline. Direct orientation array indexing similarly
regressed to 21.09%; pointer aliases remain retained for compiler scheduling.

Post-cascade radius and vertex probes were also rejected. A float radius local
produced the visible dword comparison but regressed Wibo from 40.81% to 40.71%
and reintroduced one masked call mismatch. Explicit terminal/nonterminal vertex
branches regressed to 40.74%. The x87 radius temporary and collapsed vertex
selection remain until surrounding stack and mesh ownership moves again.

## 2026-07-17 constructor ABI closure

The Windows tail returns with `retn 0x24`, proving nine stack arguments after
the `Path*` receiver. The three world-initializer calls independently expose
variants 0/1/2, float scale, integer width, start/end X, curve segment count,
two surface textures, and the Windows-only cap texture. The iOS `BuildP`
symbol preserves the same portable prefix through the two surface textures.

Guarded Binary Ninja recreation and readback now recover that exact void member
ABI and the full owner flow (`kind = variant + 0x21`, width, samples, mesh, and
finalizer). This is analysis-only: focused Wibo remains 44.05% (615/679), with
33 clean operands and no unresolved or mismatched operands.

2026-07-20 live lifetime closure: the separately previewed P schedule recovers
the preceding primary/secondary forward vectors, both current-sample reloads,
both terminal deltas, and the current mesh sample. More importantly, MLIL
proves that the two integer-looking EBP values each span a complete 0x30-byte
face record; typing them as `ObjectFaceQuad*` resolves every vertex, texture,
and UV write directly. The previous-row mesh cursor stays automatic because
its negative byte-relative address became less exact when typed. The preview
introduces no `__offset` expressions. This is analysis-only: focused Wibo
remains 44.05% (615/679), with 33 clean operands and no unresolved or
mismatched operands.

## 2026-07-25 mesh-vector ownership

Raw native assembly at `0x4260ad..0x42618c` proves that the row-terminal test
belongs inside the vertex column loop. Ordinary rows materialize one aggregate
generated position. The terminal row separately owns a previous-sample
lateral-offset vector and a generated position whose Z lane includes
`+1.0f`.

Retesting this exact source shape after the 2026-07-15 sample and delta
ownership cascade supersedes the earlier generic branch probe. Focused matching
now rises from 44.05% (615/679) to 46.46% (634/679), with 32 clean masked
operands and no unresolved or mismatched masks. The candidate frame moves no
farther than `0x34` against the native `0x40`; the remaining frame ownership
includes the still-unrecovered two-face record loop.

## 2026-07-25 face-record ownership

Raw native assembly at `0x42623f..0x4263b2` proves an inner two-iteration face
loop. Its index is `face_index + 2 * (row * width_cells + column)`, and each
branch owns a complete, distinct `ObjectFaceQuad` lifetime. The first branch
writes the even face and both parity arms select `texture_a`; the second writes
the odd face and both parity arms select `texture_b`. Both branches write the
header, four vertices, texture reference, and all four UV pairs.

This agrees independently with the guarded Binary Ninja lifetime replay, which
recovers separate `face_first` and `face_second` pointers. A shared pointer
probe both contradicted those lifetimes and fell to 36.32%. Retaining the two
branch-local records and the native index expression yields 40.83% (668/679)
with a `0x38` frame against the native `0x40`, 30 clean masked operands, and no
unresolved or mismatched masks. The previous simplified two-record writer
scored 46.46% (634/679) with a `0x34` frame, but hid the proven loop and record
ownership; its higher fuzzy score was therefore not retained.

## 2026-07-26 complete mesh-vector ownership

Raw native assembly at `0x4260bc..0x42618c` proves the same complete four-vector
model as the adjacent constructors. The ordinary branch materializes a
lateral-offset vector before its generated position. The terminal branch
reaches the previous sample through the current row cursor, materializes its
own lateral offset and an endpoint whose Z lane is extended by `1.0f`, then
constructs the generated position.

Adding the two previously collapsed owners raises focused matching from 40.83%
(668/679) to 41.27% (678/679) and improves the masked audit from 30 to 31 clean
operands with no unresolved or mismatched masks. P's candidate frame grows from
`0x38` to `0x44` against the native `0x40`; honest endpoint and counter scope
variants did not recover that four-byte slot overlap. The branch-local form is
retained because its native dataflow and near-exact instruction count are
direct evidence, while the remaining frame residual is explicitly unresolved.

## 2026-07-26 radius ownership

Raw x86 at `0x425a80..0x425aa0` proves that the incoming scale slot becomes the
single-precision absolute half-distance owner. The native code subtracts
`start_x` from `end_x`, multiplies by `0.5f`, compares the x87 value against a
dword zero, conditionally negates it, and performs one final store to the slot
subsequently consumed by all three curve variants. Ghidra 12.1.2 independently
recovers the same float half-distance and switch-wide consumer in the authored
ARM `cRPath::BuildP` at `0x5f620`.

Replacing the false `double radius_calc` plus separate float radius with a
float producer and explicit two-arm assignment to `scale_arg` raises focused
matching from 41.27% to **54.05%**. The candidate now has the exact **679/679**
instruction count, restores the native `0x40` frame, and expands the clean
masked audit from 31 to **38**, with no unresolved or mismatched operands.

Later native reuse of dead argument stack slots does not imply that the curve
divisor, angle, and Z value are source-level parameter owners. Directly
assigning them through `end_x` and `start_x` regressed to 52.58%, while moving
the curve-counter declaration to the native store site regressed to 53.76%.
The ARM function independently retains a zero-based curve counter, one-based
sample index, and byte cursor, so the scratch keeps those real owners and
leaves the remaining x86 stack-slot coalescing to the compiler.

## 2026-07-28 paired-mobile and Windows lifetime replay

The exact Android and iOS `cRPath::BuildP(int, float, int, float, float, int,
char*, char*)` bodies independently preserve the portable `curve_segments + 2`
sample count, `curve_segments + 1` terminal sample, zero-based curve counter,
one-based sample Z, and curve-phase graph. The Windows MLIL then proves where
VC6 spills that graph through dead `scale_arg`, `start_x`, and `end_x` homes.
Merging the exact EBP counter definitions with their stack spill avoids a false
second `curve_index` owner.

Both mobile bodies stop after `CalcLengthZ`. The strip vertices, face records,
UVs, winding pass, and repeated EAX/ECX/EDX `width + 1` reloads are therefore
recovered exclusively from Windows. One transaction previewed, applied,
snapshotted, and read back 23 bounded BuildP split groups. Register/stack
definitions for the mesh column, face column, and winding pass are merged only
where native SSA proves one logical counter. Reanalysis also promotes the two
basis-vector initializers and two terminal deltas to address-anchored aggregate
`Vec3` assignments.

An idempotent replay reports all 23 groups already current. Strict paired
Binary Ninja and IDA 9.4 export reports zero mismatches and 1,142/1,142 passing
health checks. The IDA refresh is retained because it replaces the stale
three-argument `PathTemplate*` view with the proven void `Path*` ABI containing
nine explicit stack arguments and exposes the `Object*` mesh owner.

This is analysis-only. Focused matching remains **54.05%** with exact **679/679**
instruction-count parity, a six-instruction exact prefix, and **41 accepted,
0 unresolved, 0 mismatched, and 0 unaudited** masked operands. No source edit,
synthetic branch, or mobile address transfer was introduced.

## 2026-07-30 sibling mesh-row replay boundary

The dependency-closed ordinary-first mesh-row shape that improves Invert,
Wibble, and both Twister targets was replayed as P's first recorded mutation
sweep. It raises the scalar score from 54.05% to 54.43% by nine weighted bytes
and preserves the six-instruction prefix and all 41 clean references, but grows
the candidate from exact 679/679 instruction parity to 688/679.

P's native evidence proves branch-local vector values and distinct face-record
owners, but it does not yet prove that the row control shares the siblings'
guarded byte-cursor source shape. The result is therefore recorded as an
instruction-count tradeoff and not retained. Further P mesh work should first
recover its native row-control owner rather than importing the family schedule
on score alone.

## 2026-07-30 authored terminal-delta subtraction

Unlike the rejected mesh-row transfer, the terminal-delta expression boundary
is exact across the constructor family. Replacing both component constructors
with `Vector3::operator-` adds 7.31 weighted bytes and raises focused matching
from 54.05% to **54.34%**. The exact 679/679 instruction count, prefix 6/679,
and all 41 clean references are unchanged; the exhaustive two-site sweep has
no tradeoff.
