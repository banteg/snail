// update_snail_presentation @ 0x4428d0 (thiscall, ret)

#include "game_root.h"
#include "player.h"


float sine(float angle);

void cRSnail::AIGoldy()
{
    if (g_game->subgame.subgame_pause_gate != 0)
        return;

    snail_skin.AI();

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
        scratch_matrix.RotIdentity();

        float angle =
            (-0.785398185f - owner_player->cutscene_pitch_cycle * 6.28318548f)
            * 1.39999998f;
        if (angle < -6.28318548f)
            angle = -6.28318548f;
        scratch_matrix.RotLocalX(angle);
        owner_player->live_transform()->LinearInterpolate(
            scratch_matrix, source_matrix, 0.939999998f);
    } else {
        if (owner_player->attachment_exit_pending != 0) {
            scratch_matrix = *owner_player->live_transform();
            source_matrix = *owner_player->live_transform();
            scratch_matrix.RotIdentity();
            owner_player->live_transform()->LinearInterpolate(
                scratch_matrix, source_matrix, 0.970000029f);
        }
    }

    cRSubGoldy* player = owner_player;
    transform = *player->live_transform();
    Vector3* camera_target = &player->cached_camera_target_world;
    transform.position = *camera_target;

    scratch_matrix = transform;
    transform.LinearInterpolate(
        scratch_matrix,
        cached_cutscene_matrix,
        0.699999988f);
    float up_y = transform.basis_up.y;
    transform.position = scratch_matrix.position;

    if (up_y > 0.0f) {
        float yaw = (transform.position.x - cached_cutscene_matrix.position.x)
            * 0.800000012f;
        transform.RotLocalY(yaw);
    }

    wobble.roll_phase = wobble.roll_phase_step + wobble.roll_phase;
    if (wobble.roll_phase > 1.0f)
        wobble.roll_phase = wobble.roll_phase - 1.0f;

    wobble.lift_phase = wobble.lift_phase_step + wobble.lift_phase;
    if (wobble.lift_phase > 1.0f)
        wobble.lift_phase = wobble.lift_phase - 1.0f;

    base_matrix = transform;
    roll_matrix.Identity();
    roll_matrix.RotLocalZ(
        sine(wobble.roll_phase * 6.28318548f) * 0.0174499992f);

    inverse_live.Invert(transform);
    transform *= inverse_live;
    transform.position.y = transform.position.y + 1.29999995f;
    transform *= roll_matrix;
    transform.position.y = transform.position.y - 1.29999995f;
    transform *= base_matrix;

    float lift_sine = sine(wobble.lift_phase * 6.28318548f);
    transform.position +=
        (transform.basis_up * lift_sine) * 0.0299999993f;

    float shell_roll_progress = cutscene_roll_progress;
    cached_cutscene_matrix = transform;

    if (shell_roll_progress > 0.0f) {
        float shell_yaw = cutscene_roll_progress * -2.09439516f;
        transform.RotLocalY(shell_yaw);
        cutscene_roll_progress = cutscene_roll_step + cutscene_roll_progress;
        if (cutscene_roll_progress > 1.0f)
            cutscene_roll_progress = 1.0f;
    }

    if (channel_release_steps_active != 0) {
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

    BuildHotSpots();

    if (cutscene.state != CUT_SCENE_STATE_INACTIVE) {
        cutscene.AI();
    } else if (anim_manager.queue_count == 0 && owner_player->slug_fall_active == 0) {
        dispatch_cutscene_animation(1, 0, OBJECT_ANIMATION_MODE_UNCHANGED);
    }

    owner_player->sub_hover.Jets();
}
