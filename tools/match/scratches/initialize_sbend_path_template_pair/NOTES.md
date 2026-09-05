# initialize_sbend_path_template_pair

Current recovery: semantic-complete (`compiler` residual). The verified
Android/iOS builder bodies establish the portable sample/control graph; the
live Windows body and scratch additionally cover the native mesh/face tail.
All references are clean, and the remaining differences are code layout.

Starter reconstruction for `initialize_sbend_path_template_pair @ 0x42df00`.

Captures the family-10 S-bend setup: `height * pi` sample count, centered option,
cosine Y/Z profiles, orientation reconstruction from the current sample,
secondary offset, delta recomputation, generated strip mesh, and finalization.

Remaining work is exact source-shape tuning, not flag changes.

2026-06-21 helper-inline pass: native contains the sample setup, secondary
copy, orientation, delta, and strip-mesh bodies inline rather than calling the
scratch-local helpers. Marking the helper layer `__forceinline` raises focused
Wibo from 10.90% (118/579 candidate instructions) to 20.52% (503/579), with
23 clean masked operands and no unresolved masks. A split sweep showed the gain
is cumulative: sample-only 8.32%, small sample/orient helpers 13.99%, no-mesh
helpers 16.74%, mesh-only 13.29%, and the full helper layer 20.52%. Plain
`static inline` is not usable in this scratch under the current Wibo harness
because it reaches a missing `lstrcpynA` import path.

2026-07-03 step/y-z order: keeping the early `height * pi` x87 load but delaying
the integer step conversion until after the first header stores moves focused
Wibo to 20.70% with 24 ok, 0 unresolved, 2 mismatch. Splitting the interior loop
so each primary sample is initialized with neutral Y/Z before the computed Y and
Z writebacks moves the retained result to 22.51% (505/579), with masked operands
at 24 ok, 0 unresolved, 1 mismatch.

2026-07-03 retained helper/copy scalar cleanup: sample setup now omits the
scratch-only `lateral_source` store and orders scalar stores/copies as
`rotation_scalar_98`, `rotation_scalar_94`, `special_scalar`, `lateral_scale`.
Focused Wibo moves from 22.51% (505/579) to 22.59% (501/579), with masked
operands unchanged at 24 ok, 0 unresolved, 1 mismatch.

2026-07-03 mesh request order: the focused masked audit showed the native mesh
setup requests facequads before vertices for this constructor. Swapping only
the two strip-mesh allocation calls moves focused Wibo to 23.33% (501/579) and
clears the masked audit to 25 ok, 0 unresolved, 0 mismatch.

2026-07-04 vertices-first request-order retest: the Binary Ninja decompile
labels the mesh calls as vertices before facequads, but replaying that source
shape regressed focused Wibo from 23.33% to 22.59% (501/579) and reintroduced
one masked call mismatch (`target request_object_facequads` against candidate
`request_object_vertices`). Keep the retained facequads-first spelling until a
larger mesh-loop rewrite changes the alignment context.

2026-07-13 interior lane ownership: both native decompilers show the oriented
primary sample copied to its secondary peer as exactly 0x40 bytes. Removing the
scratch-only scalar copies outside `TransformMatrix` moves focused Wibo from
23.33% (501/579) to 24.67% (491/579), with the masked audit improving from
25 ok to 29 ok and remaining fully clean.

2026-07-15 sample and mesh ownership: the base secondary sample, like the
interior lane, owns only its transform; its X comes from the primary base
sample, while Y and Z are authored constants. Direct base/interior array writes
recover that split and the primary-derived `center_x`. The native mesh then
uses a two-iteration face loop and direct terminal sample stores. Recovering
those shapes raises focused Wibo from 24.67% (491/579) to 40.61% (529/579),
with 36 clean masked operands.

This pass also supersedes the earlier audit-led request-order note: raw calls at
`0x42e37c` and `0x42e38e` resolve to `request_object_vertices @ 0x42f710`
followed by `request_object_facequads @ 0x42f8c0`. Restoring that semantically
correct order costs less than one point in isolation, remains audit-clean, and
is retained instead of matching the old alignment artifact.

## 2026-07-17 constructor ABI closure

