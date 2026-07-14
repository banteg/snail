# show_times_up_message @ 0x445e90

Exact match: 100.00%, 31/31 instructions.

When the message is inactive, this allocates a border widget, initializes the
centered `"Time's Up"` text with frontend flag word `0x400002`, seeds the fade
progress, and marks the controller active.

2026-07-11 authored owner: the primary `TimesUp` type is shared through
`times_up.h` across show/update/uninit and maps to mobile `cRTimesUp::Init()`.
It owns the final 0x10 bytes of `SubgameRuntime`; the border at +0x04 is a
borrowed `FrontendWidget*`. This scratch remains exact at 31/31 with all six
operands clean.

## 2026-07-14 times-up lifecycle ownership

Init now accepts only `TIMES_UP_STATE_INACTIVE` and enters
`TIMES_UP_STATE_DISPLAYING` after constructing the message. This closes the
producer edge into exact AI while preserving 31/31 instructions and all six
clean operands.
