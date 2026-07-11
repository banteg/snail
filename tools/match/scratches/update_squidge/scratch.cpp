// update_squidge @ 0x4449c0 (thiscall, ret)

#include "squidge.h"

void Squidge::update_squidge()
{
    if (y_velocity != 0.0f) {
        y_phase = y_phase + y_velocity;
        y_velocity = (y_velocity - y_phase * 0.15000001f) * 0.81999999f;
        float y_new_output;
        y_output = (y_new_output = -y_phase);
        float y_abs_velocity = y_velocity;
        if (y_abs_velocity < 0.0f)
            y_abs_velocity = -y_abs_velocity;
        if (y_abs_velocity < 0.001f) {
            float y_abs_output;
            if (y_new_output < 0.0f)
                y_abs_output = -y_new_output;
            else
                y_abs_output = y_new_output;
            if (y_abs_output < 0.001f) {
                y_velocity = 0.0f;
                y_output = 0.0f;
            }
        }
    }

    if (z_velocity != 0.0f) {
        z_phase = z_phase + z_velocity;
        z_velocity = (z_velocity - z_phase * 0.15000001f) * 0.81999999f;
        float z_new_output;
        z_output = (z_new_output = -z_phase);
        float z_abs_velocity = z_velocity;
        if (z_abs_velocity < 0.0f)
            z_abs_velocity = -z_abs_velocity;
        if (z_abs_velocity < 0.001f) {
            float z_abs_output;
            if (z_new_output < 0.0f)
                z_abs_output = -z_new_output;
            else
                z_abs_output = z_new_output;
            if (z_abs_output < 0.001f) {
                z_velocity = 0.0f;
                z_output = 0.0f;
            }
        }
    }
}
