// Active landscape/background BOD slots. The runtime uses ten 0x90-byte entries
// as repeated z-slices of the selected landscape object.
#ifndef ACTIVE_LANDSCAPE_ENTRY_H
#define ACTIVE_LANDSCAPE_ENTRY_H

#include "bod_types.h"
#include "landscape_script.h"

struct LandscapeObjectBounds {
    char unknown_000[0xac];
    float min_z; // +0xac
    char unknown_0b0[0xb8 - 0xb0];
    float max_z; // +0xb8
};

struct LandscapeObjectSlotRef {
    LandscapeObjectBounds* object; // +0x00
    char unknown_004[0xbc - 0x04];
};

class ActiveLandscapeEntry : public RenderableBod {
public:
    ActiveLandscapeEntry* initialize_active_landscape_entry(); // @ 0x408820
    void update_active_landscape_entry(); // @ 0x418ac0

    char unknown_078[0x80 - 0x78];
    int state; // +0x80
    char unknown_084[0x88 - 0x84];
    float repeat_z_span; // +0x88
    RenderableBod* reference_bod; // +0x8c, reference transform.position.z drives wrapping
};

typedef char ActiveLandscapeEntry_must_be_0x90[
    (sizeof(ActiveLandscapeEntry) == 0x90) ? 1 : -1];

#endif
