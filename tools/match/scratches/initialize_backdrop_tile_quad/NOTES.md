# initialize_backdrop_tile_quad reconstruction notes

`initialize_backdrop_tile_quad` builds one oriented textured backdrop tile quad.
It requests four vertices and one facequad, assigns the fixed tile UV window,
rotates that UV window according to the orientation, writes the oriented
quad-local X/Z coordinates, then applies an edge-selector pass over all four
vertices.

Important type notes:

- The function is a cdecl helper:
  `void initialize_backdrop_tile_quad(Object*, int edge_selector, int orientation,
  int row_selector, int column_selector, char* texture_path)`.
- Binary Ninja's apparent float return is stale x87/register state; the caller
  discards it and fixes the stack by `0x18`.
- `rotate_object_facequad_uv_pairs @ 0x430a30` is a recovered
  fastcall/thiscall-shaped helper over `ObjectFaceQuad` that rotates the four
  UV pairs. The standalone helper scratch matches 100.00%.

Current focused result:

- match: 100.00%
- target/candidate instructions: 367 / 367
- prefix: 367 / 367
- masked operands: 63 clean, 0 unresolved, 0 mismatched

Remaining gap:

The scratch matches the setup prefix and preserves the orientation/edge-selector
structure, but it is still a high mid-progress reconstruction. The recovered
UV-rotation helper clears the six former unresolved call operands, and the
orientation jump table at `0x41a581` / `0x41a9fc` is now curated as
`initialize_backdrop_tile_quad_orientation_jump_table`. Its target/candidate
entries remain a real audited mismatch. The main code-shape differences are
register choice for the negative X/Z constants in the orientation cases and
shorter edge-selector blocks where MSVC still simplifies some repeated sign
tests.

2026-06-20 orientation lane correction: case 2 now writes vertex 2's z lane as
`-0.5f`, matching both the target stores and the IDA/BN decompilers. The prior
scratch used `-0.89999998f`, which was a real transcription error rather than
register noise. Focused Wibo improves from `79.32%` to `83.00%`, and the exact
prefix advances from `91/367` to `122/367`; the remaining masked mismatch is
still only the curated orientation jump-table label.

2026-06-21 edge shrink shape pass: precomputing `edge_selector - 1` as the
switch key gives VC6 the native `esi` switch index / `edi` vertex counter split.
The shrink macro then needs a volatile first reload plus a zero-check temporary;
that prevents VC6 from reusing the outer sign predicates and restores the full
native inlined sign test. Focused Wibo now has a 100.00% normalized instruction
stream, 367/367 instructions, and a 367/367 prefix. The newly exposed
edge-selector jump table at `0x41aa0c` now has a curated reference and audits
cleanly.

2026-06-21 adjacent jump-table audit: the orientation table at `0x41a9fc` is
immediately followed by the edge-selector table at `0x41aa0c`, so the local
candidate label scan originally over-read both tables as one 11-entry table.
Adding `$L1028` as the candidate alias and teaching the matcher to honor curated
jump-table sizes for local labels clears the masked audit. Focused Wibo is now
proof-grade: 100.00%, 367/367 instructions, a 367/367 prefix, and 63 clean
masked operands.

2026-07-11 local-label refresh: subsequent source cleanup renumbered the same
bounded orientation and edge-selector tables to `$L1047` and `$L1048`.
Registering those compiler-local aliases restores the content audit without
changing source or accepting label identity as proof. Focused Wibo is again
proof-grade at 100.00%, 367/367, prefix 367/367, with 63 clean operands.
