# minimize_game_window @ 0x407490

Process-window helper called by the main loop and the completion-screen
outbound-link path. It emits the stripped `"Software Minimize Window"` report,
then posts `WM_SIZE` (`5`) with `SIZE_MINIMIZED` (`1`) to `g_main_window`.

The final imported call is `PostMessageA`, not a direct `ShowWindow` mutation;
the normal game window procedure owns the resulting minimize transition.
