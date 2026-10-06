// load_file_bytes_allocating @ 0x4051b0 (cdecl)

void* load_file_bytes_into_optional_buffer(char* file_name, void* buffer, int* out_size);

void* load_file_bytes_allocating(char* file_name, int* out_size)
{
    return load_file_bytes_into_optional_buffer(file_name, 0, out_size);
}
