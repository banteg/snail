/* Port compatibility for the MSVC <io.h> directory search the recovered file
   enumeration falls back to. Implemented in shell/files.cpp over dirent. */
#ifndef SNAIL_PORT_COMPAT_IO_H
#define SNAIL_PORT_COMPAT_IO_H
#ifdef __cplusplus
extern "C" {
#endif
struct _finddata_t {
    unsigned attrib;
    long time_create;
    long time_access;
    long time_write;
    unsigned long size;
    char name[260];
};
long _findfirst(const char* pattern, struct _finddata_t* data);
int _findnext(long handle, struct _finddata_t* data);
int _findclose(long handle);
#ifdef __cplusplus
}
#endif
#endif
