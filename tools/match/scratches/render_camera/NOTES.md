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

## Fog spill win (2026-06-21)

Declaring both fog range values as `volatile int` locals forces the native stack
spills for render states 36 and 37, removes the candidate-only `edi`/`ebp`
saves in the fog branch, and fixes the local frame from `0xc4` to `0xc8`.
Focused match rises from 70.17% to 97.78%, with 180/180 instructions, a 116/180
prefix, and 37 clean masked operands.

Both fog values must be stack-forced. Only one volatile local keeps the old
frame and regresses to the mid-60s, reloading the globals at the render-state
calls reaches only 75.42%, and moving `fog_end` after state 28 disrupts the
branch body. A volatile two-element array ties the score but is less faithful
to the scalar source. The remaining residual is just fog-branch scheduling:
native delays the second spill until after the state-28 call setup and loads the
device vtable after pushing state/value for states 36 and 37.
