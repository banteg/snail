# add_object_to_list

ObjectList allocator at `0x42fad0`.

- Confirms `ObjectList +0x00` is the live count, `+0x04` is capacity, and
  `+0x08` is the backing `Object` array.
- Confirms the object stride is `0xdc`, matching the shared `Object` view in
  `object_render_types.h`.
- Calls `initialize_object` on the selected slot before returning it.
