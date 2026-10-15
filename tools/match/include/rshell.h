// Shared RShell.o accessors, partial.
#ifndef RSHELL_H
#define RSHELL_H

// iOS RShellMemoryScratch / RShellMemoryScratch2: the two 2 MiB halves of the
// transient shell workspace. Mobile callers cast the result to the view they
// need, so it is untyped here too.
void* get_archive_data_base(); // @ 0x431a90
void* get_archive_data_end(); // @ 0x431aa0

#endif
