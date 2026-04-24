const std = @import("std");
const rl = @import("raylib");
const app = @import("app.zig");
const audio = @import("app/audio.zig");
const frontend_flow = @import("app/frontend_flow.zig");
const frontend_input = @import("app/frontend_input.zig");
const frontend_mouse = @import("app/frontend_mouse.zig");
const level_loader = @import("app/level_loader.zig");
const render_phase = @import("app/render_phase.zig");
const return_flow = @import("app/return_flow.zig");
const route_map_state = @import("app/route_map_state.zig");
const run_result = @import("app/run_result.zig");
const screenshots = @import("app/screenshots.zig");
const selected_replay = @import("app/selected_replay.zig");
const subgame_camera = @import("app/subgame_camera.zig");
const frontend_art = @import("frontend/art.zig");
const gameplay_resources = @import("gameplay/resources.zig");
const ui = @import("ui.zig");
const assets = @import("assets.zig");
const background = @import("background.zig");
const config = @import("config.zig");
const debug_browser = @import("debug/browser.zig");
const frontend = @import("frontend.zig");
const frontend_activation = @import("frontend/activation.zig");
const frontend_bridge = @import("frontend/bridge.zig");
const frontend_challenge_setup_menu = @import("frontend/challenge_setup_menu.zig");
const frontend_completion_screen = @import("frontend/completion_screen.zig");
const frontend_exit_prompt = @import("frontend/exit_prompt.zig");
const frontend_help = @import("frontend/help.zig");
const frontend_high_score_screen = @import("frontend/high_score_screen.zig");
const frontend_options_menu = @import("frontend/options_menu.zig");
const frontend_pause_menu = @import("frontend/pause_menu.zig");
const frontend_route_map = @import("frontend/route_map.zig");
const frontend_render = @import("frontend/render.zig");
const frontend_screens = @import("frontend/screens.zig");
const frontend_thanks = @import("frontend/thanks.zig");
const frontend_widget = @import("frontend/widget.zig");
const galaxy = @import("galaxy.zig");
const game_font = @import("game_font.zig");
const gameplay_art = @import("gameplay_art.zig");
const gameplay_audio_catalog = @import("gameplay/audio_catalog.zig");
const gameplay_effects = @import("gameplay/effects.zig");
const gameplay = @import("gameplay.zig");
const gameplay_assets = @import("gameplay/assets.zig");
const gameplay_hud = @import("gameplay/hud.zig");
const gameplay_presentation = @import("gameplay/presentation.zig");
const gameplay_prompt_overlay = @import("gameplay/prompt_overlay.zig");
const gameplay_render_policy = @import("gameplay/render_policy.zig");
const gameplay_runtime_entities = @import("gameplay/runtime_entities.zig");
const gameplay_voice = @import("gameplay/voice.zig");
const high_score = @import("high_score.zig");
const intro = @import("intro.zig");
const level_prompt = @import("level_prompt.zig");
const sim = @import("sim.zig");
const track = @import("track.zig");
const track_render = @import("track_render.zig");
const loading_screen = @import("loading_screen.zig");
const object = @import("object.zig");
const resource_store = @import("resource_store.zig");
const segment = @import("segment.zig");
const level = @import("level.zig");
const runtime_state = @import("runtime_state.zig");
const x2 = @import("x2.zig");
const xanim = @import("xanim.zig");

const io = std.Options.debug_io;

const default_archive_path = app.default_archive_path;
const default_screenshot_dir = app.default_screenshot_dir;
const intro_background_path = app.intro_background_path;
const main_menu_background_path = app.main_menu_background_path;
const help_background_path = app.help_background_path;
const route_map_background_path = app.route_map_background_path;
const thanks_screen_background_path = app.thanks_screen_background_path;
const frontend_cursor_texture_path = app.frontend_cursor_texture_path;
const galaxy_names_path = app.galaxy_names_path;
const intro_script_path = app.intro_script_path;
const credits_script_path = app.credits_script_path;
const intro_music_path = app.intro_music_path;
const default_texture_path = app.default_texture_path;
const default_audio_path = app.default_audio_path;
const default_model_path = app.default_model_path;
const default_object_path = app.default_object_path;
const default_level_path = app.default_level_path;
const simulation_step_seconds = 1.0 / 60.0;
const status_message_duration_ticks: u32 = 180;
const Options = app.Options;
const AppCommand = app.AppCommand;
const AutoScreenshot = app.AutoScreenshot;
const MouseLocalOverride = app.MouseLocalOverride;
const WindowSize = app.WindowSize;
const parseArgs = app.parseArgs;
const defaultWindowSizeForCommand = app.defaultWindowSizeForCommand;

const BootTask = frontend.BootTask;
const boot_tasks = frontend.boot_tasks;
const GamePhase = frontend.GamePhase;
const FrontendTransition = frontend.FrontendTransition;
const MainMenuItem = frontend.MainMenuItem;
const main_menu_items = frontend.main_menu_items;
const NewGameMenuItem = frontend.NewGameMenuItem;
const new_game_menu_items = frontend.new_game_menu_items;
const FrontendLevelMode = frontend.FrontendLevelMode;
const OptionsMenuItem = frontend.OptionsMenuItem;
const options_menu_items = frontend.options_menu_items;
const PauseMenuItem = frontend.PauseMenuItem;
const RouteMenuAction = frontend.RouteMenuAction;
const frontendRouteModeLabel = frontend.frontendRouteModeLabel;
const routeMenuActionLabel = frontend.routeMenuActionLabel;
const routeMenuHint = frontend.routeMenuHint;
const frontendLevelPath = frontend.frontendLevelPath;

const MenuPanels = ui.MenuPanels;
const VirtualLayout = ui.VirtualLayout;
const FrontendSoundFx = frontend_art.FrontendSoundFx;
const FrontendWidgetArt = frontend_art.FrontendWidgetArt;
const RouteMapArt = frontend_art.RouteMapArt;
const SliderArt = frontend_art.SliderArt;
const GameplayInvincibleModelSet = gameplay_art.InvincibleModelSet;
const GameplayJetpackModelSet = gameplay_art.JetpackModelSet;
const GameplaySoundFx = gameplay_art.SoundFx;
const GameplaySpriteArt = gameplay_art.SpriteArt;
const GameplayWeaponModelSet = gameplay_art.WeaponModelSet;

const ScreenshotRequest = screenshots.Request;

const GameplayJetpackVisualState = gameplay_presentation.JetpackVisualState;
const GameplayWeaponVisualState = gameplay_presentation.WeaponVisualState;

fn trimRight(comptime T: type, slice: []const T, values_to_strip: []const T) []const T {
    var end = slice.len;
    while (end > 0) : (end -= 1) {
        if (std.mem.indexOfScalar(T, values_to_strip, slice[end - 1]) == null) break;
    }
    return slice[0..end];
}

fn nativeJetpackVisualPresentationActive(runner: gameplay.Runner) bool {
    return gameplay_presentation.nativeJetpackVisualPresentationActive(runner);
}

test "native gameplay voice manager enforces native mode gates" {
    var manager: gameplay_voice.NativeManager = .{};

    try std.testing.expectEqual(@as(?usize, null), manager.requestPlay(.victory, .wait_for_frequency, false, 3));
    try std.testing.expectEqual(@as(?usize, 0), manager.requestPlay(.victory, .wait_for_idle, false, 3));
    try std.testing.expectEqual(@as(?usize, null), manager.requestPlay(.victory, .wait_for_idle, false, 3));

    var tick_index: usize = 0;
    while (tick_index < 240) : (tick_index += 1) {
        manager.tick();
    }
    try std.testing.expectEqual(@as(?usize, null), manager.requestPlay(.victory, .wait_for_frequency, false, 3));

    manager.global_progress = gameplay_voice.manager_frequency_seconds;
    try std.testing.expectEqual(@as(?usize, 1), manager.requestPlay(.victory, .wait_for_frequency, false, 3));

    manager.clear();
    try std.testing.expectEqual(@as(?usize, null), manager.requestPlay(.fall, .wait_for_idle, true, 2));
    try std.testing.expectEqual(@as(?usize, 0), manager.requestPlay(.fall, .interrupt_current, true, 2));
}

test "native gameplay voice manager payload play preserves set rotation" {
    var manager: gameplay_voice.NativeManager = .{};
    manager.global_progress = gameplay_voice.manager_frequency_seconds;

    try std.testing.expectEqual(@as(?usize, 133), manager.requestPayloadPlay(.tutorial, .interrupt_current, false, 133));
    try std.testing.expectEqual(@as(?usize, null), manager.requestPlay(.tutorial, .interrupt_current, false, 18));

    var tick_index: usize = 0;
    while (tick_index < 240) : (tick_index += 1) {
        manager.tick();
    }

    try std.testing.expectEqual(@as(?usize, 0), manager.requestPlay(.tutorial, .interrupt_current, false, 18));
}

test "native global audio sample ids resolve from shipped paths" {
    try std.testing.expectEqual(@as(?usize, 16), gameplay_audio_catalog.nativeGlobalAudioSampleIndexForPath("SFX2/JETPACK.OGG"));
    try std.testing.expectEqual(@as(?usize, 25), gameplay_audio_catalog.nativeGlobalAudioSampleIndexForPath("sfx2/servo1.ogg"));
    try std.testing.expectEqual(@as(?usize, 26), gameplay_audio_catalog.nativeGlobalAudioSampleIndexForPath("SFX2/SERVO2.OGG"));
    try std.testing.expectEqual(@as(?usize, 46), gameplay_audio_catalog.nativeGlobalAudioSampleIndexForPath("SFX2/SKIDSTOP.OGG"));
    try std.testing.expectEqual(@as(?usize, 133), gameplay_audio_catalog.nativeGlobalAudioSampleIndexForPath("VOICE/TUT1.OGG"));
    try std.testing.expectEqual(@as(?usize, 150), gameplay_audio_catalog.nativeGlobalAudioSampleIndexForPath("Voice/tut18.ogg"));
    try std.testing.expectEqualStrings("VOICE/TUT1.OGG", gameplay_audio_catalog.nativeGlobalAudioSamplePath(133).?);
    try std.testing.expectEqualStrings("SFX2/SERVO2.OGG", gameplay_audio_catalog.nativeGlobalAudioSamplePath(26).?);
    try std.testing.expectEqual(@as(?[]const u8, null), gameplay_audio_catalog.nativeGlobalAudioSamplePath(999));
    try std.testing.expectEqual(@as(?usize, null), gameplay_audio_catalog.nativeGlobalAudioSampleIndexForPath("VOICE/DOES-NOT-EXIST.OGG"));
}

const max_announced_slug_voice_cells: usize = 64;

const RespawnBridgeState = run_result.RespawnBridgeState;
const RunOutcome = run_result.Outcome;

fn outerReturnTargetForCompletionOwner(owner: CompletionFlowOwner) frontend_bridge.OuterReturnTarget {
    return run_result.outerReturnTargetForCompletionOwner(owner);
}

fn completionSummary(result: PendingRunResult) frontend_completion_screen.Summary {
    return run_result.summary(result);
}

const PendingRunPersistence = run_result.Persistence;
const PendingRunResult = run_result.Result;
const StandalonePostLevelHighScoreEntry = run_result.StandalonePostLevelHighScoreEntry;
const CompletionFlowOwner = run_result.CompletionFlowOwner;

const pause_menu_button_count = frontend_pause_menu.items.len;
const frontend_canvas_width: i32 = 640;
const frontend_canvas_height: i32 = 480;

const SubgameCameraState = subgame_camera.State;

