#ifndef SNAIL_MAIN_LOOP_TYPES_H
#define SNAIL_MAIN_LOOP_TYPES_H

/* Human-facing WinMain contract; replays preserve pointer width per tool. */
int __stdcall game_startup_and_main_loop(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nShowCmd);

extern HINSTANCE g_application_instance;

#endif
