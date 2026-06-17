# uninitialize_input_devices @ 0x411d80

Shutdown wrapper for the input stack. It runs the pre-input teardown helper,
releases controller devices, releases keyboard DirectInput, and tail-returns the
mouse DirectInput release result.