The Windows tail returns with `retn 0x1c`, proving seven stack arguments after
the `Path*` receiver. The world initializer supplies integer width, float
height and Z amplitude, a byte centered flag, two surface textures, and the
Windows-only vertical texture. The iOS `BuildSBend` symbol independently
preserves the portable prefix through the surface textures.

Guarded Binary Ninja recreation and readback now recover that exact void member
ABI and the centered branch on its real byte owner. Correcting the shared
declaration and scratch from `int centered` to `char centered` is a genuine
source improvement: focused Wibo rises from 40.61% to 40.79% (529/579), while
all 36 masked operands remain clean.

## 2026-07-20 live lifetime ownership

A guarded transaction proves ten complete live owners: the seed sample,
primary up/right vectors, secondary position, both terminal deltas, the mesh
sample and vertex, and both face records. The retained decompile has zero
`__offset` expressions. Typing the byte-biased forward cursor was rejected
because it introduced four backward-offset artifacts. Focused matching remains
40.79% (529/579), with 36 clean masked operands.

## 2026-07-25 induction and mesh-vector ownership

Raw native assembly proves that the interior sample loop owns a zero-based
counter at stack offset `0xa8`: the authored sample is `counter + 1`, while the
phase uses the counter directly and the backedge compares it with `steps`.
Recovering that split raises focused matching to 40.90% and adds a clean masked
operand.

The mesh vertex loop also branches on the terminal row inside the column loop.
For ordinary rows it materializes one aggregate generated position before
copying three lanes to the vertex. For the terminal row it separately
materializes a lateral-offset vector and a generated position based on the
previous sample, with the `+1.0f` owned by Z. Recovering those branch-local
aggregate owners together with the zero-based sample counter raises the retained
result from 40.79% (529/579) to 41.24% (546/579), with 37 clean masked operands
and no unresolved or mismatched masks.

An aggregate secondary-position offset was rejected. Although locally
plausible, it regressed the combined result to 39.57% and changed unrelated
register lifetimes; the native scalar additions remain the retained spelling.

## 2026-07-26 complete mesh-vector ownership

The completed family model identifies two owners still collapsed by the
initial SBend rewrite. Native `0x42e3e2..0x42e4b0` first materializes a
lateral-offset vector for the ordinary branch before its generated position.
The terminal branch separately owns an endpoint derived through the current
row cursor from the previous sample, with its Z lane extended by `1.0f`.

Adding those owners raises focused matching from 41.24% (546/579) to 44.99%
(559/579), improves the masked audit from 37 to 38 clean operands with no
unresolved or mismatched masks, and recovers the exact native `0x48` frame plus
a seven-instruction exact prefix. The face initializer also now names the
owning 16-bit `header_word` proven by the native word clear; that field-width
correction is score-neutral.

## 2026-07-27 mobile-authored selector type

The exact paired Android/iOS Path.o symbol,
`cRPath::BuildSBend(int, float, float, bool, char*, char*)`, preserves the
Windows scalar and surface-texture prefix. Windows adds only its final vertical
texture slot, proving that the centered selector is an authored `bool`.

Promoting the earlier byte placeholder from `char` to `bool` is byte-identical:
focused matching remains 44.99% (559/579 candidate/target instructions), with
a seven-instruction exact prefix and 39 clean masked operands. Windows' full
seven-stack-argument ABI is unchanged.

## 2026-07-28 dual-port control and stack-home ownership

The exact Android and iOS `BuildSBend` bodies independently preserve the
authored controls: `steps = int(height * pi)`, a zero-based sample index, and
`phase = index * 2*pi / steps`. Windows remains the machine-code authority and
adds the vertical texture slot. Its mesh tail proves that VC6 then reuses the
dead width, height, Z-amplitude, and centered argument homes for unrelated
vertex, column, and UV values.

Guarded definition-bounded splits now recover `sample_index`, `phase`,
`mesh_vertices`, `mesh_column`, `mesh_width_cells`, `face_column_for_uv`, and
the four UV scalars `u0`, `u1`, `v0`, and `v1`. The retained decompile no
longer routes those owners through `width_cells_`, `height`, `z_amplitude`, or
`centered.d`. IDA 9.4 provides a second opinion by exposing the same physical
homes as successive aliased locals.

