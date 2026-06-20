// run_frame_update @ 0x40a2a0 (thiscall, ret)

#include "active_bod.h"
#include "audio_system.h"
#include "cheat_state.h"
#include "frontend_overlay_color_lerp.h"
#include "game_root.h"
#include "mouse_cursor_state.h"
#include "sprite.h"
#include "voice_manager.h"

class FrontendTransitionOverlay {
public:
    void update_frontend_transition_overlay();
};

class RuntimeCallback {
public:
    virtual void update();
};

class EnemyManager {
public:
    void initialize_enemy_manager();
};

int report_errorf(const char* format, ...);
int queue_axis_aligned_textured_quad(
    int texture_id,
    float x,
    float y,
    float width,
    float height,
    unsigned int color,
    Color4f* tint,
    int layer);

extern CheatState g_completion_snapshot_flags; // byte_4b2f40

int GameRoot::run_frame_update()
{
    char* base = (char*)this;

    ((FrontendTransitionOverlay*)(base + 0x24))->update_frontend_transition_overlay();
    g_audio_backend.noop_runtime_ai();
    g_completion_snapshot_flags.update_cheat();
    g_voice_manager.update_voice_manager();

    float next_frame_accum = *(float*)(base + 0x518) + 1.0f;
    int sprite_update_count = 0;
    int next_frame_counter = *(int*)(base + 0x51c) + 1;
    MouseCursorState* mouse = (MouseCursorState*)(base + 0x290);
    *(int*)(base + 0x38) = 0;
    *(float*)(base + 0x518) = next_frame_accum;
    *(int*)(base + 0x3c) = 1;
    *(int*)(base + 0x51c) = next_frame_counter;
    *(unsigned char*)(base + 0x520) = 1;

    int bod_update_count = 0;
    if (mouse->is_mouse_captured()) {
        if (*(unsigned char*)(base + 0x2a4) != 0) {
            *(unsigned char*)(base + 0x2a4) = 0;
        } else {
            Color4f color;
            Color4f* tint = color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f);
            float mouse_y = *(float*)(base + 0x2a0) - 7.0f;
            float mouse_x = *(float*)(base + 0x29c) - 8.0f;
            queue_axis_aligned_textured_quad(
                22,
                mouse_x,
                mouse_y,
                64.0f,
                64.0f,
                0x1000000,
                tint,
                7);
        }
    }

    if (*(float*)(base + 0x518) > 1.0f) {
        do {
            *(float*)(base + 0x518) = *(float*)(base + 0x518) - 1.0f;
            ((FrontendOverlayColorLerp*)(base + 0x2a8))->draw_frontend_overlay_color_lerp();

            ActiveBod* bod = *(ActiveBod**)(base + 0x5ac);
            if (bod != 0) {
                do {
                    if ((bod->list_flags & 0x10) != 0) {
                        report_errorf("Debug Bod AI");
                    }

                    ActiveBod* next_bod = bod->list_next;
                    if (next_bod != 0) {
                        next_bod->list_flags |= 0x40;
                    }

                    bod->update_active_bod();
                    bod = next_bod;
                    ++bod_update_count;
                    if (next_bod == 0) {
                        break;
                    }

                    next_bod->list_flags &= ~0x40;
                } while (true);
            }

            ((RuntimeCallback*)(base + 0x124))->update();
            if (*(int*)(base + 0x74658) == 6) {
                ((RuntimeCallback*)(base + 0x31c))->update();
            }

            Sprite** bucket = g_sprite_active_heads;
            do {
                Sprite* sprite = *bucket;
                if (sprite != 0) {
                    Sprite* next_sprite;
                    do {
                        next_sprite = sprite->next;
                        sprite->update_sprite();
                        ++sprite_update_count;
                        sprite = next_sprite;
                    } while (next_sprite != 0);
                }
                ++bucket;
            } while ((int)bucket < (int)&g_sprite_free_head);

            ((EnemyManager*)(base + 0x12e55ec))->initialize_enemy_manager();
            *(unsigned char*)(base + 0x520) = 0;
        } while (*(float*)(base + 0x518) > 1.0f);
    }

    return *(int*)(base + 0x38);
}
