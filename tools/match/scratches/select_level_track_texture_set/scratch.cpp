// select_level_track_texture_set @ 0x410730 (thiscall, ret 0x4)

#include "texture_set_selector.h"

double random_float_below(float upper_bound, int zero);

void TextureSetSelector::select_level_track_texture_set(int texture_set)
{
    int selected;

    switch (texture_set) {
    case 0:
        selected = 0;
        break;
    case 1:
        selected = 1;
        break;
    case 2:
        selected = 2;
        break;
    case 3:
        selected = 3;
        break;
    case 5:
        selected = (int)random_float_below(4.0f, 0);
        break;
    default:
        selected = texture_set;
        break;
    }

    int previous = current_texture_set;
    if (selected != previous) {
        g_object_list.replace_object_list_texture_refs(
            primary_textures[selected], primary_textures[previous]);
        g_object_list.replace_object_list_texture_refs(
            secondary_textures[selected], secondary_textures[current_texture_set]);
        current_texture_set = selected;
    }
}
