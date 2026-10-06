// update_backdrop @ 0x4112f0

#include "backdrop.h"

float Sin(float radians); // @ 0x44c9d0
float Cos(float radians); // @ 0x44c980

int cRBackdrop::update_backdrop()
{
    enum {
        GRID_ROW_COUNT = sizeof(distort_grid) / sizeof(distort_grid[0]),
        GRID_COLUMN_COUNT = sizeof(distort_grid[0]) / sizeof(distort_grid[0][0]),
    };

    if (backdrop_change_queued != 0) {
        ChangeReal();
        backdrop_change_queued = 0;
    }

    for (int column_index = 0; column_index < GRID_COLUMN_COUNT; ++column_index) {
        for (int row_index = 0; row_index < GRID_ROW_COUNT; ++row_index) {
            distort_grid[row_index][column_index].phase =
                    distort_grid[row_index][column_index].phase_step
                    + distort_grid[row_index][column_index].phase;
            if (distort_grid[row_index][column_index].phase > 6.28318548f) {
                distort_grid[row_index][column_index].phase =
                    distort_grid[row_index][column_index].phase - 6.28318548f;
            }
            distort_grid[row_index][column_index].current_x_offset =
                Sin(distort_grid[row_index][column_index].phase)
                * distort_grid[row_index][column_index].x_offset;
            distort_grid[row_index][column_index].current_y_offset =
                Cos(distort_grid[row_index][column_index].phase)
                * distort_grid[row_index][column_index].y_offset;
        }
    }

    int result = active_primary_texture_id;
    if (result != -1) {
        result = backdrop_render_enabled;
        result--;
        if (result == 0) {
            if (active_split_backdrop_pair != 0) {
                return draw_split_backdrop();
            }
            return render_backdrop();
        }
    }
    return result;
}
