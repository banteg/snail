# Exact match

`TimesUp::update_times_up` @ `0x445e20` is the Windows
`cRTimesUp::AI()`. State 1 advances the progress pair and arms state 2; state 2
calls `uninit_times_up`, kills the embedded Goldy player, and clears the owner.
Android and iOS preserve the authored class/member name.

The owner is the final 0x10 bytes of `SubgameRuntime` at `+0x1272828`, directly
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
