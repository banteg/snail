// load_builtin_segment_definitions @ 0x448060 (thiscall, ret 0x4)

class LevelSegmentSlotStore {
public:
    char* load_builtin_segment_definitions(char** builtins);
};

char* LevelSegmentSlotStore::load_builtin_segment_definitions(
    char** builtins)
{
    int* slot_base = (int*)this;
    char** builtin_table = builtins;

    *slot_base = 0;
    slot_base[431665] = 1000;

    char* result = *(char**)(builtin_table[0] + 0x28);
    if (*result != 0) {
        do {
            int slot_index = *slot_base;
            char* first_row = *(char**)(builtin_table[slot_index] + 0x28);
            int row_count = 0;
            if (*first_row != 0) {
                do {
                    ++row_count;
                } while (first_row[row_count] != 0);
            }

            *(int*)((char*)slot_base + 0x4220 * slot_index + 8) = row_count;
            *(int*)builtin_table[*slot_base] = row_count;

            int grid_offset = 0;
            int source_offset = 0x28;
            do {
                int active_slot = *slot_base;
                int column = 0;
                int source_row = *(int*)(builtin_table[active_slot] + source_offset);
                char glyph = *(char*)source_row;
                do {
                    int destination = 0x4220 * active_slot + grid_offset + column;
                    ++column;
                    *((char*)slot_base + destination + 0x18) = glyph;
                    active_slot = *slot_base;
                    source_row = *(int*)(builtin_table[active_slot] + source_offset);
                    glyph = *(char*)(source_row + column);
                } while (glyph != 0);
                source_offset += 4;
                grid_offset += 0x100;
            } while (source_offset < 0x48);

            int active_slot = *slot_base;
            *(int*)((char*)slot_base + 0x4220 * active_slot + 0x14) =
                *(int*)(builtin_table[active_slot] + 0x20);

            active_slot = *slot_base;
            *(int*)((char*)slot_base + 0x4220 * active_slot + 0x10) =
                *(int*)(builtin_table[active_slot] + 0x1c);

            int next_index = *slot_base + 1;
            *slot_base = next_index;
            result = *(char**)(builtin_table[next_index] + 0x28);
        } while (*result != 0);
    }

    return result;
}
