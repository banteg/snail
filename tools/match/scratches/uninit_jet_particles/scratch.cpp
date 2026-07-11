// uninit_jet_particles @ 0x43a580 (thiscall, ret)

#include "sub_hover.h"
#include "sprite.h"

void SubHover::uninit_jet_particles()
{
    for (int row = 0; row < 15; row++) {
        for (int column = 0; column < 2; column++) {
            particle_slots[row][column].sprite->kill_sprite();
        }
    }
}
