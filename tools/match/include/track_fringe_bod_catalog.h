// Root-owned BOD catalog used by directional track-fringe emission.
#ifndef TRACK_FRINGE_BOD_CATALOG_H
#define TRACK_FRINGE_BOD_CATALOG_H

#include "bod_types.h"

enum {
    TRACK_FRINGE_BOD_CATALOG_GAME_OFFSET = 0x44db0,
    TRACK_FRINGE_BOD_CATALOG_ROOT_BOD_INDEX = 58,
    TRACK_FRINGE_FAMILY_COUNT = 8,
    TRACK_FRINGE_DIRECTION_COUNT = 4,
    TRACK_FRINGE_EDGE_VARIANT_COUNT = 3,
};

enum TrackFringeDirection {
    TRACK_FRINGE_FRONT = 0,
    TRACK_FRINGE_RIGHT = 1,
    TRACK_FRINGE_LEFT = 2,
    TRACK_FRINGE_BACK = 3,
};

class TrackFringeBodCatalog {
public:
    // Built as family -> direction -> first edge -> second edge. Runtime
    // fringe objects borrow only each BodBase::object pointer.
    BodBase entries
        [TRACK_FRINGE_FAMILY_COUNT]
        [TRACK_FRINGE_DIRECTION_COUNT]
        [TRACK_FRINGE_EDGE_VARIANT_COUNT]
        [TRACK_FRINGE_EDGE_VARIANT_COUNT];
};

typedef char TrackFringeBodCatalog_must_be_0x3f00[
    (sizeof(TrackFringeBodCatalog) == 0x3f00) ? 1 : -1];

#endif
