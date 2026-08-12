// Authored cRHelp front-end owner embedded in cRSubGame.
#ifndef HELP_H
#define HELP_H

#include "frontend_widget.h"

class cRHelp {
public:
    void Init();   // @ 0x416800
    void UnInit(); // @ 0x4168c0
    void AI();     // @ 0x4168d0

    cRBorder* back_button; // +0x00
};

typedef cRHelp Help;
typedef char Help_must_be_0x04[(sizeof(cRHelp) == 0x04) ? 1 : -1];

#endif
