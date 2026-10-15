// Presentation fixes shared by the browser and native presenters. Keep the
// recovered renderer unchanged; port/wrapped.txt redirects this narrow seam.

#include "d3d8_device.h"
#include "sprite.h"

int draw_sprite_quad_recovered(Vector3* position, cRSprite* sprite);

int draw_sprite_quad(Vector3* position, cRSprite* sprite)
{
    // cRStarManager::Init is the only producer of StarTail sprites in this
    // background scene. They sit 50 units away, but the world is visible to
    // 52: writing their depth punches moving holes in the last two units of
    // road when the world pass follows. They must still blend over the sky.
    bool background_star = sprite->texture_ref == g_sprite_texture_table[32]
        && (sprite->flags & RENDER_SCENE_MASK) == RENDER_SCENE_OVERLAY_1;
    if (!background_star)
        return draw_sprite_quad_recovered(position, sprite);

    int previous = set_emulated_depth_write(0);
    int result = draw_sprite_quad_recovered(position, sprite);
    set_emulated_depth_write(previous);
    return result;
}
