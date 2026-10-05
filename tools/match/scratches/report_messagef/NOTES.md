# report_messagef @ 0x431d60

Formats a caller-supplied varargs payload into a 4096-byte stack buffer, then
passes it through the release-stripped debug report helper as `"%s", buffer`.

`data_4a16a4` is byte-checked as the literal `"%s"`. The target call at
`0x48c404` is the statically linked CRT `vsprintf` body.

Focused match: 100%, 15/15 instructions, with four clean masked operands.

The scratch was first matched as C (`/TC`) under MSVC 6.5, whose codegen coalesces the
cdecl cleanup for the three `vsprintf` arguments and the two
`debug_report_stub` arguments into the final `add esp, 0x1014`, matching the
native wrapper while keeping the source as straightforward sequential calls.

The file-utility run 0x430f30-0x431d60 compiles as part of the RShell C++
object under the project baseline, msvc6.3; see the
[compiler identification](../../compiler-identification-20261005.md).
