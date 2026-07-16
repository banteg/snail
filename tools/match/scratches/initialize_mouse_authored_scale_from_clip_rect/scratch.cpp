// initialize_mouse_authored_scale_from_clip_rect @ 0x44bbb0 (cdecl)

#include "mouse_input_state.h"

extern "C" __declspec(dllimport) int __stdcall GetClipCursor(Rect* rect);

int update_mouse_authored_scale(float authored_width, float authored_height);

int initialize_mouse_authored_scale_from_clip_rect()
{
    GetClipCursor(&g_mouse_clip_rect);
    return update_mouse_authored_scale(640.0f, 480.0f);
}
