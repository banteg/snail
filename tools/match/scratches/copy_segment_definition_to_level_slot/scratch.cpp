// copy_segment_definition_to_level_slot @ 0x447300 (stdcall, ret 0x8)

extern char* g_game_base; // data_4df904
extern char* g_current_level_definition_name; // data_74ec74

int strings_equal_case_insensitive_path(char* lhs, char* rhs); // @ 0x44e6c0
int report_errorf(char* format, ...);

union AuthoredFloatBits {
    int bits;
    float value;
};

struct AuthoredSegmentRow {
    int flags;                     // +0x00
    int parcel_set_id;             // +0x04
    int local_x_bits;              // +0x08
    int local_y_bits;              // +0x0c
    int local_z_bits;              // +0x10
    int object_id;                 // +0x14
    int object_position_x_bits;    // +0x18
    int object_position_y_bits;    // +0x1c
    int object_position_z_bits;    // +0x20
    int object_velocity_x_bits;    // +0x24
    int object_velocity_y_bits;    // +0x28
    int object_velocity_z_bits;    // +0x2c
    int path_template_index;       // +0x30
    AuthoredFloatBits ring_speed;  // +0x34
};

struct SegmentCatalogEntry {
    int count_alias; // +0x00 on entry 0 only; the catalog count overlaps entry 0
    char display_name[0x40]; // +0x04, copied from Name:'...'
    char filename[0x40];     // +0x44, copied from Segments/*.txt enumeration
    int id;                  // +0x84
    int row_count;           // +0x88
    char glyph_columns[0x100][8]; // +0x8c, column-major source grid
    AuthoredSegmentRow rows[255]; // +0x88c
    char unknown_4054[0x4088 - 0x4054];
};

typedef char SegmentCatalogEntry_must_be_0x4088[
    (sizeof(SegmentCatalogEntry) == 0x4088) ? 1 : -1];

struct LevelSegmentSlot {
    int row_base;                 // +0x00
    int row_count;                // +0x04
    int visited;                  // +0x08
    int path_index;               // +0x0c
    char* source_name;            // +0x10
    char glyph_rows[8][0x100];    // +0x14
    AuthoredSegmentRow rows[256]; // +0x814
    int active_row_base;          // +0x4014
    unsigned char hidden;         // +0x4018
    char unknown_4019[0x4218 - 0x4019];
    int runtime_cursor;           // +0x4218
    int runtime_index;            // +0x421c
};

typedef char LevelSegmentSlot_must_be_0x4220[
    (sizeof(LevelSegmentSlot) == 0x4220) ? 1 : -1];

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
    slot->active_row_base = 0;
    slot->path_index = source->id;

    int* result = (int*)source->row_count;
    for (int metadata_row = 0; metadata_row < source->row_count; ++metadata_row) {
        AuthoredSegmentRow* destination = &slot->rows[metadata_row];
        AuthoredSegmentRow* authored = &source->rows[metadata_row];
        destination->flags = authored->flags;
        destination->object_id = authored->object_id;
        destination->object_position_x_bits = authored->object_position_x_bits;
        destination->object_position_y_bits = authored->object_position_y_bits;
        destination->object_position_z_bits = authored->object_position_z_bits;
        destination->object_velocity_x_bits = authored->object_velocity_x_bits;
        destination->object_velocity_y_bits = authored->object_velocity_y_bits;
        destination->object_velocity_z_bits = authored->object_velocity_z_bits;
        destination->parcel_set_id = authored->parcel_set_id;
        destination->local_x_bits = authored->local_x_bits;
        destination->local_y_bits = authored->local_y_bits;
        destination->local_z_bits = authored->local_z_bits;
        destination->path_template_index = authored->path_template_index;
        destination->ring_speed = authored->ring_speed;
        result = (int*)(authored + 1);
    }

    slot->hidden = 0;
    slot->runtime_cursor = 0;
    slot->runtime_index = -1;
    return result;
}
