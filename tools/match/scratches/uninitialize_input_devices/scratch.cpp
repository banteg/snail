// uninitialize_input_devices @ 0x411d80 (cdecl, tail return)

int release_global_direct3d_renderer_resources();
void release_input_controllers();
void release_keyboard_input();
int release_mouse_input();

int uninitialize_input_devices()
{
    release_global_direct3d_renderer_resources();
    release_input_controllers();
    release_keyboard_input();
    return release_mouse_input();
}
