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
