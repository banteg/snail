// copy_segment_definition_to_level_slot @ 0x447300 (stdcall, ret 0x8)

#include "segment_catalog_types.h"

extern char* g_game_base; // data_4df904
extern char* g_current_level_definition_name; // data_74ec74

int strings_equal_case_insensitive_path(char* lhs, char* rhs); // @ 0x44e6c0
int report_errorf(char* format, ...);

int* __stdcall copy_segment_definition_to_level_slot(char* segment_name, LevelSegmentSlot* slot)
{
    int* catalog_count = (int*)(g_game_base + 0x1075ae4);
    SegmentCatalogEntry* entries = (SegmentCatalogEntry*)catalog_count;
    int index = 0;
    SegmentCatalogEntry* scan = entries;
    while (index < *catalog_count) {
        if (strings_equal_case_insensitive_path(segment_name, scan->filename) == 1)
            break;
        ++index;
        ++scan;
    }

    if (index == *catalog_count)
        return (int*)report_errorf(
            "Cannot find segment %s for %s",
            segment_name,
            g_current_level_definition_name);

    SegmentCatalogEntry* source = &entries[index];

    for (int grid_row = 0; grid_row < 8; ++grid_row) {
        for (int column = 0; column < source->row_count; ++column)
            slot->glyph_rows[grid_row][column] = source->glyph_columns[column][grid_row];
    }

    slot->row_count = source->row_count;
    slot->source_name = source->filename;
    slot->angle_radians.bits = 0;
    slot->path_index = source->id;

    int* result = (int*)source->row_count;
    for (int metadata_row = 0; metadata_row < source->row_count; ++metadata_row) {
        AuthoredSegmentRow* destination = &slot->rows[metadata_row];
        AuthoredSegmentRow* authored = &source->rows[metadata_row];
        destination->flags = authored->flags;
        destination->object_id = authored->object_id;
        destination->object_position_x.bits = authored->object_position_x.bits;
        destination->object_position_y.bits = authored->object_position_y.bits;
        destination->object_position_z.bits = authored->object_position_z.bits;
        destination->object_velocity_x.bits = authored->object_velocity_x.bits;
        destination->object_velocity_y.bits = authored->object_velocity_y.bits;
        destination->object_velocity_z.bits = authored->object_velocity_z.bits;
        destination->parcel_set_id = authored->parcel_set_id;
        destination->local_x.bits = authored->local_x.bits;
        destination->local_y.bits = authored->local_y.bits;
        destination->local_z.bits = authored->local_z.bits;
        destination->path_template_index = authored->path_template_index;
        destination->ring_speed = authored->ring_speed;
        result = (int*)(authored + 1);
    }

    slot->message_text[0] = 0;
    slot->message_duration.bits = 0;
    slot->message_sample_id = -1;
    return result;
}
