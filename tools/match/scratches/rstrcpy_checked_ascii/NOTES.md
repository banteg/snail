# Rstrcpy

Exact at 31/31 instructions with two clean relocation masks. It copies a
NUL-terminated resource string and, in the Windows build, reports high-bit
bytes through the `Dodgy Rstrcpy` diagnostic while continuing the copy.

Android and iOS preserve the authored void
`Rstrcpy(char*, char const*)` contract in `RString.o`. Windows callers discard
the final copied byte left incidentally in EAX; the const source ownership and
void API are therefore retained.
