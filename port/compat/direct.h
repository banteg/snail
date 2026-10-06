/* Port compatibility for the MSVC <direct.h> calls the recovered file code makes. */
#ifndef SNAIL_PORT_COMPAT_DIRECT_H
#define SNAIL_PORT_COMPAT_DIRECT_H
#include <unistd.h>

static inline char* _getcwd(char* buffer, int size) { return getcwd(buffer, (size_t)size); }
static inline int _chdir(const char* path) { return chdir(path); }
#endif
