# probe_display_mode_count

Small display-mode probe at 0x407880. Both BN and IDA decompiles show it
walking EnumDisplaySettingsA from mode index zero until the API returns false,
using a 156-byte stack DEVMODEA buffer.

Exact match: 100.00%, 17/17 instructions, with the EnumDisplaySettingsA import
operand resolved.
