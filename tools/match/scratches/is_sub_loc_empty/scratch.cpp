// is_sub_loc_empty @ 0x439ab0 (fastcall, ret)

#include "track_attachment.h"

unsigned char SubLoc::is_sub_loc_empty()
{
    unsigned char tile_id = this->tile_id;
    unsigned char result;
    if (tile_id == SUBLOC_TILE_EMPTY
        || tile_id == SUBLOC_TILE_UNIVERSE_HOLE
        || tile_id == SUBLOC_TILE_RING_MARKER
        || tile_id == SUBLOC_TILE_WALL2
        || tile_id == SUBLOC_TILE_PATH_ENTRY_LOWERCASE) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
