// update_subgame_camera @ 0x446020 (thiscall, ret)
// cRSubGame::CameraAI(): choose the active camera source and update the shared
// camera matrix, snapping only when the selected source requests it.

#include "cameraman_state.h"

class Game {
public:
    void update_subgame_camera();

    char unknown_00[0x01];
    unsigned char camera_snap_requested; // +0x01, transient source switch flag
    char unknown_02[0x3c - 0x02];
    int subgame_state; // +0x3c
    char unknown_40[0x3bb964 - 0x40];
    CameramanState cameraman; // +0x3bb964
    char unknown_3bba3c[0x3bfa4c - 0x3bba3c];
    int override_camera_active; // +0x3bfa4c
    TransformMatrix override_camera_matrix; // +0x3bfa50
    char unknown_3bfa90[0x3bfa98 - 0x3bfa90];
    unsigned char override_camera_snap; // +0x3bfa98
};

extern int g_game_base; // data_4df904

void Game::update_subgame_camera()
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
