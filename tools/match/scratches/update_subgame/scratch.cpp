// update_subgame @ 0x438b90 (thiscall, ret)

#include "bod_list.h"
#include "completion_screen.h"
#include "fringe_object.h"
#include "high_score_record.h"
#include "new_game_menu.h"
#include "salt_hazard_types.h"
#include "slug_voice_manager.h"
#include "sprite.h"
#include "star_field.h"
#include "subgame_runtime.h"
#include "time_trial_string_formatter.h"
#include "timer_counters.h"
#include "track_attachment_types.h"
#include "track_parcel_runtime.h"
#include "track_render_cache.h"
#include "vector3.h"

class TutorialRuntime {
public:
    void* update_tutorial();
};

class BorderInit {
public:
    void hide_border_init();
    void unhide_border_init();
    void border_add_text_number(int value);
};

class RuntimeCellView {
public:
    virtual void update_runtime_cell();
};

struct ActiveRuntimeRow {
    unsigned int flags;                 // +0x00
    BodNode primary_bod;                // +0x04
    char unknown_014[0x90 - 0x14];
    Vector3 parcel_position;            // +0x90
    char unknown_09c[0xb0 - 0x9c];
    BodNode attachment_bod;             // +0xb0
    Vector3 attachment_position;        // +0xc0
    char unknown_0cc[0xf4 - 0xcc];
};
typedef char ActiveRuntimeRow_must_be_0xf4[
    (sizeof(ActiveRuntimeRow) == 0xf4) ? 1 : -1];


struct RuntimeCellSlotBase {
    char before_cell[0x3bfac8];
    TrackRowCell cell;
};

extern char* g_game_base;
extern int g_completion_bonus_x_source;
extern int g_completion_bonus_y_source;
extern int g_landscape_backdrop_variant_selector;
extern unsigned char g_window_deactivated;
extern char g_time_trial_string[];

float random_float_below(float upper_bound, const char* tag);
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
    int blend);
void rstrcpy_checked_ascii(char* destination, char* source);
int report_errorf(char* format, ...);

