// galaxy_border_bound @ 0x40a0c0 (thiscall member helper, ret 0x14)

#include "frontend_widget.h"

class GalaxyRoute {
public:
    void galaxy_border_bound(
        float* min_x,
        float* max_x,
        float* min_y,
        float* max_y,
        FrontendWidget* widget);
};

void GalaxyRoute::galaxy_border_bound(
    float* min_x,
    float* max_x,
    float* min_y,
    float* max_y,
    FrontendWidget* widget)
{
    if (widget->layout_mode == 2) {
        float current_width = *max_x - *min_x;
        if (current_width < widget->layout_width) {
            *min_x -= (widget->layout_width - current_width) * 0.5f;
            float width = widget->layout_width;
            *min_x += (width - (*max_x - *min_x)) * 0.5f;
        }
    } else {
        if (widget->layout_x < *min_x) {
            *min_x = widget->layout_x;
        }
        float max_widget_x = widget->layout_width + widget->layout_x;
        if (max_widget_x > *max_x) {
            *max_x = max_widget_x;
        }
    }

    if (widget->layout_y < *min_y) {
        *min_y = widget->layout_y;
    }
    float max_widget_y = widget->layout_height + widget->layout_y;
    if (max_widget_y > *max_y) {
        *max_y = max_widget_y;
    }
}
