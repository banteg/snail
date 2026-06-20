// read_next_display_mode_view_sample @ 0x407930 (thiscall, ret 0x10)

#include "display_mode_state.h"

char DisplayModeState::read_next_display_mode_view_sample(
    float* x, float* y, float* width, float* height)
{
    if (probe_count < 2) {
        *x = 0.0f;
        *y = 0.0f;

        int mode_width = current_mode->width;
        *width = (float)mode_width;

        int mode_height = current_mode->height;
        *height = (float)mode_height;

        queued_view_sample_count = 0;
        probe_count++;
        return 1;
    }

    if (queued_view_sample_count != 0) {
        queued_view_sample_count--;
        *x = view_samples[queued_view_sample_count].x;
        *y = view_samples[queued_view_sample_count].y;
        *width = view_samples[queued_view_sample_count].width;
        *height = view_samples[queued_view_sample_count].height;
        return 1;
    }

    return 0;
}
