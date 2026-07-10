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

2026-07-10 object and authored-width ownership:

- `load_x_mesh` now accepts the proven `Object*` owner in both loader class
  views instead of a `void*` plus scratch-local cast. The animation loader,
  exact cached-mesh loader, and raw game-asset callers all preserve their
  codegen with the typed contract.
- Parsed vertex and facequad counts are authored 16-bit values. Keeping them as
  `short` locals delays native's sign extension until each Object allocation
  or loop use and raises focused Wibo from 63.36% to 66.26%.
- The native Windows loader really does allocate and free the `Mesh vertex
  remap` buffer without populating or reading it. Cross-checking Binary Ninja
  and IDA rejected the tempting but false missing-remap hypothesis; the dead
  allocation remains explicit rather than inventing semantics.

2026-07-10 face-array ownership:

- Native keeps the face index/byte offset and reloads the Object-owned
  `facequads` base for each field. Removing the cached `ObjectFaceQuad*` and
  spelling owner-relative writes directly raises the match to 77.76%.
- Each face begins with a full `header_word = 0`, clearing both primary and
  secondary flag bytes. The old low-byte-only clear was semantically wrong;
  correcting it raises the match to 77.96% and promotes the union member into
  the shared C analysis headers.
- U and V are copied as eight scalar component assignments, not four
  `ObjectUv` struct assignments. This reproduces native's owner reloads and
  reaches a 492/492 instruction shape at 79.47%.
- Material-face indices are truncated to signed 16-bit values before indexing
  the temporary `TextureRef**` table. Resolving that pointer in a temporary
  before assigning the Object-owned face slot matches the native evaluation
  order and yields 80.20% (493/492 instructions, 46/492 prefix, 93 clean
  masks, no unresolved operands or mismatches).

Rejected probes: an explicit working face-count alias is codegen-neutral; an
advancing material-slot pointer regresses to 73.39% by disturbing unrelated
stack ownership; storing the parsed material index as a standalone `short` or
casting it inline reaches only 79.39% because VC6 schedules the destination
owner first. None are retained. The remaining residuals are honest local-slot
and register-lifetime differences, not missing mesh ownership.
