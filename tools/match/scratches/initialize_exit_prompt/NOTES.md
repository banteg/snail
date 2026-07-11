# initialize_exit_prompt

- Target: `CompletionPrompt::initialize_exit_prompt` at `0x4060d0`.
- First-pass recovery from BN decompile/disassembly. The function hides the
  active border batch, switches on `state - 2`, then allocates/layouts the
  prompt title plus Yes/No buttons for most states.
- Native has several duplicated switch arms with shared tail jumps. Keep the
  C++ cases explicit until the matcher shows which duplicated blocks can be
  safely folded without losing branch shape.
- Known state layouts:
  - states 2, 3, 7 use the centered quit title plus Yes/No at `y=330`.
  - states 8 and 9 use `prompt_y` for Yes/No under the centered title.
  - state 4 uses absolute Yes/No positions without title.
  - state 5 uses absolute title and button positions.
  - state 10 uses the centered default layout.
- Focused match: `100.00%` (`441/441` instructions, `441/441` prefix,
  `109 ok`, `0 unresolved`, `0 mismatch`).
- `initialize_exit_prompt_jump_table` is curated at `0x4067b4` with ten entries
  (`0x28` bytes) between the function `ret` at `0x4067b0` and the `0x90`
  padding before `update_completion_screen`. The table now resolves cleanly.
- Shared headers now model `FrontendWidget::initialize_frontend_widget` as
  returning the same word result as `layout_frontend_widget`; this matches the
  two no-title branches that return the call result in `eax` and remains
  codegen-neutral for this scratch.
- 2026-06-20 proof: the two no-title branches must return the final
  `no_button->initialize_frontend_widget(...)` result instead of discarding it
  with `return 0`. BN and IDA both show native leaving that call result in
  `eax`; matching the real result flow removes the extra `xor eax,eax`, fixes
  the jump-table target offset, and proves the scratch.
- A shared `result` local still remains rejected: it introduces an `edi` result
  register, shifts the stack color locals, and drops to `92.20%`.
- 2026-07-11 local-label collision audit: the current compiler generation calls
  this table `$L1075`, a spelling also used by an unrelated backdrop table.
  The matcher now retains both the alias-bounded and relocation-bounded entry
  sequences, so the ten prompt destinations are proved by content without
  assigning a globally false label alias. The exact 441/441 body remains at
  109 clean masked operands.
