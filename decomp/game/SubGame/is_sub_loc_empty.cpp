// is_sub_loc_empty @ 0x439ab0 (thiscall, ret) — cRSubLoc::IsEmpty()

#include "track_attachment.h"

bool cRSubLoc::IsEmpty()
{
    unsigned char tile_id = this->tile_id;
    bool result;
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
