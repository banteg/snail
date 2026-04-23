const std = @import("std");
const app = @import("../app.zig");
const gameplay = @import("../gameplay.zig");
const gameplay_art = @import("../gameplay_art.zig");
const gameplay_assets = @import("assets.zig");
const x2 = @import("../x2.zig");
const xanim = @import("../xanim.zig");

const default_model_path = app.default_model_path;

pub fn unloadTurbo(state: anytype) void {
    if (state.current_gameplay_turbo_animation) |*animation| {
        animation.deinit();
        state.current_gameplay_turbo_animation = null;
    }
    if (state.current_gameplay_turbo_model) |*model| {
        model.deinit();
        state.current_gameplay_turbo_model = null;
    }
    state.current_gameplay_turbo_model_path = null;
}

pub fn unloadBarrier(state: anytype) void {
    if (state.current_gameplay_barrier_object) |*loaded_object| {
        loaded_object.deinit();
        state.current_gameplay_barrier_object = null;
    }
}

pub fn unloadLazer(state: anytype) void {
    if (state.current_gameplay_lazer_object) |*loaded_object| {
        loaded_object.deinit();
        state.current_gameplay_lazer_object = null;
    }
    if (state.current_gameplay_vapour_lazer_object) |*loaded_object| {
        loaded_object.deinit();
        state.current_gameplay_vapour_lazer_object = null;
    }
}

pub fn unloadSalt(state: anytype) void {
    if (state.current_gameplay_salt_model) |*model| {
        model.deinit();
        state.current_gameplay_salt_model = null;
    }
}

pub fn unloadActorModels(state: anytype) void {
    if (state.current_gameplay_turret_model) |*model| {
        model.deinit();
        state.current_gameplay_turret_model = null;
    }
    state.current_gameplay_blaster_top_models.unload();
    state.current_gameplay_blaster_left_models.unload();
    state.current_gameplay_blaster_right_models.unload();
    state.current_gameplay_laser_left_models.unload();
    state.current_gameplay_laser_right_models.unload();
    state.current_gameplay_rocket_launcher_models.unload();
    state.current_gameplay_jetpack_thrust_models.unload();
    if (state.current_gameplay_rocket_model) |*model| {
        model.deinit();
        state.current_gameplay_rocket_model = null;
    }
    state.current_gameplay_invincible_models.unload();
    resetPresentationState(state);
}

pub fn resetPresentationState(state: anytype) void {
    state.gameplay_jetpack_visual_state = .{};
    state.gameplay_weapon_visual_state = .{};
}

pub fn unloadSprites(state: anytype) void {
    state.current_gameplay_sprites.unload();
}

pub fn unloadSoundFx(state: anytype) void {
    state.current_gameplay_sound_fx.unload();
}

pub fn reloadTurbo(state: anytype) !void {
    try reloadTurboForPath(state, default_model_path);
}

pub fn reloadTurboForPath(state: anytype, model_path: []const u8) !void {
    unloadTurbo(state);

    const entry_index = state.resources.catalog.findModelIndex(model_path) orelse return;
    const entry = state.resources.catalog.model_entries[entry_index];
    state.current_gameplay_turbo_model_path = entry.path;

    if (state.animation_catalog.findClipIndexForModelPath(entry.path)) |clip_index| {
        const clip = &state.animation_catalog.clips[clip_index];
        if (clip.frames.len > 1) {
            state.current_gameplay_turbo_animation = try xanim.Player.load(
                state.allocator,
                &state.resources.catalog,
                clip,
                true,
                xanim.frameNumberFromPath(entry.path),
            );
            try state.current_gameplay_turbo_animation.?.rendered.enableToonOutline();
            return;
        }
    }

    state.current_gameplay_turbo_model = try state.resources.model(entry.path, .{ .toon_outline = true });
}

pub fn syncTurboAnimation(state: anytype) !void {
    if (state.game_phase != .level) return;
    if (!isTutorialGameplay(state)) return;

    // PORT(verified): native `dispatch_cutscene_animation`
    // (`artifacts/ida/functions/00444600-dispatch_cutscene_animation.c:6`)
    // stores the active clip id on the player-side presentation
    // controller. The Zig port folds that onto `Runner.cutscene_anim`,
    // so the renderer maps the active `AnimClipId` to the shipped
    // `X/TURBO-*-000.X2` first frame. The tutorial tip overlay still
    // wins the dispatch implicitly: the tip prompt callsite dispatches
    // `.talk` so the clip latches without the renderer keeping its
    // own separate "is tip active" check.
    const runner = currentRunnerConst(state) orelse return;
    const desired_family = runner.cutscene_anim.active.familyKey() orelse return;
    const desired_model_path = firstClipModelPathFromFamily(state, desired_family) orelse return;

    if (state.current_gameplay_turbo_model_path) |current_path| {
        if (std.ascii.eqlIgnoreCase(current_path, desired_model_path)) return;
    }
    try reloadTurboForPath(state, desired_model_path);
}

pub fn syncCutsceneAnimFromPromptQueue(state: anytype, runner: *gameplay.Runner) void {
    if (!isTutorialGameplay(state)) return;
    const desired: gameplay.AnimClipId = if (state.level_prompt_queue.active() != null and !state.gameplay_click_start_active)
        .talk
    else
        .move;
    if (runner.cutscene_anim.active == desired) return;
    runner.dispatchCutsceneAnimation(desired, true, null);
}

