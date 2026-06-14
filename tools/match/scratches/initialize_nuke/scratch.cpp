// initialize_nuke @ 0x447110 (thiscall, ret)

struct Vector3 {
    float x;
    float y;
    float z;
};

struct Game {
    char unknown_00[0x74650];
    float subgame_rate; // +0x74650
};

struct Player {
    char unknown_00[0x70];
    float world_z; // +0x70
    char unknown_74[0x380 - 0x74];
    int player_slot; // +0x380
};

struct Sprite {
    int unknown_00;
    int flags; // +0x04
    char unknown_08[0x48 - 0x08];
    Vector3 position; // +0x48
    Vector3 velocity; // +0x54
    float scale_x; // +0x60
    float scale_y; // +0x64
    int age_or_frame; // +0x68
    int frame_step; // +0x6c
    char unknown_70[0x78 - 0x70];
    int gravity_step; // +0x78
};

struct SpriteManager {
    Sprite* allocate_sprite(int owner, int sprite_id, int texture_a, int texture_b);
};

class NukeController {
public:
    int initialize_nuke();
    int update_nuke();

    int state; // +0x00
    Player* owner_player; // +0x04
    float orbit_axis_step; // +0x08
    float orbit_axis; // +0x0c
    float phase; // +0x10
    float phase_step; // +0x14
    Sprite* sprite_slots[25]; // +0x18
};

extern Game* g_game_base; // data_4df904
extern SpriteManager g_sprite_manager; // data_790f30

int NukeController::initialize_nuke()
{
    int zero = 0;
    if (state == zero) {
        Sprite** slots = sprite_slots;
        int count = 25;

        orbit_axis = owner_player->world_z - 5.0f;
        float rate = g_game_base->subgame_rate;
        phase = 0.0f;
        phase_step = 0.104719758f;
        state = 1;
        orbit_axis_step = rate + rate;

        do {
            Sprite* sprite = g_sprite_manager.allocate_sprite(owner_player->player_slot, 0x83, -1, -1);
            *slots = sprite;
            sprite->flags |= 0x800;
            slots++;

            (*(slots - 1))->age_or_frame = zero;
            (*(slots - 1))->frame_step = zero;
            (*(slots - 1))->scale_x = 3.0f;
            (*(slots - 1))->scale_y = 3.0f;
            Vector3* velocity = &(*(slots - 1))->velocity;
            velocity->z = 0.0f;
            velocity->y = 0.0f;
            velocity->x = 0.0f;
            Vector3* position = &(*(slots - 1))->position;
            position->z = 0.0f;
            position->y = 0.0f;
            position->x = 0.0f;
            (*(slots - 1))->gravity_step = zero;
            count--;
        } while (count);
    }

    return update_nuke();
}
