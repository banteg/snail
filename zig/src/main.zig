const std = @import("std");
const rl = @import("raylib");
const app = @import("app.zig");
const audio = @import("app/audio.zig");
const audio_volume = @import("app/audio_volume.zig");
const boot_assets = @import("app/boot_assets.zig");
const frontend_audio = @import("app/frontend_audio.zig");
const frontend_flow = @import("app/frontend_flow.zig");
const frontend_input = @import("app/frontend_input.zig");
const frontend_mouse = @import("app/frontend_mouse.zig");
const game_tick = @import("app/game_tick.zig");
const level_loader = @import("app/level_loader.zig");
const math_random = @import("app/math_random.zig");
const music_audio = @import("app/music_audio.zig");
const new_game_replay_attract = @import("app/new_game_replay_attract.zig");
const phase_resources = @import("app/phase_resources.zig");
const render_phase = @import("app/render_phase.zig");
const return_flow = @import("app/return_flow.zig");
const route_map_state = @import("app/route_map_state.zig");
const run_result = @import("app/run_result.zig");
const run_tuning = @import("app/run_tuning.zig");
const screenshots = @import("app/screenshots.zig");
const screen_assets = @import("app/screen_assets.zig");
const selected_replay = @import("app/selected_replay.zig");
const subgame_camera = @import("app/subgame_camera.zig");
const track_build_seed = @import("app/track_build_seed.zig");
const voice_audio = @import("app/voice_audio.zig");
const window_state = @import("app/window_state.zig");
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
const gameplay_billboard = @import("gameplay/billboard.zig");
const gameplay_effects = @import("gameplay/effects.zig");
const gameplay = @import("gameplay.zig");
const gameplay_assets = @import("gameplay/assets.zig");
const gameplay_hud = @import("gameplay/hud.zig");
const gameplay_model_render = @import("gameplay/model_render.zig");
const gameplay_presentation = @import("gameplay/presentation.zig");
const gameplay_prompt_overlay = @import("gameplay/prompt_overlay.zig");
const gameplay_render_policy = @import("gameplay/render_policy.zig");
const gameplay_viewport_render = @import("gameplay/viewport_render.zig");
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

