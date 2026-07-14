# invert_matrix_in_place @ 0x44d280

Exact match: 100.00%, 54/54 instructions.

Copies the destination transform to a stack temporary, transposes the 3x3 basis
into the destination, then rewrites the position as the negative dot product of
the original position against each original basis axis.

The expression order on `position.x` matters for VC6's x87 schedule. The final
source keeps the source-shaped matrix inverse and does not rely on alias tricks.

2026-07-14 return-contract closure:

- iOS `RMaths.o` and both Android libraries preserve the authored
  `tMatrix::Invert()` member name. Both Android callsites discard `r0`, and the
  ARM body returns immediately after its final position store without
  constructing a result.
- The sole Windows caller, `render_object_toon`, also discards EAX. Declaring
  the member `void` and removing the synthetic `return this` remains byte-exact
  at 54/54 instructions, so the receiver value is only incidental ABI state.

2026-07-14 ownership metadata closure: the analysis header and both decompiler
replay scripts now describe the exact source owner as a void `__thiscall`
member. The previous `__fastcall` prototype happened to use the same ECX ABI,
but obscured that mobile preserves this helper as `tMatrix::Invert()`.
