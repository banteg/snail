#ifndef BN_ROOT_BOD_CATALOG_TYPES_H
#define BN_ROOT_BOD_CATALOG_TYPES_H

/*
 * Narrow Binary Ninja projection of the constructor-proven 352-entry BOD
 * catalog at GameRoot +0x44100. Type names are intentionally local to this
 * lane so importing it cannot flatten an independently recovered BodBase.
 * The complete Object owner is maintained by the object-render lane and is
 * borrowed here through a forward declaration only.
 */

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

typedef struct RootBodCatalogVec3 {
    float x;
    float y;
    float z;
} RootBodCatalogVec3;

typedef struct RootBodCatalogColor4f {
    float r;
    float g;
    float b;
    float a;
} RootBodCatalogColor4f;

typedef struct Object Object;

typedef struct RootBodCatalogEntry RootBodCatalogEntry;
struct RootBodCatalogEntry {
    void* vtable;
    uint32_t list_flags;
    RootBodCatalogEntry* list_prev;
    RootBodCatalogEntry* list_next;
    RootBodCatalogVec3 position;
    float render_arg_1c;
    float render_arg_20;
    Object* object;
    RootBodCatalogColor4f color;
};

typedef struct RootTrackCornerBodBank {
    RootBodCatalogEntry storage[4];
} RootTrackCornerBodBank;

typedef struct RootTrackSliceBodBank {
    RootBodCatalogEntry storage[8];
} RootTrackSliceBodBank;

typedef struct RootTrackFringeBodCatalog {
    RootBodCatalogEntry entries[8][4][3][3];
} RootTrackFringeBodCatalog;

typedef struct RootBodCatalog {
    RootBodCatalogEntry universe_hole;
    RootBodCatalogEntry unknown_01_04[4];
    RootTrackCornerBodBank floor_corners;
    RootTrackCornerBodBank warning_corners;
    RootTrackCornerBodBank slide_corners;
    RootBodCatalogEntry trampoline;
    RootBodCatalogEntry unknown_18_21[4];
    RootBodCatalogEntry pillars[8];
    RootTrackSliceBodBank floor_slices;
    RootTrackSliceBodBank warning_slices;
    RootTrackSliceBodBank slide_slices;
    RootBodCatalogEntry ramp_edges[3];
    RootBodCatalogEntry lazer_model;
    RootTrackFringeBodCatalog fringe_catalog;
    RootBodCatalogEntry unknown_346_350[5];
    RootBodCatalogEntry salt_model;
} RootBodCatalog;

/*
 * Analysis-only root-relative view for the eight-pass backdrop-slice loop in
 * initialize_game_assets_and_world. Native carries `game + i * 0x38`, then
 * applies the three fixed GameRoot biases below. Each named entry is borrowed
 * from its canonical RootBodCatalog bank; RootBodCatalog remains the sole
 * owner.
 */
typedef struct RootTrackSliceTripletStrideView {
    uint8_t root_to_floor_slice[0x44790];
    RootBodCatalogEntry floor_slice;
    uint8_t floor_to_warning_slice[0x188];
    RootBodCatalogEntry warning_slice;
    uint8_t warning_to_slide_slice[0x188];
    RootBodCatalogEntry slide_slice;
} RootTrackSliceTripletStrideView;

#endif
