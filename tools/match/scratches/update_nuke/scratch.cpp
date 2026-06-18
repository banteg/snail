// update_nuke @ 0x4471e0 (thiscall, ret)

#include "nuke_controller.h"

float sine(float radians);
float cosine(float radians);

int NukeController::update_nuke()
{
    NukeController* self = this;
    int result = self->state;
    if (result) {
        if (--result == 0) {
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
    }
    return result;
}
