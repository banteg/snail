// is_open_neighbor_tile_family @ 0x439ab0 (fastcall, ret)

#include "track_attachment.h"

unsigned char SubLoc::is_open_neighbor_tile_family()
{
    unsigned char tile_id = this->tile_id;
    unsigned char result;
    if (tile_id == 0
        || tile_id == 28
        || tile_id == 35
        || tile_id == 14
        || tile_id == 29) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
