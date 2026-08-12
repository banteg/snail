// cRSubTracks::ImportSegment @ 0x447300 (thiscall, ret 0x8)

#include "game_root.h"
#include "rstring.h"

extern char* g_current_level_definition_name; // data_74ec74

int report_errorf(char* format, ...);

void cRSubTracks::ImportSegment(
    char* segment_name,
    cRSubSegment* slot)
{
    cRSMTracks* catalog = &g_game->subgame.sm_tracks;
    int index = 0;
    SegmentCatalogEntry* scan = catalog->entries;
    while (index < catalog->count) {
        if (strings_equal_case_insensitive_path(segment_name, scan->filename) == 1)
            break;
        ++index;
        ++scan;
    }

    if (index == catalog->count) {
        report_errorf(
            "Cannot find segment %s for %s",
            segment_name,
            g_current_level_definition_name);
        return;
    }

    for (int grid_row = 0; grid_row < 8; ++grid_row) {
        for (int column = 0; column < catalog->entries[index].row_count; ++column)
            slot->glyph_rows[grid_row][column] =
                catalog->entries[index].glyph_columns[column][grid_row];
    }

    slot->row_count = catalog->entries[index].row_count;
    slot->source_name = catalog->entries[index].filename;
    slot->angle_radians.bits = 0;
    slot->path_index = catalog->entries[index].id;

    for (int metadata_row = 0;
         metadata_row < catalog->entries[index].row_count;
         ++metadata_row) {
        slot->rows[metadata_row].flags =
            catalog->entries[index].rows[metadata_row].flags;
        slot->rows[metadata_row].object_id =
            catalog->entries[index].rows[metadata_row].object_id;
        slot->rows[metadata_row].object_position =
            catalog->entries[index].rows[metadata_row].object_position;
        slot->rows[metadata_row].object_velocity =
            catalog->entries[index].rows[metadata_row].object_velocity;
        slot->rows[metadata_row].parcel_set_id =
            catalog->entries[index].rows[metadata_row].parcel_set_id;
        slot->rows[metadata_row].local_position =
            catalog->entries[index].rows[metadata_row].local_position;
        slot->rows[metadata_row].path_template_index =
            catalog->entries[index].rows[metadata_row].path_template_index;
        slot->rows[metadata_row].ring_speed =
            catalog->entries[index].rows[metadata_row].ring_speed;
    }

    slot->message_text[0] = 0;
    slot->message_duration.bits = 0;
    slot->message_sample_id = -1;
}
