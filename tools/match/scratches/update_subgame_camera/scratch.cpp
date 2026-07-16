// update_subgame_camera @ 0x446020 (thiscall, ret)
// cRSubGame::CameraAI(): choose the active camera source and update the shared
// camera matrix, snapping only when the selected source requests it.

#include "game_root.h"
#include "subgame_runtime.h"


void SubgameRuntime::update_subgame_camera()
{
    int state = subgame_state;
    TransformMatrix from = g_game->players[0].transform;
    camera_snap_requested = 0;

    TransformMatrix target;
    if (state == 1) {
        target.set_matrix_identity();
        target.position.y = 3.0f;
        g_game->players[0].camera.fov_degrees = 110.0f;
    } else {
        player.cameraman.update_cameraman();
        if (player.presentation.cutscene.state != CUT_SCENE_STATE_INACTIVE) {
            camera_snap_requested = player.presentation.cutscene.force_camera_update;
            target = player.presentation.cutscene.live_matrix;
            g_game->players[0].camera.fov_degrees = 110.0f;
        } else {
            target = player.cameraman.live_matrix;
            camera_snap_requested = player.cameraman.force_camera_update;
            g_game->players[0].camera.fov_degrees = player.cameraman.fov_degrees;
        }
    }

    char result = camera_snap_requested;
    if (result != 0) {
        g_game->players[0].transform = target;
        camera_snap_requested = 0;
        return;
    }

    g_game->players[0].transform.linear_interpolate_matrix(
        from, target, 0.89999998f);
}
