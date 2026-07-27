# Matched

`append_c_string` is instruction-exact at 19/19 instructions: scan to the
destination NUL, copy the source bytes, and write the final terminator.

## 2026-07-27 authored RText ownership

Android and iOS preserve the same helper as void
`RTextAppend(char*, char*)` in `RShell.o`. Mobile `ObjectTextLoad` performs the
same `.tga`, slash, and texture-name appends as Windows
`load_object_definition`, inside the same contiguous RText helper family.

All three Windows calls discard EAX. Removing the synthetic pointer return
keeps the exact object and restores the authored void boundary.
