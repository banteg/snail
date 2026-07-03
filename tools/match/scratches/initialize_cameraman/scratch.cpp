// initialize_cameraman @ 0x446160 (thiscall, ret)
#include "cameraman_state.h"

extern char* g_game_base; // data_4df904

void CameramanState::initialize_cameraman()
{
    player = (Player*)(g_game_base + 0x42fd7c);
    game = (SubgameRuntime*)(g_game_base + 0x74618);
    unresolved_cc = 0;
    set_matrix_identity(&previous_desired_matrix);
    set_matrix_identity(&desired_matrix);
    set_matrix_identity(&live_matrix);
    attachment_lift_envelope = 0.0f;
    smoothed_attachment_lift_envelope = 0.0f;
    fov_degrees = 110.0f;
}
