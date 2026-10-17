// launch_alpha72_url @ 0x433050

#include "g0.h"
#include "main_loop_state.h"

void launch_alpha72_url(char* unused_path)
{
    (void)unused_path;
    minimize_game_window();
    g_pending_window_deactivate = 1;
}
