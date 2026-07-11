// initialize_keyboard_input @ 0x44b7d0 (cdecl)

#include "direct_input_view.h"
#include "win32_window_state.h"

extern "C" __declspec(dllimport) int __stdcall GetWindowLongA(HWND hwnd, int index);
extern "C" __declspec(dllimport) HMODULE __stdcall GetModuleHandleA(char* module_name);
extern "C" int __stdcall DirectInput8Create(
    HINSTANCE module,
    unsigned int version,
    void* iid,
    DirectInput** out_input,
    void* outer_unknown);
extern "C" void* memset(void* destination, int value, unsigned int count);

void release_input_controllers();

extern DirectInput* g_keyboard_input; // data_777d4c
extern DirectInputDevice* g_keyboard_device; // data_777d50
extern unsigned char g_keyboard_previous_state[0x100]; // data_777b4c
extern unsigned char g_keyboard_current_state[0x100]; // data_777c4c
extern char g_directinput8_iid; // data_49b0c0
extern char g_directinput_keyboard_guid; // data_49b010
extern char g_directinput_keyboard_data_format; // data_49b504

int initialize_keyboard_input(HWND hwnd)
{
    GetWindowLongA(hwnd, -6);
    release_input_controllers();

    int result = DirectInput8Create(
        GetModuleHandleA(0),
        0x800,
        &g_directinput8_iid,
        &g_keyboard_input,
        0);
    if (result >= 0) {
        result = g_keyboard_input->CreateDevice(
            &g_directinput_keyboard_guid,
            &g_keyboard_device,
            0);
        if (result >= 0) {
            result = g_keyboard_device->SetDataFormat(&g_directinput_keyboard_data_format);
            if (result >= 0) {
                result = g_keyboard_device->SetCooperativeLevel(hwnd, 5);
                if (result >= 0) {
                    g_keyboard_device->Acquire();
                    memset(g_keyboard_previous_state, 0, 0x100);
                    memset(g_keyboard_current_state, 0, 0x100);
                    return 0;
                }
            }
        }
    }
    return result;
}
