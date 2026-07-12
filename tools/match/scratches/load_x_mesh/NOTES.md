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
- The native exit register is incidental: error paths leave `report_errorf`
  and the success path leaves `free_tracked_memory` in `eax`; the void ABI
  closure below proves neither is an authored result.
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
  the temporary `TextureRef**` table. At this stage of the ownership recovery,
  resolving that pointer in a temporary before assigning the Object-owned face
  slot produced the closer evaluation order and yielded 80.20% (493/492
  instructions, 46/492 prefix, 93 clean masks, no unresolved operands or
  mismatches).

2026-07-12 parser and material-slot lifetimes:

- Native preserves the raw `parse_next_signed_int` return for the authored
  vertex count, then sign-extends its low 16 bits into the working count. The
  Android sibling independently exposes the same `Rstrint(...) << 16` / signed
  high-half lifetime. Keeping both values and consuming the working count in
  the vertex pass raises focused Wibo from 80.20% to 81.54%.
- The material loop owns two distinct pieces of state: a zero-based material
  index and an advancing `TextureRef**` slot. Crucially, the slot does not
  become live until after the native `material_count > 0` guard. Binding it
  inside that guarded scope recovers the Windows register and stack schedule,
  taking the scratch from 83.52% to 95.54%.
- Assigning the final material-table lookup directly into the Object-owned face
  slot restores native right-hand-side evaluation and reaches 96.75% (494/492
  instructions, 238/492 prefix, 94 clean masks, no unresolved operands or
  mismatches).
- The sole instruction-count residual is the non-quad flag update: the target
  emits one direct byte `or`, while VC6 expands the typed field spelling into a
  byte load/`or`/store. Pointer and raw-byte probes perturb the otherwise native
  owner/register schedule, so the typed `ObjectFaceQuad::flags` update remains
  rather than forcing an artificial exact match.

Rejected probes: moving the parser locals into broad function-level scopes is
codegen-neutral; making the material-slot pointer live before the empty-list
guard loses the native index ownership; storing the parsed material index as a
standalone `short` changes the final assignment schedule; and an explicit
pointer to the face flag byte regresses the broader face-loop register
allocation. None are retained.

## 2026-07-12 DirectX loader ABI and owner closure

- Every native caller supplies the root-owned loader in `ecx` and an owned
  `Object*`, and none consumes `eax`. The cross-port method is
  `cRDirectX::LoadX(char*, cRObject*, unsigned char)`, so the stale free
  `__stdcall`/integer-result prototype is retired in favor of a void thiscall.
- `DirectXLoader` is now explicit in the shared BN/IDA object-analysis slice:
  animation bytes at `+0x00`, cache count at `+0x04`, 128 exact `0xbc` cached
  Bod/Object slots at `+0x08`, and the duplicate-vertex workspace at `+0x5e08`,
  closing the owner at `0x5e10`.
- The void correction preserves focused Wibo at `96.75%`, `494/492`, prefix
  `238`, with all 94 masked operands clean. Exact `initialize_directx_loader`,
  `load_or_reuse_cached_x_mesh`, and `load_x_animation_clip` also remain exact,
  proving the corrected family contract without match-only control flow.
