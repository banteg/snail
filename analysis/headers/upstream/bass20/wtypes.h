#ifndef SNAIL_BASS20_WTYPES_H
#define SNAIL_BASS20_WTYPES_H

/*
 * Minimal Win32 shim for importing the official BASS 2.0 `bass.h` into
 * Binary Ninja. The upstream header only needs a small subset of `wtypes.h`.
 */

#define WINAPI
#define CALLBACK

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef int BOOL;
typedef int INT;
typedef unsigned int UINT;
typedef int LONG;
typedef unsigned int ULONG;
typedef LONG HRESULT;
typedef void VOID;
typedef void *LPVOID;
typedef const void *LPCVOID;
typedef char CHAR;
typedef CHAR *LPSTR;
typedef const CHAR *LPCSTR;
typedef void *HANDLE;
typedef HANDLE HMODULE;
typedef HANDLE HWND;
typedef HANDLE HINSTANCE;
typedef unsigned long long ULONGLONG;
typedef ULONGLONG QWORD;

typedef struct GUID {
    DWORD Data1;
    WORD Data2;
    WORD Data3;
    BYTE Data4[8];
} GUID;

#endif
