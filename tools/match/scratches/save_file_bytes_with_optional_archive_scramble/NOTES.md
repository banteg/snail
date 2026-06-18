# save_file_bytes_with_optional_archive_scramble @ 0x4052a0

Writes one byte buffer to the filesystem, optionally applying the archive
scramble in place before opening the destination. The success path logs the
write, writes the bytes, and closes the stream. The failure path captures the
current directory and reports the save failure.

Match status: 93.81%, no masked operand issues.

Residual:

- Native coalesces the `_getcwd` and failure `printf` cdecl cleanup into a
  single `add esp, 0x14` and computes the stack-buffer address before popping
  the `_getcwd` arguments. The readable source shape emits `add esp, 0x8`
  after `_getcwd`, then cleans the three `printf` arguments separately.
