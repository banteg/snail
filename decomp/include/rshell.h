// Shared RShell.o accessors, partial.
#ifndef RSHELL_H
#define RSHELL_H

// iOS RShellMemoryScratch / RShellMemoryScratch2: the two 2 MiB halves of the
// transient shell workspace. Mobile callers cast the result to the view they
// need, so it is untyped here too.
void* get_archive_data_base(); // @ 0x431a90
void* get_archive_data_end(); // @ 0x431aa0

// Read a file from the game data archive, or from disk when no archive is
// loaded. A null buffer allocates one; out_size may be null.
char* load_file_bytes_fixed_size_from_archive_or_fs(
    char* file_name, char* buffer, int byte_count); // @ 0x431030
char* load_file_bytes_from_archive_or_fs(
    char* file_name, char* buffer, int* out_size); // @ 0x4312d0

#endif
