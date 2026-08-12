# RTextExtractInt

Exact at 39/39 instructions with no masked operands. It skips leading spaces,
consumes an optional minus sign, accumulates decimal digits, advances the
caller-owned cursor, and returns the signed value.

Android and iOS preserve `RTextExtractInt(char**)` between
`RTextExtractString` and `RTextExtractFloat` in `RShell.o`, with matching
`ObjectTextLoad` callsites.
