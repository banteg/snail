// Root-owned cRBod catalog built by initialize_game_assets_and_world.
#ifndef ROOT_BOD_CATALOG_H
#define ROOT_BOD_CATALOG_H

#include "bod_types.h"
#include "track_fringe_bod_catalog.h"

enum {
    ROOT_BOD_CATALOG_GAME_OFFSET = 0x44100,
    ROOT_BOD_CATALOG_ENTRY_COUNT = 0x160,
    TRACK_CORNER_BOD_COUNT = 4,
    TRACK_SLICE_BOD_COUNT = 8,
    TRACK_PILLAR_BOD_COUNT = 8,
    TRACK_RAMP_EDGE_BOD_COUNT = 3,
};

// The authored corner ids are initialized in 0, 1, 2, 3 order, but their
// storage order is 0, 1, 3, 2. Consumers that address a corner by authored id
// therefore use the explicit storage constants below.
enum TrackCornerBodStorageIndex {
    TRACK_CORNER_0_STORAGE_INDEX = 0,
    TRACK_CORNER_1_STORAGE_INDEX = 1,
    TRACK_CORNER_3_STORAGE_INDEX = 2,
    TRACK_CORNER_2_STORAGE_INDEX = 3,
};

struct TrackCornerBodBank {
    BodBase storage[TRACK_CORNER_BOD_COUNT];
};

struct TrackSliceBodBank {
    BodBase storage[TRACK_SLICE_BOD_COUNT];
};

// Exact layout of the 352-record root BOD bank. The first 58 records are the
// track/world render assets initialized at startup, records 58..345 are the
// directional fringe catalog. Five of the final six records remain unnamed;
// the last is the salt.x donor copied into the runtime salt pool.
struct RootBodCatalog {
    BodBase universe_hole; // index 0, Objects/Universe/Hole.tga
    BodBase unknown_01_04[4];
    TrackCornerBodBank floor_corners; // indices 5..8, Track0.tga
    TrackCornerBodBank warning_corners; // indices 9..12, TrackWarn.tga
    TrackCornerBodBank slide_corners; // indices 13..16, Slide0.tga
    BodBase trampoline; // index 17, Tramp.x
    BodBase unknown_18_21[4];
    // pillar1.x..pillar8.x; CondenseTrack selects [run_length - 1] for
    // horizontal tile-0x0e runs.
    BodBase pillars[TRACK_PILLAR_BOD_COUNT]; // indices 22..29
    TrackSliceBodBank floor_slices; // indices 30..37, Track0.tga
    TrackSliceBodBank warning_slices; // indices 38..45, TrackWarn.tga
    TrackSliceBodBank slide_slices; // indices 46..53, Slide0.tga
    BodBase ramp_edges[TRACK_RAMP_EDGE_BOD_COUNT]; // indices 54..56, -1/0/+1
    BodBase lazer_model; // index 57, Objects/Lazer
    TrackFringeBodCatalog fringe_catalog; // indices 58..345
    BodBase unknown_346_350[5];
    BodBase salt_model; // index 351, salt.x
};

typedef char TrackCornerBodBank_must_be_0xe0[
    (sizeof(TrackCornerBodBank) == 0xe0) ? 1 : -1];
typedef char TrackSliceBodBank_must_be_0x1c0[
    (sizeof(TrackSliceBodBank) == 0x1c0) ? 1 : -1];
typedef char RootBodCatalog_must_be_0x4d00[
    (sizeof(RootBodCatalog) == 0x4d00) ? 1 : -1];

#endif
