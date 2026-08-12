# Rstrfind

Exact at 63/63 instructions with four clean relocation masks. It scans the
second argument for an ASCII-case-insensitive occurrence of the first and
returns the matching cursor into the searched string. The two explicit inner
termination cases distinguish searched-text exhaustion from simultaneous
pattern completion and preserve the native byte lifetimes without synthetic
state.

Android and iOS preserve `Rstrfind(char*, char*)` in `RString.o`, the same
argument ownership, calls through `RstrASC`, and the same returned searched
cursor. Parser callsites independently confirm those roles.