const AppState = struct {
    allocator: std.mem.Allocator,
    resources: resource_store.Store,
    animation_catalog: xanim.Catalog,
    ui_font: game_font.Loaded,
    runtime_root_path: []const u8,
    screenshot_dir: []const u8,
    credits_with_remake: bool,
    runtime_config: config.Blob,
    runtime_config_loaded_from_file: bool,
    command: AppCommand,
    window_size: WindowSize,
    audio_ready: bool,
    audio_muted: bool,
    mouse_local_override: ?MouseLocalOverride = null,
    should_exit: bool = false,
    auto_screenshot: ?AutoScreenshot = null,
    auto_screenshot_taken: bool = false,
    frame_capture_index: u32 = 0,
    pending_screenshot: ?ScreenshotRequest = null,
    start_pause_context: bool = false,
    simulation_clock: sim.FixedStepClock = sim.FixedStepClock.init(simulation_step_seconds),
    render_time_seconds: f64 = 0.0,
    gameplay_audio_variant_counter: u32 = 0,
    game_phase: GamePhase = .boot,
    game_phase_ticks: u64 = 0,
    frontend_transition: FrontendTransition = .{},
    boot_task_index: usize = 0,
    menu_index: usize = 0,
    main_menu_button_states: [main_menu_items.len]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** main_menu_items.len,
    new_game_menu_index: usize = 0,
    new_game_button_states: [new_game_menu_items.len]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** new_game_menu_items.len,
    challenge_setup_index: usize = 0,
    challenge_setup_button_states: [frontend_challenge_setup_menu.button_count]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** frontend_challenge_setup_menu.button_count,
    options_menu_index: usize = 0,
    options_button_states: [frontend_options_menu.button_count]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** frontend_options_menu.button_count,
    pause_menu_index: usize = 0,
    pause_menu_button_states: [pause_menu_button_count]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** pause_menu_button_count,
    options_return_phase: GamePhase = .main_menu,
    help_button_states: [frontend_help.button_count]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** frontend_help.button_count,
    route_map_button_states: [frontend_route_map.button_count]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** frontend_route_map.button_count,
    high_scores_menu_index: usize = 0,
    high_scores_action_index: usize = 1,
    high_score_button_states: [frontend_high_score_screen.button_count]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** frontend_high_score_screen.button_count,
    high_score_replay_button_states: [frontend_high_score_screen.replay_button_count]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** frontend_high_score_screen.replay_button_count,
    exit_prompt_choice_index: usize = 0,
    exit_prompt_button_states: [frontend_exit_prompt.button_count]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** frontend_exit_prompt.button_count,
    exit_prompt_return_phase: GamePhase = .main_menu,
    exit_prompt_mode: frontend_exit_prompt.Mode = .quit_app,
    post_level_high_score_action_index: usize = 1,
    post_level_high_score_button_states: [frontend_high_score_screen.post_level_actions.len]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** frontend_high_score_screen.post_level_actions.len,
    post_level_high_score_name_len: usize = 0,
    post_level_high_score_name_buf: [high_score.name_capacity]u8 = [_]u8{0} ** high_score.name_capacity,
    high_score_tables: high_score.Tables,
    pending_run_result: ?PendingRunResult = null,
    completion_overlay_active: bool = false,
    preserve_completion_screen_reveal_on_enter: bool = false,
    game_status_message: ?[]const u8 = null,
    game_status_ticks: u32 = 0,
    gameplay_click_start_active: bool = false,
    seed_level_intro_cutscene: bool = false,
    subgame_camera: SubgameCameraState = .{},
    tutorial_reference_score: u32 = 0,
    gameplay_voice_manager: gameplay_voice.VoiceManager = .{},
    native_gameplay_voice_manager: gameplay_voice.NativeManager = .{},
    // Mirrors native byte `game + 0x430054` checked by
    // `apply_damage_gauge_delta` before dispatching animation id 6. No writer
    // has been recovered yet; the clear default matches normal damage entry.
    native_damage_entry_animation_blocked: bool = false,
    announced_slug_voice_cells: [max_announced_slug_voice_cells]gameplay.RowTarget = [_]gameplay.RowTarget{.{ .row = 0, .lane = 0 }} ** max_announced_slug_voice_cells,
    announced_slug_voice_cell_count: usize = 0,
    active_level_segment_index: ?usize = null,
    level_prompt_queue: level_prompt.Queue = .{},
    mouse_level_lane_target: ?f32 = null,
    frontend_route_mode: ?FrontendLevelMode = null,
    route_map_screen_mode: frontend_bridge.RouteMapScreenMode = .normal,
    frontend_route_index: usize = 0,
    start_route_index_override: ?usize = null,
    route_menu_action_index: usize = 0,
    route_map_open_index: ?usize = null,
    route_map_hover_state: frontend_route_map.HoverState = .none,
    route_map_hovered_index: ?usize = null,
    active_frontend_mode: ?FrontendLevelMode = null,
    active_frontend_level_index: usize = 0,
    current_outer_owner: frontend_bridge.OuterOwnerState = frontend_bridge.outerOwnerStateMainMenu(),
    saved_outer_owner: frontend_bridge.OuterOwnerState = frontend_bridge.outerOwnerStateMainMenu(),
    saved_replay_return_outer_owner: ?frontend_bridge.SavedReplayReturnOuterOwner = null,
    subgame_rebuild_selector: u8 = 0,
    pending_respawn_bridge_state: ?RespawnBridgeState = null,
    high_score_screen_owner: frontend_high_score_screen.Owner = .{ .main_menu_browse = .postal },
    post_level_high_score_return_owner: ?frontend_bridge.OuterOwnerState = null,
    post_level_high_score_return_opcode: frontend_bridge.OuterBridgeOpcode = .destroy_return,
    math_random_state: u32 = 1,
    current_runtime_build_seed: u32 = 0,
    current_runtime_build_seed_level_index: ?usize = null,
    current_runtime_build_seed_mode: ?FrontendLevelMode = null,
    selected_level_record_override: ?frontend_bridge.SelectedLevelRecordOverride = null,
    selected_level_record_source: ?frontend_bridge.SelectedLevelRecordSource = null,
    selected_level_record_persistent: bool = false,
    selected_level_record_outer_return_target: ?frontend_bridge.OuterReturnTarget = null,
    selected_replay_cache: ?high_score.DecodedReplay = null,
    selected_replay_fade_exit_pending: bool = false,
    route_map_route_highlight_alpha: [galaxy.map_route_count + 1]f32 = [_]f32{0.0} ** (galaxy.map_route_count + 1),
    route_map_route_highlight_target: [galaxy.map_route_count + 1]f32 = [_]f32{0.0} ** (galaxy.map_route_count + 1),
    mode: debug_browser.Mode = .textures,
    debug_light_streak_view: debug_browser.LightStreakView = .{},
    model_flip_v: bool = true,
    object_flip_v: bool = true,
    texture_index: usize,
    audio_index: usize,
    model_index: usize,
    object_index: usize,
    level_index: usize,
    segment_index: usize = 0,
    segment_render_mode: debug_browser.SegmentRenderMode = .game,
    segment_show_overlay: bool = false,
    segment_show_grid: bool = false,
    segment_show_attachments: bool = true,
    segment_track_set_index: u8 = 0,
    level_segment_index: usize = 0,
    current_texture: ?assets.LoadedTexture = null,
    frontend_canvas: ?rl.RenderTexture2D = null,
    frontend_cursor_texture: ?assets.LoadedTexture = null,
    frontend_widget_art: FrontendWidgetArt = .{},
    frontend_sound_fx: FrontendSoundFx = .{},
    hovered_frontend_target: ?frontend_activation.HoverTarget = null,
    keyboard_frontend_focus_visible: bool = false,
    pending_frontend_activation: ?frontend_activation.QueuedActivation = null,
    completion_continue_button_state: frontend_widget.TextButtonState = .{},
    completion_screen_reveal_progress: f32 = 0.0,
    thanks_screen_controller: frontend_thanks.Controller = .{},
    slider_art: SliderArt = .{},
    route_map_art: RouteMapArt = .{},
    challenge_setup_speed_display_value: f32 = 0.0,
    challenge_setup_difficulty_display_value: f32 = 0.0,
    options_sound_display_value: f32 = 0.0,
    options_music_display_value: f32 = 0.0,
    current_sound: assets.SoundSlot = .{},
    current_voice_sound: assets.SoundSlot = .{},
    current_music: ?assets.LoadedMusic = null,
    current_model: ?x2.Uploaded = null,
    current_animation: ?xanim.Player = null,
    current_object: ?object.LoadedObject = null,
    current_level: ?level.Definition = null,
    current_segment: ?segment.Definition = null,
    current_track_preview: ?track.LoadedLevelPreview = null,
    current_game_track_scene: ?track_render.Scene = null,
    current_gameplay_turbo_model: ?x2.Uploaded = null,
    current_gameplay_turbo_animation: ?xanim.Player = null,
    current_gameplay_turbo_model_path: ?[]const u8 = null,
    current_gameplay_barrier_object: ?object.LoadedObject = null,
    current_gameplay_lazer_object: ?object.LoadedObject = null,
    current_gameplay_vapour_lazer_object: ?object.LoadedObject = null,
    current_gameplay_salt_model: ?x2.Uploaded = null,
    current_gameplay_turret_model: ?x2.Uploaded = null,
    current_gameplay_blaster_top_models: GameplayWeaponModelSet = .{},
    current_gameplay_blaster_left_models: GameplayWeaponModelSet = .{},
    current_gameplay_blaster_right_models: GameplayWeaponModelSet = .{},
    current_gameplay_laser_left_models: GameplayWeaponModelSet = .{},
    current_gameplay_laser_right_models: GameplayWeaponModelSet = .{},
    current_gameplay_rocket_launcher_models: GameplayWeaponModelSet = .{},
    current_gameplay_jetpack_thrust_models: GameplayJetpackModelSet = .{},
    current_gameplay_rocket_model: ?x2.Uploaded = null,
    current_gameplay_invincible_models: GameplayInvincibleModelSet = .{},
    gameplay_jetpack_visual_state: GameplayJetpackVisualState = .{},
    gameplay_weapon_visual_state: GameplayWeaponVisualState = .{},
    current_gameplay_sprites: GameplaySpriteArt = .{},
    gameplay_billboard_shader: ?rl.Shader = null,
    current_gameplay_sound_fx: GameplaySoundFx = .{},
    gameplay_effects: gameplay_effects.Controller = .{},
    current_standalone_segment_preview: ?track.LoadedLevelPreview = null,
    current_standalone_segment_scene: ?track_render.Scene = null,
    current_game_background: ?background.Loaded = null,
    current_game_background_runtime: ?background.Runtime = null,
    current_background_light_streak_texture: ?assets.LoadedTexture = null,
    background_light_streaks: background.LightStreakController = background.LightStreakController.init(),
    current_loading_screen: ?loading_screen.Loaded = null,
    current_text_script: ?intro.Loaded = null,
    galaxy_names: ?galaxy.Definition = null,
    frontend_route_level: ?level.Definition = null,
    preloaded_intro_background: ?background.Loaded = null,
    preloaded_main_menu_background: ?background.Loaded = null,
    preloaded_route_map_background: ?background.Loaded = null,
    preloaded_help_background: ?background.Loaded = null,
    preloaded_intro_script: ?intro.Loaded = null,
    preloaded_credits_script: ?intro.Loaded = null,
    preloaded_intro_music: ?assets.LoadedMusic = null,
    preloaded_menu_music: ?assets.LoadedMusic = null,
    level_runner: ?gameplay.Runner = null,
    pending_level_input: gameplay.RunnerInput = .{},

    fn init(allocator: std.mem.Allocator, options: Options, runtime_config_result: config.LoadResult, audio_ready: bool) !AppState {
        var resources = try resource_store.Store.init(allocator, options.archive_path, audio_ready);
        errdefer resources.deinit();
        var animation_catalog = try xanim.Catalog.load(allocator, &resources.catalog);
        errdefer animation_catalog.deinit();
        var ui_font = try game_font.Loaded.load(allocator, &resources.catalog);
        errdefer ui_font.deinit();
        const frontend_canvas = if (options.command == .game) blk: {
            const canvas = try rl.loadRenderTexture(frontend_canvas_width, frontend_canvas_height);
            rl.setTextureWrap(canvas.texture, .clamp);
            rl.setTextureFilter(canvas.texture, .bilinear);
            break :blk canvas;
        } else null;
        errdefer if (frontend_canvas) |canvas| canvas.unload();
        var frontend_cursor_texture = try resources.texture(frontend_cursor_texture_path);
        errdefer frontend_cursor_texture.unload();
        var frontend_widget_art = try frontend_art.loadFrontendWidgetArt(&resources);
        errdefer frontend_widget_art.unload();
        var frontend_sound_fx = try frontend_art.loadFrontendSoundFx(&resources);
        errdefer frontend_sound_fx.unload();
        var gameplay_sound_fx = try gameplay_art.loadSoundFx(&resources);
        errdefer gameplay_sound_fx.unload();
        var gameplay_sprites = try gameplay_art.loadSpriteArt(&resources);
        errdefer gameplay_sprites.unload();
        var slider_art = try frontend_art.loadSliderArt(&resources);
        errdefer slider_art.unload();
        var route_map_art = try frontend_art.loadRouteMapArt(&resources);
        errdefer route_map_art.unload();
        var background_light_streak_texture = try resources.texture(gameplay_assets.background_light_streak_sprite_path);
        rl.setTextureFilter(background_light_streak_texture.texture, .point);
        errdefer background_light_streak_texture.unload();
        const gameplay_billboard_shader = try loadGameplayBillboardCutoutShader();
        errdefer rl.unloadShader(gameplay_billboard_shader);
        var galaxy_names: ?galaxy.Definition = try galaxy.loadByPath(allocator, &resources.catalog, galaxy_names_path);
        errdefer if (galaxy_names) |*names| names.deinit();

        const texture_index = resources.catalog.findTextureIndex(default_texture_path) orelse 0;
        const audio_index = resources.catalog.findAudioIndex(default_audio_path) orelse 0;
        const model_index = resources.catalog.findModelIndex(default_model_path) orelse 0;
        const object_index = resources.catalog.findObjectIndex(default_object_path) orelse 0;
        const level_index = resources.catalog.findLevelIndex(default_level_path) orelse 0;
        const segment_index: usize = 0;

        var state = AppState{
            .allocator = allocator,
            .resources = resources,
            .animation_catalog = animation_catalog,
            .ui_font = ui_font,
            .runtime_root_path = options.runtime_root_path,
            .screenshot_dir = options.screenshot_dir,
            .credits_with_remake = options.credits_with_remake,
            .runtime_config = runtime_config_result.blob,
            .runtime_config_loaded_from_file = runtime_config_result.loaded_from_file,
            .command = options.command,
            .window_size = options.window_size_override orelse defaultWindowSizeForCommand(options.command),
            .audio_ready = audio_ready,
            .audio_muted = options.hidden_window,
            .challenge_setup_speed_display_value = @as(f32, @floatFromInt(runtime_config_result.blob.challengeReplaySpeedValue())) * 0.01,
            .challenge_setup_difficulty_display_value = @as(f32, @floatFromInt(runtime_config_result.blob.challengeReplayDifficultyValue())) * 0.01,
            .options_sound_display_value = runtime_config_result.blob.soundVolume(),
            .options_music_display_value = runtime_config_result.blob.musicVolume(),
            .mouse_local_override = options.mouse_local_override,
            .auto_screenshot = options.auto_screenshot,
            .start_route_index_override = options.start_route_index,
            .start_pause_context = options.pause_context,
            .high_score_tables = high_score.Tables.initDefault(),
            .texture_index = texture_index,
            .audio_index = audio_index,
            .model_index = model_index,
            .object_index = object_index,
            .level_index = level_index,
            .segment_index = segment_index,
            .frontend_canvas = frontend_canvas,
            .frontend_cursor_texture = frontend_cursor_texture,
            .frontend_widget_art = frontend_widget_art,
            .frontend_sound_fx = frontend_sound_fx,
            .current_gameplay_sound_fx = gameplay_sound_fx,
            .current_gameplay_sprites = gameplay_sprites,
            .slider_art = slider_art,
            .route_map_art = route_map_art,
            .current_background_light_streak_texture = background_light_streak_texture,
            .gameplay_billboard_shader = gameplay_billboard_shader,
            .galaxy_names = galaxy_names,
        };
        errdefer state.deinit();
        galaxy_names = null;
        audio.applyAudioConfigVolumes(&state);
        if (options.command == .game) {
            try gameplay_resources.loadStaticResources(&state);
        }

        switch (options.command) {
            .debug, .smoke => {
                try debug_browser.initialize(&state);
            },
            .game => if (options.start_phase) |start_phase|
                try state.enterStartPhase(start_phase)
            else
                try state.enterGamePhase(.boot),
        }
        return state;
    }

    fn deinit(self: *AppState) void {
        audio.stopAudioPreview(self);
        self.unloadLoadingScreen();
        self.unloadGameBackground();
        self.unloadPreloadedBootAssets();
        self.clearSelectedReplayCache();
        if (self.current_background_light_streak_texture) |*texture| {
            texture.unload();
            self.current_background_light_streak_texture = null;
        }
        if (self.gameplay_billboard_shader) |shader| {
            rl.unloadShader(shader);
            self.gameplay_billboard_shader = null;
        }
        if (self.pending_screenshot) |*request| {
            request.deinit(self.allocator);
            self.pending_screenshot = null;
        }

        if (self.current_model) |*model| {
            model.deinit();
            self.current_model = null;
        }
        if (self.current_animation) |*animation| {
            animation.deinit();
            self.current_animation = null;
        }
        if (self.current_object) |*loaded_object| {
            loaded_object.deinit();
            self.current_object = null;
        }
        if (self.current_segment) |*loaded_segment| {
            loaded_segment.deinit();
            self.current_segment = null;
        }
        if (self.current_level) |*loaded_level| {
            loaded_level.deinit();
            self.current_level = null;
        }
        if (self.current_track_preview) |*loaded_track_preview| {
            loaded_track_preview.deinit();
            self.current_track_preview = null;
        }
        if (self.current_game_track_scene) |*scene| {
            scene.deinit();
            self.current_game_track_scene = null;
        }
        gameplay_resources.unloadTurbo(self);
        gameplay_resources.unloadBarrier(self);
        gameplay_resources.unloadLazer(self);
        gameplay_resources.unloadSalt(self);
        gameplay_resources.unloadActorModels(self);
        gameplay_resources.unloadSprites(self);
        gameplay_resources.unloadSoundFx(self);
        if (self.current_standalone_segment_preview) |*loaded_track_preview| {
            loaded_track_preview.deinit();
            self.current_standalone_segment_preview = null;
        }
        if (self.current_standalone_segment_scene) |*scene| {
            scene.deinit();
            self.current_standalone_segment_scene = null;
        }
        if (self.current_text_script) |*script| {
            script.deinit(self.allocator);
            self.current_text_script = null;
        }

        audio.stopVoicePlayback(self);
        if (self.current_texture) |*texture| {
            texture.unload();
            self.current_texture = null;
        }
        if (self.frontend_canvas) |canvas| {
            canvas.unload();
            self.frontend_canvas = null;
        }
        if (self.frontend_cursor_texture) |*texture| {
            texture.unload();
            self.frontend_cursor_texture = null;
        }
        self.frontend_widget_art.unload();
        self.frontend_sound_fx.unload();
        self.slider_art.unload();
        self.route_map_art.unload();
        self.unloadFrontendRouteLevel();
        if (self.galaxy_names) |*names| {
            names.deinit();
            self.galaxy_names = null;
        }

        self.ui_font.deinit();
        self.animation_catalog.deinit();
        self.resources.deinit();
        self.high_score_tables.deinit(self.allocator);
    }

    fn warmupSmokeTest(self: *AppState) !void {
        var loaded_loading_screen = try loading_screen.Loaded.load(&self.resources);
        defer loaded_loading_screen.deinit();
        if (loaded_loading_screen.background_texture.texture.width <= 0 or loaded_loading_screen.bar_texture.texture.width <= 0) {
            return error.InvalidLoadingScreenTexture;
        }

        var loaded_intro_background = try background.Loaded.loadByPath(self.allocator, &self.resources, intro_background_path);
        defer loaded_intro_background.deinit();
        if (loaded_intro_background.primary_texture.texture.width <= 0) {
            return error.InvalidIntroBackgroundTexture;
        }

        var loaded_thanks_background = try background.Loaded.loadByPath(self.allocator, &self.resources, thanks_screen_background_path);
        defer loaded_thanks_background.deinit();
        if (loaded_thanks_background.primary_texture.texture.width <= 0) {
            return error.InvalidThanksBackgroundTexture;
        }

        var loaded_intro_script = try self.loadConfiguredTextScriptEntry(intro_script_path);
        defer loaded_intro_script.deinit(self.allocator);
        if (loaded_intro_script.entries.len == 0) {
            return error.EmptyIntroScript;
        }

        var loaded_credits_script = try self.loadConfiguredTextScriptEntry(credits_script_path);
        defer loaded_credits_script.deinit(self.allocator);
        if (loaded_credits_script.entries.len == 0) {
            return error.EmptyCreditsScript;
        }

        if (!self.audio_ready or self.resources.catalog.audio_entries.len == 0) {
            return;
        }

        try debug_browser.primeAudioPreview(self);
    }

    // PORT(partial): the original loading screen advances from real archive reads
    // and startup initialization loops. The port now advances from actual front-end
    // startup loads instead of a timer, but it still does not cover the full world-init pass.
    fn advanceBootTask(self: *AppState) !bool {
        if (self.boot_task_index >= boot_tasks.len) return true;

        switch (boot_tasks[self.boot_task_index]) {
            .load_high_scores => try self.high_score_tables.loadFromRuntimeRoot(self.allocator, self.runtime_root_path),
            .load_intro_background => {
                self.unloadPreloadedBackground(&self.preloaded_intro_background);
                self.preloaded_intro_background = try background.Loaded.loadByPath(self.allocator, &self.resources, intro_background_path);
            },
            .load_main_menu_background => {
                self.unloadPreloadedBackground(&self.preloaded_main_menu_background);
                self.preloaded_main_menu_background = try background.Loaded.loadByPath(self.allocator, &self.resources, main_menu_background_path);
            },
            .load_route_map_background => {
                self.unloadPreloadedBackground(&self.preloaded_route_map_background);
                self.preloaded_route_map_background = try background.Loaded.loadByPath(self.allocator, &self.resources, route_map_background_path);
            },
            .load_help_background => {
                self.unloadPreloadedBackground(&self.preloaded_help_background);
                self.preloaded_help_background = try background.Loaded.loadByPath(self.allocator, &self.resources, help_background_path);
            },
            .load_intro_script => {
                self.unloadPreloadedTextScript(&self.preloaded_intro_script);
                self.preloaded_intro_script = try self.loadConfiguredTextScriptEntry(intro_script_path);
            },
            .load_credits_script => {
                self.unloadPreloadedTextScript(&self.preloaded_credits_script);
                self.preloaded_credits_script = try self.loadConfiguredTextScriptEntry(credits_script_path);
            },
            .load_intro_music => {
                self.unloadPreloadedMusic(&self.preloaded_intro_music);
                self.preloaded_intro_music = try self.resources.catalog.loadMusicByPath(self.allocator, intro_music_path);
            },
            .load_menu_music => {
                self.unloadPreloadedMusic(&self.preloaded_menu_music);
                self.preloaded_menu_music = try self.resources.catalog.loadMusicByPath(self.allocator, default_audio_path);
            },
        }

        self.boot_task_index += 1;
        return self.boot_task_index >= boot_tasks.len;
    }

    fn unloadPreloadedBootAssets(self: *AppState) void {
        self.unloadPreloadedBackground(&self.preloaded_intro_background);
        self.unloadPreloadedBackground(&self.preloaded_main_menu_background);
        self.unloadPreloadedBackground(&self.preloaded_route_map_background);
        self.unloadPreloadedBackground(&self.preloaded_help_background);
        self.unloadPreloadedTextScript(&self.preloaded_intro_script);
        self.unloadPreloadedTextScript(&self.preloaded_credits_script);
        self.unloadPreloadedMusic(&self.preloaded_intro_music);
        self.unloadPreloadedMusic(&self.preloaded_menu_music);
    }

    fn unloadPreloadedBackground(self: *AppState, slot: *?background.Loaded) void {
        _ = self;
        if (slot.*) |*loaded| {
            loaded.deinit();
            slot.* = null;
        }
    }

    fn unloadPreloadedTextScript(self: *AppState, slot: *?intro.Loaded) void {
        if (slot.*) |*loaded| {
            loaded.deinit(self.allocator);
            slot.* = null;
        }
    }

    fn unloadPreloadedMusic(self: *AppState, slot: *?assets.LoadedMusic) void {
        _ = self;
        if (slot.*) |*loaded| {
            loaded.unload();
            slot.* = null;
        }
    }

    pub fn saveRuntimeConfig(self: *const AppState) !void {
        try self.runtime_config.saveToRuntimeRoot(self.runtime_root_path);
    }

    fn update(self: *AppState, frame_delta_seconds: f64) !void {
        self.render_time_seconds += frame_delta_seconds;
        if (self.current_music) |music| {
            rl.updateMusicStream(music.music);
        }
        const tick_count = self.simulation_clock.beginFrame(frame_delta_seconds);
        const runner_input = self.pending_level_input;
        self.pending_level_input = .{};
        for (0..tick_count) |tick_index| {
            try self.simulateTick(if (tick_index == 0) runner_input else .{});
        }
    }

    fn simulateTick(self: *AppState, runner_input: gameplay.RunnerInput) !void {
        switch (self.command) {
            .game => try self.simulateGameTick(runner_input),
            .debug, .smoke => {
                if (self.mode == .streaks) {
                    self.debug_light_streak_view.step();
                }
                if (self.current_animation) |*animation| {
                    try animation.step(self.simulation_clock.step_seconds);
                }
                if (self.current_track_preview) |*loaded_track_preview| {
                    if (self.level_runner) |*runner| {
                        runner.step(loaded_track_preview, runner_input, @floatCast(self.simulation_clock.step_seconds));
                    }
                }
            },
        }
    }

    fn handleInput(self: *AppState) !void {
        if (rl.isKeyPressed(.f12)) {
            try self.queueScreenshot(false);
        }

        switch (self.command) {
            .game => return self.handleGameInput(),
            .smoke => return,
            .debug => return debug_browser.handleInput(self),
        }
    }

    fn currentUiLayout(self: *const AppState) VirtualLayout {
        _ = self;
        return ui.virtualLayout(.{
            .x = 0.0,
            .y = 0.0,
            .width = @floatFromInt(screenWidth()),
            .height = @floatFromInt(screenHeight()),
        });
    }

    pub fn currentFrontendMouseLocal(self: *const AppState) ?rl.Vector2 {
        return self.currentUiMouseLocal();
    }

    pub fn currentUiMouseLocal(self: *const AppState) ?rl.Vector2 {
        if (self.mouse_local_override) |mouse| {
            return .{ .x = mouse.x, .y = mouse.y };
        }
        const layout = self.currentUiLayout();
        const mouse_x = @as(f32, @floatFromInt(rl.getMouseX()));
        const mouse_y = @as(f32, @floatFromInt(rl.getMouseY()));
        if (!layout.containsScreenPoint(mouse_x, mouse_y)) return null;
        return layout.unmapPoint(mouse_x, mouse_y);
    }

    fn setFrontendHoverTarget(self: *AppState, target: ?frontend_activation.HoverTarget) void {
        frontend_input.setHoverTarget(self, target);
    }

    fn noteFrontendKeyboardNavigation(self: *AppState) void {
        frontend_input.noteKeyboardNavigation(self);
    }

    pub fn activeFrontendButtonTarget(self: *const AppState) ?frontend_activation.HoverTarget {
        return frontend_input.activeButtonTarget(self);
    }

    fn frontendButtonHot(self: *const AppState, target: frontend_activation.HoverTarget, fallback_selected: bool) bool {
        return frontend_input.buttonHot(self, target, fallback_selected);
    }

    fn queueFrontendActivation(self: *AppState, action: frontend_activation.QueuedAction) void {
        frontend_input.queueActivation(self, action);
    }

    fn dispatchFrontendActivation(self: *AppState, action: frontend_activation.QueuedAction) !void {
        try frontend_input.dispatchActivation(self, action);
    }

    fn updatePendingFrontendActivation(self: *AppState) !bool {
        return frontend_input.updatePendingActivation(self);
    }

    fn readPressedFrontendWidgetShortcutCode(_: *const AppState) ?u8 {
        return frontend_input.readPressedWidgetShortcutCode();
    }

    fn frontendShortcutActivationForCode(self: *const AppState, code: u8) ?frontend_activation.QueuedAction {
        return frontend_input.shortcutActivationForCode(self, code);
    }

    fn handleFrontendWidgetShortcutInput(self: *AppState) !bool {
        return frontend_input.handleWidgetShortcutInput(self);
    }

    fn updateFrontendWidgetAnimations(self: *AppState) void {
        frontend_input.updateWidgetAnimations(self);
    }

    pub fn snapFrontendWidgetStates(self: *AppState) void {
        frontend_input.snapWidgetStates(self);
    }

    pub fn optionsMenuLayoutState(self: *const AppState) frontend_options_menu.LayoutState {
        return frontend_mouse.optionsMenuLayoutState(self);
    }

    pub fn highScoreReplayAvailable(self: *const AppState, entry_index: usize) bool {
        const selected_mode = self.activeHighScoreScreenMode();
        if (!frontend_high_score_screen.rowsShowReplay(selected_mode, self.postLevelHighScoreContext() != null)) return false;
        const entries = self.high_score_tables.visibleEntries(selected_mode);
        return entry_index < entries.len and entries[entry_index].has_replay;
    }

    fn simulateGameTick(self: *AppState, runner_input: gameplay.RunnerInput) !void {
        const effective_runner_input = if (self.completionScreenOverlayActive())
            gameplay.RunnerInput{}
        else
            runner_input;
        self.game_phase_ticks += 1;
        if (self.current_game_background_runtime) |*runtime| {
            runtime.update();
        }
        self.background_light_streaks.update(
            render_phase.lightStreakCamera(self),
            render_phase.lightStreaksVisible(self),
        );
        if (self.game_status_ticks > 0) {
            self.game_status_ticks -= 1;
            if (self.game_status_ticks == 0) {
                self.game_status_message = null;
            }
        }
        self.gameplay_voice_manager.tick();
        self.native_gameplay_voice_manager.tick();
        if (self.game_phase == .level and !self.frontend_transition.blocksInput()) {
            if (self.level_runner) |*runner| {
                if (!runner.paused and !self.startupGameplayBlockActive()) {
                    self.level_prompt_queue.tick();
                }
                if (self.isTutorialGameplay() and runner.score.total > self.tutorial_reference_score) {
                    self.tutorial_reference_score = runner.score.total;
                }
                // PORT(verified): native `update_tip_manager` drives the active
                // `turbo-talk` clip while a tip card is up; when the tip
                // clears, the presentation controller falls back to its
                // baseline clip. The port mirrors that by diffing the
                // prompt-queue state and dispatching the correct
                // `AnimClipId` through `dispatchCutsceneAnimation`, keeping
                // the renderer's model-swap purely a consumer of the anim
                // slot.
                gameplay_resources.syncCutsceneAnimFromPromptQueue(self, runner);
            }
        }

        if (self.frontend_transition.update()) |next_phase| {
            try self.enterGamePhase(next_phase);
            self.frontend_transition.completeHandoff();
            return;
        }

        if (try self.updatePendingFrontendActivation()) {
            return;
        }

        self.updateFrontendWidgetAnimations();
        self.stepCompletionScreenReveal();
        if (self.game_phase == .thanks_screen) {
            self.thanks_screen_controller.step();
        }

        if (self.game_phase == .boot) {
            if (try self.advanceBootTask()) {
                try self.enterGamePhase(.intro);
                self.frontend_transition.beginFadeIn();
            }
            return;
        }

        if (self.game_phase == .intro or self.game_phase == .credits) {
            if (self.currentTextScriptDurationTicks()) |duration_ticks| {
                if (self.game_phase_ticks >= duration_ticks and !self.frontend_transition.blocksInput()) {
                    self.frontend_transition.beginFadeOut(.main_menu);
                }
            }
        }

        if (self.game_phase == .level) {
            if (try self.handleSelectedReplayFadeExit()) return;
            try gameplay_resources.syncTurboAnimation(self);
            if (self.current_track_preview) |*loaded_track_preview| {
                if (self.level_runner) |*runner| {
                    const previous_runner = runner.*;
                    const previous_active_level_segment_index = self.active_level_segment_index;
                    const startup_block_active = self.startupGameplayBlockActive();
                    if (!startup_block_active and !self.tutorialPromptBlocksGameplay()) {
                        runner.stepWithReplay(
                            loaded_track_preview,
                            effective_runner_input,
                            selected_replay.directiveForRunner(self, runner),
                            @floatCast(self.simulation_clock.step_seconds),
                        );
                        if (runner.consumeReplayFadeRequest()) {
                            self.selected_replay_fade_exit_pending = true;
                            if (self.frontend_transition.state == .idle) {
                                self.frontend_transition.beginOverlayFadeOut();
                            }
                            return;
                        }
                        self.updateGameplayRunnerPresentation(previous_runner, runner.*, effective_runner_input);
                        audio.playGameplayRunnerAudio(self, previous_runner, runner.*, loaded_track_preview, effective_runner_input);
                        audio.updateGameplayAmbientVoices(self, runner.*, loaded_track_preview);
                        self.gameplay_effects.spawnRunnerEffects(previous_runner, runner.*, loaded_track_preview);
                    } else {
                        self.refreshRunnerForStartupBlock(
                            runner,
                            loaded_track_preview,
                            @floatCast(self.simulation_clock.step_seconds),
                        );
                    }
                    self.updateSubgameCamera(runner);
                    try self.syncActiveLevelSegment();
                    try self.dispatchCurrentRunnerRowMessage(
                        previous_active_level_segment_index,
                        previous_runner.currentRowMessageToken(),
                        false,
                    );
                }
            }
            self.gameplay_effects.update();
            if (self.current_gameplay_turbo_animation) |*animation| {
                try animation.step(self.simulation_clock.step_seconds);
            }
            if (self.level_runner) |*runner| {
                switch (runner.consumeHandoff()) {
                    .none => {},
                    .completion_screen_init => {
                        audio.playGameplayEffect(self, self.current_gameplay_sound_fx.completion_init);
                        try self.beginCompletedRunOverlay();
                        return;
                    },
                    .completion_finalize => {
                        try self.finalizeCompletedRunScreen();
                        return;
                    },
                    .respawn => {
                        try self.beginRespawnRun();
                        return;
                    },
                    .final_loss => |cause| {
                        try self.beginFailedRun(cause);
                        return;
                    },
                }
            }
        }
    }

    fn updateGameplayRunnerPresentation(self: *AppState, previous: gameplay.Runner, current: gameplay.Runner, _: gameplay.RunnerInput) void {
        self.gameplay_jetpack_visual_state.tick();
        self.gameplay_weapon_visual_state.tick();
        self.gameplay_jetpack_visual_state.noteActiveChange(
            nativeJetpackVisualPresentationActive(previous),
            nativeJetpackVisualPresentationActive(current),
        );
        self.gameplay_weapon_visual_state.noteWeaponChannelChange(previous.movement_flags, current.movement_flags);
        if (previous.shot_cooldown_ticks == 0 and current.shot_cooldown_ticks > 0) {
            self.gameplay_weapon_visual_state.noteFire(current.movement_flags);
        }
    }

    fn handleGameInput(self: *AppState) !void {
        if (try self.handleFrontendWidgetShortcutInput()) return;

        if (rl.isKeyPressed(.escape)) {
            switch (self.game_phase) {
                .level => if (!self.completionScreenOverlayActive()) try self.enterPauseMenu(),
                .boot => self.should_exit = true,
                .main_menu => try self.beginExitPrompt(.main_menu),
                .intro, .credits => self.frontend_transition.beginFadeOut(.main_menu),
                .new_game_menu, .help => try self.enterGamePhase(.main_menu),
                .challenge_setup_menu => try self.returnToNewGameMenu(.challenge_setup_menu),
                .high_scores_menu => if (self.postLevelHighScoreContext() != null)
                    try self.cancelPostLevelHighScoreEntry()
                else
                    try self.performHighScoreMenuAction(.back),
                .options_menu => try self.leaveOptionsMenu(),
                .pause_menu => try self.resumeFromPauseMenu(),
                .route_map_menu => try self.performRouteMenuAction(.back),
                .exit_prompt => try self.enterGamePhase(self.exit_prompt_return_phase),
                .completion_screen => if (self.completionContinueVisible()) try self.continueCompletionScreen(),
                .thanks_screen => self.beginThanksScreenExit(),
            }
            return;
        }

        if (self.frontend_transition.blocksInput()) return;
        if (self.pending_frontend_activation != null) return;

        switch (self.game_phase) {
            .boot => {},
            .intro => {
                if (rl.isMouseButtonPressed(.left)) {
                    self.frontend_transition.beginFadeOut(.main_menu);
                }
            },
            .main_menu => {
                try frontend_mouse.updateMainMenuSelection(self);
                frontend_input.handleMainMenuKeyboard(self);
            },
            .new_game_menu => {
                self.normalizeNewGameMenuSelection();
                try frontend_mouse.updateNewGameSelection(self);
                frontend_input.handleNewGameKeyboard(self);
            },
            .challenge_setup_menu => {
                self.normalizeChallengeSetupSelection();
                frontend_mouse.updateChallengeSetupSelection(self);
                frontend_input.handleChallengeSetupKeyboard(self);
            },
            .options_menu => {
                try frontend_mouse.updateOptionsSelection(self);
                try frontend_input.handleOptionsKeyboard(self);
            },
            .pause_menu => {
                frontend_mouse.updatePauseSelection(self);
                frontend_input.handlePauseKeyboard(self);
            },
            .route_map_menu => {
                try frontend_mouse.updateRouteMapSelection(self);
                try frontend_input.handleRouteMapKeyboard(self);
                self.syncRouteMapHighlightTargets();
                self.stepRouteMapHighlightAnimations();
            },
            .high_scores_menu => {
                try frontend_mouse.updateHighScoresSelection(self);
                if (self.postLevelHighScoreContext() != null) {
                    self.collectPostLevelHighScoreTextInput();
                }
                frontend_input.handleHighScoresKeyboard(self);
            },
            .exit_prompt => {
                try frontend_mouse.updateExitPromptSelection(self);
                frontend_input.handleExitPromptKeyboard(self);
            },
            .completion_screen => {
                frontend_mouse.updateCompletionSelection(self);
                frontend_input.handleCompletionKeyboard(self);
            },
            .thanks_screen => {
                if (rl.isMouseButtonPressed(.left) or rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    self.beginThanksScreenExit();
                }
            },
            .credits => {
                if (rl.isMouseButtonPressed(.left)) {
                    self.frontend_transition.beginFadeOut(.main_menu);
                }
            },
            .help => {
                frontend_mouse.updateHelpSelection(self);
                frontend_input.handleHelpKeyboard(self);
            },
            .level => {
                if (self.gameplay_click_start_active) {
                    if (rl.isMouseButtonPressed(.left) or rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                        try self.activateGameplayClickStart();
                    }
                    return;
                }
                if (self.level_runner) |runner| {
                    if (runner.introCutsceneBlocksGameplay()) return;
                }
                if (self.tutorialPromptBlocksGameplay()) {
                    if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                        self.level_prompt_queue.dismissActive();
                    } else if (rl.isMouseButtonPressed(.left)) {
                        if (self.currentUiMouseLocal()) |mouse| {
                            if (gameplay_prompt_overlay.activeOkHitRect(self, &self.level_prompt_queue, true)) |ok_button| {
                                if (ok_button.contains(mouse)) {
                                    self.level_prompt_queue.dismissActive();
                                }
                            }
                        }
                    }
                    return;
                }
                if (self.completionScreenOverlayActive()) return;
                const accepts_runner_input = if (self.level_runner) |runner| runner.acceptsGameplayInput() else false;
                const accepts_live_replay_controls = accepts_runner_input and !selected_replay.playbackActive(self);
                self.mouse_level_lane_target = null;
                if (accepts_live_replay_controls and (rl.isKeyPressed(.left) or rl.isKeyPressed(.a))) {
                    self.mouse_level_lane_target = null;
                    self.pending_level_input.lane_delta -= 1;
                }
                if (accepts_live_replay_controls and (rl.isKeyPressed(.right) or rl.isKeyPressed(.d))) {
                    self.mouse_level_lane_target = null;
                    self.pending_level_input.lane_delta += 1;
                }
                if (accepts_live_replay_controls and (rl.isKeyPressed(.up) or rl.isKeyPressed(.w))) {
                    self.pending_level_input.speed_delta_rows_per_second += 2.0;
                }
                if (accepts_live_replay_controls and (rl.isKeyPressed(.down) or rl.isKeyPressed(.s))) {
                    self.pending_level_input.speed_delta_rows_per_second -= 2.0;
                }
                if (accepts_live_replay_controls and rl.isMouseButtonPressed(.left)) {
                    self.pending_level_input.fire_pressed = true;
                }
                if (accepts_live_replay_controls and rl.isMouseButtonDown(.left)) {
                    self.pending_level_input.fire_down = true;
                }
                if (accepts_runner_input and rl.isKeyPressed(.space)) {
                    try self.enterPauseMenu();
                    return;
                }
                if (rl.isKeyPressed(.r)) {
                    self.mouse_level_lane_target = null;
                    self.pending_level_input.reset = true;
                }
                if (accepts_live_replay_controls) {
                    if (self.current_track_preview) |loaded_track_preview| {
                        if (self.level_runner) |runner| {
                            self.mouse_level_lane_target = subgame_camera.laneCenterTargetForRunnerMouse(
                                loaded_track_preview,
                                runner,
                                @floatFromInt(rl.getMouseX()),
                                @floatFromInt(screenWidth()),
                            );
                            if (self.mouse_level_lane_target) |lane_target| {
                                self.pending_level_input.target_lane_center = lane_target;
                            }
                        }
                    }
                }
            },
        }
    }

    pub fn enterGamePhase(self: *AppState, phase: GamePhase) !void {
        try frontend_flow.enterGamePhase(self, phase);
    }

    fn enterStartPhase(self: *AppState, phase: GamePhase) !void {
        try frontend_flow.enterStartPhase(self, phase);
    }

    fn performMainMenuItem(self: *AppState, item: MainMenuItem) !void {
        try frontend_flow.performMainMenuItem(self, item);
    }

    fn activateMainMenuItem(self: *AppState, item: MainMenuItem) !void {
        try frontend_flow.activateMainMenuItem(self, item);
    }

    pub fn activeHighScoreScreenMode(self: *const AppState) high_score.Mode {
        return frontend_flow.activeHighScoreScreenMode(self);
    }

    fn setHighScoreBrowseOwner(self: *AppState, mode: high_score.Mode) void {
        frontend_flow.setHighScoreBrowseOwner(self, mode);
    }

    pub fn enterHighScoreBrowseScreen(self: *AppState, mode: high_score.Mode) !void {
        try frontend_flow.enterHighScoreBrowseScreen(self, mode);
    }

    fn enterPostLevelHighScoreScreen(self: *AppState, context: frontend_high_score_screen.PendingEntry) !void {
        try frontend_flow.enterPostLevelHighScoreScreen(self, context);
    }

    fn enterPostLevelHighScoreScreenWithReturn(
        self: *AppState,
        context: frontend_high_score_screen.PendingEntry,
        return_owner: ?frontend_bridge.OuterOwnerState,
        return_opcode: ?frontend_bridge.OuterBridgeOpcode,
    ) !void {
        try frontend_flow.enterPostLevelHighScoreScreenWithReturn(self, context, return_owner, return_opcode);
    }

    fn performNewGameMenuItem(self: *AppState, item: NewGameMenuItem) !void {
        try frontend_flow.performNewGameMenuItem(self, item);
    }

    fn activateNewGameMenuItem(self: *AppState, item: NewGameMenuItem) !void {
        try frontend_flow.activateNewGameMenuItem(self, item);
    }

    pub fn newGameMenuItemVisible(self: *const AppState, item: NewGameMenuItem) bool {
        return frontend_flow.newGameMenuItemVisible(self, item);
    }

    fn newGameMenuIndexVisible(self: *const AppState, index: usize) bool {
        return frontend_flow.newGameMenuIndexVisible(self, index);
    }

    fn normalizeNewGameMenuSelection(self: *AppState) void {
        frontend_flow.normalizeNewGameMenuSelection(self);
    }

    fn stepNewGameMenuSelection(self: *AppState, delta: isize) void {
        frontend_flow.stepNewGameMenuSelection(self, delta);
    }

    pub fn challengeSetupReplayAvailable(self: *const AppState) bool {
        return frontend_flow.challengeSetupReplayAvailable(self);
    }

    fn challengeSetupVisibleItems(self: *const AppState) []const frontend_challenge_setup_menu.Item {
        return frontend_flow.challengeSetupVisibleItems(self);
    }

    fn currentChallengeSetupSelectedItem(self: *const AppState) frontend_challenge_setup_menu.Item {
        return frontend_flow.currentChallengeSetupSelectedItem(self);
    }

    fn normalizeChallengeSetupSelection(self: *AppState) void {
        frontend_flow.normalizeChallengeSetupSelection(self);
    }

    pub fn enterChallengeSetupMenu(self: *AppState) !void {
        try frontend_flow.enterChallengeSetupMenu(self);
    }

    fn performChallengeSetupMenuItem(self: *AppState, item: frontend_challenge_setup_menu.Item) !void {
        try frontend_flow.performChallengeSetupMenuItem(self, item);
    }

    fn performOptionsMenuItem(self: *AppState, item: OptionsMenuItem) !void {
        try frontend_flow.performOptionsMenuItem(self, item);
    }

    fn performPauseMenuItem(self: *AppState, item: PauseMenuItem) !void {
        try frontend_flow.performPauseMenuItem(self, item);
    }

    fn performHelpMenuItem(self: *AppState, item: frontend_help.Action) !void {
        try frontend_flow.performHelpMenuItem(self, item);
    }

    fn activateOptionsMenuItem(self: *AppState, item: OptionsMenuItem) !void {
        try frontend_flow.activateOptionsMenuItem(self, item);
    }

    fn beginExitPrompt(self: *AppState, return_phase: GamePhase) !void {
        try frontend_flow.beginExitPrompt(self, return_phase);
    }

    fn beginEndGamePrompt(self: *AppState, return_phase: GamePhase) !void {
        try frontend_flow.beginEndGamePrompt(self, return_phase);
    }

    // PORT(verified): the special postal-return Star Map mode (`initialize_galaxy` with
    // `this + 4 == 1`) routes its bottom `Exit` control through the shared exit-prompt
    // controller before returning to the outer front-end flow.
    fn beginRouteMapExitPrompt(self: *AppState) !void {
        try frontend_flow.beginRouteMapExitPrompt(self);
    }

    fn performExitPromptChoice(self: *AppState, choice: frontend_exit_prompt.Choice) !void {
        try frontend_flow.performExitPromptChoice(self, choice);
    }

    fn activateExitPromptChoice(self: *AppState, choice: frontend_exit_prompt.Choice) !void {
        try frontend_flow.activateExitPromptChoice(self, choice);
    }

    fn performRouteMenuAction(self: *AppState, action: RouteMenuAction) !void {
        try frontend_flow.performRouteMenuAction(self, action);
    }

    fn performCompletionAction(self: *AppState, action: frontend_completion_screen.Action) !void {
        try frontend_flow.performCompletionAction(self, action);
    }

    fn performPostLevelHighScoreAction(self: *AppState, action: frontend_high_score_screen.PostLevelAction) !void {
        try frontend_flow.performPostLevelHighScoreAction(self, action);
    }

    fn activatePostLevelHighScoreAction(self: *AppState, action: frontend_high_score_screen.PostLevelAction) !void {
        try frontend_flow.activatePostLevelHighScoreAction(self, action);
    }

    fn performHighScoreMenuAction(self: *AppState, action: frontend_high_score_screen.MenuAction) !void {
        try frontend_flow.performHighScoreMenuAction(self, action);
    }

    fn performHighScoreReplay(self: *AppState, entry_index: usize) !void {
        try frontend_flow.performHighScoreReplay(self, entry_index);
    }

    fn activateHighScoreMenuAction(self: *AppState, action: frontend_high_score_screen.MenuAction) !void {
        try frontend_flow.activateHighScoreMenuAction(self, action);
    }

    fn enterPauseMenu(self: *AppState) !void {
        try frontend_flow.enterPauseMenu(self);
    }

    fn resumeFromPauseMenu(self: *AppState) !void {
        try frontend_flow.resumeFromPauseMenu(self);
    }

    fn outerOwnerForAbandonActiveRun(
        self: *const AppState,
        opcode: *frontend_bridge.OuterBridgeOpcode,
    ) frontend_bridge.OuterOwnerState {
        return return_flow.ownerForAbandonActiveRun(self, opcode);
    }

    fn outerOwnerForRespawnActiveRun(
        self: *AppState,
        opcode: *frontend_bridge.OuterBridgeOpcode,
    ) ?frontend_bridge.OuterOwnerState {
        return return_flow.ownerForRespawnActiveRun(self, opcode);
    }

    fn outerOwnerForPendingRunResult(
        self: *const AppState,
        result: PendingRunResult,
        opcode: *frontend_bridge.OuterBridgeOpcode,
    ) frontend_bridge.OuterOwnerState {
        return return_flow.ownerForPendingRunResult(self, result, opcode);
    }

    fn applyOuterBridgeTeardown(
        self: *AppState,
        opcode: frontend_bridge.OuterBridgeOpcode,
        next_owner: frontend_bridge.OuterOwnerState,
    ) !void {
        try return_flow.applyOuterBridgeTeardown(self, opcode, next_owner);
    }

    fn resumeActiveRunAfterRespawnBridge(self: *AppState) !void {
        try return_flow.resumeActiveRunAfterRespawnBridge(self);
    }

    fn runOuterBridgeTransition(
        self: *AppState,
        opcode: frontend_bridge.OuterBridgeOpcode,
        next_owner: frontend_bridge.OuterOwnerState,
    ) !void {
        try return_flow.runOuterBridgeTransition(self, opcode, next_owner);
    }

    fn currentFailedRunResult(self: *AppState) ?PendingRunResult {
        return run_result.currentFailedRunResult(self);
    }

    fn standalonePostLevelHighScoreEntry(
        self: *AppState,
        result: PendingRunResult,
    ) !?StandalonePostLevelHighScoreEntry {
        switch (result.completion_owner) {
            .postal_failure, .challenge_failure => {},
            else => return null,
        }

        const committed = try self.commitRunResultIfNeeded(result);
        const mode = committed.high_score_mode orelse return null;
        const rank = committed.high_score_rank orelse return null;
        return .{
            .context = .{
                .mode = mode,
                .rank = rank,
            },
            // PORT(verified): `add_arcade_high_score` / `add_survival_high_score` switch into the
            // shared post-level high-score owner (`state 0x14`), and `update_high_score_screen ->
            // exit_high_score_screen` then restores owner by the run mode lane (`state 2` for
            // postal, `state 10` for challenge), not by the preserved gameplay launch surface.
            .return_owner = blk: {
                var opcode: frontend_bridge.OuterBridgeOpcode = .destroy_return;
                break :blk self.outerOwnerForPendingRunResult(committed, &opcode);
            },
            .return_opcode = blk: {
                var opcode: frontend_bridge.OuterBridgeOpcode = .destroy_return;
                _ = self.outerOwnerForPendingRunResult(committed, &opcode);
                break :blk opcode;
            },
        };
    }

    pub fn abandonActiveRun(self: *AppState) !void {
        self.pending_run_result = null;
        self.clearPostLevelHighScoreEntry();
        var return_opcode: frontend_bridge.OuterBridgeOpcode = .destroy_return;
        const return_owner = self.outerOwnerForAbandonActiveRun(&return_opcode);
        if (!selected_replay.playbackActive(self)) {
            if (self.currentFailedRunResult()) |result| {
                if (try self.standalonePostLevelHighScoreEntry(result)) |entry| {
                    try self.enterPostLevelHighScoreScreenWithReturn(entry.context, entry.return_owner, entry.return_opcode);
                    return;
                }
            }
        }
        try self.runOuterBridgeTransition(return_opcode, return_owner);
    }

    fn enterGameplayShell(self: *AppState, level_path: []const u8) !void {
        try frontend_flow.enterGameplayShell(self, level_path);
    }

    fn enterFrontendLevelPath(self: *AppState, mode: FrontendLevelMode, level_index: usize) !void {
        try frontend_flow.enterFrontendLevelPath(self, mode, level_index);
    }

    fn enterSelectedLevelRecordPath(self: *AppState, record: frontend_bridge.SelectedLevelRecordOverride) !void {
        try frontend_flow.enterSelectedLevelRecordPath(self, record);
    }

    fn enterSelectedLevelRecordSource(self: *AppState, launch: frontend_bridge.SelectedLevelRecordLaunch) !void {
        try frontend_flow.enterSelectedLevelRecordSource(self, launch);
    }

    pub fn beginFrontendLevelPath(
        self: *AppState,
        mode: FrontendLevelMode,
        level_index: usize,
        selected_level_record_override: ?frontend_bridge.SelectedLevelRecordOverride,
        selected_level_record_launch: ?frontend_bridge.SelectedLevelRecordLaunch,
    ) !void {
        try frontend_flow.beginFrontendLevelPath(self, mode, level_index, selected_level_record_override, selected_level_record_launch);
    }

    fn leaveOptionsMenu(self: *AppState) !void {
        try frontend_flow.leaveOptionsMenu(self);
    }

    // PORT(verified): `update_help_screen` writes frontend state `2` on Back, and the frontend
    // state machine handles that by rebuilding the New Game screen/controller path rather than
    // jumping straight to the main menu. The normal Star Map `update_galaxy -> return 3`
    // path in `update_subgame` also tears down the galaxy screen and returns to the New Game
    // flow. Preserve that return target in the port instead of routing Help/Star Map Back to
    // the main menu.
    fn returnToNewGameMenu(self: *AppState, from_phase: GamePhase) !void {
        try frontend_flow.returnToNewGameMenu(self, from_phase);
    }

    fn enterFrontendLevelMode(self: *AppState, mode: FrontendLevelMode) !void {
        try frontend_flow.enterFrontendLevelMode(self, mode);
    }

    fn enterRouteMapMenu(self: *AppState, mode: FrontendLevelMode) !void {
        try frontend_flow.enterRouteMapMenu(self, mode);
    }

    pub fn enterRouteMapMenuWithScreenMode(self: *AppState, mode: FrontendLevelMode, screen_mode: frontend_bridge.RouteMapScreenMode) !void {
        try frontend_flow.enterRouteMapMenuWithScreenMode(self, mode, screen_mode);
    }

    fn unloadFrontendRouteLevel(self: *AppState) void {
        if (self.frontend_route_level) |*loaded_level| {
            loaded_level.deinit();
            self.frontend_route_level = null;
        }
    }

    pub fn reloadFrontendRouteLevel(self: *AppState) !void {
        self.unloadFrontendRouteLevel();
        const mode = self.frontend_route_mode orelse return;
        var path_buffer: [64]u8 = undefined;
        const level_path = frontendLevelPath(mode, self.frontend_route_index, &path_buffer) catch return;
        const level_index = self.resources.catalog.findLevelIndex(level_path) orelse return;
        self.frontend_route_level = try level.loadFromArchive(self.allocator, &self.resources.catalog, self.resources.catalog.level_entries[level_index]);
    }

    pub fn currentFrontendGalaxyName(self: *const AppState) ?[]const u8 {
        const names = self.galaxy_names orelse return null;
        return names.nameForRouteIndex(self.currentRouteMapOpenIndex() orelse self.frontend_route_index);
    }

    pub fn routeMapShowsReplay(self: *const AppState) bool {
        // PORT(verified): `open_galaxy_route` only reveals "Watch Best Trial" when the Star
        // Map is in internal mode `2` and the route's completion slot has replay data.
        if (self.route_map_screen_mode != .replay) return false;
        const route_index = self.currentRouteMapOpenIndex() orelse return false;
        return routeMapHasReplayEntry(self.frontend_route_mode, route_index, &self.high_score_tables);
    }

    pub fn routeMapCardIsOpen(self: *const AppState) bool {
        return route_map_state.cardIsOpen(self);
    }

    pub fn currentRouteMapOpenIndex(self: *const AppState) ?usize {
        return route_map_state.currentOpenIndex(self);
    }

    pub fn openFrontendRouteCard(self: *AppState, route_index: usize) !void {
        try route_map_state.openCard(self, route_index);
    }

    pub fn resetRouteMapHighlightAnimations(self: *AppState) void {
        route_map_state.resetHighlightAnimations(self);
    }

    pub fn syncRouteMapHighlightTargets(self: *AppState) void {
        route_map_state.syncHighlightTargets(self);
    }

    fn stepRouteMapHighlightAnimations(self: *AppState) void {
        route_map_state.stepHighlightAnimations(self);
    }

    fn clearLevelPromptQueue(self: *AppState) void {
        self.level_prompt_queue.clear();
    }

    fn isTutorialGameplay(self: *const AppState) bool {
        return level_loader.isTutorialGameplay(self);
    }

    fn isTutorialFlow(self: *const AppState) bool {
        return level_loader.isTutorialFlow(self);
    }

    fn isTutorialLevel(self: *const AppState) bool {
        return level_loader.isTutorialLevel(self);
    }

    fn tutorialPromptBlocksGameplay(self: *const AppState) bool {
        if (!self.isTutorialGameplay()) return false;
        const prompt = self.level_prompt_queue.active() orelse return false;
        return prompt.interactive;
    }

    fn tutorialClickStartCutsceneActive(self: *const AppState) bool {
        if (!self.gameplay_click_start_active) return false;
        const runner = self.level_runner orelse return false;
        return runner.introCutsceneBlocksGameplay();
    }

    fn startupGameplayBlockActive(self: *const AppState) bool {
        if (self.gameplay_click_start_active) return true;
        const runner = self.level_runner orelse return false;
        return runner.introCutsceneBlocksGameplay();
    }

    fn refreshRunnerForStartupBlock(
        self: *const AppState,
        runner: *gameplay.Runner,
        loaded_track_preview: *const track.LoadedLevelPreview,
        delta_seconds: f32,
    ) void {
        if (self.gameplay_click_start_active) {
            runner.refreshBlockedStartupState(loaded_track_preview);
            return;
        }
        if (runner.introCutsceneBlocksGameplay()) {
            runner.stepIntroStartupBlock(loaded_track_preview, delta_seconds);
            return;
        }
        runner.refreshCameraState(loaded_track_preview);
    }

    fn resetSubgameCamera(self: *AppState) void {
        level_loader.resetSubgameCamera(self);
    }

    pub fn updateSubgameCamera(self: *AppState, runner: *gameplay.Runner) void {
        const selection = subgame_camera.selectionForRunner(runner);
        subgame_camera.updateState(&self.subgame_camera, selection);
    }

    fn queueLevelSegmentPrompt(self: *AppState, segment_entry: *const level.SegmentEntry) void {
        level_loader.queueLevelSegmentPrompt(self, segment_entry);
    }

    fn activateGameplayClickStart(self: *AppState) !void {
        if (!self.gameplay_click_start_active) return;
        self.gameplay_click_start_active = false;
        self.mouse_level_lane_target = null;
        self.pending_level_input = .{};
        if (self.audio_ready) {
            if (self.frontend_sound_fx.select) |loaded| {
                rl.playSound(loaded.sound);
            }
        }
        rl.setMousePosition(@divTrunc(rl.getScreenWidth(), 2), @divTrunc(rl.getScreenHeight(), 2));
        const previous_active_level_segment_index = self.active_level_segment_index;
        try self.syncActiveLevelSegment();
        try self.dispatchCurrentRunnerRowMessage(previous_active_level_segment_index, null, true);
    }

    fn currentRunnerRowMessageSegmentIndex(self: *const AppState) ?usize {
        return level_loader.currentRunnerRowMessageSegmentIndex(self);
    }

    fn dispatchCurrentRunnerRowMessage(
        self: *AppState,
        previous_segment_index: ?usize,
        previous_token: ?u32,
        replay_sample_on_match: bool,
    ) !void {
        try level_loader.dispatchCurrentRunnerRowMessage(self, previous_segment_index, previous_token, replay_sample_on_match);
    }

    fn replaySpeedScalarForSliderValue(value: u32) f32 {
        return level_loader.replaySpeedScalarForSliderValue(value);
    }

    fn currentRunReplaySpeedScalar(self: *const AppState) f32 {
        return level_loader.currentRunReplaySpeedScalar(self);
    }

    fn currentRunChallengeDifficultyValue(self: *const AppState) u32 {
        return level_loader.currentRunChallengeDifficultyValue(self);
    }

    fn currentRunChallengeDifficultyScalar(self: *const AppState) f32 {
        return level_loader.currentRunChallengeDifficultyScalar(self);
    }

    fn currentRunChallengeSpeedValue(self: *const AppState) u32 {
        return level_loader.currentRunChallengeSpeedValue(self);
    }

    fn challengeParcelTargetCount(speed_value: u32, difficulty_scalar: f32) usize {
        return level_loader.challengeParcelTargetCount(speed_value, difficulty_scalar);
    }

    fn challengeRuntimeHazardScalar(value: u32) f32 {
        return level_loader.challengeRuntimeHazardScalar(value);
    }

    fn currentRunGarbageScalar(self: *const AppState) f32 {
        return level_loader.currentRunGarbageScalar(self);
    }

    fn currentRunSaltScalar(self: *const AppState) f32 {
        return level_loader.currentRunSaltScalar(self);
    }

    pub fn currentParcelTarget(self: *const AppState) usize {
        return level_loader.currentParcelTarget(self);
    }

    fn configureRuntimeParcels(self: *AppState, loaded_track_preview: *track.LoadedLevelPreview) !void {
        try level_loader.configureRuntimeParcels(self, loaded_track_preview);
    }

    fn currentRunRuntimeBuildFlags(self: *const AppState) u32 {
        return level_loader.currentRunRuntimeBuildFlags(self);
    }

    pub fn currentRunHighScoreEntry(self: *const AppState, score: u32) high_score.Entry {
        return level_loader.currentRunHighScoreEntry(self, score);
    }

    pub fn saveHighScoreTables(self: *AppState) !void {
        try self.high_score_tables.saveToRuntimeRoot(self.allocator, self.runtime_root_path);
    }

    fn beginCompletedRunOverlay(self: *AppState) !void {
        try run_result.beginCompletedOverlay(self);
    }

    fn finalizeCompletedRunScreen(self: *AppState) !void {
        if (self.pending_run_result == null) {
            try self.beginCompletedRunOverlay();
        }
        if (self.pending_run_result == null) return;

        self.completion_overlay_active = false;
        self.preserve_completion_screen_reveal_on_enter = true;
        try self.enterGamePhase(.completion_screen);
    }

    fn beginFailedRun(self: *AppState, cause: gameplay.DeathCause) !void {
        try run_result.beginFailedRun(self, cause);
    }

    fn beginRespawnRun(self: *AppState) !void {
        self.completion_overlay_active = false;
        self.preserve_completion_screen_reveal_on_enter = false;
        var opcode: frontend_bridge.OuterBridgeOpcode = .rebuild_clear_replay_return;
        const owner = self.outerOwnerForRespawnActiveRun(&opcode) orelse return;
        try self.runOuterBridgeTransition(opcode, owner);
    }

    fn resetCompletionScreenReveal(self: *AppState) void {
        run_result.resetCompletionScreenReveal(self);
    }

    fn completionScreenActive(self: *const AppState) bool {
        return run_result.completionScreenActive(self);
    }

    fn completionScreenOverlayActive(self: *const AppState) bool {
        return run_result.completionScreenOverlayActive(self);
    }

    fn completionScreenInteractive(self: *const AppState) bool {
        return run_result.completionScreenInteractive(self);
    }

    fn stepCompletionScreenReveal(self: *AppState) void {
        run_result.stepCompletionScreenReveal(self);
    }

    fn beginThanksScreenExit(self: *AppState) void {
        if (!self.thanks_screen_controller.allowsContinue()) return;
        if (self.frontend_transition.state != .idle) return;
        // PORT(verified): `update_thanks_for_playing_screen` plays `sfx 8`, starts the
        // front-end fade, and `uninit_thanks_screen` then writes state `0xe`, which the
        // frontend state machine immediately routes into `initialize_intro_screen(...Credits)`.
        audio.playFrontendSelectSound(self);
        self.frontend_transition.beginFadeOut(.credits);
    }

    fn completionBonusVisible(self: *const AppState, result: PendingRunResult) bool {
        return run_result.completionBonusVisible(self, result);
    }

    fn completionContinueVisible(self: *const AppState) bool {
        return run_result.completionContinueVisible(self);
    }

    fn commitRunResultIfNeeded(self: *AppState, result: PendingRunResult) !PendingRunResult {
        return run_result.commitIfNeeded(self, result);
    }

    fn commitPendingRunResultIfNeeded(self: *AppState) !void {
        try run_result.commitPendingIfNeeded(self);
    }

    fn finishPostLevelHighScoreReturn(self: *AppState) !void {
        const return_owner = self.post_level_high_score_return_owner;
        if (return_owner) |owner| {
            self.clearPostLevelHighScoreEntry();
            self.pending_run_result = null;
            self.completion_overlay_active = false;
            self.preserve_completion_screen_reveal_on_enter = false;
            try self.runOuterBridgeTransition(self.post_level_high_score_return_opcode, owner);
            return;
        }

        try self.finishPendingRunReturn();
    }

    fn failedResultPostLevelHighScoreEntry(self: *const AppState) ?StandalonePostLevelHighScoreEntry {
        const result = self.pending_run_result orelse return null;
        if (result.outcome != .failed) return null;
        const context = self.pendingRunHighScoreContext() orelse return null;

        switch (result.completion_owner) {
            .postal_failure, .challenge_failure => {},
            else => return null,
        }

        return .{
            .context = context,
            // PORT(verified): `complete_subgame` sends qualifying postal/challenge failures
            // through `add_arcade_high_score` / `add_survival_high_score`, which first arm
            // owner `0x14` plus app byte `+0x30d = 1`. `update_subgoldy_resurrect` then copies
            // that active owner into the saved-owner slot before setting state `0x1b`, so once
            // the post-level high-score owner takes over, the later return owner is already
            // fixed and no longer belongs to the live completion-screen result object.
            .return_owner = blk: {
                var opcode: frontend_bridge.OuterBridgeOpcode = .destroy_return;
                break :blk self.outerOwnerForPendingRunResult(result, &opcode);
            },
            .return_opcode = blk: {
                var opcode: frontend_bridge.OuterBridgeOpcode = .destroy_return;
                _ = self.outerOwnerForPendingRunResult(result, &opcode);
                break :blk opcode;
            },
        };
    }

    pub fn continueCompletionScreen(self: *AppState) !void {
        try self.commitPendingRunResultIfNeeded();
        if (self.failedResultPostLevelHighScoreEntry()) |entry| {
            try self.enterPostLevelHighScoreScreenWithReturn(entry.context, entry.return_owner, entry.return_opcode);
            self.pending_run_result = null;
            self.completion_overlay_active = false;
            self.preserve_completion_screen_reveal_on_enter = false;
            return;
        }
        if (self.pendingRunHighScoreContext()) |context| {
            try self.enterPostLevelHighScoreScreen(context);
            return;
        }
        try self.finishPendingRunReturn();
    }

    pub fn cancelPostLevelHighScoreEntry(self: *AppState) !void {
        try self.finishPostLevelHighScoreReturn();
    }

    fn finishPendingRunReturn(self: *AppState) !void {
        const result = self.pending_run_result orelse {
            self.completion_overlay_active = false;
            self.preserve_completion_screen_reveal_on_enter = false;
            self.setHighScoreBrowseOwner(.postal);
            try self.enterGamePhase(.main_menu);
            return;
        };
        self.clearPostLevelHighScoreEntry();
        self.pending_run_result = null;
        self.completion_overlay_active = false;
        self.preserve_completion_screen_reveal_on_enter = false;
        var opcode: frontend_bridge.OuterBridgeOpcode = .destroy_return;
        const owner = self.outerOwnerForPendingRunResult(result, &opcode);
        try self.runOuterBridgeTransition(opcode, owner);
    }

    fn pendingRunHighScoreContext(self: *const AppState) ?frontend_high_score_screen.PendingEntry {
        const result = self.pending_run_result orelse return null;
        const mode = result.high_score_mode orelse return null;
        const rank = result.high_score_rank orelse return null;
        return .{
            .mode = mode,
            .rank = rank,
        };
    }

    pub fn postLevelHighScoreContext(self: *const AppState) ?frontend_high_score_screen.PendingEntry {
        return switch (self.high_score_screen_owner) {
            .post_level_entry => |context| context,
            .main_menu_browse => null,
        };
    }

    pub fn preparePostLevelHighScoreEntry(self: *AppState, context: frontend_high_score_screen.PendingEntry) void {
        self.clearPostLevelHighScoreEntry();
        self.post_level_high_score_action_index = 1;

        const entry = self.highScoreEntry(context.mode, context.rank) orelse return;
        const existing_name = entry.name();
        const clipped = existing_name[0..@min(existing_name.len, self.post_level_high_score_name_buf.len)];
        @memcpy(self.post_level_high_score_name_buf[0..clipped.len], clipped);
        self.post_level_high_score_name_len = clipped.len;
    }

    pub fn clearPostLevelHighScoreEntry(self: *AppState) void {
        self.post_level_high_score_return_owner = null;
        self.post_level_high_score_return_opcode = .destroy_return;
        @memset(&self.post_level_high_score_name_buf, 0);
        self.post_level_high_score_name_len = 0;
        self.post_level_high_score_action_index = 1;
    }

    pub fn postLevelHighScoreDraft(self: *const AppState) []const u8 {
        return self.post_level_high_score_name_buf[0..self.post_level_high_score_name_len];
    }

    fn collectPostLevelHighScoreTextInput(self: *AppState) void {
        var codepoint = rl.getCharPressed();
        while (codepoint > 0) : (codepoint = rl.getCharPressed()) {
            if (codepoint < 0x20 or codepoint > 0x7e) continue;
            if (self.post_level_high_score_name_len >= high_score.compact_name_capacity) continue;

            const byte: u8 = @intCast(codepoint);
            const normalized = if (byte >= 'a' and byte <= 'z') std.ascii.toUpper(byte) else byte;
            self.post_level_high_score_name_buf[self.post_level_high_score_name_len] = normalized;
            self.post_level_high_score_name_len += 1;
        }

        if (rl.isKeyPressed(.backspace) and self.post_level_high_score_name_len > 0) {
            self.post_level_high_score_name_len -= 1;
            self.post_level_high_score_name_buf[self.post_level_high_score_name_len] = 0;
        }
    }

    pub fn submitPostLevelHighScore(self: *AppState) !void {
        const context = self.postLevelHighScoreContext() orelse {
            if (self.pending_run_result == null and self.post_level_high_score_return_owner == null) {
                try self.enterGamePhase(.main_menu);
                return;
            }
            try self.finishPostLevelHighScoreReturn();
            return;
        };
        const entry = self.highScoreEntryMut(context.mode, context.rank) orelse {
            try self.finishPostLevelHighScoreReturn();
            return;
        };

        entry.setName(trimRight(u8, self.postLevelHighScoreDraft(), " "));
        try self.saveHighScoreTables();
        try self.finishPostLevelHighScoreReturn();
    }

    fn highScoreEntry(self: *const AppState, mode: high_score.Mode, index: usize) ?*const high_score.Entry {
        return switch (mode) {
            .postal => if (index < self.high_score_tables.postal.len) &self.high_score_tables.postal[index] else null,
            .challenge => if (index < self.high_score_tables.challenge.len) &self.high_score_tables.challenge[index] else null,
        };
    }

    fn highScoreEntryMut(self: *AppState, mode: high_score.Mode, index: usize) ?*high_score.Entry {
        return switch (mode) {
            .postal => if (index < self.high_score_tables.postal.len) &self.high_score_tables.postal[index] else null,
            .challenge => if (index < self.high_score_tables.challenge.len) &self.high_score_tables.challenge[index] else null,
        };
    }

    fn routeMapReplayEntry(self: *const AppState) ?*const high_score.Entry {
        const route_index = self.currentRouteMapOpenIndex() orelse return null;
        const completion_index = high_score.completionIndexForRouteIndex(route_index) orelse return null;
        return &self.high_score_tables.completion[completion_index];
    }

    fn clearSelectedReplayCache(self: *AppState) void {
        if (self.selected_replay_cache) |*replay| {
            replay.deinit();
            self.selected_replay_cache = null;
        }
    }

    pub fn setSelectedLevelRecordContext(
        self: *AppState,
        selected_level_record_override: ?frontend_bridge.SelectedLevelRecordOverride,
        selected_level_record_launch: ?frontend_bridge.SelectedLevelRecordLaunch,
    ) !void {
        self.clearSelectedReplayCache();
        self.selected_level_record_override = selected_level_record_override;
        self.selected_level_record_source = if (selected_level_record_launch) |launch| launch.source else null;
        self.selected_level_record_persistent = if (selected_level_record_launch) |launch|
            launch.persistent
        else
            false;
        self.saved_replay_return_outer_owner = if (selected_level_record_launch) |launch|
            frontend_bridge.savedReplayReturnOuterOwnerForLaunch(launch)
        else
            null;
        // PORT(verified): the native selected-record control lane keeps persistence and the
        // saved return owner separate from the launch source. Only use the derived outer
        // return target when there is no recovered saved replay return owner.
        self.selected_level_record_outer_return_target = if (selected_level_record_launch) |launch|
            if (frontend_bridge.savedReplayReturnOuterOwnerForLaunch(launch) == null) launch.outer_return_target else null
        else
            null;
        self.selected_replay_fade_exit_pending = false;

        const source = self.selected_level_record_source orelse return;
        const entry = selected_replay.entryForSource(self, source) orelse return;
        if (entry.replaySampleCount() == 0) return;
        self.selected_replay_cache = try entry.decodeReplay(self.allocator);
    }

    fn handleSelectedReplayFadeExit(self: *AppState) !bool {
        if (!self.selected_replay_fade_exit_pending) return false;

        switch (self.frontend_transition.state) {
            .idle => self.frontend_transition.beginOverlayFadeOut(),
            .black_idle => {
                self.selected_replay_fade_exit_pending = false;
                var opcode: frontend_bridge.OuterBridgeOpcode = .destroy_return;
                const owner = selected_replay.outerOwnerForMarker(self, &opcode) orelse return false;
                try self.runOuterBridgeTransition(opcode, owner);
                self.frontend_transition.completeHandoff();
            },
            else => {},
        }

        return true;
    }

    fn highScoreReplayEntry(self: *const AppState, entry_index: usize) ?*const high_score.Entry {
        const selected_mode = self.activeHighScoreScreenMode();
        return self.highScoreEntry(selected_mode, entry_index);
    }

    pub fn commitPostalRouteProgress(self: *AppState) !bool {
        const highest_available = self.highestAvailableFrontendRouteIndex(.postal);
        if (highest_available == 0) return false;

        const current_index = std.math.clamp(self.active_frontend_level_index, @as(usize, 1), highest_available);
        self.runtime_config.setRouteSelectionIndex(@intCast(current_index));

        const saved_limit: usize = @intCast(self.runtime_config.routeUnlockLimit());
        const next_unlock_limit = nextPostalUnlockLimit(current_index, highest_available, saved_limit);
        const unlocked = current_index < highest_available and next_unlock_limit > std.math.clamp(saved_limit, @as(usize, 1), highest_available);
        if (next_unlock_limit != saved_limit) {
            self.runtime_config.setRouteUnlockLimit(@intCast(next_unlock_limit));
        }
        if (unlocked) {
            self.setGameStatusMessage("Unlocked the next delivery route.");
        }
        try self.saveRuntimeConfig();
        return unlocked;
    }

    fn postalCompletionCommitsHighScore(current_index: usize, highest_available: usize) bool {
        return run_result.postalCompletionCommitsHighScore(current_index, highest_available);
    }

    fn previewDescendingHighScoreRank(entries: []const high_score.Entry, score: u32) ?usize {
        return run_result.previewDescendingHighScoreRank(entries, score);
    }

    fn previewPostalRouteUnlock(current_index: usize, highest_available: usize, saved_limit: usize) bool {
        return run_result.previewPostalRouteUnlock(current_index, highest_available, saved_limit);
    }

    pub fn previewTimeTrialRecordImproved(self: *const AppState, route_index: usize, elapsed_millis: u32) bool {
        const completion_index = high_score.completionIndexForRouteIndex(route_index) orelse return false;
        const current = &self.high_score_tables.completion[completion_index];
        return !current.isActive() or elapsed_millis < current.score;
    }

    fn nextPostalUnlockLimit(current_index: usize, highest_available: usize, saved_limit: usize) usize {
        return run_result.nextPostalUnlockLimit(current_index, highest_available, saved_limit);
    }

    pub fn initialFrontendRouteIndex(self: *const AppState, mode: FrontendLevelMode) usize {
        const available_limit = self.availableFrontendRouteLimit(mode);
        if (available_limit == 0) return 0;
        const saved_index: usize = @intCast(self.runtime_config.routeSelectionIndex());
        return std.math.clamp(saved_index, @as(usize, 1), available_limit);
    }

    pub fn availableFrontendRouteLimit(self: *const AppState, mode: FrontendLevelMode) usize {
        const highest_available = self.highestAvailableFrontendRouteIndex(mode);
        if (highest_available == 0) return 0;
        const saved_limit: usize = @intCast(self.runtime_config.routeUnlockLimit());
        return std.math.clamp(saved_limit, @as(usize, 1), highest_available);
    }

    pub fn highestAvailableFrontendRouteIndex(self: *const AppState, mode: FrontendLevelMode) usize {
        switch (mode) {
            .postal => {
                if (self.resources.catalog.findLevelIndex("LEVELS/ARCADEEXTRA000.TXT") != null) return 0x33;
                return 0x32;
            },
            .time_trial => {
                var scratch: [64]u8 = undefined;
                var last_index: usize = 0x32;
                var extra_index: usize = 0x33;
                while (extra_index < 0x80) : (extra_index += 1) {
                    const path = frontendLevelPath(.time_trial, extra_index, &scratch) catch break;
                    if (self.resources.catalog.findLevelIndex(path) == null) break;
                    last_index = extra_index;
                }
                return last_index;
            },
            .challenge, .tutorial => return 0,
        }
    }

    pub fn syncGamePhaseResources(self: *AppState) !void {
        switch (self.game_phase) {
            .level, .pause_menu => {},
            else => audio.stopVoicePlayback(self),
        }
        switch (self.game_phase) {
            .boot => {
                audio.stopAudioPreview(self);
                self.active_level_segment_index = null;
                self.clearLevelPromptQueue();
                self.mouse_level_lane_target = null;
                self.boot_task_index = 0;
                self.unloadPreloadedBootAssets();
                self.unloadTextScript();
                self.unloadGameBackground();
                try self.loadLoadingScreen();
            },
            .intro => {
                self.active_level_segment_index = null;
                self.clearLevelPromptQueue();
                self.mouse_level_lane_target = null;
                self.unloadLoadingScreen();
                try self.loadGameBackground(intro_background_path);
                try audio.playMusicByPath(self, intro_music_path);
                try self.loadTextScript(intro_script_path);
            },
            .main_menu, .new_game_menu, .high_scores_menu => {
                self.active_level_segment_index = null;
                self.clearLevelPromptQueue();
                self.mouse_level_lane_target = null;
                self.unloadTextScript();
                self.unloadLoadingScreen();
                try self.loadGameBackground(main_menu_background_path);
                try audio.playMusicByPath(self, default_audio_path);
            },
            .challenge_setup_menu => {
                self.active_level_segment_index = null;
                self.clearLevelPromptQueue();
                self.mouse_level_lane_target = null;
                self.challenge_setup_speed_display_value = @as(f32, @floatFromInt(self.runtime_config.challengeReplaySpeedValue())) * 0.01;
                self.challenge_setup_difficulty_display_value = @as(f32, @floatFromInt(self.runtime_config.challengeReplayDifficultyValue())) * 0.01;
                self.unloadTextScript();
                self.unloadLoadingScreen();
                try self.loadGameBackground(main_menu_background_path);
                try audio.playMusicByPath(self, default_audio_path);
            },
            .options_menu => {
                self.options_sound_display_value = self.runtime_config.soundVolume();
                self.options_music_display_value = self.runtime_config.musicVolume();
                self.unloadTextScript();
                self.unloadLoadingScreen();
                if (self.options_return_phase == .pause_menu) {
                    try self.loadCurrentLevelBackground();
                } else {
                    self.active_level_segment_index = null;
                    self.clearLevelPromptQueue();
                    self.mouse_level_lane_target = null;
                    try self.loadGameBackground(main_menu_background_path);
                    try audio.playMusicByPath(self, default_audio_path);
                }
            },
            .pause_menu => {
                self.unloadTextScript();
                self.unloadLoadingScreen();
                try self.loadCurrentLevelBackground();
            },
            .route_map_menu => {
                self.active_level_segment_index = null;
                self.clearLevelPromptQueue();
                self.mouse_level_lane_target = null;
                self.unloadTextScript();
                self.unloadLoadingScreen();
                try self.loadGameBackground(route_map_background_path);
                try audio.playMusicByPath(self, default_audio_path);
            },
            .credits => {
                self.active_level_segment_index = null;
                self.clearLevelPromptQueue();
                self.mouse_level_lane_target = null;
                self.unloadLoadingScreen();
                try self.loadGameBackground(intro_background_path);
                try audio.playMusicByPath(self, intro_music_path);
                try self.loadTextScript(credits_script_path);
            },
            .help => {
                self.active_level_segment_index = null;
                self.clearLevelPromptQueue();
                self.mouse_level_lane_target = null;
                self.unloadTextScript();
                self.unloadLoadingScreen();
                try self.loadGameBackground(help_background_path);
                try audio.playMusicByPath(self, default_audio_path);
            },
            .exit_prompt => {
                self.unloadTextScript();
                self.unloadLoadingScreen();
                if (self.exit_prompt_return_phase == .pause_menu) {
                    try self.loadCurrentLevelBackground();
                } else if (self.exit_prompt_return_phase == .route_map_menu) {
                    self.active_level_segment_index = null;
                    self.clearLevelPromptQueue();
                    self.mouse_level_lane_target = null;
                    try self.loadGameBackground(route_map_background_path);
                    try audio.playMusicByPath(self, default_audio_path);
                } else {
                    self.active_level_segment_index = null;
                    self.clearLevelPromptQueue();
                    self.mouse_level_lane_target = null;
                    try self.loadGameBackground(main_menu_background_path);
                    try audio.playMusicByPath(self, default_audio_path);
                }
            },
            .completion_screen => {
                if (self.preserve_completion_screen_reveal_on_enter) {
                    self.preserve_completion_screen_reveal_on_enter = false;
                } else {
                    self.resetCompletionScreenReveal();
                }
                self.clearLevelPromptQueue();
                self.mouse_level_lane_target = null;
                self.unloadTextScript();
                self.unloadLoadingScreen();
                try self.loadCurrentLevelBackground();
            },
            .thanks_screen => {
                self.thanks_screen_controller.reset();
                self.active_level_segment_index = null;
                self.clearLevelPromptQueue();
                self.mouse_level_lane_target = null;
                self.unloadTextScript();
                self.unloadLoadingScreen();
                try self.loadGameBackground(thanks_screen_background_path);
                try audio.playMusicByPath(self, intro_music_path);
            },
            .level => {
                audio.stopAudioPreview(self);
                self.clearLevelPromptQueue();
                self.mouse_level_lane_target = null;
                self.unloadTextScript();
                self.unloadLoadingScreen();
                try self.loadCurrentLevelBackground();
                const previous_active_level_segment_index = self.active_level_segment_index;
                try self.syncActiveLevelSegment();
                try self.dispatchCurrentRunnerRowMessage(previous_active_level_segment_index, null, true);
            },
        }
    }

    fn loadGameLevel(self: *AppState, level_path: []const u8) !void {
        try level_loader.loadGameLevel(self, level_path);
    }

    fn syncActiveLevelSegment(self: *AppState) !void {
        try level_loader.syncActiveLevelSegment(self);
    }

    fn loadCurrentLevelBackground(self: *AppState) !void {
        const loaded_level = self.current_level orelse {
            self.unloadGameBackground();
            return;
        };
        const background_name = loaded_level.background orelse {
            self.unloadGameBackground();
            return;
        };

        var path_buffer: [256]u8 = undefined;
        const script_path = try std.fmt.bufPrint(&path_buffer, "BACKGROUNDS/{s}", .{background_name});
        try self.loadGameBackground(script_path);
    }

    fn loadGameBackground(self: *AppState, script_path: []const u8) !void {
        self.unloadGameBackground();
        var loaded = if (self.takePreloadedBackground(script_path)) |loaded|
            loaded
        else
            try background.Loaded.loadByPath(self.allocator, &self.resources, script_path);
        self.current_game_background_runtime = background.Runtime.init(&loaded);
        self.current_game_background = loaded;
    }

    fn loadLoadingScreen(self: *AppState) !void {
        self.unloadLoadingScreen();
        self.current_loading_screen = try loading_screen.Loaded.load(&self.resources);
    }

    fn loadTextScript(self: *AppState, path: []const u8) !void {
        self.unloadTextScript();
        self.current_text_script = if (self.takePreloadedTextScript(path)) |loaded|
            loaded
        else
            try self.loadConfiguredTextScriptEntry(path);
    }

    fn loadConfiguredTextScriptEntry(self: *AppState, path: []const u8) !intro.Loaded {
        if (std.ascii.eqlIgnoreCase(path, credits_script_path)) {
            return try intro.loadByPathWithOptions(
                self.allocator,
                &self.resources,
                path,
                .{ .add_remake_credit = self.credits_with_remake },
            );
        }
        return try intro.loadByPath(self.allocator, &self.resources, path);
    }

    fn unloadTextScript(self: *AppState) void {
        if (self.current_text_script) |*script| {
            script.deinit(self.allocator);
            self.current_text_script = null;
        }
    }

    fn unloadLoadingScreen(self: *AppState) void {
        if (self.current_loading_screen) |*loaded_screen| {
            loaded_screen.deinit();
            self.current_loading_screen = null;
        }
    }

    fn takePreloadedBackground(self: *AppState, script_path: []const u8) ?background.Loaded {
        if (std.ascii.eqlIgnoreCase(script_path, intro_background_path)) {
            return takeOptional(background.Loaded, &self.preloaded_intro_background);
        }
        if (std.ascii.eqlIgnoreCase(script_path, main_menu_background_path)) {
            return takeOptional(background.Loaded, &self.preloaded_main_menu_background);
        }
        if (std.ascii.eqlIgnoreCase(script_path, route_map_background_path)) {
            return takeOptional(background.Loaded, &self.preloaded_route_map_background);
        }
        if (std.ascii.eqlIgnoreCase(script_path, help_background_path)) {
            return takeOptional(background.Loaded, &self.preloaded_help_background);
        }
        return null;
    }

    fn takePreloadedTextScript(self: *AppState, path: []const u8) ?intro.Loaded {
        if (std.ascii.eqlIgnoreCase(path, intro_script_path)) {
            return takeOptional(intro.Loaded, &self.preloaded_intro_script);
        }
        if (std.ascii.eqlIgnoreCase(path, credits_script_path)) {
            return takeOptional(intro.Loaded, &self.preloaded_credits_script);
        }
        return null;
    }

    fn currentTextScriptDurationTicks(self: *const AppState) ?u64 {
        const script = self.current_text_script orelse return null;
        return script.durationTicks();
    }

    pub fn toggleFullscreenPreference(self: *AppState) void {
        self.runtime_config.setFullscreenEnabled(!self.runtime_config.fullscreenEnabled());
        self.syncWindowFullscreenPreference();
    }

    fn syncWindowFullscreenPreference(self: *AppState) void {
        const want_fullscreen = self.runtime_config.fullscreenEnabled();
        const is_fullscreen = rl.isWindowFullscreen();
        if (want_fullscreen == is_fullscreen) return;

        rl.toggleFullscreen();
        if (!want_fullscreen) {
            rl.setWindowSize(self.window_size.width, self.window_size.height);
        }
    }

    pub fn currentTextScriptProgress(self: *const AppState) ?f32 {
        const script = self.currentTextScript() orelse return null;
        return script.progressForTicks(self.game_phase_ticks);
    }

    pub fn currentTextScript(self: *const AppState) ?*const intro.Loaded {
        if (self.current_text_script) |*script| {
            return script;
        }
        return null;
    }

    fn maybeQueueAutoScreenshot(self: *AppState) !void {
        try screenshots.maybeQueueAuto(self);
    }

    fn queueScreenshot(self: *AppState, exit_after_capture: bool) !void {
        try screenshots.queue(self, exit_after_capture);
    }

    fn flushQueuedScreenshot(self: *AppState) !void {
        try screenshots.flushQueued(self);
    }

    fn unloadGameBackground(self: *AppState) void {
        if (self.current_game_background) |*loaded_background| {
            loaded_background.deinit();
            self.current_game_background = null;
        }
        self.current_game_background_runtime = null;
    }

    fn setGameStatusMessage(self: *AppState, message: []const u8) void {
        self.game_status_message = message;
        self.game_status_ticks = status_message_duration_ticks;
    }

    pub fn reloadLevel(self: *AppState) !void {
        try level_loader.reloadLevel(self);
    }

    fn nextMathRandomInt15(self: *AppState) u32 {
        return level_loader.nextMathRandomInt15(self);
    }

    fn trackBuildSeedForCurrentLoad(self: *AppState) u32 {
        return level_loader.trackBuildSeedForCurrentLoad(self);
    }

    fn invalidateTrackBuildSeed(self: *AppState) void {
        level_loader.invalidateTrackBuildSeed(self);
    }

    pub fn reloadLevelSegment(self: *AppState) !void {
        try level_loader.reloadLevelSegment(self);
    }

    pub fn activeModel(self: *const AppState) ?*const x2.Uploaded {
        if (self.current_animation) |*animation| {
            return &animation.rendered;
        }
        if (self.current_model) |*model| {
            return model;
        }
        return null;
    }

    pub fn activeLevelSegmentEntry(self: *const AppState) ?*const level.SegmentEntry {
        const loaded_level = self.current_level orelse return null;
        if (loaded_level.segments.len == 0 or self.level_segment_index >= loaded_level.segments.len) return null;
        return &loaded_level.segments[self.level_segment_index];
    }
};

