// get_track_cell_row_index @ 0x447040 (thiscall, ret)

extern char* g_game_base; // data_4df904
extern char g_track_row_cells_offset[]; // 0x4340e0

class TrackRowCell {
public:
    int get_track_cell_row_index();

    char unknown_00[0x40];
    int lane_and_flags; // +0x40, low 3 bits are lane
};

int TrackRowCell::get_track_cell_row_index()
{
    int lane = lane_and_flags & 7;
    char* row_cell = (char*)this - lane * 0x54;
    int offset = row_cell - g_game_base;
    offset -= (int)g_track_row_cells_offset;
    int cell_index = offset / 0x54;
    return cell_index / 8;
}
