# load_file_bytes

Small archive/filesystem wrapper at 0x431520. Both BN and IDA decompiles show it
passing the caller file name, a null destination buffer, and the caller output
size pointer to load_file_bytes_from_archive_or_fs.

Exact match: 100.00%, 8/8 instructions, with the wrapper call operand resolved
through load_file_bytes_from_archive_or_fs.

iOS `RShell.o` confirms this as the two-argument
`RShellLoadFile(char*, int*)` overload; the three-argument overload owns the
optional destination buffer.
