# load_object_definition

`load_object_definition @ 0x44c420` parses an authored object directory's
`_Object.txt` file. It uses the shared archive data buffer, loads
`%s/_Object.txt`, terminates the text two bytes before the loaded size, then
walks line-by-line through the supported sections.

Recovered structure:

- `[VERTEX START]` is counted first, then `request_object_vertices` allocates
  the object vertex array and indexed `x/y/z` lines populate
  `Object::vertices`.
- `[FACEQUAD START]` is counted first, then `request_object_facequads`
  allocates indexed facequad records.
- Both section counters are initialized once before the parser loop. Repeated
  section markers therefore continue the running counts rather than resetting
  a block-local count.
- Each facequad line has the face index, four vertex indices, eight UV floats,
  and a texture token. The loader appends `.tga`, builds `path/token.tga`,
  resolves it through `g_texture_refs.get_or_create_texture_ref`, and clears
  the facequad's first 16-bit flags/unknown word before writing indices and UVs.
- Lines starting with `*` are comments skipped by a hand-written newline scan,
  matching the native special case rather than the general line skipper helper.

Focused matcher result: **100.00%**, 316/316 instructions with a full exact
prefix. The masked audit resolves all 59 operands with zero mismatches.

The exact scratch retains the native `0x23c` frame, including the observed
`byte_count`, texture-name, texture-path, and object-path slots. Vertex and
facequad running counts occupy the native `+0x20` and `+0x24` function-lifetime
slots without padding or synthetic aliases.

Measured probes:

- Inverting the outer comment-line branch to keep the non-comment path inline
  improved the scratch from 44.44% to 44.80%.
- A `register` object pointer alias and then removing the alias were both
  score-neutral at 44.80%, so the simpler direct parameter use was retained.
- 2026-06-21 frame-slot pass: making only `facequad_count` block-scoped while
  leaving `vertex_count` function-scoped improves focused Wibo to 48.23%, with
  297 candidate instructions versus 325 target instructions. This recovers the
  native `0x23c` stack frame and gives a 2-instruction prefix instead of the
  old `0x240` frame with zero prefix.
- Making both counters block-scoped overcorrected the frame to `0x238` and
  regressed to 42.65%. Keeping only `facequad_count` function-scoped also
  matched the frame but scored lower at 47.27%. A `register` hint on the
  retained block-local `facequad_count` was neutral at 48.23%.
- The next residual is early callee-saved register ownership: native saves
  `ebp` immediately after `ebx`, while the retained one-counter shape delays
  the `ebp` save until the parser loop. The masked mismatches are still
  alignment fallout between the vertex and facequad regions, not unresolved
  symbols.

2026-07-10 owner-chain consolidation: this loader now sits on the shared
`ObjectList -> Object` lifecycle. Its `Object*` argument is a borrowed global
list slot; the loader installs the slot's owned vertex and facequad arrays,
while each facequad borrows a `TextureRef*` from the texture manager. The
canonical Binary Ninja/IDA header carries the two-argument declaration. The
live Binary Ninja function retains a stale `int32_t()` user type that rejects
both normal and direct type updates, so the sync deliberately reports that
tool limitation instead of claiming the live prototype was applied. Focused
Wibo remains 48.23%, 297/325, prefix 2/325, with 36 clean and five
alignment-dependent masked mismatches.

A whole-`Vector3` parsed-vertex temporary was rejected: it regressed focused
Wibo to 33.44% and enlarged the frame to `0x248`. The retained three-float
staging plus direct access to the object-owned destination array is clearer
about the destination slot and preserves the native `0x23c` frame.

2026-07-12 array/cursor ownership pass: disassembly shows that native never
caches either destination element. It reloads `Object::vertices` for each
coordinate store and `Object::facequads` for the texture, header/index, and UV
stores, so the scratch now expresses those accesses directly instead of
inventing borrowed element aliases. The first face word is also written through
the recovered `header_word` field rather than an untyped cast.

The same audit recovered one function-lifetime secondary cursor shared by the
vertex counter, vertex parser, facequad counter, and facequad parser. Together
with the function-lifetime `byte_count`, that reuse produces the native
`0x23c` frame and exact buffer offsets. Before the count-declaration correction,
the 51.33% result was lower than the semantic similarity of the two listings
because the swapped count spill slots and block layout disrupted sequence
alignment; no dummy locals, volatile qualifiers, or synthetic pointer aliases
were introduced to conceal that residual.

2026-07-12 counter order and void ownership closure:

- Declaring the vertex count before the facequad count recovers the native
  spill ownership exactly: vertex count at `esp+0x20`, facequad count at
  `esp+0x24`. This simple lifetime correction raises the focused match from
  51.33% to 54.77%, extends the exact prefix from 27 to 30 instructions, and
  improves the masked audit from 33 clean / 14 mismatched to 36 clean / 12
  alignment-dependent mismatches, while retaining the exact `0x23c` frame.