fn debugFrontendModeForLevelPath(level_path: []const u8) ?FrontendLevelMode {
    if (std.mem.eql(u8, level_path, "LEVELS/TUTORIAL.TXT")) return .tutorial;
    return .postal;
}
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
    new_game_replay_attract: new_game_replay_attract.Controller = .{},
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
    auto_dismiss_click_start: bool = false,
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
    replay_capture: high_score.ReplayCapture = .{},
    time_trial_ghost_replay_cache: ?high_score.DecodedReplay = null,
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
    gameplay_resources: gameplay_resources.State = .{},
    gameplay_jetpack_visual_state: GameplayJetpackVisualState = .{},
    gameplay_weapon_visual_state: GameplayWeaponVisualState = .{},
    gameplay_billboard_shader: ?rl.Shader = null,
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
        const gameplay_billboard_shader = try gameplay_billboard.loadAlphaCutoutShader();
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
            .mode = if (options.debug_mode) |mode_name| debug_browser.modeFromName(mode_name) orelse return error.InvalidDebugMode else .textures,
            .window_size = options.window_size_override orelse defaultWindowSizeForCommand(options.command),
            .audio_ready = audio_ready,
            .audio_muted = options.hidden_window,
            .challenge_setup_speed_display_value = @as(f32, @floatFromInt(runtime_config_result.blob.challengeReplaySpeedValue())) * 0.01,
            .challenge_setup_difficulty_display_value = @as(f32, @floatFromInt(runtime_config_result.blob.challengeReplayDifficultyValue())) * 0.01,
            .options_sound_display_value = runtime_config_result.blob.soundVolume(),
            .options_music_display_value = runtime_config_result.blob.musicVolume(),
            .mouse_local_override = options.mouse_local_override,
            .auto_screenshot = options.auto_screenshot,
            .auto_dismiss_click_start = options.auto_dismiss_click_start,
            .start_route_index_override = options.start_route_index,
            .start_pause_context = options.pause_context,
            .high_score_tables = high_score.Tables.initDefault(),
            .texture_index = texture_index,
            .audio_index = audio_index,
            .model_index = model_index,
            .object_index = object_index,
            .level_index = level_index,
            .segment_index = segment_index,
            .frontend_cursor_texture = frontend_cursor_texture,
            .frontend_widget_art = frontend_widget_art,
            .frontend_sound_fx = frontend_sound_fx,
            .gameplay_resources = .{
                .sound_fx = gameplay_sound_fx,
                .sprites = gameplay_sprites,
            },
            .slider_art = slider_art,
            .route_map_art = route_map_art,
            .current_background_light_streak_texture = background_light_streak_texture,
            .gameplay_billboard_shader = gameplay_billboard_shader,
            .galaxy_names = galaxy_names,
        };
        errdefer state.deinit();
        galaxy_names = null;
        audio_volume.applyConfigVolumes(audio_volume.context(&state));
        if (options.command == .game) {
            try gameplay_resources.loadStaticResources(&state.gameplay_resources, &state.resources);
        }

        switch (options.command) {
            .debug, .smoke => {
                try debug_browser.initialize(&state);
            },
            .game => if (options.debug_start_row) |row|
                try state.enterDebugLevelAt(options.debug_start_level_path orelse default_level_path, row, options.debug_start_lane)
            else if (options.start_level_intro)
                try state.beginFrontendLevelPath(.tutorial, 0, null, null)
            else if (options.start_mode) |start_mode|
                try state.enterStartMode(start_mode)
            else if (options.start_phase) |start_phase|
                try state.enterStartPhase(start_phase)
            else
                try state.enterGamePhase(.boot),
        }
        return state;
    }

    fn deinit(self: *AppState) void {
        music_audio.stopPreview(music_audio.context(self));
        self.unloadLoadingScreen();
        self.unloadGameBackground();
        boot_assets.unload(boot_assets.context(self));
        self.clearSelectedReplayCache();
        self.replay_capture.deinit(self.allocator);
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
        gameplay_resources.unloadStaticResources(&self.gameplay_resources);
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

        voice_audio.stopPlayback(voice_audio.context(self));
        self.clearTimeTrialGhostReplayCache();
        self.clearSelectedReplayCache();
        self.replay_capture.deinit(self.allocator);
        if (self.current_texture) |*texture| {
            texture.unload();
            self.current_texture = null;
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
                self.game_phase_ticks += 1;
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
        if (self.auto_dismiss_click_start and self.gameplayClickStartDismissible() and self.game_phase == .level) {
            self.auto_dismiss_click_start = false;
            try self.activateGameplayClickStart();
        }

        switch (self.command) {
            .game => return self.handleGameInput(),
            .smoke => return,
            .debug => return debug_browser.handleInput(self),
        }
    }

    fn currentUiLayout(self: *const AppState) VirtualLayout {
        _ = self;
        return window_state.currentUiLayout();
    }

    pub fn currentFrontendMouseLocal(self: *const AppState) ?rl.Vector2 {
        return self.currentUiMouseLocal();
    }

    pub fn currentUiMouseLocal(self: *const AppState) ?rl.Vector2 {
        return window_state.currentMouseLocal(window_state.viewContext(self));
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

    pub fn updatePendingFrontendActivation(self: *AppState) !bool {
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

    pub fn updateFrontendWidgetAnimations(self: *AppState) void {
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
        try game_tick.simulate(self, runner_input);
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
                    if (!self.gameplayClickStartDismissible()) return;
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
                            if (gameplay_prompt_overlay.activeOkHitRect(self.gameplayPromptContext(), &self.level_prompt_queue, true)) |ok_button| {
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
                if (accepts_live_replay_controls and (rl.isKeyPressed(.left) or rl.isKeyPressed(.a))) {
                    self.pending_level_input.lane_delta -= 1;
                }
                if (accepts_live_replay_controls and (rl.isKeyPressed(.right) or rl.isKeyPressed(.d))) {
                    self.pending_level_input.lane_delta += 1;
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
                    self.pending_level_input.reset = true;
                }
                if (accepts_live_replay_controls) {
                    self.pending_level_input.steering_authored_x = subgame_camera.authoredMouseXForScreen(
                        @floatFromInt(rl.getMouseX()),
                        @floatFromInt(window_state.screenWidth()),
                    );
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

    fn enterStartMode(self: *AppState, mode: FrontendLevelMode) !void {
        try frontend_flow.enterStartMode(self, mode);
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

    pub fn tryLaunchNewGameReplayAttract(self: *AppState) !bool {
        return frontend_flow.tryLaunchNewGameReplayAttract(self);
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

    fn enterDebugLevelAt(self: *AppState, level_path: []const u8, row_position: f32, lane_center: ?f32) !void {
        self.active_frontend_mode = debugFrontendModeForLevelPath(level_path);
        self.active_frontend_level_index = 0;
        self.current_outer_owner = frontend_bridge.outerOwnerStateMainMenu();
        self.saved_outer_owner = frontend_bridge.outerOwnerStateMainMenu();
        try self.setSelectedLevelRecordContext(null, null);
        try self.loadGameLevel(level_path);

        if (self.current_track_preview) |*loaded_track_preview| {
            if (self.level_runner) |*runner| {
                runner.debugWarpToTrackRow(loaded_track_preview, row_position, lane_center);
                self.gameplay_click_start_active = false;
                self.updateSubgameCamera(runner);
                self.active_level_segment_index = runner.currentRowMessageLogicalSegmentIndex();
            }
        }
        try self.enterGamePhase(.level);
        self.clearLevelPromptQueue();
        voice_audio.stopPlayback(voice_audio.context(self));
        self.gameplay_voice_manager.clear();
        self.native_gameplay_voice_manager.clear();
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

    pub fn clearLevelPromptQueue(self: *AppState) void {
        self.level_prompt_queue.clear();
    }

    pub fn isTutorialGameplay(self: *const AppState) bool {
        return level_loader.isTutorialGameplay(self);
    }

    fn isTutorialFlow(self: *const AppState) bool {
        return level_loader.isTutorialFlow(self);
    }

    fn isTutorialLevel(self: *const AppState) bool {
        return level_loader.isTutorialLevel(self);
    }

    pub fn gameplayTutorialContext(self: *const AppState) gameplay_resources.TutorialContext {
        const runner = if (self.level_runner) |*level_runner|
            level_runner
        else
            null;
        const loaded_level = if (self.current_level) |*current_level|
            current_level
        else
            null;
        return .{
            .active_frontend_mode = self.active_frontend_mode,
            .runner = runner,
            .current_level = loaded_level,
        };
    }

    fn gameplayHudContext(self: *const AppState) gameplay_hud.Context {
        const loaded_track_preview = if (self.current_track_preview) |*current_track_preview|
            current_track_preview
        else
            null;
        const loaded_level = if (self.current_level) |*current_level|
            current_level
        else
            null;
        return .{
            .font = &self.ui_font,
            .frontend_widget_art = &self.frontend_widget_art,
            .sprites = &self.gameplay_resources.sprites,
            .current_track_preview = loaded_track_preview,
            .current_level = loaded_level,
            .tutorial_reference_score = self.tutorial_reference_score,
        };
    }

    fn gameplayPromptContext(self: *const AppState) gameplay_prompt_overlay.Context {
        return .{
            .font = &self.ui_font,
            .widget_art = &self.frontend_widget_art,
            .mouse_local = self.currentUiMouseLocal(),
        };
    }

    fn runTuningContext(self: *const AppState) run_tuning.Context {
        const loaded_level = if (self.current_level) |*current_level|
            current_level
        else
            null;
        const loaded_track_preview = if (self.current_track_preview) |*current_track_preview|
            current_track_preview
        else
            null;
        return .{
            .active_frontend_mode = self.active_frontend_mode,
            .selected_level_record_override = self.selected_level_record_override,
            .runtime_config = &self.runtime_config,
            .current_level = loaded_level,
            .current_track_preview = loaded_track_preview,
            .active_frontend_level_index = self.active_frontend_level_index,
            .current_runtime_build_seed = self.current_runtime_build_seed,
        };
    }

    fn trackBuildSeedContext(self: *AppState) track_build_seed.Context {
        return .{
            .command = self.command,
            .active_frontend_mode = self.active_frontend_mode,
            .active_frontend_level_index = self.active_frontend_level_index,
            .level_index = self.level_index,
            .selected_level_record_override = self.selected_level_record_override,
            .math_random_state = &self.math_random_state,
            .current_runtime_build_seed = &self.current_runtime_build_seed,
            .current_runtime_build_seed_level_index = &self.current_runtime_build_seed_level_index,
            .current_runtime_build_seed_mode = &self.current_runtime_build_seed_mode,
        };
    }

    pub fn tutorialPromptBlocksGameplay(self: *const AppState) bool {
        if (!self.isTutorialGameplay()) return false;
        const prompt = self.level_prompt_queue.active() orelse return false;
        return prompt.interactive;
    }

    fn tutorialClickStartCutsceneActive(self: *const AppState) bool {
        if (!self.gameplay_click_start_active) return false;
        const runner = self.level_runner orelse return false;
        return runner.introCutsceneBlocksGameplay();
    }

    fn gameplayClickStartDismissible(self: *const AppState) bool {
        if (!self.gameplay_click_start_active) return false;
        return !self.tutorialClickStartCutsceneActive();
    }

    pub fn startupGameplayBlockActive(self: *const AppState) bool {
        if (self.gameplay_click_start_active) return true;
        const runner = self.level_runner orelse return false;
        return runner.introCutsceneBlocksGameplay();
    }

    pub fn refreshRunnerForStartupBlock(
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

    pub fn dispatchCurrentRunnerRowMessage(
        self: *AppState,
        previous_segment_index: ?usize,
        previous_token: ?u32,
        replay_sample_on_match: bool,
    ) !void {
        try level_loader.dispatchCurrentRunnerRowMessage(self, previous_segment_index, previous_token, replay_sample_on_match);
    }

    fn replaySpeedScalarForSliderValue(value: u32) f32 {
        return run_tuning.replaySpeedScalarForSliderValue(value);
    }

    fn currentRunReplaySpeedScalar(self: *const AppState) f32 {
        return run_tuning.currentRunReplaySpeedScalar(self.runTuningContext());
    }

    fn currentRunChallengeDifficultyValue(self: *const AppState) u32 {
        return run_tuning.currentRunChallengeDifficultyValue(self.runTuningContext());
    }

    fn currentRunChallengeDifficultyScalar(self: *const AppState) f32 {
        return run_tuning.currentRunChallengeDifficultyScalar(self.runTuningContext());
    }

    fn currentRunChallengeSpeedValue(self: *const AppState) u32 {
        return run_tuning.currentRunChallengeSpeedValue(self.runTuningContext());
    }

    fn challengeParcelTargetCount(speed_value: u32, difficulty_scalar: f32) usize {
        return run_tuning.challengeParcelTargetCount(speed_value, difficulty_scalar);
    }

    fn challengeRuntimeHazardScalar(value: u32) f32 {
        return run_tuning.challengeRuntimeHazardScalar(value);
    }

    fn currentRunGarbageScalar(self: *const AppState) f32 {
        return run_tuning.currentRunGarbageScalar(self.runTuningContext());
    }

    fn currentRunSaltScalar(self: *const AppState) f32 {
        return run_tuning.currentRunSaltScalar(self.runTuningContext());
    }

    pub fn currentParcelTarget(self: *const AppState) usize {
        return run_tuning.currentParcelTarget(self.runTuningContext());
    }

    fn configureRuntimeParcels(self: *AppState, loaded_track_preview: *track.LoadedLevelPreview) !void {
        try run_tuning.configureRuntimeParcels(self.runTuningContext(), &self.math_random_state, loaded_track_preview);
    }

    fn currentRunRuntimeBuildFlags(self: *const AppState) u32 {
        return run_tuning.currentRunRuntimeBuildFlags(self.runTuningContext());
    }

    pub fn currentRunHighScoreEntry(self: *AppState, score: u32) !high_score.Entry {
        var entry = run_tuning.currentRunHighScoreEntry(self.runTuningContext(), score);
        errdefer entry.deinit(self.allocator);
        self.replay_capture.markReplayTail();
        try self.replay_capture.attachToEntry(self.allocator, &entry);
        return entry;
    }

    pub fn captureReplayFrame(
        self: *AppState,
        loaded_track_preview: *const track.LoadedLevelPreview,
        runner: gameplay.Runner,
        input: gameplay.RunnerInput,
    ) !void {
        const world = runner.worldPosition(loaded_track_preview, 0.0);
        try self.replay_capture.appendFrame(
            self.allocator,
            world.x,
            world.z,
            input.fire_pressed,
            input.fire_down,
        );
    }

    pub fn saveHighScoreTables(self: *AppState) !void {
        try self.high_score_tables.saveToRuntimeRoot(self.allocator, self.runtime_root_path);
    }

    pub fn beginCompletedRunOverlay(self: *AppState) !void {
        try run_result.beginCompletedOverlay(self);
    }

    pub fn finalizeCompletedRunScreen(self: *AppState) !void {
        if (self.pending_run_result == null) {
            try self.beginCompletedRunOverlay();
        }
        if (self.pending_run_result == null) return;

        self.completion_overlay_active = false;
        self.preserve_completion_screen_reveal_on_enter = true;
        try self.enterGamePhase(.completion_screen);
    }

    pub fn beginFailedRun(self: *AppState, cause: gameplay.DeathCause) !void {
        try run_result.beginFailedRun(self, cause);
    }

    pub fn beginRespawnRun(self: *AppState) !void {
        self.completion_overlay_active = false;
        self.preserve_completion_screen_reveal_on_enter = false;
        var opcode: frontend_bridge.OuterBridgeOpcode = .rebuild_clear_replay_return;
        const owner = self.outerOwnerForRespawnActiveRun(&opcode) orelse return;
        try self.runOuterBridgeTransition(opcode, owner);
    }

    pub fn resetCompletionScreenReveal(self: *AppState) void {
        run_result.resetCompletionScreenReveal(self);
    }

    fn completionScreenActive(self: *const AppState) bool {
        return run_result.completionScreenActive(self);
    }

    pub fn completionScreenOverlayActive(self: *const AppState) bool {
        return run_result.completionScreenOverlayActive(self);
    }

    fn completionScreenInteractive(self: *const AppState) bool {
        return run_result.completionScreenInteractive(self);
    }

    pub fn stepCompletionScreenReveal(self: *AppState) void {
        run_result.stepCompletionScreenReveal(self);
    }

    fn beginThanksScreenExit(self: *AppState) void {
        if (!self.thanks_screen_controller.allowsContinue()) return;
        if (self.frontend_transition.state != .idle) return;
        // PORT(verified): `update_thanks_for_playing_screen` plays `sfx 8`, starts the
        // front-end fade, and `uninit_thanks_screen` then writes state `0xe`, which the
        // frontend state machine immediately routes into `initialize_intro_screen(...Credits)`.
        frontend_audio.playSelectSound(frontend_audio.context(self));
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

    pub fn clearTimeTrialGhostReplayCache(self: *AppState) void {
        if (self.time_trial_ghost_replay_cache) |*replay| {
            replay.deinit();
            self.time_trial_ghost_replay_cache = null;
        }
    }

    pub fn configureTimeTrialGhostReplayCache(self: *AppState) !void {
        self.clearTimeTrialGhostReplayCache();
        if (self.active_frontend_mode != .time_trial) return;
        if (self.selected_level_record_source != null) return;

        const completion_index = high_score.completionIndexForRouteIndex(self.active_frontend_level_index) orelse return;
        const entry = &self.high_score_tables.completion[completion_index];
        if (entry.replaySampleCount() == 0) return;
        self.time_trial_ghost_replay_cache = try entry.decodeReplay(self.allocator);
    }

    pub fn updateRunnerTimeTrialGhost(self: *const AppState, runner: *gameplay.Runner, replay_sample_index: usize) void {
        if (self.active_frontend_mode != .time_trial or self.selected_level_record_source != null) {
            runner.clearTimeTrialGhost();
            return;
        }
        const replay = self.time_trial_ghost_replay_cache orelse {
            runner.clearTimeTrialGhost();
            return;
        };
        const sample = replay.sampleAt(replay_sample_index) orelse {
            runner.clearTimeTrialGhost();
            return;
        };
        runner.markTimeTrialGhost(sample.ghostWorldZ());
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

    pub fn handleSelectedReplayFadeExit(self: *AppState) !bool {
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
        if (mode == .time_trial) return highest_available;
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
        try phase_resources.sync(self);
    }

    fn loadGameLevel(self: *AppState, level_path: []const u8) !void {
        try level_loader.loadGameLevel(self, level_path);
    }

    pub fn syncActiveLevelSegment(self: *AppState) !void {
        try level_loader.syncActiveLevelSegment(self);
    }

    pub fn loadCurrentLevelBackground(self: *AppState) !void {
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

    pub fn loadGameBackground(self: *AppState, script_path: []const u8) !void {
        try screen_assets.loadGameBackground(screen_assets.context(self), script_path);
    }

    pub fn loadLoadingScreen(self: *AppState) !void {
        try screen_assets.loadLoadingScreen(screen_assets.context(self));
    }

    pub fn loadTextScript(self: *AppState, path: []const u8) !void {
        try screen_assets.loadTextScript(screen_assets.context(self), path);
    }

    fn loadConfiguredTextScriptEntry(self: *AppState, path: []const u8) !intro.Loaded {
        return screen_assets.loadConfiguredTextScriptEntry(screen_assets.context(self), path);
    }

    pub fn unloadTextScript(self: *AppState) void {
        screen_assets.unloadTextScript(screen_assets.context(self));
    }

    pub fn unloadLoadingScreen(self: *AppState) void {
        screen_assets.unloadLoadingScreen(screen_assets.context(self));
    }

    pub fn currentTextScriptDurationTicks(self: *const AppState) ?u64 {
        return screen_assets.currentTextScriptDurationTicks(screen_assets.viewContext(self));
    }

    pub fn toggleFullscreenPreference(self: *AppState) void {
        window_state.toggleFullscreenPreference(window_state.context(self));
    }

    fn syncWindowFullscreenPreference(self: *AppState) void {
        window_state.syncFullscreenPreference(window_state.context(self));
    }

    pub fn currentTextScriptProgress(self: *const AppState) ?f32 {
        return screen_assets.currentTextScriptProgress(screen_assets.viewContext(self));
    }

    pub fn currentTextScript(self: *const AppState) ?*const intro.Loaded {
        return screen_assets.currentTextScript(screen_assets.viewContext(self));
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

    pub fn unloadGameBackground(self: *AppState) void {
        screen_assets.unloadGameBackground(screen_assets.context(self));
    }

    fn setGameStatusMessage(self: *AppState, message: []const u8) void {
        self.game_status_message = message;
        self.game_status_ticks = status_message_duration_ticks;
    }

    pub fn reloadLevel(self: *AppState) !void {
        try level_loader.reloadLevel(self);
    }

    fn nextMathRandomInt15(self: *AppState) u32 {
        return math_random.nextInt15(&self.math_random_state);
    }

    fn trackBuildSeedForCurrentLoad(self: *AppState) u32 {
        return track_build_seed.seedForCurrentLoad(self.trackBuildSeedContext());
    }

    fn invalidateTrackBuildSeed(self: *AppState) void {
        track_build_seed.invalidate(self.trackBuildSeedContext());
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

        try state.handleInput();
        try state.update(frame_delta_seconds);
        try state.maybeQueueAutoScreenshot();

        {
            rl.beginDrawing();
            defer rl.endDrawing();
            rl.clearBackground(.black);
            try drawUi(&state, options.archive_path);
        }

        try state.flushQueuedScreenshot();
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
        gameplay_viewport_render.draw(state);
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
        .width = @floatFromInt(window_state.screenWidth()),
        .height = @floatFromInt(window_state.screenHeight()),
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

    try drawGamePhaseContents(state, full_bounds, ui_layout);
    frontend_render.drawCursorOverlay(state, ui_layout);

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
    return run_tuning.runtimeBuildFlagsForFrontendMode(mode);
}

fn runnerSessionModeForFrontendMode(mode: ?FrontendLevelMode) gameplay.SessionMode {
    return run_tuning.runnerSessionModeForFrontendMode(mode);
}

fn completionBonusAppliesForMode(mode: ?FrontendLevelMode) bool {
    // PORT(verified): the native subgame keeps one shared gameplay sim and dispatches most
    // mode differences through a small mode-to-config lane in `set_subgame_features` and
    // `build_subgame_level`. Postal is the only mode that keeps the completion bonus lane.
    return run_tuning.completionBonusAppliesForMode(mode);
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

// PORT(partial): gameplay score awards now route through the recovered Windows
// `cRSubGoldy::ScoreAdd` table: garbage +10, slug +500, ring +100,
// parcel collect +100, parcel deliver +100, and variable completion bonus.
// The remaining scoring gap is deeper `cRSubGoldy::AI()` ownership and any
// unmodeled callers, not the point table.
fn bootPhaseProgress(state: *const AppState) f32 {
    return boot_assets.progress(state.boot_task_index);
}

fn drawGameplayLevelUi(state: *const AppState, layout: VirtualLayout) !void {
    gameplay_viewport_render.draw(state);

    if (state.level_runner) |runner| {
        const hud_context = state.gameplayHudContext();
        if (state.isTutorialGameplay()) {
            try drawTutorialGameplayUi(state, hud_context, layout, runner);
        } else {
            try gameplay_hud.drawStandardHud(hud_context, layout, runner);
            gameplay_hud.drawProgressBar(hud_context, layout, runner);
            gameplay_hud.drawStatusWidgets(hud_context, layout, runner);
            if (state.current_track_preview) |loaded_track_preview| {
                const camera = subgame_camera.levelCamera(&state.subgame_camera, &loaded_track_preview, state.subgame_camera.fov_degrees);
                try gameplay_hud.drawRowEventWidget(hud_context, layout, runner, camera);
            }
            try gameplay_prompt_overlay.drawGameplayStack(state.gameplayPromptContext(), layout, &state.level_prompt_queue);
            gameplay_hud.drawTimesUpWidget(hud_context, layout, runner);
        }
    }

    if (state.completionScreenOverlayActive()) {
        try drawCompletionScreenUi(state, layout);
    }
}

fn drawTutorialGameplayUi(state: *const AppState, hud_context: gameplay_hud.Context, layout: VirtualLayout, runner: gameplay.Runner) !void {
    gameplay_hud.drawProgressBar(hud_context, layout, runner);
    gameplay_hud.drawDamageGauge(hud_context, layout, runner);
    if (state.gameplay_click_start_active) {
        if (!state.tutorialClickStartCutsceneActive()) {
            gameplay_prompt_overlay.drawClickStartWidget(state.gameplayPromptContext(), layout);
        }
        gameplay_hud.drawTimesUpWidget(hud_context, layout, runner);
        return;
    }
    try gameplay_prompt_overlay.drawTutorialStack(state.gameplayPromptContext(), layout, &state.level_prompt_queue);
    gameplay_hud.drawTimesUpWidget(hud_context, layout, runner);
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
    gameplay_viewport_render.draw(state);
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

fn gameTrackSetIndexForLevel(level_track: level.Track) ?u8 {
    return level_loader.gameTrackSetIndexForLevel(level_track);
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

test "challenge setup replay gate uses the native setup mirror" {
    var state: AppState = undefined;
    state.high_score_tables = high_score.Tables.initDefault();
    defer state.high_score_tables.deinit(std.testing.allocator);

    var raw_record = [_]u8{0} ** (0x88 + 5);
    std.mem.writeInt(u32, raw_record[0x74..0x78], 1, .little);

    state.high_score_tables.challenge[0].has_replay = true;
    state.high_score_tables.challenge[0].raw_record = try std.testing.allocator.dupe(u8, &raw_record);
    try std.testing.expect(!state.challengeSetupReplayAvailable());

    state.high_score_tables.challenge_setup_replay.has_replay = true;
    state.high_score_tables.challenge_setup_replay.raw_record = try std.testing.allocator.dupe(u8, &raw_record);
    try std.testing.expect(state.challengeSetupReplayAvailable());
}

test "high-score row replay is available for score browse rows" {
    try std.testing.expect(frontend_high_score_screen.rowsShowReplay(.postal, false));
    try std.testing.expect(frontend_high_score_screen.rowsShowReplay(.challenge, false));
    try std.testing.expect(!frontend_high_score_screen.rowsShowReplay(.postal, true));
    try std.testing.expect(!frontend_high_score_screen.rowsShowReplay(.challenge, true));

    try std.testing.expectEqualDeep(
        frontend_bridge.SelectedLevelRecordSource{ .postal = 2 },
        frontend_high_score_screen.replaySource(.{ .main_menu_browse = .postal }, 2).?,
    );
    try std.testing.expectEqualDeep(
        frontend_bridge.SelectedLevelRecordSource{ .challenge = 3 },
        frontend_high_score_screen.replaySource(.{ .main_menu_browse = .challenge }, 3).?,
    );
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

test "time-trial route map is not clamped by postal unlock progress" {
    var resources = try resource_store.Store.init(std.testing.allocator, default_archive_path, false);
    defer resources.deinit();

    var state: AppState = undefined;
    state.resources = resources;
    state.runtime_config = config.Blob.initDefault();
    state.runtime_config.setRouteUnlockLimit(1);
    state.runtime_config.setRouteSelectionIndex(0x32);

    try std.testing.expectEqual(@as(usize, 1), state.availableFrontendRouteLimit(.postal));
    try std.testing.expect(state.availableFrontendRouteLimit(.time_trial) > 1);
    try std.testing.expectEqual(@as(usize, 0x32), state.initialFrontendRouteIndex(.time_trial));
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

test "click-start prompt dispatch still queues a primed segment message" {
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

    var state: AppState = undefined;
    state.current_level = loaded_level;
    defer if (state.current_level) |*owned_level| owned_level.deinit();
    state.level_runner = runner;
    state.active_frontend_mode = .tutorial;
    state.active_level_segment_index = logical_segment_index;
    state.level_prompt_queue = .{};
    state.gameplay_click_start_active = false;
    state.audio_ready = false;

    try state.dispatchCurrentRunnerRowMessage(logical_segment_index, null, true);
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
        .score_totals = .{ .bonus = 50_000 },
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
        .score_totals = .{ .bonus = 50_000 },
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

test "time trial elapsed text uses native helper format" {
    var buffer: [32]u8 = undefined;
    const text = try gameplay.formatTimeTrialString(&buffer, 91_230);
    try std.testing.expectEqualStrings("1:31:23", text);
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
    state.replay_capture = .{};
    defer state.replay_capture.deinit(std.testing.allocator);
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
    state.replay_capture = .{};
    defer state.replay_capture.deinit(std.testing.allocator);
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
    state.replay_capture = .{};
    defer state.replay_capture.deinit(std.testing.allocator);
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
    state.replay_capture = .{};
    defer state.replay_capture.deinit(std.testing.allocator);
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
    state.replay_capture = .{};
    defer state.replay_capture.deinit(std.testing.allocator);
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
    state.replay_capture = .{};
    defer state.replay_capture.deinit(std.testing.allocator);
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
    samples[0] = .{ .lateral = 0, .ghost_z_accum_raw = 0, .flags = 0 };
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
    state.replay_capture = .{};
    defer state.replay_capture.deinit(std.testing.allocator);

    const entry = try state.currentRunHighScoreEntry(12_345);
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

test "selected replay directive decodes compact lateral x and flags" {
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
    samples[0] = .{ .lateral = 0, .ghost_z_accum_raw = 0, .flags = 0 };
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

    try std.testing.expectEqual(gameplay.cutscene_none_id, runner.cutscene.id);
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
    const primed_world_position = runner.worldPosition(&loaded_track_preview, 0.0);
    const expected_raw_top_height = (@as(f32, @floatFromInt(@as(usize, @intFromFloat(@floor(4.0 * std.math.pi))))) / std.math.pi) * 2.0;
    try std.testing.expectEqual(gameplay.MovementMode.attachment, runner.movement_mode);
    try std.testing.expectApproxEqAbs(expected_raw_top_height, primed_world_position.y, 0.001);
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
    try std.testing.expect(runner.attachment.follow.active);
    try std.testing.expectEqual(subgame_camera.Source.override, camera_state.source);
    try std.testing.expect(runner.cutsceneCameraActive());
}

test "click-start remains latched until the intro handoff is visible" {
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
    state.gameplay_click_start_active = true;
    state.level_runner = gameplay.Runner.init(&loaded_track_preview);
    state.level_runner.?.setCutscene(gameplay.cutscene_intro_id);

    try std.testing.expect(!state.gameplayClickStartDismissible());

    state.level_runner.?.clearCutscene();

    try std.testing.expect(state.gameplayClickStartDismissible());
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
    try std.testing.expect(state.level_runner.?.attachment.follow.active);
    try std.testing.expect(state.level_runner.?.cutsceneCameraActive());
    try std.testing.expect(state.level_runner.?.track_step_rows > 0.0);
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
    const live_matrix = gameplay_model_render.transformFromBasis(.{ .x = 1.0, .y = 2.0, .z = 3.0 }, basis_right, basis_up, basis_forward);
    const override_matrix = gameplay_model_render.transformFromBasis(.{ .x = 5.0, .y = 6.0, .z = 7.0 }, basis_right, basis_up, basis_forward);
    const next_live_matrix = gameplay_model_render.transformFromBasis(.{ .x = 9.0, .y = 10.0, .z = 11.0 }, basis_right, basis_up, basis_forward);
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
