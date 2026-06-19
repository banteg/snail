// update_galaxy @ 0x4092f0 (thiscall)

#include "font_system.h"
#include "frontend_widget.h"
#include "game.h"
#include "level_definition_loader.h"
#include "sprite.h"
#include "vector3.h"

extern char* g_game_base; // data_4df904
extern int data_4df9b8;

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
int __stdcall draw_galaxy_line(
    int texture_id,
    float x0,
    float y0,
    float x1,
    float y1,
    float width,
    Color4f* color); // @ 0x409b00
void __stdcall play_sound_effect(int sample_id); // @ 0x44dde0

class GalaxyRouteRecordTick {
public:
    void update_galaxy_route_record(); // @ 0x409bd0
};

class GalaxyRouteRecord {
public:
    int route_name_index; // +0x00
    char unknown_004[0x08 - 0x04];
    float map_x; // +0x08
    float map_y; // +0x0c
    float map_z; // +0x10
    float route_tint_alpha; // +0x14
    float highlight_target; // +0x18
    char detail_text[0x80]; // +0x1c
    char description_text[0x2a0 - 0x9c]; // +0x9c
};

class GalaxyRouteRecordSlot {
public:
    char before_record[0x14];
    int route_name_index; // +0x14
    char unknown_018[0x1c - 0x18];
    float map_x; // +0x1c
    float map_y; // +0x20
    float map_z; // +0x24
    float route_tint_alpha; // +0x28
    float highlight_target; // +0x2c
    char detail_text[0x80]; // +0x30
    char description_text[0x2a0 - 0x9c]; // +0xb0
};

class GalaxyRouteNameRecord {
public:
    char name[0x80]; // +0x00
    int star_count; // +0x80
    int color_r_bits; // +0x84
    int color_g_bits; // +0x88
    int color_b_bits; // +0x8c
    int color_a_bits; // +0x90
    float map_x; // +0x94
    float map_y; // +0x98
    float map_z; // +0x9c
};

class GalaxyRoute {
public:
    int update_galaxy();
    FrontendWidget* open_galaxy_route(int selected_level_index);
    void close_galaxy_route();
    void destroy_galaxy();

    char active; // +0x00
    char unknown_001[0x04 - 0x01];
    int route_mode; // +0x04
    int route_state; // +0x08
    int record_count; // +0x0c
    char unknown_010[0x14 - 0x10];
    GalaxyRouteRecord records[100]; // +0x14
    char unknown_10694[0x10930 - 0x10694];
    GalaxyRouteNameRecord route_names[10]; // +0x10930
    Game* level_progress_base; // +0x10f70
    FrontendWidget* exit_or_back_widget; // +0x10f74
    FrontendWidget* route_title_widget; // +0x10f78
    FrontendWidget* route_icon_widget; // +0x10f7c
    int selected_index; // +0x10f80
    int hover_state; // +0x10f84
    char unknown_10f88[0x10f8c - 0x10f88];
    FrontendWidget* bounds_frame_widget; // +0x10f8c
    FrontendWidget* selected_title_widget; // +0x10f90
    FrontendWidget* selected_detail_widget; // +0x10f94
    FrontendWidget* selected_description_widget; // +0x10f98
    FrontendWidget* play_or_deliver_widget; // +0x10f9c
    FrontendWidget* replay_widget; // +0x10fa0
};

