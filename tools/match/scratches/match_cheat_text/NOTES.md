# match_cheat_text

`match_cheat_text` checks whether the rolling eight-byte cheat input buffer
ends with a supplied uppercase cheat word. Native rejects words of length eight
or more with `"Cheat text too long"`.

Current result: 100.00%, 42/42 candidate/target instructions, two clean masked
operands. Semantics match the decompile: `strlen(text)`, length guard, reverse
suffix compare against `CheatState::recent_text_*`, and success/failure byte
return.

Source-shape notes:

- `0 < length` is required for VC6 to emit the native `test esi, esi` gate and
  avoid the extra candidate tail instruction from the previous `length > 0`
  spelling.
- Hoisting `index` above the empty-length gate is required for the native
  `xor eax, eax` before `test esi, esi`.
- Keeping the `for` increment empty and spelling `++index; --cursor;` in the
  loop body is required for the native `inc eax` before `dec edx` tail order.

Rejected source-shape probes:

- Explicit byte temporaries, `strlen(text) + 1` spelling, a duplicated
  length local, and `register` on the length were all codegen-neutral or worse.
- An IDA-style equality loop and a `do` loop both regressed sharply by changing
  saved-register ownership.

2026-07-14 rolling-buffer ownership: the reverse-compare cursor now starts
from `CheatState::recent_text + length - 1` rather than rebuilding the same
address from raw `this + length + 7`. The field-relative spelling remains
exact at 42/42 instructions with both operands clean.

## 2026-07-18 authored member contract

Android preserves `cRCheat::MatchText(char*)`, including the mutable `char*`
parameter spelling, while every path deliberately returns zero or one. The
shared declaration now records that bool contract and the exact cross-port
parameter type. Windows remains exact at 42/42 instructions with both masked
operands clean.

The paired decompiler replays also name the reverse comparison pointer
`recent_text_cursor` from its exact ECX/EDX SSA and Hex-Rays definition
identities. It remains a `char*` borrow into the owned eight-byte window rather
than a fabricated allocation or wider field.
