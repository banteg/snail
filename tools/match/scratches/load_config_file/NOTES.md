# load_config_file

Small config-file wrapper at 0x42f470. Both BN and IDA decompiles show it
passing the caller file name and buffer to load_file_bytes_from_path with null
output-size and zero element-count arguments.

Exact match: 100.00%, 9/9 instructions, with the wrapper call operand resolved
through load_file_bytes_from_path.
