// is_neighbor_cell_solid @ 0x434b60 (thiscall, ret 0xc)

#include <stddef.h>

#include "subgame_runtime.h"
#include "track_attachment.h"

bool SubgameRuntime::is_neighbor_cell_solid(SubLoc* cell, int dx, int dz)
{
    int row = cell->get_track_cell_row_index();
    int lane = cell->lane_and_flags & SUBLOC_LANE_INDEX_MASK;
    bool result = false;
    if ((unsigned int)(lane + dx) < SUBGAME_TRACK_LANE_COUNT) {
        int neighbor_row = dz + row;
        if (neighbor_row >= 0 && neighbor_row < runtime_row_count) {
            int cell_index =
                21 * (dx + lane + SUBGAME_TRACK_LANE_COUNT * neighbor_row);
            char* cell_base = (char*)this + (cell_index << 2);
            unsigned char tile_id = *(unsigned char*)(cell_base
                + (int)offsetof(SubgameRuntime, runtime_cells[0][0].tile_id));
            SubLoc* neighbor = (SubLoc*)cell_base;
            int tile = tile_id;
            neighbor = (SubLoc*)((char*)neighbor
                + (int)offsetof(SubgameRuntime, runtime_cells));
            if (!neighbor->is_sub_loc_empty()
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