- The expanded Android and iOS corpora preserve the real global owner as
  `ObjectTextLoad(char*, cRObject*)`. Both mobile epilogues return without an
  authored result, while every Windows caller discards `eax`. The Windows cdecl
  helper is therefore a void load into the borrowed `Object*`; the final text
  cursor left in `eax` is incidental. Promoting the checked-in declarations and
  scratch to `void` is codegen-neutral at the retained 54.77% score.
- A previewed live Binary Ninja prototype update still read back as the stale
  `int32_t()` and was reverted by the bridge. The checked-in Binary Ninja
  header now carries the correct void declaration, but the repeatable sync
  continues to report this one resistant user-type defect rather than claiming
  a live mutation succeeded. The headless IDA sync accepted and verified the
  same void declaration with no missing or failed updates.

2026-07-14 parser-dispatch closure:

- The prior scratch incorrectly placed one unconditional
  `skip_to_next_line(&cursor)` after the bracket dispatch. Native has three
  semantic call sites instead: non-`[` lines, the completed vertex section,
  and the completed facequad section. An unrecognized `[` line falls directly
  to the outer termination test without advancing.
- Expressing those distinct parser paths lets VC6 tail-merge the real helper
  calls exactly. In particular, the vertex path prepares its cursor argument
  and jumps into the shared call tail, while the non-bracket and facequad paths
  share the other entry. The formerly misplaced comment block also moves after
  the epilogue and jumps back to the common termination test.
- This semantic control-flow correction raises the focused result from 55.56%
  (314/316, 30-instruction prefix, 36 clean and 12 mismatched operands) to
  100.00% (316/316, full prefix, all 59 operands clean). No register hints,
  volatile barriers, dummy locals, or byte-shaped fakematch were used.

2026-07-23 live ownership closure:

- Explicit function reanalysis in the shared Binary Ninja mutation path clears
  the formerly resistant user type. The live database now retains and
  independently reads back the authored
  `void load_object_definition(char* path, Object* object)` ABI after unrelated
  local mutations and after a second replay.
- The exact native frame proves three disjoint automatic arrays:
  `object_file_path[0x100]` at `-0x100`, `texture_path[0x80]` at `-0x180`, and
  `texture_name[0x80]` at `-0x200`. The adjacent `byte_count` at `-0x204` is
  the archive loader's out parameter. These are real source objects already
  present in the exact scratch, not overlays introduced to improve HLIL.
- The stack pointer at `-0x238` is the consuming outer `cursor`; the pointer at
  `-0x23c` is the borrowed `line_cursor` copy used to count or parse a section
  without consuming the outer traversal. Naming both lifetimes makes the two
  parser roles explicit without splitting or merging native storage.
- Ownership is now visible end to end: `path` and `object` are borrowed
  parameters; the shared archive byte bank is borrowed for the duration of the
  parse; both cursors are borrowed interior views; the loader installs owned
  vertex and facequad banks on `object`; and each facequad borrows its resolved
  `TextureRef*` from `g_texture_refs`.
- `sync_object_render_types.py` carries the canonical ABI, while
  `sync_object_loader_lifetimes.py` verifies the `Object`/`ObjectFaceQuad`/`Vec3`
  layouts and replays only these six proven frame owners. A second lifetime
  replay skips every mutation as already current.

## 2026-07-24 paired IDA loader replay

The IDA object-render replay now includes this exact 316/316 loader in its
trusted name and explicit reanalysis set. It also durably replays the same six
proven frame owners as Binary Ninja: the consuming `cursor`, borrowed
`line_cursor`, `byte_count`, `texture_name[0x80]`, `texture_path[0x80]`, and
`object_file_path[0x100]`.

The refreshed IDA artifact now exposes the authored void cdecl ABI, installs
vertices and facequads through the canonical borrowed `Object*`, and resolves
textures through the shared registry. This replaces the stale `char*`/`int*`
parameters and incidental return without changing the exact matcher source.

## 2026-07-27 mobile owner correction

The expanded Android and iOS decompile corpora disambiguate two previously
conflated loaders:

- `ObjectTextLoad(char*, cRObject*)` is the direct cross-port counterpart of
  Windows `load_object_definition`. All three load `%s/_Object.txt`, parse the
  same `[VERTEX START]` and `[FACEQUAD START]` sections through the RText helper
  family, allocate geometry on the borrowed object, and resolve texture paths.
- `cRObject::Load(char*)` is a different, much larger binary object loader. It
  consumes typed binary records, installs animation and render buffers, and
  does not parse `_Object.txt`.

In both mobile link layouts, `ObjectTextLoad` follows the ObjectProc function
family and precedes the next source family, recovering `ObjectProc.o` ownership.
The verified crosswalk and gameplay alias now record the global
`ObjectTextLoad` identity; no Windows code or ABI changed.
