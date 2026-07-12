// open_logo @ 0x419110 (thiscall)

#include "bod_types.h"
#include "intro_screen_runtime.h"
#include "object_render_types.h"
#include "sprite.h"

int load_object_definition(char* path, Object* object); // @ 0x44c420
void enumerate_matching_archive_or_fs_entries(
    char* directory,
    char* pattern,
    int* out_count,
    char* out_names); // @ 0x431740
int sprintf(char* buffer, char* format, ...);

int Logo::open_logo()
{
    LogoLetter* slot = &image_donors[0];
    int logo_count = LOGO_IMAGE_DONOR_CAPACITY;
    do {
        slot->set_bod_object(g_object_list.add_object_to_list());
        Object* object = slot->object;
        load_object_definition("Objects/Font3D", object);
        object = slot->object;
        object->flags |= 4;
        ++slot;
        --logo_count;
    } while (logo_count != 0);

    int texture_count;
    char texture_names[0x4000];
    enumerate_matching_archive_or_fs_entries("Intro", "*.tga", &texture_count, texture_names);

    int result = texture_count;
    int index = 0;
    if (result > 0) {
        char* name = texture_names;
        do {
            char texture_path[0x80];
            sprintf(texture_path, "Intro/%s", name);
            TextureRef* texture = g_texture_refs.get_or_create_texture_ref(texture_path, 0, 0);
            texture->flags |= TEXTURE_REF_REGISTERED;
            result = texture_count;
            ++index;
            name += 0x80;
        } while (index < result);
    }
    return result;
}
