const std = @import("std");

const app = @import("../app.zig");
const frontend = @import("../frontend.zig");
const gameplay = @import("../gameplay.zig");
const gameplay_art = @import("../gameplay_art.zig");
const level = @import("../level.zig");
const object = @import("../object.zig");
const resource_store = @import("../resource_store.zig");
const x2 = @import("../x2.zig");
const xanim = @import("../xanim.zig");
const gameplay_assets = @import("assets.zig");

const default_model_path = app.default_model_path;

pub const State = struct {
    turbo_model: ?x2.Uploaded = null,
    turbo_animation: ?xanim.Player = null,
    turbo_model_path: ?[]const u8 = null,
    barrier_object: ?object.LoadedObject = null,
    lazer_object: ?object.LoadedObject = null,
    vapour_lazer_object: ?object.LoadedObject = null,
    salt_model: ?x2.Uploaded = null,
    wall2_pillar_models: [gameplay_assets.gameplay_wall2_pillar_model_paths.len]?x2.Uploaded =
        [_]?x2.Uploaded{null} ** gameplay_assets.gameplay_wall2_pillar_model_paths.len,
    blaster_top_models: gameplay_art.WeaponModelSet = .{},
    blaster_left_models: gameplay_art.WeaponModelSet = .{},
    blaster_right_models: gameplay_art.WeaponModelSet = .{},
    laser_left_models: gameplay_art.WeaponModelSet = .{},
    laser_right_models: gameplay_art.WeaponModelSet = .{},
    rocket_launcher_models: gameplay_art.WeaponModelSet = .{},
    jetpack_thrust_models: gameplay_art.JetpackModelSet = .{},
    rocket_model: ?x2.Uploaded = null,
    post_office_stop_model: ?x2.Uploaded = null,
    invincible_models: gameplay_art.InvincibleModelSet = .{},
    sprites: gameplay_art.SpriteArt = .{},
    sound_fx: gameplay_art.SoundFx = .{},
};

pub const TutorialContext = struct {
    active_frontend_mode: ?frontend.FrontendLevelMode,
    runner: ?*const gameplay.Runner,
    current_level: ?*const level.Definition,
};

pub const TurboSyncContext = struct {
    game_phase: frontend.GamePhase,
    tutorial: TutorialContext,
};

pub const PromptCutsceneContext = struct {
    tutorial: TutorialContext,
    prompt_active: bool,
    click_start_active: bool,
};

pub fn unloadTurbo(state: *State) void {
    if (state.turbo_animation) |*animation| {
        animation.deinit();
        state.turbo_animation = null;
    }
    if (state.turbo_model) |*model| {
        model.deinit();
        state.turbo_model = null;
    }
    state.turbo_model_path = null;
}

pub fn unloadBarrier(state: *State) void {
    if (state.barrier_object) |*loaded_object| {
        loaded_object.deinit();
        state.barrier_object = null;
    }
}

pub fn unloadLazer(state: *State) void {
    if (state.lazer_object) |*loaded_object| {
        loaded_object.deinit();
        state.lazer_object = null;
    }
    if (state.vapour_lazer_object) |*loaded_object| {
        loaded_object.deinit();
        state.vapour_lazer_object = null;
    }
}

pub fn unloadSalt(state: *State) void {
    if (state.salt_model) |*model| {
        model.deinit();
        state.salt_model = null;
    }
}

pub fn unloadActorModels(state: *State) void {
    for (&state.wall2_pillar_models) |*model_slot| {
        if (model_slot.*) |*model| {
            model.deinit();
            model_slot.* = null;
        }
    }
    state.blaster_top_models.unload();
    state.blaster_left_models.unload();
    state.blaster_right_models.unload();
    state.laser_left_models.unload();
    state.laser_right_models.unload();
    state.rocket_launcher_models.unload();
    state.jetpack_thrust_models.unload();
    if (state.rocket_model) |*model| {
        model.deinit();
        state.rocket_model = null;
    }
    if (state.post_office_stop_model) |*model| {
        model.deinit();
        state.post_office_stop_model = null;
    }
    state.invincible_models.unload();
}

pub fn unloadSprites(state: *State) void {
    state.sprites.unload();
}

