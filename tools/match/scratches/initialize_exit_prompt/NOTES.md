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
- Focused match: `99.66%` (`441` target insns, `442` candidate insns),
  `108 ok`, `1 unresolved`, `0 mismatch`.
- Remaining code-shape delta: shared headers model `FrontendWidget::initialize_frontend_widget`
  as `void`; native leaves the final call's `eax` live on the two final-call
  return paths, while the scratch uses `return 0` and emits one extra
  `xor eax,eax`.
