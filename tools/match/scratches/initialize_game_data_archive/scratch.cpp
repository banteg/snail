// initialize_game_data_archive @ 0x430e40 (cdecl)

#include "archive_index.h"
#include "input_controller_state.h"
#include "tracked_allocation_stack.h"

extern int g_tracked_allocation_total_bytes; // data_5108b4
extern float g_text_input_repeat_accumulator; // data_5108b8
extern float g_text_input_repeat_step;        // data_50339c
extern unsigned char g_text_input_last_repeat_code; // data_53c7f5
char load_archive_index(char* path);
void reset_registered_sound_sample_count();
void* allocate_tracked_memory(int size, char* name);
extern "C" __declspec(dllimport) int __stdcall GetClipCursor(void* rect);

char initialize_game_data_archive()
{
    char clip_rect[16];
    int zero = 0;

    g_archive_startup_flag = (unsigned char)zero;
    g_tracked_allocation_total_bytes = zero;
    g_tracked_allocation_stack.initialize_tracked_allocation_stack();
    g_text_input_repeat_accumulator = 0.0f;
    g_text_input_repeat_step = 0.0f;
    g_text_input_last_repeat_code = 0;

    if (load_archive_index("SnailMail.dat") == 0) {
        return 0;
    }

    reset_registered_sound_sample_count();
    g_archive_data_base = allocate_tracked_memory(RSHELL_SCRATCH_SIZE, "Scratch Pad");
    g_music_memory_buffer =
        (char*)allocate_tracked_memory(
            RSHELL_MUSIC_MEMORY_BUFFER_SIZE, "Music Memory Buffer");

    int authored_x = 0x43a00000;
    int authored_y = 0x43700000;
    char* slot_axis_y = (char*)g_input_slot0_buttons - 4;
    do {
        *(int*)(slot_axis_y - 4) = 0;
        *(int*)slot_axis_y = 0;
        *(int*)(slot_axis_y + 4) = 0;
        *(int*)(slot_axis_y + 0x10) = authored_x;
        *(int*)(slot_axis_y + 0x14) = authored_y;
        *(int*)(slot_axis_y + 0x18) = 0;
        slot_axis_y += 0x38;
    } while ((int)slot_axis_y < 0x5033b0);

    GetClipCursor(clip_rect);
    return 1;
}
