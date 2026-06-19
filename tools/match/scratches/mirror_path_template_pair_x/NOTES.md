# mirror_path_template_pair_x reconstruction notes

`mirror_path_template_pair_x` builds the mirrored half of an attachment path
template from an authored source half. It copies the source template metadata,
allocates matching samples, mirrors X-space sample transforms and deltas,
requests a destination strip mesh, mirrors strip vertices, copies optional
vertex colours, flips face winding/UV U coordinates, then finalizes the path
template.

Current focused result:

- match: 79.17%
- target/candidate instructions: 314 / 310
- prefix: 31 / 314
- masked operands: 15 clean, 0 unresolved, 0 mismatched

Important shape notes:

- `segment_count` and `width_cells` stay as signed fields; the loops use the
  native `> 0`, `>= 0`, and `<`/`<=` signed comparisons.
- The 0x40 sample transform copies and 0x30 face copies are aggregate
  assignments, which MSVC lowers to the expected `rep movsd` blocks.
- The scalar sample fields before the transform copy are real source stores,
  not artifacts. The transform copy only covers the first 0x40 bytes.
- Transform and delta X components use multiply-by-`-1.0f`, while the direct
  copied scalar/vertex X values use `fchs`.
- `finalize_path_template` is fastcall/this-shaped here; the non-void return
  observed by decompilers is stale register state.

Remaining gap:

The scratch is behaviorally complete, but the sample loop still differs in
equivalent SIB operand ordering (`base + index` vs `index + base`) and in a few
scheduler choices around the secondary sample X negation. The face loop also
has minor scheduling differences in the vertex/UV swaps. Those are left visible
rather than forcing the source with non-semantic clutter.
