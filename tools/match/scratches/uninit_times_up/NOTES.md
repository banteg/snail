# Exact match

`TimesUp::uninit_times_up` @ `0x445e70` is the Windows
`cRTimesUp::UnInit()`. When active, it returns the borrowed widget at `+0x04`
to the root `BorderManager`; the embedded owner never owns or frees the widget
allocation itself.

The primary 0x10-byte `TimesUp` owner remains exact at 8/8 instructions with
both operands clean.
