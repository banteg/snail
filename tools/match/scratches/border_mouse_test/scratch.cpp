// cRBorder::MouseTest() / border_mouse_test @ 0x404580

#include "frontend_widget.h"
#include "game_root.h"
#include "tga_image_view.h"

extern SpriteManager g_sprite_manager; // data_790f30

unsigned char FrontendWidget::border_mouse_test()
{
    MouseCursorState* mouse = &g_game->players[0].mouse_cursor;

    if (texture_hit_test_enabled) {
        float texture_right = texture_hit_width;
        texture_right += texture_hit_x;
        float texture_bottom = texture_hit_height;
        texture_bottom += texture_hit_y;
        if (mouse->saved_x >= texture_hit_x
            && texture_right > mouse->saved_x
            && mouse->saved_y >= texture_hit_y
            && texture_bottom > mouse->saved_y) {
            float u = texture_hit_x;
            u = (mouse->saved_x - u) / texture_hit_width;
            float v = texture_hit_y;
            v = (mouse->saved_y - v) / texture_hit_height;
            TgaImageView* mask =
                g_sprite_manager.get_sprite_tga(texture_hit_test_sprite);

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
    } else if (layout_x - target_padding < mouse->saved_x
        && layout_width + target_padding + layout_x > mouse->saved_x
        && layout_y - target_padding < mouse->saved_y
        && layout_height + target_padding + layout_y > mouse->saved_y) {
        return 1;
    }

    return 0;
}
