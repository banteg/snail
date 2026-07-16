# write_file_bytes @ 0x431650

Walks a possibly nested output path by switching into each intermediate
directory, writes the final path component with `fopen("wb")`/`fwrite`, reports
save failures with the current directory, and restores the caller's original
working directory.

The scratch compiles as C (`/TC`) so the success `fwrite`/`fclose` path and the
failure `_getcwd`/`report_messagef` path both coalesce cleanup into the native
shared epilogue.

Focused proof:

```text
./match.sh scratches/write_file_bytes --full
match: 100.00%
target: 74 insns, candidate: 74 insns
prefix: 74/74 target insns
masked operands: 10 ok, 0 unresolved, 0 mismatch
```

iOS `RShell.o` names the public contract `RShellSaveFile(char*, void*, int)`.
Using that caller-owned buffer and signed 32-bit length directly is
codegen-neutral for the exact Windows implementation.

2026-07-15 CRT ownership: the stream, directory, and write operations now come
from VC6's real `<stdio.h>` and `<direct.h>` declarations. Replacing the opaque
`File` and five local CRT prototypes with `FILE*` keeps the exact 74/74 object
and ten clean masked operands.

2026-07-16 decompiler replay closure:

- IDA now preserves the distinct 256-byte path component, 512-byte error
  directory, 512-byte original directory, and file stream locals. Correct CRT
  and directory-helper prototypes keep `fwrite(bytes, 1, byte_count, stream)`
  intact instead of reinterpreting its call slots as frontend structures.
- The replay removes the stale overlapping local override, applies the real
  stack offsets, and verifies an idempotent readback. Paired health checks pass;
  matching remains exact at 74/74 instructions with ten clean masked operands.
