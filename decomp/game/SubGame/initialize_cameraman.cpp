// initialize_cameraman @ 0x446160 (thiscall, ret)
#include "cameraman.h"
#include "game_root.h"


void cRCameraman::Init()
{
    player = g_game->subgame.embedded_player();
    game = &g_game->subgame;
    force_camera_update = 0;
    previous_desired_matrix.Identity();
    desired_matrix.Identity();
    live_matrix.Identity();
    attachment_lift_envelope = 0.0f;
    smoothed_attachment_lift_envelope = 0.0f;
    fov_degrees = 110.0f;
}
