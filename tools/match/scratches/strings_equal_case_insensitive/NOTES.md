# RTextCompStart

Exact at 50/50 instructions with no masked operands. The source deliberately
performs separate lexical reads for each raw and ASCII-folded byte lifetime;
VC6 then reproduces the native raw-first byte-lane allocation without volatile
state or synthetic dependencies.

Android and iOS preserve `RTextCompStart(char*, char*)` in the same contiguous
`RShell.o` family and use it at the corresponding `ObjectTextLoad` section
markers. Its success condition is asymmetric: the prefix may terminate while
the searched text continues. The later `RString.o` `Rstrcmp` helper instead
requires both strings to terminate and is not this function.
