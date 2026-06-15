# load_file_bytes_allocating

Small filesystem load wrapper at 0x4051b0. Both BN and IDA decompiles show it
passing the caller file name, a null destination buffer, and the caller output
size pointer to load_file_bytes_into_optional_buffer.

Exact match: 100.00%, 8/8 instructions, with the wrapper call operand resolved
through load_file_bytes_into_optional_buffer.
