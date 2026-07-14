// initialize_subgoldy @ 0x43a9c0 (thiscall, ret 0x4)

#include <stddef.h>

#include "anim_manager.h"
#include "cameraman.h"
#include "click_start.h"
#include "completion.h"
#include "damage_guage.h"
#include "game_root.h"
#include "invincible.h"
#include "object_render_types.h"
#include "sub_hover.h"
#include "player.h"
#include "snail_skin.h"
#include "transform_matrix.h"

extern GameRoot* g_game; // data_4df904

void Player::initialize_subgoldy(int player_slot)
{
    int zero = 0;

    this->player_slot = player_slot;
    this->game = &g_game->subgame;
    this->heading_roll = 0.0f;
    this->row_event.id = zero;
    this->control_override_active = (unsigned char)zero;
    this->nuke.owner_player = this;
    this->nuke.state = NUKE_STATE_INACTIVE;
    this->row_event_cutscene_started = (unsigned char)zero;
    this->resurrect_progress = 0.0f;
    this->completion_handoff_timer = 0.0f;
    this->movement_flags = zero;
    this->previous_movement_flags = -1;
    this->trampoline_bounce_active = (unsigned char)zero;
    this->presentation.invincible_shell.channel_release_steps_active =
        (unsigned char)zero;
    this->game->completion.state = COMPLETION_STATE_INACTIVE;
    this->presentation.jetpack_channel.selected_state = zero;
    this->presentation.weapon_channels[0].selected_state = zero;
    this->presentation.weapon_channels[1].selected_state = zero;
    this->presentation.weapon_channels[2].selected_state = zero;
    this->cutscene_pitch_cycle = 0.0f;
    this->cutscene_pitch_cycle_step = 0.0f;

    this->presentation.object->distort.initialize_object_distort();
    this->interaction_max_z = -19.0f;
    this->movement_sound_variant_sample = zero;
    this->presentation.invincible_shell.cutscene_roll_progress = 0.0f;
    this->presentation.invincible_shell.cutscene_roll_step = 0.0166666675f;
    this->slow_commentary_timer = 0.0f;
    this->slow_commentary_step = 0.0166666675f;
    this->squidge.initialize_score_stats();
    this->presentation.invincible_shell.initialize_invincible_shell();
    this->startup_voice_step = 0.0555555522f;
    this->startup_voice_timer = 0.0555555522f;
    this->attachment_exit_progress = 0.0f;
    this->attachment_exit_progress_step = 0.0166666675f;

    if ((this->presentation.object->flags & OBJECT_FLAG_HAS_ANIMATION) != 0) {
        this->presentation.list_flags |= BOD_FLAG_SYNC_ANIMATION;
        this->presentation.render_animation_manager =
            &this->presentation.anim_manager;
        this->presentation.anim_manager.initialize_anim_manager();
        this->presentation.anim_manager.state = 1;
        this->presentation.anim_manager.target_model = &this->presentation;
        this->presentation.anim_manager.animation_slots =
            this->presentation.cutscene_animation_slots;
        this->presentation.anim_manager.queue_count = zero;
    } else {
        this->presentation.anim_manager.initialize_anim_manager();
        this->presentation.anim_manager.state = zero;
    }

    if ((this->presentation.jetpack_channel.object->flags & OBJECT_FLAG_HAS_ANIMATION) != 0) {
        this->presentation.jetpack_channel.list_flags =
            (this->presentation.jetpack_channel.list_flags
                & ~BOD_FLAG_RENDER_ENABLED)
            | BOD_FLAG_SYNC_ANIMATION;
        this->presentation.jetpack_channel.selected_state = zero;
        this->presentation.jetpack_channel.render_animation_manager =
            &this->presentation.jetpack_channel.anim_manager;
        this->presentation.jetpack_channel.anim_manager.initialize_anim_manager();
        this->presentation.jetpack_channel.anim_manager.state = 1;
        this->presentation.jetpack_channel.anim_manager.target_model =
            &this->presentation.jetpack_channel;
        this->presentation.jetpack_channel.anim_manager.animation_slots =
            this->presentation.jetpack_channel.animation_slots;
        this->presentation.jetpack_channel.anim_manager.queue_count = zero;
    } else {
        this->presentation.jetpack_channel.anim_manager.initialize_anim_manager();
        this->presentation.jetpack_channel.anim_manager.state = zero;
    }

    if ((this->presentation.weapon_channels[0].object->flags
            & OBJECT_FLAG_HAS_ANIMATION) != 0) {
        this->presentation.weapon_channels[0].list_flags =
            (this->presentation.weapon_channels[0].list_flags
                & ~BOD_FLAG_RENDER_ENABLED)
            | BOD_FLAG_SYNC_ANIMATION;
        this->presentation.weapon_channels[0].selected_state = zero;
        this->presentation.weapon_channels[0].render_animation_manager =
            &this->presentation.weapon_channels[0].anim_manager;
        this->presentation.weapon_channels[0].anim_manager.initialize_anim_manager();
        this->presentation.weapon_channels[0].anim_manager.state = 1;
        this->presentation.weapon_channels[0].anim_manager.target_model =
            &this->presentation.weapon_channels[0];
        this->presentation.weapon_channels[0].anim_manager.animation_slots =
            this->presentation.weapon_channels[0].animation_slots;
        this->presentation.weapon_channels[0].anim_manager.queue_count = zero;
    } else {
        this->presentation.weapon_channels[0].anim_manager.initialize_anim_manager();
        this->presentation.weapon_channels[0].anim_manager.state = zero;
    }

    if ((this->presentation.weapon_channels[1].object->flags
            & OBJECT_FLAG_HAS_ANIMATION) != 0) {
        this->presentation.weapon_channels[1].list_flags =
            (this->presentation.weapon_channels[1].list_flags
                & ~BOD_FLAG_RENDER_ENABLED)
            | BOD_FLAG_SYNC_ANIMATION;
        this->presentation.weapon_channels[1].selected_state = zero;
        this->presentation.weapon_channels[1].render_animation_manager =
            &this->presentation.weapon_channels[1].anim_manager;
        this->presentation.weapon_channels[1].anim_manager.initialize_anim_manager();
        this->presentation.weapon_channels[1].anim_manager.state = 1;
        this->presentation.weapon_channels[1].anim_manager.target_model =
            &this->presentation.weapon_channels[1];
        this->presentation.weapon_channels[1].anim_manager.animation_slots =
            this->presentation.weapon_channels[1].animation_slots;
        this->presentation.weapon_channels[1].anim_manager.queue_count = zero;
    } else {
        this->presentation.weapon_channels[1].anim_manager.initialize_anim_manager();
        this->presentation.weapon_channels[1].anim_manager.state = zero;
    }

    if ((this->presentation.weapon_channels[2].object->flags
            & OBJECT_FLAG_HAS_ANIMATION) != 0) {
        this->presentation.weapon_channels[2].list_flags =
            (this->presentation.weapon_channels[2].list_flags
                & ~BOD_FLAG_RENDER_ENABLED)
            | BOD_FLAG_SYNC_ANIMATION;
        this->presentation.weapon_channels[2].selected_state = zero;
        this->presentation.weapon_channels[2].render_animation_manager =
            &this->presentation.weapon_channels[2].anim_manager;
        this->presentation.weapon_channels[2].anim_manager.initialize_anim_manager();
        this->presentation.weapon_channels[2].anim_manager.state = 1;
        this->presentation.weapon_channels[2].anim_manager.target_model =
            &this->presentation.weapon_channels[2];
        this->presentation.weapon_channels[2].anim_manager.animation_slots =
            this->presentation.weapon_channels[2].animation_slots;
        this->presentation.weapon_channels[2].anim_manager.queue_count = zero;
    } else {
        this->presentation.weapon_channels[2].anim_manager.initialize_anim_manager();
        this->presentation.weapon_channels[2].anim_manager.state = zero;
    }

    this->presentation.snail_skin.initialize_snail_skin();
    this->presentation.cutscene.initialize_cutscene_ai();
    if (this->game->selected_level_record_active == 0)
        this->presentation.cutscene.state = 1;
    this->presentation.owner_player = this;
    this->presentation.transform.set_matrix_identity();
    this->presentation.cached_cutscene_matrix.set_matrix_identity();
    this->presentation.previous_live_matrix.set_matrix_identity();
    this->parcels_collected = zero;
    click_start.initialize_click_start(this);
    cameraman.initialize_cameraman();
    initialize_subgoldy_ghost(this->player_slot);

    this->damage_retrigger_step = 0.0505050495f;
    this->surface_reaction_step = 0.0505050495f;
    transform.position.x = 0.0f;
    transform.position.y = 0.0f;
    transform.position.z = 4.0f;
    this->last_ring_spawn_z = 0.0f;
    this->barrier_hold_progress = 0.0f;
    this->barrier_hold_step = 0.0166666675f;
    this->damage_retrigger_timer = 0.0f;
    this->surface_reaction_timer = 0.0f;
    this->presentation.wobble_roll_phase = 0.0f;
    this->presentation.wobble_roll_phase_step = 0.00574712642f;
    this->presentation.wobble_lift_phase = 0.0f;
    this->presentation.wobble_lift_phase_step = 0.00677506765f;
    this->resurrect_active = (unsigned char)zero;
    cached_camera_target_world = transform.position;
    int* velocity_lanes = (int*)&this->velocity;
    velocity_lanes[2] = zero;
    velocity_lanes[1] = zero;
    velocity_lanes[0] = zero;

    int active_slot = this->player_slot;
    PlayerControlSource* control_source;
    if (active_slot == 1) {
        GameRoot* app = g_game;
        GameInput* control_check = &app->game_inputs[0];
        if (control_check != 0)
            control_source = &app->game_inputs[0].input;
        else
            control_source = 0;
    } else {
        GameRoot* app = g_game;
        GameInput* control_check = &app->game_inputs[1];
        if (control_check != 0)
            control_source = &app->game_inputs[1].input;
        else
            control_source = 0;
    }
    this->control_source = control_source;
    this->movement_fire_progress = 0.0f;
    this->completion_handoff_active = (unsigned char)zero;
    this->slide_extension_threshold_z = 0.0f;
    this->damage_gauge.initialize_damage_gauge();
    progress_bar.noop_runtime_ai();
    this->follow_state.active = (unsigned char)zero;

    enum {
        SHOT_TRANSFORM_TO_STATE =
            offsetof(GolbShot, state) - offsetof(GolbShot, flight_transform),
        SHOT_TRANSFORM_TO_GAME =
            offsetof(GolbShot, game) - offsetof(GolbShot, flight_transform),
    };
    char* shot_transform = (char*)&this->golb_shots[0].flight_transform;
    int transform_count = 12;
    do {
        *(int*)(shot_transform + SHOT_TRANSFORM_TO_STATE) = zero;
        ((TransformMatrix*)shot_transform)->set_matrix_identity();
        *(SubgameRuntime**)(shot_transform + SHOT_TRANSFORM_TO_GAME) = this->game;
        shot_transform += sizeof(GolbShot);
        --transform_count;
    } while (transform_count);

    int player_flags = this->list_flags;
    int gauge_slot = this->player_slot;
    player_flags |= 0x20;
    this->list_flags = player_flags;
    this->completion_handoff_cycle_progress = 0.0f;
    this->completion_handoff_cycle_step = 0.208333343f;
    this->unused_274c = zero;
    this->sub_hover.initialize_jetpack_gauge(gauge_slot);
    this->lane_lean_state = zero;
    this->lane_lean_amplitude = 0.0f;
    this->lane_lean_progress = 0.0f;
    this->lane_lean_progress_step = 0.0f;
    this->timer_360_state = zero;
    this->unknown_364 = zero;
    this->timer_360_progress = 0.0f;
    this->timer_360_step = 0.0f;
    this->nuke_effect_progress = 0.0f;
    this->nuke_effect_progress_step = 0.0f;
    this->attachment_exit_pending = (unsigned char)zero;
    this->boost_one_tick = (unsigned char)zero;
    this->lives = zero;
    this->game->camera_snap_requested = 1;
}
