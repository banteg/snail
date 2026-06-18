// initialize_game_data_archive @ 0x430e40 (cdecl)

#include "golb.h"

extern int g_tracked_allocation_total_bytes; // data_5108b4
extern int g_tracked_allocation_depth;       // data_5108c0
extern float g_text_input_repeat_accumulator; // data_5108b8
extern float g_text_input_repeat_step;        // data_50339c
extern unsigned char g_text_input_last_repeat_code; // data_53c7f5
extern unsigned char g_archive_startup_flag; // data_53c7f4
extern int g_archive_data_base;              // data_53c7ec
extern char* g_music_memory_buffer;          // data_53c7e8
extern int g_input_slot0_axis_y;             // data_503340

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
    ((GolbPathBank*)&g_tracked_allocation_depth)->initialize_enemy_manager();
    g_text_input_repeat_accumulator = 0.0f;
    g_text_input_repeat_step = 0.0f;
    g_text_input_last_repeat_code = 0;

    if (load_archive_index("SnailMail.dat") == 0) {
        return 0;
    }

    reset_registered_sound_sample_count();
    g_archive_data_base = (int)allocate_tracked_memory(0x400000, "Scratch Pad");
    g_music_memory_buffer =
        (char*)allocate_tracked_memory(0x64000, "Music Memory Buffer");

    int authored_x = 0x43a00000;
    int authored_y = 0x43700000;
    int* slot_axis_y = &g_input_slot0_axis_y;
    do {
        slot_axis_y[-1] = 0;
        slot_axis_y[0] = 0;
        slot_axis_y[1] = 0;
        slot_axis_y[4] = authored_x;
        slot_axis_y[5] = authored_y;
        slot_axis_y[6] = 0;
        slot_axis_y += 0xe;
    } while ((int)slot_axis_y < 0x5033b0);

    GetClipCursor(clip_rect);
    return 1;
}
