#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

class ProgressBar {
public:
    void update_progress_bar(); // @ 0x437c40

    int state; // +0x00
};

typedef char ProgressBar_must_be_0x4[(sizeof(ProgressBar) == 0x4) ? 1 : -1];

#endif
