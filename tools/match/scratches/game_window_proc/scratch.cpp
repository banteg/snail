// game_window_proc @ 0x4074b0 (stdcall, ret 0x10)

#include "audio_system.h"
#include "display_mode_state.h"
#include "main_loop_state.h"
#include "mouse_input_state.h"
#include "win32_window_state.h"

extern "C" __declspec(dllimport) void __stdcall PostQuitMessage(int exit_code);
extern "C" __declspec(dllimport) LRESULT __stdcall DefWindowProcA(
    HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
extern "C" __declspec(dllimport) unsigned int __stdcall timeGetTime();

extern int debug_report_stub(char* format, ...); // @ 0x449c00
extern int handle_game_window_activate();        // @ 0x4072f0
extern char handle_game_window_deactivate();     // @ 0x407440
extern int restore_desktop_display_mode();       // @ 0x407860

extern DisplayModeState g_display_mode_state;       // data_4df9e0

LRESULT __stdcall game_window_proc(
    HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (message <= 0x200) {
        if (message == 0x200) {
            goto handle_mouse_wheel_delta;
        }

        switch (message) {
            case 0x10:
                PostQuitMessage(0);
                return 0;

            case 0x100:
                if (wparam != 0x1b) {
                    return 0;
                }
                PostQuitMessage(0);
                return 0;

            case 2:
                return 0;

            case 6: {
                unsigned int activate_code = wparam & 0xffff;
                if (activate_code == 0) {
                    g_audio_backend.pause_audio_backend_if_running();
                    debug_report_stub("WM_ACTIVATE INACTIVE\n");
                    handle_game_window_deactivate();
                    return 0;
                }

                if (activate_code == 1) {
                    g_audio_backend.resume_audio_backend_if_paused();
                    debug_report_stub("WM_ACTIVATE ACTIVE\n");
                    handle_game_window_activate();
                }
                return 0;
            }

            case 5:
                if (wparam == 1) {
                    debug_report_stub("WM_MINIMIZED\n");
                    g_audio_backend.pause_audio_backend_if_running();
                    g_window_deactivated = 1;
                    restore_desktop_display_mode();
                    return 0;
                }

                if (wparam == 0) {
                    g_audio_backend.resume_audio_backend_if_paused();
                    g_window_deactivated = 0;
                    g_previous_frame_timestamp_seconds =
                        (float)timeGetTime() * 0.001f;
                    g_display_mode_state.reset_display_mode_probe_count();
                }
                return 0;

            default:
                return DefWindowProcA(hwnd, message, wparam, lparam);
        }
    } else {
        switch (message) {
            case 0x20a:
                goto handle_mouse_wheel_delta;

            case 0x201:
                g_left_mouse_button_latch[0] = 1;
                g_left_mouse_button_state[0] = 1;
                return 0;

            case 0x202:
                g_left_mouse_button_latch[0] = 0;
                g_left_mouse_button_state[0] = 0;
                return 0;

            case 0x204:
                g_right_mouse_button_latch[0] = 1;
                g_right_mouse_button_state[0] = 1;
                return 0;

            case 0x205:
                g_right_mouse_button_latch[0] = 0;
                g_right_mouse_button_state[0] = 0;
                return 0;

            default:
                return DefWindowProcA(hwnd, message, wparam, lparam);
        }
    }

handle_mouse_wheel_delta:
    short wheel_delta = (short)(wparam >> 16);
    if (wheel_delta > 0) {
        g_mouse_wheel_delta[0] = 1;
    } else if (wheel_delta < 0) {
        g_mouse_wheel_delta[0] = -1;
    }
    return 0;
}
