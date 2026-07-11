// is_neighbor_cell_solid @ 0x434b60 (thiscall, ret 0xc)

#include "subgame_runtime.h"
#include "track_attachment.h"

bool SubgameRuntime::is_neighbor_cell_solid(SubLoc* cell, int dx, int dz)
{
    int row = cell->get_track_cell_row_index();
    int lane = cell->lane_and_flags & 7;
    bool result = false;
    if ((unsigned int)(lane + dx) < 8) {
        int neighbor_row = dz + row;
        if (neighbor_row >= 0 && neighbor_row < runtime_row_count) {
            int cell_index = 21 * (dx + lane + 8 * neighbor_row);
            char* cell_base = (char*)this + (cell_index << 2);
            unsigned char tile_id = *(unsigned char*)(cell_base + 0x3bfb04);
            SubLoc* neighbor = (SubLoc*)cell_base;
            int tile = tile_id;
            neighbor = (SubLoc*)((char*)neighbor + 0x3bfac8);
            if (!neighbor->is_open_neighbor_tile_family()
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
