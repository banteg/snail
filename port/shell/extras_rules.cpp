// Mobile gameplay rules for the Ultimate profile (extras.h, profile.h), from
// the Android release. The wrappers listed in port/wrapped.txt run their
// *_recovered bodies unchanged and, in the Ultimate profile, apply what
// Android does differently.

#include <string.h>

#include "extras.h"
#include "player.h"
#include "rmath_random.h"
#include "score_buckets.h"
#include "sound_effect_manager.h"
#include "sub_tracks.h"
#include "subgame_runtime.h"
#include "track_parcel_runtime.h"
#include "voice_manager.h"

float RAND_recovered(float upper_bound, char* tag) __asm__("_Z14RAND_recoveredfPc");
void subgoldy_collision_recovered(cRSubGoldy* self) __asm__("_ZN10cRSubGoldy19Collision_recoveredEv");

int sprintf(char* buffer, const char* format, ...);

namespace {

// Android cRSubTracks::Init (000850d4) imports Padding, a four-row empty
// segment, beside every level's segments; cRSubGame::BuildLevel (0007e88c)
// then lays it between each pair of segments a Random: level picks. Its slot
// here is the first unused one, after the level's own.
int g_padding_slot = -1;
bool g_padding_turn = false;
int g_padding_picks = 0;
int g_wide_parcels = 0;

}  // namespace

void extras_import_padding(cRSubTracks* level_definition)
{
    g_padding_slot = -1;
    if (!g_port_ultimate || level_definition->random_enabled != 1
        || level_definition->segment_count >= (int)(sizeof(level_definition->segment_slots) / sizeof(SubSegment)))
        return;
    g_padding_slot = level_definition->segment_count;
    level_definition->ImportSegment((char*)"padding.txt", &level_definition->segment_slots[g_padding_slot]);
}

void extras_begin_level_build()
{
    g_padding_turn = false;
    g_padding_picks = 0;
}

// BuildLevel draws each random segment with RAND tagged "Segtra" (or
// "Segdif" in challenge mode). Android skips that draw on every other pick
// and takes Padding instead, so the draws it does make line up with these.
float RAND(float upper_bound, char* tag)
{
    if (g_padding_slot >= 0 && tag && (strcmp(tag, "Segtra") == 0 || strcmp(tag, "Segdif") == 0)) {
        g_padding_turn = !g_padding_turn;
        if (!g_padding_turn) {
            ++g_padding_picks;
            return (float)g_padding_slot;
        }
    }
    return RAND_recovered(upper_bound, tag);
}

// Android cRSubGoldy::Collision (00077f5c) collects a parcel within 1.73 of
// the player; Windows uses 1.24. The recovered sweep collects those within
// 1.24, and this second pass, behind the same gates, those it left between
// 1.24 and 1.73, so they score on the same tick.
void cRSubGoldy::Collision()
{
    bool sweeps = !attachment_exit_pending && !boost_one_tick && !slug_fall_active;
    subgoldy_collision_recovered(this);
    if (!g_port_ultimate || !sweeps)
        return;
    for (int n = 0; n < (int)(sizeof(game->parcel_manager.slots) / sizeof(game->parcel_manager.slots[0])); ++n) {
        if (game->parcel_manager.slots[n].state != PARCEL_STATE_TRACK_ACTIVE)
            continue;
        Vector3 delta;
        delta.x = game->parcel_manager.slots[n].position.x - cached_camera_target_world.x;
        delta.y = game->parcel_manager.slots[n].position.y - cached_camera_target_world.y;
        delta.z = game->parcel_manager.slots[n].position.z - cached_camera_target_world.z;
        if (!(delta.z < 1.0f && delta.Normalize() < 1.73f))
            continue;
        ScoreAdd(SUBGOLDY_SCORE_PARCEL_COLLECT, 0);
        g_voice_manager.Play(VOICE_SET_PACKAGE, VOICE_PLAY_AFTER_GLOBAL_COOLDOWN, -1);
        g_sound_effect_manager.Play(27);
        game->parcel_manager.slots[n].state = PARCEL_STATE_COLLECT_PENDING;
        ++g_wide_parcels;
        int collected = ++parcels_collected;
        if (!game->level_mode)
            sprintf(game->lives_text_widget->text_buffer, "%i/%i", collected, game->level_definition.parcel_count);
    }
}

int extras_padding_pick_count()
{
    return g_padding_picks;
}

int extras_wide_parcel_count()
{
    return g_wide_parcels;
}
