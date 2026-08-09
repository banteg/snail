// Complete root-owned landscape manager. The constructor and runtime methods
// prove one contiguous aggregate containing the ten live render entries and
// the parsed script bank.
#ifndef LANDSCAPE_MANAGER_H
#define LANDSCAPE_MANAGER_H

#include "active_landscape_entry.h"
#include "landscape_script.h"

enum {
    LANDSCAPE_ACTIVE_ENTRY_COUNT = 10,
    LANDSCAPE_SCRIPT_CAPACITY = 128,
};

class cRLandscapeManager {
public:
    void Open(); // @ 0x4182e0
    int Import(char* script_name); // @ 0x4182f0
    void Init(int script_index); // @ 0x418870
    void UnInit(); // @ 0x418a30

    ActiveLandscapeEntry active_entries[LANDSCAPE_ACTIVE_ENTRY_COUNT]; // +0x0000
    int script_count; // +0x05a0
    LandscapeScriptRecord scripts[LANDSCAPE_SCRIPT_CAPACITY]; // +0x05a4
};

typedef cRLandscapeManager LandscapeManager;

typedef char cRLandscapeManager_must_be_0x97a4[
    (sizeof(cRLandscapeManager) == 0x97a4) ? 1 : -1];
typedef char LandscapeManager_must_be_0x97a4[
    (sizeof(LandscapeManager) == 0x97a4) ? 1 : -1];

#endif
