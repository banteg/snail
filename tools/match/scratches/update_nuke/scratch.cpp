// update_nuke @ 0x4471e0 (thiscall, ret)

struct Vector3 {
    float x;
    float y;
    float z;
};

struct Sprite {
    char unknown_00[0x48];
    Vector3 position; // +0x48
};

class NukeController {
public:
    int update_nuke();

    int state; // +0x00
    void* owner_player; // +0x04
    float orbit_axis_step; // +0x08
    float orbit_axis; // +0x0c
    float phase; // +0x10
    float phase_step; // +0x14
    Sprite* sprite_slots[25]; // +0x18
};

float sine(float radians);
float cosine(float radians);

int NukeController::update_nuke()
{
    NukeController* self = this;
    int result = self->state;
    if (result) {
        if (--result == 0) {
            self->orbit_axis = self->orbit_axis_step + self->orbit_axis;

            float advanced_phase = self->phase_step + self->phase;
            self->phase = advanced_phase;
            if (advanced_phase > 6.2831855f)
                self->phase = advanced_phase - 6.2831855f;

            Sprite** slots = self->sprite_slots;
            int i = 0;
            do {
                float angle_base = (float)i * 0.039999999f;
                float angle = angle_base * 6.2831855f + self->phase;
                (*slots)->position.z = self->orbit_axis;
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
