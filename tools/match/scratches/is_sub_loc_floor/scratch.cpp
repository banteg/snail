// is_sub_loc_floor @ 0x439a40 (fastcall, ret)

#include "track_attachment.h"

unsigned char SubLoc::is_sub_loc_floor()
{
    unsigned char tile_id = this->tile_id;
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
