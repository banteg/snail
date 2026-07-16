# enumerate_input_controllers @ 0x44b3c0

Creates the parent DirectInput object, enumerates up to four joystick devices,
stores the resulting count, then applies the joystick data format, cooperative
level, and axis-range object callback to each accepted device.

Exact source-shape note: after successful device enumeration, native returns
zero if either the first joystick slot is null or the resulting count is
non-positive. A source fallthrough to the prior DirectInput result keeps the
instruction count but shifts the success/error return labels.

## 2026-07-16 shared DirectInput state ownership

The interface IID and joystick `DIDATAFORMAT` now come from the same shared SDK
record bank as the keyboard and mouse setup paths. Together with the existing
four-entry interface bank, this gives enumeration one process-owned DirectInput
lifetime instead of scratch-local declarations. The function remains exact at
71/71 instructions with all 14 operands clean.
