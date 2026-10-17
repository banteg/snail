// Shared DatBuild.o functions, partial. iOS DatBuild.cpp defines LoadFile,
// SaveFile and DatBuild().
#ifndef DATBUILD_H
#define DATBUILD_H

#include <stdio.h>

char file_exists(char* path); // @ 0x405140
int get_stream_length_preserve_position(FILE* file); // @ 0x405170
void* load_file_bytes_allocating(char* file_name, int* out_size); // @ 0x4051b0
void scramble_archive_bytes_in_place(void* buffer, int size); // @ 0x405270
int save_file_bytes_with_optional_archive_scramble(
    char* file_name, void* bytes, int byte_count, char should_scramble); // @ 0x4052a0
void delete_file_path(char* path); // @ 0x405340

#endif
