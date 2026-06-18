# update_overlay @ 0x40a1b0

Advances the overlay rotation angle by the initialized step, wraps it into the
`0..2*pi` range, rebuilds the screen matrix around z, copies that matrix into
the world slot, and rebuilds the inverse screen matrix.

Focused match: 100%, 42/42 instructions, with seven clean masked operands. The
upper wrap is strict (`rotation_angle > 2*pi`), which matches the native
`test ah, 0x41` compare. The `Overlay` layout is shared with
`initialize_overlay` in `include/overlay.h`.
