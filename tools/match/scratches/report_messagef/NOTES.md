# report_messagef @ 0x431d60

Formats a caller-supplied varargs payload into a 4096-byte stack buffer, then
passes it through the release-stripped debug report helper as `"%s", buffer`.

`data_4a16a4` is byte-checked as the literal `"%s"`. The target call at
`0x48c404` is the statically linked CRT `vsprintf` body.

Focused match: 100%, 15/15 instructions, with four clean masked operands.

This scratch compiles as C (`/TC`). The C-mode MSVC 6.5 codegen coalesces the
cdecl cleanup for the three `vsprintf` arguments and the two
`debug_report_stub` arguments into the final `add esp, 0x1014`, matching the
native wrapper while keeping the source as straightforward sequential calls.
