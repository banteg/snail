# `render_camera` recovery notes

Target: `render_camera @ 0x411fa0` (`cdecl`, 685 bytes, 180 instructions).

This scratch reconstructs the renderer camera setup helper called twice by
`render_game_frame`. BN callsites confirm the source-level signature is the
plain nine-argument cdecl form:

- viewport x/y and width/height fractions;
- FOV in degrees;
- source camera matrix;
- active view matrix pointer;
- fog/world flag;
- post-sprite object pass flag.

IDA's older `esi` usercall view is an artifact: the native body loads the
source camera matrix from the sixth stack argument into `esi` after setting the
projection transform.

## Recovered behavior

- Converts viewport x/y and scaled width/height into a D3D viewport and calls
  device vtable slot `+0xa0`.
- Stores near/far/FOV/aspect projection globals, builds the projection matrix,
  and installs it as Direct3D transform state `3`.
- Stores `g_object_render_pass_filter` from the post-sprite flag.
- Builds eye/target/up vectors from the source transform at `+0x30`, `+0x20`,
  and `+0x10`, then calls `build_camera_view_matrix` and installs transform
  state `2`.
- Enables the depth/render-state trio `7=1`, `14=1`, and `23=4`.
- Enables fog only when the caller's draw-world flag and
  `GameRoot::fog_enabled` are set. The root-owned start/end/density floats feed
  render states `36/37/38`; its fog color is packed through
  `ColorBGRA8::pack_color_rgba_u8`, then alpha is forced to zero before render
  state `34`.
- Stores the active camera source matrix at `g_render_camera_source_matrix`,
  stores the active view matrix pointer at the newly named
  `g_render_camera_view_matrix`, and clears `g_current_texture_ref`.

## Exact fog ownership and source shape (2026-07-10)

The write-side game initializer proves `GameRoot +0x04..+0x23` is an embedded
fog-settings block: enabled byte, start/end/density floats, and `Color4f`.
Direct3D render states 36 and 37 consume the raw DWORD encodings of local float
copies of `fog_start` and `fog_end`. Spelling that standard D3D address-taking
idiom naturally produces the native stack frame and scheduling.

Focused Wibo is now exact: 100.00%, 180/180 instructions, full 180-instruction
prefix, and 37 clean masked operands. The earlier 97.78% scratch used
`volatile int` solely to force those spills; that compiler coercion has been
retired rather than treated as a legitimate match. The exact source also
confirms `RenderCamera +0xc0` is the float FOV in degrees, not an integer camera
mode.
