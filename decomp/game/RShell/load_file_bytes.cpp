// load_file_bytes @ 0x431520 (cdecl)

void* load_file_bytes_from_archive_or_fs(char* file_name, void* buffer, int* out_size);

void* load_file_bytes(char* file_name, int* out_size)
{
    return load_file_bytes_from_archive_or_fs(file_name, 0, out_size);
}
