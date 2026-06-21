// get_or_create_texture_ref @ 0x44e810 (thiscall, ret 0xc)

#include "sprite.h"

void report_errorf(char* format, ...);
void copy_c_string(char* destination, char* source);
unsigned char strings_equal_case_insensitive(char* left, char* right); // @ 0x431dc0

TextureRef* TextureRefList::get_or_create_texture_ref(char* texture_path, int arg3, int flags)
{
    int i = 0;
    int current;
    TextureRef* result;

    if (count == capacity) {
        report_errorf("Too many Texture References - Increase TextureList.Init(MAX) in g0.cpp");
    }

    if ((flags & 0x800) == 0 && count > 0) {
        char* cursor = entries[0].name;
        while (i < count) {
            if (strings_equal_case_insensitive(cursor, texture_path) != 0)
                goto found_existing;
            ++i;
            cursor += sizeof(TextureRef);
        }
    }

    copy_c_string(entries[count].name, texture_path);
    current = count;
    entries[current].slot_index = current;
    entries[count].flags = 0;
    entries[count].flags = 0x400;
    entries[count].texture_ref = (void*)arg3;
    entries[count].mip_levels = 1;

    result = &entries[count];
    ++count;
    return result;

found_existing:
    return &entries[i];
}