pub fn main(init: std.process.Init) !void {
    var gpa: std.heap.DebugAllocator(.{}) = .init;
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    const options = try parseArgs(allocator, init.minimal.args);
    try runtime_state.ensureRootExists(options.runtime_root_path);
    try std.Io.Dir.cwd().createDirPath(io, options.screenshot_dir);
    var runtime_config_result = try config.Blob.loadFromRuntimeRoot(allocator, options.runtime_root_path);
    if (options.fullscreen) {
        runtime_config_result.blob.setFullscreenEnabled(true);
    }

    const startup_fullscreen = options.fullscreen or
        (runtime_config_result.loaded_from_file and runtime_config_result.blob.fullscreenEnabled());
    runtime_config_result.blob.setFullscreenEnabled(startup_fullscreen);
    // Development default: stay windowed until fullscreen is requested explicitly or a saved runtime config says otherwise.
    rl.setConfigFlags(.{
        .fullscreen_mode = startup_fullscreen,
        .window_hidden = options.hidden_window,
    });
    const initial_window_size = options.window_size_override orelse defaultWindowSizeForCommand(options.command);
    rl.initWindow(initial_window_size.width, initial_window_size.height, "snail");
    // Keep ESC available for game/frontend input; window close still comes from the platform close event.
    rl.setExitKey(.null);
    defer rl.closeWindow();
    if (options.command == .game) {
        rl.hideCursor();
    } else {
        rl.showCursor();
    }

    rl.initAudioDevice();
    const audio_ready = rl.isAudioDeviceReady();
    defer {
        if (audio_ready) {
            rl.closeAudioDevice();
        }
    }

    var state = try AppState.init(allocator, options, runtime_config_result, audio_ready);
    defer state.saveRuntimeConfig() catch |err| std.log.err("failed to save runtime config: {}", .{err});
    defer state.deinit();
    const runtime_start_seconds = rl.getTime();

    if (options.command == .smoke) {
        try state.warmupSmokeTest();
    }

    rl.setTargetFPS(144);
    var frames_left: usize = if (options.command == .smoke) 3 else std.math.maxInt(usize);

    while (!rl.windowShouldClose() and !state.should_exit and frames_left > 0) {
        if (options.timeout_seconds) |timeout_seconds| {
            const timeout_seconds_f64 = @as(f64, @floatFromInt(timeout_seconds));
            if (rl.getTime() - runtime_start_seconds >= timeout_seconds_f64) {
                return error.RunTimeout;
            }
        }
        const frame_delta_seconds = @as(f64, rl.getFrameTime());
        if (options.command == .smoke) {
            frames_left -= 1;
        }

        try state.flushQueuedScreenshot();
        try state.handleInput();
        try state.update(frame_delta_seconds);
        try state.maybeQueueAutoScreenshot();

        rl.beginDrawing();
        defer rl.endDrawing();

        rl.clearBackground(.black);
        try drawUi(&state, options.archive_path);
    }
}

