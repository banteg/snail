# report_errorf @ 0x431cc0

Formats a caller-supplied varargs payload into a 4096-byte stack buffer, then
emits the native error prefix, formatted payload, and shared newline through
the release-stripped debug report helper.

`data_4a4880` is the native `***** ERROR ***** ` prefix, `data_4a16a4` is
byte-checked as `"%s"`, and `data_4a44cc` is the shared newline literal already
documented by `display_score_stats`.

Match status: 82.93%, no masked operand issues.

Residual:

- Native coalesces the cdecl cleanup for the three `vsprintf` arguments plus
  all stripped debug helper arguments into the final `add esp, 0x101c`.
  MSVC 6.5 emits cleanup after each call for the readable source shape.
