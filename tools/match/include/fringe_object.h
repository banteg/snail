// Track fringe BOD objects and pool manager, partial.
#ifndef FRINGE_OBJECT_H
#define FRINGE_OBJECT_H

#include "bod_types.h"

class FringeObject : public BodBase {
public:
    FringeObject* initialize_fringe_object(); // @ 0x408650
    void refresh_fringe_object_draw_list();   // @ 0x439b00
};

typedef char FringeObject_must_be_0x38[(sizeof(FringeObject) == 0x38) ? 1 : -1];

class FringeManager {
public:
    void initialize_fringe_manager(); // @ 0x447090
    FringeObject* allocate_fringe_object(); // @ 0x4470a0

    // Fixed storage embedded in SubgameRuntime. initialize_fringe_manager()
    // rewinds the cursor; allocation never transfers object ownership.
    FringeObject objects[7000]; // +0x00000
    int count;                  // +0x5fb40
};

typedef char FringeManager_must_be_0x5fb44[
    (sizeof(FringeManager) == 0x5fb44) ? 1 : -1];

#endif
