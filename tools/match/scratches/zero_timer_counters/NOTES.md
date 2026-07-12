# zero_timer_counters

- Exact match: 100.00%, 8/8 instructions.
- Cross-port recovery identifies the 0x18-byte receiver as authored `cRTime`
  and this method as `cRTime::Zero()`. iOS v1.5/v1.9 preserve the name in
  `SubGame.o`; Android preserves both the symbol and the same six-field layout.
- The method is void. Windows uses EAX as a shared zero source for all six
  stores, while Android returns directly after the stores; changing the C++
  declaration from an incidental `int` result to void remains byte exact.
