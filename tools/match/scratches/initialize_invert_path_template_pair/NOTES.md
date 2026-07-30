# initialize_invert_path_template_pair

Ownership reconstruction for `initialize_invert_path_template_pair @ 0x429250`.

Models the fixed 34-sample invert template with `0x29` kind, runtime flag `+0x9c`
set, terminal `pi` rotation scalar, half-angle interior rotation scalar,
secondary offsets, deltas, strip mesh generation, and finalization.

Current focused result: 70.69% (611/600 candidate/target instructions), with
35 masked operands ok, 0 unresolved, and 0 mismatched. The exact prefix covers
109 target instructions and the candidate retains the native `0x54` frame.
Residuals are primarily commutative address encodings, interior stack coloring,
and face-loop value schedules; this reconstruction deliberately avoids
normalizer gaming.

2026-06-21 helper-inline sweep: native flattens the scratch-local helper layer.
Forcing those helpers inline moves focused Wibo from 8.66% (116/600
candidate/target instructions) to 20.20% (509/600), with masked operands
improving from 7 ok, 0 unresolved, 7 mismatch to 14 ok, 0 unresolved, 2
mismatch.

2026-07-03 retained helper/copy scalar cleanup: sample setup now omits the
scratch-only `lateral_source` store and orders scalar stores/copies as
`rotation_scalar_98`, `rotation_scalar_94`, `special_scalar`, `lateral_scale`.
Focused Wibo moves from 20.20% (509/600) to 22.89% (501/600), with masked
operands improving from 14 ok, 0 unresolved, 2 mismatch to 18 ok, 0 unresolved,
2 mismatch.

2026-07-03 retained interior-X cleanup: the native interior loop stores the
interpolated lateral value in `center_x` but leaves transform `position.x` at
0.0f. Spelling that through the sample initializer moves focused Wibo from
22.89% (501/600) to 23.82% (500/600), and clears the masked audit from
18 ok, 0 unresolved, 2 mismatch to 21 ok, 0 unresolved, 0 mismatch.

2026-07-04 retained mesh-face loop cleanup: replacing the direct two-face
`a`/`b` writes with the shared two-iteration `face_index` loop and single
`uv[3].v` tail store moves focused Wibo from 23.82% (500/600) to 29.37%
(510/600), with masked operands improving from 21 ok, 0 unresolved,
0 mismatch to 23 ok, 0 unresolved, 0 mismatch.

2026-07-13 terminal ownership: replacing `primary_last` and `secondary_last`
pointer aliases with direct count-relative stores through the two `Path` sample
arrays moves focused Wibo from 29.37% (510/600) to 31.31% (518/600). The
masked audit remains clean at 23 ok, 0 unresolved, 0 mismatch. The delta loop
retains its local sample pointers, matching the independently measured `wibble`
boundary.

2026-07-13 interior lane ownership: the native interior loop copies only the
0x40-byte `TransformMatrix`; `center_x`, rotation, special, and lateral-scale
fields remain primary-owned. Giving that loop an interior-specific transform
copy moves focused Wibo from 31.31% (518/600) to 33.94% (508/600), while the
masked audit remains clean at 23 ok, 0 unresolved, 0 mismatch. Letting the
transform-only helper also cover endpoints scored 36.03% (488/600) but
introduced two call mismatches and lost the endpoint ownership boundary.
Spelling the independently initialized endpoint transforms directly, including
the primary-only terminal pi rotation, scored 30.77% (479/600) with two call
mismatches. Those endpoint experiments were rejected; only the proved interior
ownership change is retained.

2026-07-13 interior orientation ownership: each primary sample owns the
position delta from its predecessor as `basis_forward`, normalizes that vector,
then owns `basis_right = basis_up cross basis_forward` before its 0x40-byte
transform is copied to the secondary lane. Recovering that sequence moves
focused Wibo from 33.94% (508/600) to 36.59% (537/600), with the masked audit
still clean at 25 ok, 0 unresolved, 0 mismatch.

2026-07-15 sample ownership cascade: expanding both endpoints and the interior
initializer into directly owned `PathSample` stores recovers the independent
primary/secondary endpoint transforms, the primary-only terminal pi rotation,
and the native split `sample_index`/`local_index` traversal. The interpolated
center remains primary sample metadata while transform X stays zero; interior
secondary samples receive only the 0x40-byte transform before their basis-up
offset. This source shape scored 51.27% (539/600), with 32 ok, 0 unresolved,
0 mismatch before the mesh argument ownership correction below.

