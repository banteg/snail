// load_config_file @ 0x42f470 (cdecl)

void* load_file_bytes_from_path(char* file_name, void* buffer, int* out_size, int element_count);

void* load_config_file(char* file_name, void* buffer)
{
    return load_file_bytes_from_path(file_name, buffer, 0, 0);
}
