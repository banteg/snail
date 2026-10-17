// cRLogo::Open @ 0x419110 (thiscall)

#include <stdio.h>

#include "bod_types.h"
#include "intro_screen_runtime.h"
#include "object_render_types.h"
#include "rshell.h"
#include "sprite.h"

void cRLogo::Open()
{
    for (int logo_index = 0;
         logo_index < LOGO_IMAGE_DONOR_CAPACITY;
         ++logo_index) {
        image_donors[logo_index].SetObject(
            g_object_list.Add());
        Object* object = image_donors[logo_index].object;
        load_object_definition("Objects/Font3D", object);
        object = image_donors[logo_index].object;
        object->flags |= OBJECT_FLAG_DYNAMIC_VERTICES;
    }

    int texture_count;
    char texture_names[0x80][0x80];
    enumerate_matching_archive_or_fs_entries("Intro", "*.tga", &texture_count, texture_names);

    int result = texture_count;
    int index = 0;
    if (result > 0) {
        char* name = texture_names[0];
        do {
            char texture_path[0x80];
            sprintf(texture_path, "Intro/%s", name);
            cRTexture* texture = g_texture_refs.Add(texture_path, 0, 0);
            texture->flags |= TEXTURE_REF_REGISTERED;
            result = texture_count;
            ++index;
            name += 0x80;
        } while (index < result);
    }
}
