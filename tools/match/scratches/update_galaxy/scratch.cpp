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

extern char* g_game_base; // data_4df904

inline Vector3 subtract_screen_xy(const Vector3& lhs, float screen_x, float screen_y)
{
    Vector3 result;
    result.x = lhs.x - screen_x;
    result.y = lhs.y - screen_y;
    result.z = lhs.z;
    return result;
}

int queue_axis_aligned_textured_quad_uv(
    int texture_id,
    float x,
    float y,
    float width,
    float height,
    unsigned int flags,
    Color4f* color,
    float u0,
    float v0,
    float u1,
    float v1,
    int layer,
    int blend); // @ 0x44a9b0
int Galaxy::update_galaxy()
{
    Color4f color;
    // Windows folds the mobile cRGalaxy::Render() phase into this update.
    {
        Color4f route_zero_color;
        color.noop_this_constructor();

        level_progress_base->hide_gameplay_scores();

        int tick_index = 0;
        if (g_runtime_config.highest_galaxy_route_index >= 0) {
            GalaxyRouteSlot* tick_record = route_slots;
            do {
                tick_record->update_galaxy_route_record();
                ++tick_index;
                ++tick_record;
            } while (tick_index <= g_runtime_config.highest_galaxy_route_index);
        }

        if (route_state == 1 && (bounds_frame_widget->widget_flags & 0x1000) == 0) {
            color.store_color4f(1.0f, 1.0f, 1.0f, 0.999000013f);
            GalaxyRouteIndexedSlotView* selected_record =
                (GalaxyRouteIndexedSlotView*)((char*)this +
                                              selected_index * sizeof(GalaxyRouteSlot));
            FrontendWidget* card = bounds_frame_widget;

            if (card->frame_x > selected_record->map_x) {
                draw_galaxy_line(153, selected_record->map_x + 16.0f, selected_record->map_y,
                                 card->frame_x - 6.0f, selected_record->map_y, 4.0f, &color);
            } else {
                draw_galaxy_line(153, selected_record->map_x - 16.0f, selected_record->map_y,
                                 card->frame_width + card->frame_x + 6.0f, selected_record->map_y,
                                 4.0f, &color);
            }
        }

        int route_index = 1;
        if (g_runtime_config.highest_galaxy_route_index >= 1) {
            do {
                int record_offset = route_index * sizeof(GalaxyRouteSlot);
                GalaxyRouteIndexedSlotView* record =
                    (GalaxyRouteIndexedSlotView*)((char*)this + record_offset);
                color = route_names[record->route_name_index].color;
                color.r = 1.0f;
                color.g = 1.0f;
                color.b = 1.0f;
                color.a = 0.99000001f;

                if (!route_index) {
                    queue_axis_aligned_textured_quad_uv(
                        151, route_slots[0].record.map_x - 16.0f,
                        route_slots[0].record.map_y - 16.0f, 32.0f, 32.0f, 0x1000000,
                        route_zero_color.set_color_rgba(1.0f, 0.0f, 0.0f, 0.99000001f), 0.0f, 0.0f,
                        1.0f, 1.0f, 15, 0);
                } else {
                    if (route_mode == 1 && route_index > selected_index)
                        goto skip_route_icon;
                    queue_axis_aligned_textured_quad_uv(
                        151, record->map_x - 16.0f, record->map_y - 16.0f, 32.0f, 32.0f, 0x1000000,
                        &color, 0.0f, 0.0f, 1.0f, 1.0f, 15, 0);
                }

            skip_route_icon:
                if (record->route_tint_alpha > 0.0f) {
                    color.a = record->route_tint_alpha;
                    queue_axis_aligned_textured_quad_uv(
                        150, record->map_x - 32.0f, record->map_y - 32.0f, 64.0f, 64.0f, 0x1000000,
                        &color, 0.0f, 0.0f, 1.0f, 1.0f, 15, 0);
                }

                ++route_index;
            } while (route_index <= g_runtime_config.highest_galaxy_route_index);
        }

        color.set_color_white();
        color.a = 0.200000003f;
        int line_index = 1;
        if (g_runtime_config.highest_galaxy_route_index > 1) {
            GalaxyRouteSlot* next_record = &route_slots[2];
            do {
                if (line_index < selected_index) {
                    color.a = 0.800000012f;
                    draw_galaxy_line(154, next_record[-1].record.map_x,
                                     next_record[-1].record.map_y, next_record->record.map_x,
                                     next_record->record.map_y, 4.0f, &color);
                } else {
                    if (route_mode != 1) {
                        color.a = 0.200000003f;
                        draw_galaxy_line(154, next_record[-1].record.map_x,
                                         next_record[-1].record.map_y, next_record->record.map_x,
                                         next_record->record.map_y, 4.0f, &color);
                    }
                }
                ++line_index;
                ++next_record;
            } while (line_index < g_runtime_config.highest_galaxy_route_index);
        }

        color.set_color_white();
        int galaxy_index = 0;
        GalaxyRouteNameRecord* route_name = route_names;
        do {
            queue_axis_aligned_textured_quad_uv(galaxy_index + 139, route_name->map_x - 128.0f,
                                                route_name->map_y - 128.0f, 256.0f, 256.0f,
                                                0x1000000, &color, 0.0f, 0.0f, 1.0f, 1.0f, 15, 0);
            ++galaxy_index;
            ++route_name;
        } while (galaxy_index < 10);
    }

    int hovered_route_index = -1;
    int probe_index = 1;
    GameInput* mouse_state = ((GameRoot*)g_game_base)->players[0].game_input;
    float mouse_x = mouse_state->input.authored_x;
    float mouse_y = mouse_state->input.authored_y;

    hover_state = 0;
    if (route_state == 1) {
        FrontendWidget* card = bounds_frame_widget;
        float edge = card->active_padding;
        if (card->frame_x - edge < mouse_x &&
            card->frame_width + edge + card->frame_x > mouse_x &&
            card->frame_y - edge < mouse_y &&
            card->frame_height + card->frame_y + edge > mouse_y) {
            hover_state = 1;
            if (g_runtime_config.highest_galaxy_route_index >= 1) {
                do {
                    if (probe_index == selected_index) {
                        route_slots[probe_index].record.highlight_target = 1.0f;
                    } else {
                        route_slots[probe_index].record.highlight_target = 0.0f;
                    }
                    ++probe_index;
                } while (probe_index <= g_runtime_config.highest_galaxy_route_index);
            }
        }
    }

    if (route_mode == 1) {
        route_slots[selected_index].record.highlight_target = 1.0f;
    } else if (hover_state == 0) {
        if (route_state == 1) {
            GalaxyRouteRecord* selected_record = &route_slots[selected_index].record;
            Vector3 selected_probe = subtract_screen_xy(
                *(Vector3*)&selected_record->map_x, mouse_x, mouse_y);
            if (selected_probe.normalize_vector() < 17.0f && hover_state == 0) {
                hovered_route_index = selected_index;
                hover_state = 2;
                route_slots[hovered_route_index].record.highlight_target = 1.0f;
            }
        }

        if (g_runtime_config.highest_galaxy_route_index >= 1) {
            GalaxyRouteSlot* probe_slot = &route_slots[1];
            do {
                Vector3 probe = subtract_screen_xy(
                    *(Vector3*)&probe_slot->record.map_x, mouse_x, mouse_y);
                if (probe.normalize_vector() < 17.0f && hover_state == 0) {
                    hover_state = 2;
                    hovered_route_index = probe_index;
                    probe_slot->record.highlight_target = 1.0f;
                } else {
                    if (route_state == 1 && probe_index == selected_index) {
                        probe_slot->record.highlight_target = 1.0f;
                    } else {
                        probe_slot->record.highlight_target = 0.0f;
                    }
                }
                ++probe_index;
                ++probe_slot;
            } while (probe_index <= g_runtime_config.highest_galaxy_route_index);
        }
    }

    if (((GameRoot*)g_game_base)->border_manager.delayed_widget_active != 0)
        return 0;

    unsigned int flags = exit_or_back_widget->widget_flags;
    if ((flags & 0x20) != 0) {
        exit_or_back_widget->widget_flags = flags & ~0x20;
        if (route_mode == 1) {
            ((GameRoot*)g_game_base)->exit_controller.previous_frontend_state =
                ((GameRoot*)g_game_base)->players[0].frontend_state;
            ((GameRoot*)g_game_base)->exit_controller.state = 11;
            ((GameRoot*)g_game_base)->players[0].frontend_state = 8;
            return 0;
        }

        destroy_galaxy();
        return 3;
    }

    int state = route_state;
    if (state == 1) {
        flags = play_or_deliver_widget->widget_flags;
        if ((flags & 0x20) != 0) {
            play_or_deliver_widget->widget_flags = flags & ~0x20;
            destroy_galaxy();
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
    if ((flags & 0x20) != 0) {
        replay_widget->widget_flags = flags & ~0x20;
        destroy_galaxy();
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

    if (((GameRoot*)g_game_base)->fade.state == 0 && route_mode != 1) {
        int current_hover_state = hover_state;
        if (current_hover_state != 1) {
            unsigned int mouse_flags = mouse_state->input.pressed_buttons;
            if (current_hover_state == 2 && (mouse_flags & 0x4000) != 0) {
                if (hovered_route_index != selected_index) {
                    if (state == 1) {
                        close_galaxy_route();
                        open_galaxy_route(hovered_route_index);
                        g_sound_effect_manager.play_sound_effect(8);
                    } else if (state == 0) {
                        open_galaxy_route(hovered_route_index);
                        g_sound_effect_manager.play_sound_effect(8);
                    }
                }
                return 0;
            }

            if (current_hover_state == 0
                && (mouse_flags & 0x4000) != 0
                && state == 1
                && g_runtime_config.highest_galaxy_route_index > 1) {
                close_galaxy_route();
                g_sound_effect_manager.play_sound_effect(8);
                return 0;
            }
        }
    }

    return 0;
}
