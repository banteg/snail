// Authored cRFringe BOD objects and cRFringeManager pool, partial.
#ifndef FRINGE_OBJECT_H
#define FRINGE_OBJECT_H

#include "bod_types.h"
#include "fringe_fwd.h"

class cRFringe : public BodBase {
public:
    cRFringe(); // @ 0x408650
    void AI(); // @ 0x439b00
};

typedef char cRFringe_must_be_0x38[
    (sizeof(cRFringe) == 0x38) ? 1 : -1];
typedef char Fringe_must_be_0x38[(sizeof(Fringe) == 0x38) ? 1 : -1];

class cRFringeManager {
public:
    void Init(); // @ 0x447090
    cRFringe* GetFringe(); // @ 0x4470a0

    // Fixed storage embedded in cRSubGame. Init() rewinds the cursor;
    // GetFringe() lends the next object without transferring ownership.
    cRFringe objects[7000]; // +0x00000
    int count;              // +0x5fb40
};

typedef cRFringeManager FringeManager;

typedef char cRFringeManager_must_be_0x5fb44[
    (sizeof(cRFringeManager) == 0x5fb44) ? 1 : -1];
typedef char FringeManager_must_be_0x5fb44[
    (sizeof(FringeManager) == 0x5fb44) ? 1 : -1];

#endif
