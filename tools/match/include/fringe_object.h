// Authored cRFringe BOD objects and cRFringeManager pool, partial.
#ifndef FRINGE_OBJECT_H
#define FRINGE_OBJECT_H

#include "bod_types.h"
#include "fringe_fwd.h"

class Fringe : public BodBase {
public:
    Fringe* initialize_fringe_object(); // @ 0x408650
    void refresh_fringe_object_draw_list();   // @ 0x439b00
};

typedef char Fringe_must_be_0x38[(sizeof(Fringe) == 0x38) ? 1 : -1];

class FringeManager {
public:
    void initialize_fringe_manager(); // @ 0x447090
    Fringe* allocate_fringe_object(); // @ 0x4470a0

    // Fixed storage embedded in SubgameRuntime. initialize_fringe_manager()
    // rewinds the cursor; allocation never transfers object ownership.
    Fringe objects[7000];       // +0x00000
    int count;                  // +0x5fb40
};

typedef char FringeManager_must_be_0x5fb44[
    (sizeof(FringeManager) == 0x5fb44) ? 1 : -1];

#endif
