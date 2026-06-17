#ifndef TEXTURE_SET_SELECTOR_H
#define TEXTURE_SET_SELECTOR_H

#include "object_render_types.h"
#include "sprite.h"

struct TextureSetSelector {
    void select_level_track_texture_set(int texture_set); // @ 0x410730

    TextureRef* primary_textures[4]; // +0x00
    TextureRef* secondary_textures[4]; // +0x10
    int current_texture_set; // +0x20
};

#endif
