// Authored cRTutorial owner embedded in cRSubGame.
#ifndef TUTORIAL_H
#define TUTORIAL_H

class cRSubGame;

class cRTutorial {
public:
    void Init(); // @ 0x448da0
    void UnInit(); // @ 0x448dd0
    void AI(); // @ 0x448de0

    int state; // +0x00
    char unknown_04[0x0c - 0x04];
    cRSubGame* game; // +0x0c, borrowed containing subgame
    char unknown_10[0x1c - 0x10];
};

typedef cRTutorial Tutorial;
typedef char Tutorial_must_be_0x1c[
    (sizeof(cRTutorial) == 0x1c) ? 1 : -1];

#endif
