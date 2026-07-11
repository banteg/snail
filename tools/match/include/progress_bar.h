#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

class ProgressBar {
public:
    // cRProgressBar::Init folds into the shared one-byte stub at 0x407b50.
    void noop_runtime_ai();
    void update_progress_bar(); // @ 0x437c40, cRProgressBar::AI

    // Authored empty C++ class; Player supplies alignment padding afterward.
    unsigned char _empty;
};

typedef char ProgressBar_must_be_0x1[(sizeof(ProgressBar) == 0x1) ? 1 : -1];

#endif
