# Matched

`skip_to_next_line` is instruction-exact at 13/13 instructions. It advances
the caller-owned cursor through LF or NUL and then steps once so the next read
starts on the following line.

## 2026-07-27 authored RText ownership

Android and iOS preserve the same body as void `RTextNewLine(char**)` in
`RShell.o`, between `RTextCompStart` and `RTextAppend`. Mobile
`ObjectTextLoad` uses it at the same section and row boundaries as Windows
`load_object_definition`.

All seven Windows calls discard EAX. Removing the synthetic pointer return
preserves the exact object, recovering the authored void contract directly.
