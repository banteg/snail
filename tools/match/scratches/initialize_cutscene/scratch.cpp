// initialize_cutscene @ 0x4428d0 (thiscall, ret)

#include "game_root.h"
#include "player.h"

extern char* g_game_base; // data_4df904

float sine(float angle);

void Snail::initialize_cutscene()
{
    if (((GameRoot*)g_game_base)->subgame.subgame_pause_gate != 0)
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
        scratch_matrix.rotate_matrix_world_x(angle);
        owner_player->live_transform()->linear_interpolate_matrix(
            &scratch_matrix, &source_matrix, 0.939999998f);
    } else {
        if (owner_player->attachment_exit_pending != 0) {
            scratch_matrix = *owner_player->live_transform();
            source_matrix = *owner_player->live_transform();
            scratch_matrix.set_matrix_rotation_identity();
            owner_player->live_transform()->linear_interpolate_matrix(
                &scratch_matrix, &source_matrix, 0.970000029f);
        }
    }

    Player* player = owner_player;
    live_matrix = *player->live_transform();
    Vector3* camera_target = &player->cached_camera_target_world;
    live_matrix.position = *camera_target;

    scratch_matrix = live_matrix;
    live_matrix.linear_interpolate_matrix(
        &scratch_matrix,
        &cached_cutscene_matrix,
        0.699999988f);
    float up_y = live_matrix.basis_up.y;
    live_matrix.position = scratch_matrix.position;

    if (up_y > 0.0f) {
        float yaw = (live_matrix.position.x - cached_cutscene_matrix.position.x)
            * 0.800000012f;
        live_matrix.rotate_matrix_world_y(yaw);
    }

    wobble_roll_phase = wobble_roll_phase_step + wobble_roll_phase;
    if (wobble_roll_phase > 1.0f)
        wobble_roll_phase = wobble_roll_phase - 1.0f;

    wobble_lift_phase = wobble_lift_phase_step + wobble_lift_phase;
    if (wobble_lift_phase > 1.0f)
        wobble_lift_phase = wobble_lift_phase - 1.0f;

    base_matrix = live_matrix;
    set_matrix_identity(&roll_matrix);
    roll_matrix.rotate_matrix_world_z(
        sine(wobble_roll_phase * 6.28318548f) * 0.0174499992f);

    inverse_live.invert_matrix_from_source(&live_matrix);
    live_matrix.multiply_matrix_in_place(&inverse_live);
    live_matrix.position.y = live_matrix.position.y + 1.29999995f;
    live_matrix.multiply_matrix_in_place(&roll_matrix);
    live_matrix.position.y = live_matrix.position.y - 1.29999995f;
    live_matrix.multiply_matrix_in_place(&base_matrix);

    float lift_sine = sine(wobble_lift_phase * 6.28318548f);
    live_matrix.position +=
        (live_matrix.basis_up * lift_sine) * 0.0299999993f;

    float shell_roll_progress = invincible_shell.cutscene_roll_progress;
    cached_cutscene_matrix = live_matrix;

    if (shell_roll_progress > 0.0f) {
        float shell_yaw = invincible_shell.cutscene_roll_progress * -2.09439516f;
        live_matrix.rotate_matrix_world_y(shell_yaw);
        invincible_shell.cutscene_roll_progress =
            invincible_shell.cutscene_roll_step + invincible_shell.cutscene_roll_progress;
        if (invincible_shell.cutscene_roll_progress > 1.0f)
            invincible_shell.cutscene_roll_progress = 1.0f;
    }

    if (invincible_shell.channel_release_steps_active != 0) {
        jetpack_channel.live_matrix.position.x =
            jetpack_channel.release_step.x + jetpack_channel.live_matrix.position.x;
        jetpack_channel.live_matrix.position.y =
            jetpack_channel.release_step.y + jetpack_channel.live_matrix.position.y;
        jetpack_channel.live_matrix.position.z =
            jetpack_channel.release_step.z + jetpack_channel.live_matrix.position.z;

        weapon_channels[0].live_matrix.position.x =
            weapon_channels[0].release_step.x + weapon_channels[0].live_matrix.position.x;
        weapon_channels[0].live_matrix.position.y =
            weapon_channels[0].release_step.y + weapon_channels[0].live_matrix.position.y;
        weapon_channels[0].live_matrix.position.z =
            weapon_channels[0].release_step.z + weapon_channels[0].live_matrix.position.z;

        weapon_channels[2].live_matrix.position.x =
            weapon_channels[2].release_step.x + weapon_channels[2].live_matrix.position.x;
        weapon_channels[2].live_matrix.position.y =
            weapon_channels[2].release_step.y + weapon_channels[2].live_matrix.position.y;
        weapon_channels[2].live_matrix.position.z =
            weapon_channels[2].release_step.z + weapon_channels[2].live_matrix.position.z;

        weapon_channels[1].live_matrix.position.x =
            weapon_channels[1].release_step.x + weapon_channels[1].live_matrix.position.x;
        weapon_channels[1].live_matrix.position.y =
            weapon_channels[1].release_step.y + weapon_channels[1].live_matrix.position.y;
        weapon_channels[1].live_matrix.position.z =
            weapon_channels[1].release_step.z + weapon_channels[1].live_matrix.position.z;
    } else {
        jetpack_channel.live_matrix = live_matrix;
        weapon_channels[0].live_matrix = live_matrix;
        weapon_channels[2].live_matrix = live_matrix;
        weapon_channels[1].live_matrix = live_matrix;
    }

    snail_hotspot_source_matrix_a = live_matrix;
    snail_hotspot_body.transform = *owner_player->live_transform();
    camera_target = &owner_player->cached_camera_target_world;
    snail_hotspot_body.transform.position = *camera_target;

    update_snail_skin();

    if (cutscene.state != 0) {
        cutscene.update_cutscene();
    } else if (anim_manager.queue_count == 0 && owner_player->control_override_active == 0) {
        dispatch_cutscene_animation(1, 0, -1);
    }

    owner_player->sub_hover.update_jet_particles();
}
