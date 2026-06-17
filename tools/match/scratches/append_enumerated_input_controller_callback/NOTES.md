# append_enumerated_input_controller_callback @ 0x44b490

DirectInput device-enumeration callback for joystick discovery. It appends each
created joystick device into the four-entry `g_joystick_devices` array and keeps
enumerating until four devices have been accepted.