This is a provenance and ownership recovery, not a source-shape score claim:
the matcher source remains 44.99%. Binary Ninja still prints a few reads from
the original `centered` home because the dword counter overwrite is an
`MLIL_SET_VAR_FIELD`; the replay helper now sees that destination and splits it
transactionally while retaining the mobile-proven `bool` parameter.

## 2026-07-30 terminal-delta expression ownership

The exact terminal-delta helper shape shared with Twister permits a bounded
allocation-owner transfer. Replacing four function-loop pointer aliases with
direct primary and secondary array ownership raises focused matching from
44.99% to **55.57%**, adds 218.67 weighted bytes, and extends the exact prefix
from 7 to **67/579** instructions. The candidate moves from 559 to 562
instructions and all 39 masked references remain clean.

With those direct owners established, replacing both expanded component-wise
subtractions with the authored `Vector3::operator-` form adds another 10.87
weighted bytes. The retained result is **56.09%**, 562/579 candidate/target
instructions, prefix 67/579, and 39 clean references. The exhaustive two-site
sweep also covers either operator in isolation; the paired form is the unique
best result and introduces no proof-state or instruction-count tradeoff.

## 2026-07-30 authored orientation subtraction

The primary orientation expression carries the same independently recovered
`Vector3::operator-` ownership. It adds 14.50 weighted bytes and raises
focused matching from 56.09% to **56.79%**, while preserving 562/579
instructions, prefix 67/579, and all 39 clean references.

## 2026-07-30 native mesh replay and face emission

Raw Windows assembly proves the mesh row is a guarded, nested do-loop using a
`0xa8`-byte sample cursor, with the ordinary row as fallthrough and separate
sample/vertex owners in the ordinary and terminal branches. Replaying that
complete schedule is a material win: 56.79% becomes **65.21%**, adding 173.99
weighted bytes while preserving the 67-instruction prefix and all 39 clean
references.

The native face tail contains parity-controlled equal-arm texture calls.
Adding those authored branches while retaining the existing common face record
adds another 17.10 weighted bytes and brings the candidate from 562 to 578
instructions against the native 579. Branch-local face records and the full
guarded face schedule both regress sharply, so they are not retained.

The final focused result is **66.03%** (578/579 candidate/target instructions),
prefix 67/579, exact `0x48` frame, and 39 clean references. Retesting the
secondary offset after the mesh change rejects all eight vector and scalar
owner alternatives; the closest named-scalar form still loses 19.04 weighted
bytes. All 24 one- and two-site parity orientations are byte-neutral.

The checked ledger contains eleven sweeps and 52 unique variants: seven
improving, 26 neutral, and 19 degrading. That history documents the current
SBend source-shape frontier.

## 2026-07-30 mesh arithmetic ownership

The native mesh block already proven at `0x42e3e2..0x42e4b0` also preserves
allocation-sensitive arithmetic ownership. Widening the shared lateral
temporary from `float` to `double` adds 8.32 weighted bytes, while the
expression-only double spelling incurs reference debt and the split-float and
volatile alternatives are neutral or sharply worse.

An exhaustive 35-variant interaction sweep then proves that both branch-local
lateral scales and both generated-position additions use the authored
`Vector3` operators. All four sites are required for the best result; either
operand order for the additions emits identical bytes. The retained
position-first spelling is consistent with the independently recovered mesh
family.

Together the five changes add 44.20 weighted bytes and raise focused matching
from 66.03% to **68.17%**. The candidate is 574/579 instructions, the exact
prefix remains 67/579, and all 39 masked references remain clean. The two
bounded sweeps cover all 39 planned variants without truncation.

## 2026-07-30 Y-profile ownership

Native `0x42e09d..0x42e0b0` applies the half-wave scale before multiplying by
`height`. Splitting that ownership in the source, parallel to the already
authored Z-profile sequence, prevents VC6 from reversing the two factors and
adds 3.59 weighted bytes. All five grouped, nested, named, and split spellings
emit the same winning code.

The retained compound form raises focused matching from **68.17%** to
**68.34%**, with 574/579 candidate/target instructions, a 67-instruction exact
prefix, the exact `0x48` frame, and all 39 references clean.

