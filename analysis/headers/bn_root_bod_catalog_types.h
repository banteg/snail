#ifndef BN_ROOT_BOD_CATALOG_TYPES_H
#define BN_ROOT_BOD_CATALOG_TYPES_H

/*
 * Narrow Binary Ninja projection of the constructor-proven 352-entry BOD
 * catalog at GameRoot +0x44100. Type names are intentionally local to this
 * lane so importing it cannot flatten an independently recovered BodBase.
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

typedef struct RootBodCatalogEntry RootBodCatalogEntry;
struct RootBodCatalogEntry {
    void* vtable;
    uint32_t list_flags;
    RootBodCatalogEntry* list_prev;
    RootBodCatalogEntry* list_next;
    RootBodCatalogVec3 position;
    float render_arg_1c;
    float render_arg_20;
    void* object;
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

#endif