int GalaxyRoute::update_galaxy()
{
    Color4f route_zero_color;
    Color4f color;
    color.noop_this_constructor();

    level_progress_base->hide_gameplay_scores();

    int tick_index = 0;
    if (data_4df9b8 >= 0) {
        GalaxyRouteRecordTick* tick_record = (GalaxyRouteRecordTick*)((char*)this + 0x10);
        do {
            tick_record->update_galaxy_route_record();
            ++tick_index;
            tick_record = (GalaxyRouteRecordTick*)((char*)tick_record + 0x2a0);
        } while (tick_index <= data_4df9b8);
    }

    if (route_state == 1 && (bounds_frame_widget->widget_flags & 0x1000) == 0) {
        color.store_color4f(1.0f, 1.0f, 1.0f, 0.999000013f);
        GalaxyRouteRecord* selected_record = &records[selected_index];
        FrontendWidget* card = bounds_frame_widget;

        float card_x;
        float route_x;
        if (card->frame_x <= selected_record->map_x) {
            card_x = card->frame_width + card->frame_x + 6.0f;
            route_x = selected_record->map_x - 16.0f;
        } else {
            card_x = card->frame_x - 6.0f;
            route_x = selected_record->map_x + 16.0f;
        }
        draw_galaxy_line(
            153,
            route_x,
            selected_record->map_y,
            card_x,
            selected_record->map_y,
            4.0f,
            &color);
    }

    int route_index = 1;
    if (data_4df9b8 >= 1) {
        do {
            int record_offset = route_index * 0x2a0;
            GalaxyRouteRecordSlot* record = (GalaxyRouteRecordSlot*)((char*)this + record_offset);
            color.r = 1.0f;
            color.g = 1.0f;
            color.b = 1.0f;
            color.a = 0.99000001f;

            Color4f* icon_color;
            float icon_x;
            float icon_y;
            if (route_index) {
                if (route_mode == 1 && route_index > selected_index)
                    goto skip_route_icon;
                icon_color = &color;
                icon_y = record->map_y - 16.0f;
                icon_x = record->map_x;
            } else {
                icon_color = route_zero_color.set_color_rgba(1.0f, 0.0f, 0.0f, 0.99000001f);
                icon_y = *(float*)((char*)this + 0x20) - 16.0f;
                icon_x = *(float*)((char*)this + 0x1c);
            }

            {
                queue_axis_aligned_textured_quad_uv(
                    151,
                    icon_x - 16.0f,
                    icon_y,
                    32.0f,
                    32.0f,
                    0x1000000,
                    icon_color,
                    0.0f,
                    0.0f,
                    1.0f,
                    1.0f,
                    15,
                    0);
            }

        skip_route_icon:
            if (record->route_tint_alpha > 0.0f) {
                color.a = record->route_tint_alpha;
                queue_axis_aligned_textured_quad_uv(
                    150,
                    record->map_x - 32.0f,
                    record->map_y - 32.0f,
                    64.0f,
                    64.0f,
                    0x1000000,
                    &color,
                    0.0f,
                    0.0f,
                    1.0f,
                    1.0f,
                    15,
                    0);
            }

            ++route_index;
        } while (route_index <= data_4df9b8);
    }

    color.set_color_white();
    color.a = 0.200000003f;
    int line_index = 1;
    if (data_4df9b8 > 1) {
        GalaxyRouteRecord* next_record = &records[2];
        do {
            if (line_index < selected_index) {
                color.a = 0.800000012f;
                draw_galaxy_line(
                    154,
                    next_record[-1].map_x,
                    next_record[-1].map_y,
                    next_record->map_x,
                    next_record->map_y,
                    4.0f,
                    &color);
            } else {
                if (route_mode != 1) {
                    color.a = 0.200000003f;
                    draw_galaxy_line(
                        154,
                        next_record[-1].map_x,
                        next_record[-1].map_y,
                        next_record->map_x,
                        next_record->map_y,
                        4.0f,
                        &color);
                }
            }
            ++line_index;
            ++next_record;
        } while (line_index < data_4df9b8);
    }

    color.set_color_white();
    int galaxy_index = 0;
    GalaxyRouteNameRecord* route_name = route_names;
    do {
        queue_axis_aligned_textured_quad_uv(
            galaxy_index + 139,
            route_name->map_x - 128.0f,
            route_name->map_y - 128.0f,
            256.0f,
            256.0f,
            0x1000000,
            &color,
            0.0f,
            0.0f,
            1.0f,
            1.0f,
            15,
            0);
        ++galaxy_index;
        ++route_name;
    } while (galaxy_index < 10);

    int hovered_route_index = -1;
    int probe_index = 1;
    char* mouse_state = *(char**)(g_game_base + 0x28c);
    float mouse_x = *(float*)(mouse_state + 0x60);
    float mouse_y = *(float*)(mouse_state + 0x64);

    hover_state = 0;
    if (route_state == 1) {
        FrontendWidget* card = bounds_frame_widget;
        float edge = *(float*)((char*)card + 0x220);
        if (card->frame_x - edge < mouse_x
            && card->frame_width + edge + card->frame_x > mouse_x
            && card->frame_y - edge < mouse_y
            && card->frame_height + card->frame_y + edge > mouse_y) {
            hover_state = 1;
            if (data_4df9b8 >= 1) {
                do {
                    if (probe_index == selected_index) {
                        records[probe_index].highlight_target = 1.0f;
                    } else {
                        records[probe_index].highlight_target = 0.0f;
                    }
                    ++probe_index;
                } while (probe_index <= data_4df9b8);
            }
        }
    }

    if (route_mode == 1) {
        records[selected_index].highlight_target = 1.0f;
    } else if (hover_state == 0) {
        if (route_state == 1) {
            GalaxyRouteRecord* selected_record = &records[selected_index];
            Vector3 selected_probe;
            selected_probe.x = selected_record->map_x - mouse_x;
            selected_probe.y = selected_record->map_y - mouse_y;
            selected_probe.z = selected_record->map_z;
            if (selected_probe.normalize_vector() < 17.0f && hover_state == 0) {
                hovered_route_index = selected_index;
                hover_state = 2;
                records[hovered_route_index].highlight_target = 1.0f;
            }
        }

        if (data_4df9b8 >= 1) {
            GalaxyRouteRecord* probe_record = &records[1];
            do {
                Vector3 probe;
                probe.x = probe_record->map_x - mouse_x;
                probe.y = probe_record->map_y - mouse_y;
                probe.z = probe_record->map_z;
                if (probe.normalize_vector() < 17.0f && hover_state == 0) {
                    hover_state = 2;
                    hovered_route_index = probe_index;
                    probe_record->highlight_target = 1.0f;
                } else {
                    if (route_state == 1 && probe_index == selected_index) {
                        probe_record->highlight_target = 1.0f;
                    } else {
                        probe_record->highlight_target = 0.0f;
                    }
                }
                ++probe_index;
                ++probe_record;
            } while (probe_index <= data_4df9b8);
        }
    }

    if (*(unsigned char*)(g_game_base + 0x440ec) != 0)
        return 0;

    unsigned int flags = exit_or_back_widget->widget_flags;
    if ((flags & 0x20) != 0) {
        exit_or_back_widget->widget_flags = flags & ~0x20;
        if (route_mode == 1) {
            *(int*)(g_game_base + 0x4f3b4) = *(int*)(g_game_base + 0x1b8);
            *(int*)(g_game_base + 0x4f3ac) = 11;
            *(int*)(g_game_base + 0x1b8) = 8;
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
            *(int*)((char*)level_progress_base + 0x44) = selected_index;
            ((LevelDefinitionLoader*)((char*)level_progress_base + 0xa874))
                ->load_frontend_level_by_mode_and_index(
                    *(int*)((char*)level_progress_base + 0x40),
                    *(int*)((char*)level_progress_base + 0x44));
            if (*(int*)((char*)level_progress_base + 0x40) == 0
                && *(int*)((char*)level_progress_base + 0x1270fc8) == 1) {
                return 2;
            }
            return 1;
        }
    }

    flags = replay_widget->widget_flags;
    if ((flags & 0x20) != 0) {
        replay_widget->widget_flags = flags & ~0x20;
        destroy_galaxy();
        *(int*)((char*)level_progress_base + 0x44) = selected_index;
        ((LevelDefinitionLoader*)((char*)level_progress_base + 0xa874))
            ->load_frontend_level_by_mode_and_index(
                *(int*)((char*)level_progress_base + 0x40),
                *(int*)((char*)level_progress_base + 0x44));
        *(unsigned char*)((char*)level_progress_base + 0xff25d0) = 1;
        *(int*)((char*)level_progress_base + 0xff25d4) =
            selected_index * 0x1fac0 + (int)level_progress_base + 0x944150;
        return 1;
    }

    if (*(int*)(g_game_base + 0x24) == 0 && route_mode != 1) {
        int current_hover_state = hover_state;
        if (current_hover_state != 1) {
            unsigned int mouse_flags = *(unsigned int*)(mouse_state + 0x3c);
            if (current_hover_state == 2 && (mouse_flags & 0x4000) != 0) {
                if (hovered_route_index != selected_index) {
                    if (state == 1) {
                        close_galaxy_route();
                        open_galaxy_route(hovered_route_index);
                        play_sound_effect(8);
                    } else if (state == 0) {
                        open_galaxy_route(hovered_route_index);
                        play_sound_effect(8);
                    }
                }
                return 0;
            }

            if (current_hover_state == 0
                && (mouse_flags & 0x4000) != 0
                && state == 1
                && data_4df9b8 > 1) {
                close_galaxy_route();
                play_sound_effect(8);
                return 0;
            }
        }
    }

    return 0;
}
