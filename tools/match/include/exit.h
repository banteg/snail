// Authored cRExit owner embedded in GameRoot.
#ifndef EXIT_H
#define EXIT_H

#include "frontend_widget.h"

class cRExit {
public:
    void UnInit(); // @ 0x406060
    void Init();   // @ 0x4060d0
    void AI();     // @ 0x4067e0

    int state; // +0x00
    char unknown_04[0x08 - 0x04];
    int previous_frontend_state; // +0x08
    float prompt_y; // +0x0c
    cRBorder* prompt_title; // +0x10
    cRBorder* yes_button; // +0x14
    cRBorder* no_button; // +0x18
};

typedef cRExit Exit;
typedef char Exit_must_be_0x1c[
    (sizeof(cRExit) == 0x1c) ? 1 : -1];

int __cdecl launch_alpha72_url(char* url); // @ 0x433050

#endif
