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
- Enables fog only when the caller's draw-world flag and game fog flag are set.
  The fog color is packed through `ColorBGRA8::pack_color_rgba_u8`, then alpha
  is forced to zero before render state `34`.
- Stores the active camera source matrix at `g_render_camera_source_matrix`,
  stores the active view matrix pointer at the newly named
  `g_render_camera_view_matrix`, and clears `g_current_texture_ref`.

## Current match

Focused matcher result: 70.17%, 182 candidate instructions versus 180 target
instructions, 0-instruction prefix, 34 clean masked operands, no unresolved
operands, and one masked constant mismatch in the viewport scaling prologue.

The first mismatch is the stack frame:

```text
target:    sub esp, 0xc8
candidate: sub esp, 0xc4
```

Most later local offsets are shifted by four bytes. The candidate also preserves
fog start/end in `edi`/`ebp`, while native spills those values into existing
stack locals and keeps only `esi` saved for the camera matrix.

## Rejected trial

Declaring fog start as a float and passing its raw bits did move one fog value
to the stack, but it regressed the result to 66.85% and introduced call/global
operand mismatches around `pack_color_rgba_u8`. The retained scratch keeps the
cleaner integer render-state values.
