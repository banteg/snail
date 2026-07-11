// Complete root-owned landscape manager. The constructor and runtime methods
// prove one contiguous aggregate containing the ten live render entries and
// the parsed script bank.
#ifndef LANDSCAPE_MANAGER_H
#define LANDSCAPE_MANAGER_H

#include "active_landscape_entry.h"
#include "landscape_script.h"

class LandscapeManager {
public:
    void reset_landscape_manager(); // @ 0x4182e0
    int load_landscape_script_by_name(char* script_name); // @ 0x4182f0
    void activate_landscape_entry(int script_index); // @ 0x418870
    void clear_active_landscape_entries(); // @ 0x418a30

    ActiveLandscapeEntry active_entries[10]; // +0x0000
    int script_count; // +0x05a0
    LandscapeScriptRecord scripts[128]; // +0x05a4
};

typedef char LandscapeManager_must_be_0x97a4[
    (sizeof(LandscapeManager) == 0x97a4) ? 1 : -1];

#endif
