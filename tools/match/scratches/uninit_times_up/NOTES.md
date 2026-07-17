# Exact match

`TimesUp::uninit_times_up` @ `0x445e70` is the Windows
`cRTimesUp::UnInit()`. When active, it returns the borrowed widget at `+0x04`
to the root `BorderManager`; the embedded owner never owns or frees the widget
allocation itself.

The primary 0x10-byte `TimesUp` owner remains exact at 8/8 instructions with
both operands clean.

## 2026-07-14 times-up lifecycle ownership

Teardown now tests `TIMES_UP_STATE_INACTIVE` explicitly. Both active states
still release the borrowed border through the root manager, and focused
matching remains exact at 8/8 instructions with both operands clean.

2026-07-17 paired runtime replay: IDA now retains the authored
`void __thiscall(TimesUp*)` ABI and exposes the borrowed `border` field instead
of a raw `_DWORD**` receiver, matching Binary Ninja. Focused output remains
exact at 8/8 instructions with both masked operands clean.
