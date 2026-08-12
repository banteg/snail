# RTextAppend

Exact at 19/19 instructions with no masked operands. It scans to the
destination NUL, appends the source bytes, and writes the final terminator.

Android and iOS preserve the void `RTextAppend(char*, char*)` contract in the
contiguous `RShell.o` RText family. Mobile `ObjectTextLoad` performs the same
extension, separator, and texture-name appends as Windows
`load_object_definition`; all three Windows calls discard EAX.
