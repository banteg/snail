// is_floor_cache_tile_family @ 0x439ad0 (fastcall, ret)

#include "track_attachment.h"

unsigned char __fastcall is_floor_cache_tile_family(TrackRowCell* cell)
{
    unsigned char tile_id = cell->tile_id;
    unsigned char result;
    if (tile_id == 15
        || tile_id == 23
        || tile_id == 24
        || tile_id == 25
        || tile_id == 26
        || tile_id == 16
        || tile_id == 18
        || tile_id == 19) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
