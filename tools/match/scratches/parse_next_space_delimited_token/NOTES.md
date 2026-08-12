# RTextExtractString

Exact at 27/27 instructions with no masked operands. It skips leading spaces,
copies through the next space or CR, terminates the output, and advances the
caller-owned cursor.

Android and iOS preserve the authored void
`RTextExtractString(char**, char*)` contract in `RShell.o`; the sole Windows
caller also discards EAX. The scratch retains a `char**` result solely as a
documented VC6 source-shape harness: every natural void transcription tested
recolored the cursor/output registers and lost the exact body. The shared
header, analyzers, and authentic reference symbol remain void. No dummy branch,
volatile value, or synthetic dependency is used.
