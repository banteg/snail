# restore_desktop_display_mode

Small display-mode restore wrapper at 0x407860. Both BN and IDA decompiles show
it calling ChangeDisplaySettingsA with null DEVMODE/zero flags and then
returning ShowCursor(1).

Exact match: 100.00%, 6/6 instructions, with the ChangeDisplaySettingsA and
ShowCursor import operands resolved.
