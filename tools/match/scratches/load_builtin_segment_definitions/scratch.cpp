// load_builtin_segment_definitions @ 0x448060 (thiscall, ret 0x4)

struct AuthoredSegmentRow {
    int flags;
    int parcel_set_id;
    int local_x_bits;
    int local_y_bits;
    int local_z_bits;
    int object_id;
    int object_position_x_bits;
    int object_position_y_bits;
    int object_position_z_bits;
    int object_rotation_x_bits;
    int object_rotation_y_bits;
    int object_rotation_z_bits;
    int attachment_template_index;
    int row_event_id;
};

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

struct BuiltinSegmentDefinition {
    int row_count;            // +0x00, filled after measuring row 0
    char unknown_04[0x18];
    int path_index;           // +0x1c
    char* source_name;        // +0x20
    int unknown_24;
    char* glyph_rows[8];      // +0x28
};

class LevelSegmentSlotStore {
public:
    int count; // +0x00
    LevelSegmentSlot slots[103]; // +0x04

    char* load_builtin_segment_definitions(BuiltinSegmentDefinition** builtins);
};

char* LevelSegmentSlotStore::load_builtin_segment_definitions(
    BuiltinSegmentDefinition** builtins)
{
    count = 0;
    slots[102].row_base = 1000;

    char* result = builtins[0]->glyph_rows[0];
    if (*result != 0) {
        do {
            int slot_index = count;
            char* first_row = builtins[slot_index]->glyph_rows[0];
            int row_count = 0;
            while (first_row[row_count] != 0)
                ++row_count;

            slots[slot_index].row_count = row_count;
            builtins[count]->row_count = row_count;

            int grid_offset = 0;
            int row_index = 0;
            do {
                int active_slot = count;
                int column = 0;
                char* source_row = builtins[active_slot]->glyph_rows[row_index];
                char glyph = *source_row;
                do {
                    int destination = 0x4220 * active_slot + grid_offset + column;
                    ++column;
                    *((char*)&slots[0] + destination + 0x14) = glyph;
                    active_slot = count;
                    source_row = builtins[active_slot]->glyph_rows[row_index];
                    glyph = source_row[column];
                } while (glyph != 0);
                ++row_index;
                grid_offset += 0x100;
            } while (row_index < 8);

            int active_slot = count;
            slots[active_slot].source_name = builtins[active_slot]->source_name;

            active_slot = count;
            slots[active_slot].path_index = builtins[active_slot]->path_index;

            int next_index = count + 1;
            count = next_index;
            result = builtins[next_index]->glyph_rows[0];
        } while (*result != 0);
    }

    return result;
}
