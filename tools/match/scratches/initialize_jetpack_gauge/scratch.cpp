// initialize_jetpack_gauge @ 0x43a930 (thiscall, returns 0)

extern char* g_game_base; // data_4df904

class JetpackGaugeController {
public:
    int initialize_jetpack_gauge(int player_slot);

    float progress;                   // +0x00
    float progress_step;              // +0x04
    char unknown_08[0x4];             // +0x08
    int state;                        // +0x0c
    char* player;                     // +0x10
    float wobble_x;                   // +0x14
    float wobble_y;                   // +0x18
    float wobble_alpha;               // +0x1c
    char particle_slots[0x1e0];       // +0x20
    char* game;                       // +0x200
    char unknown_204[0x8];            // +0x204
    float warning_intensity_latch;    // +0x20c
    float warning_intensity;          // +0x210
};

int JetpackGaugeController::initialize_jetpack_gauge(int player_slot)
{
    progress = 0.0f;
    char* game_ptr = g_game_base + 0x74618;
    progress_step = 0.00166666671f;
    game = game_ptr;
    char* player_ptr = g_game_base + 0x42fd7c;
    state = 0;
    player = player_ptr;
    wobble_alpha = 0.0f;
    wobble_y = 0.0f;
    wobble_x = 0.0f;
    warning_intensity_latch = 0.0f;
    return 0;
}
