// get_track_cell_row_index @ 0x447040 (thiscall, ret)

#include "track_attachment_types.h"

class GameRoot;

extern GameRoot* g_game; // data_4df904
extern char g_track_row_cells_offset[]; // 0x4340e0

int cRSubLoc::get_track_cell_row_index()
{
    int lane = lane_and_flags & (SUBGAME_TRACK_LANE_COUNT - 1);
    char* row_cell = (char*)this - lane * (int)sizeof(cRSubLoc);
    int offset = row_cell - (char*)g_game;
    offset -= (int)g_track_row_cells_offset;
    int cell_index = offset / (int)sizeof(cRSubLoc);
    return cell_index / SUBGAME_TRACK_LANE_COUNT;
}
