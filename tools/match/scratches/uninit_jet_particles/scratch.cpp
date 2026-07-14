// uninit_jet_particles @ 0x43a580 (thiscall, ret)

#include "sub_hover.h"
#include "sprite.h"

void SubHover::uninit_jet_particles()
{
    for (int row = 0; row < JET_PARTICLE_ROW_COUNT; row++) {
        for (int column = 0; column < JET_PARTICLE_COLUMN_COUNT; column++) {
            particle_slots[row][column].sprite->kill_sprite();
        }
    }
}
