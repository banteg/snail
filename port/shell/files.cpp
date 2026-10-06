// File, archive and window-adjacent RShell pieces whose recovered bodies call
// Win32. Each follows its recovered body (decomp/), minus the Win32 call.

#include <dirent.h>
#include <fnmatch.h>
#include <io.h>
#include <stdio.h>
#include <string.h>

#include "archive_index.h"
#include "game_root.h"
#include "input_controller_state.h"
#include "main_loop_state.h"
#include "mouse_input_state.h"
#include "text_input_repeat_state.h"
#include "tracked_allocation_stack.h"

extern int g_tracked_allocation_total_bytes;
char load_archive_index(char* path);
void reset_registered_sound_sample_count();
void* allocate_tracked_memory(int size, char* name);

// decomp/game/RShell/initialize_game_data_archive.cpp without GetClipCursor.
char initialize_game_data_archive()
{
    g_archive_startup_flag = 0;
    g_tracked_allocation_total_bytes = 0;
    g_tracked_allocation_stack.initialize_tracked_allocation_stack();
    g_text_input_repeat_accumulator = 0.0f;
    g_text_input_repeat_step = 0.0f;
    g_text_input_last_repeat_code = 0;
    if (load_archive_index((char*)"SnailMail.dat") == 0) {
        return 0;
    }
    reset_registered_sound_sample_count();
    g_archive_data_base = allocate_tracked_memory(RSHELL_SCRATCH_SIZE, (char*)"Scratch Pad");
    g_music_memory_buffer =
        (char*)allocate_tracked_memory(RSHELL_MUSIC_MEMORY_BUFFER_SIZE, (char*)"Music Memory Buffer");
    for (int i = 0; i < INPUT_CONTROLLER_SLOT_COUNT; ++i) {
        input_controller_slot(i).axis_x = 0.0f;
        input_controller_slot(i).axis_y = 0.0f;
        input_controller_slot(i).buttons = 0;
        input_controller_slot(i).authored_x = 320.0f;
        input_controller_slot(i).authored_y = 240.0f;
        input_controller_slot(i).pointer_value = 0.0f;
    }
    return 1;
}

// decomp/engine/Mouse/click_mouse_screen.cpp without SetCursorPos: the shell
// owns the system cursor.
void click_mouse_screen(int slot, int x, int y)
{
    g_mouse_screen_x[slot] = x;
    g_mouse_screen_y[slot] = y;
    g_mouse_live_x[slot] = (float)x;
    float y_float = (float)y;
    g_mouse_live_y[slot] = y_float;
    cRGameInput* owner = g_game->players[0].game_input;
    owner->input.authored_x = (float)x;
    g_game->players[0].game_input->input.authored_y = y_float;
}

// The original opened a browser at the publisher's site.
void __cdecl launch_alpha72_url(char* url)
{
    fprintf(stderr, "snail: open %s\n", url);
}

// <io.h> directory search over dirent: one open search, matching the
// recovered caller, which never closes its handle.
namespace {
DIR* g_find_directory = 0;
char g_find_pattern[260];

int find_next_match(struct _finddata_t* data)
{
    while (struct dirent* entry = readdir(g_find_directory)) {
        if (fnmatch(g_find_pattern, entry->d_name, FNM_CASEFOLD) == 0) {
            memset(data, 0, sizeof(*data));
            strncpy(data->name, entry->d_name, sizeof(data->name) - 1);
            return 0;
        }
    }
    return -1;
}
}  // namespace

extern "C" long _findfirst(const char* pattern, struct _finddata_t* data)
{
    if (g_find_directory) {
        closedir(g_find_directory);
    }
    g_find_directory = opendir(".");
    if (!g_find_directory) {
        return -1;
    }
    strncpy(g_find_pattern, pattern, sizeof(g_find_pattern) - 1);
    return find_next_match(data) == 0 ? 1 : -1;
}

extern "C" int _findnext(long, struct _finddata_t* data)
{
    return g_find_directory ? find_next_match(data) : -1;
}

extern "C" int _findclose(long)
{
    if (g_find_directory) {
        closedir(g_find_directory);
        g_find_directory = 0;
    }
    return 0;
}