pub fn loadBarrier(state: anytype) !void {
    unloadBarrier(state);

    if (state.resources.catalog.findObjectIndex(gameplay_assets.gameplay_barrier_object_path) != null) {
        state.current_gameplay_barrier_object = try state.resources.object(gameplay_assets.gameplay_barrier_object_path, .{});
    }
}

pub fn loadLazer(state: anytype) !void {
    unloadLazer(state);

    if (state.resources.catalog.findObjectIndex(gameplay_assets.gameplay_lazer_object_path) != null) {
        state.current_gameplay_lazer_object = try state.resources.object(gameplay_assets.gameplay_lazer_object_path, .{});
    }

    if (state.resources.catalog.findObjectIndex(gameplay_assets.gameplay_vapour_lazer_object_path) != null) {
        state.current_gameplay_vapour_lazer_object = try state.resources.object(gameplay_assets.gameplay_vapour_lazer_object_path, .{});
    }
}

pub fn loadSalt(state: anytype) !void {
    unloadSalt(state);

    if (state.resources.catalog.findModelIndex(gameplay_assets.gameplay_salt_model_path) != null) {
        state.current_gameplay_salt_model = try state.resources.model(gameplay_assets.gameplay_salt_model_path, .{});
    }
}

pub fn loadActorModels(state: anytype) !void {
    unloadActorModels(state);

    if (state.resources.catalog.findModelIndex(gameplay_assets.gameplay_turret_model_path) != null) {
        state.current_gameplay_turret_model = try state.resources.model(gameplay_assets.gameplay_turret_model_path, .{});
    }

    try gameplay_art.loadWeaponModelSet(
        &state.resources,
        &state.current_gameplay_blaster_top_models,
        gameplay_assets.gameplay_blaster_top_model_path,
        &gameplay_assets.gameplay_blaster_top_draw_model_paths,
        gameplay_assets.gameplay_blaster_top_fire_model_path,
    );
    try gameplay_art.loadWeaponModelSet(
        &state.resources,
        &state.current_gameplay_blaster_left_models,
        gameplay_assets.gameplay_blaster_left_model_path,
        &gameplay_assets.gameplay_blaster_left_draw_model_paths,
        null,
    );
    try gameplay_art.loadWeaponModelSet(
        &state.resources,
        &state.current_gameplay_blaster_right_models,
        gameplay_assets.gameplay_blaster_right_model_path,
        &gameplay_assets.gameplay_blaster_right_draw_model_paths,
        null,
    );
    try gameplay_art.loadWeaponModelSet(
        &state.resources,
        &state.current_gameplay_laser_left_models,
        gameplay_assets.gameplay_laser_left_model_path,
        &gameplay_assets.gameplay_laser_left_draw_model_paths,
        null,
    );
    try gameplay_art.loadWeaponModelSet(
        &state.resources,
        &state.current_gameplay_laser_right_models,
        gameplay_assets.gameplay_laser_right_model_path,
        &gameplay_assets.gameplay_laser_right_draw_model_paths,
        null,
    );
    try gameplay_art.loadWeaponModelSet(
        &state.resources,
        &state.current_gameplay_rocket_launcher_models,
        gameplay_assets.gameplay_rocket_launcher_model_path,
        &gameplay_assets.gameplay_rocket_launcher_draw_model_paths,
        null,
    );
    for (gameplay_assets.gameplay_jetpack_thrust_model_paths, 0..) |path, index| {
        if (state.resources.catalog.findModelIndex(path) != null) {
            state.current_gameplay_jetpack_thrust_models.frames[index] = try state.resources.model(path, .{ .toon_outline = true });
        }
    }
    if (state.resources.catalog.findModelIndex(gameplay_assets.gameplay_rocket_model_path) != null) {
        state.current_gameplay_rocket_model = try state.resources.model(gameplay_assets.gameplay_rocket_model_path, .{});
    }
    for (gameplay_assets.gameplay_invincible_model_paths, 0..) |path, index| {
        if (state.resources.catalog.findModelIndex(path) != null) {
            state.current_gameplay_invincible_models.frames[index] = try state.resources.model(path, .{});
        }
    }
}

pub fn loadStaticResources(state: anytype) !void {
    try loadBarrier(state);
    try loadLazer(state);
    try loadSalt(state);
    try loadActorModels(state);
}

pub fn activeTurbo(state: anytype) ?*const x2.Uploaded {
    if (state.current_gameplay_turbo_animation) |*animation| {
        return &animation.rendered;
    }
    if (state.current_gameplay_turbo_model) |*model| {
        return model;
    }
    return null;
}

fn currentRunnerConst(state: anytype) ?*const gameplay.Runner {
    if (state.level_runner) |*runner| return runner;
    return null;
}

fn firstClipModelPathFromFamily(state: anytype, family_key: []const u8) ?[]const u8 {
    for (state.animation_catalog.clips) |*clip| {
        if (!std.ascii.eqlIgnoreCase(clip.family_key, family_key)) continue;
        if (clip.frames.len == 0) continue;
        const entry = state.resources.catalog.model_entries[clip.frames[0].entry_index];
        return entry.path;
    }
    return null;
}

fn isTutorialGameplay(state: anytype) bool {
    if (state.active_frontend_mode == .tutorial) return true;
    if (state.level_runner) |runner| {
        if (runner.session_mode == .tutorial) return true;
    }
    const loaded_level = state.current_level orelse return false;
    return std.mem.eql(u8, loaded_level.source_path, "LEVELS/TUTORIAL.TXT");
}
