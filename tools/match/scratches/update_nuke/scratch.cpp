// update_nuke @ 0x4471e0 (thiscall)

#include "nuke.h"

float sine(float radians);
float cosine(float radians);

void Nuke::update_nuke()
{
    Nuke* self = this;
    int result = self->state;
    switch (result) {
    case 0:
        goto done;
    case 1:
        goto active;
    default:
        goto done;
    }
done:
    return;

active:
    self->orbit_center_z = self->orbit_center_z_step + self->orbit_center_z;

    float advanced_phase = self->orbit_phase_step + self->orbit_phase;
    self->orbit_phase = advanced_phase;
    if (advanced_phase > 6.2831855f)
        self->orbit_phase = advanced_phase - 6.2831855f;

    int i = 0;
    Sprite** slots = self->sprite_slots;
    do {
        float angle_base = (float)i * 0.039999999f;
        float angle = angle_base * 6.2831855f + self->orbit_phase;
        (*slots)->position.z = self->orbit_center_z;
        float angle_arg = angle;
        (*slots)->position.x = sine(angle_arg) * 7.0f;
        float y = cosine(angle_arg) * 7.0f;
        result = (int)*slots;
        i++;
        slots++;
        ((Sprite*)result)->position.y = y;
    } while (i < 25);
}
