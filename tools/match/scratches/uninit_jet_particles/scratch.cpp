// uninit_jet_particles @ 0x43a580 (thiscall, ret)

class Sprite {
public:
    void kill_sprite();
};

struct JetParticleSlot {
    Sprite* sprite;        // +0x00
    char unknown_04[0xc];  // +0x04
};

class JetpackGaugeController {
public:
    void uninit_jet_particles();

    char unknown_00[0x20];                 // +0x00
    JetParticleSlot particle_slots[15][2]; // +0x20
};

void JetpackGaugeController::uninit_jet_particles()
{
    for (int row = 0; row < 15; row++) {
        for (int column = 0; column < 2; column++) {
            particle_slots[row][column].sprite->kill_sprite();
        }
    }
}
