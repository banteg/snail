# Rstrint

Exact at 47/47 instructions with no masked operands. It advances a caller-owned
cursor to `-`, `+`, `.`, or a decimal digit, consumes an optional minus sign,
accumulates base-10 digits, and leaves the cursor after the token.

Android and iOS preserve `Rstrint(char**)` in `RString.o`. The pre-scan reads
the classifier through a scoped current pointer while retaining the
caller-owner loop condition; that natural source shape reproduces native's
early minus gate and delayed saved-register setup without coercion.
