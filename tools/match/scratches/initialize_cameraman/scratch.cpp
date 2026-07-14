// initialize_cameraman @ 0x446160 (thiscall, ret)
#include "cameraman.h"
#include "game_root.h"

extern GameRoot* g_game; // data_4df904

void Cameraman::initialize_cameraman()
{
    player = g_game->subgame.embedded_player();
    game = &g_game->subgame;
    force_camera_update = 0;
    previous_desired_matrix.set_matrix_identity();
    desired_matrix.set_matrix_identity();
    live_matrix.set_matrix_identity();
    attachment_lift_envelope = 0.0f;
    smoothed_attachment_lift_envelope = 0.0f;
    fov_degrees = 110.0f;
}