2026-07-15 strip texture ownership: target stack references prove that face 0
uses `texture_b` and face 1 uses `vertical_texture`; `texture_a` is not consumed
by this generated strip. The generic row/column parity branch remains in the
native code even though both arms select the same respective texture pointer.
Recovering those arguments, the per-branch 16-bit `header_word` clear, and the
two face-local bodies gives the retained 49.66% (564/600), with 30 ok,
0 unresolved, 0 mismatch. This is lower than the 51.27% intermediate but fixes
real behavior, remains well above the 36.59% baseline, and brings the candidate
instruction count materially closer to the 600-instruction target.

## 2026-07-17 live constructor ABI closure

Both native world-init callsites push `6.0f`, width `8`, mode `1`, two surface
textures, and the vertical texture before calling this constructor; the tail at
`0x429ac6` is `retn 0x18`. iOS exposes the same
`(float, int, bool, char*, char*)` prefix for both `BuildInvert` and
`BuildInvert1`, so the ABI is portable evidence even though the exact surviving
Windows name split remains intentionally unresolved.

Guarded recreation and post-write readback now expose the complete seven-
parameter `Path*` prototype with no pending operation. The refreshed caller
shows full-arity owners at public slot `0x29` and transition slot `0x3e`, and
the callee now ends in void finalizer flow. This is analysis-only: focused
matching remains 49.66% (564/600) with 30 clean masked operands.

## 2026-07-20 live lifetime ownership

A guarded transaction proves ten complete live owners: the primary seed,
up/right vectors, secondary position, both terminal deltas, mesh sample and
vertex, and both face records. Their accesses now render through
`PathTemplateSample`, `Vec3`, and `ObjectFaceQuad`. The constructor retains its
16 existing fixed-index `__offset` occurrences for samples 32/33, but the
replay adds none. Focused matching remains 49.66% (564/600) with 30 clean
masked operands.

## 2026-07-25 mesh-vector ownership

Raw native assembly at `0x42978f..0x42986c` proves that the row-terminal test
belongs inside the vertex column loop. Ordinary rows materialize a complete
generated-position vector before copying its three lanes to the output vertex.
The terminal row instead owns a separate lateral-offset vector based on the
previous sample, followed by a generated-position vector whose Z lane owns the
`+1.0f`.

Recovering those branch-local aggregate owners raises focused matching from
49.66% (564/600) to 50.00% (592/600). The masked audit improves from 30 to 31
clean operands, with no unresolved or mismatched masks. The remaining native
`0x54` versus candidate `0x3c` frame gap therefore belongs to other constructor
lifetimes rather than the mesh vertex ownership.

## 2026-07-26 complete mesh-vector ownership

The recovered family model shows that the initial rewrite still collapsed the
ordinary branch's lateral-offset vector and the terminal branch's endpoint
vector. Native `0x42979e..0x42986c` materializes both: the endpoint comes from
the previous sample reached through the current row cursor and extends its Z
lane by `1.0f`.

Adding those owners raises focused matching from 50.00% (592/600) to 51.71%
(599/600), preserves 31 clean masked operands with no unresolved or mismatched
masks, and recovers the exact native `0x54` frame plus a seven-instruction exact
prefix. The candidate is now one instruction shorter than the target. Its first
residual is an ESI/EDI owner swap after the prologue, not missing mesh dataflow.

## 2026-07-26 secondary offset ownership

The native interior-copy tail at `0x42953c..0x42959b` computes all three
primary up-vector products before updating any secondary position lane. Those
products form one `Vector3` offset, and the destination position is a separate
borrowed `Vector3*`; the prior scratch expressed three unrelated scalar
updates.

Recovering both owners raises focused matching from 51.71% to **52.92%**.
The candidate is 598/600 instructions, retains the exact `0x54` frame and
seven-instruction prefix, and expands the clean masked audit from 31 to **33**
operands with no unresolved or mismatched masks. The prologue register-owner
swap remains, so no register coercion is introduced.

## 2026-07-27 paired mobile boolean ownership

The exact Android and iOS symbols both name
`cRPath::BuildInvert(float, int, bool, char*, char*)`, proving that the third
authored scalar is `bool side_exit`. Both bodies end after sample/delta
construction and `CalcLengthZ`; Windows retains the sixth stack argument for
the vertical texture and builds the strip mesh locally. Refining the source,
shared headers, and analysis prototypes is ABI- and byte-neutral: focused
matching remains 52.92% (598/600), with a seven-instruction prefix and 35 clean
masked operands.

