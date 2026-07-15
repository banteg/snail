// set_backdrop_distort @ 0x410c40 (thiscall, ret 0x4)
// Seeds the backdrop distortion grid from the script Distort scalar.

#include "backdrop.h"

int next_math_random_value(); // @ 0x44c900

void Backdrop::set_backdrop_distort(float distort)
{
    enum {
        GRID_ROW_COUNT = sizeof(distort_grid) / sizeof(distort_grid[0]),
        GRID_COLUMN_COUNT = sizeof(distort_grid[0]) / sizeof(distort_grid[0][0]),
        GRID_LAST_COLUMN = GRID_COLUMN_COUNT - 1,
        GRID_LAST_ROW = GRID_ROW_COUNT - 1,
    };

    int i;
    int j;
    int interior;
    for (i = 0; i < GRID_ROW_COUNT; i++) {
        for (j = 0; j < GRID_COLUMN_COUNT; j++) {
            interior =
                j != 0 && i != 0 && j != GRID_LAST_COLUMN && i != GRID_LAST_ROW;
            if (interior) {
                distort_grid[i][j].phase =
                    (float)next_math_random_value() * 0.000191747604f;
                distort_grid[i][j].phase_step =
                    (1.0f /
                        (((float)next_math_random_value() * 0.00006103515625f +
                             3.0f) *
                            60.0f)) *
                    6.28318548f;
                distort_grid[i][j].x_offset =
                    ((float)next_math_random_value() - 16384.0f) *
                    distort *
                    0.00006103515625f;
                distort_grid[i][j].y_offset =
                    ((float)next_math_random_value() - 16384.0f) *
                    distort *
                    0.00006103515625f;
            } else {
                distort_grid[i][j].phase = 0.0f;
                distort_grid[i][j].phase_step = 0.0f;
                distort_grid[i][j].x_offset = 0.0f;
                distort_grid[i][j].y_offset = 0.0f;
            }
        }
    }
}
