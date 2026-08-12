# mirror_path reconstruction notes

`mirror_path` builds the mirrored half of an attachment path
template from an authored source half. It copies the source template metadata,
allocates matching samples, mirrors X-space sample transforms and deltas,
requests a destination strip mesh, mirrors strip vertices, copies optional
vertex colours, flips face winding/UV U coordinates, then finalizes the path
template.

The optional colour copy is governed by shared
`OBJECT_FLAG_USE_VERTEX_COLOURS`; the old path-local flag name duplicated the
generic `Object` owner used by the grouped-vertex builder.

Current focused result:

- match: 97.45%
- target/candidate instructions: 314 / 314
- prefix: 273 / 314
- masked operands: 15 clean, 0 unresolved, 0 mismatched

Important shape notes:

- `segment_count` and `width_cells` stay as signed fields; the loops use the
  native `> 0`, `>= 0`, and `<`/`<=` signed comparisons.
- The 0x40 sample transform copies and 0x30 face copies are aggregate
  assignments, which MSVC lowers to the expected `rep movsd` blocks.
- `primary_samples[sample_index]` and `secondary_samples[sample_index]` are
  owned typed arrays. Natural array indexing lets MSVC recover the native
  count and strength-reduced 0xa8-byte induction variables; keeping the loop
  increment at the source-level loop bottom raises the exact prefix from 31 to
  273 instructions.
- The iOS `cRPath::Mirror(cRPath*)` implementation independently confirms the
  typed sample-array walk and aggregate 0x40 transform copies. Its platform
  implementation stops before the Windows-only strip-mesh mirroring work.
- `strip_mesh` is the shared borrowed `Object*` owner. The scratch-local 0x60
  mesh overlay duplicated the already recovered `Object::flags`, `vertices`,
  `vertex_colours`, and `facequads` fields and is no longer needed.
- The scalar sample fields before the transform copy are real source stores,
  not artifacts. The transform copy only covers the first 0x40 bytes.
- Transform and delta X components use multiply-by-`-1.0f`, while the direct
  copied scalar/vertex X values use `fchs`.
- `calc_path_length_z` is fastcall/this-shaped here; the non-void return
  observed by decompilers is stale register state.

Remaining gap:

The scratch is behaviorally complete and the first 273 target instructions are
exact. The remaining face-loop instructions differ only in independent
vertex/UV swap scheduling: the target keeps both UV values on the x87 stack,
while this equivalent candidate moves one value through a general register.
Separate UV temporary names are codegen-neutral; explicitly loading both sides
produces the target x87 operation forms but regresses scheduling. The natural
one-temporary swaps are retained rather than forcing instruction order with
non-semantic clutter.

## 2026-07-17 Path ABI closure

The guarded Binary Ninja replay now gives both parameters the full `Path*`
owner and records the method as void, matching `cRPath::Mirror(cRPath*)` and
the Windows callers that discard tail register state. This removes the stale
partial `PathTemplate*` identity without perturbing the accepted source:
focused matching remains 97.45%, 314/314 instructions, with a 273-instruction
exact prefix and all 15 masked operands clean.

Android and iOS independently preserve the exact authored
`cRPath::Mirror(cRPath*)` symbol. Their implementations confirm the sample
array ownership and stop after `CalcLengthZ()`; Windows additionally mirrors
the strip mesh and flips its face winding. The authored name is therefore
high-confidence while the platform body difference remains explicit.

## 2026-07-27 face-pair ownership closure

The Windows-only strip-mesh tail is now exact. Each copied
`ObjectFaceQuad` owns two independent operations:

- exchange the two vertex-index pairs to reverse winding; and
- exchange the U components within the corresponding two UV pairs.

Keeping those exchanges as small typed helpers preserves the alias boundary
between each complete pair. VC6 consequently finishes the first vertex pair
before loading the second, and keeps both float values live on the x87 stack
for each U exchange. This is the natural aggregate-member source shape behind
the native schedule; it introduces no volatile state, dummy work, or synthetic
data.

Focused matching improves from **97.45%** to **100.00%**: 314/314
instructions, a 314-instruction exact prefix, and all 15 masked operands clean.
Together with the independently named Android and iOS bodies, this closes the
shared `cRPath::Mirror(cRPath*)` owner while retaining the explicit fact that
only Windows mirrors the generated strip mesh.

## 2026-08-12 authored method surface

The live Windows function is a 1058-byte void thiscall with typed `cRPath*`
receiver and source parameters. Binary Ninja records 60 direct calls from the
asset initializer; every call passes one path-pair secondary as the receiver
and its authored primary half as the source. Together with the independently
named Android and iOS `cRPath::Mirror(cRPath*)` bodies, this anchors the exact
`cRPath::Mirror` spelling throughout the Windows source. The stable
`mirror_path` name remains only the address-keyed scratch identity.
