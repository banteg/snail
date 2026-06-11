// mark_track_warning_zones @ 0x4354f0 (thiscall, ret)
// cRSubGame::WarnTrack() per Android symbols: stamps a 6-row x 2-col
// warning footprint (flags |= 0x18) behind every hazard-bearing tile.

struct RuntimeTrackCell {
    unsigned char tile; // +0x00
    char pad_01[3];
    unsigned int flags; // +0x04
    char pad_08[84 - 8];
};

class GameRuntime {
public:
    void mark_track_warning_zones();

    char unknown_00[0x54];
    int runtime_row_count; // +0x54
    char unknown_58[0x3bfb04 - 0x58];
    RuntimeTrackCell cells[1]; // +0x3bfb04, row-major, 8 per row
};

void GameRuntime::mark_track_warning_zones()
{
    int row = 0;
    if (runtime_row_count - 1 > 0) {
        RuntimeTrackCell* cell = cells;
        do {
            for (int col = 0; col < 8; ++col, ++cell) {
                char t = cell->tile;
                if (t == 2 || t == 3 || t == 4 || t == 5 || t == 6 || t == 7
                    || t == 8 || t == 9 || t == 10 || t == 11 || t == 12
                    || t == 13 || t == 14 || t == 23 || t == 25 || t == 33) {
                    int r = row;
                    int idx = col + 8 * row;
                    for (int back = 6; back; --back) {
                        for (int dc = -1; dc < 1; ++dc) {
                            if (r >= 0 && r < runtime_row_count - 1
                                && dc + col >= 0 && dc + col < 8)
                                cells[idx + dc].flags |= 0x18;
                        }
                        --r;
                        idx -= 8;
                    }
                }
            }
            ++row;
        } while (row < runtime_row_count - 1);
    }
}
