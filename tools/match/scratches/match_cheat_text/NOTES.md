# match_cheat_text

`match_cheat_text` checks whether the rolling eight-byte cheat input buffer
ends with a supplied uppercase cheat word. Native rejects words of length eight
or more with `"Cheat text too long"`.

Current result: 68.24%, 43/42 candidate/target instructions, two clean masked
operands. Semantics match the decompile: `strlen(text)`, length guard, reverse
suffix compare against `CheatState::recent_text_*`, and success/failure byte
return.

Residual:

- Native moves the post-`strlen` length from `ecx` into `esi`, then keeps the
  rolling-buffer cursor in `edx` and uses `cl`/`bl` for the byte compare. The
  clean source keeps the length in `ecx`, uses `esi` for the cursor, and
  compares through `dl`/`bl`.
- Explicit byte temporaries, `strlen(text) + 1` spelling, a duplicated
  length local, and `register` on the length were all codegen-neutral or worse.
  Do not force the remaining register ownership with fake locals or dummy
  aliases.
