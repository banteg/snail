// update_row_event_display @ 0x404cf0 (fastcall, ret)

#include "track_parcel_runtime.h"

extern char* g_game_base; // data_4df904

struct Vec3 {
    float x;
    float y;
    float z;
};

struct FrontendWidget {
    void hide_border_init();
    void unhide_border_init();

    char unknown_00[0x1a0];
    unsigned int widget_flags; // +0x1a0
    char unknown_1a4[0x128];
    char text_buffer[2];       // +0x2cc
};

struct GameRuntime {
    TrackParcelRuntime* spawn_track_parcel(float* world_position, void* owner);
};

struct Player {
    void add_subgoldy_score(int score_kind, int bonus_score);
};

struct SoundEffectManager {
    void play_sound_effect(int sound_id); // thiscall on the global manager
};
extern SoundEffectManager g_sound_effect_manager;

struct InputState {
    char unknown_00[0x3c];
    unsigned int control_flags; // +0x3c
};

struct RowEventDisplayController {
    FrontendWidget* widget_a;   // +0x00
    FrontendWidget* widget_b;   // +0x04
    FrontendWidget* widget_c;   // +0x08
    FrontendWidget* widget_d;   // +0x0c
    FrontendWidget* widget_e;   // +0x10
    int state;                  // +0x14
    unsigned char gate_18;      // +0x18
    char unknown_19[0x3];
    int parcel_target_count;    // +0x1c
    int bonus_enabled;          // +0x20
    int staged_parcel_count;    // +0x24
    int delivered_parcel_count; // +0x28
    float progress;             // +0x2c
    float progress_step;        // +0x30
    float widget_world_x;       // +0x34
    float widget_world_y;       // +0x38
    float widget_world_z;       // +0x3c
    float bonus_blink_progress; // +0x40
    float bonus_blink_step;     // +0x44
    int bonus_score;            // +0x48
    int display_token;          // +0x4c
};

void __fastcall update_row_event_display(RowEventDisplayController* controller)
{
    if (controller->state == 0)
        return;

    char pause_gate = *(g_game_base + 0x74621);
    if (pause_gate != 0) {
        FrontendWidget* widget_b = controller->widget_b;
        widget_b->hide_border_init();
        controller->widget_a->hide_border_init();
        controller->widget_d->hide_border_init();
        controller->widget_c->hide_border_init();
        controller->widget_e->hide_border_init();
        return;
    }

    FrontendWidget* widget_b = controller->widget_b;
    widget_b->unhide_border_init();
    controller->widget_a->unhide_border_init();
    controller->widget_d->unhide_border_init();
    controller->widget_e->unhide_border_init();

    switch (controller->state) {
    case 0:
        return;
    case 1: {
        float progress = controller->progress_step;
        progress += controller->progress;
        controller->progress = progress;
        if (progress > 1.0f) {
            int staged_parcel_count = controller->staged_parcel_count;
            int parcel_target_count = controller->parcel_target_count;
            if (staged_parcel_count < parcel_target_count) {
                ++staged_parcel_count;
                controller->staged_parcel_count = staged_parcel_count;
                char* game = g_game_base;
                TrackParcelRuntime* parcel =
                    ((GameRuntime*)(game + 0x74618))->spawn_track_parcel((float*)(game + 0x433f34), game + 0x42fd7c);
                Sprite* sprite = parcel->sprite;
                parcel->state = 6;
                sprite->size_end = 0.0f;
                parcel->sprite->size_start = 0.0f;
            }

            parcel_target_count = controller->parcel_target_count;
            controller->progress = 0.0f;
            if (controller->staged_parcel_count == parcel_target_count) {
                if (parcel_target_count == 0) {
                    controller->state = 6;
                    controller->progress = 0.0f;
                    controller->progress_step = 0.00833333377f;
                } else {
                    controller->state = 2;
                }
            }
        }
        break;
    }
    case 6: {
        float progress = controller->progress_step;
        progress += controller->progress;
        controller->progress = progress;
        if (progress > 1.0f)
            controller->state = 3;
        break;
    }
    case 3: {
        controller->widget_e->unhide_border_init();
        int bonus_enabled = controller->bonus_enabled;
        controller->gate_18 = 0;
        controller->state = 4;
        if (bonus_enabled != 0) {
            controller->widget_c->unhide_border_init();
            if (controller->parcel_target_count == 0) {
                char* game = g_game_base;
                if (*(int*)(game + 0x74658) == 1) {
                    ((Player*)(game + 0x42fd7c))->add_subgoldy_score(5, controller->bonus_score);
                    g_sound_effect_manager.play_sound_effect(0x31);
                }
            }
        }
        /* fall through */
    }
    case 4: {
        char* game = g_game_base;
        if (controller->bonus_enabled != 0) {
            float blink_progress = controller->bonus_blink_step + controller->bonus_blink_progress;
            controller->bonus_blink_progress = blink_progress;
            if (blink_progress > 1.0f) {
                FrontendWidget* widget_c = controller->widget_c;
                controller->bonus_blink_progress = 0.0f;
                if ((widget_c->widget_flags & 0x1000) != 0)
                    widget_c->unhide_border_init();
                else
                    widget_c->hide_border_init();
            }
            game = g_game_base;
        }

        if ((((InputState**)(game + 0x28c))[0]->control_flags & 0x4000) != 0) {
            controller->state = 5;
            g_sound_effect_manager.play_sound_effect(8);
        }
        break;
    }
    }

    float* game = (float*)g_game_base;
    Vec3 camera_forward;
    Vec3 doubled_base;
    Vec3 scaled_target;
    Vec3 target;
    Vec3 base_target;
    Vec3 widget_world;
    Vec3* widget_world_out = (Vec3*)&controller->widget_world_x;

    camera_forward.x = game[95] * 6.0f;
    camera_forward.y = game[96] * 6.0f;
    camera_forward.z = game[97] * 6.0f;
    doubled_base.x = game[91] + game[91];
    doubled_base.y = game[92] + game[92];
    doubled_base.z = game[93] + game[93];
    scaled_target.x = game[87] * 7.30000019f;
    scaled_target.y = game[88] * 7.30000019f;
    scaled_target.z = game[89] * 7.30000019f;
    target.x = scaled_target.x + game[99];
    target.y = scaled_target.y + game[100];
    target.z = scaled_target.z + game[101];
    base_target.x = doubled_base.x + target.x;
    base_target.y = target.y + doubled_base.y;
    base_target.z = target.z + doubled_base.z;
    widget_world.x = base_target.x + camera_forward.x;
    widget_world.y = base_target.y + camera_forward.y;
    widget_world.z = base_target.z + camera_forward.z;
    *widget_world_out = widget_world;

    int delivered_parcel_count = controller->delivered_parcel_count;
    if (delivered_parcel_count < 10)
        controller->widget_b->text_buffer[0] = 0x20;
    else
        controller->widget_b->text_buffer[0] = (char)(delivered_parcel_count / 10 + 0x30);
    controller->widget_b->text_buffer[1] = (char)(controller->delivered_parcel_count % 10 + 0x30);
}
