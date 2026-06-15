// Track row-cell tile-byte view, partial.
//
// This view starts at TrackRowCell +0x3c and walks with the full 0x54 row-cell
// stride. It is not the full anchor-bearing TrackRowCell base view.
#ifndef TRACK_ROW_CELL_TILE_VIEWS_H
#define TRACK_ROW_CELL_TILE_VIEWS_H

struct TrackRowCellTileByteView {
    unsigned char tile_id; // TrackRowCell +0x3c
    char unknown_01[0x04 - 0x01];
    unsigned int lane_and_flags; // TrackRowCell +0x40
    char unknown_08[0x54 - 0x08];
};

#endif
