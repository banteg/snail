// uninit_jet_particles @ 0x43a580 (thiscall, ret)

#include "jetpack_gauge.h"
#include "sprite.h"

void JetpackGaugeController::uninit_jet_particles()
{
    for (int row = 0; row < 15; row++) {
        for (int column = 0; column < 2; column++) {
            particle_slots[row][column].sprite->kill_sprite();
        }
    }
}
