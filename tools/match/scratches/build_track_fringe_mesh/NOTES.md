# build_track_fringe_mesh reconstruction notes

Current recovery: semantic-complete (open source-shape residual). The live Windows
`cRPath` receiver and exact Android/iOS `BuildFringe` bodies establish the
generated-object ownership, both edge extrusions and clamp cases, and the full
face/UV loop. Candidate and target are both 318 instructions with all 23
references clean; the remaining regions are store scheduling only.

`build_track_fringe_mesh` creates the generated side/fringe strip mesh for an
attachment path template. It allocates an `Object` into the template's second
`BodBase` slot at `+0x60`, copies the current track skirt colour into that BOD,
requests four vertices and two facequads per segment, extrudes the outer edge by
0.4 units along the normalized edge direction, optionally clamps X by side, and
builds the two textured facequads for each segment.

The generated mesh raises `OBJECT_FLAG_DISABLE_CULLING` and
`OBJECT_FLAG_TINT_DIRTY`. The latter transfers the retained skirt colour into
the grouped vertex stream on the first translucent draw; `render_object`
clears it after calling `set_object_color`.

Current focused result:

- match: 99.06%
- target/candidate instructions: 318 / 318
- prefix: 100 / 318
- masked operands: 23 clean, 0 unresolved, 0 mismatched

Important type notes:

- `Path +0x60` is a second `BodBase`, corroborating the
  `initialize_path_template_record_pair` constructor and this mesh builder.
- The source mesh for sampled track vertices remains the first BOD/object slot
  at `Path +0x24`; the generated mesh lives in the second
  BOD's `object` field at `+0x84`.
- Non-mirrored templates use source columns `1/0` for the first edge and
  `width_cells - 1 / width_cells` for the opposite edge; mirrored templates swap
  those pairs.
- `clamp_side == -1.0f` clamps positive generated X values to zero;
  `clamp_side == 1.0f` clamps negative generated X values to zero. Android's
  authored `cRPath::BuildFringe` independently preserves the same two exact
  sentinel cases.

Remaining gap:

The remaining gap is now local store scheduling. The exact `0x68` stack frame,
row-centered generated-vertex cursor, vector temporary family, face-loop
instruction count, near/far source-column ownership, and generated-object
register handoff are recovered. Native still schedules a few vector-result and
face index/UV stores differently.

## 2026-07-12 authored vector and clamp recovery

- Android's named `cRPath::BuildFringe` independently confirms the Windows
  algorithm. The two edge extrusions are real vector expressions:
  `outer = inner + normalize(inner - outer) * 0.4f`. Recovering the local-result
  subtraction and by-value scale/add operators raises the candidate from
  `281` to `317` instructions and restores the target's `0x68` frame.
- The skirt-colour return object is scoped only across the colour copy, so VC6
  reuses its dead stack storage for later vector temporaries. Generated rows
  read directly through the owned `Path::strip_mesh`; the redundant generic
  source-object alias is gone.
- The geometry and face loops share one integer cursor, and UV corner `3` is
  written before corners `0..2`, matching the Android owner and the Windows
  store family.
- The old `clamp_side != 1.0f` branch was a semantic reconstruction error.
  Both native ports clamp positive X only for `-1.0f`, clamp negative X only
  for `+1.0f`, and leave X untouched for every other value.

These source-backed changes improve the focused match from `42.07%` to
`69.92%`, with `317/318` instructions, an `18/318` prefix, and all `23` masked
operands clean.

## 2026-07-13 source-column and face-index ownership

- The generated face indices do not own a reusable `vertex_base` local.
  Spelling each typed index directly from `row * 4` restores the target's
  missing row copy and exact `318/318` instruction count, raising the focused
  result from 69.92% to 73.27%.
- The mirrored and non-mirrored branches assign the near source column before
  the far source column. That source order gives VC6 the native `ecx`/`edx`
  ownership through both edge-extrusion passes and raises the result to 89.31%.
  Android's `cRPath::BuildFringe` independently confirms the same near/far
  column pairs and the separate generated face loop.
- The live Binary Ninja prototype now reads
  `void __thiscall build_track_fringe_mesh(Path*, char*, float)`. Applying the
  existing `Path` type makes the leading `bod.object` visible as the sampled
  source mesh and `fringe_mesh_bod.object` as the separately owned generated
  mesh; all callers ignore the stale machine return.

Rejected probes are not retained: declaration-only reordering is codegen
neutral; an Android-shaped 16-bit vertex cursor regresses Windows to 85.98%
and loses instruction parity; narrowing the generated-object scope prevents
the native stack-slot reuse and grows the frame to `0x74`; and no speculative
UV setter was introduced because other recovered object paths corroborate
scalar `ObjectUv` component assignments.

## 2026-07-14 generated-mesh and skirt-colour ownership

The allocated generated mesh now flows directly from the typed
`Path::fringe_mesh_bod.object` field without recasting its owner. The skirt
colour borrow reloads the canonical `GameRoot* g_game` and calls the embedded
`subgame`, replacing the equivalent `char* + 0x74618` reconstruction while
preserving the native singleton access. Focused output is byte-identical at
89.31%, 318/318 instructions, prefix 18/318, with all 23 operands clean.

