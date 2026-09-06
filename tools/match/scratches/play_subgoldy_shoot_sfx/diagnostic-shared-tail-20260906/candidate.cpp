// play_subgoldy_shoot_sfx @ 0x43afd0, authored cRSubGoldy::PlayShootSfx()

#include "audio_system.h"
#include "game_root.h"
#include "player.h"


int gRMathRand2();

void cRSubGoldy::PlayShootSfx()
{
    unsigned int flags = shoot_flags;
    int sound_id;

    if ((flags & 7) != 0) {
        int variant = (int)(
            (float)gRMathRand2() * 0.0000305175781f * 2.0f);
        shoot_sfx_variant_sample = variant;
        sound_id = variant + 17;
    } else if ((flags & 0x18) != 0) {
        int variant = (int)(
            (float)gRMathRand2() * 0.0000305175781f * 3.0f);
        shoot_sfx_variant_sample = variant;
        sound_id = variant + 19;
    } else {
        if ((flags & 0x60) == 0)
            return;
        int variant = (int)(
            (float)gRMathRand2() * 0.0000305175781f * 3.0f);
        shoot_sfx_variant_sample = variant;
        sound_id = variant + 22;
    }

    if (sound_id != -1) {
        if (!attachment_exit_pending)
            goto play_direct;
        {
            Vector3 vector;
            Vector3 normalized_vector;

            vector =
                g_game->players[0].transform.position - transform.position;

            normalized_vector = vector;
            float distance = normalized_vector.Normalize();
            float volume = distance / -60.0f + 1.0f;
            if (volume < 0.0f) {
                volume = 0.0f;
            }
            if (volume > 1.0f) {
                volume = 1.0f;
            }
            g_sound_effect_manager.PlayVolume(sound_id, volume);
        }
        return;
play_direct:
        g_sound_effect_manager.Play(sound_id);
    }
}
