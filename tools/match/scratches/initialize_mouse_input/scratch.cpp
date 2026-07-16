// initialize_mouse_input @ 0x44c310 (cdecl)

#include "direct_input_view.h"
#include "mouse_input_state.h"
#include "win32_window_state.h"

extern "C" __declspec(dllimport) HMODULE __stdcall GetModuleHandleA(char* module_name);
extern "C" int __stdcall DirectInput8Create(
    HINSTANCE module,
    unsigned int version,
    const DirectInputGuid* iid,
    DirectInput** out_input,
    void* outer_unknown);

extern float g_authored_view_width; // data_4df85c
extern float g_authored_view_height; // data_4b7760

int initialize_mouse_input(HWND hwnd)
{
    float mouse_x = g_authored_view_width * 0.5f;
    float mouse_y = g_authored_view_height * 0.5f;
    g_mouse_live_x[0] = mouse_x;
    g_hide_system_cursor_flag = 1;
    g_mouse_live_y[0] = mouse_y;

    int result = DirectInput8Create(
        GetModuleHandleA(0),
        0x800,
        &g_directinput8_iid,
        &g_mouse_input,
        0);
    if (result >= 0) {
        result = g_mouse_input->CreateDevice(
            &g_directinput_mouse_guid,
            &g_mouse_device,
            0);
        if (result >= 0) {
            result = g_mouse_device->SetDataFormat(&g_directinput_mouse_data_format);
            if (result >= 0) {
                g_mouse_device->SetCooperativeLevel(hwnd, 4);
                g_mouse_device->Acquire();
                return 0;
            }
        }
    }
    return result;
}
