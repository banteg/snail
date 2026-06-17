# update_keyboard_input @ 0x44b870

Polls the keyboard DirectInput device, builds the slot-0 button mask and axes,
and clears both keyboard buffers on lost/unacquired device errors.

The source uses `if (GetDeviceState(...) < 0) { reacquire } else { map keys }`
because native lays out the reacquire block before the key-mapping block and
jumps forward on successful polling.
