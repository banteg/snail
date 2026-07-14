// Track row-cell tile-byte view, partial.
//
// This view starts at TrackRowCell/SubLoc::tile_id (+0x3c) and walks with the
// full sizeof(SubLoc) == 0x54 stride. It is not the full anchor-bearing cell
// base view; callers that must preserve field-first pointer induction derive
// the containing or neighboring SubLoc from those two layout facts.
#ifndef TRACK_ROW_CELL_TILE_VIEWS_H
#define TRACK_ROW_CELL_TILE_VIEWS_H

#include "fringe_fwd.h"

struct TrackRowCellTileByteView {
    unsigned char tile_id; // TrackRowCell +0x3c
    unsigned char open_edge_mask; // TrackRowCell +0x3d, SubLocOpenEdgeFlag bits
    char unknown_02[0x04 - 0x02];
    unsigned int lane_and_flags; // TrackRowCell +0x40, SubLocFlag bits
    char unknown_08[0x54 - 0x08];
};

// Field-first view beginning at TrackRowCell +0x44. These are non-owning
// handles to objects allocated and recycled by the shared FringeManager.
struct TrackRowCellFringeLinkView {
    Fringe* front;
    Fringe* right;
    Fringe* left;
    Fringe* back;
    char next_cell[0x54 - 0x10];
};

typedef char TrackRowCellFringeLinkView_must_stride_0x54[
    (sizeof(TrackRowCellFringeLinkView) == 0x54) ? 1 : -1];

#endif
