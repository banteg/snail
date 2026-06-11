// is_slide_cache_tile_family @ 0x439a40 (fastcall, ret)

struct TrackRowCell {
    char unknown_00[0x3c];
    unsigned char tile_id;
};

unsigned char __fastcall is_slide_cache_tile_family(TrackRowCell* cell)
{
    unsigned char tile_id = cell->tile_id;
    unsigned char result;
    if (tile_id == 1
        || tile_id == 20
        || tile_id == 21
        || tile_id == 33
        || tile_id == 34
        || tile_id == 27) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