pub fn unloadSoundFx(state: *State) void {
    state.sound_fx.unload();
}

pub fn unloadStaticResources(state: *State) void {
    unloadTurbo(state);
    unloadBarrier(state);
    unloadLazer(state);
    unloadSalt(state);
    unloadActorModels(state);
    unloadSprites(state);
    unloadSoundFx(state);
}

pub fn reloadTurbo(
    state: *State,
    allocator: std.mem.Allocator,
    store: *resource_store.Store,
    animation_catalog: *const xanim.Catalog,
) !void {
    try reloadTurboForPath(state, allocator, store, animation_catalog, default_model_path);
}

pub fn reloadTurboForPath(
    state: *State,
    allocator: std.mem.Allocator,
    store: *resource_store.Store,
    animation_catalog: *const xanim.Catalog,
    model_path: []const u8,
) !void {
    unloadTurbo(state);

    const entry_index = store.catalog.findModelIndex(model_path) orelse return;
    const entry = store.catalog.model_entries[entry_index];
    state.turbo_model_path = entry.path;

    if (animation_catalog.findClipIndexForModelPath(entry.path)) |clip_index| {
        const clip = &animation_catalog.clips[clip_index];
        if (clip.frames.len > 1) {
            state.turbo_animation = try xanim.Player.load(
                allocator,
                &store.catalog,
                clip,
                true,
                xanim.frameNumberFromPath(entry.path),
            );
            try state.turbo_animation.?.rendered.enableToonOutline();
            return;
        }
    }

    state.turbo_model = try store.model(entry.path, .{ .toon_outline = true });
}

pub fn syncTurboAnimation(
    state: *State,
    allocator: std.mem.Allocator,
    store: *resource_store.Store,
    animation_catalog: *const xanim.Catalog,
    context: TurboSyncContext,
) !void {
    if (context.game_phase != .level) return;
    if (!isTutorialGameplay(context.tutorial)) return;

    // PORT(verified): native `dispatch_cutscene_animation`
    // (`artifacts/ida/functions/00444600-dispatch_cutscene_animation.c:6`)
    // stores the active clip id on the player-side presentation
    // controller. The Zig port folds that onto `Runner.cutscene.anim`,
    // so the renderer maps the active `AnimClipId` to the shipped
    // `X/TURBO-*-000.X2` first frame. The tutorial tip overlay still
    // wins the dispatch implicitly: the tip prompt callsite dispatches
    // `.talk` so the clip latches without the renderer keeping its
    // own separate "is tip active" check.
    const runner = context.tutorial.runner orelse return;
    const desired_family = runner.cutscene.anim.active.familyKey() orelse return;
    const desired_model_path = firstClipModelPathFromFamily(store, animation_catalog, desired_family) orelse return;

    if (state.turbo_model_path) |current_path| {
        if (std.ascii.eqlIgnoreCase(current_path, desired_model_path)) return;
    }
    try reloadTurboForPath(state, allocator, store, animation_catalog, desired_model_path);
}

pub fn syncCutsceneAnimFromPromptQueue(context: PromptCutsceneContext, runner: *gameplay.Runner) void {
    if (!isTutorialGameplay(context.tutorial)) return;
    const desired: gameplay.AnimClipId = if (context.prompt_active and !context.click_start_active)
        .talk
    else
        .move;
    if (runner.cutscene.anim.active == desired) return;
    runner.dispatchCutsceneAnimation(desired, true, null);
}

pub fn loadBarrier(state: *State, store: *resource_store.Store) !void {
    unloadBarrier(state);

    if (store.catalog.findObjectIndex(gameplay_assets.gameplay_barrier_object_path) != null) {
        state.barrier_object = try store.object(gameplay_assets.gameplay_barrier_object_path, .{});
    }
}

pub fn loadLazer(state: *State, store: *resource_store.Store) !void {
    unloadLazer(state);

    state.lazer_object = try store.object(gameplay_assets.gameplay_lazer_object_path, .{});
    state.vapour_lazer_object = try store.object(gameplay_assets.gameplay_vapour_lazer_object_path, .{});
}

pub fn loadSalt(state: *State, store: *resource_store.Store) !void {
    unloadSalt(state);

    state.salt_model = try store.model(gameplay_assets.gameplay_salt_model_path, .{});
}

