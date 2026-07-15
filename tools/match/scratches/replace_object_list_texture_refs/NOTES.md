# replace_object_list_texture_refs

Object-list texture replacement helper at `0x430d90`.

- Walks the `ObjectList` storage (`count`, `capacity`, `objects`) and skips
  entries whose `Object +0x2c` vertex count is zero.
- Rewrites source facequad texture refs at `ObjectFaceQuad +0x0c`.
- Calls `replace_object_group_texture_refs` so already-built grouped render
  tables at `Object +0xd0` stay consistent with the source facequads.

This helper is currently only reached from `select_level_track_texture_set`,
which swaps both banks of level track texture refs.

## 2026-06-20 source-shape pass

Baseline was `51.85%`, `5/53` prefix, with one clean masked operand. Native
keeps a running byte cursor in `eax`, stores the current byte offset in the
second stack local, and only advances that local at the loop bottom. Rewriting
the scratch to use a separate `object_cursor` byte cursor plus
`object_offset = object_cursor` at the bottom raises the match to `69.16%` and
the prefix to `14/53`.

The typed-array walk `&objects[object_index]` regresses to `47.17%`, so this
helper still looks like original byte-cursor source even though
`add_object_to_list` proves the backing storage is an `Object[]`. A direct
`TextureRef**` slot pointer matches the native inner address form but swaps the
outer zero/count registers and drops to `61.68%`; keep the clearer
`ObjectFaceQuad*` spelling until a stronger object-address ownership lead
appears. A `register Object*` hint was codegen-neutral and is not retained.

## 2026-06-20 object texture-family audit

Rechecking the decompiler-looking single `object_offset += 0xdc` recurrence
regressed to the old `51.85%` shape, and changing only the object pointer
expression from `object_cursor` to `object_offset` also regressed to `51.85%`.
The separate `object_cursor` used for the pointer plus `object_offset` advanced
at the loop bottom is therefore evidence-backed even though it looks redundant.
The remaining residual is still object-address register ownership around
`objects + offset`, not a reason to return to typed `Object[]` indexing.

## 2026-06-20 larger object-texture retry

Focused Wibo still reports `69.16%`, `54/53` candidate/target instructions,
`14/53` prefix, and one clean masked operand. Reversing the byte-pointer
expression to `object_cursor + (char*)objects` and casting the object-list base
through an integer address are both codegen-neutral: VC6 still keeps the object
base in `ecx` instead of native's `add eax, [objects]` cursor shape. Keep the
current byte-cursor source because it preserves the verified loop-bottom
offset recurrence, and treat the object-address register ownership as the next
real residual.

## 2026-06-21 loop-tail schedule pass

Focused Wibo improves to `74.77%`, `54/53` candidate/target instructions,
`14/53` prefix, and one clean masked operand after moving `++object_index`
before the byte-cursor advance at the loop bottom. This matches native's tail
order: reload object index, reload byte offset, reload count, increment the
index, add `0xdc` to the byte offset, compare, then store both locals.

Object-address ownership remains the first mismatch. Spelling the object
address as `(Object*)(object_cursor + (int)objects)`, unsigned variants,
split integer address locals, mutating the cursor through an absolute address,
raw field loads, or a vertex-count pointer are all codegen-neutral once the
tail-order fix is present. They keep `objects` in `ecx` instead of native's
`add eax, [objects]`, so the retained typed byte-cursor source is still the
best evidence-backed shape.

## 2026-07-15 authored owner and void ABI

Android retains this method as `cRObjects::ReTextureObjects`. Its body walks
the owner-provided contiguous object allocation, replaces matching face-quad
texture references, and updates the built grouped-render texture table. The
Android object and face records have port-specific widths, but the same two
container strides are explicit there; the Windows source now derives its
`0xdc` object and `0x30` face advances from `sizeof(Object)` and
`sizeof(ObjectFaceQuad)` instead of duplicating layout constants.

Neither build has a stable result: Windows leaves the final object byte offset
in `eax`, while Android's empty and populated exits preserve unrelated pointer
residue. The sole Windows caller discards the value. The existing void
`ObjectList` method is therefore the authored contract, and the repeatable
Binary Ninja/IDA object-render lanes now replay that receiver and its two
borrowed `TextureRef*` arguments. Focused matching remains honestly partial at
74.77%, 54/53 candidate/target instructions, prefix 14/53, with one clean
masked operand; the residual is still the documented object-address register
allocation.
