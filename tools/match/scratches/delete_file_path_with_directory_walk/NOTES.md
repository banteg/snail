# delete_file_path_with_directory_walk @ 0x431540

Walks a possibly nested path by switching into each intermediate directory
component through `set_current_directory_with_drive_fallback`, then tests the
final component with `fopen("wb")`, reports deletion, closes the handle, calls
`remove`, and restores the caller's original working directory.

The source preserves the native success-path quirk: the `remove` failure report
uses the same current-directory stack buffer, but the target only refreshes that
buffer on the initial `fopen` failure path.

Focused proof:

```text
./match.sh scratches/delete_file_path_with_directory_walk --full
match: 100.00%
target: 84 insns, candidate: 84 insns
prefix: 84/84 target insns
masked operands: 14 ok, 0 unresolved, 0 mismatch
```

2026-07-15 CRT ownership: VC6's `<stdio.h>` and `<direct.h>` now own the
`FILE*`, `fopen`/`fclose`/`remove`, and directory calls. The exact 84/84 object
and 14 clean masked operands survive removal of the opaque `File` and six local
CRT declarations.