pub fn loadActorModels(state: *State, store: *resource_store.Store) !void {
    unloadActorModels(state);

    for (gameplay_assets.gameplay_wall2_pillar_model_paths, 0..) |model_path, index| {
        if (store.catalog.findModelIndex(model_path) != null) {
            state.wall2_pillar_models[index] = try store.model(model_path, .{});
        }
    }

    try gameplay_art.loadWeaponModelSet(
        store,
        &state.blaster_top_models,
        gameplay_assets.gameplay_blaster_top_model_path,
        &gameplay_assets.gameplay_blaster_top_draw_model_paths,
        gameplay_assets.gameplay_blaster_top_fire_model_path,
    );
    try gameplay_art.loadWeaponModelSet(
        store,
        &state.blaster_left_models,
        gameplay_assets.gameplay_blaster_left_model_path,
        &gameplay_assets.gameplay_blaster_left_draw_model_paths,
        null,
    );
    try gameplay_art.loadWeaponModelSet(
        store,
        &state.blaster_right_models,
        gameplay_assets.gameplay_blaster_right_model_path,
        &gameplay_assets.gameplay_blaster_right_draw_model_paths,
        null,
    );
    try gameplay_art.loadWeaponModelSet(
        store,
        &state.laser_left_models,
        gameplay_assets.gameplay_laser_left_model_path,
        &gameplay_assets.gameplay_laser_left_draw_model_paths,
        null,
    );
    try gameplay_art.loadWeaponModelSet(
        store,
        &state.laser_right_models,
        gameplay_assets.gameplay_laser_right_model_path,
        &gameplay_assets.gameplay_laser_right_draw_model_paths,
        null,
    );
    try gameplay_art.loadWeaponModelSet(
        store,
        &state.rocket_launcher_models,
        gameplay_assets.gameplay_rocket_launcher_model_path,
        &gameplay_assets.gameplay_rocket_launcher_draw_model_paths,
        null,
    );
    for (gameplay_assets.gameplay_jetpack_thrust_model_paths, 0..) |path, index| {
        if (store.catalog.findModelIndex(path) != null) {
            state.jetpack_thrust_models.frames[index] = try store.model(path, .{ .toon_outline = true });
        }
    }
    state.rocket_model = try store.model(gameplay_assets.gameplay_rocket_model_path, .{});
    if (store.catalog.findModelIndex(gameplay_assets.gameplay_post_office_stop_model_path) != null) {
        state.post_office_stop_model = try store.model(gameplay_assets.gameplay_post_office_stop_model_path, .{});
    }
    for (gameplay_assets.gameplay_invincible_model_paths, 0..) |path, index| {
        if (store.catalog.findModelIndex(path) != null) {
            state.invincible_models.frames[index] = try store.model(path, .{});
        }
    }
}

pub fn loadStaticResources(state: *State, store: *resource_store.Store) !void {
    try loadBarrier(state, store);
    try loadLazer(state, store);
    try loadSalt(state, store);
    try loadActorModels(state, store);
}

pub fn activeTurbo(state: *const State) ?*const x2.Uploaded {
    if (state.turbo_animation) |*animation| {
        return &animation.rendered;
    }
    if (state.turbo_model) |*model| {
        return model;
    }
    return null;
}

fn firstClipModelPathFromFamily(
    store: *const resource_store.Store,
    animation_catalog: *const xanim.Catalog,
    family_key: []const u8,
) ?[]const u8 {
    for (animation_catalog.clips) |*clip| {
        if (!std.ascii.eqlIgnoreCase(clip.family_key, family_key)) continue;
        if (clip.frames.len == 0) continue;
        const entry = store.catalog.model_entries[clip.frames[0].entry_index];
        return entry.path;
    }
    return null;
}

fn isTutorialGameplay(context: TutorialContext) bool {
    if (context.active_frontend_mode == .tutorial) return true;
    if (context.runner) |runner| {
        if (runner.session_mode == .tutorial) return true;
    }
    const loaded_level = context.current_level orelse return false;
    return std.mem.eql(u8, loaded_level.source_path, "LEVELS/TUTORIAL.TXT");
}
