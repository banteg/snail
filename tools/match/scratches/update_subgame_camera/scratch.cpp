// update_subgame_camera @ 0x446020 (thiscall, ret)
// cRSubGame::CameraAI(): choose the active camera source and update the shared
// camera matrix, snapping only when the selected source requests it.

#include "subgame_runtime.h"


void SubgameRuntime::update_subgame_camera()
{
    int state = subgame_state;
    TransformMatrix from = *(TransformMatrix*)(g_game_base + 0x15c);
    camera_snap_requested = 0;

    TransformMatrix target;
    if (state == 1) {
        set_matrix_identity(&target);
        target.position.y = 3.0f;
        *(float*)(g_game_base + 0x284) = 110.0f;
    } else {
        cameraman.update_cameraman();
        if (override_camera_active != 0) {
            camera_snap_requested = override_camera_snap;
            target = override_camera_matrix;
            *(float*)(g_game_base + 0x284) = 110.0f;
        } else {
            target = cameraman.live_matrix;
            camera_snap_requested = cameraman.unresolved_cc;
            *(float*)(g_game_base + 0x284) = cameraman.fov_degrees;
        }
    }

    char result = camera_snap_requested;
    if (result != 0) {
        *(TransformMatrix*)(g_game_base + 0x15c) = target;
        camera_snap_requested = 0;
        return;
    }

    ((TransformMatrix*)(g_game_base + 0x15c))->linear_interpolate_matrix(
        &from, &target, 0.89999998f);
}
