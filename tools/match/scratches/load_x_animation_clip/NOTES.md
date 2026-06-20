# load_x_animation_clip

Starter semantic scratch for the X animation clip loader.

- `this` is the DirectX/X-loader state used by `initialize_directx_loader`: `animation_bytes` at `+0x00` and `DuplicateVertexBuffer` at `+0x5e08`.
- The per-frame keyframe record is 0x80 bytes. It embeds `BodBase` at `+0x00`, so the loaded frame object pointer is `+0x24`; the parsed frame number is at `+0x7c`, matching `request_object_animation`.
- The missing-script default path is written as `mode_flags = 1`. IDA's `v24 | 1` / BN's `eax_8 | 1` appears to be a register artifact, not a meaningful API value.
- 2026-06-20 reference audit: the X mesh enumeration output buffer is now
  curated as `g_x_animation_clip_enumeration_names` at `0x4b2f50` with
  `data_4b2f50` retained as an alias. Focused Wibo remains `69.32%`,
  `225/228`, `3/228` prefix, but the masked audit improves from
  `42 ok / 3 unresolved` to `45 ok / 0 unresolved`.
