// is_neighbor_cell_solid @ 0x434b60 (thiscall, ret 0xc)

#include "track_attachment.h"

unsigned char __fastcall is_open_neighbor_tile_family(TrackRowCell* cell);

class Game {
public:
    bool is_neighbor_cell_solid(TrackRowCell* cell, int dx, int dz);

    char unknown_00[0x54];
    int runtime_row_count; // +0x54
    char unknown_58[0x3bfac8 - 0x58];
    TrackRowCell runtime_cells[1]; // +0x3bfac8, 8 cells per row
};

bool Game::is_neighbor_cell_solid(TrackRowCell* cell, int dx, int dz)
{
    int row = cell->get_track_cell_row_index();
    int lane = cell->lane_word & 7;
    bool result = false;
    if ((unsigned int)(lane + dx) < 8) {
        int neighbor_row = dz + row;
        if (neighbor_row >= 0 && neighbor_row < runtime_row_count) {
            int cell_index = 21 * (dx + lane + 8 * neighbor_row);
            unsigned char tile_id = *(unsigned char*)((char*)this + (cell_index << 2) + 0x3bfb04);
            TrackRowCell* neighbor = (TrackRowCell*)((char*)this + (cell_index << 2));
            int tile = tile_id;
            neighbor = (TrackRowCell*)((char*)neighbor + 0x3bfac8);
            if (!is_open_neighbor_tile_family(neighbor)
                && tile != 0
                && tile != 35
                && tile != 28
                && tile != 22) {
                return true;
            }
        }
    }
    return result;
}
