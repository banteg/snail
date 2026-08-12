# RTextNewLine

Exact at 13/13 instructions with no masked operands. It advances the
caller-owned cursor through LF or NUL, then steps once so the next read starts
on the following line.

Android and iOS preserve the void `RTextNewLine(char**)` contract and its slot
between `RTextCompStart` and `RTextAppend` in `RShell.o`. All seven Windows
calls discard EAX.
