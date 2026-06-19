# load_x_animation_clip

Starter semantic scratch for the X animation clip loader.

- `this` is the DirectX/X-loader state used by `initialize_directx_loader`: `animation_bytes` at `+0x00` and `DuplicateVertexBuffer` at `+0x5e08`.
- The per-frame keyframe record is 0x80 bytes. It embeds `BodBase` at `+0x00`, so the loaded frame object pointer is `+0x24`; the parsed frame number is at `+0x7c`, matching `request_object_animation`.
- The missing-script default path is written as `mode_flags = 1`. IDA's `v24 | 1` / BN's `eax_8 | 1` appears to be a register artifact, not a meaningful API value.
