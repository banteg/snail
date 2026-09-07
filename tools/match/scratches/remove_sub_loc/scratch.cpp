// remove_sub_loc @ 0x439bc0 (thiscall, ret) — cRSubLoc::Remove()

#include "fringe_object.h"
#include "game_root.h"
#include "track_attachment_types.h"

void cRSubLoc::Remove()
{
    int row_index = Yi();
    unsigned char tile = tile_id;

    if (tile == SUBLOC_TILE_PATH_ENTRY_LOWERCASE
        || tile == SUBLOC_TILE_PATH_ENTRY_UPPERCASE) {
        if ((g_game->subgame.runtime_rows[row_index].flags
                & SUBROW_FLAG_PATH_OR_MODEL_VELOCITY) != 0) {
            if ((g_game->subgame.runtime_rows[row_index].attachment_body.list_flags
                    & BOD_FLAG_LINKED) != 0)
                g_game->active_bod_list.remove_bod(
                    &g_game->subgame.runtime_rows[row_index].attachment_body);
        }
    }

    if ((list_flags & BOD_FLAG_LINKED) != 0)
        g_game->active_bod_list.remove_bod(this);

    for (int i = 0; i < (int)(sizeof(fringes) / sizeof(fringes[0])); ++i) {
        if (fringes[i] != 0 && (fringes[i]->list_flags & BOD_FLAG_LINKED) != 0)
            g_game->active_bod_list.remove_bod(fringes[i]);
    }
}
