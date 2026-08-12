# load_config_file

Small config-file wrapper at 0x42f470. Both BN and IDA decompiles show it
passing the caller file name and buffer to load_file_bytes_from_path with null
output-size and zero element-count arguments.

Exact match: 100.00%, 9/9 instructions, with the wrapper call operand resolved
through load_file_bytes_from_path.

2026-08-12 Register ownership recovery: the v1.5 iOS Mach-O STABS records put
`gRegisterLoadFile(char*, void*)` directly in `Register.cpp` / `Register.o`.
Its body forwards to `MacLoadFile`; Android preserves the exact overload and
forwards null size output plus a zero final argument to the four-argument
overload. Windows has the identical wrapper shape, and its sole caller passes
`"SnailMail.cfg"` plus the cross-port config owner while discarding EAX. This
recovers the authored overload and source unit without importing either
platform's file backend or return-type inference.
