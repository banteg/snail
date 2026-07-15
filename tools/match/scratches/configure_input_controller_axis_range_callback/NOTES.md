# configure_input_controller_axis_range_callback @ 0x44b4e0

DirectInput object-enumeration callback that applies the native joystick axis
range property of `[-1000, 1000]` to each enumerated joystick device for objects
whose type has the low axis bits set.

The callback and stack property now use the complete SDK
`DIDEVICEOBJECTINSTANCEA` and `DIPROPRANGE` owners. The axis selector is
`dwType +0x18`; the property has the canonical 0x10-byte `DIPROPHEADER`
followed by `lMin` and `lMax`, for an exact size of 0x18.