Two adjacent allocation hypotheses remain rejected. Naming the hoisted
floating-point step denominator is neutral only when loop-local; persistent
names lose 10.74 weighted bytes and shorten the prefix to 59 instructions.
Retesting the native-looking three-scalar secondary offset after the mesh
arithmetic change still loses at least 19.04 weighted bytes, while pointer and
aggregate forms lose more than 239. The compact direct secondary additions
therefore remain independently measured.

## 2026-07-31 terminal, face, and secondary ownership

The Windows terminal mesh row retains the current `0xa8`-byte sample cursor and
addresses the prior sample through a negative element index. Removing the
scratch-only `sample - 1` pointer adds 17.94 weighted bytes. Reconstructing the
endpoint as a default `Vector3` with separate X, Y, and extended-Z assignments
adds another 15.43 weighted bytes and recovers the native integer Y copy.

The face tail is a guarded nested schedule: `column` is zeroed before the
positive-width guard and the width loop is a do-loop. More importantly, the
native reuses the original argument homes for `face_index`, `column`, and the
facequad base. A common face pointer obscured that ownership. Naming the
integer face offset while keeping direct indexed record writes recovers the
three exact stack homes and raises the focused match from 71.00% to **79.07%**.
All 24 parity orientations are byte-neutral.

Several tempting address shapes are now bounded. Branch-local face pointers
regress to 61.01%; branch-local integer offsets regress to 70.02%; and repeating
the complete index at every field expands the candidate to 741 instructions
and 44.55%. Array and pointer-plus-index spellings for the interior samples are
byte-identical, as are asymmetric indexed and pointer access spellings for the
second face. The stable integer offset is therefore retained.

The exact Android and iOS bodies independently confirm that the copied
secondary transform receives a scaled `basis_up` vector. Replaying that
aggregate offset after the face allocation graph stabilized is a material
late-context improvement: it adds 40.63 weighted bytes and reduces the
candidate from 582 to 581 instructions, moving 79.07% to **81.03%**. An
explicit component constructor for the terminal generated position then adds
3.57 weighted bytes.

The retained result is **81.21%** (581/579 candidate/target instructions),
prefix 67/579, exact `0x48` frame, and 39 clean references with no unresolved,
mismatched, or unaudited masks. The checked ledger now contains 33 sweeps and
205 unique variants; all seven terminal component operand-order combinations
are byte-neutral. The remaining gaps are register/SIB selection, one
cross-call argument schedule, terminal x87 stack order, and face-tail code
layout rather than unresolved behavior.

## 2026-07-31 sample and delta cursor cascade

The exact iOS and Android bodies use a logical sample counter alongside a
physical `0xa8`-byte sample cursor. The Windows target has the same ownership:
EBX initially holds the positive `steps` guard, then becomes the `0xa8` cursor,
while a separate logical counter drives the phase and loop condition.
Replaying that guarded do-loop and materializing the fixed `(1, 0, 0)` up
vector before the cursor recovers the authored register lifetime. The focused
match rises from **81.21%** to **88.85%**, and the exact prefix extends from 67
to 216 instructions.

The inlined delta pass has the same two-owner shape: a logical counter controls
the `segment_count - 1` loop while a byte cursor advances through both sample
arrays. Recovering it raises the result to **90.06%**, with 578/579
candidate/target instructions, an exact 373-instruction prefix, the exact
`0x48` frame, and all 39 references clean. Reverting only the delta cursor
loses 25.02 weighted bytes and 157 prefix instructions; reverting the complete
sample-cursor cascade loses 183.09 weighted bytes, adds three candidate
instructions, and shortens the prefix by 306. Inlining the fixed up-vector
value independently loses 3.57 weighted bytes and drops the prefix from 373
to 69.

The new frontier starts in the terminal endpoint's x87 addition schedule.
All seven component operand-order combinations, all six named component
lifetime orders, and all 24 face-parity orientations are byte-neutral.
Reintroducing a common face pointer after the cursor recovery regresses to
80.42%. These bounded replays leave terminal x87 scheduling and equivalent
face-tail layout as the residual, not an unimplemented behavior or unsafe
reference shortcut.

## 2026-07-31 post-cursor terminal emission bound

The broader terminal construction grid had previously been measured before
the sample/delta cursor cascade, so it was replayed against the final 90.06%
allocation. Neither authored `Vector3::operator+` order nor default component
assignment reproduces the native x87 stack; each loses 3.57 weighted bytes.
Copy-plus-assign forms lose 161.90 to 172.55 weighted bytes, add six to eight
instructions, and shorten the exact prefix from 373 to 69.

