# update_overlay @ 0x40a1b0

Advances the embedded camera's overlay rotation alias by the final
`cROverlay::rotation_step`, wraps it into the `0..2*pi` range, rebuilds the
parent renderable transform around z, copies that transform into the embedded
camera, and rebuilds the camera view matrix.

Focused match: 100%, 42/42 instructions, with seven clean masked operands. The
upper wrap is strict (`rotation_angle > 2*pi`), which matches the native
`test ah, 0x41` compare. The `Overlay` layout is shared with
`initialize_overlay` in `include/overlay.h`. The constructor and root viewport
bindings independently prove that the `+0x80..+0x147` region is an owned
`RenderCamera`, not three unrelated matrices and scalar fields.

Android and iOS independently retain this method as the void
`cROverlay::AI()`. Both preserve the angular wrap, local-Z transform rebuild,
owned camera transform copy, and inverse-view update. Their platform offsets
differ, so only the owner graph and operation transfer to Windows.

2026-08-09 primary owner promotion: the matcher now emits this callback as
`cROverlay::AI()` and binds the owner-qualified VC6 spelling
`?AI@cROverlay@@QAEXXZ`; `Overlay` remains the compatibility typedef used by
the tracked analyzer replay. Windows has no direct code xref to this leaf:
`0x4972ec` is a one-entry callback table containing `0x40a1b0`, installed on
all three root-owned overlays by the constructor at `0x407e0a`, `0x407e28`,
and `0x407e46`. The ownership spelling is codegen-neutral and keeps the exact
42/42 stream with all seven masked operands clean.
