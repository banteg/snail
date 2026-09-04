# calc_object_facequad_normals

Current recovery: semantic-complete (`compiler` residual). Exact Android/iOS
`cRObject::CalcFaceQuadNormals` bodies and the live Windows `Object` method
establish the complete face-pair construction, weighted vertex accumulation,
validation, normalization, inversion, and temporary-tally lifetime. All 22
references are clean; the four-instruction deficit is bounded VC6 tally/x87
and scale-one SIB allocation.

Ownership-recovered scratch for `calc_object_facequad_normals @ 0x42fcb0`.

This is the full object normal rebuild used by object build and animation
refresh paths. It extends the lighter `calc_object_facequad_normals_simple`
shape with per-vertex normal accumulation:

- calls `request_object_facequad_normals` to ensure both `vertex_normals` and
  `facequad_normals` exist;
- allocates a temporary `Normal Tally` float array sized to `vertex_count`;
- zeros that tally with the native `memset`/rep-store pattern;
- walks each 0x30-byte facequad and writes two 12-byte face normals into the
  `Object::facequad_normals` pair stream;
- for four-index quads, accumulates the second face normal into all four
  vertex-normal slots with weight `1.0f`;
- accumulates the first face normal into all four vertex-normal slots with
  weight `2.0999999f`;
- reports `"Invalid Face Vertex Index"` when any face index is greater than
  `vertex_count`;
- divides each vertex normal by its tally, normalizes it, then inverts it;
- frees the temporary tally buffer.

2026-07-10 ownership recovery applies the exact value and alias shape proven by
`calc_object_facequad_normals_simple`:

- each vertex subtraction first owns a temporary `Vector3`, then copies into
  the persistent `lhs` or `rhs` cross-product operand;
- face and output-normal addresses are recomputed from their byte offsets
  instead of retained as long-lived pointers;
- quad normal construction/storage and quad accumulation are two independent
  flag checks, matching the native control flow;
- vertex-normal additions for all four face indices happen first, followed by
  all four tally increments, for both the `1.0f` quad contribution and the
  `2.0999999f` primary contribution;
- final inversion owns a returned/temporary vector value which is copied back,
  while the divide-only normal pointer ends before normalization;
- the same source counter is reset between face and vertex phases, and tally
  access remains the natural `normal_tally[index]` expression.

`OBJECT_FACEQUAD_FLAG_TRIANGLE` is the owned face-kind discriminator: this
builder omits the second face normal and fourth-corner accumulation when it is
set, matching the X-loader producer and the edge/index consumers.

Focused Wibo rises from 17.13% (392/437, one masked mismatch) to 90.03%,
436/437 candidate/target instructions, prefix 27/437, and 22 clean masked
operands with no unresolved or mismatched operands. Native now agrees on the
0x68-byte frame, `this` in `esi`, tally allocation in `ebx`, and face offset in
`edi`.

The honest residual is VC6 allocation/encoding: it assigns the shared counter
and normal offset to the opposite two stack slots, chooses the counter rather
than the strength-reduced tally cursor for `ebp` in the final phase, and emits
equivalent base/index ordering for repeated `facequads + face_offset` SIB
operands. Explicit cursor, declaration-order, operand-order, and wider pointer
lifetime probes did not recover that tie and were not retained.

The iOS ARMv6 binary retains this owner as
`cRObject::CalcFaceQuadNormals()` in `RObject.o`; both Windows callers discard
EAX and consume the rebuilt normal arrays through the same `Object`. The
analysis headers and repeatable BN/IDA sync now use the source-shaped void
thiscall instead of a synthetic integer fastcall. This is an ownership/ABI
correction only and does not hide the 90.03% stack-allocation residual.

## 2026-07-15 checked-in owner replay

The refreshed Binary Ninja artifact now carries `Object*` through the normal
allocator, vertex/facequad banks, counts, and final free. Its health check
rejects the prior `arg1`/raw-offset form without changing the 90.03% scratch.

## 2026-07-18 two-lane normal ownership replay

The restarted Binary Ninja session confirms the void `Object` method and both
callers without further mutation. The repeatable IDA lane is now anchored at
`0x42fcb0`, verifies `ObjectToonEdge` alongside the existing Object geometry
types, and persists the temporary `float* normal_tally`, primary
`face_normal`, secondary `quad_normal`, and their loop owners. The refreshed
artifact therefore exposes the same vertex, facequad, and normal banks as the
source-shaped scratch instead of the old `int* this`/integer-return form.

