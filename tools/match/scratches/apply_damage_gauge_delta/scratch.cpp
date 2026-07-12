// apply_damage_gauge_delta @ 0x4413f0 (thiscall, ret 0x8)
// Hit-flash side-effect chain + gauge fill clamp. Gate: sign bit of the
// owning Player's movement flags (unforced only); state 2 blocks unforced
// positive deltas and negative ones during a trampoline bounce.

#include "damage_guage.h"
#include "game_root.h"
#include "voice_manager.h"

extern GameRoot* g_game; // data_4df904

void DamageGuage::apply_damage_gauge_delta(float delta, char force)
{
    if (((g_game->subgame.embedded_player()->movement_flags & 0x80) == 0 || force)
        && (state != 2
            || (delta <= 0.0f
                && (delta >= 0.0f
                    || g_game->subgame.embedded_player()->trampoline_bounce_active != 1)))) {
        if (hit_flash_progress == 0.0f && delta > 0.0f) {
            g_game->subgame.embedded_player()->presentation.snail_skin
                .change_snail_skin(1, 0.2f);
            if (!g_voice_manager.play_voice_manager(0, 1, -1)) {
                if (g_voice_manager.play_voice_manager(9, 0, -1))
                    hit_flash_progress = hit_flash_step;
                if (!g_game->subgame.embedded_player()->control_override_active) {
                    g_game->subgame.embedded_player()->presentation
                        .dispatch_cutscene_animation(6, 1, -1);
                    g_game->subgame.embedded_player()->presentation
                        .dispatch_cutscene_animation(1, 0, -1);
                }
            } else {
                hit_flash_progress = hit_flash_step;
            }
        }
        float updated = delta + fill;
        fill = updated;
        if (updated < 0.0f) {
            updated = 0.0f;
        } else {
            if (updated > 1.0f)
                updated = 1.0f;
        }
        fill = updated;
    }
}