fn drawUi(state: *const AppState, archive_path: []const u8) !void {
    switch (state.command) {
        .game => return drawGameUi(state),
        .debug, .smoke => return debug_browser.drawUi(state, archive_path),
    }
}

fn drawGamePhaseContents(state: *const AppState, bounds: rl.Rectangle, ui_layout: VirtualLayout) !void {
    if (render_phase.usesGameplayBackdrop(state)) {
        if (state.current_game_background) |loaded_background| {
            if (state.current_game_background_runtime) |runtime| {
                _ = runtime.draw(&loaded_background, bounds);
            } else {
                _ = loaded_background.draw(bounds);
            }
            state.background_light_streaks.draw(
                bounds,
                render_phase.lightStreakCamera(state),
                if (state.current_background_light_streak_texture) |loaded| loaded.texture else null,
            );
        } else {
            rl.drawRectangleRec(bounds, .black);
        }
        drawSubgameViewport(state);
    } else if (state.current_game_background) |loaded_background| {
        if (state.current_game_background_runtime) |runtime| {
            switch (state.game_phase) {
                .intro, .credits => runtime.drawStretched(&loaded_background, bounds),
                else => _ = runtime.draw(&loaded_background, bounds),
            }
        } else {
            _ = loaded_background.draw(bounds);
        }
        state.background_light_streaks.draw(
            bounds,
            render_phase.lightStreakCamera(state),
            if (state.current_background_light_streak_texture) |loaded| loaded.texture else null,
        );
    } else {
        rl.drawRectangleRec(bounds, .black);
    }

    switch (state.game_phase) {
        .boot => unreachable,
        .intro => frontend_screens.drawTextScript(state, ui_layout),
        .main_menu => try frontend_screens.drawMainMenu(state, ui_layout),
        .new_game_menu => try frontend_screens.drawNewGameMenu(state, ui_layout),
        .challenge_setup_menu => try frontend_screens.drawChallengeSetupMenu(state, ui_layout),
        .options_menu => try frontend_screens.drawOptionsMenu(state, ui_layout),
        .pause_menu => frontend_screens.drawPauseMenu(state, ui_layout),
        .route_map_menu => try frontend_screens.drawRouteMapMenu(state, ui_layout),
        .high_scores_menu => try frontend_screens.drawHighScoresMenu(state, ui_layout),
        .exit_prompt => frontend_screens.drawExitPrompt(state, ui_layout),
        .completion_screen => try drawCompletionScreenUi(state, ui_layout),
        .thanks_screen => frontend_screens.drawThanks(state, ui_layout),
        .credits => frontend_screens.drawTextScript(state, ui_layout),
        .help => frontend_screens.drawHelp(state, ui_layout),
        .level => try drawGameplayLevelUi(state, ui_layout),
    }
}

fn drawGameUi(state: *const AppState) !void {
    const full_bounds: rl.Rectangle = .{
        .x = 0.0,
        .y = 0.0,
        .width = @floatFromInt(screenWidth()),
        .height = @floatFromInt(screenHeight()),
    };
    const ui_layout = ui.virtualLayout(full_bounds);

    if (state.game_phase == .boot) {
        if (state.current_loading_screen) |loaded_screen| {
            loaded_screen.draw(full_bounds, bootPhaseProgress(state));
        } else {
            rl.drawRectangleRec(full_bounds, .black);
        }
        frontend_screens.drawBoot(state, ui_layout);
        return;
    }

    if (render_phase.frontendUsesCanvas(state)) {
        if (state.frontend_canvas) |canvas| {
            const authored_bounds: rl.Rectangle = .{
                .x = 0.0,
                .y = 0.0,
                .width = ui.authored_width,
                .height = ui.authored_height,
            };
            const authored_layout = ui.virtualLayout(authored_bounds);

            {
                canvas.begin();
                defer canvas.end();
                rl.clearBackground(.black);
                try drawGamePhaseContents(state, authored_bounds, authored_layout);
                frontend_render.drawCursorOverlay(state, authored_layout);
            }

            rl.drawTexturePro(
                canvas.texture,
                .{
                    .x = 0.0,
                    .y = 0.0,
                    .width = @floatFromInt(canvas.texture.width),
                    .height = -@as(f32, @floatFromInt(canvas.texture.height)),
                },
                full_bounds,
                .{ .x = 0.0, .y = 0.0 },
                0.0,
                .white,
            );
        } else {
            try drawGamePhaseContents(state, full_bounds, ui_layout);
            frontend_render.drawCursorOverlay(state, ui_layout);
        }
    } else {
        try drawGamePhaseContents(state, full_bounds, ui_layout);
        frontend_render.drawCursorOverlay(state, ui_layout);
    }

    state.frontend_transition.draw(full_bounds);
}

fn completionFlowOwnerForOutcome(outcome: RunOutcome, mode: ?FrontendLevelMode) CompletionFlowOwner {
    return run_result.completionFlowOwnerForOutcome(outcome, mode);
}

fn outerReturnTargetForOutcome(outcome: RunOutcome, mode: ?FrontendLevelMode) frontend_bridge.OuterReturnTarget {
    // PORT(verified): the ordinary postal completion path still returns through the
    // post-completion Star Map owner. Only the final shipped route upgrades to the
    // thanks-screen path.
    return run_result.outerReturnTargetForOutcome(outcome, mode);
}

fn postalCompletionOuterReturnTarget(current_index: usize, highest_available: usize) frontend_bridge.OuterReturnTarget {
    return run_result.postalCompletionReturnTarget(current_index, highest_available);
}

fn postalCompletionOwner(current_index: usize, highest_available: usize) CompletionFlowOwner {
    return run_result.postalCompletionOwner(current_index, highest_available);
}

// PORT(verified): the native subgame keeps one shared gameplay sim and dispatches most
// mode differences through a small mode-to-config lane in `set_subgame_features` and
// `build_subgame_level`. Keep the mode helpers literal and local instead of routing
// them through an intermediate config struct.
fn runtimeBuildFlagsForFrontendMode(mode: ?FrontendLevelMode) u32 {
    return level_loader.runtimeBuildFlagsForFrontendMode(mode);
}

fn runnerSessionModeForFrontendMode(mode: ?FrontendLevelMode) gameplay.SessionMode {
    return level_loader.runnerSessionModeForFrontendMode(mode);
}

fn completionBonusAppliesForMode(mode: ?FrontendLevelMode) bool {
    // PORT(verified): the native subgame keeps one shared gameplay sim and dispatches most
    // mode differences through a small mode-to-config lane in `set_subgame_features` and
    // `build_subgame_level`. Postal is the only mode that keeps the completion bonus lane.
    return level_loader.completionBonusAppliesForMode(mode);
}

fn routeMapHasReplayEntry(
    mode: ?FrontendLevelMode,
    route_index: usize,
    tables: *const high_score.Tables,
) bool {
    // PORT(verified): `open_galaxy_route` only reveals the replay action when the Star Map
    // controller is in its time-trial mode (`this + 4 == 2`) and the selected completion
    // slot reports state `1`. The closest persisted Windows-equivalent signal in the port
    // is a ScoreC completion entry with replay samples still present.
    if (mode != .time_trial) return false;
    const completion_index = high_score.completionIndexForRouteIndex(route_index) orelse return false;
    return tables.completion[completion_index].has_replay;
}

fn formatElapsedMillis(buffer: []u8, elapsed_millis: u32) ![]const u8 {
    const total_seconds = @divTrunc(elapsed_millis, 1000);
    const minutes = @divTrunc(total_seconds, 60);
    const seconds = @mod(total_seconds, 60);
    const centiseconds = @divTrunc(@mod(elapsed_millis, 1000), 10);
    return std.fmt.bufPrint(buffer, "{d:0>2}:{d:0>2}.{d:0>2}", .{ minutes, seconds, centiseconds });
}

// PORT(partial): this now follows the recovered Windows `cRSubGoldy::ScoreAdd` constants for the
// score events the current runner actually models:
// ring collect (+100 for the scoring ring families), parcel pickup (+100), parcel register (+10), and the
// postal-only completion bonus (+50,000). Health pickup no longer scores in the Windows-targeted path.
// Slug kills (+500), garbage-side score events (+10),
// jetpack/speed-up scoring, and the rest of the original `cRSubGoldy::AI()` path remain unported.
fn bootPhaseProgress(state: *const AppState) f32 {
    if (boot_tasks.len == 0) return 1.0;
    return std.math.clamp(
        @as(f32, @floatFromInt(state.boot_task_index)) / @as(f32, @floatFromInt(boot_tasks.len)),
        0.0,
        1.0,
    );
}

fn drawGameplayLevelUi(state: *const AppState, layout: VirtualLayout) !void {
    drawSubgameViewport(state);

    if (state.level_runner) |runner| {
        if (state.isTutorialGameplay()) {
            try drawTutorialGameplayUi(state, layout, runner);
        } else {
            try gameplay_hud.drawStandardHud(state, layout, runner);
            gameplay_hud.drawProgressBar(state, layout, runner);
            gameplay_hud.drawStatusWidgets(state, layout, runner);
            if (state.current_track_preview) |loaded_track_preview| {
                const camera = subgame_camera.levelCamera(&state.subgame_camera, &loaded_track_preview, state.subgame_camera.fov_degrees);
                try gameplay_hud.drawRowEventWidget(state, layout, runner, camera);
            }
            try gameplay_prompt_overlay.drawGameplayStack(state, layout, &state.level_prompt_queue);
        }
    }

    if (state.completionScreenOverlayActive()) {
        try drawCompletionScreenUi(state, layout);
    }
}

fn drawTutorialGameplayUi(state: *const AppState, layout: VirtualLayout, runner: gameplay.Runner) !void {
    try gameplay_hud.drawTutorialHud(state, layout, runner);
    gameplay_hud.drawProgressBar(state, layout, runner);
    gameplay_hud.drawTutorialLives(state, layout, runner.visible_life_stock);
    gameplay_hud.drawDamageGauge(state, layout, runner);
    if (state.gameplay_click_start_active) {
        if (!state.tutorialClickStartCutsceneActive()) {
            gameplay_prompt_overlay.drawStaticWidget(state, layout, "Click to Start", true);
        }
        return;
    }
    try gameplay_prompt_overlay.drawTutorialStack(state, layout, &state.level_prompt_queue);
}

fn formatScoreWithCommas(buffer: []u8, score: u32) ![:0]const u8 {
    var digits_buffer: [16]u8 = undefined;
    const digits = try std.fmt.bufPrint(&digits_buffer, "{d}", .{score});

    var write_index: usize = 0;
    const remainder = digits.len % 3;
    for (digits, 0..) |digit, index| {
        if (index != 0 and (index % 3 == remainder or (remainder == 0 and index % 3 == 0))) {
            if (write_index >= buffer.len - 1) return error.NoSpaceLeft;
            buffer[write_index] = ',';
            write_index += 1;
        }
        if (write_index >= buffer.len - 1) return error.NoSpaceLeft;
        buffer[write_index] = digit;
        write_index += 1;
    }
    if (write_index >= buffer.len) return error.NoSpaceLeft;
    buffer[write_index] = 0;
    return buffer[0..write_index :0];
}

fn drawCompletionScreenUi(state: *const AppState, layout: VirtualLayout) !void {
    drawSubgameViewport(state);
    const result = state.pending_run_result orelse return;
    const summary = completionSummary(result);
    if (result.outcome == .completed) {
        try frontend_completion_screen.drawCompleted(
            state,
            layout,
            summary,
            state.completionBonusVisible(result),
            state.completion_continue_button_state,
            state.completionContinueVisible(),
        );
    } else {
        try frontend_completion_screen.drawFailed(
            state,
            layout,
            summary,
            state.completion_continue_button_state,
        );
    }
}

fn drawSubgameViewport(state: *const AppState) void {
    const loaded_track_preview = state.current_track_preview orelse return;
    const runner = state.level_runner;
    const selected_segment_index = if (runner) |live_runner|
        if (loaded_track_preview.locateRow(live_runner.current_global_row)) |row_location|
            row_location.segment_index
        else
            0
    else if (loaded_track_preview.segments.len != 0 and state.level_segment_index < loaded_track_preview.segments.len)
        state.level_segment_index
    else
        0;
    const camera = if (runner != null)
        subgame_camera.levelCamera(&state.subgame_camera, &loaded_track_preview, state.subgame_camera.fov_degrees)
    else
        loaded_track_preview.previewCamera(@floatCast(state.render_time_seconds), selected_segment_index);
    camera.begin();
    defer rl.endMode3D();

    if (state.current_game_track_scene) |*scene| {
        scene.drawGameplay(&loaded_track_preview, selected_segment_index);
    } else {
        loaded_track_preview.draw(selected_segment_index);
    }
    const live_runner = runner orelse return;
    if (state.gameplay_click_start_active) {
        drawGameplayTurbo(state, &loaded_track_preview, live_runner, camera);
        return;
    }
    drawGameplayRuntimeActors(state, &loaded_track_preview, live_runner, camera);
    drawGameplayBarrier(state, &loaded_track_preview, live_runner);
    drawGameplayTurbo(state, &loaded_track_preview, live_runner, camera);
}
const BillboardUv = struct {
    left: f32,
    top: f32,
    right: f32,
    bottom: f32,
};

