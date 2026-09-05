// update_galaxy @ 0x4092f0 (thiscall)

#include "font_system.h"
#include "frontend_widget.h"
#include "game_root.h"
#include "galaxy_route_types.h"
#include "runtime_config.h"
#include "sound_effect_manager.h"
#include "sprite.h"
#include "subgame_runtime.h"
#include "vector3.h"


int OSDPrintUV(
    int texture_id,
    float x,
    float y,
    float width,
    float height,
    int flags,
    tColour* color,
    float u0,
    float v0,
    float u1,
    float v1,
    int blend_mode,
    float rotation); // @ 0x44a9b0
int cRGalaxy::AI()
{
    Vector3 probe;
    tColour color;
    // Windows folds the mobile cRGalaxy::Render() phase into this update.
    {
        tColour route_zero_color;
        color.noop_this_constructor();

        level_progress_base->HideScores();

        int tick_index = 0;
        if (g_runtime_config.highest_galaxy_route_index >= 0) {
            do {
                route_slots[tick_index].AI();
                ++tick_index;
            } while (tick_index <= g_runtime_config.highest_galaxy_route_index);
        }

        if (route_state == 1
            && (bounds_frame_widget->widget_flags & FRONTEND_WIDGET_FLAG_HIDDEN)
                == 0) {
            color.store_color4f(1.0f, 1.0f, 1.0f, 0.999000013f);
            GalaxyRouteIndexedSlotView* selected_record =
                (GalaxyRouteIndexedSlotView*)((char*)this +
                                              selected_index * sizeof(cRGalaxyStar));
            FrontendWidget* card = bounds_frame_widget;

            if (card->frame_x > selected_record->map_x) {
                Line(153, selected_record->map_x + 16.0f, selected_record->map_y,
                     card->frame_x - 6.0f, selected_record->map_y, 4.0f, color);
            } else {
                Line(153, selected_record->map_x - 16.0f, selected_record->map_y,
                     card->frame_width + card->frame_x + 6.0f, selected_record->map_y,
                     4.0f, color);
            }
        }

        int route_index = 1;
        if (g_runtime_config.highest_galaxy_route_index >= 1) {
            do {
                color = route_names[
                    route_slots[route_index].record.route_name_index].color;
                color.r = 1.0f;
                color.g = 1.0f;
                color.b = 1.0f;
                color.a = 0.99000001f;

                if (!route_index) {
                    OSDPrintUV(
                        151, route_slots[0].record.map_x - 16.0f,
                        route_slots[0].record.map_y - 16.0f, 32.0f, 32.0f, 0x1000000,
                        route_zero_color.Set(1.0f, 0.0f, 0.0f, 0.99000001f), 0.0f, 0.0f,
                        1.0f, 1.0f, 15, 0);
                } else {
                    if (route_mode == 1 && route_index > selected_index)
                        goto skip_route_icon;
                    OSDPrintUV(
                        151, route_slots[route_index].record.map_x - 16.0f,
                        route_slots[route_index].record.map_y - 16.0f,
                        32.0f, 32.0f, 0x1000000,
                        &color, 0.0f, 0.0f, 1.0f, 1.0f, 15, 0);
                }

            skip_route_icon:
                if (route_slots[route_index].record.route_tint_alpha > 0.0f) {
                    color.a = route_slots[route_index].record.route_tint_alpha;
                    OSDPrintUV(
                        150, route_slots[route_index].record.map_x - 32.0f,
                        route_slots[route_index].record.map_y - 32.0f,
                        64.0f, 64.0f, 0x1000000,
                        &color, 0.0f, 0.0f, 1.0f, 1.0f, 15, 0);
                }

                ++route_index;
            } while (route_index <= g_runtime_config.highest_galaxy_route_index);
        }

        color.White();
        color.a = 0.200000003f;
        int line_index = 1;
        if (g_runtime_config.highest_galaxy_route_index > 1) {
            do {
                if (line_index < selected_index) {
                    color.a = 0.800000012f;
                    Line(154, route_slots[line_index].record.map_x,
                         route_slots[line_index].record.map_y, route_slots[line_index + 1].record.map_x,
                         route_slots[line_index + 1].record.map_y, 4.0f, color);
                } else {
                    if (route_mode != 1) {
                        color.a = 0.200000003f;
                        Line(154, route_slots[line_index].record.map_x,
                             route_slots[line_index].record.map_y, route_slots[line_index + 1].record.map_x,
                             route_slots[line_index + 1].record.map_y, 4.0f, color);
                    }
                }
                ++line_index;
            } while (line_index < g_runtime_config.highest_galaxy_route_index);
        }

        color.White();
        int galaxy_index = 0;
        do {
            OSDPrintUV(galaxy_index + 139, route_names[galaxy_index].map_x - 128.0f,
                                                route_names[galaxy_index].map_y - 128.0f, 256.0f, 256.0f,
                                                0x1000000, &color, 0.0f, 0.0f, 1.0f, 1.0f, 15, 0);
            ++galaxy_index;
        } while (galaxy_index < 10);
    }

    int hovered_route_index = -1;
    Vector3 mouse_position;
    mouse_position.x = g_game->players[0].game_input->input.authored_x;
    mouse_position.y = g_game->players[0].game_input->input.authored_y;
    mouse_position.z = 0.0f;

    hover_state = 0;
    if (route_state == 1) {
        FrontendWidget* card = bounds_frame_widget;
        if (card->frame_x - card->active_padding < mouse_position.x &&
            card->frame_width + card->active_padding + card->frame_x > mouse_position.x &&
            card->frame_y - card->active_padding < mouse_position.y &&
            card->frame_height + card->frame_y + card->active_padding > mouse_position.y) {
            hover_state = 1;
            int highlight_index = 1;
            if (g_runtime_config.highest_galaxy_route_index >= 1) {
                do {
                    if (highlight_index == selected_index) {
                        route_slots[highlight_index].record.highlight_target = 1.0f;
                    } else {
                        route_slots[highlight_index].record.highlight_target = 0.0f;
                    }
                    ++highlight_index;
                } while (highlight_index <= g_runtime_config.highest_galaxy_route_index);
            }
        }
    }

    if (route_mode == 1) {
        route_slots[selected_index].record.highlight_target = 1.0f;
    } else if (hover_state == 0) {
        if (route_state == 1) {
            GalaxyRouteRecord* selected_record = &route_slots[selected_index].record;
            probe = *(Vector3*)&selected_record->map_x - mouse_position;
            if (probe.Normalize() < 17.0f && hover_state == 0) {
                hovered_route_index = selected_index;
                hover_state = 2;
                route_slots[hovered_route_index].record.highlight_target = 1.0f;
            }
        }

        int probe_index = 1;
        if (g_runtime_config.highest_galaxy_route_index >= 1) {
            do {
                probe =
                    *(Vector3*)&route_slots[probe_index].record.map_x
                    - mouse_position;
                if (probe.Normalize() < 17.0f && hover_state == 0) {
                    hover_state = 2;
                    hovered_route_index = probe_index;
                    route_slots[probe_index].record.highlight_target = 1.0f;
                } else {
                    if (route_state == 1 && probe_index == selected_index) {
                        route_slots[probe_index].record.highlight_target = 1.0f;
                    } else {
                        route_slots[probe_index].record.highlight_target = 0.0f;
                    }
                }
                ++probe_index;
            } while (probe_index <= g_runtime_config.highest_galaxy_route_index);
        }
    }

    cRGame* input_game = g_game;
    if (input_game->border_manager.delayed_widget_active != 0)
        return 0;

    unsigned int flags = exit_or_back_widget->widget_flags;
    if ((flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
        exit_or_back_widget->widget_flags =
            flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
        if (route_mode == 1) {
            g_game->exit_controller.previous_frontend_state =
                g_game->players[0].frontend_state;
            g_game->exit_controller.state = 11;
            g_game->players[0].frontend_state = 8;
            return 0;
        }

        UnInit();
        return 3;
    }

    int state = route_state;
    if (state == 1) {
        flags = play_or_deliver_widget->widget_flags;
        if ((flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
            play_or_deliver_widget->widget_flags =
                flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
            UnInit();
            level_progress_base->level_mode_arg = selected_index;
            level_progress_base->level_definition
                .load_frontend_level_by_mode_and_index(
                    level_progress_base->level_mode,
                    level_progress_base->level_mode_arg);
            if (level_progress_base->level_mode == 0
                && level_progress_base->subgame_rebuild_selector == 1) {
                return 2;
            }
            return 1;
        }
    }

    flags = replay_widget->widget_flags;
    if ((flags & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED) != 0) {
        replay_widget->widget_flags =
            flags & ~FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED;
        UnInit();
        level_progress_base->level_mode_arg = selected_index;
        level_progress_base->level_definition.load_frontend_level_by_mode_and_index(
            level_progress_base->level_mode,
            level_progress_base->level_mode_arg);
        level_progress_base->selected_level_record_active = 1;
        level_progress_base->selected_level_record =
            &level_progress_base->sub_high_score
                 .time_trial_route_records[selected_index];
        return 1;
    }

    if (g_game->fade.state == 0 && route_mode != 1) {
        if (hover_state != 1) {
            if (hover_state == 2
                && (input_game->players[0].game_input->input.pressed_buttons
                    & INPUT_BUTTON_PRIMARY) != 0) {
                if (hovered_route_index != selected_index) {
                    if (state == 1) {
                        BoxOff();
                        BoxOn(hovered_route_index);
                        g_sound_effect_manager.Play(8);
                    } else if (state == 0) {
                        BoxOn(hovered_route_index);
                        g_sound_effect_manager.Play(8);
                    }
                }
                return 0;
            }

            if (hover_state == 0
                && (input_game->players[0].game_input->input.pressed_buttons
                    & INPUT_BUTTON_PRIMARY) != 0
                && state == 1
                && g_runtime_config.highest_galaxy_route_index > 1) {
                BoxOff();
                g_sound_effect_manager.Play(8);
                return 0;
            }
        }
    }

    return 0;
}
