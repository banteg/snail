#ifndef SNAIL_RTEXT_H
#define SNAIL_RTEXT_H

// Stable Windows harness names for the authored RShell.o RText helper family.
// Android and iOS preserve the original names and the same contiguous order.
void __cdecl copy_c_string(char* destination, char* source); // RTextCopy
bool __cdecl strings_equal_case_insensitive(
    char* left, char* prefix); // RTextCompStart
void __cdecl skip_to_next_line(char** cursor); // RTextNewLine
void __cdecl append_c_string(char* destination, char* source); // RTextAppend
void __cdecl parse_next_space_delimited_token(
    char** cursor, char* out); // RTextExtractString
int __cdecl parse_next_int32(char** cursor); // RTextExtractInt
float __cdecl parse_next_float32(char** cursor); // RTextExtractFloat

#endif
