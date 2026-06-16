// calc_subgame_rate @ 0x4404d0 (thiscall, ret)

float sine(float angle);

class Game {
public:
    void calc_subgame_rate();

    char unknown_00[0x30];
    float base_rate; // +0x30
    char unknown_34[0x38 - 0x34];
    float subgame_rate; // +0x38
    int subgame_state; // +0x3c
    int level_mode; // +0x40
    char unknown_44[0x58 - 0x44];
    int completion_row_start; // +0x58
    char unknown_5c[0x3bb7d4 - 0x5c];
    float completion_progress_z; // +0x3bb7d4
    char unknown_3bb7d8[0x3bbb28 - 0x3bb7d8];
    int bonus_rate_state; // +0x3bbb28
    char unknown_3bbb2c[0x3bbb48 - 0x3bbb2c];
    float bonus_rate_phase; // +0x3bbb48
    char unknown_3bbb4c[0x3bdec0 - 0x3bbb4c];
    int nuke_rate_state; // +0x3bdec0
    char unknown_3bdec4[0x3be0c0 - 0x3bdec4];
    float nuke_rate_progress; // +0x3be0c0
};

void Game::calc_subgame_rate()
{
    if (subgame_state == 2) {
        float completion_fraction = completion_progress_z / (float)completion_row_start;
        if (completion_fraction < 0.0f)
            completion_fraction = 0.0f;
        else if (completion_fraction > 1.0f)
            completion_fraction = 1.0f;

        int mode = level_mode;
        if (mode == 1 || mode == 3) {
            subgame_rate = completion_fraction * 0.550000012f + base_rate;
        } else if (mode == 4) {
            subgame_rate = completion_fraction * 0.400000006f + base_rate + 0.200000003f;
        } else {
            subgame_rate = completion_fraction * 0.200000003f + base_rate;
        }

        if (bonus_rate_state == 2) {
            float bonus = 0.600000024f;
            if (mode == 1 || mode == 4)
                bonus = 0.400000006f;
            float phase = bonus_rate_phase;
            if (phase < 0.25 || phase > 0.75) {
                bonus = (1.0f - sine(phase * 12.566371f + 1.57079637f))
                    * 0.5f * bonus;
            }
            subgame_rate += bonus;
        }

        if (nuke_rate_state == 1)
            subgame_rate += nuke_rate_progress * 0.5f;
    } else {
        subgame_rate = base_rate;
    }
}
