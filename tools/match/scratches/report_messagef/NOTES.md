# report_messagef @ 0x431d60

Formats a caller-supplied varargs payload into a 4096-byte stack buffer, then
passes it through the release-stripped debug report helper as `"%s", buffer`.

`data_4a16a4` is byte-checked as the literal `"%s"`. The target call at
`0x48c404` is the statically linked CRT `vsprintf` body.

Match status: 83.87%, no masked operand issues.

Residual:

- Native coalesces the cdecl cleanup for the three `vsprintf` arguments and
  the two `debug_report_stub` arguments into the final `add esp, 0x1014`.
  MSVC 6.5 emits `add esp, 0xc` after `vsprintf`, then cleans the report
  arguments separately for the readable source shape.
- Probed and rejected: nested comma expression and `void vsprintf`; both kept
  the same cleanup split.
