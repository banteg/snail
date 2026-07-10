// spawn_track_parcel @ 0x443730 (thiscall, ret 8)

#include "subgame_runtime.h"

TrackParcelRuntime* SubgameRuntime::spawn_track_parcel(Vector3* world_position, Player*)
{
    TrackParcelRuntime* parcel = parcel_pool.allocate_track_parcel_slot();
    if (parcel != 0) {
        parcel->state = 1;
        parcel->position = *world_position;
        parcel->owner_player = embedded_player();

        Sprite* sprite = g_sprite_manager.allocate_sprite(parcel_sprite_owner, 0x79, -1, -1);
        parcel->sprite = sprite;
        sprite->flags |= 0x800;
        parcel->sprite->progress = 0.0f;
        parcel->sprite->progress_step = 0.0f;
        parcel->sprite->gravity_step = 0.0f;

        Color4f color;
        parcel->sprite->color = *color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f);
        parcel->sprite->size_start = 1.0f;
        parcel->sprite->size_end = 1.0f;
        parcel->sprite->position = parcel->position;

        if (((int)world_position->z & 1) != 0) {
            parcel->bob_phase = 0.0f;
            parcel->bob_phase_step = 0.012820513f;
            return parcel;
        }
        parcel->bob_phase = 0.5f;
        parcel->bob_phase_step = 0.012820513f;
        return parcel;
    }
    return 0;
}
