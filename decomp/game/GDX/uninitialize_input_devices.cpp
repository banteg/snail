// uninitialize_input_devices @ 0x411d80 (cdecl, tail return)

#include "direct3d_renderer.h"
#include "input_polling.h"

int uninitialize_input_devices()
{
    release_global_direct3d_renderer_resources();
    release_input_controllers();
    release_keyboard_input();
    return release_mouse_input();
}
