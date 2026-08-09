// uninit_jet_particles / cRSubHover::JetUnInit @ 0x43a580 (thiscall, ret)

#include "sub_hover.h"
#include "sprite.h"

void cRSubHover::JetUnInit()
{
    for (int row = 0; row < JET_PARTICLE_ROW_COUNT; row++) {
        for (int column = 0; column < JET_PARTICLE_COLUMN_COUNT; column++) {
            particle_slots[row][column].sprite->Kill();
        }
    }
}
