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

Proof status:

The setup, orientation, edge-selector, UV rotation, and all repeated sign tests
now reproduce the native 367-instruction stream. The adjacent compiler tables
are accepted only through their bounded four- and seven-entry relocation
contents. Historical recovery steps below explain how the earlier mismatch was
closed.

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

2026-07-11 star-manager header refresh: the new inline vector operator shifts
the two local labels once more to `$L1051`/`$L1052`. COFF places the four-entry
orientation table at object `+0x52c` and the seven-entry edge-selector table at
`+0x53c`; their relocation sequences are unchanged. Registering these aliases
restores bounded content auditing without changing the exact source stream.
The paired vector-add operator advances the current labels to
`$L1055`/`$L1056` at those same offsets, again with unchanged bounded contents.

2026-07-11 frame-renderer header refresh: promoting the shared sprite depth
workspace advances the same two compiler-local labels to `$L1074`/`$L1075`.
COFF still places the tables at object `+0x52c`/`+0x53c`; all four orientation
destinations and all seven edge-selector destinations remain identical to the
curated target tables. The new aliases therefore preserve content auditing
without changing either exact source stream.

2026-07-11 shared-device header refresh: expanding the common IDirect3DDevice8
vtable advances the same bounded tables to `$L1140`/`$L1141`. COFF still places
the four-entry orientation table at object `+0x52c` and the seven-entry
edge-selector table at `+0x53c`. Their contents match the tracked `0x10`/`0x1c`
target ranges exactly, restoring 367/367 proof with 63 clean operands.