void SubgameRuntime::update_subgame()
{
    char* game = (char*)this;
    int cell_index;
    int attachment_count;
    Color4f replay_color;
    Color4f replay_color_alt;
    Color4f skirt_color;

    calc_subgame_rate();
    int one = 1;

    switch (subgame_state) {
    case 3:
        subgame_state = 4;
        subgame_pause_gate = (unsigned char)one;
        pause_fade = pause_fade_step;
        pause_menu.initialize_pause_menu();
        // Native fallthrough: initialization immediately receives one update.
    case 4:
        pause_menu.update_pause_menu();
        return;

    case 7:
        if (selected_level_record_persistent == one) {
            selected_level_record_active = (unsigned char)one;
            build_subgame_level(0);
            subgame_state = 2;
            *(int*)(g_game_base + 0x56c) = one;
            return;
        }
        selected_level_record_active = 0;
        build_subgame_level(0);
        subgame_state = 2;
        *(int*)(g_game_base + 0x56c) = one;
        return;

    case 0: {
        int selector = subgame_rebuild_selector;
        subgame_state = one;
        if (selector == one)
            break;
        if (selector == 0 || selector == 3)
            goto build_selected_level;

        if (selected_level_record_persistent == one) {
            selected_level_record_active = (unsigned char)one;
            build_subgame_level(selected_level_record->replay_level_index);
            return;
        }

        selected_level_record_active = 0;
        ((StarField*)(g_game_base + 0x4f33c))->hide_star_field();
    }
        // Fresh state-zero setup enters the same front-end dispatch as state one.
    case 1: {
        random_float_below(1.0f, 0);
        *(int*)(game + 0x28) = g_completion_bonus_y_source;
        *(int*)(game + 0x2c) = g_completion_bonus_x_source;

        int result;
        switch (level_mode) {
        case 0:
            result = ((CompletionGalaxyRoute*)(game + 0x1260020))->update_galaxy();
            if (result == one) {
                subgame_rebuild_selector = 3;
                g_landscape_backdrop_variant_selector = level_mode_arg;
                build_subgame_level(level_mode_arg);
                return;
            }
            if (result == 2) {
                subgame_rebuild_selector = one;
                g_landscape_backdrop_variant_selector = level_mode_arg;
                build_subgame_level(level_mode_arg);
                return;
            }
            if (result != 3)
                break;
            destroy_subgame();
            *(int*)(g_game_base + 0x1b8) = 2;
            return;

        case 4:
            result = ((CompletionGalaxyRoute*)(game + 0x1260020))->update_galaxy();
            if (result == one) {
                subgame_rebuild_selector = 2;
                g_landscape_backdrop_variant_selector = level_mode_arg;
                goto build_selected_level;
            }
            if (result != 3)
                break;
            destroy_subgame();
            *(int*)(g_game_base + 0x1b8) = 2;
            return;

        case 1:
            result = ((ChallengeSetupScreen*)(game + 0x125ffe0))->update_challenge_setup_screen();
            if (result == one) {
                subgame_rebuild_selector = 2;
                build_subgame_level(0);
                return;
            }
            if (result != 3)
                break;
            destroy_subgame();
            *(int*)(g_game_base + 0x1b8) = 2;
            return;

        case 7:
            subgame_rebuild_selector = 2;
            build_subgame_level(0);
            return;
        }
        break;
    }

    case 2: {
        int zero = 0;
        int three = 3;
        if (selected_level_record_active == one
            && *(unsigned char*)(g_game_base + 0x4f2e0) == zero) {
            if (level_mode == three) {
                queue_axis_aligned_textured_quad_uv(
                    27, 580.0f, 6.0f, 64.0f, 64.0f, 0x1000000,
                    replay_color.set_color_rgba(1.0f, 1.0f, 1.0f, 0.400000006f),
                    0.0f, 0.0f, 1.0f, 1.0f, 1, 0);
            } else {
                queue_axis_aligned_textured_quad_uv(
                    27, 288.0f, 10.0f, 64.0f, 64.0f, 0x1000000,
                    replay_color_alt.set_color_rgba(1.0f, 1.0f, 1.0f, 0.400000006f),
                    0.0f, 0.0f, 1.0f, 1.0f, 1, 0);
            }
        }

        int two = 2;
        if (*(unsigned char*)(game + 0x3bbba4) == zero
            && *(int*)(game + 0x3bb884) != two)
            ((TimerCounters*)(game + 0x3bba4c))->advance_timer_counters(1.0f);

        if (level_mode == 7)
            ((TutorialRuntime*)(game + 0xa858))->update_tutorial();

        ((SlugVoiceManager*)(game + 0x35bb7c))->update_slug_voice_manager();

        if (*(unsigned char*)(game + 8) == one) {
            *(unsigned char*)(game + 9) = zero;
            *(unsigned char*)(game + 8) = zero;
            g_sprite_manager.set_sprite_manager_paused(0);
        }

        char* app = g_game_base;
        if ((selected_level_record_active != zero
                && *(float*)(game + 0x0c) == 0.0f
                && (*(unsigned int*)(*(char**)(game + 0x3bbba0) + 4) & 0x4000) != 0)
            || *(unsigned char*)(app + 0x4f2e0) != zero) {
            *(int*)(app + 0x1bc) = *(int*)(app + 0x1b8);
            if (selected_level_record_persistent != zero)
                *(int*)(g_game_base + 0x1b8) = 0x1a;
            else
                *(int*)(g_game_base + 0x1b8) = 0x1b;
            if (*(float*)(g_game_base + 0x4f2e4) <= 1.0f)
                *(unsigned char*)(g_game_base + 0x4f2e0) = zero;
            return;
        }

        if ((read_pressed_text_input_key_code() == 11 || g_window_deactivated == one)
            && *(int*)(g_game_base + 0x24) == zero) {
            *(unsigned char*)(game + 9) = one;
            subgame_state = three;
            g_sprite_manager.set_sprite_manager_paused((char)one);
            if (*(int*)(game + 0x3bb884) == two)
                ((BorderInit*)*(void**)(game + 0x3bb888))->hide_border_init();
            return;
        }

        if (*(float*)(game + 0x0c) > 0.0f) {
            float fade = *(float*)(game + 0x10) + *(float*)(game + 0x0c);
            *(float*)(game + 0x0c) = fade;
            if (fade > 1.0f)
                *(float*)(game + 0x0c) = 0.0f;
            if (*(int*)(game + 0x3bb884) == two)
                ((BorderInit*)*(void**)(game + 0x3bb888))->unhide_border_init();
        }

        if (*(unsigned char*)game != zero) {
            *(int*)(game + 0x20) = zero;
            if (level_mode == two)
                *(int*)(game + 0x24) = *(int*)(game + 0x54);
            else
                *(int*)(game + 0x24) = (int)*(float*)(game + 0x3be0e4) + 46;
        } else {
            int old_end = *(int*)(game + 0x24);
            *(int*)(game + 0x20) = old_end;
            if (level_mode == two) {
                *(int*)(game + 0x24) = *(int*)(game + 0x54);
            } else {
                int new_end = (int)*(float*)(game + 0x3be0e4) + 46;
                if (new_end > old_end)
                    *(int*)(game + 0x24) = new_end;
            }
        }

        int scan_limit = *(int*)(game + 0x58) + 20;
        if (*(int*)(game + 0x24) > scan_limit)
            *(int*)(game + 0x24) = scan_limit;

        cell_index = *(int*)(game + 0x20);
        while (cell_index < *(int*)(game + 0x24)) {
            if ((((ActiveRuntimeRow*)(game + 0x5ccac8 + cell_index * 0xf4))->flags & 2) != zero) {
                BodNode* row_node = &((ActiveRuntimeRow*)(game + 0x5ccac8 + cell_index * 0xf4))->primary_bod;
                if ((row_node->list_flags & 0x200) != zero) {
                    report_errorf("List ADD");
                } else {
                    BodNode** first_ref = &((BodList*)(g_game_base + 0x5a8))->first;
                    BodNode* first = *first_ref;
                    if (first == 0) {
                        *first_ref = row_node;
                        row_node->list_prev = 0;
                        (*first_ref)->list_next = 0;
                    } else {
                        first->list_prev = row_node;
                        (*first_ref)->list_prev->list_next = *first_ref;
                        BodNode* new_first = (*first_ref)->list_prev;
                        *first_ref = new_first;
                        new_first->list_prev = 0;
                    }
                    row_node->list_flags |= 0x200;
                }
            }

            if ((((ActiveRuntimeRow*)(game + 0x5ccac8 + cell_index * 0xf4))->flags & 0x10) != zero
                && (*(unsigned int*)(game + 0x4c) & 0x800000) != zero)
                spawn_track_parcel(&((ActiveRuntimeRow*)(game + 0x5ccac8 + cell_index * 0xf4))->parcel_position, game + 0x3bb764);

            attachment_count = zero;
            while (attachment_count < 8) {
                if (cell_index >= zero && cell_index < *(int*)(game + 0x54)) {
                    RuntimeCellSlotBase* cell_slot =
                        (RuntimeCellSlotBase*)(game
                            + sizeof(TrackRowCell) * (attachment_count + 8 * cell_index));
                    if ((cell_slot->cell.bod.list_flags & 0x200) == zero) {
                        if ((cell_slot->cell.lane_and_flags & 0x4000) != zero) {
                            unsigned char tile = cell_slot->cell.tile_id;
                            if (tile == 29 || tile == 30) {
                                if (*(void**)((char*)&cell_slot->cell + 0x24) != 0) {
                                BodNode* node = &cell_slot->cell.bod;
                                BodNode* active_list = (BodNode*)(game + 0x355cb4);
                                if ((node->list_flags & 0x200) != zero) {
                                    report_errorf("List ADDafter");
                                } else {
                                    node->list_prev = active_list;
                                    node->list_next = active_list->list_next;
                                    active_list->list_next = node;
                                    if (node->list_next != 0)
                                        node->list_next->list_prev = node;
                                    node->list_flags |= 0x200;
                                }

                                *(float*)((char*)&cell_slot->cell + 0x20) =
                                    (float)(cell_index % 8) * 0.125f;
                                node = &((ActiveRuntimeRow*)(game + 0x5ccac8 + cell_index * 0xf4))->attachment_bod;
                                active_list = (BodNode*)(game + 0x355b64);
                                if ((node->list_flags & 0x200) != zero) {
                                    report_errorf("List ADDafter");
                                } else {
                                    node->list_prev = active_list;
                                    node->list_next = active_list->list_next;
                                    active_list->list_next = node;
                                    if (node->list_next != 0)
                                        node->list_next->list_prev = node;
                                    node->list_flags |= 0x200;
                                }
                                ((ActiveRuntimeRow*)(game + 0x5ccac8 + cell_index * 0xf4))->attachment_position = cell_slot->cell.anchor_position;
                                }
                            } else {
                                BodNode* node = &cell_slot->cell.bod;
                                BodNode* active_list = (BodNode*)(game + 0x355b9c);
                                if ((node->list_flags & 0x200) != zero) {
                                    report_errorf("List ADDafter");
                                } else {
                                    node->list_prev = active_list;
                                    node->list_next = active_list->list_next;
                                    active_list->list_next = node;
                                    if (node->list_next != 0)
                                        node->list_next->list_prev = node;
                                    node->list_flags |= 0x200;
                                }
                            }
                            ((RuntimeCellView*)&cell_slot->cell)->update_runtime_cell();
                        }

                        FringeObject** fringe = &cell_slot->cell.fringe_front;
                        int fringe_count = 4;
                        do {
                            FringeObject* object = *fringe;
                            if (object != 0) {
                                BodNode* node = (BodNode*)object;
                                BodNode* active_list = (BodNode*)(game + 0x355b64);
                                if ((node->list_flags & 0x200) != zero) {
                                    report_errorf("List ADDafter");
                                } else {
                                    node->list_prev = active_list;
                                    node->list_next = active_list->list_next;
                                    active_list->list_next = node;
                                    if (node->list_next != 0)
                                        node->list_next->list_prev = node;
                                    node->list_flags |= 0x200;
                                }
                                Color4f* color =
                                    ((SubgameRuntime*)(g_game_base + 0x74618))->get_track_skirt_color(&skirt_color);
                                (*fringe)->color = *color;
                            }
                            ++fringe;
                            --fringe_count;
                        } while (fringe_count != zero);

                        if (cell_slot->cell.tile_id == 23
                            && (*(unsigned int*)(game + 0x4c) & 0x800) != zero
                            && cell_index >= *(int*)(game + 0x50)
                            && cell_index < *(int*)(game + 0x58))
                            spawn_track_health_pickup(&cell_slot->cell, (Player*)(game + 0x3bb764));

                        if (cell_slot->cell.tile_id == 24
                            && cell_index >= *(int*)(game + 0x50)
                            && cell_index < *(int*)(game + 0x58))
                            spawn_track_speedup(&cell_slot->cell, (Player*)(game + 0x3bb764));

                        if (cell_slot->cell.tile_id == 25
                            && cell_index >= *(int*)(game + 0x50)
                            && cell_index < *(int*)(game + 0x58))
                            spawn_track_jetpack_pickup(&cell_slot->cell, (Player*)(game + 0x3bb764));

                        unsigned char hazard_tile = cell_slot->cell.tile_id;
                        if (hazard_tile == 33
                            || ((cell_slot->cell.lane_and_flags & 0x10) == 0
                                && (hazard_tile == 1 || hazard_tile == 21)
                                && (*(unsigned int*)(game + 0x4c) & 2) != 0
                                && random_float_below(1.0f, "G")
                                    > (1.0f - *(float*)(game + 0x125ffd8)) * 0.2f
                                        + 0.8f
                                && (attachment_count == 0
                                    || *((unsigned char*)&cell_slot->cell - 0x18) == 1
                                    || *((unsigned char*)&cell_slot->cell - 0x18) == 20
                                    || *((unsigned char*)&cell_slot->cell - 0x18) == 21
                                    || *((unsigned char*)&cell_slot->cell - 0x18) == 32)
                                && (attachment_count == 7
                                    || *((unsigned char*)&cell_slot->cell + 0x90) == 1
                                    || *((unsigned char*)&cell_slot->cell + 0x90) == 20
                                    || *((unsigned char*)&cell_slot->cell + 0x90) == 21
                                    || *((unsigned char*)&cell_slot->cell + 0x90) == 32)
                                && cell_index >= *(int*)(game + 0x50)
                                && cell_index < *(int*)(game + 0x58)
                                && *(int*)(game + 0x3bb884) != 2
                                && (level_mode != 4
                                    || random_float_below(1.0f, "G2")
                                        <= *(float*)(game + 0x48) * 0.3f + 0.7f)
                                && (level_mode != 0
                                    || random_float_below(1.0f, "G3")
                                        <= *(float*)(game + 0x48) * 0.6f + 0.4f))) {
                            spawn_track_garbage_hazard(
                                &cell_slot->cell, (Player*)(game + 0x3bb764));
                        }

                        hazard_tile = cell_slot->cell.tile_id;
                        if (hazard_tile == 34) {
                            if (cell_index >= *(int*)(game + 0x50)
                                && cell_index < *(int*)(game + 0x58)) {
                                ((SaltHazardPool*)(game + 0x3578c0))->spawn_salt_hazard(
                                    &cell_slot->cell.anchor_position);
                            }
                        } else if ((cell_slot->cell.lane_and_flags & 8) == 0
                            && (hazard_tile == 1 || hazard_tile == 15)
                            && *(int*)(game + 0x3bb884) != 2
                            && (*(unsigned int*)(game + 0x4c) & 0x10000) != 0
                            && random_float_below(1.0f, "S")
                                > (1.0f - *(float*)(game + 0x125ffdc)) * 0.02f
                                    + 0.98f
                            && cell_index >= *(int*)(game + 0x50)
                            && cell_index < *(int*)(game + 0x58)) {
                            ((SaltHazardPool*)(game + 0x3578c0))->spawn_salt_hazard(
                                &cell_slot->cell.anchor_position);
                        }

                        if ((*(unsigned int*)(game + 0x4c) & 0x80) != 0
                            && cell_slot->cell.tile_id == 18
                            && cell_index >= *(int*)(game + 0x50)
                            && cell_index < *(int*)(game + 0x58)) {
                            spawn_slug_hazard(&cell_slot->cell, (Player*)(game + 0x3bb764));
                        }

                        unsigned int ring_flags = ((ActiveRuntimeRow*)(game + 0x5ccac8 + cell_index * 0xf4))->flags;
                        if ((ring_flags & 0x200) == 0) {
                            if (cell_slot->cell.tile_id == 35) {
                                if ((ring_flags & 0x400) != 0) {
                                    spawn_track_ring_or_special_effect(
                                        &cell_slot->cell, 5, (Player*)(game + 0x3bb764),
                                        ((float*)game)[cell_index
                                            + 20 * (3 * cell_index + 74772) + 24924]);
                                } else if ((ring_flags & 0x2000) != 0) {
                                    spawn_track_ring_or_special_effect(
                                        &cell_slot->cell, 8, (Player*)(game + 0x3bb764),
                                        ((float*)game)[cell_index
                                            + 20 * (3 * cell_index + 74772) + 24924]);
                                } else if ((ring_flags & 0x800) != 0) {
                                    spawn_track_ring_or_special_effect(
                                        &cell_slot->cell, 6, (Player*)(game + 0x3bb764),
                                        ((float*)game)[cell_index
                                            + 20 * (3 * cell_index + 74772) + 24924]);
                                } else if ((ring_flags & 0x1000) != 0) {
                                    spawn_track_ring_or_special_effect(
                                        &cell_slot->cell, 7, (Player*)(game + 0x3bb764),
                                        ((float*)game)[cell_index
                                            + 20 * (3 * cell_index + 74772) + 24924]);
                                } else {
                                    goto after_authored_ring;
                                }
                                *(float*)(game + 0x3bbae0) =
                                    cell_slot->cell.anchor_position.z;
after_authored_ring:
                                ;
                            } else if ((cell_slot->cell.tile_id == 2 || cell_slot->cell.tile_id == 3
                                    || cell_slot->cell.tile_id == 4 || cell_slot->cell.tile_id == 5
                                    || cell_slot->cell.tile_id == 6 || cell_slot->cell.tile_id == 7)
                                && *(float*)(game + 0x3bbae0) + 10.0f
                                    < cell_slot->cell.anchor_position.z
                                && cell_index < *(int*)(game + 0x58)) {
                                TrackRowCell* projected_cell =
                                    (TrackRowCell*)((char*)&cell_slot->cell + 0xfc0);
                                if ((ring_flags & 0x2000) != 0) {
                                    spawn_track_ring_or_special_effect(
                                        projected_cell, 8, (Player*)(game + 0x3bb764),
                                        ((float*)game)[cell_index
                                            + 20 * (3 * cell_index + 74772) + 24924]);
                                    *(float*)(game + 0x3bbae0) =
                                        projected_cell->anchor_position.z;
                                } else if ((ring_flags & 0x800) != 0) {
                                    spawn_track_ring_or_special_effect(
                                        projected_cell, 6, (Player*)(game + 0x3bb764),
                                        ((float*)game)[cell_index
                                            + 20 * (3 * cell_index + 74772) + 24924]);
                                    *(float*)(game + 0x3bbae0) =
                                        projected_cell->anchor_position.z;
                                } else if ((ring_flags & 0x1000) != 0) {
                                    spawn_track_ring_or_special_effect(
                                        projected_cell, 7, (Player*)(game + 0x3bb764),
                                        ((float*)game)[cell_index
                                            + 20 * (3 * cell_index + 74772) + 24924]);
                                    *(float*)(game + 0x3bbae0) =
                                        projected_cell->anchor_position.z;
                                } else if ((*(unsigned int*)(game + 0x4c) & 8) != 0
                                    && (random_float_below(1.0f, "R") > 0.7f
                                        || level_mode == 7)
                                    && cell_slot->cell.tile_id != 5 && cell_slot->cell.tile_id != 6
                                    && cell_slot->cell.tile_id != 7) {
                                    spawn_track_ring_or_special_effect(
                                        &cell_slot->cell, 4, (Player*)(game + 0x3bb764), 0.0f);
                                    if (*(int*)(game + 0x3bbb68) < 10)
                                        *(float*)(game + 0x3bbae0) =
                                            cell_slot->cell.anchor_position.z;
                                    else
                                        *(float*)(game + 0x3bbae0) =
                                            cell_slot->cell.anchor_position.z + 35.0f;
                                }
                            } else if ((cell_slot->cell.tile_id == 8 || cell_slot->cell.tile_id == 9
                                    || cell_slot->cell.tile_id == 10)
                                && *(float*)(game + 0x3bbae0) + 10.0f
                                    < cell_slot->cell.anchor_position.z
                                && cell_index < *(int*)(game + 0x58)) {
                                if ((ring_flags & 0x800) != 0) {
                                    spawn_track_ring_or_special_effect(
                                        &cell_slot->cell, 2, (Player*)(game + 0x3bb764),
                                        ((float*)game)[cell_index
                                            + 20 * (3 * cell_index + 74772) + 24924]);
                                    *(float*)(game + 0x3bbae0) = cell_slot->cell.anchor_position.z;
                                } else if (random_float_below(1.0f, "R2") > 0.7f
                                    || level_mode == 7
                                    || (((ActiveRuntimeRow*)(game + 0x5ccac8 + cell_index * 0xf4))->flags & 0x800) != 0) {
                                    spawn_track_ring_or_special_effect(
                                        &cell_slot->cell, 2, (Player*)(game + 0x3bb764), 0.0f);
                                    *(float*)(game + 0x3bbae0) = cell_slot->cell.anchor_position.z;
                                }
                            }
                        }
                    }
                }
                ++attachment_count;
            }
            ++cell_index;
            *(unsigned char*)game = zero;
        }

        ((TrackRenderCacheManager*)(game + 0x5c))->update_track_render_cache_rows();

        if (level_mode == 4) {
            TimeTrialStringFormatter* formatter = (TimeTrialStringFormatter*)(game + 0xff25e0);
            char* text = formatter->format_time_trial_string((TimerCounters*)(game + 0x3bba4c));
            rstrcpy_checked_ascii((char*)*(char**)(game + 0x35bb88) + 0x2cc, text);
            int record_offset = level_mode_arg * 0x1fac0;
            if (*(int*)(game + record_offset + 0x944150) == one) {
                text = formatter->format_time_trial_string(
                    (TimerCounters*)(game + record_offset + 0x944158));
                rstrcpy_checked_ascii((char*)*(char**)(game + 0x35bb8c) + 0x2cc, text);
                break;
            }
            ((BorderInit*)*(void**)(game + 0x35bb8c))->hide_border_init();
            update_subgame_camera();
            return;
        }

        *(unsigned char*)(*(char**)(game + 0x35bb88) + 0x2cc) = zero;
        ((BorderInit*)*(void**)(game + 0x35bb88))->border_add_text_number(
            *(int*)(game + 0x3bba48));
        if (*(int*)(game + 0x3bba48) > *(int*)(game + 0x355d94)) {
            *(int*)(game + 0x355d94) = *(int*)(game + 0x3bba48);
            *(unsigned char*)(*(char**)(game + 0x35bb8c) + 0x2cc) = zero;
            ((BorderInit*)*(void**)(game + 0x35bb8c))->border_add_text_number(
                *(int*)(game + 0x355d94));
            update_subgame_camera();
            return;
        }
        break;
    }
    }

    update_subgame_camera();
    return;

build_selected_level:
    build_subgame_level(level_mode_arg);
}
