// Authored cRTutorial owner embedded in SubgameRuntime.
#ifndef TUTORIAL_H
#define TUTORIAL_H

class SubgameRuntime;

class Tutorial {
public:
    void initialize_tutorial(); // @ 0x448da0, cRTutorial::Init
    void uninit_tutorial(); // @ 0x448dd0, cRTutorial::UnInit
    void* update_tutorial(); // @ 0x448de0, cRTutorial::AI

    int state; // +0x00
    char unknown_04[0x0c - 0x04];
    SubgameRuntime* game; // +0x0c, borrowed containing subgame
    char unknown_10[0x1c - 0x10];
};

typedef char Tutorial_must_be_0x1c[
    (sizeof(Tutorial) == 0x1c) ? 1 : -1];

#endif
