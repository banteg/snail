# add_object_to_list

ObjectList allocator at `0x42fad0`.

- Confirms `ObjectList +0x00` is the live count, `+0x04` is capacity, and
  `+0x08` is the backing `Object` array.
- Confirms the object stride is `0xdc`, matching the shared `Object` view in
  `object_render_types.h`.
- Calls `initialize_object` on the selected slot before returning it.

2026-06-20 object-list proof pass: replacing the raw byte-stride expression with
the typed array source idiom `&objects[count++]` makes this proof-grade:
focused Wibo reports 100.00%, 24/24 instructions, prefix 24/24, and three clean
masked operands. The previous raw `(char*)objects + 20 * (11 * count++)`
spelling preserved the same semantics but let VC6 reuse `esi` for the selected
object. The typed array expression naturally keeps `this` in `esi`, saves `edi`
for the returned object pointer, and emits the native `0xdc` stride through the
same scaled `11 * 20` arithmetic. A separate `object_offset` local was
codegen-neutral at the old 73.91%, so the accepted change is the durable
typed-container source shape, not a local scheduling trick.

## 2026-07-18 analyzer ownership closure

Native xrefs show 202 allocator references across eight owning callers,
including the startup asset builder plus the mesh cache, animation loader,
logo, track-fringe, render-cache, and Font3D lanes. The live
Binary Ninja and IDA databases already agree on `ObjectList* -> Object*`, but
the checked-in allocator artifacts were stale raw-pointer views. The canonical
object-render replays now own the three list lifecycle names, the exact 0x0c
global `g_object_list`, and all direct callers so a fresh export cannot regress
to `_DWORD* this`, `unk_4B7648`, or a hand-scaled opaque result. The allocator
remains exact at 24/24 instructions with three clean operands.
