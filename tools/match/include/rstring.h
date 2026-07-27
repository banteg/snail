#ifndef SNAIL_RSTRING_H
#define SNAIL_RSTRING_H

// Stable Windows harness names for the authored RString.o helper family.
// Android and iOS preserve the original names and the same contiguous order.
char __cdecl ascii_upper_if_lowercase(char value); // RstrASC
void __cdecl rstrcpy_checked_ascii(
    char* destination, const char* source); // Rstrcpy
char* __cdecl find_case_insensitive_substring(
    char* pattern, char* searched); // Rstrfind
char* __cdecl advance_to_next_crlf_line(char* cursor); // Rstrnewline
// Windows returns a full int here; both mobile decompilers render the same
// strict-equality result as bool, but importing that ABI changes VC6 codegen.
int __cdecl strings_equal_case_insensitive_path(
    char* left, char* right); // Rstrcmp
int __cdecl parse_next_signed_int(char** cursor); // Rstrint

#endif
