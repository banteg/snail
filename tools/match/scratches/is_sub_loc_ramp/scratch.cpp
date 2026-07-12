// is_sub_loc_ramp @ 0x439a70 (fastcall, ret)

#include "track_attachment.h"

unsigned char SubLoc::is_sub_loc_ramp()
{
    unsigned char tile_id = this->tile_id;
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
