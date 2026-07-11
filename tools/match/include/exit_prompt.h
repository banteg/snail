// Authored cRExit owner embedded in GameRoot.
#ifndef EXIT_PROMPT_H
#define EXIT_PROMPT_H

#include "frontend_widget.h"

class ExitPrompt {
public:
    int destroy_completion_screen(); // @ 0x406060, cRExit::UnInit
    int initialize_exit_prompt(); // @ 0x4060d0, cRExit::Init
    int update_completion_screen(); // @ 0x4067e0, cRExit::AI

    int state; // +0x00
    char unknown_04[0x08 - 0x04];
    int previous_frontend_state; // +0x08
    float prompt_y; // +0x0c
    FrontendWidget* prompt_title; // +0x10
    FrontendWidget* yes_button; // +0x14
    FrontendWidget* no_button; // +0x18
};

typedef char ExitPrompt_must_be_0x1c[
    (sizeof(ExitPrompt) == 0x1c) ? 1 : -1];

int __cdecl launch_alpha72_url(char* url); // @ 0x433050

#endif
