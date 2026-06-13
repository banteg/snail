// explode_slug_hazard @ 0x43f680 (thiscall, ret)

struct Vector3 {
    float x;
    float y;
    float z;
};

class Color4f {
public:
    void set_color_grayscale(float intensity);

    float r;
    float g;
    float b;
    float a;
};

struct Sprite {
    int unknown_00;
    unsigned int flags;      // +0x04
    char unknown_08[0x2c - 0x08];
    Color4f color;           // +0x2c
    char unknown_3c[0x48 - 0x3c];
    Vector3 position;        // +0x48
    Vector3 velocity;        // +0x54
    float scale_x;           // +0x60
    float scale_y;           // +0x64
    int age_or_frame;        // +0x68
    float frame_step;        // +0x6c
    int unknown_70;
    int unknown_74;
    float gravity_step;      // +0x78
    char unknown_7c[0x88 - 0x7c];
    float doubled_size;      // +0x88
};

struct SpriteManager {
    Sprite* allocate_sprite(int owner, int sprite_id, int texture_a, int texture_b);
};

struct Game {
    char unknown_00[0x38];
    float track_center_x;          // +0x38
    char unknown_3c[0x3bbb7c - 0x3c];
    float slug_explosion_base_z;   // +0x3bbb7c
};

class SlugHazardRuntime {
public:
    int explode_slug_hazard();

    char unknown_00[0x68];
    Vector3 world_position; // +0x68
    char unknown_74[0x88 - 0x74];
    Game* owner_game;       // +0x88
};

extern SpriteManager g_sprite_manager; // data_790f30

int next_math_random_value();

int SlugHazardRuntime::explode_slug_hazard()
{
    int count = 70;
    int result;
    do {
        float spread = (float)next_math_random_value() * 0.0000061035157f + 0.2f;
        float size = (float)next_math_random_value() * 0.000030517578f;
        size = size * 0.75f + 0.25f;
        Sprite* sprite = g_sprite_manager.allocate_sprite(1, 129, -1, -1);
        sprite->age_or_frame = 0;
        sprite->flags |= 0x802;
        sprite->doubled_size = size + size;
        float frame_step =
            1.0f
            / (((float)next_math_random_value() * 0.000015258789f + 0.60000002f) * 60.0f)
            * owner_game->track_center_x;
        sprite->unknown_70 = 0;
        sprite->unknown_74 = 0;
        sprite->frame_step = frame_step;
        float intensity = (float)next_math_random_value() * 0.0000091552738f + 0.69999999f;
        sprite->color.set_color_grayscale(intensity);
        sprite->scale_x = size * 0.30000001f;
        sprite->scale_y = size * 1.2f;
        float track_center = owner_game->track_center_x;
        float gravity_step = track_center * track_center;
        gravity_step *= -0.0099999998f;
        sprite->gravity_step = gravity_step * 2.2f;

        float side = ((float)next_math_random_value() - 16384.0f) * spread * 0.000061035156f;
        float up = (float)next_math_random_value() * (spread + 0.30000001f) * 0.000030517578f;
        Game* game = owner_game;
        float forward =
            (float)next_math_random_value() * spread * 0.000030517578f
            + game->slug_explosion_base_z;
        float speed = game->track_center_x;
        Vector3 staged_velocity;
        staged_velocity.x = speed * side;
        staged_velocity.y = up * speed;
        staged_velocity.z = forward * speed;
        sprite->velocity = staged_velocity;

        Vector3* velocity = &sprite->velocity;
        float position_scale = (float)next_math_random_value() * 0.00030517578f;
        Vector3 position_offset;
        position_offset.x = position_scale * velocity->x;
        position_offset.y = position_scale * velocity->y;
        position_offset.z = position_scale * velocity->z;
        Vector3 staged_position;
        staged_position.x = position_offset.x + world_position.x;
        staged_position.y = position_offset.y + world_position.y;
        staged_position.z = position_offset.z + world_position.z;
        sprite->position = staged_position;
        result = --count;
    } while (result);

    return result;
}