Five direct vertex-emission forms close the remaining source boundary.
Constructor assignment is byte-identical to the retained local constructor.
Direct pointer/array fields and named component stores instead shorten the
candidate by five instructions, collapse the prefix to zero, and fall to
79.86%. The scratch remains **90.06%**, 578/579 instructions, prefix 373/579,
with all 39 references clean. The first mismatch at `0x42e477` is now bounded
across operand order, local lifetime, aggregate construction, compound
assignment, and direct destination emission.

## 2026-09-05 continued loop-owner campaign

Fifteen mesh-vector lifetime combinations and six direct authored-body expansions are neutral at 90.06%. The helper boundary is not sufficient to explain this builder's remaining terminal and face schedule. Canonical source stays unchanged.

## 2026-09-05 continued source-shape investigation

The terminal endpoint is now expressed as `(previous.position + Vector3(0, 0, 1)) + previous.basis_right * lateral`. Unlike the scalar endpoint reconstruction, this preserves the vector addition evaluation and reproduces the entire native terminal x87 sequence. All temporary, local, and outer constant-vector forms of this nested expression agree. The retained temporary form improves 90.06% to 91.10%, extending the exact prefix from 373 to 443, with all 39 references clean. This directly supersedes the earlier claim that the terminal expression boundary was closed.

Five branch-owner forms, three setter forms, and two diagnostic constructor forms do not improve the prior baseline. After the endpoint recovery, twelve UV-owner forms are non-improving; twelve parity/UV duplication forms regress, and four winding-dispatch forms have no tradeoff-free gain. These experiments leave the face schedule open rather than attributing it to the compiler.

Fifteen per-corner UV value forms and fifteen texture-selection expression forms also give no tradeoff-free improvement; no auxiliary UV type or helper is retained.

Twelve face-index arithmetic forms, 6 cross-phase counter reuse forms, nine face-field ownership forms, and twelve checkerboard-parity expressions add no tradeoff-free gain. Wide integer index expressions are byte-neutral, so the explicit short casts are not required by code generation. The nested checkerboard form raises Snake's fuzzy score but worsens instruction count and is rejected. These receipts preserve the tested combinations without closing the face-source hypothesis.

## 2026-09-05 additional source-shape checks

Seven combinations of const vector value returns are byte-neutral at 91.10%. No shared-header change is retained.

## 2026-09-05 operation-boundary checks

Six complete front/back face-emission helper forms test both indexed banks and per-face pointer arguments. Indexed forms are neutral at 91.10%; pointer forms regress. The native branch-local address scaling and UV publication remain unresolved. No helper is retained.

## 2026-09-05 shared checkerboard texture operation

Twelve `whole-shared-texture-choice-20260905-mutations.json` forms separate
checkerboard texture selection from face publication. They cover returned
texture values, direct face publication, parity versus row/column arguments,
value/reference texture parameters, and both predicate orientations. Both
texture parameters receive the same per-winding source texture, preserving
the native apparently redundant checkerboard choice. All are neutral at
91.10%, prefix 443, with all 39 references clean. No helper is retained. This
operation boundary does not recover the branch-local face address or UV
publication schedule; it does not establish exhaustion.

## 2026-09-05 shared vector operator ownership diagnostics

Four `whole-vector-operator-ownership-20260905-mutations.json` variants embed
an unchanged vector header control and move addition, subtraction, or both
from free const-reference functions to const members with identical explicit
result bodies. All are neutral in this caller. The same four-way replay in
S-bend, star-field initialization, CreateGolb, and exact LookAt also stays
neutral, with unchanged instruction counts, prefixes, and clean references.

These results do not independently prove free-versus-member authored spelling;
they show that this distinction does not explain the tested native differences.
No shared header or caller-specific operator implementation is changed.

## 2026-09-05 owning-member build phases

Six whole-source variants inline the delta phase, strip-mesh phase, or both
into the owning cRPath method, with explicit blocks or flat local scopes.
All are neutral at 91.10%, 578/579 instructions, prefix 443, and 39 clean
references. The scratch-only helper boundary is not responsible for this
measured residual. No source change is retained.