Focused Wibo remains honestly unchanged at 90.03%, 436/437 instructions,
prefix 27/437, and 22 clean masked operands. No matcher source change was
retained; the residual is still the documented VC6 stack-slot and register
allocation tie.

## 2026-07-23 durable full-normal ownership graph

The Binary Ninja replay now guards and restores 34 native lifetimes across the
complete rebuild:

- the allocation result and retained EBX owner for the heap `float` tally;
- integer face/normal/vertex byte offsets and the two loop indices;
- complete `ObjectFaceQuad*` borrows for primary, quad, accumulation, and
  validation phases;
- every retained `Vec3*` vertex borrow used to construct both face normals;
- owned `face_normal` and `quad_normal` stack values plus their output slots;
- all eight `Vec3*` vertex-normal accumulation slots;
- the tally cursor and the final average, normalize, and inversion borrows.

The shared EDI lifetime is deliberately `int32_t`: native advances it by
`0x30` in the face loop, resets it, then advances it by `0x0c` in the vertex
loop. It is never an owned `float*` or synthetic array cursor. The refreshed
decompile now exposes `vertex_0` through `vertex_3`, component-level
accumulation into each vertex normal, validation through a complete face, and
the full final normal pass. Direct base-plus-offset expressions that native
forms without first materializing a complete face pointer remain visible.

The matcher source is unchanged and still reports the honest 90.03%,
436/437-instruction result with 22 clean masked operands. This slice improves
recoverable ownership only; it does not disguise the established VC6
stack-slot, register-allocation, or SIB-order residuals.

## 2026-07-29 mobile-authored geometry surface

Android and iOS retain this body as `cRObject::CalcFaceQuadNormals()`. Their
shared `RObject.o` family also preserves `CalcTextureGroups`, `AddEdge`, and
`CalcEdges`. Those authored member names now replace the descriptive matcher
surface and all typed Windows callsites; the stable scratch IDs, addresses,
calling conventions, and honest residuals remain unchanged.

## 2026-07-30 final tally cursor lifetime

Focused Wibo improves from 90.03% to **93.56%**. The exact prefix grows from
27 to 98 instructions, all 22 masked references remain clean, and the retained
source now keeps the final tally cursor explicitly:

- `ebp` owns the advancing `float*` tally cursor;
- the shared face/vertex index occupies native's `esp+0x10` stack slot;
- the face-normal byte offset occupies native's `esp+0x14` stack slot;
- the face-loop tail and final vertex-loop setup consequently match native.

The current tally element is a borrowed `const float&`. This is semantically safe
here because `normal_tally` is a fresh tracked allocation and cannot alias the
object-owned `vertex_normals` written between cursor advances. It also leaves
an honest codegen tradeoff visible: native snapshots the tally once on the x87
stack and uses three `fdiv st(1)` operations before popping it, while this
candidate divides through the borrowed memory slot three times. The candidate
is therefore 433 instructions against native's 437 rather than proof-grade.

Eight recorded sweeps covered 42 variants. Declaration and scope changes,
copied scalar values, separate vertex indices, quotient staging, direct face
address spellings, and an experimentally inlined scalar vector division were
neutral or worse. Any copied tally value makes VC6 give `ebp` back to the
counter and restores the old swapped stack-slot schedule; direct face-address
forms also preserve the repeated scale-one SIB base/index reversal. Five
consecutive post-win sweeps found no better source shape, so both residuals
remain explicit without volatile state, inline assembly, or a speculative
shared vector operator.

## 2026-09-04 source-expression diagnostics

All 31 combinations in `edge-expression-tally-interaction-mutations.json`
against `94f05adb8` test four subtraction-expression recoveries together with
a copied final tally. Replacing both quad edges changes the tail while keeping
the first 382 instructions: 435/437 instructions at 97.48%, with 22 clean
references. It also introduces new tail address/scheduling differences and is
not promoted. Adding a copied tally gives 439/437 at 94.29% and again changes
the earlier stack allocation. The canonical 97.47% source stays unchanged;
these coupled effects do not close the final divisor/owner hypothesis.