const gameplay_billboard_alpha_cutout_fragment_shader: [:0]const u8 =
    \\#version 330
    \\in vec2 fragTexCoord;
    \\in vec4 fragColor;
    \\uniform sampler2D texture0;
    \\uniform vec4 colDiffuse;
    \\out vec4 finalColor;
    \\
    \\void main() {
    \\    vec4 color = texture(texture0, fragTexCoord) * colDiffuse * fragColor;
    \\    if (color.a <= 0.05) discard;
    \\    finalColor = color;
    \\}
;

fn loadGameplayBillboardCutoutShader() !rl.Shader {
    return try rl.loadShaderFromMemory(null, gameplay_billboard_alpha_cutout_fragment_shader);
}

fn drawGameplayRuntimeActors(
    state: *const AppState,
    loaded_track_preview: *const track.LoadedLevelPreview,
    runner: gameplay.Runner,
    camera: rl.Camera3D,
) void {
    if (loaded_track_preview.max_width == 0 or loaded_track_preview.total_rows == 0) return;

    const current_row = loaded_track_preview.rowIndexAtWorldZ(runner.row_position);
    const start_row = current_row -| 1;
    const end_row = @min(loaded_track_preview.total_rows, current_row + 72);

    var global_row = end_row;
    while (global_row > start_row) {
        global_row -= 1;
        if (!gameplay_render_policy.actorRowVisible(runner, global_row)) continue;
        const row_location = loaded_track_preview.locateRow(global_row) orelse continue;
        for (0..row_location.row.cells.len) |lane_index| {
            const sample = loaded_track_preview.gameplayCellSampleAt(global_row, lane_index) orelse continue;
            switch (sample.kind) {
                .slug => drawGameplaySlugActor(state, loaded_track_preview, runner, camera, global_row, lane_index),
                .ring => {
                    if (gameplay_render_policy.staticRingVisible(loaded_track_preview, row_location, loaded_track_preview.runtimeTileAt(global_row, lane_index))) {
                        drawGameplayStaticRingActor(state, loaded_track_preview, camera, row_location, lane_index);
                    }
                },
                .health, .jetpack, .attachment_probe, .attachment_entry, .trampoline, .garbage, .salt => {},
            }
            if (row_location.row.cells[lane_index] == '=') {
                drawGameplayTurretActor(state, loaded_track_preview, runner, global_row, lane_index);
            }
        }
    }

    for (runner.activeTrackParcels()) |parcel| {
        if (!parcel.active()) continue;
        if (!gameplay_render_policy.actorRowVisible(runner, parcel.row)) continue;
        drawGameplayTrackParcelActor(state, camera, parcel);
    }

    for (runner.activeRuntimeHazards()) |hazard| {
        if (!gameplay_render_policy.hazardVisible(runner, hazard)) continue;
        switch (hazard.kind) {
            .garbage => {
                drawGameplayGarbageActor(state, loaded_track_preview, camera, hazard);
            },
        }
    }

    // PORT(verified): dedicated `cRSalt`-shaped pool render. Each active
    // slot owns its own world position + yaw and is drawn with the shared
    // `drawGameplaySaltSlotActor` helper that reads the same salt mesh path
    // as the legacy branch.
    for (runner.activeRuntimeSalts()) |slot| {
        if (!gameplay_render_policy.saltSlotVisible(runner, slot)) continue;
        drawGameplaySaltSlotActor(state, camera, slot);
    }

    for (runner.activeRuntimePickups()) |pickup| {
        if (!gameplay_render_policy.pickupVisible(runner, pickup)) continue;
        switch (pickup.kind) {
            .health => drawGameplayHealthPickupActor(state, camera, pickup),
            .jetpack => drawGameplayJetpackPickupActor(state, camera, pickup),
        }
    }

    for (runner.activeRuntimeRingEffects()) |effect| {
        if (!gameplay_render_policy.ringEffectVisible(runner, effect)) continue;
        drawGameplayRuntimeRingEffectActor(state, camera, effect);
    }

    for (runner.activeProjectiles()) |projectile| {
        drawGameplayProjectileActor(state, projectile);
    }

    drawGameplayEffects(state, camera);
}

fn drawGameplaySlugActor(
    state: *const AppState,
    preview: *const track.LoadedLevelPreview,
    runner: gameplay.Runner,
    camera: rl.Camera3D,
    global_row: usize,
    lane_index: usize,
) void {
    if (runner.isSlugDefeated(global_row, lane_index)) return;

    // Native slug hazards spawn a world sprite with size lanes +0x60/+0x64 both seeded to 2.0,
    // and `draw_sprite_quad` treats that blended value as the quad half-extent.
    const slug_sprite_half_extent: f32 = 2.0;
    const slug_sprite_world_size: f32 = slug_sprite_half_extent * 2.0;
    const slug_sprite_y_offset: f32 = 1.7;
    // Native `spawn_slug_hazard` allocates the live sprite with texture ref 118 (`SLUG000`), and
    // `update_slug_hazard_ai` only switches to 119/120 during non-default state-machine branches.
    // So authored live slugs should not free-run a local blink in the port.
    const loaded_texture = state.current_gameplay_sprites.slug_frames[0] orelse return;
    const position = gameplayLaneWorldPosition(preview, global_row, lane_index, slug_sprite_y_offset);
    drawGameplayBillboardTextureRect(
        loaded_texture.texture,
        .{ .x = 0.0, .y = 0.0, .width = @floatFromInt(loaded_texture.texture.width), .height = @floatFromInt(loaded_texture.texture.height) },
        position,
        slug_sprite_world_size,
        slug_sprite_world_size,
        camera,
        state.gameplay_billboard_shader,
        .white,
    );
}

fn drawGameplayGarbageActor(
    state: *const AppState,
    preview: *const track.LoadedLevelPreview,
    camera: rl.Camera3D,
    hazard: gameplay_runtime_entities.Hazard,
) void {
    _ = preview;
    if (hazard.state == .inactive) return;
    const variant_index = @as(usize, @intCast((hazard.row + hazard.lane * 3) % gameplay_assets.gameplay_garbage_sprite_paths.len));
    const loaded_texture = state.current_gameplay_sprites.garbage_variants[variant_index] orelse return;
    drawGameplayBillboardTextureRectRolled(
        loaded_texture.texture,
        .{ .x = 0.0, .y = 0.0, .width = @floatFromInt(loaded_texture.texture.width), .height = @floatFromInt(loaded_texture.texture.height) },
        hazard.world_position,
        hazard.presentation_scale,
        hazard.presentation_scale,
        camera,
        state.gameplay_billboard_shader,
        hazard.presentation_phase + (@as(f32, @floatCast(state.render_time_seconds)) * 1.75),
        .{ .r = 255, .g = 255, .b = 255, .a = if (hazard.state == .active) 232 else 255 },
    );
}

fn drawGameplaySaltSlotActor(
    state: *const AppState,
    camera: rl.Camera3D,
    slot: gameplay_runtime_entities.SaltSlot,
) void {
    if (slot.state != .active) return;
    drawGameplaySaltVisual(state, camera, slot.world_position, slot.yaw_radians);
}

fn drawGameplaySaltVisual(
    state: *const AppState,
    camera: rl.Camera3D,
    world_position: rl.Vector3,
    yaw_radians: f32,
) void {
    const presentation_alpha: u8 = 232;
    if (state.current_gameplay_salt_model) |*model| {
        const yaw_sin = std.math.sin(yaw_radians);
        const yaw_cos = std.math.cos(yaw_radians);
        const right: rl.Vector3 = .{ .x = yaw_cos, .y = 0.0, .z = -yaw_sin };
        const up: rl.Vector3 = .{ .x = 0.0, .y = 1.0, .z = 0.0 };
        const forward: rl.Vector3 = .{ .x = yaw_sin, .y = 0.0, .z = yaw_cos };
        const world_transform = modelTransformFromBasis(world_position, right, up, forward);
        const local_offset = rl.Matrix.translate(
            -model.bounds.center.x,
            -model.bounds.center.y,
            -model.bounds.center.z,
        );
        const scale_value = 0.46;
        const scale = rl.Matrix.scale(scale_value, scale_value, scale_value);
        model.drawTintedEx(
            world_transform.multiply(local_offset).multiply(scale),
            .{ .r = 255, .g = 255, .b = 255, .a = presentation_alpha },
        );
        return;
    }

    const icon = state.ui_font.slots[game_font.IconGlyph.salt.slotIndex()];
    drawGameplayBillboardTextureRect(
        state.ui_font.texture,
        .{
            .x = icon.source_x,
            .y = icon.source_y,
            .width = icon.source_width,
            .height = icon.source_height,
        },
        world_position,
        0.58,
        0.72,
        camera,
        state.gameplay_billboard_shader,
        .{ .r = 144, .g = 198, .b = 255, .a = presentation_alpha },
    );
}

fn drawGameplayTurretActor(
    state: *const AppState,
    preview: *const track.LoadedLevelPreview,
    runner: gameplay.Runner,
    global_row: usize,
    lane_index: usize,
) void {
    const flash_ticks = runner.turretFlashTicksAt(global_row, lane_index);
    const model = blk: {
        if (flash_ticks > 0) {
            if (state.current_gameplay_blaster_top_models.fire) |*fire_model| break :blk fire_model.*;
        }
        break :blk state.current_gameplay_turret_model orelse return;
    };
    const floor_height = preview.floorHeightAtCellCenter(global_row, lane_index) orelse 0.0;
    const position = preview.worldPositionForLane(
        @as(f32, @floatFromInt(lane_index)) + 0.5,
        @as(f32, @floatFromInt(global_row)),
        floor_height + 0.18,
    );
    drawGameplayUploadedModel(
        model,
        position,
        .{ .x = 1.0, .y = 0.0, .z = 0.0 },
        .{ .x = 0.0, .y = 1.0, .z = 0.0 },
        .{ .x = 0.0, .y = 0.0, .z = 1.0 },
        .{ .x = 0.34, .y = 0.34, .z = 0.34 },
        null,
    );
}

fn drawGameplayHealthPickupActor(
    state: *const AppState,
    camera: rl.Camera3D,
    pickup: gameplay_runtime_entities.Pickup,
) void {
    const loaded_texture = state.current_gameplay_sprites.health orelse return;
    drawGameplayBillboardTexture(loaded_texture.texture, pickup.presentation_position, 0.52, 0.52, camera, state.gameplay_billboard_shader, .white);
}

fn drawGameplayJetpackPickupActor(
    state: *const AppState,
    camera: rl.Camera3D,
    pickup: gameplay_runtime_entities.Pickup,
) void {
    const frame_index: usize = @intFromFloat(@mod(@floor(state.render_time_seconds * 8.0), @as(f64, @floatFromInt(gameplay_assets.gameplay_jetpack_sprite_paths.len))));
    const loaded_texture = state.current_gameplay_sprites.jetpack_frames[frame_index] orelse return;
    drawGameplayBillboardTexture(loaded_texture.texture, pickup.presentation_position, 0.64, 0.88, camera, state.gameplay_billboard_shader, .white);
}

fn drawGameplayStaticRingActor(
    state: *const AppState,
    preview: *const track.LoadedLevelPreview,
    camera: rl.Camera3D,
    row_location: track.RowLocation,
    lane_index: usize,
) void {
    const ring_kind = if (row_location.row.annotation) |annotation|
        switch (annotation) {
            .ring => |kind| kind,
            else => segment.RingKind.normal,
        }
    else
        segment.RingKind.normal;
    const position = gameplayLaneWorldPosition(preview, row_location.global_row, lane_index, 0.72);
    switch (ring_kind) {
        .none => {},
        .normal => if (state.current_gameplay_sprites.ring) |loaded_texture| {
            drawGameplayBillboardTexture(loaded_texture.texture, position, 0.46, 0.46, camera, state.gameplay_billboard_shader, .{ .r = 255, .g = 246, .b = 180, .a = 232 });
        },
        .powerup => if (state.current_gameplay_sprites.powerup) |loaded_texture| {
            drawGameplayBillboardTexture(loaded_texture.texture, position, 0.64, 0.64, camera, state.gameplay_billboard_shader, .white);
        },
        .explode => if (state.current_gameplay_sprites.ring_big) |loaded_texture| {
            drawGameplayBillboardTexture(loaded_texture.texture, position, 0.72, 0.72, camera, state.gameplay_billboard_shader, .{ .r = 255, .g = 220, .b = 120, .a = 232 });
        },
        .slow => if (state.current_gameplay_sprites.slow_ring) |loaded_texture| {
            drawGameplayBillboardTexture(loaded_texture.texture, position, 0.5, 0.5, camera, state.gameplay_billboard_shader, .white);
        },
    }
}

fn drawGameplayRuntimeRingEffectActor(
    state: *const AppState,
    camera: rl.Camera3D,
    effect: gameplay_runtime_entities.RingEffect,
) void {
    const ring_kind = gameplay.nativeRuntimeRingKindLabel(effect.kind) orelse return;
    const position = effect.presentation_position;
    const scale = effect.presentation_scale;
    switch (ring_kind) {
        .none => {},
        .normal => if (state.current_gameplay_sprites.ring) |loaded_texture| {
            drawGameplayBillboardTexture(loaded_texture.texture, position, 0.46 * scale, 0.46 * scale, camera, state.gameplay_billboard_shader, .{ .r = 255, .g = 246, .b = 180, .a = 232 });
        },
        .powerup => if (state.current_gameplay_sprites.powerup) |loaded_texture| {
            drawGameplayBillboardTexture(loaded_texture.texture, position, 0.64 * scale, 0.64 * scale, camera, state.gameplay_billboard_shader, .white);
        },
        .explode => if (state.current_gameplay_sprites.ring_big) |loaded_texture| {
            drawGameplayBillboardTexture(loaded_texture.texture, position, 0.72 * scale, 0.72 * scale, camera, state.gameplay_billboard_shader, .{ .r = 255, .g = 220, .b = 120, .a = 232 });
        },
        .slow => if (state.current_gameplay_sprites.slow_ring) |loaded_texture| {
            drawGameplayBillboardTexture(loaded_texture.texture, position, 0.5 * scale, 0.5 * scale, camera, state.gameplay_billboard_shader, .white);
        },
    }
}

fn drawGameplayTrackParcelActor(
    state: *const AppState,
    camera: rl.Camera3D,
    parcel: gameplay_runtime_entities.TrackParcel,
) void {
    const loaded_texture = state.current_gameplay_sprites.parcel orelse return;
    const position = parcel.presentationPosition();
    const scale = parcel.presentationScale();
    drawGameplayBillboardTexture(
        loaded_texture.texture,
        position,
        0.56 * scale,
        0.56 * scale,
        camera,
        state.gameplay_billboard_shader,
        if (parcel.parcel_id == 0)
            .white
        else
            .{ .r = 196, .g = 255, .b = 196, .a = 232 },
    );
}

fn gameplayLaneWorldPosition(preview: *const track.LoadedLevelPreview, global_row: usize, lane_index: usize, y_offset: f32) rl.Vector3 {
    const floor_height = preview.floorHeightAtCellCenter(global_row, lane_index) orelse 0.0;
    return preview.worldPositionForLane(@as(f32, @floatFromInt(lane_index)) + 0.5, @as(f32, @floatFromInt(global_row)), floor_height + y_offset);
}

fn drawGameplayBillboardTexture(
    texture: rl.Texture2D,
    position: rl.Vector3,
    width: f32,
    height: f32,
    camera: rl.Camera3D,
    shader: ?rl.Shader,
    tint: rl.Color,
) void {
    drawGameplayBillboardTextureRect(
        texture,
        .{ .x = 0.0, .y = 0.0, .width = @floatFromInt(texture.width), .height = @floatFromInt(texture.height) },
        position,
        width,
        height,
        camera,
        shader,
        tint,
    );
}

fn drawGameplayBillboardTextureRectRolled(
    texture: rl.Texture2D,
    source: rl.Rectangle,
    position: rl.Vector3,
    width: f32,
    height: f32,
    camera: rl.Camera3D,
    shader: ?rl.Shader,
    roll_radians: f32,
    tint: rl.Color,
) void {
    const forward = normalizeVector3(.{
        .x = camera.target.x - camera.position.x,
        .y = camera.target.y - camera.position.y,
        .z = camera.target.z - camera.position.z,
    });
    var right = crossVector3(forward, camera.up);
    if (vectorLength(right) <= 0.0001) {
        right = .{ .x = 1.0, .y = 0.0, .z = 0.0 };
    } else {
        right = normalizeVector3(right);
    }
    var up = crossVector3(right, forward);
    if (vectorLength(up) <= 0.0001) {
        up = .{ .x = 0.0, .y = 1.0, .z = 0.0 };
    } else {
        up = normalizeVector3(up);
    }

    if (@abs(roll_radians) > 0.0001) {
        const roll_cos = std.math.cos(roll_radians);
        const roll_sin = std.math.sin(roll_radians);
        const rotated_right: rl.Vector3 = .{
            .x = (right.x * roll_cos) - (up.x * roll_sin),
            .y = (right.y * roll_cos) - (up.y * roll_sin),
            .z = (right.z * roll_cos) - (up.z * roll_sin),
        };
        const rotated_up: rl.Vector3 = .{
            .x = (right.x * roll_sin) + (up.x * roll_cos),
            .y = (right.y * roll_sin) + (up.y * roll_cos),
            .z = (right.z * roll_sin) + (up.z * roll_cos),
        };
        right = rotated_right;
        up = rotated_up;
    }

    const half_width = width * 0.5;
    const half_height = height * 0.5;
    const top_left: rl.Vector3 = .{
        .x = position.x - (right.x * half_width) + (up.x * half_height),
        .y = position.y - (right.y * half_width) + (up.y * half_height),
        .z = position.z - (right.z * half_width) + (up.z * half_height),
    };
    const bottom_left: rl.Vector3 = .{
        .x = position.x - (right.x * half_width) - (up.x * half_height),
        .y = position.y - (right.y * half_width) - (up.y * half_height),
        .z = position.z - (right.z * half_width) - (up.z * half_height),
    };
    const bottom_right: rl.Vector3 = .{
        .x = position.x + (right.x * half_width) - (up.x * half_height),
        .y = position.y + (right.y * half_width) - (up.y * half_height),
        .z = position.z + (right.z * half_width) - (up.z * half_height),
    };
    const top_right: rl.Vector3 = .{
        .x = position.x + (right.x * half_width) + (up.x * half_height),
        .y = position.y + (right.y * half_width) + (up.y * half_height),
        .z = position.z + (right.z * half_width) + (up.z * half_height),
    };
    const uv = BillboardUv{
        .left = source.x / @as(f32, @floatFromInt(texture.width)),
        .top = source.y / @as(f32, @floatFromInt(texture.height)),
        .right = (source.x + source.width) / @as(f32, @floatFromInt(texture.width)),
        .bottom = (source.y + source.height) / @as(f32, @floatFromInt(texture.height)),
    };
    drawGameplayBillboardQuad(texture, top_left, bottom_left, bottom_right, top_right, uv, shader, tint);
}

fn drawGameplayBillboardTextureRect(
    texture: rl.Texture2D,
    source: rl.Rectangle,
    position: rl.Vector3,
    width: f32,
    height: f32,
    camera: rl.Camera3D,
    shader: ?rl.Shader,
    tint: rl.Color,
) void {
    drawGameplayBillboardTextureRectRolled(texture, source, position, width, height, camera, shader, 0.0, tint);
}

fn drawGameplayBillboardQuad(
    texture: rl.Texture2D,
    top_left: rl.Vector3,
    bottom_left: rl.Vector3,
    bottom_right: rl.Vector3,
    top_right: rl.Vector3,
    uv: BillboardUv,
    shader: ?rl.Shader,
    tint: rl.Color,
) void {
    if (shader) |cutout_shader| {
        rl.beginShaderMode(cutout_shader);
        defer rl.endShaderMode();
    }
    rl.gl.rlDisableDepthMask();
    defer rl.gl.rlEnableDepthMask();
    rl.gl.rlSetTexture(texture.id);
    defer rl.gl.rlSetTexture(0);

    rl.gl.rlBegin(rl.gl.rl_quads);
    defer rl.gl.rlEnd();
    rl.gl.rlColor4ub(tint.r, tint.g, tint.b, tint.a);

    rl.gl.rlTexCoord2f(uv.left, uv.top);
    rl.gl.rlVertex3f(top_left.x, top_left.y, top_left.z);
    rl.gl.rlTexCoord2f(uv.left, uv.bottom);
    rl.gl.rlVertex3f(bottom_left.x, bottom_left.y, bottom_left.z);
    rl.gl.rlTexCoord2f(uv.right, uv.bottom);
    rl.gl.rlVertex3f(bottom_right.x, bottom_right.y, bottom_right.z);
    rl.gl.rlTexCoord2f(uv.right, uv.top);
    rl.gl.rlVertex3f(top_right.x, top_right.y, top_right.z);
}

fn drawGameplayBarrier(state: *const AppState, loaded_track_preview: *const track.LoadedLevelPreview, runner: gameplay.Runner) void {
    const loaded_object = state.current_gameplay_barrier_object orelse return;
    // Native barrier visibility follows `Game.level_mode == FrontendLevelMode.tutorial`
    // (= 7): `initialize_tutorial` (0x448da0) sets `runtime_flags |= 0x600000` and
    // `set_subgame_features` (0x435df0) maps the tutorial mode to runtime_flags
    // 0xe4cfff which also includes those bits. NoFall segments additionally expose
    // the barrier in non-tutorial modes via the per-row annotation.
    const tutorial_active = runner.session_mode == .tutorial or state.isTutorialLevel();
    const barrier_active = tutorial_active or runner.current_annotation == .no_fall;
    if (!barrier_active) return;

    const runner_position = runner.worldPosition(loaded_track_preview, 0.4);
    // `update_barrier_ai` 0x440f80 updates only the object-space Y/Z slots:
    // `y = 0.4`, `z = owner->+0x70` (player z). The barrier mesh is authored in
    // world orientation, so the draw should follow the owner without inventing
    // an extra upright rotation.
    const world_transform = rl.Matrix.translate(0.0, 0.4, runner_position.z);
    // What we know from the native decompile:
    //
    //   - The mesh is two thin horizontal quads at x=±4.5, y=±0.3, z=-18..+40
    //     (see OBJECTS/BARRIER/_OBJECT.TXT; the Wii and Android ports ship the
    //     same vertices).
    //   - BARRIER.TGA is a 4x4 vertical gradient (dark blue → bright blue →
    //     dark blue) with alpha=255 everywhere.
    //   - Windows barrier setup stores object tint `(1, 1, 1, 0.8)` and blend
    //     preset `7` in `initialize_game_assets_and_world` (0x40acf0).
    //   - Windows texture load `sub_412a70` tags 32-bit TGA textures with
    //     `TextureRef.flags |= 0x10000`; `render_object` (0x4126c0) only enters
    //     `set_blend_mode(...)` when object alpha != 1 and that flag is set.
    //     BARRIER.TGA is 32-bit, so the barrier definitely takes the blended
    //     grouped-object path.
    //   - Windows `set_blend_mode(7)` resolves to additive blending
    //     (`SRC=ONE`, `DEST=ONE`).
    //   - Android barrier setup stores the same tint `(1, 1, 1, 0.8)` and
    //     assigns blend preset `3`; `G0SetBlend(3)` is also additive and
    //     explicitly disables depth writes for the draw.
    //   - Native grouped-object draws keep back-face culling enabled unless the
    //     object sets the `0x100000` opt-out flag. Barrier init does not set it.
    //
    // Port choice:
    // Use the recovered additive path and disable depth writes for the draw so
    // the translucent barrier does not stamp the later scene. This matches the
    // Android renderer directly, and it is the only way the Windows additive
    // barrier can behave without the Z corruption we saw in the port.
    //
    // We still disable back-face culling in the port. The authored barrier
    // quads point outward from the track center (`+X` on the right strip,
    // `-X` on the left strip), so our raylib/OpenGL mesh winding hides the
    // interior faces when culling is left on.
    rl.beginBlendMode(.additive);
    defer rl.endBlendMode();
    rl.gl.rlDisableDepthMask();
    defer rl.gl.rlEnableDepthMask();
    rl.gl.rlDisableBackfaceCulling();
    defer rl.gl.rlEnableBackfaceCulling();
    const barrier_tint = rl.Color{ .r = 255, .g = 255, .b = 255, .a = 204 };
    loaded_object.drawTintedEx(world_transform, barrier_tint);
}

fn drawGameplayProjectileActor(state: *const AppState, projectile: gameplay.Projectile) void {
    const forward = normalizeVector3(.{
        .x = projectile.dir_x,
        .y = projectile.dir_y,
        .z = projectile.dir_z,
    });
    var up: rl.Vector3 = .{ .x = 0.0, .y = 1.0, .z = 0.0 };
    if (@abs(dotVector3(forward, up)) > 0.95) {
        up = .{ .x = 1.0, .y = 0.0, .z = 0.0 };
    }

    var right = crossVector3(up, forward);
    if (vectorLength(right) <= 0.0001) {
        right = .{ .x = 1.0, .y = 0.0, .z = 0.0 };
    } else {
        right = normalizeVector3(right);
    }
    const corrected_up = normalizeVector3(crossVector3(forward, right));
    const position: rl.Vector3 = .{
        .x = projectile.world_x,
        .y = projectile.world_y,
        .z = projectile.world_z,
    };
    const world_transform = modelTransformFromBasis(position, right, corrected_up, forward);
    const local_offset = rl.Matrix.translate(
        0.0,
        0.0,
        0.0,
    );
    _ = local_offset;

    switch (projectile.kind) {
        .turbo => {
            const loaded_object = state.current_gameplay_lazer_object orelse return;
            const offset = rl.Matrix.translate(
                -loaded_object.center.x,
                -loaded_object.center.y,
                -loaded_object.center.z,
            );
            const scale = rl.Matrix.scale(0.18, 0.18, 0.18);
            loaded_object.drawTintedEx(
                world_transform.multiply(offset).multiply(scale),
                .{ .r = 170, .g = 220, .b = 255, .a = 232 },
            );
        },
        .laser => {
            const loaded_object = state.current_gameplay_vapour_lazer_object orelse state.current_gameplay_lazer_object orelse return;
            const offset = rl.Matrix.translate(
                -loaded_object.center.x,
                -loaded_object.center.y,
                -loaded_object.center.z,
            );
            const scale = rl.Matrix.scale(0.22, 0.22, 0.22);
            loaded_object.drawTintedEx(
                world_transform.multiply(offset).multiply(scale),
                .{ .r = 180, .g = 255, .b = 255, .a = 236 },
            );
        },
        .enemy_laser => {
            const loaded_object = state.current_gameplay_vapour_lazer_object orelse state.current_gameplay_lazer_object orelse return;
            const offset = rl.Matrix.translate(
                -loaded_object.center.x,
                -loaded_object.center.y,
                -loaded_object.center.z,
            );
            const scale = rl.Matrix.scale(0.18, 0.18, 0.18);
            loaded_object.drawTintedEx(
                world_transform.multiply(offset).multiply(scale),
                .{ .r = 255, .g = 136, .b = 96, .a = 236 },
            );
        },
        .rocket => {
            const model = state.current_gameplay_rocket_model orelse {
                const loaded_object = state.current_gameplay_lazer_object orelse return;
                const offset = rl.Matrix.translate(
                    -loaded_object.center.x,
                    -loaded_object.center.y,
                    -loaded_object.center.z,
                );
                const scale = rl.Matrix.scale(0.22, 0.22, 0.22);
                loaded_object.drawTintedEx(
                    world_transform.multiply(offset).multiply(scale),
                    .{ .r = 255, .g = 224, .b = 164, .a = 236 },
                );
                return;
            };
            drawGameplayUploadedModel(
                model,
                position,
                right,
                corrected_up,
                forward,
                .{ .x = 0.16, .y = 0.16, .z = 0.16 },
                null,
            );
        },
    }
}

fn drawGameplayEffects(state: *const AppState, camera: rl.Camera3D) void {
    for (0..state.gameplay_effects.count) |index| {
        const effect = state.gameplay_effects.items[index];
        if (!effect.active or effect.ticks_remaining == 0) continue;
        const loaded_texture = switch (effect.kind) {
            .explode_big => state.current_gameplay_sprites.explode_big,
            .explode_small => state.current_gameplay_sprites.explode_small,
            .slug_goo => state.current_gameplay_sprites.slug_goo,
            .smoke => state.current_gameplay_sprites.smoke,
        } orelse continue;
        drawGameplayBillboardTexture(
            loaded_texture.texture,
            effect.position,
            effect.width,
            effect.height,
            camera,
            state.gameplay_billboard_shader,
            effect.tint,
        );
    }
}

fn drawGameplayTurbo(
    state: *const AppState,
    loaded_track_preview: *const track.LoadedLevelPreview,
    runner: gameplay.Runner,
    camera: rl.Camera3D,
) void {
    const model = gameplay_resources.activeTurbo(state) orelse return;
    const click_start_active = state.gameplay_click_start_active;
    const pose = if (click_start_active and state.tutorialClickStartCutsceneActive())
        tutorialClickStartTurboPose(model, loaded_track_preview, runner)
    else
        gameplayTurboPose(model, loaded_track_preview, runner);
    model.drawEx(pose.transform);
    model.drawToonOutlineEx(pose.transform, camera, .black);

    if (click_start_active) return;
    drawGameplayTurboAttachments(state, pose.position, pose.right, pose.up, pose.forward, runner, camera);
}

