// spawn_track_parcel @ 0x443730 (thiscall, ret 8)

#include "track_parcel_runtime.h"

class SubgameRuntime {
public:
    TrackParcelRuntime* spawn_track_parcel(Vector3* world_position, void* owner_hint);

    char unknown_000000[0x3bb764];
    char score_stats; // root game +0x3bb764
    char unknown_3bb765[0x3bbae4 - 0x3bb765];
    int parcel_sprite_owner; // root game +0x3bbae4
    char unknown_3bbae8[0x125e480 - 0x3bbae8];
    TrackParcelPool parcel_pool; // root game +0x125e480
};

TrackParcelRuntime* SubgameRuntime::spawn_track_parcel(Vector3* world_position, void*)
{
    TrackParcelRuntime* parcel = parcel_pool.allocate_track_parcel_slot();
    if (parcel != 0) {
        parcel->state = 1;
        parcel->world_position = *world_position;
        parcel->owner = &score_stats;

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
        parcel->sprite->position = parcel->world_position;

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