iOS also contains `BuildInvert1`, so the Windows-to-mobile name mapping remains
conservatively medium confidence. That family split does not weaken the exact
parameter type shared by the paired `BuildInvert` symbols. The residual Windows
prologue is still an ESI/EDI owner swap; no register coercion is introduced.

## 2026-07-28 paired mobile control ownership

The exact Android and iOS `BuildInvert` bodies independently preserve endpoints
0 and 33, 32 interior samples, a logical interior index starting at zero, and a
separate `0xa8`-stride sample cursor. Their interior expression tree also
preserves one `2*pi/32` curve phase, shared by the half-angle rotation scalar
and sine/cosine up-vector construction. The `BuildInvert1` family ambiguity
does not affect that portable control graph.

Windows MLIL/SSA at `0x4293dd..0x429573` proves the exact native definition
identities. A guarded transaction reunifies the register, argument-slot, and
temporary-stack fragments as `interior_index`, keeps
`interior_sample_offset` as an integer byte cursor, and recovers
`curve_phase`. The Windows delta loop at `0x4295a4..0x42966b` independently
proves `delta_index` and `delta_sample_offset`. Preview, application, live
readback, and idempotent replay all pass without increasing the 16 existing
fixed-index `__offset` occurrences.

This is analysis-only. Focused matching remains **52.92%** (598/600), with a
seven-instruction prefix and 35 clean masked operands. Strict paired Binary
Ninja and IDA 9.4 export reports zero selector mismatches.

## 2026-07-30 value, delta, and mesh lifetime closure

The retained batch began at **52.92%** (598/600 candidate/target instructions),
with a seven-instruction prefix, the exact native `0x54` frame, and 35 clean
masked operands. Paired Windows and mobile evidence supports authored vector
values for the interior secondary offset, both path-delta subtractions, and the
interior forward direction. Recovering the first three together reaches
54.00% with an exact 600/600 instruction count. Advancing the logical interior
index before constructing the secondary offset then resolves the global
ESI/EDI owner swap, raising agreement to 58.55% and extending the exact prefix
from 7 to 109 instructions. The interior forward `operator-` extends it again
to 114 instructions, and a named integer-to-float Z-position owner gives the
small retained move to 59.05%.

The Windows delta loop keeps EDI as its logical counter and ESI as its
`0xa8`-stride cursor. Named current/next sample pointers consumed ESI and
produced the mirror allocation. Direct primary or secondary array ownership is
worse alone, but recovering both lanes together restores the native owners and
raises agreement to **63.51%**. Reverting either authored subtraction operator
under that owner shape is also worse. The paired form grows the candidate to
603 instructions and shortens the exact prefix to 109, but improves the delta
region by 97 weighted bytes and preserves all 35 audited references.

The native vertex loop uses a guarded logical row, a separate `0xa8` sample
cursor, ordinary-row and terminal-row vector values, and branch-local vertex
destinations. A guarded byte cursor alone is byte-identical. Recovering the
complete branch-local shape raises agreement to 67.71%; isolating the control
order proves that ordinary rows must remain the first branch and the terminal
row the fallback, producing the retained **70.69%** result. The final candidate
is 611/600 instructions, retains the 109-instruction exact prefix and `0x54`
frame, and keeps 35 references clean with no unresolved, mismatched, or
unaudited operands.

Twenty recorded sweeps cover 79 evaluated variants. The bounded neutral and
negative results are:

- advancing the sample cursor before the three offset additions is
  byte-identical, while advancing the logical counter before the position
  stores falls to 56.50% and creates one unaudited reference;
- inlining the derived Z integer expression is byte-identical; a named
  converted float is the only small improvement;
- six extra `basis_up` destination/value forms fall to 48.58%..54.50%;
- three guarded delta schedules are byte-identical, and component delta
  constructors lose 4..7 weighted bytes under direct array ownership;
- mesh acquisition order, native face-address grouping, four lateral scalar
  spellings, and supported member scale operators are byte-identical;
- the complete guarded native face schedule falls to 66.39%, a loop-scoped
  vertex column falls to 64.74%, and a separate face-segment counter falls to
  67.38%;
- sharing the vertex destination retains only 67.89%, while terminal vector
  addition via `operator+` falls to 69.92%;
- the unsupported `scalar * Vector3` spelling was rejected by the recovered
  class ABI and rerun as the valid, byte-identical `Vector3 * scalar` form.