fn drawGameplayTurboAttachments(
    state: *const AppState,
    position: rl.Vector3,
    right: rl.Vector3,
    up: rl.Vector3,
    forward: rl.Vector3,
    runner: gameplay.Runner,
    camera: rl.Camera3D,
) void {
    const channel_states = gameplay.nativeWeaponChannelStates(runner.movement_flags);

    const top_active = channel_states.center == 1 or
        state.gameplay_weapon_visual_state.top_draw_ticks > 0 or
        state.gameplay_weapon_visual_state.top_hide_ticks > 0;
    if (top_active) {
        if (state.current_gameplay_blaster_top_models.currentModel(
            state.gameplay_weapon_visual_state.top_draw_ticks,
            state.gameplay_weapon_visual_state.top_fire_ticks,
            state.gameplay_weapon_visual_state.top_hide_ticks,
        )) |model| {
            drawGameplayUploadedModelWithToonOutline(
                model,
                offsetPosition(position, right, up, forward, 0.0, 0.22, 0.10),
                right,
                up,
                forward,
                .{ .x = 0.22, .y = 0.22, .z = 0.22 },
                camera,
            );
        }
    }

    const left_active = channel_states.left != 0 or
        state.gameplay_weapon_visual_state.left_draw_ticks > 0 or
        state.gameplay_weapon_visual_state.left_hide_ticks > 0;
    if (left_active) {
        const left_selected_state = state.gameplay_weapon_visual_state.sideSelectedState(channel_states.left, true);
        const left_model = switch (left_selected_state) {
            1 => state.current_gameplay_blaster_left_models.currentModel(
                state.gameplay_weapon_visual_state.left_draw_ticks,
                0,
                state.gameplay_weapon_visual_state.left_hide_ticks,
            ),
            2 => state.current_gameplay_laser_left_models.currentModel(
                state.gameplay_weapon_visual_state.left_draw_ticks,
                0,
                state.gameplay_weapon_visual_state.left_hide_ticks,
            ),
            else => null,
        };
        if (left_model) |model| {
            drawGameplayUploadedModelWithToonOutline(
                model,
                offsetPosition(position, right, up, forward, -0.24, 0.11, 0.08),
                right,
                up,
                forward,
                .{ .x = 0.22, .y = 0.22, .z = 0.22 },
                camera,
            );
        }
    }

    const right_active = channel_states.right != 0 or
        state.gameplay_weapon_visual_state.right_draw_ticks > 0 or
        state.gameplay_weapon_visual_state.right_hide_ticks > 0;
    if (right_active) {
        const right_selected_state = state.gameplay_weapon_visual_state.sideSelectedState(channel_states.right, false);
        const right_model = switch (right_selected_state) {
            1 => state.current_gameplay_blaster_right_models.currentModel(
                state.gameplay_weapon_visual_state.right_draw_ticks,
                0,
                state.gameplay_weapon_visual_state.right_hide_ticks,
            ),
            2 => state.current_gameplay_laser_right_models.currentModel(
                state.gameplay_weapon_visual_state.right_draw_ticks,
                0,
                state.gameplay_weapon_visual_state.right_hide_ticks,
            ),
            else => null,
        };
        if (right_model) |model| {
            drawGameplayUploadedModelWithToonOutline(
                model,
                offsetPosition(position, right, up, forward, 0.24, 0.11, 0.08),
                right,
                up,
                forward,
                .{ .x = 0.22, .y = 0.22, .z = 0.22 },
                camera,
            );
        }
    }

    const rocket_active = channel_states.center == 3 or
        state.gameplay_weapon_visual_state.rocket_draw_ticks > 0 or
        state.gameplay_weapon_visual_state.rocket_hide_ticks > 0;
    if (rocket_active) {
        if (state.current_gameplay_rocket_launcher_models.currentModel(
            state.gameplay_weapon_visual_state.rocket_draw_ticks,
            0,
            state.gameplay_weapon_visual_state.rocket_hide_ticks,
        )) |model| {
            drawGameplayUploadedModelWithToonOutline(
                model,
                offsetPosition(position, right, up, forward, 0.0, 0.23, 0.12),
                right,
                up,
                forward,
                .{ .x = 0.24, .y = 0.24, .z = 0.24 },
                camera,
            );
        }
    }

    const jetpack_visual_active = nativeJetpackVisualPresentationActive(runner);
    const jetpack_visible = jetpack_visual_active or
        state.gameplay_jetpack_visual_state.draw_ticks > 0 or
        state.gameplay_jetpack_visual_state.hide_ticks > 0;
    if (jetpack_visible) {
        if (state.current_gameplay_jetpack_thrust_models.currentModel(
            state.gameplay_jetpack_visual_state.draw_ticks,
            jetpack_visual_active,
            state.gameplay_jetpack_visual_state.hide_ticks,
            state.render_time_seconds,
        )) |model| {
            drawGameplayUploadedModelWithToonOutline(
                model,
                offsetPosition(position, right, up, forward, 0.0, 0.10, -0.18),
                right,
                up,
                forward,
                .{ .x = 0.24, .y = 0.24, .z = 0.24 },
                camera,
            );
        }
    }

    if (runner.invincible_ticks > 0) {
        if (state.current_gameplay_invincible_models.currentModel(state.render_time_seconds)) |model| {
            drawGameplayUploadedModel(
                model.*,
                offsetPosition(position, right, up, forward, 0.0, 0.02, 0.0),
                right,
                up,
                forward,
                .{ .x = 1.05, .y = 1.05, .z = 1.05 },
                .{ .r = 220, .g = 240, .b = 255, .a = 180 },
            );
        }
    }
}

fn drawGameplayUploadedModel(
    model: x2.Uploaded,
    position: rl.Vector3,
    right: rl.Vector3,
    up: rl.Vector3,
    forward: rl.Vector3,
    scale: rl.Vector3,
    tint: ?rl.Color,
) void {
    const transform = gameplayUploadedModelTransform(&model, position, right, up, forward, scale);
    if (tint) |tint_color| {
        drawGameplayUploadedModelTinted(&model, transform, tint_color);
    } else {
        model.drawEx(transform);
    }
}

fn drawGameplayUploadedModelWithToonOutline(
    model: *const x2.Uploaded,
    position: rl.Vector3,
    right: rl.Vector3,
    up: rl.Vector3,
    forward: rl.Vector3,
    scale: rl.Vector3,
    camera: rl.Camera3D,
) void {
    const transform = gameplayUploadedModelTransform(model, position, right, up, forward, scale);
    model.drawEx(transform);
    model.drawToonOutlineEx(transform, camera, .black);
}

fn gameplayUploadedModelTransform(
    model: *const x2.Uploaded,
    position: rl.Vector3,
    right: rl.Vector3,
    up: rl.Vector3,
    forward: rl.Vector3,
    scale: rl.Vector3,
) rl.Matrix {
    const world_transform = modelTransformFromBasis(position, right, up, forward);
    const local_offset = rl.Matrix.translate(
        -model.bounds.center.x,
        -model.bounds.center.y,
        -model.bounds.center.z,
    );
    const model_scale = rl.Matrix.scale(scale.x, scale.y, scale.z);
    return world_transform.multiply(local_offset).multiply(model_scale);
}

fn drawGameplayUploadedModelTinted(model: *const x2.Uploaded, transform: rl.Matrix, tint: rl.Color) void {
    for (model.submeshes) |submesh| {
        var material = submesh.material;
        material.maps[@intFromEnum(rl.MaterialMapIndex.albedo)].color = tint;
        rl.drawMesh(submesh.mesh, material, transform);
    }
}

const GameplayTurboPose = struct {
    position: rl.Vector3,
    right: rl.Vector3,
    up: rl.Vector3,
    forward: rl.Vector3,
    transform: rl.Matrix,
};

const gameplay_turbo_body_height: f32 = 0.02;
const tutorial_click_start_body_height: f32 = 0.08;

fn gameplayTurboPose(model: *const x2.Uploaded, loaded_track_preview: *const track.LoadedLevelPreview, runner: gameplay.Runner) GameplayTurboPose {
    const forward = normalizeVector3(runner.worldForward(loaded_track_preview));
    const up = normalizeVector3(runner.worldUp(loaded_track_preview));
    var right = crossVector3(up, forward);
    if (vectorLength(right) <= 0.0001) {
        right = .{ .x = 1.0, .y = 0.0, .z = 0.0 };
    } else {
        right = normalizeVector3(right);
    }
    const corrected_up = normalizeVector3(crossVector3(forward, right));
    const position = runner.worldPosition(loaded_track_preview, gameplay_turbo_body_height);
    const world_transform = modelTransformFromBasis(position, right, corrected_up, forward);
    const local_offset = groundedCharacterModelOffset(model);
    return .{
        .position = position,
        .right = right,
        .up = corrected_up,
        .forward = forward,
        .transform = world_transform.multiply(local_offset),
    };
}

fn tutorialClickStartTurboPose(model: *const x2.Uploaded, loaded_track_preview: *const track.LoadedLevelPreview, runner: gameplay.Runner) GameplayTurboPose {
    const base_pose = gameplayTurboPose(model, loaded_track_preview, runner);
    const position = runner.worldPosition(loaded_track_preview, tutorial_click_start_body_height);
    const world_transform = modelTransformFromBasis(position, base_pose.right, base_pose.up, base_pose.forward);
    const local_offset = groundedCharacterModelOffset(model);
    return .{
        .position = position,
        .right = base_pose.right,
        .up = base_pose.up,
        .forward = base_pose.forward,
        .transform = world_transform.multiply(local_offset),
    };
}

fn groundedCharacterModelOffset(model: *const x2.Uploaded) rl.Matrix {
    return rl.Matrix.translate(
        -model.bounds.center.x,
        -model.bounds.min.y,
        -model.bounds.center.z,
    );
}

fn centeredModelOffset(model: *const x2.Uploaded) rl.Matrix {
    return rl.Matrix.translate(
        -model.bounds.center.x,
        -model.bounds.center.y,
        -model.bounds.center.z,
    );
}

fn offsetPosition(
    origin: rl.Vector3,
    right: rl.Vector3,
    up: rl.Vector3,
    forward: rl.Vector3,
    local_x: f32,
    local_y: f32,
    local_z: f32,
) rl.Vector3 {
    return .{
        .x = origin.x + (right.x * local_x) + (up.x * local_y) + (forward.x * local_z),
        .y = origin.y + (right.y * local_x) + (up.y * local_y) + (forward.y * local_z),
        .z = origin.z + (right.z * local_x) + (up.z * local_y) + (forward.z * local_z),
    };
}

