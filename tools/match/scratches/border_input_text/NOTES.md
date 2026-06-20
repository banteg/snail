# border_input_text @ 0x4035b0

Starter scratch for front-end inline text editing.

Models the recovered autorepeat key codes, cursor marker movement, insertion,
delete/backspace, word-ish moves across `>` separators, numeric/space filter
flags, blink timer, layout refresh, and OK-button finalization. It uses raw
widget offsets matching `border_input_text_init`.

Expected residuals:
- cursor-move cases are semantic but not native-scheduled;
- the compact-space numeric mode is relationship-first;
- there is no attempt to force the native byte-for-byte loop shapes yet.

2026-06-20 ABI cleanup:

- Replaced the scratch-local `InputOkState::update_input_ok()` `int` stub with
  `include/input_ok_state.h`; the exact `update_input_ok` and
  `initialize_input_ok` scratches prove the `FrontendWidget*` return.
- Replaced the scratch-local `BorderManager::kill_border(void*)` stub with the
  shared `BorderManager::kill_border(FrontendWidget*)` declaration.
- Focused matcher stayed at 17.77% with 297/446 candidate/target instructions
  and 8 clean masked operands. This removes the `InputOkState` ABI-conflict
  row and contributes to the shared `BorderManager` row cleanup.
