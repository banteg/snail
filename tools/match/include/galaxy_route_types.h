// Shared star-map route controller and record views.
#ifndef GALAXY_ROUTE_TYPES_H
#define GALAXY_ROUTE_TYPES_H

#include "frontend_widget.h"

class cRSubGame;

struct GalaxyPoint {
    union {
        int x_bits;
        float x;
    };
    union {
        int y_bits;
        float y;
    };
};

typedef char GalaxyPoint_must_be_0x08[
    (sizeof(GalaxyPoint) == 0x08) ? 1 : -1];

class GalaxyRouteRecord {
public:
    int route_name_index; // +0x00
    char unknown_004[0x08 - 0x04];
    union {
        int map_x_bits; // +0x08
        float map_x;    // +0x08
    };
    union {
        int map_y_bits; // +0x0c
        float map_y;    // +0x0c
    };
    union {
        int map_z_bits; // +0x10
        float map_z;    // +0x10
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
    char description_text[0x29c - 0x9c]; // +0x9c
};

typedef char GalaxyRouteRecord_must_be_0x29c[
    (sizeof(GalaxyRouteRecord) == 0x29c) ? 1 : -1];

// Android preserves this exact child owner as cRGalaxyStar. Its AI member
// advances the +0x18 tint toward the +0x1c target, and both mobile Galaxy
// owners traverse the children at the same 0x2a0 stride as Windows.
class cRGalaxyStar {
public:
    void AI(); // @ 0x409bd0

    int unknown_000; // +0x00
    GalaxyRouteRecord record; // +0x04
};

typedef cRGalaxyStar GalaxyStar;

typedef char cRGalaxyStar_must_be_0x2a0[
    (sizeof(cRGalaxyStar) == 0x2a0) ? 1 : -1];
typedef char GalaxyStar_must_be_0x2a0[
    (sizeof(GalaxyStar) == 0x2a0) ? 1 : -1];

// Compatibility vocabulary for older notes and out-of-tree analysis scripts.
typedef GalaxyStar GalaxyRouteSlot;

// Non-owning view used when native keeps `this + index * 0x2a0` as its base
// instead of materializing route_slots +0x10. Storage remains route_slots[].
struct GalaxyRouteIndexedSlotView {
    char before_slot_record[0x14];
    int route_name_index; // +0x14
    char unknown_018[0x1c - 0x18];
    float map_x; // +0x1c
    float map_y; // +0x20
    float map_z; // +0x24
    float route_tint_alpha; // +0x28
    float highlight_target; // +0x2c
};

class GalaxyRouteNameRecord {
public:
    GalaxyRouteNameRecord* initialize_galaxy_route_name_record(); // @ 0x408880

    char name[0x80]; // +0x00
    int star_count; // +0x80
    tColour color; // +0x84
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

class cRGalaxy {
public:
    void Open(); // @ 0x4088e0, Windows no-argument bootstrap
    void UnInit(); // @ 0x408c10
    void Init(); // @ 0x408cf0
    int AI(); // @ 0x4092f0, includes the Windows render phase
    void BoxOff(); // @ 0x409bf0
    void BoxOn(int selected_level_index); // @ 0x409c50
    void Line(
        int texture_id,
        float x0,
        float y0,
        float x1,
        float y1,
        float width,
        tColour& color); // @ 0x409b00
    void BorderBound(
        float& min_x,
        float& max_x,
        float& min_y,
        float& max_y,
        cRBorder* widget); // @ 0x40a0c0

    char active; // +0x00
    char unknown_001[0x04 - 0x01];
    int route_mode; // +0x04
    int route_state; // +0x08
    int record_count; // +0x0c
    // Constructor-built slot array. Each slot has a four-byte tick prefix and
    // a 0x29c-byte authored/display record.
    cRGalaxyStar route_slots[101]; // +0x10, ends at +0x10930
    GalaxyRouteNameRecord route_names[10]; // +0x10930
    cRSubGame* level_progress_base; // +0x10f70, borrowed enclosing subgame
    union {
        struct {
            cRBorder* exit_or_back_widget; // +0x10f74
            cRBorder* route_title_widget; // +0x10f78
            cRBorder* route_icon_widget; // +0x10f7c
        };
        cRBorder* pre_route_borders[3]; // +0x10f74
    };
    int selected_index; // +0x10f80
    int hover_state; // +0x10f84
    char unknown_10f88[0x10f8c - 0x10f88];
    union {
        struct {
            cRBorder* bounds_frame_widget; // +0x10f8c
            cRBorder* selected_title_widget; // +0x10f90
            cRBorder* selected_detail_widget; // +0x10f94
            cRBorder* selected_description_widget; // +0x10f98
            cRBorder* play_or_deliver_widget; // +0x10f9c
            cRBorder* replay_widget; // +0x10fa0
        };
        struct {
            cRBorder* bounds_widget; // +0x10f8c
            cRBorder* title_widget; // +0x10f90
            cRBorder* detail_widget; // +0x10f94
            cRBorder* description_widget; // +0x10f98
            cRBorder* back_widget; // +0x10f9c
            cRBorder* continue_widget; // +0x10fa0
        };
        cRBorder* borders[6]; // +0x10f8c
    };
    int unknown_10fa4; // +0x10fa4, unresolved cRGalaxy tail
};

typedef cRGalaxy Galaxy;

typedef char cRGalaxy_must_be_0x10fa8[
    (sizeof(cRGalaxy) == 0x10fa8) ? 1 : -1];
typedef char Galaxy_must_be_0x10fa8[
    (sizeof(Galaxy) == 0x10fa8) ? 1 : -1];

extern GalaxyPoint g_galaxy_group_points[10]; // data_4a1c4c
extern GalaxyPoint g_galaxy_route_points[101]; // data_4a1d14

#endif
