// initialize_cutscene @ 0x4428d0 (thiscall, ret)

#include "game_root.h"
#include "player.h"

extern GameRoot* g_game; // data_4df904

float sine(float angle);

void Snail::initialize_cutscene()
{
    if (g_game->subgame.subgame_pause_gate != 0)
        return;

    snail_skin.update_snail_skin_transition();

    TransformMatrix scratch_matrix;
    TransformMatrix source_matrix;
    TransformMatrix roll_matrix;
    TransformMatrix inverse_live;
    TransformMatrix base_matrix;
    if (owner_player->cutscene_pitch_cycle > 0.0f) {
        owner_player->cutscene_pitch_cycle =
            owner_player->cutscene_pitch_cycle_step + owner_player->cutscene_pitch_cycle;
        if (owner_player->cutscene_pitch_cycle > 1.0f)
            owner_player->cutscene_pitch_cycle = 0.0f;

        scratch_matrix = *owner_player->live_transform();
        source_matrix = *owner_player->live_transform();
        scratch_matrix.set_matrix_rotation_identity();

        float angle =
            (-0.785398185f - owner_player->cutscene_pitch_cycle * 6.28318548f)
            * 1.39999998f;
        if (angle < -6.28318548f)
            angle = -6.28318548f;
        scratch_matrix.rotate_matrix_local_x(angle);
        owner_player->live_transform()->linear_interpolate_matrix(
            scratch_matrix, source_matrix, 0.939999998f);
    } else {
        if (owner_player->attachment_exit_pending != 0) {
            scratch_matrix = *owner_player->live_transform();
            source_matrix = *owner_player->live_transform();
            scratch_matrix.set_matrix_rotation_identity();
            owner_player->live_transform()->linear_interpolate_matrix(
                scratch_matrix, source_matrix, 0.970000029f);
        }
    }

    Player* player = owner_player;
    transform = *player->live_transform();
    Vector3* camera_target = &player->cached_camera_target_world;
    transform.position = *camera_target;

    scratch_matrix = transform;
    transform.linear_interpolate_matrix(
        scratch_matrix,
        cached_cutscene_matrix,
        0.699999988f);
    float up_y = transform.basis_up.y;
    transform.position = scratch_matrix.position;

    if (up_y > 0.0f) {
        float yaw = (transform.position.x - cached_cutscene_matrix.position.x)
            * 0.800000012f;
        transform.rotate_matrix_local_y(yaw);
    }

    wobble_roll_phase = wobble_roll_phase_step + wobble_roll_phase;
    if (wobble_roll_phase > 1.0f)
        wobble_roll_phase = wobble_roll_phase - 1.0f;

    wobble_lift_phase = wobble_lift_phase_step + wobble_lift_phase;
    if (wobble_lift_phase > 1.0f)
        wobble_lift_phase = wobble_lift_phase - 1.0f;

    base_matrix = transform;
    roll_matrix.set_matrix_identity();
    roll_matrix.rotate_matrix_local_z(
        sine(wobble_roll_phase * 6.28318548f) * 0.0174499992f);

    inverse_live.invert_matrix_from_source(transform);
    transform.multiply_matrix(inverse_live);
    transform.position.y = transform.position.y + 1.29999995f;
    transform.multiply_matrix(roll_matrix);
    transform.position.y = transform.position.y - 1.29999995f;
    transform.multiply_matrix(base_matrix);

    float lift_sine = sine(wobble_lift_phase * 6.28318548f);
    transform.position +=
        (transform.basis_up * lift_sine) * 0.0299999993f;

    float shell_roll_progress = invincible_shell.cutscene_roll_progress;
    cached_cutscene_matrix = transform;

    if (shell_roll_progress > 0.0f) {
        float shell_yaw = invincible_shell.cutscene_roll_progress * -2.09439516f;
        transform.rotate_matrix_local_y(shell_yaw);
        invincible_shell.cutscene_roll_progress =
            invincible_shell.cutscene_roll_step + invincible_shell.cutscene_roll_progress;
        if (invincible_shell.cutscene_roll_progress > 1.0f)
            invincible_shell.cutscene_roll_progress = 1.0f;
    }

    if (invincible_shell.channel_release_steps_active != 0) {
        jetpack_channel.transform.position.x =
            jetpack_channel.release_step.x + jetpack_channel.transform.position.x;
        jetpack_channel.transform.position.y =
            jetpack_channel.release_step.y + jetpack_channel.transform.position.y;
        jetpack_channel.transform.position.z =
            jetpack_channel.release_step.z + jetpack_channel.transform.position.z;

        weapon_channels[0].transform.position.x =
            weapon_channels[0].release_step.x + weapon_channels[0].transform.position.x;
        weapon_channels[0].transform.position.y =
            weapon_channels[0].release_step.y + weapon_channels[0].transform.position.y;
        weapon_channels[0].transform.position.z =
            weapon_channels[0].release_step.z + weapon_channels[0].transform.position.z;

        weapon_channels[2].transform.position.x =
            weapon_channels[2].release_step.x + weapon_channels[2].transform.position.x;
        weapon_channels[2].transform.position.y =
            weapon_channels[2].release_step.y + weapon_channels[2].transform.position.y;
        weapon_channels[2].transform.position.z =
            weapon_channels[2].release_step.z + weapon_channels[2].transform.position.z;

        weapon_channels[1].transform.position.x =
            weapon_channels[1].release_step.x + weapon_channels[1].transform.position.x;
        weapon_channels[1].transform.position.y =
            weapon_channels[1].release_step.y + weapon_channels[1].transform.position.y;
        weapon_channels[1].transform.position.z =
            weapon_channels[1].release_step.z + weapon_channels[1].transform.position.z;
    } else {
        jetpack_channel.transform = transform;
        weapon_channels[0].transform = transform;
        weapon_channels[2].transform = transform;
        weapon_channels[1].transform = transform;
    }

    snail_hotspot_source_body.transform = transform;
    snail_hotspot_body.transform = *owner_player->live_transform();
    camera_target = &owner_player->cached_camera_target_world;
    snail_hotspot_body.transform.position = *camera_target;

    update_snail_skin();

    if (cutscene.state != CUT_SCENE_STATE_INACTIVE) {
        cutscene.update_cutscene();
    } else if (anim_manager.queue_count == 0 && owner_player->control_override_active == 0) {
        dispatch_cutscene_animation(1, 0, OBJECT_ANIMATION_MODE_UNCHANGED);
    }

    owner_player->sub_hover.update_jet_particles();
}
