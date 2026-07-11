# update_overlay @ 0x40a1b0

Advances the embedded camera's overlay rotation alias by the final
`Overlay::rotation_step`, wraps it into the `0..2*pi` range, rebuilds the
parent renderable transform around z, copies that transform into the embedded
camera, and rebuilds the camera view matrix.

Focused match: 100%, 42/42 instructions, with seven clean masked operands. The
upper wrap is strict (`rotation_angle > 2*pi`), which matches the native
`test ah, 0x41` compare. The `Overlay` layout is shared with
`initialize_overlay` in `include/overlay.h`. The constructor and root viewport
bindings independently prove that the `+0x80..+0x147` region is an owned
`RenderCamera`, not three unrelated matrices and scalar fields.
