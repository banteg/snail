#ifndef SNAIL_RTEXT_H
#define SNAIL_RTEXT_H

// Android and iOS preserve these authored RShell.o names in the same
// contiguous order as the exact Windows bodies.
void __cdecl RTextCopy(char* destination, char* source);
bool __cdecl RTextCompStart(char* left, char* prefix);
void __cdecl RTextNewLine(char** cursor);
void __cdecl RTextAppend(char* destination, char* source);
void __cdecl RTextExtractString(char** cursor, char* out);
int __cdecl RTextExtractInt(char** cursor);
float __cdecl RTextExtractFloat(char** cursor);

#endif
