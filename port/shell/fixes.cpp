// Fixes for the original's own bugs (fixes.h, docs/port/original-bugs.md).
// The wrappers listed in port/wrapped.txt run their *_recovered bodies
// unchanged and, in the Ultimate profile, correct what the original got wrong
// around them.

#include "d3d8_device.h"
#include "fixes.h"
#include "game_root.h"
#include "garbage_hazard_slot.h"
#include "player.h"
#include "profile.h"
#include "slug_hazard_types.h"
#include "sprite.h"
#include "subgame_runtime.h"

void subgame_add_slug_recovered(cRSubGame* self, cRSubLoc* cell, cRSubGoldy* player)
    __asm__("_ZN9cRSubGame17AddSlug_recoveredEP8cRSubLocP10cRSubGoldy");
void subgame_add_garbage_recovered(cRSubGame* self, cRSubLoc* cell, cRSubGoldy* player)
    __asm__("_ZN9cRSubGame20AddGarbage_recoveredEP8cRSubLocP10cRSubGoldy");
int draw_sprite_quad_recovered(Vector3* position, cRSprite* sprite);

namespace {

// The facing cRSlug::AI and cRSubGarbage::AI give their sprite every tick.
float hazard_facing(const cRSubGoldy* player, float attachment_facing_angle)
{
    float facing = player->heading_roll + attachment_facing_angle;
    if (player->follow_state.active == 1)
        facing += player->follow_state.orientation_b;
    return facing;
}

template <typename Slot, int Capacity>
int first_inactive(Slot (&slots)[Capacity])
{
    for (int i = 0; i < Capacity; ++i) {
        if (slots[i].state == 0)
            return i;
    }
    return -1;
}

}  // namespace

// Hazards upright for their first frame: AddSlug and AddGarbage (both
// byte-matched) work out the hazard's angle on the track with CalcRealPos but
// leave its new sprite upright, and the hazard's AI turns it only on the next
// tick. Both take the first free slot, so the slot free before the call is the
// one they fill.
void cRSubGame::AddSlug(cRSubLoc* cell, cRSubGoldy* player)
{
    int slot = first_inactive(slug_hazards.slots);
    subgame_add_slug_recovered(this, cell, player);
    if (g_port_ultimate && slot >= 0) {
        cRSlug& slug = slug_hazards.slots[slot];
        slug.sprite->facing_angle = hazard_facing(player, slug.attachment_facing_angle);
    }
}

void cRSubGame::AddGarbage(cRSubLoc* cell, cRSubGoldy* player)
{
    int slot = first_inactive(garbage_hazards.slots);
    subgame_add_garbage_recovered(this, cell, player);
    if (g_port_ultimate && slot >= 0) {
        cRSubGarbage& garbage = garbage_hazards.slots[slot];
        garbage.sprite->facing_angle = hazard_facing(player, garbage.attachment_facing_angle);
    }
}

// Background streaks cutting holes in the road: cRStarManager::Init is the
// only producer of StarTail sprites in the background scene. They sit 50 units
// away, but the world is visible to 52, so writing their depth punches moving
// holes in the last two units of road when the world pass follows. They must
// still blend over the sky.
int draw_sprite_quad(Vector3* position, cRSprite* sprite)
{
    bool background_star = sprite->texture_ref == g_sprite_texture_table[32]
        && (sprite->flags & RENDER_SCENE_MASK) == RENDER_SCENE_OVERLAY_1;
    if (!g_port_ultimate || !background_star)
        return draw_sprite_quad_recovered(position, sprite);

    int previous = set_emulated_depth_write(0);
    int result = draw_sprite_quad_recovered(position, sprite);
    set_emulated_depth_write(previous);
    return result;
}

int fixes_upright_hazard_count()
{
    int upright = 0;
    for (const cRSlug& slug : g_game->subgame.slug_hazards.slots) {
        if (slug.state == SUB_SLUG_STATE_ACTIVE && slug.attachment_facing_angle != 0.0f
            && slug.sprite->facing_angle == 0.0f)
            ++upright;
    }
    for (const cRSubGarbage& garbage : g_game->subgame.garbage_hazards.slots) {
        if (garbage.state == SUB_GARBAGE_STATE_ACTIVE && garbage.attachment_facing_angle != 0.0f
            && garbage.sprite->facing_angle == 0.0f)
            ++upright;
    }
    return upright;
}
