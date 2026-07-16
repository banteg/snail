// update_row_event_display @ 0x404cf0 (thiscall, ret) — cRCompletion::AI()

#include "audio_system.h"
#include "completion.h"
#include "game_root.h"
#include "input_state.h"
#include "player.h"
#include "subgame_runtime.h"
#include "track_parcel_runtime.h"
#include "vector3.h"


typedef Vector3 Vec3;

void Completion::update_row_event_display()
{
    Completion* controller = this;
    if (controller->state == COMPLETION_STATE_INACTIVE)
        return;

    char pause_gate = g_game->subgame.subgame_pause_gate;
    if (pause_gate != 0) {
        FrontendWidget* delivered_count_widget = controller->delivered_count_widget;
        delivered_count_widget->hide_border_init();
        controller->title_widget->hide_border_init();
        controller->bonus_icon_widget->hide_border_init();
        controller->bonus_summary_widget->hide_border_init();
        controller->continue_widget->hide_border_init();
        return;
    }

    FrontendWidget* delivered_count_widget = controller->delivered_count_widget;
    delivered_count_widget->unhide_border_init();
    controller->title_widget->unhide_border_init();
    controller->bonus_icon_widget->unhide_border_init();
    controller->continue_widget->unhide_border_init();

    switch (controller->state) {
    case COMPLETION_STATE_INACTIVE:
        return;
    case COMPLETION_STATE_STAGING_PARCELS: {
        float progress = controller->progress_step;
        progress += controller->progress;
        controller->progress = progress;
        if (progress > 1.0f) {
            int staged_parcel_count = controller->staged_parcel_count;
            int parcel_target_count = controller->parcel_target_count;
            if (staged_parcel_count < parcel_target_count) {
                ++staged_parcel_count;
                controller->staged_parcel_count = staged_parcel_count;
                GameRoot* game = g_game;
                Parcel* parcel =
                    game->subgame.spawn_track_parcel(
                        game->subgame.parcel_home_anchor(),
                        &game->subgame.player);
                Sprite* sprite = parcel->sprite;
                parcel->state = PARCEL_STATE_DELIVERY_PENDING;
                sprite->size_end = 0.0f;
                parcel->sprite->size_start = 0.0f;
            }

            parcel_target_count = controller->parcel_target_count;
            controller->progress = 0.0f;
            if (controller->staged_parcel_count == parcel_target_count) {
                if (parcel_target_count == 0) {
                    controller->state = COMPLETION_STATE_EMPTY_DELIVERY_DELAY;
                    controller->progress = 0.0f;
                    controller->progress_step = 0.00833333377f;
                } else {
                    controller->state = COMPLETION_STATE_WAITING_FOR_DELIVERIES;
                }
            }
        }
        break;
    }
    case COMPLETION_STATE_EMPTY_DELIVERY_DELAY: {
        float progress = controller->progress_step;
        progress += controller->progress;
        controller->progress = progress;
        if (progress > 1.0f)
            controller->state = COMPLETION_STATE_SUMMARY_PENDING;
        break;
    }
    case COMPLETION_STATE_SUMMARY_PENDING: {
        controller->continue_widget->unhide_border_init();
        int bonus_enabled = controller->bonus_enabled;
        controller->gate_18 = 0;
        controller->state = COMPLETION_STATE_SUMMARY_ACTIVE;
        if (bonus_enabled != 0) {
            controller->bonus_summary_widget->unhide_border_init();
            if (controller->parcel_target_count == 0) {
                GameRoot* game = g_game;
                if (game->subgame.level_mode == 1) {
                    game->subgame.player.add_subgoldy_score(
                        SUBGOLDY_SCORE_BONUS, controller->bonus_score);
                    g_sound_effect_manager.play_sound_effect(0x31);
                }
            }
        }
        /* fall through */
    }
    case COMPLETION_STATE_SUMMARY_ACTIVE: {
        GameRoot* game = g_game;
        if (controller->bonus_enabled != 0) {
            float blink_progress = controller->bonus_blink_step + controller->bonus_blink_progress;
            controller->bonus_blink_progress = blink_progress;
            if (blink_progress > 1.0f) {
                FrontendWidget* bonus_summary_widget = controller->bonus_summary_widget;
                controller->bonus_blink_progress = 0.0f;
                if ((bonus_summary_widget->widget_flags
                        & FRONTEND_WIDGET_FLAG_HIDDEN)
                    != 0)
                    bonus_summary_widget->unhide_border_init();
                else
                    bonus_summary_widget->hide_border_init();
            }
            game = g_game;
        }

        if ((game->players[0].game_input->input.pressed_buttons
                & INPUT_BUTTON_PRIMARY)
            != 0) {
            controller->state = COMPLETION_STATE_CONTINUE_ACCEPTED;
            g_sound_effect_manager.play_sound_effect(8);
        }
        break;
    }
    }

    TransformMatrix* player_transform = &g_game->players[0].transform;
    Vec3 camera_forward;
    Vec3 doubled_base;
    Vec3 scaled_target;
    Vec3 target;
    Vec3 base_target;
    Vec3 widget_world;
    Vec3* widget_world_out = &controller->widget_world;

    camera_forward.x = player_transform->basis_forward.x * 6.0f;
    camera_forward.y = player_transform->basis_forward.y * 6.0f;
    camera_forward.z = player_transform->basis_forward.z * 6.0f;
    doubled_base.x = player_transform->basis_up.x + player_transform->basis_up.x;
    doubled_base.y = player_transform->basis_up.y + player_transform->basis_up.y;
    doubled_base.z = player_transform->basis_up.z + player_transform->basis_up.z;
    scaled_target.x = player_transform->basis_right.x * 7.30000019f;
    scaled_target.y = player_transform->basis_right.y * 7.30000019f;
    scaled_target.z = player_transform->basis_right.z * 7.30000019f;
    target.x = scaled_target.x + player_transform->position.x;
    target.y = scaled_target.y + player_transform->position.y;
    target.z = scaled_target.z + player_transform->position.z;
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
