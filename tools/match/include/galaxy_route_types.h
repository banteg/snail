// Shared star-map route controller and record views.
#ifndef GALAXY_ROUTE_TYPES_H
#define GALAXY_ROUTE_TYPES_H

#include "frontend_widget.h"

class Game;

class GalaxyRouteRecordTick {
public:
    void update_galaxy_route_record(); // @ 0x409bd0
};

class GalaxyRouteRecord {
public:
    int route_name_index; // +0x00
    char unknown_004[0x08 - 0x04];
    union {
        int map_x_bits; // +0x08
        float map_x;   // +0x08
    };
    union {
        int map_y_bits; // +0x0c
        float map_y;   // +0x0c
    };
    union {
        int map_z_bits; // +0x10
        float map_z;   // +0x10
    };
    union {
        int route_tint_alpha_bits; // +0x14
        int highlight_bits;        // +0x14
        float route_tint_alpha;    // +0x14
    };
    union {
        int highlight_target_bits; // +0x18
        int selected_bits;         // +0x18
        float highlight_target;    // +0x18
    };
    char detail_text[0x80]; // +0x1c
    char description_text[0x2a0 - 0x9c]; // +0x9c
};

typedef char GalaxyRouteRecord_must_be_0x2a0[
    (sizeof(GalaxyRouteRecord) == 0x2a0) ? 1 : -1];

class GalaxyRouteRecordSlot {
public:
    char before_record[0x14];
    int route_name_index; // +0x14
    char unknown_018[0x1c - 0x18];
    float map_x; // +0x1c
    float map_y; // +0x20
    float map_z; // +0x24
    float route_tint_alpha; // +0x28
    float highlight_target; // +0x2c
    char detail_text[0x80]; // +0x30
    char description_text[0x2a0 - 0x9c]; // +0xb0
};

class GalaxyRouteNameRecord {
public:
    char name[0x80]; // +0x00
    int star_count; // +0x80
    union {
        int color_r_bits; // +0x84
        float color_r;    // +0x84
    };
    union {
        int color_g_bits; // +0x88
        float color_g;    // +0x88
    };
    union {
        int color_b_bits; // +0x8c
        float color_b;    // +0x8c
    };
    union {
        int color_a_bits; // +0x90
        float color_a;    // +0x90
    };
    union {
        int map_x_bits; // +0x94
        float map_x;   // +0x94
    };
    union {
        int map_y_bits; // +0x98
        float map_y;   // +0x98
    };
    union {
        int map_z_bits; // +0x9c
        float map_z;   // +0x9c
    };
};

typedef char GalaxyRouteNameRecord_must_be_0xa0[
    (sizeof(GalaxyRouteNameRecord) == 0xa0) ? 1 : -1];

class GalaxyRoute {
public:
    int load_galaxy_layout(); // @ 0x4088e0
    FrontendWidget* initialize_galaxy(); // @ 0x408cf0
    void destroy_galaxy(); // @ 0x408c10
    int update_galaxy(); // @ 0x4092f0
    void close_galaxy_route(); // @ 0x409bf0
    FrontendWidget* open_galaxy_route(int selected_level_index); // @ 0x409c50
    void galaxy_border_bound(
        float* min_x,
        float* max_x,
        float* min_y,
        float* max_y,
        FrontendWidget* widget); // @ 0x40a0c0

    char active; // +0x00
    char unknown_001[0x04 - 0x01];
    int route_mode; // +0x04
    int route_state; // +0x08
    int record_count; // +0x0c
    char unknown_010[0x14 - 0x10];
    GalaxyRouteRecord records[100]; // +0x14
    char unknown_10694[0x10930 - 0x10694];
    GalaxyRouteNameRecord route_names[10]; // +0x10930
    char* level_progress_base; // +0x10f70, embedded subgame/progress base
    union {
        struct {
            FrontendWidget* exit_or_back_widget; // +0x10f74
            FrontendWidget* route_title_widget; // +0x10f78
            FrontendWidget* route_icon_widget; // +0x10f7c
        };
        FrontendWidget* pre_route_borders[3]; // +0x10f74
    };
    int selected_index; // +0x10f80
    int hover_state; // +0x10f84
    char unknown_10f88[0x10f8c - 0x10f88];
    union {
        struct {
            FrontendWidget* bounds_frame_widget; // +0x10f8c
            FrontendWidget* selected_title_widget; // +0x10f90
            FrontendWidget* selected_detail_widget; // +0x10f94
            FrontendWidget* selected_description_widget; // +0x10f98
            FrontendWidget* play_or_deliver_widget; // +0x10f9c
            FrontendWidget* replay_widget; // +0x10fa0
        };
        struct {
            FrontendWidget* bounds_widget; // +0x10f8c
            FrontendWidget* title_widget; // +0x10f90
            FrontendWidget* detail_widget; // +0x10f94
            FrontendWidget* description_widget; // +0x10f98
            FrontendWidget* back_widget; // +0x10f9c
            FrontendWidget* continue_widget; // +0x10fa0
        };
        FrontendWidget* borders[6]; // +0x10f8c
    };
};

typedef char GalaxyRoute_must_be_0x10fa4[
    (sizeof(GalaxyRoute) == 0x10fa4) ? 1 : -1];

#endif