## 2026-07-15 Binary Ninja object-owner replay

The repeatable Binary Ninja path/object replay now installs `Object*` on the
shared `BodBase +0x24` slot and on the object allocation helpers. The tracked
decompile consequently resolves the generated owner as
`self->fringe_mesh_bod.object`, its `ObjectFlag` word and blend mode, the source
bank as `self->bod.object->vertices`, and both allocation calls without the
obsolete 0x60-byte `PathTemplateStripMesh` prefix. The remaining raw offsets
are derived row/face cursor expressions; they do not represent an unresolved
object owner. Focused matching remains byte-identical at 89.31%.

## 2026-07-19 generated-bank lifetime order

The generated vertex bank is now declared before the generated face bank, the
same natural lifetime order already used by `BuildFringeSuperTramp`: vertices
feed the first loop immediately, while faces are retained for the later loop.
That ordinary declaration order lets VC6 keep the generated `Object*` in EBX
through allocation and then hand ESI directly to the vertex walk, matching the
native setup. Focused matching improves from 90.25% to 92.77%, the common
prefix advances from 18 to 100 instructions, and the exact 318-instruction and
23-operand shapes remain intact.

A guarded Binary Ninja replay now names the borrowed generated `Object*`, its
vertex and face banks, and the per-row `Vec3*` clamp cursor in this builder. The
same replay names the SuperTramp builder's generated banks plus both cap
extrapolation and copy lifetimes, all after verifying the canonical `Path`,
`BodBase`, `Object`, `ObjectFaceQuad`, and `Vec3` layouts.

The compiler's interior face-vertex cursor was deliberately left automatic.
Naming that `uint16_t*` made Binary Ninja discard its better shifted
`ObjectFaceQuad` field rendering, so the probe was removed before export. The
remaining interior row/face expressions are borrowed cursors into the two
Object-managed allocations, not evidence for another owner or transfer.

## 2026-07-25 generated row and face-pair cursor ownership

The two native interior cursors are now represented explicitly in the analysis
type layer without changing matching source. The vertex loop carries
`inner_a.z` at `+0x14` inside a four-`Vec3`, `0x30`-byte row; the face loop
carries `first_face.vertex_0` at `+0x02` inside two adjacent
`ObjectFaceQuad`s and advances by the complete `0x60`-byte pair. Both views
borrow their storage from the generated `Object::vertices` and
`Object::facequads` banks.

Binary Ninja and IDA now replay those same offset-pointer layouts and fail
closed on their sizes. The tracked decompiles expose the surrounding row and
both faces rather than anonymous scalar offsets. Matching source and the
focused result remain byte-identical at 92.77%, 318/318 instructions, prefix
100/318, with all 23 masked operands clean.

## 2026-07-29 recorded store-scheduling frontier

Six recorded mutation sweeps evaluate 251 variants (213 unique) around every
remaining mismatch region. None improves the 92.77%, exact
`318/318`-instruction, prefix-100 baseline: 176 variants are byte-identical and
75 degrade. All 23 masked operands remain clean.

- The 15 one-site and 56 paired edge-direction combinations cover
  initialization versus assignment, explicit operator and assignment calls,
  named/const differences, wrapped temporaries, and borrowed row pointers or
  references. Every form is byte-identical. Native still delays publication
  of the x lane across the y-lane x87 store in both vector-return copies.
- Ten first-face index forms cover signed, unsigned, and 16-bit reusable
  bases; shifted and staged bases; named scalar indices; and face
  pointers/references. The four no-base aliases are neutral. Reusable bases
  remove native instructions or perturb the allocation schedule and regress
  as low as 83.41%.
- Sixteen one-site and 64 paired UV-owner forms cover face and UV borrows,
  direct union aliases, named constants, corner pointers, and whole
  `ObjectUv` values. Scalar aliases are neutral; materialized pointer or
  aggregate owners regress. A final 59-variant cross-site sweep combines the
  four neutral index forms with neutral first- and second-face UV forms; all
  index/UV interactions are also neutral.

The retained direct indices and scalar UV assignments agree with the verified
mobile
`cRPath::BuildFringe` geometry and remain the strongest source-backed form.
The residual is bounded to VC6 store scheduling, not missing geometry,
ownership, reference identity, or control flow; no synthetic aggregate,
volatile qualifier, or manual store barrier is retained.

## 2026-09-05 goal-600 source ownership campaign

Direct generated-face indexing raises 92.77% to **99.06%**, with 318/318 instructions and all 23 references clean. `whole-mesh-bank-lifetimes-20260905.json` tests fifteen combinations of row indexing, direct face indexing, mesh-bank lifetime and direction lifetimes. Replacing the borrowed face-pair pointer with `facequads[row * 2]` / `[row * 2 + 1]` recovers the face index and UV store schedule. The retained generated-vertex indexing is score-neutral within the winning combination. No layout or shared operator changes are needed.

Only the two direction-result copy schedules remain different. Four additional whole-direction value forms (component constructor, named components, component stores, copy/subtract) do not improve the new baseline. The earlier description of face-store differences as a compiler residual was too strong: ordinary source ownership repaired them.

The recorded probes describe the tested source forms only; they do not establish exhaustion.
