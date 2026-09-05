# Render-cache face helper

`append_track_cache_object` @ `0x433960` is the second distinct helper after
the public cache builder. It borrows source faces and position, writes into the
manager-owned family vertex/index staging buffers, emits one triangle for
triangle faces and two for quads, and delegates vertex identity to
`add_track_cache_vertex` before enforcing the family index capacity.

Binary Ninja confirms the unused `row_index` still occupies the first stack
slot and the function returns the resulting index count (or the error-report
result on overflow).

## Owner and source-shape closure (2026-07-11)

Every caller passes the real `cRObject`/`Object` geometry owner. The older
cross-decompiler `PathTemplateStripMesh*` prototype was only a partial object
prefix and is now retired from this helper, the object allocation APIs, and
the three `Path` mesh-owner fields. The narrow prefix view
remains only in mirror/finalizer scratch source where it is an explicit
code-generation view rather than a claimed allocation type.

Writing the loop directly as `source->facequads[face_index]` lets VC6 perform
the native strength reduction: `source` stays in `esi`, `ebp` becomes the
`0x30`-byte face offset, and the compiler reloads `source->facequads` for each
vertex call. Assigning the borrowed position into the local inside the loop
also recovers the native post-empty-check lifetime. This raises the helper
from 35.65%, 164/167, prefix 1 to **95.81%, 167/167, prefix 16**, with six
clean operands.

Only two equivalent scheduling regions remain: the three scalar position-copy
loads/stores around the first call setup, and the final `max_indices` compare
register (`edx` versus `ecx`). Const qualification, component-wise float
temporaries, reversed comparison spelling, and explicit limit/result locals
did not improve those regions; the float-temporary form also introduced x87
traffic. None is retained, and no register-shaped or synthetic construct is
used.

The triangle/quad branch now uses `OBJECT_FACEQUAD_FLAG_TRIANGLE`. The X mesh
loader sets that bit only for three-index authored faces, and this cache helper
consumes it by emitting three rather than six indices; it does not own or
mutate the borrowed face record.

## Borrowed face and staging-cursor lifetimes (2026-07-19)

Exact Binary Ninja SSA readback now preserves the two coupled loop cursors:
`face_index` counts records while `face_byte_offset` advances by the native
`0x30`-byte `ObjectFaceQuad` stride. Four short EAX lifetimes are typed as the
borrowed face used for vertices 0 through 3. This recovers every source vertex
and UV pair as `face_vertex_n->vertex_n` and `face_vertex_n->uv[n]` instead of
anonymous `void*` arithmetic. The copied `Vec3` is likewise named
`local_position`, and the triangle/quad index bases join through the real
`next_index_count` staging cursor before it is stored back to the caller-owned
count.

The replay first guards `Vec3`, `ObjectUv`, `ObjectFaceQuad`, `Object`, and
`SegmentCache` widths and owner fields. A temporary byte-view annotation for
the triangle flag survived as a user variable but produced a misleading scaled
array expression, so it was deleted after exact readback rather than retained.
Direct-return, declaration-scope, comparison, and scalar-copy source probes
were codegen-neutral or worse. The honest matcher source therefore remains at
`95.81%`, `167/167` instructions, prefix `16`, with six clean operands; no
scheduling-only construct was kept.

## 2026-07-24 native `tVector(float*)` constructor

The Android binary independently retains both constructor aliases for
`tVector::tVector(float*)` at `0x172e4` and `0x17300`. Each body performs the
same authored three-lane copy: load and store offsets `0`, `4`, and `8`, then
return. This supplies the missing source-level owner for the Windows loop's
local position rather than merely suggesting a different scalar assignment
schedule.

Constructing `local_position` from the borrowed position's first float inside
the face loop reproduces the complete native copy and first vertex-call setup.
The focused result rises from `95.81%`, prefix `16`, to **`98.80%`, prefix
`155`**, while remaining `167/167` instructions with all six masked operands
clean.

The sole residual is the terminal capacity check: target and candidate load
the same `max_indices` and `*index_count` values but choose `edx` versus `ecx`
for the limit. Direct return, a retained result, a retained limit, reversed
comparison spelling, and a conditional expression all compile to the same or
worse schedule. None is retained as a register-directed workaround.

## 2026-07-29 bounded capacity-tail audit

A nine-variant sweep retested reversed comparison, retained result/limit
locals in both declaration orders, a borrowed count pointer, two
success-first branches, and a conditional result. Eight are byte-identical to
the 98.80% baseline; the reversed comparison is worse.

The exact residual is two instructions at the 155-instruction prefix. Native
emits `mov edx,[esp+0x44]`, then `mov eax,[edi]`, then `cmp eax,edx`;
the candidate loads `[edi]` first and carries the same stack limit in `ecx`.
Both paths compare the same recovered `*index_count` and `max_indices`, and all
six references remain clean. This local post-loop register allocation has no
source-level callee or neighboring definition whose TU placement can alter
the relationship, so no TU probe or register-directed source is retained.

## 2026-07-29 formal capacity-tail boundary

Three recorded sweeps cover the capacity check's control, owners, and integer
types. Five branch forms include reversed comparison, success-first in both
polarities, explicit `else`, and a conditional result. Three are
byte-identical; reversing operand polarity adds a second comparison mismatch
and regresses to 98.20%.

Six local-owner forms retain the count and limit in both declaration orders,
with const or deferred initialization, plus a borrowed count pointer. Every
form is byte-identical: even spelling the limit before the count does not
change VC6's final register schedule. Five signed/unsigned `int`/`long`
combinations produce three more neutral builds; the two unsigned-count forms
again regress to 98.20% by changing comparison polarity.

The ledger contains 16 unique variants: 0 improve, 12 are byte-identical, and
4 regress. The tested forms leave this lane at
**98.80%** (`167/167`, prefix 155, all six references clean). Native loads
`max_indices` into `edx` before loading `*index_count` into `eax`; VC6 loads
the count first and carries the same limit in `ecx`. These tested local forms did not resolve the difference. Whole-function
source lifetimes and compiler provenance remain separate hypotheses.

## 2026-09-05 whole-loop source probes

Six recorded whole-loop probes test copy construction, per-face versus outer position lifetime, and structured for/while face traversal. The copy-lifetime changes regress and the structured loops are neutral at 98.80%, with all six references clean. The capacity-tail lifetime remains open; these probes do not establish a compiler-provenance requirement.

## 2026-09-05 additional operation-boundary probes

Six ordinary capacity-check helper forms, using value/reference/pointer count inputs and value/reference limits, are byte-neutral at 98.80%. No helper is retained.

## 2026-09-05 emitted-index count borrow scopes

Four complete count-reference scopes cover function entry, after face-index
initialization, per-face entry, and the triangle/quad publication boundary.
All are neutral at 98.80%, 167/167 instructions, prefix 155, and six clean
references. No reference alias is retained; these scopes do not recover the
terminal limit-load order.
