// set_current_directory_with_drive_fallback @ 0x430f30 (cdecl)

#include <direct.h>

#include "rerror.h"

extern char g_blank_text[];

int __cdecl set_current_directory_with_drive_fallback(char* path)
{
    char drive_root[4];
    char current_directory[256];

    if (path != g_blank_text) {
        if (path[1] == ':') {
            drive_root[0] = path[0];
            drive_root[1] = ':';
            drive_root[2] = '\\';
            drive_root[3] = 0;
            chdir(drive_root);

            if (path[2] == 0) {
                goto success;
            }
            if (path[3] == 0) {
                goto success;
            }

            path += 3;
        }

        if (chdir(path) != 0) {
            getcwd(current_directory, 256);
            report_messagef("ERROR: cannot find directory %s (from %s)\n", path, current_directory);
            return 1;
        }
    }

success:
    return 0;
}
