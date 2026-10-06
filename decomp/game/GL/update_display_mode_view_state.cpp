// update_display_mode_view_state @ 0x412940 (thiscall)

#include "display_mode_state.h"

float get_authored_view_width();  // @ 0x433030
float get_authored_view_height(); // @ 0x433040

char DisplayModeState::update_display_mode_view_state()
{
    if (current_mode == 0) {
        return 0;
    }

    get_authored_view_width();
    get_authored_view_height();
    int previous_probe_count = probe_count;

    float x;
    float height;
    float width;
    float y;
    while (1) {
        if (read_next_display_mode_view_sample(&x, &y, &width, &height) == 0)
            break;
        int bottom = (int)(y + height);
        int mode_height = current_mode->height;
        y = (float)(mode_height - bottom);

        if (probe_count != previous_probe_count)
            break;
    }

    return 1;
}
