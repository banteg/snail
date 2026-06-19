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
