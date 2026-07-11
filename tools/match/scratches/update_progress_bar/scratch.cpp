// update_progress_bar @ 0x437c40 (thiscall, ret)
// Queues the left-column gameplay progress-bar HUD quads.

#include "font_system.h"
#include "game_root.h"
#include "progress_bar.h"
#include "sprite.h"

extern GameRoot* g_game; // data_4df904

int queue_axis_aligned_textured_quad_uv(
    int texture_id,
    float x,
    float y,
    float width,
    float height,
    unsigned int flags,
    Color4f* color,
    float u0,
    float v0,
    float u1,
    float v1,
    int layer,
    int blend);

void ProgressBar::update_progress_bar()
{
    GameRoot* game = g_game;
    float progress =
        (game->subgame.embedded_player()->position.z
            - (float)game->subgame.first_block_row_count)
        / ((float)game->subgame.completion_row_start
            - (float)game->subgame.first_block_row_count);
    if (progress < 0.0f) {
        progress = 0.0f;
    } else if (progress > 1.0f) {
        progress = 1.0f;
    }

    float remaining_height = (1.0f - progress) * 232.0f + 12.0f;
    float lit_y = remaining_height + 150.0f;

    Color4f color;
    queue_axis_aligned_textured_quad_uv(
        0x9d,
        12.0f,
        lit_y - 39.0f,
        64.0f,
        64.0f,
        0x1000000,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        0.0f,
        0.0f,
        1.0f,
        1.0f,
        3,
        0);

    float split_v = remaining_height * 0.00390625f;
    queue_axis_aligned_textured_quad_uv(
        0x9b,
        13.0f,
        150.0f,
        64.0f,
        remaining_height,
        0x1000000,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        0.0f,
        0.0f,
        1.0f,
        split_v,
        3,
        0);

    queue_axis_aligned_textured_quad_uv(
        0x9c,
        13.0f,
        lit_y,
        64.0f,
        256.0f - remaining_height,
        0x1000000,
        color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
        0.0f,
        split_v,
        1.0f,
        1.0f,
        3,
        0);
}
