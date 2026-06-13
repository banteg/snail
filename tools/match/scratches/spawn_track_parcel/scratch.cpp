// spawn_track_parcel @ 0x443730 (thiscall, ret 8)

struct Vector3 {
    float x;
    float y;
    float z;
};

struct Color4f {
    Color4f* set_color_rgba(float r, float g, float b, float a);

    float r;
    float g;
    float b;
    float a;
};

struct Sprite {
    int unknown_00;
    int flags; // +0x04
    char unknown_08[0x2c - 0x08];
    Color4f color; // +0x2c
    char unknown_3c[0x48 - 0x3c];
    Vector3 position; // +0x48
    char unknown_54[0x60 - 0x54];
    float scale_x; // +0x60
    float scale_y; // +0x64
    int unknown_68; // +0x68
    int unknown_6c; // +0x6c
    char unknown_70[0x78 - 0x70];
    int unknown_78; // +0x78
};

struct SpriteManager {
    Sprite* allocate_sprite(int owner, int sprite_id, int texture_a, int texture_b);
};

extern SpriteManager g_sprite_manager; // data_790f30

struct TrackParcelRuntime {
    virtual int update_track_parcel();

    char unknown_04[0x10 - 0x04];
    Vector3 world_position; // +0x10
    char unknown_1c[0x38 - 0x1c];
    int state; // +0x38
    char unknown_3c[0x54 - 0x3c];
    Sprite* sprite; // +0x54
    char unknown_58[0x5c - 0x58];
    float bob_phase; // +0x5c
    float bob_phase_step; // +0x60
    void* owner; // +0x64
    char unknown_68[0x8c - 0x68];
};

struct TrackParcelPool {
    TrackParcelRuntime* allocate_track_parcel_slot();
};

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
        parcel->sprite->unknown_68 = 0;
        parcel->sprite->unknown_6c = 0;
        parcel->sprite->unknown_78 = 0;

        Color4f color;
        parcel->sprite->color = *color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f);
        parcel->sprite->scale_x = 1.0f;
        parcel->sprite->scale_y = 1.0f;
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
