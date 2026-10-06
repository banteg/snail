// get_track_cell_row_index @ 0x447040 (thiscall, ret) — cRSubLoc::Yi()

#include "track_attachment_types.h"

#ifdef SNAIL_PORT
#include <stddef.h>

#include "game_root.h"

// The original's immediate 0x4340e0 is this offset; it lies inside the image's
// address range, so the VC6 spelling below routes it through a symbol.
#define g_track_row_cells_offset ((char*)offsetof(cRGame, subgame.runtime_cells))
#else
class cRGame;

extern cRGame* g_game; // data_4df904
extern char g_track_row_cells_offset[]; // 0x4340e0
#endif

int cRSubLoc::Yi()
{
    int lane = lane_and_flags & (SUBGAME_TRACK_LANE_COUNT - 1);
    char* row_cell = (char*)this - lane * (int)sizeof(cRSubLoc);
    int offset = row_cell - (char*)g_game;
    offset -= (int)g_track_row_cells_offset;
    int cell_index = offset / (int)sizeof(cRSubLoc);
    return cell_index / SUBGAME_TRACK_LANE_COUNT;
}
