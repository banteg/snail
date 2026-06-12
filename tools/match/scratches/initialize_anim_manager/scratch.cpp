// initialize_anim_manager @ 0x4447c0 (thiscall, ret)

class AnimationDispatchState {
public:
    void initialize_anim_manager();

    int active;           // +0x00
    float progress;       // +0x04
    float progress_step;  // +0x08
    char unknown_0c[0x04];
    unsigned char edge_latched; // +0x10
};

void AnimationDispatchState::initialize_anim_manager()
{
    progress = 0.0f;
    progress_step = 0.0f;
    active = 0;
    edge_latched = 0;
}
