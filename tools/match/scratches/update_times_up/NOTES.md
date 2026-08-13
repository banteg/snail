# Exact match

`TimesUp::update_times_up` @ `0x445e20` is the Windows
`cRTimesUp::AI()`. State 1 advances the progress pair and arms state 2; state 2
calls `uninit_times_up`, kills the embedded Goldy player, and clears the owner.
Android and iOS preserve the authored class/member name.

The owner is the final 0x10 bytes of `cRSubGame` at `+0x1272828`, directly
after the 0x50-byte `Completion`. The primary `TimesUp` type remains exact at
26/26 instructions with all five operands clean.

The kill target now resolves through `GameRoot::subgame.player`; the old
`root + 0x42fd7c` cast described the same embedded owner but hid its lifetime.
Focused matching remains exact.

## 2026-07-14 times-up lifecycle ownership

AI now consumes `TimesUpState` directly: `DISPLAYING` advances the countdown,
`EXPIRED` tears down the borrowed widget and kills the embedded player, and the
shared tail returns the controller to `INACTIVE`. Focused matching remains
exact at 26/26 instructions with all five operands clean.

## 2026-07-17 paired runtime replay

The maintained IDA subgame-runtime replay now applies the missing
`void __thiscall(TimesUp*)` ABI, matching Binary Ninja and the exact tail type.
Both tracked decompilers expose the state/progress lifecycle directly; no
matching source changed. Focused output remains exact at 26/26 instructions
with five clean masked operands.

## 2026-07-25 IDA Player-root replay

The expiry kill at `0x445e3a` borrows root `+0x42fd7c`, exactly the embedded
Player already named in source and Binary Ninja. Normalizing that single
colliding operand removes IDA's false standalone `g_player_block` expression
and closes the TimesUp-to-Player lifetime without changing the exact 26/26
matcher result.

## 2026-08-12 authored method surface

The scratch now spells the exact member as `cRTimesUp::AI()` and exports
`?AI@cRTimesUp@@QAEXXZ`. Its sole external Windows caller passes the final
0x10-byte owner at `cRSubGame + 0x1272828`; the state-2 arm calls the adjacent
authored `UnInit()` member on the same receiver. Android and iOS independently
retain `cRTimesUp::AI()`. Matching stays exact at 26/26 with five clean operands.

## 2026-08-13 canonical database ownership

Live Binary Ninja and IDA readback found the exact 0x10-byte layout only under
the generic `TimesUp` name, embedded at the final `cRSubGame +0x1272828`, with
no `cRTimesUp` type present. The guarded replay now retires that generic owner
only after full layout equivalence, verifies the canonical tail embed, and
assigns this function `void __thiscall(cRTimesUp*)`. Matching remains exact at
26/26 with all five operands clean.
