// play_slug_voice @ 0x43f560 (thiscall, ret 0x4)

#include "game_root.h"
#include "slug_hazard_types.h"

void play_voice_backend(int sample_id, float volume, float pitch, float pan);

void Slug::play_slug_voice(int sample_index)
{
    if (voice_active == 0) {
        GameRoot* game = g_game;
        if (game->subgame.slug_voice_manager.active == 0) {
            game->subgame.slug_voice_manager.progress =
                game->subgame.slug_voice_manager.step;
            g_game->subgame.slug_voice_manager.active = 1;
            voice_active = 1;
            voice_progress = 0.0f;
            play_voice_backend(sample_index, 1.0f, -1.0f, 0.0f);
        }
    }
}