fn vectorLength(v: rl.Vector3) f32 {
    return std.math.sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

fn addVector3(a: rl.Vector3, b: rl.Vector3) rl.Vector3 {
    return .{
        .x = a.x + b.x,
        .y = a.y + b.y,
        .z = a.z + b.z,
    };
}

fn scaleVector3(v: rl.Vector3, scalar: f32) rl.Vector3 {
    return .{
        .x = v.x * scalar,
        .y = v.y * scalar,
        .z = v.z * scalar,
    };
}

fn normalizeVector3(v: rl.Vector3) rl.Vector3 {
    const len = vectorLength(v);
    if (len <= 0.0001) return .{ .x = 0.0, .y = 0.0, .z = 1.0 };
    return .{
        .x = v.x / len,
        .y = v.y / len,
        .z = v.z / len,
    };
}

fn crossVector3(a: rl.Vector3, b: rl.Vector3) rl.Vector3 {
    return .{
        .x = (a.y * b.z) - (a.z * b.y),
        .y = (a.z * b.x) - (a.x * b.z),
        .z = (a.x * b.y) - (a.y * b.x),
    };
}

fn lerpVector3(a: rl.Vector3, b: rl.Vector3, t: f32) rl.Vector3 {
    return .{
        .x = std.math.lerp(a.x, b.x, t),
        .y = std.math.lerp(a.y, b.y, t),
        .z = std.math.lerp(a.z, b.z, t),
    };
}

fn dotVector3(a: rl.Vector3, b: rl.Vector3) f32 {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

fn modelTransformFromBasis(position: rl.Vector3, right: rl.Vector3, up: rl.Vector3, forward: rl.Vector3) rl.Matrix {
    return .{
        .m0 = right.x,
        .m4 = up.x,
        .m8 = forward.x,
        .m12 = position.x,
        .m1 = right.y,
        .m5 = up.y,
        .m9 = forward.y,
        .m13 = position.y,
        .m2 = right.z,
        .m6 = up.z,
        .m10 = forward.z,
        .m14 = position.z,
        .m3 = 0.0,
        .m7 = 0.0,
        .m11 = 0.0,
        .m15 = 1.0,
    };
}

fn gameTrackSetIndexForLevel(level_track: level.Track) ?u8 {
    return level_loader.gameTrackSetIndexForLevel(level_track);
}

fn takeOptional(comptime T: type, slot: *?T) ?T {
    if (slot.*) |value| {
        slot.* = null;
        return value;
    }
    return null;
}

fn wrappedIndex(count: usize, current: usize, delta: isize) usize {
    if (count == 0) return 0;

    const count_isize: isize = @intCast(count);
    const current_isize: isize = @intCast(current);
    var next = @mod(current_isize + delta, count_isize);
    if (next < 0) {
        next += count_isize;
    }
    return @intCast(next);
}

// PORT(verified): the original window bootstrap falls back to a 640x480 client area
// in windowed mode, while its fullscreen presets are also all 4:3.
// Evidence: sub_4119d0.
fn screenWidth() i32 {
    return rl.getScreenWidth();
}

fn screenHeight() i32 {
    return rl.getScreenHeight();
}

test "wrapped index handles negative deltas" {
    try std.testing.expectEqual(@as(usize, 4), wrappedIndex(5, 0, -1));
    try std.testing.expectEqual(@as(usize, 0), wrappedIndex(5, 0, 5));
}

test "completion bonus only applies to postal mode" {
    try std.testing.expect(completionBonusAppliesForMode(.postal));
    try std.testing.expect(!completionBonusAppliesForMode(.challenge));
    try std.testing.expect(!completionBonusAppliesForMode(.time_trial));
    try std.testing.expect(!completionBonusAppliesForMode(.tutorial));
    try std.testing.expect(completionBonusAppliesForMode(null));
}

test "frontend mode helpers match the recovered shared subgame routing" {
    try std.testing.expectEqual(gameplay.SessionMode.postal, runnerSessionModeForFrontendMode(.postal));
    try std.testing.expectEqual(gameplay.SessionMode.challenge, runnerSessionModeForFrontendMode(.challenge));
    try std.testing.expectEqual(gameplay.SessionMode.time_trial, runnerSessionModeForFrontendMode(.time_trial));
    try std.testing.expectEqual(gameplay.SessionMode.tutorial, runnerSessionModeForFrontendMode(.tutorial));

    try std.testing.expectEqual(track.postalChallengeRuntimeBuildFlags, runtimeBuildFlagsForFrontendMode(.postal));
    try std.testing.expectEqual(track.postalChallengeRuntimeBuildFlags, runtimeBuildFlagsForFrontendMode(.challenge));
    try std.testing.expectEqual(track.timeTrialRuntimeBuildFlags, runtimeBuildFlagsForFrontendMode(.time_trial));
    try std.testing.expectEqual(track.tutorialRuntimeBuildFlags, runtimeBuildFlagsForFrontendMode(.tutorial));
}

test "route map replay gate follows time-trial completion replays" {
    var tables = high_score.Tables.initDefault();
    tables.completion[0].has_replay = true;

    try std.testing.expect(routeMapHasReplayEntry(.time_trial, 1, &tables));
    try std.testing.expect(!routeMapHasReplayEntry(.postal, 1, &tables));
    try std.testing.expect(!routeMapHasReplayEntry(.time_trial, 0, &tables));
    try std.testing.expect(!routeMapHasReplayEntry(.time_trial, tables.completion.len + 1, &tables));

    tables.completion[0].has_replay = false;
    try std.testing.expect(!routeMapHasReplayEntry(.time_trial, 1, &tables));
}

test "high-score row replay is challenge-only" {
    try std.testing.expect(!frontend_high_score_screen.rowsShowReplay(.postal, false));
    try std.testing.expect(frontend_high_score_screen.rowsShowReplay(.challenge, false));
    try std.testing.expect(!frontend_high_score_screen.rowsShowReplay(.challenge, true));
}

test "route map screen modes follow windows route-map entry paths" {
    try std.testing.expectEqual(frontend_bridge.RouteMapScreenMode.normal, frontend_bridge.defaultRouteMapScreenMode(.postal));
    try std.testing.expectEqual(frontend_bridge.RouteMapScreenMode.replay, frontend_bridge.defaultRouteMapScreenMode(.time_trial));
    try std.testing.expect(frontend_bridge.routeMapAllowsRouteSwitching(.normal));
    try std.testing.expect(frontend_bridge.routeMapAllowsRouteSwitching(.replay));
    try std.testing.expect(!frontend_bridge.routeMapAllowsRouteSwitching(.post_completion_exit));
    try std.testing.expectEqualStrings("Back", frontend_bridge.routeMapBackLabelForScreenMode(.normal));
    try std.testing.expectEqualStrings("Back", frontend_bridge.routeMapBackLabelForScreenMode(.replay));
    try std.testing.expectEqualStrings("Exit", frontend_bridge.routeMapBackLabelForScreenMode(.post_completion_exit));
}

test "route map body text stays empty without route script copy" {
    try std.testing.expectEqualStrings("", frontend_route_map.bodyText(null));
    try std.testing.expectEqualStrings("My first route!", frontend_route_map.bodyText("My first route!"));
}

test "run return targets follow the recovered native bridge where confirmed" {
    try std.testing.expectEqual(frontend_bridge.OuterReturnTarget.postal_route_map, outerReturnTargetForOutcome(.completed, .postal));
    try std.testing.expectEqual(frontend_bridge.OuterReturnTarget.time_trial_route_map, outerReturnTargetForOutcome(.completed, .time_trial));
    try std.testing.expectEqual(frontend_bridge.OuterReturnTarget.challenge_setup_menu, outerReturnTargetForOutcome(.completed, .challenge));
    try std.testing.expectEqual(frontend_bridge.OuterReturnTarget.new_game_menu, outerReturnTargetForOutcome(.completed, .tutorial));
    try std.testing.expectEqual(frontend_bridge.OuterReturnTarget.new_game_menu, outerReturnTargetForOutcome(.failed, .postal));
    try std.testing.expectEqual(frontend_bridge.OuterReturnTarget.challenge_setup_menu, outerReturnTargetForOutcome(.failed, .challenge));
    try std.testing.expectEqual(frontend_bridge.OuterReturnTarget.time_trial_route_map, outerReturnTargetForOutcome(.failed, .time_trial));
    try std.testing.expectEqual(frontend_bridge.OuterReturnTarget.main_menu, outerReturnTargetForOutcome(.failed, .tutorial));
}

test "completion flow owners map postal loops to the recovered return targets" {
    try std.testing.expectEqual(frontend_bridge.OuterReturnTarget.postal_route_map, outerReturnTargetForCompletionOwner(.postal_route_map));
    try std.testing.expectEqual(frontend_bridge.OuterReturnTarget.thanks_screen, outerReturnTargetForCompletionOwner(.postal_final));
    try std.testing.expectEqual(frontend_bridge.OuterReturnTarget.new_game_menu, outerReturnTargetForCompletionOwner(.postal_failure));
    try std.testing.expectEqual(frontend_bridge.OuterReturnTarget.challenge_setup_menu, outerReturnTargetForCompletionOwner(.challenge_completion));
    try std.testing.expectEqual(frontend_bridge.OuterReturnTarget.challenge_setup_menu, outerReturnTargetForCompletionOwner(.challenge_failure));
}

test "respawn bridge state preserves the active run across rebuilds" {
    var state: AppState = undefined;
    state.active_frontend_mode = .postal;
    state.active_frontend_level_index = 7;
    state.level_runner = gameplay.Runner{};
    state.level_runner.?.session_mode = .postal;
    state.level_runner.?.score.total = 12_345;
    state.level_runner.?.visible_life_stock = 2;
    state.level_runner.?.tick_count = 90;
    state.level_runner.?.stopwatch.advance(90.0);
    state.level_runner.?.counters.parcels = 3;
    state.level_runner.?.row_event_display.parcel_target_count = 7;
    state.level_runner.?.row_event_display.staged_parcel_count = 3;
    state.level_runner.?.row_event_display.delivered_parcel_count = 3;
    state.level_runner.?.parcel.collected_rows[0] = 42;
    state.level_runner.?.parcel.collected_row_count = 1;

    var respawn_opcode: frontend_bridge.OuterBridgeOpcode = .destroy_return;
    const respawn_owner = state.outerOwnerForRespawnActiveRun(&respawn_opcode);
    try std.testing.expect(respawn_owner != null);
    try std.testing.expectEqual(frontend_bridge.OuterBridgeOpcode.rebuild_clear_replay_return, respawn_opcode);
    try std.testing.expectEqual(@as(u8, 0x1c), state.subgame_rebuild_selector);
    try std.testing.expectEqual(frontend_bridge.OuterOwner.resume_active_run, respawn_owner.?.owner);

    const bridge_state = state.pending_respawn_bridge_state orelse return error.TestExpectedRespawnBridgeState;
    try std.testing.expectEqual(@as(?FrontendLevelMode, .postal), bridge_state.frontend_mode);
    try std.testing.expectEqual(@as(usize, 7), bridge_state.frontend_level_index);
    try std.testing.expectEqual(gameplay.SessionMode.postal, bridge_state.runner.session_mode);
    try std.testing.expectEqual(@as(u32, 12_345), bridge_state.runner.score.total);
    try std.testing.expectEqual(@as(u32, 2), bridge_state.runner.visible_life_stock);
    try std.testing.expectEqual(@as(u32, 3), bridge_state.runner.counters.parcels);
    try std.testing.expectEqual(@as(usize, 1), bridge_state.runner.parcel.collected_row_count);
    try std.testing.expectEqual(@as(usize, 42), bridge_state.runner.parcel.collected_rows[0]);
}

test "final postal completion returns through the thanks screen" {
    try std.testing.expectEqual(frontend_bridge.OuterReturnTarget.postal_route_map, postalCompletionOuterReturnTarget(1, 0x32));
    try std.testing.expectEqual(frontend_bridge.OuterReturnTarget.thanks_screen, postalCompletionOuterReturnTarget(0x32, 0x32));
    try std.testing.expectEqual(frontend_bridge.OuterReturnTarget.thanks_screen, postalCompletionOuterReturnTarget(0x33, 0x33));
}

test "frontend widget shortcut codes follow the recovered pause and post-score widgets" {
    var state: AppState = undefined;
    state.game_phase = .pause_menu;
    state.pending_run_result = null;
    try std.testing.expectEqualDeep(
        frontend_activation.QueuedAction{ .pause_menu = .end_game },
        state.frontendShortcutActivationForCode(11).?,
    );
    try std.testing.expectEqualDeep(
        frontend_activation.QueuedAction{ .pause_menu = .options },
        state.frontendShortcutActivationForCode(111).?,
    );
    try std.testing.expectEqualDeep(
        frontend_activation.QueuedAction{ .pause_menu = .@"resume" },
        state.frontendShortcutActivationForCode(5).?,
    );
    try std.testing.expectEqualDeep(
        frontend_activation.QueuedAction{ .pause_menu = .@"resume" },
        state.frontendShortcutActivationForCode(6).?,
    );

    state.game_phase = .high_scores_menu;
    state.pending_run_result = .{
        .level_name = "x",
        .mode = .postal,
        .elapsed_millis = 0,
        .parcel_count = 0,
        .parcel_target = 0,
        .score = 0,
        .score_is_partial = false,
        .high_score_mode = .postal,
        .high_score_rank = 0,
        .outer_return_target = .postal_route_map,
    };
    state.high_score_screen_owner = .{ .post_level_entry = .{
        .mode = .postal,
        .rank = 0,
    } };
    try std.testing.expectEqualDeep(
        frontend_activation.QueuedAction{ .post_level_high_scores = .cancel },
        state.frontendShortcutActivationForCode(11).?,
    );
    try std.testing.expectEqualDeep(
        frontend_activation.QueuedAction{ .post_level_high_scores = .submit },
        state.frontendShortcutActivationForCode(5).?,
    );
    try std.testing.expectEqualDeep(
        frontend_activation.QueuedAction{ .post_level_high_scores = .submit },
        state.frontendShortcutActivationForCode(6).?,
    );
    try std.testing.expectEqual(@as(?frontend_activation.QueuedAction, null), state.frontendShortcutActivationForCode(111));
}

test "level segment prompt dispatch keys from the runner row message owner" {
    var catalog = try assets.Catalog.init(std.testing.allocator, default_archive_path);
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath(default_level_path) orelse return error.EntryNotFound;
    var loaded_level = try level.loadFromArchive(std.testing.allocator, &catalog, entry);

    var loaded_track_preview = try track.LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &loaded_level,
        .{ .load_models = false },
    );
    defer loaded_track_preview.deinit();

    var runner = gameplay.Runner.init(&loaded_track_preview);
    var target_logical_segment_index: ?usize = null;
    for (0..loaded_track_preview.total_rows) |global_row| {
        const row_location = loaded_track_preview.locateRow(global_row) orelse continue;
        const logical_segment_index = loaded_track_preview.segment_logical_indices[row_location.segment_index] orelse continue;
        if (loaded_level.segments[logical_segment_index].message == null) continue;
        target_logical_segment_index = logical_segment_index;
        break;
    }

    const logical_segment_index = target_logical_segment_index orelse return error.TestExpectedSegmentMessage;
    const expected_message = loaded_level.segments[logical_segment_index].message.?;
    var tick: usize = 0;
    while (tick < 4096 and runner.currentRowMessageLogicalSegmentIndex() != logical_segment_index) : (tick += 1) {
        runner.step(&loaded_track_preview, .{}, 1.0 / 60.0);
    }

    try std.testing.expectEqual(logical_segment_index, runner.currentRowMessageLogicalSegmentIndex().?);

    var state: AppState = undefined;
    state.current_level = loaded_level;
    defer if (state.current_level) |*owned_level| owned_level.deinit();
    state.level_runner = runner;
    state.active_frontend_mode = .tutorial;
    state.active_level_segment_index = null;
    state.level_prompt_queue = .{};
    state.gameplay_click_start_active = false;
    state.audio_ready = false;

    try state.syncActiveLevelSegment();
    try std.testing.expectEqual(@as(?level_prompt.Entry, null), state.level_prompt_queue.active());

    try state.dispatchCurrentRunnerRowMessage(null, null, true);
    try std.testing.expectEqual(@as(?usize, logical_segment_index), state.active_level_segment_index);
    try std.testing.expectEqualStrings(expected_message, state.level_prompt_queue.active().?.message);
}

test "completion reveal stages the bonus line before continue" {
    const result = PendingRunResult{
        .level_name = "To Infinity!",
        .mode = .postal,
        .elapsed_millis = 0,
        .parcel_count = 7,
        .parcel_target = 7,
        .score = 50_000,
        .score_is_partial = false,
        .score_totals = .{ .completion_bonus = 50_000 },
        .outer_return_target = .postal_route_map,
    };

    const summary = completionSummary(result);
    try std.testing.expect(!frontend_completion_screen.bonusVisibleAtProgress(summary, 0.999));
    try std.testing.expect(!frontend_completion_screen.continueVisibleAtProgress(summary, 0.999));
    try std.testing.expect(frontend_completion_screen.bonusVisibleAtProgress(summary, 1.0));
    try std.testing.expect(!frontend_completion_screen.continueVisibleAtProgress(summary, 1.999));
    try std.testing.expect(frontend_completion_screen.continueVisibleAtProgress(summary, 2.0));
}

test "completion reveal skips the bonus stage when no bonus line exists" {
    const result = PendingRunResult{
        .level_name = "To Infinity!",
        .mode = .postal,
        .elapsed_millis = 0,
        .parcel_count = 5,
        .parcel_target = 7,
        .score = 0,
        .score_is_partial = true,
        .outer_return_target = .postal_route_map,
    };

    const summary = completionSummary(result);
    try std.testing.expect(!frontend_completion_screen.bonusVisibleAtProgress(summary, 1.0));
    try std.testing.expect(!frontend_completion_screen.continueVisibleAtProgress(summary, 0.999));
    try std.testing.expect(frontend_completion_screen.continueVisibleAtProgress(summary, 1.0));
}

test "completion overlay helpers distinguish overlay from finalized screen" {
    var state: AppState = undefined;
    state.pending_run_result = .{
        .outcome = .completed,
        .level_name = "To Infinity!",
        .mode = .postal,
        .elapsed_millis = 0,
        .parcel_count = 7,
        .parcel_target = 7,
        .score = 50_000,
        .score_is_partial = true,
        .outer_return_target = .postal_route_map,
    };
    state.game_phase = .level;
    state.completion_overlay_active = true;
    state.frontend_transition = .{};

    try std.testing.expect(state.completionScreenActive());
    try std.testing.expect(state.completionScreenOverlayActive());
    try std.testing.expect(!state.completionScreenInteractive());

    state.game_phase = .completion_screen;
    state.completion_overlay_active = false;

    try std.testing.expect(state.completionScreenActive());
    try std.testing.expect(!state.completionScreenOverlayActive());
    try std.testing.expect(state.completionScreenInteractive());
}

test "completion reveal advances while the early overlay is active in level phase" {
    var state: AppState = undefined;
    state.pending_run_result = .{
        .outcome = .completed,
        .level_name = "To Infinity!",
        .mode = .postal,
        .elapsed_millis = 0,
        .parcel_count = 7,
        .parcel_target = 7,
        .score = 50_000,
        .score_is_partial = false,
        .score_totals = .{ .completion_bonus = 50_000 },
        .outer_return_target = .postal_route_map,
    };
    state.game_phase = .level;
    state.completion_overlay_active = true;
    state.frontend_transition = .{};
    state.completion_screen_reveal_progress = 0.0;

    state.stepCompletionScreenReveal();

    try std.testing.expectApproxEqAbs(frontend_completion_screen.reveal_step, state.completion_screen_reveal_progress, 0.0001);
}

test "postal completion copy matches the recovered widget strings" {
    var buffer: [64]u8 = undefined;
    try std.testing.expectEqualStrings("Delivery Complete!", frontend_completion_screen.title(completionSummary(.{
        .level_name = "To Infinity!",
        .mode = .postal,
        .elapsed_millis = 0,
        .parcel_count = 1,
        .parcel_target = 1,
        .score = 0,
        .score_is_partial = false,
        .outer_return_target = .postal_route_map,
    })));
    try std.testing.expectEqualStrings("1 Package Delivered", try frontend_completion_screen.packageLine(&buffer, completionSummary(.{
        .level_name = "To Infinity!",
        .mode = .postal,
        .elapsed_millis = 0,
        .parcel_count = 1,
        .parcel_target = 1,
        .score = 0,
        .score_is_partial = false,
        .outer_return_target = .postal_route_map,
    })));
    try std.testing.expectEqualStrings("07 Packages Delivered", try frontend_completion_screen.packageLine(&buffer, completionSummary(.{
        .level_name = "To Infinity!",
        .mode = .postal,
        .elapsed_millis = 0,
        .parcel_count = 7,
        .parcel_target = 7,
        .score = 0,
        .score_is_partial = false,
        .outer_return_target = .postal_route_map,
    })));
}

test "elapsed millis format as mm:ss.cc" {
    var buffer: [32]u8 = undefined;
    const text = try formatElapsedMillis(&buffer, 91_230);
    try std.testing.expectEqualStrings("01:31.23", text);
}

test "tutorial score format uses commas" {
    var buffer: [24]u8 = undefined;
    const text = try formatScoreWithCommas(&buffer, 61_450);
    try std.testing.expectEqualStrings("61,450", text);
}

test "high score mode index follows screen order" {
    try std.testing.expectEqual(@as(usize, 0), frontend_high_score_screen.modeIndex(.postal));
    try std.testing.expectEqual(@as(usize, 1), frontend_high_score_screen.modeIndex(.challenge));
}

test "high score controller helpers stay screen-local" {
    try std.testing.expectEqualStrings("Postal High Scores", frontend_high_score_screen.title(.{ .main_menu_browse = .postal }));
    try std.testing.expectEqualStrings("Enter your name here!", frontend_high_score_screen.title(.{ .post_level_entry = .{ .mode = .postal, .rank = 0 } }));
    try std.testing.expectEqual(high_score.Mode.challenge, frontend_high_score_screen.nextBrowseMode(.{ .main_menu_browse = .postal }).?);
    try std.testing.expect(frontend_high_score_screen.nextBrowseMode(.{ .post_level_entry = .{ .mode = .postal, .rank = 0 } }) == null);
    try std.testing.expectEqualDeep(
        frontend_bridge.SelectedLevelRecordSource{ .challenge = 3 },
        frontend_high_score_screen.replaySource(.{ .main_menu_browse = .challenge }, 3).?,
    );
    try std.testing.expect(frontend_high_score_screen.replaySource(.{ .post_level_entry = .{ .mode = .challenge, .rank = 3 } }, 3) == null);
}

test "new game menu mapping matches frontend route modes" {
    try std.testing.expectEqual(NewGameMenuItem.postal_mode, frontend_activation.newGameMenuItemForFrontendMode(.postal));
    try std.testing.expectEqual(NewGameMenuItem.time_trial, frontend_activation.newGameMenuItemForFrontendMode(.time_trial));
    try std.testing.expectEqual(NewGameMenuItem.challenge_mode, frontend_activation.newGameMenuItemForFrontendMode(.challenge));
    try std.testing.expectEqual(NewGameMenuItem.tutorial, frontend_activation.newGameMenuItemForFrontendMode(.tutorial));
    try std.testing.expectEqual(@as(usize, 1), frontend_activation.newGameMenuIndexForItem(.postal_mode));
    try std.testing.expectEqual(@as(usize, 2), frontend_activation.newGameMenuIndexForItem(.time_trial));
    try std.testing.expectEqual(@as(usize, 4), frontend_activation.newGameMenuIndexForItem(.help));
}

test "new game tutorial gate hides the later mode rows until tutorial launch" {
    var state: AppState = undefined;
    state.runtime_config = config.Blob.initDefault();

    try std.testing.expect(state.newGameMenuItemVisible(.tutorial));
    try std.testing.expect(!state.newGameMenuItemVisible(.postal_mode));
    try std.testing.expect(!state.newGameMenuItemVisible(.time_trial));
    try std.testing.expect(!state.newGameMenuItemVisible(.challenge_mode));
    try std.testing.expect(state.newGameMenuItemVisible(.help));
    try std.testing.expect(state.newGameMenuItemVisible(.back));

    state.runtime_config.setNewGameExtraModesVisible(true);
    try std.testing.expect(state.newGameMenuItemVisible(.postal_mode));
    try std.testing.expect(state.newGameMenuItemVisible(.time_trial));
    try std.testing.expect(state.newGameMenuItemVisible(.challenge_mode));
}

test "new game selection skips hidden rows while the tutorial gate is closed" {
    var state: AppState = undefined;
    state.runtime_config = config.Blob.initDefault();
    state.new_game_menu_index = frontend_activation.newGameMenuIndexForItem(.tutorial);

    state.stepNewGameMenuSelection(1);
    try std.testing.expectEqual(frontend_activation.newGameMenuIndexForItem(.help), state.new_game_menu_index);

    state.stepNewGameMenuSelection(1);
    try std.testing.expectEqual(frontend_activation.newGameMenuIndexForItem(.back), state.new_game_menu_index);

    state.stepNewGameMenuSelection(1);
    try std.testing.expectEqual(frontend_activation.newGameMenuIndexForItem(.tutorial), state.new_game_menu_index);

    state.new_game_menu_index = frontend_activation.newGameMenuIndexForItem(.challenge_mode);
    state.normalizeNewGameMenuSelection();
    try std.testing.expectEqual(frontend_activation.newGameMenuIndexForItem(.tutorial), state.new_game_menu_index);
}

test "postal unlock limit stops at the highest available route" {
    try std.testing.expectEqual(@as(usize, 2), AppState.nextPostalUnlockLimit(1, 0x32, 1));
    try std.testing.expectEqual(@as(usize, 0x32), AppState.nextPostalUnlockLimit(0x32, 0x32, 0x32));
    try std.testing.expectEqual(@as(usize, 0x33), AppState.nextPostalUnlockLimit(0x33, 0x33, 0x33));
    try std.testing.expectEqual(@as(usize, 0x32), AppState.nextPostalUnlockLimit(0x33, 0x32, 0x40));
}

test "postal unlock preview only reports newly unlocked routes" {
    try std.testing.expect(AppState.previewPostalRouteUnlock(1, 0x32, 1));
    try std.testing.expect(!AppState.previewPostalRouteUnlock(0x32, 0x32, 0x32));
    try std.testing.expect(!AppState.previewPostalRouteUnlock(0x33, 0x32, 0x40));
}

test "postal high-score commit gates on the final shipped route" {
    try std.testing.expect(!AppState.postalCompletionCommitsHighScore(1, 0x32));
    try std.testing.expect(!AppState.postalCompletionCommitsHighScore(0x31, 0x32));
    try std.testing.expect(AppState.postalCompletionCommitsHighScore(0x32, 0x32));
    try std.testing.expect(AppState.postalCompletionCommitsHighScore(0x33, 0x33));
}

test "ordinary postal completion commits unlock progress without staging arcade score entry" {
    var temp_dir = std.testing.tmpDir(.{});
    defer temp_dir.cleanup();

    var previous_dir = try std.Io.Dir.cwd().openDir(io, ".", .{});
    defer previous_dir.close(io);
    const resources = try resource_store.Store.init(std.testing.allocator, default_archive_path, false);

    try std.process.setCurrentDir(io, temp_dir.dir);
    defer std.process.setCurrentDir(io, previous_dir) catch unreachable;

    var state: AppState = undefined;
    state.allocator = std.testing.allocator;
    state.runtime_root_path = "runtime";
    state.resources = resources;
    defer state.resources.deinit();
    state.high_score_tables = high_score.Tables.initDefault();
    defer state.high_score_tables.deinit(std.testing.allocator);
    state.runtime_config = config.Blob.initDefault();
    state.runtime_config.setRouteUnlockLimit(1);
    state.active_frontend_mode = .postal;
    state.active_frontend_level_index = 1;
    state.current_track_preview = null;
    state.current_level = null;
    state.current_runtime_build_seed = 0;
    state.selected_level_record_override = null;
    state.selected_replay_cache = null;
    state.high_score_screen_owner = .{ .main_menu_browse = .postal };
    state.pending_run_result = .{
        .level_name = "Route 1",
        .mode = .postal,
        .elapsed_millis = 10_000,
        .parcel_count = 1,
        .parcel_target = 1,
        .score = 12_345,
        .score_is_partial = true,
        .completion_owner = .postal_route_map,
        .persistence = .completed,
        .outer_return_target = .postal_route_map,
    };

    try state.commitPendingRunResultIfNeeded();

    const updated = state.pending_run_result.?;
    try std.testing.expectEqual(PendingRunPersistence.none, updated.persistence);
    try std.testing.expectEqual(@as(?high_score.Mode, null), updated.high_score_mode);
    try std.testing.expectEqual(@as(?usize, null), updated.high_score_rank);
    try std.testing.expect(updated.unlocked_next_route);
    try std.testing.expectEqual(frontend_bridge.OuterReturnTarget.postal_route_map, updated.outer_return_target);
    try std.testing.expectEqual(@as(u32, 2), state.runtime_config.routeUnlockLimit());
}

test "final postal completion stages postal score entry before thanks return" {
    var temp_dir = std.testing.tmpDir(.{});
    defer temp_dir.cleanup();

    var previous_dir = try std.Io.Dir.cwd().openDir(io, ".", .{});
    defer previous_dir.close(io);
    const resources = try resource_store.Store.init(std.testing.allocator, default_archive_path, false);

    try std.process.setCurrentDir(io, temp_dir.dir);
    defer std.process.setCurrentDir(io, previous_dir) catch unreachable;

    var state: AppState = undefined;
    state.allocator = std.testing.allocator;
    state.runtime_root_path = "runtime";
    state.resources = resources;
    defer state.resources.deinit();
    state.high_score_tables = high_score.Tables.initDefault();
    defer state.high_score_tables.deinit(std.testing.allocator);
    state.runtime_config = config.Blob.initDefault();
    state.runtime_config.setRouteUnlockLimit(0x32);
    state.active_frontend_mode = .postal;
    state.active_frontend_level_index = 0x32;
    state.current_track_preview = null;
    state.current_level = null;
    state.current_runtime_build_seed = 0;
    state.selected_level_record_override = null;
    state.selected_replay_cache = null;
    state.high_score_screen_owner = .{ .main_menu_browse = .postal };
    state.pending_run_result = .{
        .level_name = "Final Route",
        .mode = .postal,
        .elapsed_millis = 20_000,
        .parcel_count = 9,
        .parcel_target = 9,
        .score = 65_000,
        .score_is_partial = true,
        .completion_owner = .postal_final,
        .persistence = .completed,
        .outer_return_target = .thanks_screen,
    };

    try state.commitPendingRunResultIfNeeded();

    const updated = state.pending_run_result.?;
    try std.testing.expectEqual(PendingRunPersistence.none, updated.persistence);
    try std.testing.expectEqual(@as(?high_score.Mode, .postal), updated.high_score_mode);
    try std.testing.expectEqual(frontend_bridge.OuterReturnTarget.thanks_screen, updated.outer_return_target);
    try std.testing.expect(!updated.unlocked_next_route);
    const context = state.pendingRunHighScoreContext() orelse return error.TestExpectedPendingHighScoreEntry;
    try std.testing.expectEqual(high_score.Mode.postal, context.mode);
    try std.testing.expectEqual(@as(usize, 0), context.rank);
}

test "postal failure only stages post-level score entry when the score qualifies" {
    var temp_dir = std.testing.tmpDir(.{});
    defer temp_dir.cleanup();

    var previous_dir = try std.Io.Dir.cwd().openDir(io, ".", .{});
    defer previous_dir.close(io);

    try std.process.setCurrentDir(io, temp_dir.dir);
    defer std.process.setCurrentDir(io, previous_dir) catch unreachable;

    var state: AppState = undefined;
    state.allocator = std.testing.allocator;
    state.runtime_root_path = "runtime";
    state.high_score_tables = high_score.Tables.initDefault();
    defer state.high_score_tables.deinit(std.testing.allocator);
    state.runtime_config = config.Blob.initDefault();
    state.active_frontend_mode = .postal;
    state.active_frontend_level_index = 7;
    state.current_track_preview = null;
    state.current_level = null;
    state.current_runtime_build_seed = 0;
    state.selected_level_record_override = null;
    state.selected_replay_cache = null;
    state.high_score_screen_owner = .{ .main_menu_browse = .postal };

    for (state.high_score_tables.postal[0..high_score.visible_entry_count], 0..) |*entry, index| {
        entry.* = .{ .score = @as(u32, @intCast(1_000 - index * 10)) };
    }

    state.pending_run_result = .{
        .outcome = .failed,
        .level_name = "Route 7",
        .mode = .postal,
        .elapsed_millis = 30_000,
        .parcel_count = 2,
        .parcel_target = 9,
        .score = 900,
        .score_is_partial = true,
        .completion_owner = .postal_failure,
        .persistence = .failed,
        .outer_return_target = .new_game_menu,
    };

    try state.commitPendingRunResultIfNeeded();

    const updated = state.pending_run_result.?;
    try std.testing.expectEqual(PendingRunPersistence.none, updated.persistence);
    try std.testing.expectEqual(@as(?high_score.Mode, .postal), updated.high_score_mode);
    try std.testing.expectEqual(@as(?usize, null), updated.high_score_rank);
    try std.testing.expectEqual(@as(?frontend_high_score_screen.PendingEntry, null), state.pendingRunHighScoreContext());
    try std.testing.expectEqual(frontend_bridge.OuterReturnTarget.new_game_menu, updated.outer_return_target);
}

test "postal abandon can stage standalone post-level score entry" {
    var temp_dir = std.testing.tmpDir(.{});
    defer temp_dir.cleanup();

    var previous_dir = try std.Io.Dir.cwd().openDir(io, ".", .{});
    defer previous_dir.close(io);

    try std.process.setCurrentDir(io, temp_dir.dir);
    defer std.process.setCurrentDir(io, previous_dir) catch unreachable;

    var state: AppState = undefined;
    state.allocator = std.testing.allocator;
    state.runtime_root_path = "runtime";
    state.high_score_tables = high_score.Tables.initDefault();
    defer state.high_score_tables.deinit(std.testing.allocator);
    state.runtime_config = config.Blob.initDefault();
    state.active_frontend_mode = .postal;
    state.active_frontend_level_index = 7;
    state.current_track_preview = null;
    state.current_level = null;
    state.current_runtime_build_seed = 0;
    state.selected_level_record_override = null;
    state.selected_level_record_source = null;
    state.selected_replay_cache = null;
    state.saved_outer_owner = frontend_bridge.outerOwnerStateRouteMap(.{
        .mode = .postal,
        .screen_mode = .normal,
    });

    for (state.high_score_tables.postal[0..high_score.visible_entry_count], 0..) |*entry, index| {
        entry.* = .{ .score = @as(u32, @intCast(100 - index)) };
    }

    const staged = (try state.standalonePostLevelHighScoreEntry(.{
        .outcome = .failed,
        .level_name = "Route 7",
        .mode = .postal,
        .elapsed_millis = 30_000,
        .parcel_count = 2,
        .parcel_target = 9,
        .score = 900,
        .score_is_partial = true,
        .completion_owner = .postal_failure,
        .persistence = .failed,
        .outer_return_target = .new_game_menu,
    })) orelse return error.TestExpectedPendingHighScoreEntry;

    try std.testing.expectEqual(high_score.Mode.postal, staged.context.mode);
    try std.testing.expectEqual(@as(usize, 0), staged.context.rank);
    try std.testing.expectEqual(frontend_bridge.OuterOwner.new_game_menu, staged.return_owner.owner);
    try std.testing.expectEqual(frontend_bridge.OuterBridgeOpcode.destroy_return, staged.return_opcode);
    try std.testing.expectEqual(@as(u32, 900), state.high_score_tables.postal[0].score);
}

test "parity: persistent high-score replay abandon restores the saved return owner" {
    var state: AppState = undefined;
    state.active_frontend_mode = .postal;
    state.active_frontend_level_index = 3;
    state.selected_level_record_override = null;
    state.selected_level_record_source = .{ .postal = 0 };
    state.selected_level_record_persistent = true;
    state.saved_replay_return_outer_owner = .high_scores_menu;
    state.selected_level_record_outer_return_target = null;

    var opcode: frontend_bridge.OuterBridgeOpcode = .rebuild_return;
    const owner = state.outerOwnerForAbandonActiveRun(&opcode);

    try std.testing.expectEqual(frontend_bridge.OuterBridgeOpcode.destroy_return, opcode);
    try std.testing.expectEqual(frontend_bridge.OuterOwner.high_scores_menu, owner.owner);
    try std.testing.expectEqual(high_score.Mode.postal, owner.high_score_mode);
}

test "standalone postal abandon skips score entry when the score does not qualify" {
    var temp_dir = std.testing.tmpDir(.{});
    defer temp_dir.cleanup();

    var previous_dir = try std.Io.Dir.cwd().openDir(io, ".", .{});
    defer previous_dir.close(io);

    try std.process.setCurrentDir(io, temp_dir.dir);
    defer std.process.setCurrentDir(io, previous_dir) catch unreachable;

    var state: AppState = undefined;
    state.allocator = std.testing.allocator;
    state.runtime_root_path = "runtime";
    state.high_score_tables = high_score.Tables.initDefault();
    defer state.high_score_tables.deinit(std.testing.allocator);
    state.runtime_config = config.Blob.initDefault();
    state.active_frontend_mode = .postal;
    state.active_frontend_level_index = 7;
    state.current_track_preview = null;
    state.current_level = null;
    state.current_runtime_build_seed = 0;
    state.selected_level_record_override = null;
    state.selected_level_record_source = null;
    state.selected_replay_cache = null;
    state.saved_outer_owner = frontend_bridge.outerOwnerStateRouteMap(.{
        .mode = .postal,
        .screen_mode = .normal,
    });

    for (state.high_score_tables.postal[0..high_score.visible_entry_count], 0..) |*entry, index| {
        entry.* = .{ .score = @as(u32, @intCast(1_000 - index * 10)) };
    }

    try std.testing.expectEqual(@as(?StandalonePostLevelHighScoreEntry, null), try state.standalonePostLevelHighScoreEntry(.{
        .outcome = .failed,
        .level_name = "Route 7",
        .mode = .postal,
        .elapsed_millis = 30_000,
        .parcel_count = 2,
        .parcel_target = 9,
        .score = 900,
        .score_is_partial = true,
        .completion_owner = .postal_failure,
        .persistence = .failed,
        .outer_return_target = .new_game_menu,
    }));
}

test "challenge abandon keeps post-level score entry on the challenge return lane" {
    var temp_dir = std.testing.tmpDir(.{});
    defer temp_dir.cleanup();

    var previous_dir = try std.Io.Dir.cwd().openDir(io, ".", .{});
    defer previous_dir.close(io);

    try std.process.setCurrentDir(io, temp_dir.dir);
    defer std.process.setCurrentDir(io, previous_dir) catch unreachable;

    var state: AppState = undefined;
    state.allocator = std.testing.allocator;
    state.runtime_root_path = "runtime";
    state.high_score_tables = high_score.Tables.initDefault();
    defer state.high_score_tables.deinit(std.testing.allocator);
    state.runtime_config = config.Blob.initDefault();
    state.active_frontend_mode = .challenge;
    state.active_frontend_level_index = 0;
    state.current_track_preview = null;
    state.current_level = null;
    state.current_runtime_build_seed = 0;
    state.selected_level_record_override = null;
    state.selected_level_record_source = null;
    state.selected_replay_cache = null;
    state.saved_outer_owner = frontend_bridge.outerOwnerStateChallengeSetupMenu();

    for (state.high_score_tables.challenge[0..high_score.visible_entry_count], 0..) |*entry, index| {
        entry.* = .{ .score = @as(u32, @intCast(100 - index)) };
    }

    const staged = (try state.standalonePostLevelHighScoreEntry(.{
        .outcome = .failed,
        .level_name = "Challenge",
        .mode = .challenge,
        .elapsed_millis = 30_000,
        .parcel_count = 0,
        .parcel_target = 0,
        .score = 900,
        .score_is_partial = true,
        .completion_owner = .challenge_failure,
        .persistence = .failed,
        .outer_return_target = .challenge_setup_menu,
    })) orelse return error.TestExpectedPendingHighScoreEntry;

    try std.testing.expectEqual(high_score.Mode.challenge, staged.context.mode);
    try std.testing.expectEqual(@as(usize, 0), staged.context.rank);
    try std.testing.expectEqual(frontend_bridge.OuterOwner.challenge_setup_menu, staged.return_owner.owner);
    try std.testing.expectEqual(frontend_bridge.OuterBridgeOpcode.rebuild_return, staged.return_opcode);
    try std.testing.expectEqual(@as(u32, 900), state.high_score_tables.challenge[0].score);
}

test "parity: transient time-trial replay abandon stays on the rebuild route-map lane" {
    var state: AppState = undefined;
    state.active_frontend_mode = .time_trial;
    state.active_frontend_level_index = 5;
    state.selected_level_record_override = null;
    state.selected_level_record_source = .{ .completion = 0 };
    state.selected_level_record_persistent = false;
    state.saved_replay_return_outer_owner = null;
    state.selected_level_record_outer_return_target = null;

    const samples = try std.testing.allocator.alloc(high_score.DecodedReplaySample, 1);
    samples[0] = .{ .lateral = 0, .secondary_lane = 0, .flags = 0 };
    state.selected_replay_cache = .{
        .allocator = std.testing.allocator,
        .samples = samples,
    };
    defer if (state.selected_replay_cache) |*replay| replay.deinit();

    var opcode: frontend_bridge.OuterBridgeOpcode = .destroy_return;
    const owner = state.outerOwnerForAbandonActiveRun(&opcode);

    try std.testing.expectEqual(frontend_bridge.OuterBridgeOpcode.rebuild_return, opcode);
    try std.testing.expectEqual(frontend_bridge.OuterOwner.route_map, owner.owner);
    try std.testing.expectEqual(FrontendLevelMode.time_trial, owner.route_map.mode);
    try std.testing.expectEqual(frontend_bridge.defaultRouteMapScreenMode(.time_trial), owner.route_map.screen_mode);
    try std.testing.expectEqual(@as(?usize, 5), owner.route_map.start_route_override);
}

test "high-score browse owner drives table toggles while post-level entry stays fixed" {
    var state: AppState = undefined;
    state.high_scores_menu_index = frontend_high_score_screen.modeIndex(.postal);
    state.high_score_screen_owner = .{ .main_menu_browse = .postal };

    try state.performHighScoreMenuAction(.switch_table);
    try std.testing.expectEqual(high_score.Mode.challenge, state.activeHighScoreScreenMode());

    state.high_score_screen_owner = .{ .post_level_entry = .{
        .mode = .postal,
        .rank = 3,
    } };
    try state.performHighScoreMenuAction(.switch_table);
    try std.testing.expectEqual(high_score.Mode.postal, state.activeHighScoreScreenMode());
}

test "parity: high-score browse back returns to the owning frontend controller" {
    const postal_owner = frontend_bridge.highScoreBrowseBackOwner(.postal);
    try std.testing.expectEqual(frontend_bridge.OuterOwner.new_game_menu, postal_owner.owner);
    try std.testing.expectEqual(NewGameMenuItem.postal_mode, postal_owner.new_game_menu_item);

    const challenge_owner = frontend_bridge.highScoreBrowseBackOwner(.challenge);
    try std.testing.expectEqual(frontend_bridge.OuterOwner.challenge_setup_menu, challenge_owner.owner);
}

test "thanks screen message sequence matches the recovered owner timing" {
    var controller = frontend_thanks.Controller{};
    try std.testing.expectEqualStrings("Thanks For Playing!", controller.currentText().?);
    try std.testing.expect(!controller.allowsContinue());

    for (0..241) |_| controller.step();
    try std.testing.expectEqual(frontend_thanks.Stage.title_hidden, controller.stage);
    try std.testing.expectEqual(@as(?[]const u8, null), controller.currentText());

    for (0..31) |_| controller.step();
    try std.testing.expectEqual(frontend_thanks.Stage.challenge_visible, controller.stage);
    try std.testing.expectEqualStrings("Test your reflexes in Challenge Mode!", controller.currentText().?);
    try std.testing.expect(controller.allowsContinue());

    for (0..241) |_| controller.step();
    try std.testing.expectEqual(frontend_thanks.Stage.challenge_hidden, controller.stage);
    try std.testing.expectEqual(@as(?[]const u8, null), controller.currentText());

    for (0..31) |_| controller.step();
    try std.testing.expectEqual(frontend_thanks.Stage.time_trial_visible, controller.stage);
    try std.testing.expectEqualStrings("Improve your skills in Time Trial!", controller.currentText().?);

    for (0..241) |_| controller.step();
    try std.testing.expectEqual(frontend_thanks.Stage.time_trial_hidden, controller.stage);
    try std.testing.expectEqual(@as(?[]const u8, null), controller.currentText());

    for (0..31) |_| controller.step();
    try std.testing.expectEqual(frontend_thanks.Stage.continue_visible, controller.stage);
    try std.testing.expectEqualStrings("Click to Continue", controller.currentText().?);

    for (0..241) |_| controller.step();
    try std.testing.expectEqual(frontend_thanks.Stage.continue_hold, controller.stage);
    try std.testing.expectEqualStrings("Click to Continue", controller.currentText().?);
    try std.testing.expectEqual(@as(f32, 0.0), controller.progress_step);
}

test "thanks screen exit follows the native credits handoff" {
    var state: AppState = undefined;
    state.audio_ready = false;
    state.frontend_transition = .{};
    state.thanks_screen_controller = .{};

    state.beginThanksScreenExit();
    try std.testing.expectEqual(frontend.FrontendTransitionState.idle, state.frontend_transition.state);
    try std.testing.expectEqual(@as(?GamePhase, null), state.frontend_transition.pending_phase);

    state.thanks_screen_controller.stage = .challenge_visible;
    state.beginThanksScreenExit();
    try std.testing.expectEqual(frontend.FrontendTransitionState.fading_out, state.frontend_transition.state);
    try std.testing.expectEqual(@as(?GamePhase, .credits), state.frontend_transition.pending_phase);
}

test "preview descending high-score rank matches visible insertion rules" {
    var tables = high_score.Tables.initDefault();
    defer tables.deinit(std.testing.allocator);

    for (tables.postal[0..high_score.visible_entry_count], 0..) |*entry, index| {
        entry.* = .{ .score = @as(u32, @intCast(1000 - index * 10)) };
    }

    try std.testing.expectEqual(@as(?usize, 5), AppState.previewDescendingHighScoreRank(tables.postal[0..], 955));
    try std.testing.expectEqual(@as(?usize, null), AppState.previewDescendingHighScoreRank(tables.postal[0..], 900));
}

test "current run high-score entry carries replay mode and build settings" {
    var state: AppState = undefined;
    state.runtime_config = config.Blob.initDefault();
    state.runtime_config.setChallengeReplaySpeedValue(100);
    state.runtime_config.setChallengeReplayDifficultyValue(55);
    state.active_frontend_mode = .challenge;
    state.active_frontend_level_index = 7;
    state.current_track_preview = null;
    state.current_runtime_build_seed = 321;
    state.selected_level_record_override = null;
    state.selected_replay_cache = null;

    const entry = state.currentRunHighScoreEntry(12_345);
    try std.testing.expectEqual(@as(u32, 12_345), entry.score);
    try std.testing.expectEqual(@as(u32, 7), entry.replay_level_index);
    try std.testing.expectEqual(@as(u32, 1), entry.replay_mode_id);
    try std.testing.expectEqual(@as(u32, 100), entry.challenge_speed_value);
    try std.testing.expectApproxEqAbs(@as(f32, 1.1), entry.replay_speed_scalar, 0.0001);
    try std.testing.expectEqual(@as(u32, 55), entry.challenge_difficulty_value);
    try std.testing.expectEqual(@as(u32, track.defaultRuntimeBuildFlags), entry.runtime_build_flags);
    try std.testing.expectApproxEqAbs(@as(f32, 0.55), entry.challenge_difficulty_scalar, 0.0001);
    try std.testing.expectEqual(@as(u32, 321), entry.runtime_build_seed);
    try std.testing.expectApproxEqAbs(@as(f32, 0.44), entry.garbage_scalar, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.44), entry.salt_scalar, 0.0001);
}

