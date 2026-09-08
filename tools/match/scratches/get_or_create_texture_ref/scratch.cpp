// get_or_create_texture_ref @ 0x44e810 (thiscall, ret 0xc)

#include "sprite.h"
#include "rtext.h"

#include "rdebug.h"

cRTexture* cRTextures::Add(
    char* texture_path, void* payload, int flags)
{
    int i = 0;
    int current;
    cRTexture* result;

    if (count == capacity) {
        report_errorf("Too many Texture References - Increase TextureList.Init(MAX) in g0.cpp");
    }

    if ((flags & TEXTURE_REF_DISABLE_PATH_REUSE) == 0 && 0 < count) {
        char* cursor = entries[0].name;
        while (i < count) {
            if (RTextCompStart(cursor, texture_path) != 0)
                goto found_existing;
            ++i;
            cursor += sizeof(cRTexture);
        }
    }

    RTextCopy(entries[count].name, texture_path);
    current = count;
    entries[current].slot_index = current;
    entries[count].flags = 0;
    entries[count].flags = TEXTURE_REF_REGISTERED;
    entries[count].texture_ref = payload;
    entries[count].mip_levels = 1;

    result = &entries[count];
    ++count;
    return result;

found_existing:
    return &entries[i];
}
