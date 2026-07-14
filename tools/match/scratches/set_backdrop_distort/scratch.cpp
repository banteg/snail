// set_backdrop_distort @ 0x410c40 (thiscall, ret 0x4)
// Seeds the backdrop distortion grid from the script Distort scalar.

#include "backdrop.h"

int next_math_random_value(); // @ 0x44c900

void Backdrop::set_backdrop_distort(float distort)
{
    enum {
        GRID_ROW_COUNT = sizeof(distort_grid) / sizeof(distort_grid[0]),
        GRID_COLUMN_COUNT = sizeof(distort_grid[0]) / sizeof(distort_grid[0][0]),
        GRID_CELL_COUNT = sizeof(distort_cells) / sizeof(distort_cells[0]),
        GRID_LAST_COLUMN = GRID_COLUMN_COUNT - 1,
        GRID_LAST_ROW_BASE = (GRID_ROW_COUNT - 1) * GRID_COLUMN_COUNT,
    };

    int i;
    int j;
    int border;
    float* result;
    float* cell;

    for (i = 0; i < GRID_CELL_COUNT; i += GRID_COLUMN_COUNT) {
        for (j = 0; j < GRID_COLUMN_COUNT; j++) {
            border =
                j == 0 || i == 0 || j == GRID_LAST_COLUMN || i == GRID_LAST_ROW_BASE;
            if (border) {
                result = (float*)this + (i + j) * 6;
                result[22] = 0.0f;
                result[23] = 0.0f;
                *((float*)this + (i + j + 4) * 6) = 0.0f;
                result[25] = 0.0f;
            } else {
                cell = (float*)this + (i + j) * 6;
                cell[22] =
                    (float)next_math_random_value() * 0.000191747604f;
                cell[23] =
                    (1.0f /
                        (((float)next_math_random_value() * 0.00006103515625f +
                             3.0f) *
                            60.0f)) *
                    6.28318548f;
                *((float*)this + (i + j + 4) * 6) =
                    ((float)next_math_random_value() - 16384.0f) *
                    distort *
                    0.00006103515625f;
                cell[25] =
                    ((float)next_math_random_value() - 16384.0f) *
                    distort *
                    0.00006103515625f;
            }
        }
    }
}
