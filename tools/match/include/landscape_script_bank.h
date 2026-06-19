// Landscape script lookup interface used by menu/help backdrop setup and level
// definition parsing.
#ifndef LANDSCAPE_SCRIPT_BANK_H
#define LANDSCAPE_SCRIPT_BANK_H

#include "landscape_script.h"

class LandscapeScriptBank {
public:
    int load_landscape_script_by_name(char* script_name);

    char unknown_000[0x5a0];
    int script_count; // +0x5a0
    LandscapeScriptRecord scripts[128]; // +0x5a4
};

#endif
