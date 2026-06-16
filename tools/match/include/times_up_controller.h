// Times-up message controller view, partial.
#ifndef TIMES_UP_CONTROLLER_H
#define TIMES_UP_CONTROLLER_H

#include "frontend_widget.h"

class TimesUpController {
public:
    void update_times_up(); // @ 0x445e20
    void uninit_times_up(); // @ 0x445e70
    void show_times_up_message(); // @ 0x445e90

    int state; // +0x00
    FrontendWidget* border; // +0x04
    float progress; // +0x08
    float progress_step; // +0x0c
};

typedef char TimesUpController_must_be_0x10[
    (sizeof(TimesUpController) == 0x10) ? 1 : -1];

#endif
