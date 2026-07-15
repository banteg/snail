// enumerate_input_controllers @ 0x44b3c0 (cdecl)

#include "direct_input_view.h"
#include "win32_window_state.h"

extern "C" __declspec(dllimport) HMODULE __stdcall GetModuleHandleA(char* module_name);
extern "C" int __stdcall DirectInput8Create(
    HINSTANCE module,
    unsigned int version,
    const DirectInputGuid* iid,
    DirectInput** out_input,
    void* outer_unknown);

int __stdcall append_enumerated_input_controller_callback(
    DIDEVICEINSTANCEA* instance,
    void* context);
int __stdcall configure_input_controller_axis_range_callback(
    DIDEVICEOBJECTINSTANCEA* instance,
    void* context);

extern DirectInputGuid g_directinput8_iid; // data_49b0c0
extern DIDATAFORMAT g_directinput_joystick_data_format; // data_49b2fc

int enumerate_input_controllers(HWND hwnd, int* out_count)
{
    g_joystick_count = 0;
    *out_count = 0;

    int result = DirectInput8Create(
        GetModuleHandleA(0),
        0x800,
        &g_directinput8_iid,
        &g_joystick_input,
        0);
    if (result >= 0) {
        result = g_joystick_input->EnumDevices(
            4,
            append_enumerated_input_controller_callback,
            0,
            1);
        if (result >= 0) {
            *out_count = g_joystick_count;
            int index;
            if (g_joystick_devices[0] != 0 && (index = 0, g_joystick_count > 0)) {
                DirectInputDevice** device_ref = g_joystick_devices;
                while (1) {
                    result = (*device_ref)->SetDataFormat(&g_directinput_joystick_data_format);
                    if (result < 0)
                        return result;
                    result = (*device_ref)->SetCooperativeLevel(hwnd, 5);
                    if (result < 0)
                        return result;
                    result = (*device_ref)->EnumObjects(
                        configure_input_controller_axis_range_callback,
                        (void*)hwnd,
                        0);
                    if (result < 0)
                        return result;

                    ++index;
                    ++device_ref;
                    if (index >= g_joystick_count)
                        return 0;
                }
            } else {
                return 0;
            }
        }
    }
    return result;
}
