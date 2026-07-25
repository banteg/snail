#ifndef SNAIL_WIN32_WINDOW_STATE_TYPES_H
#define SNAIL_WIN32_WINDOW_STATE_TYPES_H

/*
 * Recovered 32-bit Win32 window ABI used by the startup/input and renderer
 * reset paths. Handles are pointer-sized process tokens in the original
 * program; the target is 32-bit, so the explicit aliases remain four bytes.
 */
typedef int BOOL;
typedef int HWND;
typedef int HDC;
typedef int HINSTANCE;
typedef int HICON;
typedef int HCURSOR;
typedef int HBRUSH;
typedef int HMENU;
typedef int LRESULT;
typedef unsigned int UINT;
typedef unsigned int WPARAM;
typedef int LPARAM;

typedef LRESULT (__stdcall* WindowProc)(
    HWND hwnd,
    UINT message,
    WPARAM wparam,
    LPARAM lparam);

typedef struct Rect {
    int left;
    int top;
    int right;
    int bottom;
} Rect;

typedef struct WndClassA {
    UINT style;
    WindowProc wnd_proc;
    int cls_extra;
    int wnd_extra;
    HINSTANCE instance;
    HICON icon;
    HCURSOR cursor;
    HBRUSH background;
    char* menu_name;
    char* class_name;
} WndClassA;

typedef struct DevModeA {
    char device_name[32];
    unsigned short spec_version;
    unsigned short driver_version;
    unsigned short size;
    unsigned short driver_extra;
    unsigned int fields;
    unsigned char unknown_02c[0x68 - 0x2c];
    unsigned int bits_per_pel;
    unsigned int pels_width;
    unsigned int pels_height;
    unsigned char unknown_074[0x9c - 0x74];
} DevModeA;

typedef char Rect_must_be_0x10[(sizeof(Rect) == 0x10) ? 1 : -1];
typedef char WndClassA_must_be_0x28[(sizeof(WndClassA) == 0x28) ? 1 : -1];
typedef char DevModeA_must_be_0x9c[(sizeof(DevModeA) == 0x9c) ? 1 : -1];

int __cdecl initialize_game_window_and_input(char* window_name);
int __cdecl enumerate_input_controllers(HWND window, int* out_count);
LRESULT __stdcall game_window_proc(
    HWND hwnd,
    UINT message,
    WPARAM wparam,
    LPARAM lparam);

extern int g_controller_count_view;

extern HDC g_main_window_dc;
extern HWND g_main_window;
extern unsigned char g_fullscreen_active;
extern HWND g_bass_window;

extern Rect g_saved_window_rect;
extern unsigned char g_saved_window_rect_valid;
extern HINSTANCE g_game_window_instance;

#endif
