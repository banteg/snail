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

## 2026-08-12 authored method surface

The scratch now spells the exact member as `cRTimesUp::UnInit()` and exports
`?UnInit@cRTimesUp@@QAEXXZ`. Live Windows recovery finds the teardown edge from
`cRSubGame` destruction and the internal expiry edge from `cRTimesUp::AI()`.
Android independently preserves the class-qualified symbol and body. Matching
stays exact at 8/8 with both operands clean.

## 2026-08-13 canonical database ownership

The two live Windows callers prove the same canonical receiver: `destroy_subgame`
passes the final `cRSubGame +0x1272828` child, while `cRTimesUp::AI()` reuses its
own receiver on expiry. Both decompiler replays now preserve that exact
`cRTimesUp*` ABI and the borrowed border field. Matching stays exact at 8/8
with both operands clean.
