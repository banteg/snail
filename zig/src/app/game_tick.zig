const audio = @import("audio.zig");
const boot_assets = @import("boot_assets.zig");
const render_phase = @import("render_phase.zig");
const selected_replay = @import("selected_replay.zig");

const gameplay = @import("../gameplay.zig");
const gameplay_presentation = @import("../gameplay/presentation.zig");
const gameplay_resources = @import("../gameplay/resources.zig");

pub fn simulate(state: anytype, runner_input: gameplay.RunnerInput) !void {
    const effective_runner_input = if (state.completionScreenOverlayActive())
        gameplay.RunnerInput{}
    else
        runner_input;
    state.game_phase_ticks += 1;
    if (state.current_game_background_runtime) |*runtime| {
        runtime.update();
    }
    state.background_light_streaks.update(
        render_phase.lightStreakCamera(state),
        render_phase.lightStreaksVisible(state),
    );
    if (state.game_status_ticks > 0) {
        state.game_status_ticks -= 1;
        if (state.game_status_ticks == 0) {
            state.game_status_message = null;
        }
    }
    state.gameplay_voice_manager.tick();
    state.native_gameplay_voice_manager.tick();
    if (state.game_phase == .level and !state.frontend_transition.blocksInput()) {
        if (state.level_runner) |*runner| {
            if (!runner.paused and !state.startupGameplayBlockActive()) {
                state.level_prompt_queue.tick();
            }
            if (state.isTutorialGameplay() and runner.score.total > state.tutorial_reference_score) {
                state.tutorial_reference_score = runner.score.total;
            }
            // PORT(verified): native `update_tip_manager` drives the active
            // `turbo-talk` clip while a tip card is up; when the tip clears,
            // the presentation controller falls back to its baseline clip. The
            // port mirrors that by diffing the prompt-queue state and dispatching
            // the correct `AnimClipId` through `dispatchCutsceneAnimation`,
            // keeping the renderer's model-swap purely a consumer of the anim slot.
            gameplay_resources.syncCutsceneAnimFromPromptQueue(.{
                .tutorial = state.gameplayTutorialContext(),
                .prompt_active = state.level_prompt_queue.active() != null,
                .click_start_active = state.gameplay_click_start_active,
            }, runner);
        }
    }

    if (state.frontend_transition.update()) |next_phase| {
        try state.enterGamePhase(next_phase);
        state.frontend_transition.completeHandoff();
        return;
    }

    if (try state.updatePendingFrontendActivation()) {
        return;
    }

    state.updateFrontendWidgetAnimations();
    if (state.game_phase == .new_game_menu and !state.frontend_transition.blocksInput()) {
        if (try state.tryLaunchNewGameReplayAttract()) return;
    }
    state.stepCompletionScreenReveal();
    if (state.game_phase == .thanks_screen) {
        state.thanks_screen_controller.step();
    }

    if (state.game_phase == .boot) {
        if (try boot_assets.advance(boot_assets.context(state))) {
            try state.enterGamePhase(.intro);
            state.frontend_transition.beginFadeIn();
        }
        return;
    }

    if (state.game_phase == .intro or state.game_phase == .credits) {
        if (state.currentTextScriptDurationTicks()) |duration_ticks| {
            if (state.game_phase_ticks >= duration_ticks and !state.frontend_transition.blocksInput()) {
                state.frontend_transition.beginFadeOut(.main_menu);
            }
        }
    }

    if (state.game_phase == .level) {
        if (try state.handleSelectedReplayFadeExit()) return;
        try gameplay_resources.syncTurboAnimation(
            &state.gameplay_resources,
            state.allocator,
            &state.resources,
            &state.animation_catalog,
            .{
                .game_phase = state.game_phase,
                .tutorial = state.gameplayTutorialContext(),
            },
        );
        if (state.current_track_preview) |*loaded_track_preview| {
            if (state.level_runner) |*runner| {
                const previous_runner = runner.*;
                const previous_active_level_segment_index = state.active_level_segment_index;
                const startup_block_active = state.startupGameplayBlockActive();
                if (!startup_block_active and !state.tutorialPromptBlocksGameplay()) {
                    runner.stepWithReplay(
                        loaded_track_preview,
                        effective_runner_input,
                        selected_replay.directiveForRunner(state, runner),
                        @floatCast(state.simulation_clock.step_seconds),
                    );
                    if (state.selected_level_record_source == null and
                        runner.replay_sample_index > previous_runner.replay_sample_index)
                    {
                        try state.captureReplayFrame(loaded_track_preview, runner.*, effective_runner_input);
                    }
                    if (runner.consumeReplayFadeRequest()) {
                        state.selected_replay_fade_exit_pending = true;
                        if (state.frontend_transition.state == .idle) {
                            state.frontend_transition.beginOverlayFadeOut();
                        }
                        return;
                    }
                    updateGameplayRunnerPresentation(state, previous_runner, runner.*);
                    audio.playGameplayRunnerAudio(state, previous_runner, runner.*, loaded_track_preview, effective_runner_input);
                    state.gameplay_effects.spawnRunnerEffects(previous_runner, runner.*, loaded_track_preview);
                    state.updateRunnerTimeTrialGhost(runner, previous_runner.replay_sample_index);
                } else {
                    state.refreshRunnerForStartupBlock(
                        runner,
                        loaded_track_preview,
                        @floatCast(state.simulation_clock.step_seconds),
                    );
                    state.updateRunnerTimeTrialGhost(runner, runner.replay_sample_index);
                }
                state.updateSubgameCamera(runner);
                try state.syncActiveLevelSegment();
                try state.dispatchCurrentRunnerRowMessage(
                    previous_active_level_segment_index,
                    previous_runner.currentRowMessageToken(),
                    false,
                );
            }
        }
        state.gameplay_effects.update();
        if (state.gameplay_resources.turbo_animation) |*animation| {
            try animation.step(state.simulation_clock.step_seconds);
        }
        if (state.level_runner) |*runner| {
            switch (runner.consumeHandoff()) {
                .none => {},
                .completion_screen_init => {
                    audio.playGameplayEffect(state, state.gameplay_resources.sound_fx.completion_init);
                    try state.beginCompletedRunOverlay();
                    return;
                },
                .completion_finalize => {
                    try state.finalizeCompletedRunScreen();
                    return;
                },
                .respawn => {
                    try state.beginRespawnRun();
                    return;
                },
                .final_loss => |cause| {
                    try state.beginFailedRun(cause);
                    return;
                },
            }
        }
    }
}

fn updateGameplayRunnerPresentation(state: anytype, previous: gameplay.Runner, current: gameplay.Runner) void {
    state.gameplay_jetpack_visual_state.tick();
    state.gameplay_weapon_visual_state.tick();
    state.gameplay_jetpack_visual_state.noteActiveChange(
        gameplay_presentation.nativeJetpackVisualPresentationActive(previous.jetpack.thrust_visual_active),
        gameplay_presentation.nativeJetpackVisualPresentationActive(current.jetpack.thrust_visual_active),
    );
    state.gameplay_weapon_visual_state.noteWeaponChannelChange(previous.presentation.movement_flags, current.presentation.movement_flags);
    if (previous.presentation.shot_cooldown_ticks == 0 and current.presentation.shot_cooldown_ticks > 0) {
        state.gameplay_weapon_visual_state.noteFire(current.presentation.movement_flags);
    }
}
