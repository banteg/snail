# update_joystick_input @ 0x44b570

Polls each enumerated DirectInput joystick, reacquires after transient poll
loss, normalizes the primary X/Y axes with the same `0.001f` scale as native,
and maps the sampled button bytes into the shared input-controller bitmask.

The stack record is the SDK-owned 0x110-byte `DIJOYSTATE2`, not a local prefix
plus an anonymous button tail. The input path consumes `lX`, `lY`, and the
first sixteen bytes of `rgbButtons`; the complete velocity, acceleration, and
force lanes preserve the public ABI through the exact end of the record. The
button mapping intentionally uses the authored DirectInput button indices
rather than renumbering them by output mask order.

Exact source-shape note: the native loop is count-driven (`slot <
g_joystick_count`) with a separate null-device break. Spelling the loop as
`while (*device_ref != 0)` adds an unwanted pretest of the first device pointer.
