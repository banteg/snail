// delete_file_path_with_directory_walk @ 0x431540 (cdecl)

#include <direct.h>
#include <stdio.h>

int report_messagef(char* format, ...);
int set_current_directory_with_drive_fallback(char* path);

int __cdecl delete_file_path_with_directory_walk(char* path)
{
    char path_part[256];
    char current_directory[512];
    char original_directory[512];
    char* cursor;
    int index;
    char c;
    FILE* file;

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
        report_messagef("ERROR:Cannot delete file : %s (from %s)\n", path_part, current_directory);
    } else {
        report_messagef("*Deleting file* :%s\n", path_part);
        fclose(file);
        if (remove(path_part) == -1) {
            report_messagef("ERROR:Cannot delete file : %s (from %s)\n", path_part, current_directory);
        }
    }

    return chdir(original_directory);
}
