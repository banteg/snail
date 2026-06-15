// resolve_uncaptured_cursor_sensitivity_scale @ 0x44bc20 (cdecl)

extern char* g_game_base; // data_4df904

class MouseCursorState {
public:
    unsigned char is_mouse_captured();
};

float resolve_uncaptured_cursor_sensitivity_scale(float scale)
{
    if (((MouseCursorState*)(g_game_base + 0x290))->is_mouse_captured())
        return 1.0f;
    return scale * 1.79999995f + 0.699999988f;
}
