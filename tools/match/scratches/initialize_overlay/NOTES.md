# initialize_overlay @ 0x40a240

Initializes the shared overlay transform state at `0x38`, `0xb8`, and `0x100`.
The rotation starts at zero, advances by `0.00036547193f`, and uses `38.0f` in
the remaining scalar lane at `+0x140`.

Focused match: 100%, 17/17 instructions, with three clean masked operands.
The `Overlay` layout is now shared in `include/overlay.h`.
