// update_garbage_hazard @ 0x43f200 (thiscall, ret)
// cRSubGarbage::AI(): hover/contact registration, nuke/contact burst setup,
// burst integration, smoke cadence, teardown, and final sprite roll update.

typedef unsigned int DWORD;

struct Vec3 {
    float x;
    float y;
    float z;
};

struct Sprite {
    char unknown_00[0x48];
    Vec3 position;      // +0x48
    char unknown_54[0x7c - 0x54];
    float local_roll_y; // +0x7c
};

class GarbageHazardSlot;

struct ContactTargetRegistry {
    void append_subgame_contact_target(
        Vec3* position,
        float radius,
        int kind,
        GarbageHazardSlot* object);
};

struct Game {
    char unknown_00[0x09];
    unsigned char paused; // +0x09
    char unknown_0a[0x38 - 0x0a];
    float subgame_rate; // +0x38
    char unknown_3c[0x1270fd4 - 0x3c];
    ContactTargetRegistry contact_targets; // +0x1270fd4
};

struct Player {
    void add_subgoldy_score(int event_id, int value);

    char unknown_00[0x370];
    float heading_roll; // +0x370
    float nuke_effect_progress; // +0x374
    char unknown_378[0x384 - 0x378];
    unsigned char roll_add_enabled; // +0x384
    char unknown_385[0x3a0 - 0x385];
    float roll_add; // +0x3a0
    char unknown_3a4[0x2980 - 0x3a4];
    float interaction_max_z; // +0x2980
};

class GarbageHazardSlot {
public:
    GarbageHazardSlot* update_garbage_hazard();
    GarbageHazardSlot* destroy_garbage_hazard();
    void spawn_garbage_smoke_particle(Vec3* position, Vec3* velocity, Player* player);

    char unknown_00[0x68];
    Vec3 world_position; // +0x68
    char unknown_74[0x80 - 0x74];
    GarbageHazardSlot* next_active; // +0x80
    int state; // +0x84
    int collision_side; // +0x88, 1 right / 2 left
    Game* game; // +0x8c
    Vec3 velocity; // +0x90
    float radius; // +0x9c
    float sprite_y_offset; // +0xa0
    int unknown_a4; // +0xa4
    float burst_rate_step; // +0xa8
    float smoke_timer; // +0xac
    float smoke_timer_step; // +0xb0
    Sprite* sprite; // +0xb4
    char unknown_b8[0xc0 - 0xb8];
    Player* player; // +0xc0
};

double random_signed_float_below(float upper_bound);
double random_float_below(float upper_bound);

GarbageHazardSlot* GarbageHazardSlot::update_garbage_hazard()
{
    Game* result = game;
    if (!result->paused) {
        switch (state) {
        case 0:
            return 0;

        case 1: {
            Vec3* position = &world_position;
            DWORD* sprite_position = (DWORD*)&sprite->position;
            DWORD* source_position = (DWORD*)position;
            sprite_position[0] = source_position[0];
            sprite_position[1] = source_position[1];
            sprite_position[2] = source_position[2];

            Player* owner = player;
            if (world_position.z < owner->interaction_max_z)
                return destroy_garbage_hazard();

            if (owner->nuke_effect_progress > 0.0f) {
                double x = position->x;
                state = 2;
                if (x <= 0.0f)
                    collision_side = 2;
                else
                    collision_side = 1;
                owner->add_subgoldy_score(0, 0);
            }

            game->contact_targets.append_subgame_contact_target(
                &world_position,
                radius,
                0,
                this);
            break;
        }

        case 2: {
            state = 3;
            float random_x = (float)random_signed_float_below(0.1f);
            float random_y = (float)random_float_below(0.2f) + 0.1f;
            double random_z = random_float_below(0.30000001f);
            Game* rate_game = game;
            Vec3* burst_velocity = &velocity;
            double rate = rate_game->subgame_rate;

            float scaled_x = (float)(rate * random_x);
            velocity.x = scaled_x;
            float scaled_y = (float)(random_y * rate);
            velocity.y = scaled_y;
            float scaled_z = (float)(random_z * rate);
            velocity.z = scaled_z;

            int side = collision_side;
            if (side == 1) {
                double adjusted_x = burst_velocity->x;
                if (adjusted_x < 0.0f)
                    adjusted_x = -adjusted_x;
                burst_velocity->x = (float)adjusted_x;
            } else if (side == 2) {
                double adjusted_x = burst_velocity->x;
                if (adjusted_x < 0.0f)
                    adjusted_x = -adjusted_x;
                burst_velocity->x = (float)-adjusted_x;
            }

            int sign;
            if (burst_velocity->x >= 0.0f)
                sign = burst_velocity->x != 0.0f;
            else
                sign = -1;
            unknown_a4 = 0;
            burst_velocity->x =
                (float)((double)sign * 0.2f * rate_game->subgame_rate + burst_velocity->x);
            burst_rate_step = rate_game->subgame_rate * 0.0083333338f;
            smoke_timer = 0.0f;
            smoke_timer_step = rate_game->subgame_rate * 0.27777779f;
        }
            // fall through

        case 3: {
            world_position.x = velocity.x + world_position.x;
            world_position.y = velocity.y + world_position.y;
            world_position.z = velocity.z + world_position.z;

            DWORD* sprite_position = (DWORD*)&sprite->position;
            DWORD* source_position = (DWORD*)&world_position;
            sprite_position[0] = source_position[0];
            sprite_position[1] = source_position[1];
            sprite_position[2] = source_position[2];

            Game* owner_game = game;
            velocity.y = owner_game->subgame_rate
                    * owner_game->subgame_rate
                    * -0.0099999998f
                + velocity.y;

            Player* owner = player;
            if (world_position.y < -10.0f || world_position.z < owner->interaction_max_z)
                return destroy_garbage_hazard();

            float next_smoke_timer = smoke_timer_step + smoke_timer;
            smoke_timer = next_smoke_timer;
            if (next_smoke_timer > 1.0f) {
                smoke_timer = 0.0f;
                spawn_garbage_smoke_particle(&world_position, &velocity, owner);
            }
            break;
        }

        default:
            break;
        }

        sprite->local_roll_y = player->heading_roll + sprite_y_offset;
        Player* roll_result = player;
        if (roll_result->roll_add_enabled == 1)
            sprite->local_roll_y = roll_result->roll_add + sprite->local_roll_y;
        return (GarbageHazardSlot*)roll_result;
    }
    return (GarbageHazardSlot*)result;
}
