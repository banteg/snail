// run_frame_update @ 0x40a2a0 (thiscall, ret)

#include "audio_system.h"
#include "bod_ai_dispatch.h"
#include "cheat_state.h"
#include "game_root.h"
#include "sprite.h"
#include "voice_manager.h"

int report_errorf(const char* format, ...);
int queue_axis_aligned_textured_quad(
    int texture_id,
    float x,
    float y,
    float width,
    float height,
    unsigned int color,
    tColour* tint,
    int blend_mode);

int GameRoot::run_frame_update()
{
    fade.update_frontend_transition_overlay();
    g_audio_backend.noop_runtime_ai();
    g_cheat_state.update_cheat();
    g_voice_manager.update_voice_manager();

    int sprite_update_count = 0;
    int next_frame_counter = frame_counter + 1;
    MouseCursorState* mouse = &players[0].mouse_cursor;
    frontend_quit_requested = 0;
    fixed_update_accumulator += 1.0f;
    fixed_update_count = 1;
    frame_counter = next_frame_counter;
    input_sampling_gate = 1;

    int bod_update_count = 0;
    if (mouse->is_mouse_captured()) {
        if (players[0].mouse_cursor.suppress_next_draw != 0) {
            players[0].mouse_cursor.suppress_next_draw = 0;
        } else {
            tColour color;
            queue_axis_aligned_textured_quad(
                22,
                players[0].mouse_cursor.saved_x - 8.0f,
                players[0].mouse_cursor.saved_y - 7.0f,
                64.0f,
                64.0f,
                0x1000000,
                color.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
                7);
        }
    }

    if (fixed_update_accumulator > 1.0f) {
        do {
            fixed_update_accumulator = fixed_update_accumulator - 1.0f;
            players[0].frontend_overlay.draw_frontend_overlay_color_lerp();

            BodNode* bod = active_bod_list.first;
            if (bod != 0) {
                do {
                    if ((bod->list_flags & BOD_FLAG_DEBUG) != 0) {
                        report_errorf("Debug Bod AI");
                    }

                    BodNode* next_bod = bod->list_next;
                    if (next_bod != 0) {
                        next_bod->list_flags |= BOD_FLAG_NEXT_UPDATE_GUARD;
                    }

                    ((BodAiDispatch*)bod)->update_bod_ai();
                    bod = next_bod;
                    ++bod_update_count;
                    if (next_bod == 0) {
                        break;
                    }

                    next_bod->list_flags &= ~BOD_FLAG_NEXT_UPDATE_GUARD;
                } while (true);
            }

            ((BodAiDispatch*)&players[0])->update_bod_ai();
            if (subgame.level_mode == 6) {
                ((BodAiDispatch*)&players[1])->update_bod_ai();
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

            subgame.enemy_manager.initialize_enemy_manager();
            input_sampling_gate = 0;
        } while (fixed_update_accumulator > 1.0f);
    }

    return frontend_quit_requested;
}
