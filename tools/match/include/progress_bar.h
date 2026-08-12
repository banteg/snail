#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

class cRProgressBar {
public:
    // cRProgressBar::Init folds into the shared one-byte stub at 0x407b50.
    void noop_runtime_ai();
    void AI(); // @ 0x437c40

    // Authored empty C++ class; cRSubGoldy supplies alignment padding afterward.
    unsigned char _empty;
};

typedef cRProgressBar ProgressBar;
typedef char ProgressBar_must_be_0x1[
    (sizeof(cRProgressBar) == 0x1) ? 1 : -1];

#endif
