#ifndef SNAIL_WIN32_MIN_H
#define SNAIL_WIN32_MIN_H

/* Minimal Win32 and COM base types for Binary Ninja header import. */

#define WINAPI
#define CALLBACK
#define STDMETHODCALLTYPE

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

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
typedef HANDLE HMONITOR;
typedef unsigned int ULONG_PTR;
typedef unsigned int DWORD_PTR;
typedef long long LONGLONG;
typedef unsigned long long ULONGLONG;
typedef ULONGLONG QWORD;

typedef struct GUID {
    DWORD Data1;
    WORD Data2;
    WORD Data3;
    BYTE Data4[8];
} GUID;

typedef const GUID *REFGUID;
typedef REFGUID REFIID;
typedef GUID IID;
typedef IID CLSID;

typedef struct RECT {
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
} RECT;

typedef struct POINT {
    LONG x;
    LONG y;
} POINT;

typedef struct IUnknownVtbl IUnknownVtbl;
typedef struct IUnknown IUnknown;

struct IUnknownVtbl {
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(IUnknown *self, REFIID riid, void **out_object);
    ULONG (STDMETHODCALLTYPE *AddRef)(IUnknown *self);
    ULONG (STDMETHODCALLTYPE *Release)(IUnknown *self);
};

struct IUnknown {
    IUnknownVtbl *lpVtbl;
};

#endif
