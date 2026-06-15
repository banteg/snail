// is_slide_cache_tile_family @ 0x439a40 (fastcall, ret)

#include "track_attachment.h"

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
