// update_row_event_display @ 0x404cf0 (fastcall, ret)

#include "audio_system.h"
#include "game_root.h"
#include "input_state.h"
#include "player.h"
#include "row_event_display.h"
#include "subgame_runtime.h"
#include "track_parcel_runtime.h"
#include "vector3.h"

extern char* g_game_base; // data_4df904

typedef Vector3 Vec3;

void __fastcall update_row_event_display(RowEventDisplayController* controller)
{
    if (controller->state == 0)
        return;

    char pause_gate = ((GameRoot*)g_game_base)->subgame.subgame_pause_gate;
    if (pause_gate != 0) {
        FrontendWidget* delivered_count_widget = controller->delivered_count_widget;
        delivered_count_widget->hide_border_init();
        controller->widget_a->hide_border_init();
        controller->widget_d->hide_border_init();
        controller->bonus_widget->hide_border_init();
        controller->continue_widget->hide_border_init();
        return;
    }

    FrontendWidget* delivered_count_widget = controller->delivered_count_widget;
    delivered_count_widget->unhide_border_init();
    controller->widget_a->unhide_border_init();
    controller->widget_d->unhide_border_init();
    controller->continue_widget->unhide_border_init();

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
                    ((SubgameRuntime*)(game + 0x74618))->spawn_track_parcel(
                        (Vector3*)(game + 0x433f34),
                        (Player*)(game + 0x42fd7c));
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
        controller->continue_widget->unhide_border_init();
        int bonus_enabled = controller->bonus_enabled;
        controller->gate_18 = 0;
        controller->state = 4;
        if (bonus_enabled != 0) {
            controller->bonus_widget->unhide_border_init();
            if (controller->parcel_target_count == 0) {
                char* game = g_game_base;
                if (*(int*)(game + 0x74658) == 1) {
                    ((Player*)(game + 0x42fd7c))->add_subgoldy_score(SUBGOLDY_SCORE_BONUS, controller->bonus_score);
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
                FrontendWidget* bonus_widget = controller->bonus_widget;
                controller->bonus_blink_progress = 0.0f;
                if ((bonus_widget->widget_flags & 0x1000) != 0)
                    bonus_widget->unhide_border_init();
                else
                    bonus_widget->hide_border_init();
            }
            game = g_game_base;
        }

        if ((((GameRoot*)game)->players[0].game_input->input.pressed_buttons & 0x4000) != 0) {
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
        controller->delivered_count_widget->text_buffer[0] = 0x20;
    else
        controller->delivered_count_widget->text_buffer[0] = (char)(delivered_parcel_count / 10 + 0x30);
    controller->delivered_count_widget->text_buffer[1] = (char)(controller->delivered_parcel_count % 10 + 0x30);
}
