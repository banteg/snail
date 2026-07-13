# debug_report_stub @ 0x449c00

Release-build variadic reporting sink used across startup, rendering, audio,
track building, warnings, and error wrappers. The shipped body is exactly
`xor eax, eax; ret`: it reads no arguments, leaves caller cleanup to cdecl, and
returns zero.

Tracking the stripped sink as its own exact function resolves the common call
target without pretending the omitted formatting/output implementation exists.
