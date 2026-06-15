// uninit_nuke @ 0x4470e0 (thiscall, ret)

#include "sprite.h"

class NukeController {
public:
    void uninit_nuke();

    int state; // +0x00
    char unknown_04[0x18 - 0x04];
    Sprite* sprite_slots[25]; // +0x18
};

void NukeController::uninit_nuke()
{
    if (state == 1) {
        for (int i = 0; i < 25; i++) {
            sprite_slots[i]->kill_sprite();
        }
        state = 0;
    }
}
