// initialize_sprite @ 0x44de90 (thiscall, ret)

class Color4f {
public:
    void set_color_white();

    float r;
    float g;
    float b;
    float a;
};

struct TextureRef;

struct Vector3 {
    float x;
    float y;
    float z;
};

class Sprite {
public:
    void initialize_sprite();

    void* object_ref; // +0x00, initialized to sentinel -1
    unsigned int flags; // +0x04
    int owner; // +0x08
    Sprite* next; // +0x0c
    Sprite* prev; // +0x10
    int unknown_14; // +0x14
    int unknown_18; // +0x18
    TextureRef* texture_ref; // +0x1c
    TextureRef* texture_ref_a; // +0x20
    TextureRef* texture_ref_b; // +0x24
    int draw_mode; // +0x28
    Color4f color; // +0x2c
    Vector3 previous_position; // +0x3c
    Vector3 position; // +0x48
    Vector3 velocity; // +0x54
    float scale_x; // +0x60
    float scale_y; // +0x64
    float progress; // +0x68
    float progress_step; // +0x6c
    float lifetime; // +0x70
    float lifetime_step; // +0x74
    float gravity_step; // +0x78
    float facing_angle; // +0x7c
    float facing_angle_step; // +0x80
    int unknown_84; // +0x84
    float corner_scale; // +0x88
    float facing_refresh_progress; // +0x8c
    float facing_refresh_step; // +0x90
    float depth_offset; // +0x94
    int unknown_98; // +0x98
    int texture_id; // +0x9c
    int frame_count; // +0xa0
    int frame; // +0xa4
    int frame_step; // +0xa8
    float frame_progress; // +0xac
    float frame_progress_step; // +0xb0
};

void Sprite::initialize_sprite()
{
    flags = 0x49;
    color.set_color_white();

    int zero = 0;
    gravity_step = -0.013f;
    draw_mode = zero;
    progress = 0.0f;
    lifetime = 0.0f;
    lifetime_step = 0.0f;
    facing_angle = 0.0f;
    facing_angle_step = 0.0f;
    unknown_84 = zero;
    corner_scale = 1.0f;
    facing_refresh_progress = 0.0f;
    facing_refresh_step = 0.0f;
    depth_offset = -500.0f;
    texture_ref_a = 0;
    texture_ref_b = 0;
    velocity.z = 0.0f;
    velocity.y = 0.0f;
    velocity.x = 0.0f;
    unknown_98 = zero;
    object_ref = (void*)-1;
    texture_id = zero;
    frame_count = zero;
    frame = zero;
    frame_progress = 0.0f;
    frame_progress_step = 0.0f;
    frame_step = 1;
}
