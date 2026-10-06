// is_neighbor_cell_solid @ 0x434b60 (thiscall, ret 0xc)

#include <stddef.h>

#include "subgame_runtime.h"
#include "track_attachment.h"

bool cRSubGame::TestLoc(cRSubLoc* cell, int dx, int dz)
{
    int row = cell->Yi();
    int lane = cell->lane_and_flags & SUBLOC_LANE_INDEX_MASK;
    bool result = false;
    if ((unsigned int)(lane + dx) < SUBGAME_TRACK_LANE_COUNT) {
        int neighbor_row = dz + row;
        if (neighbor_row >= 0 && neighbor_row < runtime_row_count) {
            int cell_index =
                21 * (dx + lane + SUBGAME_TRACK_LANE_COUNT * neighbor_row);
            char* cell_base = (char*)this + (cell_index << 2);
            unsigned char tile_id = *(unsigned char*)(cell_base
                + (int)offsetof(cRSubGame, runtime_cells[0][0].tile_id));
            cRSubLoc* neighbor = (cRSubLoc*)cell_base;
            int tile = tile_id;
            neighbor = (cRSubLoc*)((char*)neighbor
                + (int)offsetof(cRSubGame, runtime_cells));
            if (!neighbor->IsEmpty()
                && tile != SUBLOC_TILE_EMPTY
                && tile != SUBLOC_TILE_RING_MARKER
                && tile != SUBLOC_TILE_UNIVERSE_HOLE
                && tile != SUBLOC_TILE_TRAMPOLINE) {
                return true;
            }
        }
    }
    return result;
}
