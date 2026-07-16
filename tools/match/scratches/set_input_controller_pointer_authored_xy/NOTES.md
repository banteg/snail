# set_input_controller_pointer_authored_xy @ 0x4323a0

Seeds one input-controller slot with authored 640x480 pointer coordinates, then
converts those authored coordinates back into the stored screen-region bounds
before calling `click_mouse_screen`.

The authored X/Y parameters are stored as raw float bit patterns. Spelling them
as `int` parameters in the scratch preserves the native `mov` stores while the
later arithmetic reinterprets the same stack slots as floats.

2026-07-16 owner correction: the raw-bit stores now target the authored-X/Y
fields selected from the two separate 0x20-byte controller payloads at their
proved 0x38-byte stride. This avoids claiming either trailing stride gap or the
intervening RShell repeat global as controller-owned. VC6 retains the exact
40/40 instruction stream and all 11 operands resolve to the corresponding
fields.
