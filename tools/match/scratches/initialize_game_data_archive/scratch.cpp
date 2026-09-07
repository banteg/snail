// initialize_game_data_archive @ 0x430e40 (cdecl)

#include "archive_index.h"
#include "input_controller_state.h"
#include "rect.h"
#include "text_input_repeat_state.h"
#include "tracked_allocation_stack.h"

extern int g_tracked_allocation_total_bytes; // data_5108b4
char load_archive_index(char* path);
void reset_registered_sound_sample_count();
void* allocate_tracked_memory(int size, char* name);
extern "C" __declspec(dllimport) int __stdcall GetClipCursor(Rect* rect);

char initialize_game_data_archive()
{
    Rect clip_rect;
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

    for (int i = 0; i < INPUT_CONTROLLER_SLOT_COUNT; ++i) {
        input_controller_slot(i).axis_x = 0.0f;
        input_controller_slot(i).axis_y = 0.0f;
        input_controller_slot(i).buttons = 0;
        input_controller_slot(i).authored_x = 320.0f;
        input_controller_slot(i).authored_y = 240.0f;
        input_controller_slot(i).pointer_value = 0.0f;
    }

    GetClipCursor(&clip_rect);
    return 1;
}
