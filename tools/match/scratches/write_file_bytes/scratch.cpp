// write_file_bytes @ 0x431650 (cdecl)

typedef struct File File;

#ifdef __cplusplus
extern "C" {
#endif
File* __cdecl fopen(char* path, char* mode);
int __cdecl fclose(File* file);
unsigned int __cdecl fwrite(void* buffer, unsigned int element_size, unsigned int element_count, File* file);
char* __cdecl getcwd(char* buffer, int size);
int __cdecl chdir(char* path);
#ifdef __cplusplus
}
#endif

int report_messagef(char* format, ...);
int set_current_directory_with_drive_fallback(char* path);

int __cdecl write_file_bytes(char* path, void* bytes, int byte_count)
{
    char path_part[256];
    char current_directory[512];
    char original_directory[512];
    char* cursor;
    int index;
    char c;
    File* file;

    getcwd(original_directory, 512);
    cursor = path;

    do {
        c = *cursor;
        index = 0;
        while (c != 0) {
            if (c == '/') {
                break;
            }
            if (c == '\\') {
                break;
            }
            path_part[index] = c;
            c = cursor[1];
            ++index;
            ++cursor;
        }

        c = *cursor;
        if (c == '/' || c == '\\') {
            path_part[index] = 0;
            set_current_directory_with_drive_fallback(path_part);
            ++cursor;
        }
    } while (*cursor != 0);

    path_part[index] = 0;
    file = fopen(path_part, "wb");
    if (file == 0) {
        getcwd(current_directory, 512);
        report_messagef("ERROR:Cannot save file : %s (from %s)\n", path_part, current_directory);
    } else {
        fwrite(bytes, 1, byte_count, file);
        fclose(file);
    }

    return chdir(original_directory);
}
