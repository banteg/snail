# snapshot_current_display_mode

Small display-mode wrapper at 0x407850. Both BN and IDA decompiles show it
calling EnumDisplaySettingsA with a null device name, ENUM_CURRENT_SETTINGS
(-1), and the shared DEVMODEA buffer at 0x4df868.

Exact match: 100.00%, 5/5 instructions, with the EnumDisplaySettingsA import
and g_current_display_mode buffer operands resolved.
