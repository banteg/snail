// initialize_subgoldy_resurrect @ 0x441fa0 (thiscall, ret 0x4)

class Player {
public:
    int initialize_subgoldy_resurrect(int final_loss);

    char unknown_00[0x80];
    int resurrect_final_loss;          // +0x80
    unsigned char resurrect_active;    // +0x84
    char unknown_85[0x8c - 0x85];
    float resurrect_progress;          // +0x8c
    float resurrect_progress_step;     // +0x90
};

int Player::initialize_subgoldy_resurrect(int final_loss)
{
    resurrect_active = 1;
    resurrect_final_loss = final_loss;
    resurrect_progress = 0.0f;
    resurrect_progress_step = 0.00833333377f;
    return final_loss;
}
