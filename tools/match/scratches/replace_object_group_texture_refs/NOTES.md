# replace_object_group_texture_refs

Small grouped-render helper at `0x4145c0`. When an object already owns grouped
render buffers (`OBJECT_FLAG_RENDER_BUFFERS_READY`), it scans `Object +0xd0`
and replaces any group texture entry matching the old `TextureRef`.

This is only called by `replace_object_list_texture_refs`, after that caller has
also rewritten the source facequad texture refs.

## 2026-07-23 grouped texture ownership closure

The canonical object replay now carries the exact cdecl signature
`(Object*, TextureRef*, TextureRef*)` into Binary Ninja. A bounded companion
replay preserves the `Object*` receiver, integer group index, retained
`TextureRef**` bank, current entry, replacement entry, and slot lifetimes after
verifying `Object::flags`, `texture_group_count`, and `group_texture_refs`.

The tracked decompile now expresses the whole operation as indexed replacement
through `object->group_texture_refs`; the old raw `arg1 + 0xd0` and integer
texture identities are gone. Preview/apply readback verified all seven callee
lifetimes, and the second replay skipped the prototype and every lifetime as
already current.

No matcher source changed. Focused output remains exact at `100.00%`, `26/26`
instructions, prefix `26/26`, with no masked operands.
