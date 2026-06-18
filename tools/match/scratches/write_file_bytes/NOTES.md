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
