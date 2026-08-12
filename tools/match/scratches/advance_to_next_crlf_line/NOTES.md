# Rstrnewline

Exact at 22/22 instructions with no masked operands. It finds the next CRLF
pair and returns its following byte, or null when no following non-empty line
exists. This is distinct from the LF-oriented `RTextNewLine(char**)` cursor
mutator.

Android and iOS preserve `Rstrnewline(char*)` in `RString.o`. The redundant
inner NUL guard is retained because VC6 carries the outer test flags across the
linefeed load and emits the native duplicate zero check.
