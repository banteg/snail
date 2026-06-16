// galaxy_border_bound @ 0x40a0c0 (thiscall member helper, ret 0x14)

class GalaxyWidgetBoundsView {
public:
    char unknown_000[0x238];
    float x; // +0x238
    float y; // +0x23c
    char unknown_240[0x248 - 0x240];
    float width; // +0x248
    float height; // +0x24c
    char unknown_250[0x25c - 0x250];
    int mode; // +0x25c
};

class GalaxyRoute {
public:
    void galaxy_border_bound(
        float* min_x,
        float* max_x,
        float* min_y,
        float* max_y,
        GalaxyWidgetBoundsView* widget);
};

void GalaxyRoute::galaxy_border_bound(
    float* min_x,
    float* max_x,
    float* min_y,
    float* max_y,
    GalaxyWidgetBoundsView* widget)
{
    if (widget->mode == 2) {
        float current_width = *max_x - *min_x;
        if (current_width < widget->width) {
            *min_x -= (widget->width - current_width) * 0.5f;
            float width = widget->width;
            *min_x += (width - (*max_x - *min_x)) * 0.5f;
        }
    } else {
        if (widget->x < *min_x) {
            *min_x = widget->x;
        }
        float max_widget_x = widget->width + widget->x;
        if (max_widget_x > *max_x) {
            *max_x = max_widget_x;
        }
    }

    if (widget->y < *min_y) {
        *min_y = widget->y;
    }
    float max_widget_y = widget->height + widget->y;
    if (max_widget_y > *max_y) {
        *max_y = max_widget_y;
    }
}
