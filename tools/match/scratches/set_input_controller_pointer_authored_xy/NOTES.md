# set_input_controller_pointer_authored_xy @ 0x4323a0

Seeds one input-controller slot with authored 640x480 pointer coordinates, then
converts those authored coordinates back into the stored screen-region bounds
before calling `click_mouse_screen`.

The authored X/Y parameters are stored as raw float bit patterns. Spelling them
as `int` parameters in the scratch preserves the native `mov` stores while the
later arithmetic reinterprets the same stack slots as floats.

2026-07-13 owner closure: the raw-bit stores now target
`g_input_controller_slots[slot].authored_x/authored_y` through the recovered
two-record owner. VC6 retains the exact 40/40 instruction stream and all 11
operands resolve to the corresponding fields.