test "challenge parcel target matches recovered placement formula" {
    try std.testing.expectEqual(@as(usize, 1), AppState.challengeParcelTargetCount(0, 0.0));
    try std.testing.expectEqual(@as(usize, 41), AppState.challengeParcelTargetCount(40, 0.4));
    try std.testing.expectEqual(@as(usize, 78), AppState.challengeParcelTargetCount(100, 0.55));
}

test "current parcel target prefers live preview count" {
    var state: AppState = undefined;
    var preview: track.LoadedLevelPreview = undefined;
    preview.parcel_target_count = 37;
    state.current_track_preview = preview;
    state.current_level = null;
    try std.testing.expectEqual(@as(usize, 37), state.currentParcelTarget());

    var loaded_level: level.Definition = undefined;
    loaded_level.parcels = 9;
    state.current_track_preview = null;
    state.current_level = loaded_level;
    try std.testing.expectEqual(@as(usize, 9), state.currentParcelTarget());
}

test "mode-specific runtime build flags follow recovered subgame presets" {
    var state: AppState = undefined;
    state.current_track_preview = null;
    state.selected_level_record_override = null;
    state.selected_replay_cache = null;

    state.active_frontend_mode = .postal;
    try std.testing.expectEqual(@as(u32, track.postalChallengeRuntimeBuildFlags), state.currentRunRuntimeBuildFlags());

    state.active_frontend_mode = .challenge;
    try std.testing.expectEqual(@as(u32, track.postalChallengeRuntimeBuildFlags), state.currentRunRuntimeBuildFlags());

    state.active_frontend_mode = .time_trial;
    try std.testing.expectEqual(@as(u32, track.timeTrialRuntimeBuildFlags), state.currentRunRuntimeBuildFlags());

    state.active_frontend_mode = .tutorial;
    try std.testing.expectEqual(@as(u32, track.tutorialRuntimeBuildFlags), state.currentRunRuntimeBuildFlags());
}

test "selected level record override follows recovered compact lanes" {
    const entry = high_score.Entry{
        .replay_level_index = 12,
        .replay_mode_id = 4,
        .runtime_build_flags = 0x0075cfff,
        .replay_speed_scalar = 0.74,
        .challenge_speed_value = 55,
        .challenge_difficulty_value = 40,
        .challenge_difficulty_scalar = 0.4,
        .runtime_build_seed = 222,
        .garbage_scalar = 0.32,
        .salt_scalar = 0.45,
    };
    const record = frontend_bridge.SelectedLevelRecordOverride.fromHighScoreEntry(&entry) orelse return error.TestUnexpectedResult;

    try std.testing.expectEqual(FrontendLevelMode.time_trial, record.mode);
    try std.testing.expectEqual(@as(usize, 12), record.level_index);
    try std.testing.expectEqual(@as(u32, 0x0075cfff), record.runtime_build_flags);
    try std.testing.expectApproxEqAbs(@as(f32, 0.74), record.replay_speed_scalar, 0.0001);
    try std.testing.expectEqual(@as(u32, 55), record.challenge_speed_value);
    try std.testing.expectEqual(@as(u32, 40), record.challenge_difficulty_value);
    try std.testing.expectApproxEqAbs(@as(f32, 0.4), record.challenge_difficulty_scalar, 0.0001);
    try std.testing.expectEqual(@as(u32, 222), record.runtime_build_seed);
    try std.testing.expectApproxEqAbs(@as(f32, 0.32), record.garbage_scalar, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.45), record.salt_scalar, 0.0001);
}

test "selected level record override rejects unresolved mode ids" {
    const entry = high_score.Entry{
        .replay_level_index = 1,
        .replay_mode_id = 3,
    };
    try std.testing.expect(frontend_bridge.SelectedLevelRecordOverride.fromHighScoreEntry(&entry) == null);
}

test "selected replay directive decodes compact lateral x and the secondary lane" {
    var tables = high_score.Tables.initDefault();
    defer tables.deinit(std.testing.allocator);

    const record_len = 0x88 + 5;
    const raw_record = try std.testing.allocator.alloc(u8, record_len);
    @memset(raw_record, 0);
    std.mem.writeInt(u32, raw_record[0x74..0x78], 1, .little);
    std.mem.writeInt(i16, raw_record[0x88..0x8a], 0x1800, .little);
    std.mem.writeInt(i16, raw_record[0x8a..0x8c], 0, .little);
    raw_record[0x8c] = 0x0c;
    tables.completion[0].raw_record = raw_record;
    tables.completion[0].has_replay = true;

    var replay = try tables.completion[0].decodeReplay(std.testing.allocator);
    defer replay.deinit();

    const first = selected_replay.directiveForDecodedReplay(&replay, 0);
    try std.testing.expect(first.active);
    try std.testing.expectApproxEqAbs(@as(f32, 1.5), first.lateral_world_x.?, 0.0001);
    try std.testing.expectEqual(@as(?i32, 0), first.secondary_lane);
    try std.testing.expectEqual(@as(u8, 0x0c), first.raw_flag_bits);

    const tail = selected_replay.directiveForDecodedReplay(&replay, 1);
    try std.testing.expect(tail.active);
    try std.testing.expect(tail.lateral_world_x == null);
    try std.testing.expectEqual(@as(u8, 0), tail.raw_flag_bits);
}

test "selected replay results skip persistence and score-table awards" {
    var state: AppState = undefined;
    state.high_score_tables = high_score.Tables.initDefault();
    defer state.high_score_tables.deinit(std.testing.allocator);
    state.selected_level_record_override = null;
    state.active_frontend_mode = null;
    state.selected_level_record_source = .{ .challenge = 2 };
    state.selected_level_record_persistent = false;
    state.saved_replay_return_outer_owner = null;
    state.selected_level_record_outer_return_target = null;
    state.selected_replay_cache = null;

    const raw_record = try std.testing.allocator.alloc(u8, 0x88 + 5);
    @memset(raw_record, 0);
    std.mem.writeInt(u32, raw_record[0x74..0x78], 1, .little);
    state.high_score_tables.challenge[2].raw_record = raw_record;
    state.high_score_tables.challenge[2].has_replay = true;
    state.selected_replay_cache = try state.high_score_tables.challenge[2].decodeReplay(std.testing.allocator);
    defer if (state.selected_replay_cache) |*replay| replay.deinit();

    var result = PendingRunResult{
        .level_name = "Replay",
        .mode = .challenge,
        .elapsed_millis = 1234,
        .parcel_count = 0,
        .parcel_target = 0,
        .score = 42_000,
        .score_is_partial = true,
        .high_score_mode = .challenge,
        .high_score_rank = 3,
        .time_trial_record_improved = true,
        .unlocked_next_route = true,
        .persistence = .completed,
        .outer_return_target = .main_menu,
    };
    run_result.applySelectedReplayResultOverrides(&state, &result);

    try std.testing.expectEqual(PendingRunPersistence.none, result.persistence);
    try std.testing.expect(result.high_score_mode == null);
    try std.testing.expect(result.high_score_rank == null);
    try std.testing.expect(!result.time_trial_record_improved);
    try std.testing.expect(!result.unlocked_next_route);
    try std.testing.expectEqual(frontend_bridge.OuterReturnTarget.high_scores_menu, result.outer_return_target);
}

test "transient postal replay failure stays off the post-level high-score lane" {
    var state: AppState = undefined;
    state.selected_level_record_override = null;
    state.active_frontend_mode = null;
    state.selected_level_record_source = .{ .postal = 2 };
    state.selected_level_record_persistent = false;
    state.saved_replay_return_outer_owner = null;
    state.selected_level_record_outer_return_target = null;

    const samples = try std.testing.allocator.alloc(high_score.DecodedReplaySample, 1);
    samples[0] = .{ .lateral = 0, .secondary_lane = 0, .flags = 0 };
    state.selected_replay_cache = .{
        .allocator = std.testing.allocator,
        .samples = samples,
    };
    defer if (state.selected_replay_cache) |*replay| replay.deinit();

    var result = PendingRunResult{
        .outcome = .failed,
        .level_name = "Replay",
        .mode = .postal,
        .elapsed_millis = 1234,
        .parcel_count = 0,
        .parcel_target = 0,
        .score = 42_000,
        .score_is_partial = true,
        .high_score_mode = .postal,
        .high_score_rank = 0,
        .completion_owner = .postal_failure,
        .persistence = .failed,
        .outer_return_target = .main_menu,
    };
    run_result.applySelectedReplayResultOverrides(&state, &result);

    try std.testing.expectEqual(PendingRunPersistence.none, result.persistence);
    try std.testing.expect(result.high_score_mode == null);
    try std.testing.expect(result.high_score_rank == null);
    try std.testing.expectEqual(frontend_bridge.OuterReturnTarget.high_scores_menu, result.outer_return_target);

    state.pending_run_result = result;
    try std.testing.expectEqual(@as(?frontend_high_score_screen.PendingEntry, null), state.pendingRunHighScoreContext());
    try std.testing.expectEqual(@as(?StandalonePostLevelHighScoreEntry, null), state.failedResultPostLevelHighScoreEntry());
}

test "selected level record override drives live run tuning lanes" {
    var state: AppState = undefined;
    state.runtime_config = config.Blob.initDefault();
    state.current_track_preview = null;
    state.current_level = null;
    state.active_frontend_mode = .challenge;
    state.selected_replay_cache = null;
    state.selected_level_record_override = .{
        .mode = .challenge,
        .level_index = 0,
        .runtime_build_flags = 0x00f5cfff,
        .replay_speed_scalar = 0.56,
        .challenge_speed_value = 40,
        .challenge_difficulty_value = 55,
        .challenge_difficulty_scalar = 0.55,
        .runtime_build_seed = 444,
        .garbage_scalar = 0.12,
        .salt_scalar = 0.34,
    };

    try std.testing.expectApproxEqAbs(@as(f32, 0.56), state.currentRunReplaySpeedScalar(), 0.0001);
    try std.testing.expectEqual(@as(u32, 40), state.currentRunChallengeSpeedValue());
    try std.testing.expectEqual(@as(u32, 55), state.currentRunChallengeDifficultyValue());
    try std.testing.expectApproxEqAbs(@as(f32, 0.55), state.currentRunChallengeDifficultyScalar(), 0.0001);
    try std.testing.expectEqual(@as(u32, 0x00f5cfff), state.currentRunRuntimeBuildFlags());
    try std.testing.expectApproxEqAbs(@as(f32, 0.12), state.currentRunGarbageScalar(), 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.34), state.currentRunSaltScalar(), 0.0001);
}

test "selected level record override seeds track rebuilds without frontend rng" {
    var state: AppState = undefined;
    state.command = .game;
    state.active_frontend_mode = .time_trial;
    state.active_frontend_level_index = 9;
    state.level_index = 123;
    state.current_runtime_build_seed = 0;
    state.current_runtime_build_seed_level_index = null;
    state.current_runtime_build_seed_mode = null;
    state.selected_level_record_override = .{
        .mode = .time_trial,
        .level_index = 9,
        .runtime_build_flags = track.timeTrialRuntimeBuildFlags,
        .replay_speed_scalar = 0.74,
        .challenge_speed_value = 0,
        .challenge_difficulty_value = 0,
        .challenge_difficulty_scalar = 0.0,
        .runtime_build_seed = 777,
        .garbage_scalar = 0.11,
        .salt_scalar = 0.22,
    };

    try std.testing.expectEqual(@as(u32, 777), state.trackBuildSeedForCurrentLoad());
    try std.testing.expectEqual(@as(u32, 777), state.current_runtime_build_seed);
    try std.testing.expectEqual(@as(?usize, 123), state.current_runtime_build_seed_level_index);
    try std.testing.expectEqual(@as(?FrontendLevelMode, .time_trial), state.current_runtime_build_seed_mode);
}

fn seededLiveSubgameCamera(runner_input: gameplay.Runner) SubgameCameraState {
    var runner = runner_input;
    var camera_state = SubgameCameraState{};
    subgame_camera.updateState(&camera_state, subgame_camera.selectionForRunner(&runner));
    return camera_state;
}

test "gameplay camera looks ahead of the runner" {
    var catalog = try assets.Catalog.init(std.testing.allocator, default_archive_path);
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath(default_level_path) orelse return error.EntryNotFound;
    var loaded_level = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer loaded_level.deinit();

    var loaded_track_preview = try track.LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &loaded_level,
        .{ .load_models = false },
    );
    defer loaded_track_preview.deinit();

    var runner = gameplay.Runner.init(&loaded_track_preview);
    runner.step(&loaded_track_preview, .{}, @floatCast(simulation_step_seconds));
    const camera_state = seededLiveSubgameCamera(runner);

    const camera = subgame_camera.levelCamera(&camera_state, &loaded_track_preview, camera_state.fov_degrees);
    const transform = subgame_camera.transformFromMatrix(camera_state.shared_matrix);
    const player_position = runner.worldPosition(&loaded_track_preview, 0.82);
    try std.testing.expect(camera.target.z > camera.position.z);
    try std.testing.expect(camera.position.z < player_position.z);
    try std.testing.expect(camera.position.y > 0.0);
    try std.testing.expectApproxEqAbs(transform.position.x + transform.forward.x, camera.target.x, 0.001);
    try std.testing.expectApproxEqAbs(transform.position.y + transform.forward.y, camera.target.y, 0.001);
    try std.testing.expectApproxEqAbs(transform.position.z + transform.forward.z, camera.target.z, 0.001);
    try std.testing.expectApproxEqAbs(runner.cameramanFovDegrees(), camera.fovy, 0.001);
}

test "gameplay camera keeps lateral steering mostly behind turbo" {
    var catalog = try assets.Catalog.init(std.testing.allocator, default_archive_path);
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath(default_level_path) orelse return error.EntryNotFound;
    var loaded_level = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer loaded_level.deinit();

    var loaded_track_preview = try track.LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &loaded_level,
        .{ .load_models = false },
    );
    defer loaded_track_preview.deinit();

    var runner = gameplay.Runner.init(&loaded_track_preview);
    runner.lane_center = 6.5;
    runner.lane_index = 6;
    runner.resolved_lane_index = 6;
    runner.step(&loaded_track_preview, .{}, @floatCast(simulation_step_seconds));
    const camera_state = seededLiveSubgameCamera(runner);

    const camera = subgame_camera.levelCamera(&camera_state, &loaded_track_preview, camera_state.fov_degrees);
    const player_position = runner.worldPosition(&loaded_track_preview, 0.82);

    try std.testing.expect(player_position.x > 0.0);
    try std.testing.expect(camera.position.x > 0.0);
    try std.testing.expect(camera.target.x > 0.0);
    try std.testing.expect(camera.target.x < player_position.x);
    try std.testing.expect(camera.position.x <= player_position.x);
}

test "shared gameplay camera derives target and up from the shared matrix" {
    var catalog = try assets.Catalog.init(std.testing.allocator, default_archive_path);
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath(default_level_path) orelse return error.EntryNotFound;
    var loaded_level = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer loaded_level.deinit();

    var loaded_track_preview = try track.LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &loaded_level,
        .{ .load_models = false },
    );
    defer loaded_track_preview.deinit();

    var runner = gameplay.Runner.init(&loaded_track_preview);
    runner.step(&loaded_track_preview, .{}, @floatCast(simulation_step_seconds));
    const camera_state = seededLiveSubgameCamera(runner);
    const camera = subgame_camera.levelCamera(&camera_state, &loaded_track_preview, camera_state.fov_degrees);
    const transform = subgame_camera.transformFromMatrix(camera_state.shared_matrix);
    try std.testing.expectApproxEqAbs(transform.position.x, camera.position.x, 0.001);
    try std.testing.expectApproxEqAbs(transform.position.y, camera.position.y, 0.001);
    try std.testing.expectApproxEqAbs(transform.position.z, camera.position.z, 0.001);
    try std.testing.expectApproxEqAbs(transform.up.x, camera.up.x, 0.001);
    try std.testing.expectApproxEqAbs(transform.up.y, camera.up.y, 0.001);
    try std.testing.expectApproxEqAbs(transform.up.z, camera.up.z, 0.001);
    try std.testing.expectApproxEqAbs(transform.position.z + transform.forward.z, camera.target.z, 0.001);
}

test "intro cutscene override seeds the shared camera and later clears back to live" {
    var catalog = try assets.Catalog.init(std.testing.allocator, default_archive_path);
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath(default_level_path) orelse return error.EntryNotFound;
    var loaded_level = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer loaded_level.deinit();

    var loaded_track_preview = try track.LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &loaded_level,
        .{ .load_models = false },
    );
    defer loaded_track_preview.deinit();

    var runner = gameplay.Runner.init(&loaded_track_preview);
    var camera_state = SubgameCameraState{};
    runner.setCutscene(gameplay.cutscene_intro_id);
    runner.refreshCameraState(&loaded_track_preview);
    subgame_camera.updateState(&camera_state, subgame_camera.selectionForRunner(&runner));

    try std.testing.expectEqual(subgame_camera.Source.override, camera_state.source);
    try std.testing.expectApproxEqAbs(@as(f32, 110.0), camera_state.fov_degrees, 0.001);

    for (0..gameplay.intro_cutscene_duration_ticks + 2) |_| {
        runner.refreshCameraState(&loaded_track_preview);
        subgame_camera.updateState(&camera_state, subgame_camera.selectionForRunner(&runner));
    }

    try std.testing.expectEqual(gameplay.cutscene_none_id, runner.cutscene_id);
    try std.testing.expectEqual(subgame_camera.Source.live, camera_state.source);
}

test "blocked click-start refresh path primes the tutorial start attachment camera" {
    var catalog = try assets.Catalog.init(std.testing.allocator, default_archive_path);
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath(default_level_path) orelse return error.EntryNotFound;
    var loaded_level = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer loaded_level.deinit();

    var loaded_track_preview = try track.LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &loaded_level,
        .{ .load_models = false },
    );
    defer loaded_track_preview.deinit();

    var runner = gameplay.Runner.init(&loaded_track_preview);
    var camera_state = SubgameCameraState{};

    runner.refreshBlockedStartupState(&loaded_track_preview);
    subgame_camera.updateState(&camera_state, subgame_camera.selectionForRunner(&runner));

    const camera = subgame_camera.levelCamera(&camera_state, &loaded_track_preview, camera_state.fov_degrees);
    try std.testing.expectEqual(gameplay.MovementMode.attachment, runner.movement_mode);
    try std.testing.expect(runner.worldPosition(&loaded_track_preview, 0.0).y >= 7.9);
    try std.testing.expect(camera.position.y > 0.0);
    try std.testing.expect(camera.target.z > camera.position.z);
    try std.testing.expect(camera_state.source == .live);
    try std.testing.expect(!camera_state.snap_next);
}

test "intro cutscene click-start path still primes the tutorial start attachment under override camera" {
    var catalog = try assets.Catalog.init(std.testing.allocator, default_archive_path);
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath(default_level_path) orelse return error.EntryNotFound;
    var loaded_level = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer loaded_level.deinit();

    var loaded_track_preview = try track.LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &loaded_level,
        .{ .load_models = false },
    );
    defer loaded_track_preview.deinit();

    var runner = gameplay.Runner.init(&loaded_track_preview);
    var camera_state = SubgameCameraState{};
    runner.setCutscene(gameplay.cutscene_intro_id);

    runner.refreshBlockedStartupState(&loaded_track_preview);
    subgame_camera.updateState(&camera_state, subgame_camera.selectionForRunner(&runner));

    try std.testing.expectEqual(gameplay.MovementMode.attachment, runner.movement_mode);
    try std.testing.expect(runner.attachment_follow.active);
    try std.testing.expectEqual(subgame_camera.Source.override, camera_state.source);
    try std.testing.expect(runner.cutsceneCameraActive());
}

test "startup block after click-start dismissal resumes the live runner under intro camera" {
    var catalog = try assets.Catalog.init(std.testing.allocator, default_archive_path);
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath(default_level_path) orelse return error.EntryNotFound;
    var loaded_level = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer loaded_level.deinit();

    var loaded_track_preview = try track.LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &loaded_level,
        .{ .load_models = false },
    );
    defer loaded_track_preview.deinit();

    var state: AppState = undefined;
    state.gameplay_click_start_active = false;
    state.level_runner = gameplay.Runner.init(&loaded_track_preview);
    state.level_runner.?.setCutscene(gameplay.cutscene_intro_id);
    state.level_runner.?.refreshBlockedStartupState(&loaded_track_preview);
    const starting_row_position = state.level_runner.?.row_position;

    try std.testing.expect(state.startupGameplayBlockActive());

    state.refreshRunnerForStartupBlock(
        &state.level_runner.?,
        &loaded_track_preview,
        @floatCast(simulation_step_seconds),
    );

    try std.testing.expectEqual(gameplay.MovementMode.attachment, state.level_runner.?.movement_mode);
    try std.testing.expect(state.level_runner.?.attachment_follow.active);
    try std.testing.expect(state.level_runner.?.cutsceneCameraActive());
    try std.testing.expect(state.level_runner.?.movement_rate_scalar > 0.0);
    try std.testing.expect(state.level_runner.?.row_position > starting_row_position);
}

test "intro light streak camera falls back to the default star-field camera" {
    var state: AppState = undefined;
    state.game_phase = .intro;
    state.subgame_camera = .{};

    const camera = render_phase.lightStreakCamera(&state);
    try std.testing.expectApproxEqAbs(render_phase.default_light_streak_camera.position.x, camera.position.x, 0.001);
    try std.testing.expectApproxEqAbs(render_phase.default_light_streak_camera.position.y, camera.position.y, 0.001);
    try std.testing.expectApproxEqAbs(render_phase.default_light_streak_camera.position.z, camera.position.z, 0.001);
    try std.testing.expectApproxEqAbs(render_phase.default_light_streak_camera.fov_degrees, camera.fov_degrees, 0.001);
    try std.testing.expectApproxEqAbs(render_phase.default_light_streak_camera.forward.x, camera.forward.x, 0.001);
    try std.testing.expectApproxEqAbs(render_phase.default_light_streak_camera.forward.y, camera.forward.y, 0.001);
    try std.testing.expectApproxEqAbs(render_phase.default_light_streak_camera.forward.z, camera.forward.z, 0.001);
}

test "credits phase keeps the native star-field visibility" {
    var state: AppState = undefined;
    state.game_phase = .credits;
    state.options_return_phase = .main_menu;
    state.exit_prompt_return_phase = .main_menu;

    try std.testing.expect(render_phase.lightStreaksVisible(&state));
}

test "shared subgame camera honors snap flags and otherwise blends across source changes" {
    const basis_right = rl.Vector3{ .x = 1.0, .y = 0.0, .z = 0.0 };
    const basis_up = rl.Vector3{ .x = 0.0, .y = 1.0, .z = 0.0 };
    const basis_forward = rl.Vector3{ .x = 0.0, .y = 0.0, .z = 1.0 };
    const live_matrix = modelTransformFromBasis(.{ .x = 1.0, .y = 2.0, .z = 3.0 }, basis_right, basis_up, basis_forward);
    const override_matrix = modelTransformFromBasis(.{ .x = 5.0, .y = 6.0, .z = 7.0 }, basis_right, basis_up, basis_forward);
    const next_live_matrix = modelTransformFromBasis(.{ .x = 9.0, .y = 10.0, .z = 11.0 }, basis_right, basis_up, basis_forward);
    var state = SubgameCameraState{};

    subgame_camera.updateState(&state, .{
        .source = .live,
        .matrix = live_matrix,
        .fov_degrees = 110.0,
        .snap_next = true,
    });
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), state.shared_matrix.m12, 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 2.0), state.shared_matrix.m13, 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 3.0), state.shared_matrix.m14, 0.001);

    subgame_camera.updateState(&state, .{
        .source = .override,
        .matrix = override_matrix,
        .fov_degrees = 110.0,
        .snap_next = true,
    });
    try std.testing.expectApproxEqAbs(@as(f32, 5.0), state.shared_matrix.m12, 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 6.0), state.shared_matrix.m13, 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 7.0), state.shared_matrix.m14, 0.001);

    subgame_camera.updateState(&state, .{
        .source = .live,
        .matrix = live_matrix,
        .fov_degrees = 120.0,
        .snap_next = false,
    });
    try std.testing.expectApproxEqAbs(std.math.lerp(@as(f32, 5.0), @as(f32, 1.0), subgame_camera.blend_factor), state.shared_matrix.m12, 0.001);
    try std.testing.expectApproxEqAbs(std.math.lerp(@as(f32, 6.0), @as(f32, 2.0), subgame_camera.blend_factor), state.shared_matrix.m13, 0.001);
    try std.testing.expectApproxEqAbs(std.math.lerp(@as(f32, 7.0), @as(f32, 3.0), subgame_camera.blend_factor), state.shared_matrix.m14, 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 120.0), state.fov_degrees, 0.001);

    subgame_camera.updateState(&state, .{
        .source = .live,
        .matrix = next_live_matrix,
        .fov_degrees = 130.0,
        .snap_next = false,
    });
    try std.testing.expectApproxEqAbs(
        std.math.lerp(
            std.math.lerp(@as(f32, 5.0), @as(f32, 1.0), subgame_camera.blend_factor),
            @as(f32, 9.0),
            subgame_camera.blend_factor,
        ),
        state.shared_matrix.m12,
        0.001,
    );
    try std.testing.expectApproxEqAbs(
        std.math.lerp(
            std.math.lerp(@as(f32, 6.0), @as(f32, 2.0), subgame_camera.blend_factor),
            @as(f32, 10.0),
            subgame_camera.blend_factor,
        ),
        state.shared_matrix.m13,
        0.001,
    );
    try std.testing.expectApproxEqAbs(
        std.math.lerp(
            std.math.lerp(@as(f32, 7.0), @as(f32, 3.0), subgame_camera.blend_factor),
            @as(f32, 11.0),
            subgame_camera.blend_factor,
        ),
        state.shared_matrix.m14,
        0.001,
    );
    try std.testing.expectApproxEqAbs(@as(f32, 130.0), state.fov_degrees, 0.001);
}

test "non-live subgame camera sources force the recovered 110-degree FOV" {
    try std.testing.expectApproxEqAbs(@as(f32, 160.0), subgame_camera.fovDegreesForSource(.live, 160.0), 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 110.0), subgame_camera.fovDegreesForSource(.override, 160.0), 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 110.0), subgame_camera.fovDegreesForSource(.identity, 160.0), 0.001);
}

test "mouse lane-center target mapping respects bounds" {
    const bounds: track.LaneBounds = .{ .min = 2, .max = 4 };
    var catalog = try assets.Catalog.init(std.testing.allocator, default_archive_path);
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath(default_level_path) orelse return error.EntryNotFound;
    var loaded_level = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer loaded_level.deinit();

    var loaded_track_preview = try track.LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &loaded_level,
        .{ .load_models = false },
    );
    defer loaded_track_preview.deinit();

    try std.testing.expectApproxEqAbs(@as(f32, 4.5), subgame_camera.laneCenterTargetForMouseX(loaded_track_preview, 0.0, 1280.0, bounds), 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 4.5), subgame_camera.laneCenterTargetForMouseX(loaded_track_preview, 640.0, 1280.0, bounds), 0.01);
    try std.testing.expectApproxEqAbs(@as(f32, 2.5), subgame_camera.laneCenterTargetForMouseX(loaded_track_preview, 1279.0, 1280.0, bounds), 0.001);
}

test "tutorial startup mouse steering matches the native mirrored authored x axis" {
    var catalog = try assets.Catalog.init(std.testing.allocator, default_archive_path);
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath(default_level_path) orelse return error.EntryNotFound;
    var loaded_level = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer loaded_level.deinit();

    var loaded_track_preview = try track.LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &loaded_level,
        .{ .load_models = false },
    );
    defer loaded_track_preview.deinit();

    var runner = gameplay.Runner.init(&loaded_track_preview);
    runner.refreshBlockedStartupState(&loaded_track_preview);

    const probe_row_position = std.math.clamp(
        runner.row_position + 6.0,
        0.0,
        @max(@as(f32, @floatFromInt(loaded_track_preview.total_rows)) - 0.001, 0.0),
    );
    const probe_global_row = loaded_track_preview.rowIndexAtWorldZ(probe_row_position);
    const row_location = loaded_track_preview.locateRow(probe_global_row) orelse return error.TestUnexpectedResult;
    const bounds = loaded_track_preview.laneBoundsForRow(row_location);
    const left_target = subgame_camera.laneCenterTargetForMouseX(loaded_track_preview, 0.0, 1280.0, bounds);
    const right_target = subgame_camera.laneCenterTargetForMouseX(loaded_track_preview, 1279.0, 1280.0, bounds);

    try std.testing.expect(left_target > right_target);
}

test "tutorial mouse center maps to the authored track center after startup" {
    var catalog = try assets.Catalog.init(std.testing.allocator, default_archive_path);
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath(default_level_path) orelse return error.EntryNotFound;
    var loaded_level = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer loaded_level.deinit();

    var loaded_track_preview = try track.LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &loaded_level,
        .{ .load_models = false },
    );
    defer loaded_track_preview.deinit();

    const row_location = loaded_track_preview.locateRow(track.defaultRuntimeActiveRowStart) orelse return error.TestUnexpectedResult;
    const bounds = loaded_track_preview.laneBoundsForRow(row_location);
    try std.testing.expectApproxEqAbs(
        @as(f32, 5.0),
        subgame_camera.laneCenterTargetForMouseX(loaded_track_preview, 640.0, 1280.0, bounds),
        0.01,
    );
}
