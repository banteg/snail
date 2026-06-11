// is_ramp_cache_tile_family @ 0x439a70 (fastcall, ret)

struct TrackRowCell {
    char unknown_00[0x3c];
    unsigned char tile_id;
};

unsigned char __fastcall is_ramp_cache_tile_family(TrackRowCell* cell)
{
    unsigned char tile_id = cell->tile_id;
    unsigned char result;
    if (tile_id == 2
        || tile_id == 3
        || tile_id == 4
        || tile_id == 8
        || tile_id == 9
        || tile_id == 10
        || tile_id == 11
        || tile_id == 12
        || tile_id == 13
        || tile_id == 5
        || tile_id == 6
        || tile_id == 7) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
