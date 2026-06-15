# read_current_display_resolution

Small display-resolution helper at 0x4078b0. Both BN and IDA decompiles show it
reading dmPelsWidth/dmPelsHeight from a 156-byte stack DEVMODEA buffer after
EnumDisplaySettingsA succeeds, with a 640x480 fallback when it fails.

Exact match: 100.00%, 22/22 instructions, with the EnumDisplaySettingsA import
operand resolved.
