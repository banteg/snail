# build_track_fringe_mesh reconstruction notes

`build_track_fringe_mesh` creates the generated side/fringe strip mesh for an
attachment path template. It allocates an `Object` into the template's second
`BodBase` slot at `+0x60`, copies the current track skirt colour into that BOD,
requests four vertices and two facequads per segment, extrudes the outer edge by
0.4 units along the normalized edge direction, optionally clamps X by side, and
builds the two textured facequads for each segment.

The generated mesh raises `OBJECT_FLAG_DISABLE_CULLING`; the remaining low
`0x40` tint bit is still numeric because its ownership has not closed.

Current focused result:

- match: 89.31%
- target/candidate instructions: 318 / 318
- prefix: 18 / 318
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

The remaining gap is now register and store scheduling. The exact `0x68` stack
frame, row-centered generated-vertex cursor, vector temporary family, face-loop
instruction count, and near/far source-column ownership are recovered. Native
keeps the generated `Object` in `ebx` during setup where the current candidate
uses `esi`, and schedules a few vector-result and face index/UV stores
differently.

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
