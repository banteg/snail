// Track row-cell anchor view, partial.
//
// For path-follow scratches that only need the row anchor and row-index helper.
// It intentionally depends on the including scratch's local Vec3 view and avoids
// naming the +0x38 attachment-template pointer because some users need
// matrix-backed template/sample views instead of the full Path
// layout.
#ifndef TRACK_ROW_CELL_ANCHOR_VIEW_H
#define TRACK_ROW_CELL_ANCHOR_VIEW_H

struct TrackRowCellAnchorView {
    char unknown_00[0x10];
    Vec3 anchor_position; // +0x10
    char unknown_1c[0x38 - 0x1c];

    int get_track_cell_row_index();
};

#endif
