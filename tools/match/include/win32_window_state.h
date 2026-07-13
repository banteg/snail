// Shared 32-bit Win32 window ABI and process-owned window state.
#ifndef WIN32_WINDOW_STATE_H
#define WIN32_WINDOW_STATE_H

#include "rect.h"

typedef int BOOL;
typedef int HWND;
typedef int HDC;
typedef int HINSTANCE;
typedef int HICON;
typedef int HCURSOR;
typedef int HBRUSH;
typedef int HMENU;
typedef int HMODULE;
typedef int LONG;
typedef unsigned int UINT;
typedef unsigned int WPARAM;
typedef int LPARAM;
typedef int LRESULT;
typedef unsigned short ATOM;

typedef LRESULT (__stdcall* WindowProc)(
    HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

struct WndClassA {
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
};

typedef char WndClassA_must_be_0x28[(sizeof(WndClassA) == 0x28) ? 1 : -1];

struct DevModeA {
    char device_name[32];
    unsigned short spec_version;
    unsigned short driver_version;
    unsigned short size;
    unsigned short driver_extra;
    unsigned int fields;
    char unknown_02c[0x68 - 0x2c];
    unsigned int bits_per_pel;
    unsigned int pels_width;
    unsigned int pels_height;
    char unknown_074[0x9c - 0x74];
};

typedef char DevModeA_must_be_0x9c[(sizeof(DevModeA) == 0x9c) ? 1 : -1];

struct WindowMessage {
    HWND hwnd;
    UINT message;
    WPARAM wparam;
    LPARAM lparam;
    unsigned int time;
    int point_x;
    int point_y;
};

typedef char WindowMessage_must_be_0x1c[
    (sizeof(WindowMessage) == 0x1c) ? 1 : -1];

// WinMain saves this instance for the separately registered BASS window.
extern HINSTANCE g_application_instance; // data_4dfad8

extern HDC g_main_window_dc; // data_4dfaec
extern HWND g_main_window; // data_4dfaf0
extern unsigned char g_fullscreen_active; // data_4dfaf4
extern HWND g_bass_window; // data_4dfaf8

// The main-window module keeps its own cached instance in the renderer globals.
extern HINSTANCE g_game_window_instance; // data_50327c
extern Rect g_saved_window_rect; // data_503268
extern unsigned char g_saved_window_rect_valid; // data_503278

#endif
