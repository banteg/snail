# append_enumerated_input_controller_callback @ 0x44b490

DirectInput device-enumeration callback for joystick discovery. It appends each
created joystick device into the four-entry `g_joystick_devices` array and keeps
enumerating until four devices have been accepted.

## 2026-07-14 joystick-bank ownership closure

The process-owned DirectInput pointer, accepted-device count, and fixed
four-entry device bank now live together in `direct_input_view.h`; enumeration,
axis setup, polling, and shutdown borrow that shared owner instead of repeating
scratch-local declarations. The callback derives its signed acceptance bound
from the bank itself. The explicit `int` cast is source-contract evidence:
without it, VC6 lowers the unsigned `sizeof` expression to a different compare.

All five affected exact helpers remain byte-identical. Their normalized listing
hashes are:

- `enumerate_input_controllers`:
  `3109e3e229ab0355f31f7cc93af213da8eb4320555d57ced79de7c83b9d82585`
- `append_enumerated_input_controller_callback`:
  `7cf8550fbfb3b7d8665ef4f06f5510d5dfb1092064cc5749bee35666884ab544`
- `configure_input_controller_axis_range_callback`:
  `95f0af252286615abf6dc4a295735d4d9fd392d6520d26c5d6f9dd7f7ddd2092`
- `update_joystick_input`:
  `041d15cd0d9c67bf6a41da000488bc036ec77d98da73d191fd1464bdfaf7b1ab`
- `release_input_controllers`:
  `796214bfea81bf07c9b36ab9099240c0897b221767d80fef1b0997894381e8c5`
