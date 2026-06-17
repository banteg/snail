# initialize_keyboard_input @ 0x44b7d0

Initializes keyboard DirectInput after `release_input_controllers`, then clears
the two 0x100-byte keyboard state buffers.

`DirectInput8Create` is `__stdcall`; using the default C calling convention
adds a non-native stack cleanup after the call.
