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
  `108 ok`, `0 unresolved`, `1 mismatch`.
- `initialize_exit_prompt_jump_table` is curated at `0x4067b4` with ten entries
  (`0x28` bytes) between the function `ret` at `0x4067b0` and the `0x90`
  padding before `update_completion_screen`. The masked audit now reports the
  table as a real content mismatch instead of an anonymous unresolved image
  address: native entries include the shared return offset `0x6d9`, while the
  candidate table uses `0x6db` because of the extra `xor eax,eax`.
- Shared headers now model `FrontendWidget::initialize_frontend_widget` as
  returning `FrontendWidget*`, matching the `initialize_frontend_widget` scratch
  and the IDA result flow here. This is codegen-neutral for this scratch and
  preserves the exact menu initializer scratches tested with it.
- Rejected tail attempts: direct `return (int)no_button->initialize_frontend_widget(...)`
  on the two no-title branches reshapes the switch to `74.86%`; a shared
  `result` local keeps the audit clean but introduces an `edi` result register,
  shifts all stack color locals, and drops to `92.20%`. Keep the explicit
  `return 0` spelling until there is a source shape that removes the `xor`
  without perturbing the switch layout.
