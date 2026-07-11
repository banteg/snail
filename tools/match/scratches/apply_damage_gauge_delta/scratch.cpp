// apply_damage_gauge_delta @ 0x4413f0 (thiscall, ret 0x8)
// Hit-flash side-effect chain + gauge fill clamp. Gate: sign bit of
// game+0x4300b4 (unforced only); state 2 blocks unforced positive deltas
// and blocks unforced negative ones while game+0x42ff60 == 1.

#include "damage_guage.h"
#include "voice_manager.h"

struct SnailSkinTransition;
struct AnimDispatcher;

extern char* g_game_base; // data_4df904
extern char g_damage_gate_byte[];          // 0x4300b4, sign bit blocks unforced
extern char g_negative_delta_block_byte[]; // 0x42ff60
extern char g_damage_gauge_anim_suppress_offset[]; // 0x430054
extern char g_snail_skin_transition[];     // 0x430938
extern char g_player_presentation_offset[]; // 0x432700

struct SnailSkinTransitionApi {
    void change_snail_skin(int slot_id, float duration_seconds); // @ 0x445fd0, matched
};

struct AnimDispatcherApi {
    void dispatch_cutscene_animation(int animation, int immediate, int initial_frame);
};

void DamageGuage::apply_damage_gauge_delta(float delta, char force)
{
    if (((*(unsigned char*)(g_damage_gate_byte + (int)g_game_base) & 0x80) == 0 || force)
        && (state != 2
            || (delta <= 0.0f
                && (delta >= 0.0f || *(g_negative_delta_block_byte + (int)g_game_base) != 1)))) {
        if (hit_flash_progress == 0.0f && delta > 0.0f) {
            ((SnailSkinTransitionApi*)(g_snail_skin_transition + (int)g_game_base))
                ->change_snail_skin(1, 0.2f);
            if (g_voice_manager.play_voice_manager(0, 1, -1)) {
                hit_flash_progress = hit_flash_step;
            } else {
                if (g_voice_manager.play_voice_manager(9, 0, -1))
                    hit_flash_progress = hit_flash_step;
                if (!*(g_damage_gauge_anim_suppress_offset + (int)g_game_base)) {
                    ((AnimDispatcherApi*)(g_player_presentation_offset + (int)g_game_base))
                        ->dispatch_cutscene_animation(6, 1, -1);
                    ((AnimDispatcherApi*)(g_player_presentation_offset + (int)g_game_base))
                        ->dispatch_cutscene_animation(1, 0, -1);
                }
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
