// open_galaxy_route @ 0x409c50 (thiscall, ret 4)

#include "frontend_widget.h"

void __cdecl rstrcpy_checked_ascii(char* destination, char* source);

class GalaxyRouteRecord {
public:
    int route_name_index; // +0x00, indexes route_name_table
    char unknown_004[0x08 - 0x04];
    float map_x; // +0x08
    float map_y; // +0x0c
    char unknown_010[0x1c - 0x10];
    char detail_text[0x80]; // +0x1c
    char description_text[0x2a0 - 0x9c]; // +0x9c
};

class GalaxyRoute {
public:
    FrontendWidget* open_galaxy_route(int selected_level_index);
    void galaxy_border_bound(
        float* min_x,
        float* max_x,
        float* min_y,
        float* max_y,
        FrontendWidget* widget);

    int unknown_000; // +0x00
    int route_mode; // +0x04
    int route_state; // +0x08
    char unknown_00c[0x14 - 0x00c];
    GalaxyRouteRecord records[100]; // +0x14
    char unknown_10694[0x10930 - 0x10694];
    char route_name_table[10][0xa0]; // +0x10930
    char* level_progress_base; // +0x10f70
    char unknown_10f74[0x10f80 - 0x10f74];
    int selected_index; // +0x10f80
    char unknown_10f84[0x10f8c - 0x10f84];
    FrontendWidget* bounds_frame_widget; // +0x10f8c
    FrontendWidget* title_widget; // +0x10f90
    FrontendWidget* detail_widget; // +0x10f94
    FrontendWidget* description_widget; // +0x10f98
    FrontendWidget* back_widget; // +0x10f9c
    FrontendWidget* continue_widget; // +0x10fa0
};

FrontendWidget* GalaxyRoute::open_galaxy_route(int selected_level_index)
{
    route_state = 1;
    selected_index = selected_level_index;

    title_widget->unhide_border_init();
    rstrcpy_checked_ascii(
        title_widget->text_buffer,
        route_name_table[records[selected_index].route_name_index]);
    title_widget->layout_anchor_x = records[selected_index].map_x + 60.0f;
    title_widget->layout_anchor_y = records[selected_index].map_y - 130.0f;

    while (1) {
        title_widget->layout_frontend_widget();

        detail_widget->unhide_border_init();
        rstrcpy_checked_ascii(detail_widget->text_buffer, records[selected_index].detail_text);
        detail_widget->stack_widget_below(title_widget);

        description_widget->unhide_border_init();
        rstrcpy_checked_ascii(description_widget->text_buffer, records[selected_index].description_text);
        description_widget->stack_widget_below(detail_widget);

        back_widget->unhide_border_init();
        back_widget->layout_center_x =
            title_widget->layout_width * 0.5f + title_widget->layout_x - 320.0f;
        back_widget->stack_widget_below(description_widget);

        if (*(int*)(level_progress_base + selected_index * 0x1fac0 + 0x944150) == 1 && route_mode == 2) {
            continue_widget->unhide_border_init();
            continue_widget->layout_center_x =
                title_widget->layout_width * 0.5f + title_widget->layout_x - 320.0f;
            continue_widget->stack_widget_below(description_widget);
            back_widget->stack_widget_below(continue_widget);
        } else {
            continue_widget->hide_border_init();
        }

        bounds_frame_widget->unhide_border_init();

        float min_x = 1000.0f;
        float max_x = -1000.0f;
        float min_y = 1000.0f;
        float max_y = -1000.0f;

        galaxy_border_bound(&min_x, &max_x, &min_y, &max_y, title_widget);
        galaxy_border_bound(&min_x, &max_x, &min_y, &max_y, detail_widget);
        galaxy_border_bound(&min_x, &max_x, &min_y, &max_y, description_widget);
        galaxy_border_bound(&min_x, &max_x, &min_y, &max_y, back_widget);

        max_y += 8.0f;
        min_x -= 8.0f;
        max_x += 8.0f;

        if (max_x > 630.0f) {
            title_widget->layout_anchor_x =
                records[selected_index].map_x - (max_x - min_x) - 40.0f;
        }
        if (min_y < 50.0f) {
            title_widget->layout_anchor_y = 50.0f;
        }
        if (max_y > 450.0f) {
            title_widget->layout_anchor_y = 450.0f - (max_y - min_y);
        }

        if (max_x > 631.0f) {
            continue;
        }
        if (min_y < 49.0f) {
            continue;
        }
        if (max_y > 451.0f) {
            continue;
        }

        bounds_frame_widget->frame_width = max_x - min_x;
        bounds_frame_widget->frame_height = max_y - min_y;
        bounds_frame_widget->frame_x = min_x;
        bounds_frame_widget->frame_y = min_y;

        back_widget->layout_center_x =
            bounds_frame_widget->frame_width * 0.5f + bounds_frame_widget->frame_x - 320.0f;
        FrontendWidget* result = bounds_frame_widget;
        continue_widget->layout_center_x =
            result->frame_width * 0.5f + result->frame_x - 320.0f;
        return result;
    }
}
