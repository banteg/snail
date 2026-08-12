# RTextCopy

Exact at 10/10 instructions with no masked operands. The post-increment source
loop preserves the native duplicate byte load while implementing the authored
void `RTextCopy(char*, char*)` contract.

Android and iOS retain this name and body at the head of the contiguous
`RShell.o` RText family. Mobile `ObjectTextLoad` uses it in the same path-copy
role as Windows `load_object_definition`; both Windows callers discard EAX.
