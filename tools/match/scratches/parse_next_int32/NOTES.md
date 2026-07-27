# Matched

`parse_next_int32` is instruction-exact at 39/39 instructions. It skips leading
spaces, consumes an optional minus sign, accumulates decimal digits, advances
the caller-owned cursor, and returns the signed value.

## 2026-07-27 authored RText ownership

Android and iOS preserve the same API and behavior as
`RTextExtractInt(char**)` in `RShell.o`. Its position between
`RTextExtractString` and `RTextExtractFloat`, plus the matching
`ObjectTextLoad` call sites, resolves the Windows source owner without
transferring mobile layout assumptions.
