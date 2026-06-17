# set_input_controller_pointer_authored_xy @ 0x4323a0

Seeds one input-controller slot with authored 640x480 pointer coordinates, then
converts those authored coordinates back into the stored screen-region bounds
before calling `click_mouse_screen`.

The authored X/Y parameters are stored as raw float bit patterns. Spelling them
as `int` parameters in the scratch preserves the native `mov` stores while the
later arithmetic reinterprets the same stack slots as floats.
