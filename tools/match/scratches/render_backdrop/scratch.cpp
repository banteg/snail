// render_backdrop @ 0x411040 (thiscall, ret)
// Draws the active single-texture backdrop through the 7x7 distortion grid.

#define BACKDROP_RENDER_BACKDROP_RETURNS_VOID
#include "backdrop.h"
#include "font_system.h"

void Backdrop::render_backdrop()
{
    enum {
        GRID_COLUMN_COUNT = sizeof(distort_grid[0]) / sizeof(distort_grid[0][0]),
        GRID_QUAD_COUNT = GRID_COLUMN_COUNT - 1,
    };

    tColour normal_color;
    tColour flipped_color;

    float row = 0.0f;
    do {
        float column = 0.0f;
        do {
            int row_index = (int)row;
            int column_index = (int)column;
            unsigned char flip = active_flip;
            int cell_index = row_index + column_index * GRID_COLUMN_COUNT;
            float* cell = (float*)this + cell_index * 6;
            float next_column;

            if (flip == 0) {
                next_column = column + 1.0f;
                float next_row = row + 1.0f;
                float left_x = row * 91.4285736f;
                float right_y = next_column * 68.5714264f;
                float right_x = next_row * 91.4285736f;
                float left_y = column * 68.5714264f;
                queue_textured_quad_corners(
                    active_primary_texture_id,
                    left_x + cell[26],
                    left_y + cell[27],
                    right_x + cell[32],
                    left_y + cell[33],
                    right_x + cell[80],
                    right_y + cell[81],
                    left_x + cell[74],
                    right_y + cell[75],
                    0,
                    0,
                    0x8000000,
                    normal_color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                    row * 0.0892857164f,
                    column * 0.133928567f,
                    next_row * 0.0892857164f,
                    next_column * 0.133928567f,
                    0,
                    0);
            } else {
                next_column = column + 1.0f;
                float next_row = row + 1.0f;
                float left_x = row * 91.4285736f;
                float right_y = next_column * 68.5714264f;
                float right_x = next_row * 91.4285736f;
                float left_y = column * 68.5714264f;
                queue_textured_quad_corners(
                    active_primary_texture_id,
                    left_x + cell[26],
                    left_y + cell[27],
                    right_x + cell[32],
                    left_y + cell[33],
                    right_x + cell[80],
                    right_y + cell[81],
                    left_x + cell[74],
                    right_y + cell[75],
                    0,
                    0,
                    0x8000000,
                    flipped_color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                    0.800000012f - row * 0.0892857164f,
                    column * 0.133928567f,
                    0.800000012f - next_row * 0.0892857164f,
                    next_column * 0.133928567f,
                    0,
                    0);
            }

            column = next_column;
        } while (column < GRID_QUAD_COUNT);

        row += 1.0f;
    } while (row < GRID_QUAD_COUNT);
}
