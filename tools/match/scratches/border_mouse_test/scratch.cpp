// border_mouse_test @ 0x404580 (thiscall-shaped fastcall)

#include "frontend_widget.h"
#include "mouse_cursor_state.h"

struct TextureHitMask {
    char unknown_00[0x0c];
    unsigned short width;
    unsigned short height;
    char unknown_10[0x12 - 0x10];
    unsigned char pixels[1];
};

extern char* g_game_base; // data_4df904
extern SpriteManager g_sprite_manager; // data_790f30

unsigned char __fastcall border_mouse_test(FrontendWidget* widget)
{
    MouseCursorState* mouse = (MouseCursorState*)(g_game_base + 0x290);

    if (widget->texture_hit_test_enabled) {
        float texture_right = widget->texture_hit_width;
        texture_right += widget->texture_hit_x;
        float texture_bottom = widget->texture_hit_height;
        texture_bottom += widget->texture_hit_y;
        if (mouse->saved_x >= widget->texture_hit_x
            && texture_right > mouse->saved_x
            && mouse->saved_y >= widget->texture_hit_y
            && texture_bottom > mouse->saved_y) {
            float u = widget->texture_hit_x;
            u = (mouse->saved_x - u) / widget->texture_hit_width;
            float v = widget->texture_hit_y;
            v = (mouse->saved_y - v) / widget->texture_hit_height;
            TextureHitMask* mask =
                (TextureHitMask*)g_sprite_manager.get_sprite_texture_ref(
                    widget->texture_hit_test_sprite);

            int width = mask->width;
            int x = (int)((float)width * u);
            int height = mask->height;
            int y = (int)((float)height * v);

            if (x < 0) {
                x = 0;
            } else if (x > width - 1) {
                x = width - 1;
            }

            if (y < 0) {
                y = 0;
            } else if (y > height - 1) {
                y = height - 1;
            }

            int row = width;
            row *= y;
            int pixel_index = row + x + 6;

            if (*((unsigned char*)mask + pixel_index * 3) == 0)
                return 1;
        }
    } else if (widget->layout_x - widget->target_padding < mouse->saved_x
        && widget->layout_width + widget->target_padding + widget->layout_x > mouse->saved_x
        && widget->layout_y - widget->target_padding < mouse->saved_y
        && widget->layout_height + widget->layout_y + widget->target_padding > mouse->saved_y) {
        return 1;
    }

    return 0;
}
