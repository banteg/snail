// resolve_uncaptured_cursor_sensitivity_scale @ 0x44bc20 (cdecl)

#include "game_root.h"


float resolve_uncaptured_cursor_sensitivity_scale(float scale)
{
    if (g_game->players[0].mouse_cursor.is_mouse_captured())
        return 1.0f;
    return scale * 1.79999995f + 0.699999988f;
}
