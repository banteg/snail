#ifndef SNAIL_RSTRING_H
#define SNAIL_RSTRING_H

// Android and iOS preserve these authored RString.o names in the same
// contiguous order as the exact Windows bodies.
char __cdecl RstrASC(char value);
void __cdecl Rstrcpy(char* destination, const char* source);
char* __cdecl Rstrfind(char* pattern, char* searched);
char* __cdecl Rstrnewline(char* cursor);
// Windows returns a full int here; both mobile decompilers render the same
// strict-equality result as bool, but importing that ABI changes VC6 codegen.
int __cdecl Rstrcmp(char* left, char* right);
int __cdecl Rstrint(char** cursor);

#endif
