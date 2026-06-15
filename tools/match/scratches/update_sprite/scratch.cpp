// update_sprite @ 0x44df30 (thiscall, ret)

struct Vector3 {
    float x;
    float y;
    float z;
};

class SpriteManager {
public:
    char paused;
};

extern SpriteManager g_sprite_manager; // data_790f30

class Sprite {
public:
    void update_sprite();
    void kill_sprite();
    char* set_sprite_texture_ref(int texture_id, int frame);

    void* object_ref; // +0x00
    unsigned int flags; // +0x04
    int owner; // +0x08
    Sprite* next; // +0x0c
    Sprite* prev; // +0x10
    char unknown_14[0x3c - 0x14];
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
    char unknown_84[0x9c - 0x84];
    int texture_id; // +0x9c
    int frame_count; // +0xa0
    int frame; // +0xa4
    int frame_step; // +0xa8
    float frame_progress; // +0xac
    float frame_progress_step; // +0xb0
};

void Sprite::update_sprite()
{
    unsigned int current_flags = flags;
    if ((current_flags & 0x800) != 0 && g_sprite_manager.paused != 0) {
        return;
    }

    if ((current_flags & 0x8) == 0) {
        float next_progress = progress_step + progress;
        progress = next_progress;
        if (next_progress > 1.0f || next_progress < 0.0f) {
            progress = 1.0f;
            if ((current_flags & 0x100) == 0) {
                kill_sprite();
            }
            return;
        }

        if (lifetime_step != 0.0f) {
            float next_lifetime = lifetime_step + lifetime;
            lifetime = next_lifetime;
            if (next_lifetime > 1.0f) {
                lifetime_step = 0.0f;
            }
        }
    } else {
        flags = current_flags & ~0x8;
    }

    flags &= ~0x8;

    Vector3* previous = &previous_position;
    Vector3* current = &position;
    *previous = *current;
    current->x += velocity.x;
    float next_y = velocity.y;
    next_y += current->y;
    current->y = next_y;
    current->z += velocity.z;
    velocity.y += gravity_step;
    facing_angle += facing_angle_step;

    if (lifetime_step > 0.0f) {
        flags |= 0x200;
    } else {
        flags &= ~0x200;
    }

    unsigned int animation_flags = flags;
    if ((animation_flags & 0x2000) == 0) {
        return;
    }

    float next_frame_progress = frame_progress_step + frame_progress;
    frame_progress = next_frame_progress;
    if (next_frame_progress > 1.0f) {
        frame_progress = next_frame_progress - 1.0f;
        frame += frame_step;
        int next_frame = frame;

        if ((animation_flags & 0x4000) != 0) {
            if (next_frame == frame_count) {
                frame_step = -1;
                frame = frame_count - 1;
            }
            if (frame == -1) {
                frame = 0;
                frame_step = 1;
            }
        } else {
            if (next_frame == frame_count) {
                frame = 0;
            }
        }

        set_sprite_texture_ref(texture_id, frame);
    }
}
