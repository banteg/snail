# Rstrcmp

Exact at 33/33 instructions with no masked operands. It performs strict
ASCII-case-insensitive equality and succeeds only when both folded strings
terminate together, unlike prefix-friendly `RTextCompStart`.

Android and iOS preserve `Rstrcmp(char*, char*)` in `RString.o`. Their
decompilers infer bool, but the return type is absent from the C++ symbol;
Windows emits full-EAX 0/1 writes and all six callers consume the full result.
A bool transcription changes those writes to AL, so the evidence-backed
Windows ABI remains `int`.
