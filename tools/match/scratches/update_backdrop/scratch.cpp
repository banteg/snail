// update_backdrop @ 0x4112f0

#include "backdrop.h"

float sine(float radians); // @ 0x44c9d0
float cosine(float radians); // @ 0x44c980

int Backdrop::update_backdrop()
{
    float phase;
    int phase_bits;

    if (backdrop_change_queued != 0) {
        change_backdrop_real();
        backdrop_change_queued = 0;
    }

    BackdropDistortCell* column = distort_cells;
    int column_count = 8;
    do {
        BackdropDistortCell* cell = column;
        int row_count = 8;
        do {
            phase = cell->phase_step;
            phase += cell->phase;
            phase_bits = *(int*)&phase;
            *(int*)&cell->phase = phase_bits;
            phase = *(float*)&phase_bits;
            if (phase > 6.28318548f) {
                cell->phase = phase - 6.28318548f;
            }

            cell->current_x_offset = sine(cell->phase) * cell->x_offset;
            cell->current_y_offset = cosine(cell->phase) * cell->y_offset;
            cell += 8;
            row_count--;
        } while (row_count != 0);

        ++column;
        column_count--;
    } while (column_count != 0);

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
