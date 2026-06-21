# match_cheat_text

`match_cheat_text` checks whether the rolling eight-byte cheat input buffer
ends with a supplied uppercase cheat word. Native rejects words of length eight
or more with `"Cheat text too long"`.

Current result: 95.24%, 42/42 candidate/target instructions, two clean masked
operands. Semantics match the decompile: `strlen(text)`, length guard, reverse
suffix compare against `CheatState::recent_text_*`, and success/failure byte
return.

Residual:

- `0 < length` is required for VC6 to emit the native `test esi, esi` gate and
  avoid the extra candidate tail instruction from the previous `length > 0`
  spelling.
- The remaining mismatch is the compare loop register split: native stages the
  rolling-buffer byte through `cl` while the candidate uses `dl`.
- Explicit byte temporaries, `strlen(text) + 1` spelling, a duplicated
  length local, and `register` on the length were all codegen-neutral or worse.
  Do not force the remaining register ownership with fake locals or dummy
  aliases.
