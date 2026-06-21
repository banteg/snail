# `load_x_mesh` reconstruction notes

Semantic starter for `DirectXLoader::load_x_mesh` at `0x405640`.

Focused Wibo result after the material-cursor split: 46.74%, 475 candidate
instructions versus 492 target instructions, with 67 masked operands OK and no
unresolved masks.

The function loads `X/<mesh>` or `X/<mesh>2` from the archive buffer, parses the
`Frame`, `Mesh`, `MeshTextureCoords`, and `MeshMaterialList` blocks, allocates
object vertices/facequads, copies UVs, installs a temporary
`X/snail-turbo.tga` texture, and then replaces face textures from the material
index table.

Notable shape details:

- IDA reports this as a free `__stdcall`, but existing callsites and the
  `initialize_directx_loader` layout make it a `DirectXLoader` member.
- The third parameter is an option flag; bit `2` suppresses missing texture
  warnings and sets material texture flag byte 1 bit `0x80`.
- The decompile allocates `"Mesh vertex remap"` but only frees it in this path.
- The native return value is incidental: errors return `report_errorf`, while
  the success path returns after freeing the material list.
- Keeping separate early/later material cursors is important. Reusing one
  cursor collapses a native stack slot and drops the scratch to 21.92%.

2026-06-21 mesh-path branch pass:

- Focused Wibo improves from 46.74% to 63.36%, with 477 candidate instructions
  versus 492 target instructions, a 43-instruction prefix, and 91 clean masked
  operands with no mismatches.
- Rewriting the initial archive-index/path-suffix choice as a nested
  `is_archive_index_loaded() != 0` branch recovers the native common
  `mesh_path` argument setup around the inlined `strlen` scan. This also
  removes the previous four masked mismatches, which were caused by the old
  two-`sprintf` shape shifting later string/function relocations.
- A single conditional-format `sprintf` call improved the score to 62.38% and
  cleared the masked mismatches, but kept only a 10-instruction prefix because
  VC6 selected the format through a register instead of the native branchy
  setup. The retained nested spelling keeps the same semantics and gives the
  better native prefix.
- A `register` hint on `frame_cursor` was codegen-neutral at 63.36%; the next
  residual is still frame cursor ownership (`edi` native versus `ebp`
  candidate), not the mesh-path branch.
