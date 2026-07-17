# mirror_path_template_pair_x reconstruction notes

`mirror_path_template_pair_x` builds the mirrored half of an attachment path
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
- `finalize_path_template` is fastcall/this-shaped here; the non-void return
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
