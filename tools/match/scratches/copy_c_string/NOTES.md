# Matched

`copy_c_string` matches exactly with the post-increment source idiom:
copy `*source` to `*destination++`, then test and advance `source` in the loop
condition. This preserves the native duplicated source-byte load and register
ownership.

## 2026-07-27 authored RText ownership

Android and iOS preserve this helper as void
`RTextCopy(char*, char*)` in `RShell.o`. It begins the same contiguous
`RTextCopy` through `RTextExtractFloat` sequence as Windows, and mobile
`ObjectTextLoad` calls it in the same path-building position as Windows
`load_object_definition`.

Both Windows callers discard EAX. Removing the synthetic pointer return keeps
the exact 10/10 Windows object, so the matcher now carries the authored void
contract without code-generation scaffolding.
