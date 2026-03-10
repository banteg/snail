const std = @import("std");
const rl = @import("raylib");
const app = @import("app.zig");
const app_ui = @import("app_ui.zig");
const assets = @import("assets.zig");
const background = @import("background.zig");
const config = @import("config.zig");
const frontend = @import("frontend.zig");
const frontend_widget = @import("frontend_widget.zig");
const galaxy = @import("galaxy.zig");
const game_font = @import("game_font.zig");
const gameplay = @import("gameplay.zig");
const high_score = @import("high_score.zig");
const intro = @import("intro.zig");
const level_prompt = @import("level_prompt.zig");
const sim = @import("sim.zig");
const track = @import("track.zig");
const loading_screen = @import("loading_screen.zig");
const object = @import("object.zig");
const segment = @import("segment.zig");
const level = @import("level.zig");
const runtime_state = @import("runtime_state.zig");
const x2 = @import("x2.zig");
const xanim = @import("xanim.zig");

const default_archive_path = app.default_archive_path;
const default_screenshot_dir = app.default_screenshot_dir;
const intro_background_path = app.intro_background_path;
const main_menu_background_path = app.main_menu_background_path;
const help_background_path = app.help_background_path;
const route_map_background_path = app.route_map_background_path;
const route_map_logo_texture_path = app.route_map_logo_texture_path;
const route_map_border_texture_path = app.route_map_border_texture_path;
const route_map_galaxy_select_texture_path = app.route_map_galaxy_select_texture_path;
const route_map_level_select_texture_path = app.route_map_level_select_texture_path;
const route_map_level_star_texture_path = app.route_map_level_star_texture_path;
const route_map_line_texture_path = app.route_map_line_texture_path;
const route_map_line_star_texture_path = app.route_map_line_star_texture_path;
const route_map_galaxy_texture_paths = app.route_map_galaxy_texture_paths;
const frontend_cursor_texture_path = app.frontend_cursor_texture_path;
const widget_border_texture_path = app.widget_border_texture_path;
const frontend_highlight_sound_path = app.frontend_highlight_sound_path;
const frontend_select_sound_path = app.frontend_select_sound_path;
const slider_less_texture_path = app.slider_less_texture_path;
const slider_less_hover_texture_path = app.slider_less_hover_texture_path;
const slider_more_texture_path = app.slider_more_texture_path;
const slider_more_hover_texture_path = app.slider_more_hover_texture_path;
const slider_bar_texture_path = app.slider_bar_texture_path;
const slider_bar_full_texture_path = app.slider_bar_full_texture_path;
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
const RouteMenuAction = frontend.RouteMenuAction;
const frontendRouteModeLabel = frontend.frontendRouteModeLabel;
const routeMenuActionLabel = frontend.routeMenuActionLabel;
const routeMenuHint = frontend.routeMenuHint;
const frontendLevelPath = frontend.frontendLevelPath;

const MenuPanels = app_ui.MenuPanels;
const VirtualLayout = app_ui.VirtualLayout;

const ScreenshotRequest = struct {
    relative_path_z: [:0]u8,
    exit_after_capture: bool,

    fn deinit(self: *ScreenshotRequest, allocator: std.mem.Allocator) void {
        allocator.free(self.relative_path_z);
    }
};

const SliderArt = struct {
    less: ?assets.LoadedTexture = null,
    less_hover: ?assets.LoadedTexture = null,
    more: ?assets.LoadedTexture = null,
    more_hover: ?assets.LoadedTexture = null,
    bar: ?assets.LoadedTexture = null,
    bar_full: ?assets.LoadedTexture = null,

    fn unload(self: *SliderArt) void {
        if (self.less) |*texture| {
            texture.unload();
            self.less = null;
        }
        if (self.less_hover) |*texture| {
            texture.unload();
            self.less_hover = null;
        }
        if (self.more) |*texture| {
            texture.unload();
            self.more = null;
        }
        if (self.more_hover) |*texture| {
            texture.unload();
            self.more_hover = null;
        }
        if (self.bar) |*texture| {
            texture.unload();
            self.bar = null;
        }
        if (self.bar_full) |*texture| {
            texture.unload();
            self.bar_full = null;
        }
    }
};

const FrontendWidgetArt = struct {
    border: ?assets.LoadedTexture = null,

    fn unload(self: *FrontendWidgetArt) void {
        if (self.border) |*texture| {
            texture.unload();
            self.border = null;
        }
    }
};

const FrontendSoundFx = struct {
    highlight: ?assets.LoadedSound = null,
    select: ?assets.LoadedSound = null,

    fn unload(self: *FrontendSoundFx) void {
        if (self.highlight) |*sound| {
            sound.unload();
            self.highlight = null;
        }
        if (self.select) |*sound| {
            sound.unload();
            self.select = null;
        }
    }
};

const RouteMapArt = struct {
    logo: ?assets.LoadedTexture = null,
    border: ?assets.LoadedTexture = null,
    galaxy_select: ?assets.LoadedTexture = null,
    level_select: ?assets.LoadedTexture = null,
    level_star: ?assets.LoadedTexture = null,
    line: ?assets.LoadedTexture = null,
    line_star: ?assets.LoadedTexture = null,
    galaxies: [galaxy.map_galaxy_count]?assets.LoadedTexture = [_]?assets.LoadedTexture{null} ** galaxy.map_galaxy_count,

    fn unload(self: *RouteMapArt) void {
        if (self.logo) |*texture| {
            texture.unload();
            self.logo = null;
        }
        if (self.border) |*texture| {
            texture.unload();
            self.border = null;
        }
        if (self.galaxy_select) |*texture| {
            texture.unload();
            self.galaxy_select = null;
        }
        if (self.level_select) |*texture| {
            texture.unload();
            self.level_select = null;
        }
        if (self.level_star) |*texture| {
            texture.unload();
            self.level_star = null;
        }
        if (self.line) |*texture| {
            texture.unload();
            self.line = null;
        }
        if (self.line_star) |*texture| {
            texture.unload();
            self.line_star = null;
        }
        for (&self.galaxies) |*texture| {
            if (texture.*) |*loaded| {
                loaded.unload();
                texture.* = null;
            }
        }
    }
};

fn loadFrontendWidgetArt(allocator: std.mem.Allocator, catalog: *const assets.Catalog) !FrontendWidgetArt {
    var art = FrontendWidgetArt{};
    errdefer art.unload();

    art.border = try catalog.loadTextureByPath(allocator, widget_border_texture_path);

    return art;
}

fn loadFrontendSoundFx(allocator: std.mem.Allocator, catalog: *const assets.Catalog, audio_ready: bool) !FrontendSoundFx {
    if (!audio_ready) return .{};

    var sound_fx = FrontendSoundFx{};
    errdefer sound_fx.unload();

    sound_fx.highlight = try catalog.loadSoundByPath(allocator, frontend_highlight_sound_path);
    sound_fx.select = try catalog.loadSoundByPath(allocator, frontend_select_sound_path);

    return sound_fx;
}

fn loadSliderArt(allocator: std.mem.Allocator, catalog: *const assets.Catalog) !SliderArt {
    var art = SliderArt{};
    errdefer art.unload();

    art.less = try catalog.loadTextureByPath(allocator, slider_less_texture_path);
    art.less_hover = try catalog.loadTextureByPath(allocator, slider_less_hover_texture_path);
    art.more = try catalog.loadTextureByPath(allocator, slider_more_texture_path);
    art.more_hover = try catalog.loadTextureByPath(allocator, slider_more_hover_texture_path);
    art.bar = try catalog.loadTextureByPath(allocator, slider_bar_texture_path);
    art.bar_full = try catalog.loadTextureByPath(allocator, slider_bar_full_texture_path);

    return art;
}

fn loadRouteMapArt(allocator: std.mem.Allocator, catalog: *const assets.Catalog) !RouteMapArt {
    var art = RouteMapArt{};
    errdefer art.unload();

    art.logo = try catalog.loadTextureByPath(allocator, route_map_logo_texture_path);
    art.border = try catalog.loadTextureByPath(allocator, route_map_border_texture_path);
    art.galaxy_select = try catalog.loadTextureByPath(allocator, route_map_galaxy_select_texture_path);
    art.level_select = try catalog.loadTextureByPath(allocator, route_map_level_select_texture_path);
    art.level_star = try catalog.loadTextureByPath(allocator, route_map_level_star_texture_path);
    art.line = try catalog.loadTextureByPath(allocator, route_map_line_texture_path);
    art.line_star = try catalog.loadTextureByPath(allocator, route_map_line_star_texture_path);
    for (route_map_galaxy_texture_paths, 0..) |path, index| {
        art.galaxies[index] = try catalog.loadTextureByPath(allocator, path);
    }

    return art;
}

const ResultReturnTarget = enum {
    main_menu,
    postal_route_map,
    time_trial_route_map,
    replay_current_level,
};

const RunOutcome = enum {
    completed,
    failed,
};

const PendingRunResult = struct {
    outcome: RunOutcome = .completed,
    level_name: []const u8,
    mode: ?FrontendLevelMode,
    elapsed_millis: u32,
    parcel_count: u32,
    parcel_target: usize,
    score: u32,
    score_is_partial: bool,
    score_totals: gameplay.ScoreTotals = .{},
    visible_life_stock: u32 = 0,
    damage_gauge: f32 = 0.0,
    high_score_mode: ?high_score.Mode = null,
    high_score_rank: ?usize = null,
    time_trial_record_improved: bool = false,
    unlocked_next_route: bool = false,
    return_target: ResultReturnTarget,
};

const PendingHighScoreEntry = struct {
    mode: high_score.Mode,
    rank: usize,
};

const CompletionAction = enum {
    continue_flow,
    replay_level,

    fn label(self: CompletionAction) []const u8 {
        return switch (self) {
            .continue_flow => "Continue",
            .replay_level => "Replay",
        };
    }
};

const completion_actions = [_]CompletionAction{
    .continue_flow,
    .replay_level,
};

const high_score_screen_modes = [_]high_score.Mode{
    .postal,
    .challenge,
};

const ExitPromptChoice = enum {
    no,
    yes,

    fn label(self: ExitPromptChoice) []const u8 {
        return switch (self) {
            .no => "No",
            .yes => "Yes",
        };
    }
};

const exit_prompt_choices = [_]ExitPromptChoice{
    .yes,
    .no,
};

const PostLevelHighScoreAction = enum {
    cancel,
    submit,

    fn label(self: PostLevelHighScoreAction) []const u8 {
        return switch (self) {
            .cancel => "Cancel",
            .submit => "Submit",
        };
    }
};

const post_level_high_score_actions = [_]PostLevelHighScoreAction{
    .cancel,
    .submit,
};

const HighScoreMenuAction = enum {
    back,
    switch_table,
};

const high_score_menu_actions = [_]HighScoreMenuAction{
    .back,
    .switch_table,
};

const route_menu_actions_without_replay = [_]RouteMenuAction{
    .play,
    .back,
};

const route_menu_actions_with_replay = [_]RouteMenuAction{
    .play,
    .watch_best_trial,
    .back,
};

const options_button_count = 2;
const options_fullscreen_button_index: usize = 0;
const options_back_button_index: usize = 1;
const options_fullscreen_anchor_y: f32 = 83.0;
const options_button_center_offset_x: f32 = 0.0;
const options_slider_center_x: f32 = 320.0;
const options_sound_slider_center_y: f32 = 183.0;
const options_music_slider_center_y: f32 = 277.0;
const options_back_anchor_y: f32 = 390.0;
const options_slider_panel_width: f32 = 418.0;
const options_slider_panel_height: f32 = 86.0;
const options_slider_arrow_size: f32 = 64.0;
const options_slider_arrow_offset_x: f32 = 172.0;
const options_slider_arrow_center_y_offset: f32 = 10.0;
const high_score_button_count = 2;
const exit_prompt_button_count = 2;
const high_score_title_y: f32 = 64.0;
const high_score_row_start_y: f32 = 111.0;
const high_score_row_pitch: f32 = 27.0;
const high_score_footer_y: f32 = 381.0;
const high_score_entry_cancel_x: f32 = -110.0;
const high_score_entry_submit_x: f32 = 55.0;
const high_score_back_x: f32 = -132.0;
const high_score_toggle_x: f32 = 33.0;
const exit_prompt_title_y: f32 = 200.0;
const exit_prompt_button_y: f32 = 330.0;
const exit_prompt_yes_x: f32 = -80.0;
const exit_prompt_no_x: f32 = 80.0;
const frontend_activation_delay_step: f32 = 1.0 / 3.0;

const FrontendHoverTarget = enum(u8) {
    main_menu_new_game,
    main_menu_high_scores,
    main_menu_options,
    main_menu_credits,
    main_menu_exit,
    new_game_tutorial,
    new_game_postal_mode,
    new_game_time_trial,
    new_game_challenge_mode,
    new_game_help,
    new_game_back,
    options_fullscreen,
    options_sound_volume,
    options_music_volume,
    options_back,
    high_scores_back,
    high_scores_switch_table,
    post_level_high_scores_cancel,
    post_level_high_scores_submit,
    exit_prompt_yes,
    exit_prompt_no,
};

const FrontendQueuedAction = union(enum) {
    main_menu: MainMenuItem,
    new_game_menu: NewGameMenuItem,
    options_menu: OptionsMenuItem,
    high_scores_menu: HighScoreMenuAction,
    post_level_high_scores: PostLevelHighScoreAction,
    exit_prompt: ExitPromptChoice,
};

const FrontendQueuedActivation = struct {
    action: FrontendQueuedAction,
    target: FrontendHoverTarget,
    requires_fade: bool,
    progress: f32 = 0.0,
};

fn hoverTargetForMainMenu(index: usize) FrontendHoverTarget {
    return switch (index) {
        0 => .main_menu_new_game,
        1 => .main_menu_high_scores,
        2 => .main_menu_options,
        3 => .main_menu_credits,
        4 => .main_menu_exit,
        else => unreachable,
    };
}

fn hoverTargetForNewGame(index: usize) FrontendHoverTarget {
    return switch (index) {
        0 => .new_game_tutorial,
        1 => .new_game_postal_mode,
        2 => .new_game_time_trial,
        3 => .new_game_challenge_mode,
        4 => .new_game_help,
        5 => .new_game_back,
        else => unreachable,
    };
}

fn hoverTargetForOptions(index: usize) FrontendHoverTarget {
    return switch (index) {
        0 => .options_fullscreen,
        1 => .options_sound_volume,
        2 => .options_music_volume,
        3 => .options_back,
        else => unreachable,
    };
}

fn hoverTargetForHighScores(index: usize) FrontendHoverTarget {
    return switch (index) {
        0 => .high_scores_back,
        1 => .high_scores_switch_table,
        else => unreachable,
    };
}

fn hoverTargetForPostLevelHighScores(index: usize) FrontendHoverTarget {
    return switch (index) {
        0 => .post_level_high_scores_cancel,
        1 => .post_level_high_scores_submit,
        else => unreachable,
    };
}

fn hoverTargetForExitPrompt(index: usize) FrontendHoverTarget {
    return switch (index) {
        0 => .exit_prompt_yes,
        1 => .exit_prompt_no,
        else => unreachable,
    };
}

fn queuedActivationTarget(action: FrontendQueuedAction) FrontendHoverTarget {
    return switch (action) {
        .main_menu => |item| switch (item) {
            .new_game => .main_menu_new_game,
            .high_scores => .main_menu_high_scores,
            .options => .main_menu_options,
            .credits => .main_menu_credits,
            .exit => .main_menu_exit,
        },
        .new_game_menu => |item| switch (item) {
            .tutorial => .new_game_tutorial,
            .postal_mode => .new_game_postal_mode,
            .time_trial => .new_game_time_trial,
            .challenge_mode => .new_game_challenge_mode,
            .help => .new_game_help,
            .back => .new_game_back,
        },
        .options_menu => |item| switch (item) {
            .fullscreen => .options_fullscreen,
            .back => .options_back,
            .sound_volume, .music_volume => unreachable,
        },
        .high_scores_menu => |item| switch (item) {
            .back => .high_scores_back,
            .switch_table => .high_scores_switch_table,
        },
        .post_level_high_scores => |item| switch (item) {
            .cancel => .post_level_high_scores_cancel,
            .submit => .post_level_high_scores_submit,
        },
        .exit_prompt => |choice| switch (choice) {
            .yes => .exit_prompt_yes,
            .no => .exit_prompt_no,
        },
    };
}

fn queuedActivationRequiresFade(action: FrontendQueuedAction) bool {
    return switch (action) {
        .main_menu => |item| switch (item) {
            .credits => true,
            else => false,
        },
        .new_game_menu => |item| switch (item) {
            .tutorial, .help => true,
            else => false,
        },
        else => false,
    };
}

const Mode = enum {
    textures,
    audio,
    models,
    objects,
    levels,
};

const AppState = struct {
    allocator: std.mem.Allocator,
    catalog: assets.Catalog,
    animation_catalog: xanim.Catalog,
    ui_font: game_font.Loaded,
    runtime_root_path: []const u8,
    screenshot_dir: []const u8,
    runtime_config: config.Blob,
    runtime_config_loaded_from_file: bool,
    command: AppCommand,
    window_size: WindowSize,
    audio_ready: bool,
    audio_muted: bool,
    should_exit: bool = false,
    auto_screenshot: ?AutoScreenshot = null,
    auto_screenshot_taken: bool = false,
    frame_capture_index: u32 = 0,
    pending_screenshot: ?ScreenshotRequest = null,
    simulation_clock: sim.FixedStepClock = sim.FixedStepClock.init(simulation_step_seconds),
    render_time_seconds: f64 = 0.0,
    game_phase: GamePhase = .boot,
    game_phase_ticks: u64 = 0,
    frontend_transition: FrontendTransition = .{},
    boot_task_index: usize = 0,
    menu_index: usize = 0,
    main_menu_button_states: [main_menu_items.len]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** main_menu_items.len,
    new_game_menu_index: usize = 0,
    new_game_button_states: [new_game_menu_items.len]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** new_game_menu_items.len,
    options_menu_index: usize = 0,
    options_button_states: [options_button_count]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** options_button_count,
    high_scores_menu_index: usize = 0,
    high_scores_action_index: usize = 1,
    high_score_button_states: [high_score_button_count]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** high_score_button_count,
    exit_prompt_choice_index: usize = 0,
    exit_prompt_button_states: [exit_prompt_button_count]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** exit_prompt_button_count,
    exit_prompt_return_phase: GamePhase = .main_menu,
    completion_action_index: usize = 0,
    post_level_high_score_action_index: usize = 1,
    post_level_high_score_button_states: [post_level_high_score_actions.len]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** post_level_high_score_actions.len,
    post_level_high_score_name_len: usize = 0,
    post_level_high_score_name_buf: [high_score.name_capacity]u8 = [_]u8{0} ** high_score.name_capacity,
    high_score_tables: high_score.Tables,
    pending_run_result: ?PendingRunResult = null,
    game_status_message: ?[]const u8 = null,
    game_status_ticks: u32 = 0,
    active_level_segment_index: ?usize = null,
    level_prompt_queue: level_prompt.Queue = .{},
    mouse_level_lane_target: ?usize = null,
    frontend_route_mode: ?FrontendLevelMode = null,
    frontend_route_index: usize = 0,
    route_menu_action_index: usize = 0,
    active_frontend_mode: ?FrontendLevelMode = null,
    active_frontend_level_index: usize = 0,
    mode: Mode = .textures,
    model_flip_v: bool = true,
    object_flip_v: bool = true,
    texture_index: usize,
    audio_index: usize,
    model_index: usize,
    object_index: usize,
    level_index: usize,
    level_segment_index: usize = 0,
    current_texture: ?assets.LoadedTexture = null,
    frontend_cursor_texture: ?assets.LoadedTexture = null,
    frontend_widget_art: FrontendWidgetArt = .{},
    frontend_sound_fx: FrontendSoundFx = .{},
    hovered_frontend_target: ?FrontendHoverTarget = null,
    pending_frontend_activation: ?FrontendQueuedActivation = null,
    slider_art: SliderArt = .{},
    route_map_art: RouteMapArt = .{},
    current_sound: ?assets.LoadedSound = null,
    current_music: ?assets.LoadedMusic = null,
    current_model: ?x2.LoadedModel = null,
    current_animation: ?xanim.Player = null,
    current_object: ?object.LoadedObject = null,
    current_level: ?level.Definition = null,
    current_segment: ?segment.Definition = null,
    current_track_preview: ?track.LoadedLevelPreview = null,
    current_game_background: ?background.Loaded = null,
    current_game_background_runtime: ?background.Runtime = null,
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
        var catalog = try assets.Catalog.init(allocator, options.archive_path);
        errdefer catalog.deinit();
        var animation_catalog = try xanim.Catalog.load(allocator, &catalog);
        errdefer animation_catalog.deinit();
        var ui_font = try game_font.Loaded.load(allocator, &catalog);
        errdefer ui_font.deinit();
        var frontend_cursor_texture = try catalog.loadTextureByPath(allocator, frontend_cursor_texture_path);
        errdefer frontend_cursor_texture.unload();
        var frontend_widget_art = try loadFrontendWidgetArt(allocator, &catalog);
        errdefer frontend_widget_art.unload();
        var frontend_sound_fx = try loadFrontendSoundFx(allocator, &catalog, audio_ready);
        errdefer frontend_sound_fx.unload();
        var slider_art = try loadSliderArt(allocator, &catalog);
        errdefer slider_art.unload();
        var route_map_art = try loadRouteMapArt(allocator, &catalog);
        errdefer route_map_art.unload();
        var galaxy_names = try galaxy.loadByPath(allocator, &catalog, galaxy_names_path);
        errdefer galaxy_names.deinit();

        const texture_index = catalog.findTextureIndex(default_texture_path) orelse 0;
        const audio_index = catalog.findAudioIndex(default_audio_path) orelse 0;
        const model_index = catalog.findModelIndex(default_model_path) orelse 0;
        const object_index = catalog.findObjectIndex(default_object_path) orelse 0;
        const level_index = catalog.findLevelIndex(default_level_path) orelse 0;

        var state = AppState{
            .allocator = allocator,
            .catalog = catalog,
            .animation_catalog = animation_catalog,
            .ui_font = ui_font,
            .runtime_root_path = options.runtime_root_path,
            .screenshot_dir = options.screenshot_dir,
            .runtime_config = runtime_config_result.blob,
            .runtime_config_loaded_from_file = runtime_config_result.loaded_from_file,
            .command = options.command,
            .window_size = options.window_size_override orelse defaultWindowSizeForCommand(options.command),
            .audio_ready = audio_ready,
            .audio_muted = options.hidden_window,
            .auto_screenshot = options.auto_screenshot,
            .high_score_tables = high_score.Tables.initDefault(),
            .texture_index = texture_index,
            .audio_index = audio_index,
            .model_index = model_index,
            .object_index = object_index,
            .level_index = level_index,
            .frontend_cursor_texture = frontend_cursor_texture,
            .frontend_widget_art = frontend_widget_art,
            .frontend_sound_fx = frontend_sound_fx,
            .slider_art = slider_art,
            .route_map_art = route_map_art,
            .galaxy_names = galaxy_names,
        };
        errdefer state.deinit();
        state.applyAudioConfigVolumes();

        switch (options.command) {
            .debug, .smoke => {
                try state.high_score_tables.loadFromRuntimeRoot(allocator, options.runtime_root_path);
                try state.reloadTexture();
                try state.reloadModel();
                try state.reloadObject();
                try state.reloadLevel();
            },
            .game => if (options.start_phase) |start_phase|
                try state.enterStartPhase(start_phase)
            else
                try state.enterGamePhase(.boot),
        }
        return state;
    }

    fn deinit(self: *AppState) void {
        self.stopAudioPreview();
        self.unloadLoadingScreen();
        self.unloadGameBackground();
        self.unloadPreloadedBootAssets();
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
        if (self.current_text_script) |*script| {
            script.deinit(self.allocator);
            self.current_text_script = null;
        }

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
        self.catalog.deinit();
        self.high_score_tables.deinit(self.allocator);
    }

    fn warmupSmokeTest(self: *AppState) !void {
        var loaded_loading_screen = try loading_screen.Loaded.load(self.allocator, &self.catalog);
        defer loaded_loading_screen.deinit();
        if (loaded_loading_screen.background_texture.texture.width <= 0 or loaded_loading_screen.bar_texture.texture.width <= 0) {
            return error.InvalidLoadingScreenTexture;
        }

        var loaded_intro_background = try background.Loaded.loadByPath(self.allocator, &self.catalog, intro_background_path);
        defer loaded_intro_background.deinit();
        if (loaded_intro_background.primary_texture.texture.width <= 0) {
            return error.InvalidIntroBackgroundTexture;
        }

        var loaded_intro_script = try intro.loadByPath(self.allocator, &self.catalog, intro_script_path);
        defer loaded_intro_script.deinit(self.allocator);
        if (loaded_intro_script.entries.len == 0) {
            return error.EmptyIntroScript;
        }

        var loaded_credits_script = try intro.loadByPath(self.allocator, &self.catalog, credits_script_path);
        defer loaded_credits_script.deinit(self.allocator);
        if (loaded_credits_script.entries.len == 0) {
            return error.EmptyCreditsScript;
        }

        if (!self.audio_ready or self.catalog.audio_entries.len == 0) {
            return;
        }

        try self.previewSound();
        self.stopAudioPreview();
        try self.previewMusic();
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
                self.preloaded_intro_background = try background.Loaded.loadByPath(self.allocator, &self.catalog, intro_background_path);
            },
            .load_main_menu_background => {
                self.unloadPreloadedBackground(&self.preloaded_main_menu_background);
                self.preloaded_main_menu_background = try background.Loaded.loadByPath(self.allocator, &self.catalog, main_menu_background_path);
            },
            .load_route_map_background => {
                self.unloadPreloadedBackground(&self.preloaded_route_map_background);
                self.preloaded_route_map_background = try background.Loaded.loadByPath(self.allocator, &self.catalog, route_map_background_path);
            },
            .load_help_background => {
                self.unloadPreloadedBackground(&self.preloaded_help_background);
                self.preloaded_help_background = try background.Loaded.loadByPath(self.allocator, &self.catalog, help_background_path);
            },
            .load_intro_script => {
                self.unloadPreloadedTextScript(&self.preloaded_intro_script);
                self.preloaded_intro_script = try intro.loadByPath(self.allocator, &self.catalog, intro_script_path);
            },
            .load_credits_script => {
                self.unloadPreloadedTextScript(&self.preloaded_credits_script);
                self.preloaded_credits_script = try intro.loadByPath(self.allocator, &self.catalog, credits_script_path);
            },
            .load_intro_music => {
                self.unloadPreloadedMusic(&self.preloaded_intro_music);
                self.preloaded_intro_music = try self.catalog.loadMusicByPath(self.allocator, intro_music_path);
            },
            .load_menu_music => {
                self.unloadPreloadedMusic(&self.preloaded_menu_music);
                self.preloaded_menu_music = try self.catalog.loadMusicByPath(self.allocator, default_audio_path);
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

    fn saveRuntimeConfig(self: *const AppState) !void {
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
            .debug => {},
        }

        if (rl.isKeyPressed(.tab)) {
            try self.setMode(nextMode(self.mode));
        }
        if (rl.isKeyPressed(.one)) {
            try self.setMode(.textures);
        }
        if (rl.isKeyPressed(.two)) {
            try self.setMode(.audio);
        }
        if (rl.isKeyPressed(.three)) {
            try self.setMode(.models);
        }
        if (rl.isKeyPressed(.four)) {
            try self.setMode(.objects);
        }
        if (rl.isKeyPressed(.five)) {
            try self.setMode(.levels);
        }

        if (self.mode == .levels) {
            if (rl.isKeyPressed(.left)) {
                self.level_index = wrappedIndex(self.catalog.level_entries.len, self.level_index, -1);
                try self.reloadLevel();
            }
            if (rl.isKeyPressed(.right)) {
                self.level_index = wrappedIndex(self.catalog.level_entries.len, self.level_index, 1);
                try self.reloadLevel();
            }
            if (rl.isKeyPressed(.up)) {
                try self.stepLevelSegment(-1);
            }
            if (rl.isKeyPressed(.down)) {
                try self.stepLevelSegment(1);
            }
            if (rl.isKeyPressed(.a)) {
                self.pending_level_input.lane_delta -= 1;
            }
            if (rl.isKeyPressed(.d)) {
                self.pending_level_input.lane_delta += 1;
            }
            if (rl.isKeyPressed(.w)) {
                self.pending_level_input.speed_delta_rows_per_second += 2.0;
            }
            if (rl.isKeyPressed(.s)) {
                self.pending_level_input.speed_delta_rows_per_second -= 2.0;
            }
            if (rl.isKeyPressed(.space)) {
                self.pending_level_input.toggle_pause = true;
            }
            if (rl.isKeyPressed(.r)) {
                self.pending_level_input.reset = true;
            }
        } else {
            if (rl.isKeyPressed(.left)) {
                try self.stepSelection(-1);
            }
            if (rl.isKeyPressed(.right)) {
                try self.stepSelection(1);
            }
            if (rl.isKeyPressed(.up)) {
                try self.stepSelection(-10);
            }
            if (rl.isKeyPressed(.down)) {
                try self.stepSelection(10);
            }
        }

        if (self.mode == .audio and self.audio_ready) {
            if (rl.isKeyPressed(.space)) {
                try self.previewSound();
            }
            if (rl.isKeyPressed(.enter)) {
                try self.previewMusic();
            }
            if (rl.isKeyPressed(.s)) {
                self.stopAudioPreview();
            }
        }

        if (self.mode == .models and rl.isKeyPressed(.f)) {
            self.model_flip_v = !self.model_flip_v;
            try self.reloadModel();
        }
        if (self.mode == .models and rl.isKeyPressed(.r)) {
            if (self.current_animation) |*animation| {
                try animation.restart();
            }
        }
        if (self.mode == .models and rl.isKeyPressed(.p)) {
            if (self.current_animation) |*animation| {
                animation.togglePause();
            }
        }
        if (self.mode == .objects and rl.isKeyPressed(.f)) {
            self.object_flip_v = !self.object_flip_v;
            try self.reloadObject();
        }
    }

    fn currentUiLayout(self: *const AppState) VirtualLayout {
        _ = self;
        return app_ui.virtualLayout(.{
            .x = 0.0,
            .y = 0.0,
            .width = @floatFromInt(screenWidth()),
            .height = @floatFromInt(screenHeight()),
        });
    }

    fn currentFrontendMouseLocal(self: *const AppState) ?rl.Vector2 {
        const layout = self.currentUiLayout();
        const mouse_x = @as(f32, @floatFromInt(rl.getMouseX()));
        const mouse_y = @as(f32, @floatFromInt(rl.getMouseY()));
        if (!layout.containsScreenPoint(mouse_x, mouse_y)) return null;
        return layout.unmapPoint(mouse_x, mouse_y);
    }

    fn setFrontendHoverTarget(self: *AppState, target: ?FrontendHoverTarget) void {
        if (self.hovered_frontend_target == target) return;
        self.hovered_frontend_target = target;
        if (target != null) {
            self.playFrontendHoverSound();
        }
    }

    fn activeFrontendButtonTarget(self: *const AppState) ?FrontendHoverTarget {
        if (self.pending_frontend_activation) |pending| {
            return pending.target;
        }
        return self.hovered_frontend_target;
    }

    fn frontendButtonHot(self: *const AppState, target: FrontendHoverTarget, fallback_selected: bool) bool {
        if (self.activeFrontendButtonTarget()) |active_target| {
            return active_target == target;
        }
        return fallback_selected;
    }

    fn queueFrontendActivation(self: *AppState, action: FrontendQueuedAction) void {
        if (self.pending_frontend_activation != null) return;
        self.playFrontendSelectSound();
        const requires_fade = queuedActivationRequiresFade(action);
        if (requires_fade) {
            self.frontend_transition.beginOverlayFadeOut();
        }
        self.pending_frontend_activation = .{
            .action = action,
            .target = queuedActivationTarget(action),
            .requires_fade = requires_fade,
        };
    }

    fn dispatchFrontendActivation(self: *AppState, action: FrontendQueuedAction) !void {
        switch (action) {
            .main_menu => |item| try self.performMainMenuItem(item),
            .new_game_menu => |item| try self.performNewGameMenuItem(item),
            .options_menu => |item| try self.performOptionsMenuItem(item),
            .high_scores_menu => |item| try self.performHighScoreMenuAction(item),
            .post_level_high_scores => |item| try self.performPostLevelHighScoreAction(item),
            .exit_prompt => |choice| try self.performExitPromptChoice(choice),
        }
    }

    fn updatePendingFrontendActivation(self: *AppState) !bool {
        if (self.pending_frontend_activation) |*pending| {
            pending.progress = @min(pending.progress + frontend_activation_delay_step, 1.0);
            const fade_ready = !pending.requires_fade or self.frontend_transition.state == .black_idle;
            if (pending.progress >= 0.999 and fade_ready) {
                const action = pending.action;
                const should_fade_in = pending.requires_fade and self.frontend_transition.state == .black_idle;
                self.pending_frontend_activation = null;
                try self.dispatchFrontendActivation(action);
                if (should_fade_in) {
                    self.frontend_transition.completeHandoff();
                }
                return true;
            }
        }
        return false;
    }

    fn playFrontendHoverSound(self: *AppState) void {
        if (!self.audio_ready) return;
        if (self.frontend_sound_fx.highlight) |sound| {
            rl.stopSound(sound.sound);
            rl.playSound(sound.sound);
        }
    }

    fn playFrontendSelectSound(self: *AppState) void {
        if (!self.audio_ready) return;
        if (self.frontend_sound_fx.select) |sound| {
            rl.stopSound(sound.sound);
            rl.playSound(sound.sound);
        }
    }

    fn updateFrontendWidgetAnimations(self: *AppState) void {
        const main_menu_active = self.game_phase == .main_menu and !self.frontend_transition.blocksInput();
        for (&self.main_menu_button_states, 0..) |*state, index| {
            state.stepFor(.menu_button, main_menu_active and self.frontendButtonHot(hoverTargetForMainMenu(index), self.menu_index == index));
        }

        const new_game_active = self.game_phase == .new_game_menu and !self.frontend_transition.blocksInput();
        for (&self.new_game_button_states, 0..) |*state, index| {
            state.stepFor(.menu_button, new_game_active and self.frontendButtonHot(hoverTargetForNewGame(index), self.new_game_menu_index == index));
        }

        const options_active = self.game_phase == .options_menu and !self.frontend_transition.blocksInput();
        self.options_button_states[options_fullscreen_button_index].stepFor(.menu_button, options_active and self.frontendButtonHot(hoverTargetForOptions(0), self.options_menu_index == 0));
        self.options_button_states[options_back_button_index].stepFor(.menu_button, options_active and self.frontendButtonHot(hoverTargetForOptions(3), self.options_menu_index == 3));

        const high_scores_active = self.game_phase == .high_scores_menu and !self.frontend_transition.blocksInput();
        for (&self.high_score_button_states, 0..) |*state, index| {
            state.stepFor(.footer_button, high_scores_active and self.postLevelHighScoreContext() == null and self.frontendButtonHot(hoverTargetForHighScores(index), self.high_scores_action_index == index));
        }
        for (&self.post_level_high_score_button_states, 0..) |*state, index| {
            state.stepFor(.footer_button, high_scores_active and self.postLevelHighScoreContext() != null and self.frontendButtonHot(hoverTargetForPostLevelHighScores(index), self.post_level_high_score_action_index == index));
        }

        const exit_prompt_active = self.game_phase == .exit_prompt and !self.frontend_transition.blocksInput();
        for (&self.exit_prompt_button_states, 0..) |*state, index| {
            state.stepFor(.menu_button, exit_prompt_active and self.frontendButtonHot(hoverTargetForExitPrompt(index), self.exit_prompt_choice_index == index));
        }
    }

    fn snapFrontendWidgetStates(self: *AppState) void {
        for (&self.main_menu_button_states, 0..) |*state, index| {
            state.snapFor(.menu_button, self.game_phase == .main_menu and self.frontendButtonHot(hoverTargetForMainMenu(index), self.menu_index == index));
        }
        for (&self.new_game_button_states, 0..) |*state, index| {
            state.snapFor(.menu_button, self.game_phase == .new_game_menu and self.frontendButtonHot(hoverTargetForNewGame(index), self.new_game_menu_index == index));
        }
        self.options_button_states[options_fullscreen_button_index].snapFor(.menu_button, self.game_phase == .options_menu and self.frontendButtonHot(hoverTargetForOptions(0), self.options_menu_index == 0));
        self.options_button_states[options_back_button_index].snapFor(.menu_button, self.game_phase == .options_menu and self.frontendButtonHot(hoverTargetForOptions(3), self.options_menu_index == 3));
        for (&self.high_score_button_states, 0..) |*state, index| {
            state.snapFor(.footer_button, self.game_phase == .high_scores_menu and self.postLevelHighScoreContext() == null and self.frontendButtonHot(hoverTargetForHighScores(index), self.high_scores_action_index == index));
        }
        for (&self.post_level_high_score_button_states, 0..) |*state, index| {
            state.snapFor(.footer_button, self.game_phase == .high_scores_menu and self.postLevelHighScoreContext() != null and self.frontendButtonHot(hoverTargetForPostLevelHighScores(index), self.post_level_high_score_action_index == index));
        }
        for (&self.exit_prompt_button_states, 0..) |*state, index| {
            state.snapFor(.menu_button, self.game_phase == .exit_prompt and self.frontendButtonHot(hoverTargetForExitPrompt(index), self.exit_prompt_choice_index == index));
        }
    }

    fn updateMainMenuMouseSelection(self: *AppState) !void {
        const local_mouse = self.currentFrontendMouseLocal() orelse {
            self.setFrontendHoverTarget(null);
            return;
        };
        var anchor_y: f32 = 90.0;
        var hovered_index: ?usize = null;

        for (main_menu_items, 0..) |item, index| {
            const text_rect = frontend_widget.type20TextRect(&self.ui_font, item.label(), anchor_y, frontend_widget.type20_center_offset_x);
            if (frontend_widget.hitRect(text_rect, self.main_menu_button_states[index]).contains(local_mouse)) {
                hovered_index = index;
            }
            anchor_y = frontend_widget.stackBelow(text_rect);
        }

        if (hovered_index) |index| {
            self.setFrontendHoverTarget(hoverTargetForMainMenu(index));
            self.menu_index = index;
            if (rl.isMouseButtonPressed(.left)) {
                self.queueFrontendActivation(.{ .main_menu = main_menu_items[index] });
            }
        } else {
            self.setFrontendHoverTarget(null);
        }
    }

    fn updateNewGameMenuMouseSelection(self: *AppState) !void {
        const local_mouse = self.currentFrontendMouseLocal() orelse {
            self.setFrontendHoverTarget(null);
            return;
        };
        var hovered_index: ?usize = null;
        var anchor_y: f32 = 80.0;

        for (new_game_menu_items[0..4], 0..) |item, index| {
            const text_rect = frontend_widget.type20TextRect(&self.ui_font, item.label(), anchor_y, frontend_widget.type20_center_offset_x);
            if (frontend_widget.hitRect(text_rect, self.new_game_button_states[index]).contains(local_mouse)) {
                hovered_index = index;
            }
            anchor_y = frontend_widget.stackBelow(text_rect);
        }

        const help_rect = frontend_widget.type20TextRect(&self.ui_font, "Help", 350.0, -220.0);
        if (frontend_widget.hitRect(help_rect, self.new_game_button_states[4]).contains(local_mouse)) {
            hovered_index = 4;
        }

        const back_rect = frontend_widget.type20TextRect(&self.ui_font, "Back", 350.0, frontend_widget.type20_center_offset_x);
        if (frontend_widget.hitRect(back_rect, self.new_game_button_states[5]).contains(local_mouse)) {
            hovered_index = 5;
        }

        if (hovered_index) |index| {
            self.setFrontendHoverTarget(hoverTargetForNewGame(index));
            self.new_game_menu_index = index;
            if (rl.isMouseButtonPressed(.left)) {
                self.queueFrontendActivation(.{ .new_game_menu = new_game_menu_items[index] });
            }
        } else {
            self.setFrontendHoverTarget(null);
        }
    }

    fn updateOptionsMouseSelection(self: *AppState) !void {
        const local_mouse = self.currentFrontendMouseLocal() orelse {
            self.setFrontendHoverTarget(null);
            return;
        };

        const fullscreen_rect = optionsFullscreenTextRect(self);
        if (frontend_widget.hitRect(fullscreen_rect, self.options_button_states[options_fullscreen_button_index]).contains(local_mouse)) {
            self.setFrontendHoverTarget(hoverTargetForOptions(0));
            self.options_menu_index = 0;
            if (rl.isMouseButtonPressed(.left)) {
                self.queueFrontendActivation(.{ .options_menu = .fullscreen });
            }
            return;
        }

        const sound_panel_rect = optionsSliderPanelRect(options_sound_slider_center_y);
        if (sound_panel_rect.contains(local_mouse)) {
            self.setFrontendHoverTarget(hoverTargetForOptions(1));
            self.options_menu_index = 1;
            if (rl.isMouseButtonPressed(.left)) {
                if (optionsSliderLessRect(options_sound_slider_center_y).contains(local_mouse)) {
                    try self.stepOptionsMenuValue(.sound_volume, -0.2);
                } else if (optionsSliderMoreRect(options_sound_slider_center_y).contains(local_mouse)) {
                    try self.stepOptionsMenuValue(.sound_volume, 0.2);
                }
            }
            return;
        }

        const music_panel_rect = optionsSliderPanelRect(options_music_slider_center_y);
        if (music_panel_rect.contains(local_mouse)) {
            self.setFrontendHoverTarget(hoverTargetForOptions(2));
            self.options_menu_index = 2;
            if (rl.isMouseButtonPressed(.left)) {
                if (optionsSliderLessRect(options_music_slider_center_y).contains(local_mouse)) {
                    try self.stepOptionsMenuValue(.music_volume, -0.2);
                } else if (optionsSliderMoreRect(options_music_slider_center_y).contains(local_mouse)) {
                    try self.stepOptionsMenuValue(.music_volume, 0.2);
                }
            }
            return;
        }

        const back_rect = optionsBackTextRect(self);
        if (frontend_widget.hitRect(back_rect, self.options_button_states[options_back_button_index]).contains(local_mouse)) {
            self.setFrontendHoverTarget(hoverTargetForOptions(3));
            self.options_menu_index = 3;
            if (rl.isMouseButtonPressed(.left)) {
                self.queueFrontendActivation(.{ .options_menu = .back });
            }
            return;
        }

        self.setFrontendHoverTarget(null);
    }

    fn updateHighScoresMouseSelection(self: *AppState) !void {
        const local_mouse = self.currentFrontendMouseLocal() orelse {
            self.setFrontendHoverTarget(null);
            return;
        };

        if (self.postLevelHighScoreContext() != null) {
            const cancel_rect = highScoreFooterTextRect(self, post_level_high_score_actions[0].label(), high_score_entry_cancel_x);
            if (frontend_widget.hitRect(cancel_rect, self.post_level_high_score_button_states[0]).contains(local_mouse)) {
                self.setFrontendHoverTarget(hoverTargetForPostLevelHighScores(0));
                self.post_level_high_score_action_index = 0;
                if (rl.isMouseButtonPressed(.left)) {
                    self.queueFrontendActivation(.{ .post_level_high_scores = .cancel });
                }
                return;
            }

            const submit_rect = highScoreFooterTextRect(self, post_level_high_score_actions[1].label(), high_score_entry_submit_x);
            if (frontend_widget.hitRect(submit_rect, self.post_level_high_score_button_states[1]).contains(local_mouse)) {
                self.setFrontendHoverTarget(hoverTargetForPostLevelHighScores(1));
                self.post_level_high_score_action_index = 1;
                if (rl.isMouseButtonPressed(.left)) {
                    self.queueFrontendActivation(.{ .post_level_high_scores = .submit });
                }
                return;
            }
        } else {
            const back_rect = highScoreFooterTextRect(self, "Back", high_score_back_x);
            if (frontend_widget.hitRect(back_rect, self.high_score_button_states[0]).contains(local_mouse)) {
                self.setFrontendHoverTarget(hoverTargetForHighScores(0));
                self.high_scores_action_index = 0;
                if (rl.isMouseButtonPressed(.left)) {
                    self.queueFrontendActivation(.{ .high_scores_menu = .back });
                }
                return;
            }

            const toggle_rect = highScoreFooterTextRect(self, highScoreTableToggleLabel(high_score_screen_modes[@min(self.high_scores_menu_index, high_score_screen_modes.len - 1)]), high_score_toggle_x);
            if (frontend_widget.hitRect(toggle_rect, self.high_score_button_states[1]).contains(local_mouse)) {
                self.setFrontendHoverTarget(hoverTargetForHighScores(1));
                self.high_scores_action_index = 1;
                if (rl.isMouseButtonPressed(.left)) {
                    self.queueFrontendActivation(.{ .high_scores_menu = .switch_table });
                }
                return;
            }
        }

        self.setFrontendHoverTarget(null);
    }

    fn updateExitPromptMouseSelection(self: *AppState) !void {
        const local_mouse = self.currentFrontendMouseLocal() orelse {
            self.setFrontendHoverTarget(null);
            return;
        };

        const yes_rect = exitPromptTextRect(self, exit_prompt_choices[0].label(), exit_prompt_yes_x);
        if (frontend_widget.hitRect(yes_rect, self.exit_prompt_button_states[0]).contains(local_mouse)) {
            self.setFrontendHoverTarget(hoverTargetForExitPrompt(0));
            self.exit_prompt_choice_index = 0;
            if (rl.isMouseButtonPressed(.left)) {
                self.queueFrontendActivation(.{ .exit_prompt = .yes });
            }
            return;
        }

        const no_rect = exitPromptTextRect(self, exit_prompt_choices[1].label(), exit_prompt_no_x);
        if (frontend_widget.hitRect(no_rect, self.exit_prompt_button_states[1]).contains(local_mouse)) {
            self.setFrontendHoverTarget(hoverTargetForExitPrompt(1));
            self.exit_prompt_choice_index = 1;
            if (rl.isMouseButtonPressed(.left)) {
                self.queueFrontendActivation(.{ .exit_prompt = .no });
            }
            return;
        }

        self.setFrontendHoverTarget(null);
    }

    fn simulateGameTick(self: *AppState, runner_input: gameplay.RunnerInput) !void {
        self.game_phase_ticks += 1;
        if (self.current_game_background_runtime) |*runtime| {
            runtime.update();
        }
        if (self.game_status_ticks > 0) {
            self.game_status_ticks -= 1;
            if (self.game_status_ticks == 0) {
                self.game_status_message = null;
            }
        }
        self.level_prompt_queue.tick();

        if (self.frontend_transition.update()) |next_phase| {
            try self.enterGamePhase(next_phase);
            self.frontend_transition.completeHandoff();
            return;
        }

        if (try self.updatePendingFrontendActivation()) {
            return;
        }

        self.updateFrontendWidgetAnimations();

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
            if (self.current_track_preview) |*loaded_track_preview| {
                if (self.level_runner) |*runner| {
                    runner.step(loaded_track_preview, runner_input, @floatCast(self.simulation_clock.step_seconds));
                }
            }
            try self.syncActiveLevelSegment(false);
            if (self.level_runner) |*runner| {
                switch (runner.consumeHandoff()) {
                    .none => {},
                    .completion => {
                        try self.beginCompletedRun();
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

    fn handleGameInput(self: *AppState) !void {
        if (rl.isKeyPressed(.escape)) {
            switch (self.game_phase) {
                .level => try self.enterGamePhase(.main_menu),
                .boot => self.should_exit = true,
                .main_menu => try self.beginExitPrompt(.main_menu),
                .intro, .credits => self.frontend_transition.beginFadeOut(.main_menu),
                .new_game_menu, .help => try self.enterGamePhase(.main_menu),
                .high_scores_menu => if (self.postLevelHighScoreContext() != null)
                    try self.cancelPostLevelHighScoreEntry()
                else
                    try self.enterGamePhase(.main_menu),
                .options_menu => try self.leaveOptionsMenu(),
                .route_map_menu => try self.enterGamePhase(.main_menu),
                .exit_prompt => try self.enterGamePhase(self.exit_prompt_return_phase),
                .completion_screen => try self.continueCompletionScreen(),
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
                try self.updateMainMenuMouseSelection();
                if (rl.isKeyPressed(.up)) {
                    self.menu_index = wrappedIndex(main_menu_items.len, self.menu_index, -1);
                }
                if (rl.isKeyPressed(.down)) {
                    self.menu_index = wrappedIndex(main_menu_items.len, self.menu_index, 1);
                }
                if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    self.queueFrontendActivation(.{ .main_menu = main_menu_items[self.menu_index] });
                }
            },
            .new_game_menu => {
                try self.updateNewGameMenuMouseSelection();
                if (rl.isKeyPressed(.up)) {
                    self.new_game_menu_index = wrappedIndex(new_game_menu_items.len, self.new_game_menu_index, -1);
                }
                if (rl.isKeyPressed(.down)) {
                    self.new_game_menu_index = wrappedIndex(new_game_menu_items.len, self.new_game_menu_index, 1);
                }
                if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    self.queueFrontendActivation(.{ .new_game_menu = new_game_menu_items[self.new_game_menu_index] });
                }
            },
            .options_menu => {
                try self.updateOptionsMouseSelection();
                if (rl.isKeyPressed(.up)) {
                    self.options_menu_index = wrappedIndex(options_menu_items.len, self.options_menu_index, -1);
                }
                if (rl.isKeyPressed(.down)) {
                    self.options_menu_index = wrappedIndex(options_menu_items.len, self.options_menu_index, 1);
                }

                const selected = options_menu_items[self.options_menu_index];
                if (rl.isKeyPressed(.left) or rl.isKeyPressed(.a)) {
                    try self.stepOptionsMenuValue(selected, -0.2);
                }
                if (rl.isKeyPressed(.right) or rl.isKeyPressed(.d)) {
                    try self.stepOptionsMenuValue(selected, 0.2);
                }
                if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    switch (selected) {
                        .fullscreen, .back => self.queueFrontendActivation(.{ .options_menu = selected }),
                        .sound_volume, .music_volume => {},
                    }
                }
            },
            .route_map_menu => {
                const route_actions = self.activeRouteMenuActions();
                if (rl.isKeyPressed(.up)) {
                    self.route_menu_action_index = wrappedIndex(route_actions.len, self.route_menu_action_index, -1);
                }
                if (rl.isKeyPressed(.down)) {
                    self.route_menu_action_index = wrappedIndex(route_actions.len, self.route_menu_action_index, 1);
                }
                if (rl.isKeyPressed(.left)) {
                    try self.stepFrontendRouteSelection(-1);
                }
                if (rl.isKeyPressed(.right)) {
                    try self.stepFrontendRouteSelection(1);
                }
                if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    try self.activateRouteMenuAction(route_actions[self.route_menu_action_index]);
                }
            },
            .high_scores_menu => {
                try self.updateHighScoresMouseSelection();
                if (self.postLevelHighScoreContext() != null) {
                    self.collectPostLevelHighScoreTextInput();
                    if (rl.isKeyPressed(.up) or rl.isKeyPressed(.left)) {
                        self.post_level_high_score_action_index = wrappedIndex(post_level_high_score_actions.len, self.post_level_high_score_action_index, -1);
                    }
                    if (rl.isKeyPressed(.down) or rl.isKeyPressed(.right)) {
                        self.post_level_high_score_action_index = wrappedIndex(post_level_high_score_actions.len, self.post_level_high_score_action_index, 1);
                    }
                    if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                        self.queueFrontendActivation(.{ .post_level_high_scores = post_level_high_score_actions[self.post_level_high_score_action_index] });
                    }
                } else {
                    if (rl.isKeyPressed(.up) or rl.isKeyPressed(.left)) {
                        self.high_scores_action_index = wrappedIndex(high_score_menu_actions.len, self.high_scores_action_index, -1);
                    }
                    if (rl.isKeyPressed(.down) or rl.isKeyPressed(.right)) {
                        self.high_scores_action_index = wrappedIndex(high_score_menu_actions.len, self.high_scores_action_index, 1);
                    }
                    if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                        self.queueFrontendActivation(.{ .high_scores_menu = high_score_menu_actions[self.high_scores_action_index] });
                    }
                }
            },
            .exit_prompt => {
                try self.updateExitPromptMouseSelection();
                if (rl.isKeyPressed(.up) or rl.isKeyPressed(.left)) {
                    self.exit_prompt_choice_index = wrappedIndex(exit_prompt_choices.len, self.exit_prompt_choice_index, -1);
                }
                if (rl.isKeyPressed(.down) or rl.isKeyPressed(.right)) {
                    self.exit_prompt_choice_index = wrappedIndex(exit_prompt_choices.len, self.exit_prompt_choice_index, 1);
                }
                if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    self.queueFrontendActivation(.{ .exit_prompt = exit_prompt_choices[self.exit_prompt_choice_index] });
                }
            },
            .completion_screen => {
                if (rl.isKeyPressed(.up) or rl.isKeyPressed(.left)) {
                    self.completion_action_index = wrappedIndex(completion_actions.len, self.completion_action_index, -1);
                }
                if (rl.isKeyPressed(.down) or rl.isKeyPressed(.right)) {
                    self.completion_action_index = wrappedIndex(completion_actions.len, self.completion_action_index, 1);
                }
                if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    try self.activateCompletionAction(completion_actions[self.completion_action_index]);
                }
            },
            .credits => {
                if (rl.isMouseButtonPressed(.left)) {
                    self.frontend_transition.beginFadeOut(.main_menu);
                }
            },
            .help => {
                if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    try self.enterGamePhase(.main_menu);
                }
            },
            .level => {
                const accepts_input = if (self.level_runner) |runner| runner.acceptsGameplayInput() else false;
                if (accepts_input and (rl.isKeyPressed(.left) or rl.isKeyPressed(.a))) {
                    self.mouse_level_lane_target = null;
                    self.pending_level_input.lane_delta -= 1;
                }
                if (accepts_input and (rl.isKeyPressed(.right) or rl.isKeyPressed(.d))) {
                    self.mouse_level_lane_target = null;
                    self.pending_level_input.lane_delta += 1;
                }
                if (accepts_input and (rl.isKeyPressed(.up) or rl.isKeyPressed(.w))) {
                    self.pending_level_input.speed_delta_rows_per_second += 2.0;
                }
                if (accepts_input and (rl.isKeyPressed(.down) or rl.isKeyPressed(.s))) {
                    self.pending_level_input.speed_delta_rows_per_second -= 2.0;
                }
                if (accepts_input and rl.isKeyPressed(.space)) {
                    self.pending_level_input.toggle_pause = true;
                }
                if (rl.isKeyPressed(.r)) {
                    self.mouse_level_lane_target = null;
                    self.pending_level_input.reset = true;
                }
                if (accepts_input) {
                    if (self.current_track_preview) |loaded_track_preview| {
                        if (self.level_runner) |runner| {
                            const mouse_delta = rl.getMouseDelta();
                            if (@abs(mouse_delta.x) > 0.01) {
                                self.mouse_level_lane_target = laneTargetForRunnerMouse(
                                    loaded_track_preview,
                                    runner,
                                    @floatFromInt(rl.getMouseX()),
                                );
                            }
                            if (self.mouse_level_lane_target) |lane_target| {
                                if (lane_target < runner.lane_index) {
                                    self.pending_level_input.lane_delta -= 1;
                                } else if (lane_target > runner.lane_index) {
                                    self.pending_level_input.lane_delta += 1;
                                }
                            }
                        }
                    }
                }
            },
        }
    }

    fn enterGamePhase(self: *AppState, phase: GamePhase) !void {
        self.game_phase = phase;
        self.game_phase_ticks = 0;
        self.hovered_frontend_target = null;
        self.pending_frontend_activation = null;
        try self.syncGamePhaseResources();
        self.snapFrontendWidgetStates();
    }

    fn enterStartPhase(self: *AppState, phase: GamePhase) !void {
        try self.high_score_tables.loadFromRuntimeRoot(self.allocator, self.runtime_root_path);

        switch (phase) {
            .boot => try self.enterGamePhase(.boot),
            .intro,
            .main_menu,
            .new_game_menu,
            .options_menu,
            .high_scores_menu,
            .help,
            .credits,
            => try self.enterGamePhase(phase),
            .exit_prompt => try self.beginExitPrompt(.main_menu),
            .route_map_menu => try self.enterRouteMapMenu(.postal),
            .level => try self.enterGameplayShell(default_level_path),
            .completion_screen => return error.UnsupportedStartPhase,
        }
    }

    fn performMainMenuItem(self: *AppState, item: MainMenuItem) !void {
        switch (item) {
            .new_game => try self.enterGamePhase(.new_game_menu),
            .high_scores => {
                self.high_scores_menu_index = 0;
                self.high_scores_action_index = 1;
                try self.enterGamePhase(.high_scores_menu);
            },
            .options => try self.enterGamePhase(.options_menu),
            .credits => try self.enterGamePhase(.credits),
            .exit => try self.beginExitPrompt(.main_menu),
        }
    }

    fn activateMainMenuItem(self: *AppState, item: MainMenuItem) !void {
        self.playFrontendSelectSound();
        try self.performMainMenuItem(item);
    }

    fn performNewGameMenuItem(self: *AppState, item: NewGameMenuItem) !void {
        switch (item) {
            .tutorial => try self.enterFrontendLevelMode(.tutorial),
            .postal_mode => try self.enterFrontendLevelMode(.postal),
            .time_trial => try self.enterFrontendLevelMode(.time_trial),
            .challenge_mode => try self.enterFrontendLevelMode(.challenge),
            .help => try self.enterGamePhase(.help),
            .back => try self.enterGamePhase(.main_menu),
        }
    }

    fn activateNewGameMenuItem(self: *AppState, item: NewGameMenuItem) !void {
        self.playFrontendSelectSound();
        try self.performNewGameMenuItem(item);
    }

    fn performOptionsMenuItem(self: *AppState, item: OptionsMenuItem) !void {
        switch (item) {
            .fullscreen => self.toggleFullscreenPreference(),
            .sound_volume, .music_volume => {},
            .back => try self.leaveOptionsMenu(),
        }
    }

    fn activateOptionsMenuItem(self: *AppState, item: OptionsMenuItem) !void {
        self.playFrontendSelectSound();
        try self.performOptionsMenuItem(item);
    }

    fn beginExitPrompt(self: *AppState, return_phase: GamePhase) !void {
        self.exit_prompt_choice_index = 1;
        self.exit_prompt_return_phase = return_phase;
        try self.enterGamePhase(.exit_prompt);
    }

    fn performExitPromptChoice(self: *AppState, choice: ExitPromptChoice) !void {
        switch (choice) {
            .no => try self.enterGamePhase(self.exit_prompt_return_phase),
            .yes => self.should_exit = true,
        }
    }

    fn activateExitPromptChoice(self: *AppState, choice: ExitPromptChoice) !void {
        self.playFrontendSelectSound();
        try self.performExitPromptChoice(choice);
    }

    fn activateRouteMenuAction(self: *AppState, action: RouteMenuAction) !void {
        self.playFrontendSelectSound();
        switch (action) {
            .play => try self.enterSelectedFrontendRoute(),
            .watch_best_trial => self.setGameStatusMessage("Best-trial replay playback is not ported."),
            .back => try self.enterGamePhase(.main_menu),
        }
    }

    fn activateCompletionAction(self: *AppState, action: CompletionAction) !void {
        self.playFrontendSelectSound();
        switch (action) {
            .continue_flow => try self.continueCompletionScreen(),
            .replay_level => try self.replayCompletedRun(),
        }
    }

    fn performPostLevelHighScoreAction(self: *AppState, action: PostLevelHighScoreAction) !void {
        switch (action) {
            .cancel => try self.cancelPostLevelHighScoreEntry(),
            .submit => try self.submitPostLevelHighScore(),
        }
    }

    fn activatePostLevelHighScoreAction(self: *AppState, action: PostLevelHighScoreAction) !void {
        self.playFrontendSelectSound();
        try self.performPostLevelHighScoreAction(action);
    }

    fn performHighScoreMenuAction(self: *AppState, action: HighScoreMenuAction) !void {
        switch (action) {
            .back => try self.enterGamePhase(.main_menu),
            .switch_table => self.high_scores_menu_index = wrappedIndex(high_score_screen_modes.len, self.high_scores_menu_index, 1),
        }
    }

    fn activateHighScoreMenuAction(self: *AppState, action: HighScoreMenuAction) !void {
        self.playFrontendSelectSound();
        try self.performHighScoreMenuAction(action);
    }

    fn enterGameplayShell(self: *AppState, level_path: []const u8) !void {
        self.active_frontend_mode = null;
        self.active_frontend_level_index = 0;
        try self.loadGameLevel(level_path);
        try self.enterGamePhase(.level);
    }

    fn enterFrontendLevelPath(self: *AppState, mode: FrontendLevelMode, level_index: usize) !void {
        var path_buffer: [64]u8 = undefined;
        const level_path = try frontendLevelPath(mode, level_index, &path_buffer);
        self.active_frontend_mode = mode;
        self.active_frontend_level_index = level_index;
        try self.loadGameLevel(level_path);
        try self.enterGamePhase(.level);
    }

    fn leaveOptionsMenu(self: *AppState) !void {
        try self.saveRuntimeConfig();
        try self.enterGamePhase(.main_menu);
    }

    fn enterFrontendLevelMode(self: *AppState, mode: FrontendLevelMode) !void {
        switch (mode) {
            .postal, .time_trial => try self.enterRouteMapMenu(mode),
            .challenge, .tutorial => try self.enterFrontendLevelPath(mode, 0),
        }
    }

    fn enterRouteMapMenu(self: *AppState, mode: FrontendLevelMode) !void {
        self.frontend_route_mode = mode;
        self.frontend_route_index = self.initialFrontendRouteIndex(mode);
        self.route_menu_action_index = 0;
        try self.reloadFrontendRouteLevel();
        try self.enterGamePhase(.route_map_menu);
    }

    fn unloadFrontendRouteLevel(self: *AppState) void {
        if (self.frontend_route_level) |*loaded_level| {
            loaded_level.deinit();
            self.frontend_route_level = null;
        }
    }

    fn reloadFrontendRouteLevel(self: *AppState) !void {
        self.unloadFrontendRouteLevel();
        const mode = self.frontend_route_mode orelse return;
        var path_buffer: [64]u8 = undefined;
        const level_path = frontendLevelPath(mode, self.frontend_route_index, &path_buffer) catch return;
        const level_index = self.catalog.findLevelIndex(level_path) orelse return;
        self.frontend_route_level = try level.loadFromArchive(self.allocator, &self.catalog, self.catalog.level_entries[level_index]);
    }

    fn currentFrontendGalaxyName(self: *const AppState) ?[]const u8 {
        const names = self.galaxy_names orelse return null;
        return names.nameForRouteIndex(self.frontend_route_index);
    }

    fn routeMapShowsReplay(self: *const AppState) bool {
        _ = self;
        return false;
    }

    fn activeRouteMenuActions(self: *const AppState) []const RouteMenuAction {
        return if (self.routeMapShowsReplay())
            &route_menu_actions_with_replay
        else
            &route_menu_actions_without_replay;
    }

    fn clearLevelPromptQueue(self: *AppState) void {
        self.level_prompt_queue.clear();
    }

    fn queueLevelSegmentPrompt(self: *AppState, segment_entry: *const level.SegmentEntry) void {
        const message = segment_entry.message orelse return;
        self.level_prompt_queue.enqueue(message, level_prompt.durationTicks(segment_entry.duration));
    }

    fn enterSelectedFrontendRoute(self: *AppState) !void {
        const mode = self.frontend_route_mode orelse return;
        try self.enterFrontendLevelPath(mode, self.frontend_route_index);
    }

    fn saveHighScoreTables(self: *AppState) !void {
        try self.high_score_tables.saveToRuntimeRoot(self.allocator, self.runtime_root_path);
    }

    fn beginCompletedRun(self: *AppState) !void {
        if (self.pending_run_result != null) return;

        const loaded_level = self.current_level orelse return;
        const active_mode = self.active_frontend_mode;
        const parcel_target = loaded_level.parcels orelse 0;
        if (completionBonusAppliesForMode(active_mode)) {
            if (self.level_runner) |*runner| {
                runner.applyCompletionBonus(parcel_target);
            }
        }
        const runner = self.level_runner orelse return;
        const parcel_count = runner.counters.parcels;
        const elapsed_millis = completionElapsedMillis(runner);
        var result = PendingRunResult{
            .outcome = .completed,
            .level_name = loaded_level.name,
            .mode = active_mode,
            .elapsed_millis = elapsed_millis,
            .parcel_count = parcel_count,
            .parcel_target = parcel_target,
            .score = 0,
            .score_is_partial = false,
            .score_totals = runner.score,
            .visible_life_stock = runner.visible_life_stock,
            .damage_gauge = runner.damage_gauge,
            .return_target = resultReturnTargetForOutcome(.completed, active_mode),
        };

        switch (active_mode orelse .tutorial) {
            .postal => {
                result.score = runner.score.total;
                result.score_is_partial = true;

                const entry = high_score.Entry{
                    .score = result.score,
                };
                const insert = self.high_score_tables.addArcade(entry);
                result.high_score_mode = .postal;
                result.high_score_rank = insert.rank;
                result.unlocked_next_route = try self.commitPostalRouteProgress();
                try self.saveHighScoreTables();
            },
            .challenge => {
                result.score = runner.score.total;
                result.score_is_partial = true;

                const entry = high_score.Entry{
                    .score = result.score,
                };
                const insert = self.high_score_tables.addSurvival(entry);
                result.high_score_mode = .challenge;
                result.high_score_rank = insert.rank;
                try self.saveHighScoreTables();
            },
            .time_trial => {
                result.score = elapsed_millis;
                const entry = high_score.Entry{
                    .score = elapsed_millis,
                };
                const insert = self.high_score_tables.addTimeTrial(self.active_frontend_level_index, entry);
                result.time_trial_record_improved = insert.improved;
                try self.saveHighScoreTables();
            },
            .tutorial => {},
        }

        self.completion_action_index = 0;
        self.pending_run_result = result;
        try self.enterGamePhase(.completion_screen);
    }

    fn beginFailedRun(self: *AppState, cause: gameplay.DeathCause) !void {
        _ = cause;
        if (self.pending_run_result != null) return;

        const loaded_level = self.current_level orelse return;
        const runner = self.level_runner orelse return;
        const active_mode = self.active_frontend_mode;
        const parcel_target = loaded_level.parcels orelse 0;
        const elapsed_millis = completionElapsedMillis(runner);
        var result = PendingRunResult{
            .outcome = .failed,
            .level_name = loaded_level.name,
            .mode = active_mode,
            .elapsed_millis = elapsed_millis,
            .parcel_count = runner.counters.parcels,
            .parcel_target = parcel_target,
            .score = 0,
            .score_is_partial = true,
            .score_totals = runner.score,
            .visible_life_stock = runner.visible_life_stock,
            .damage_gauge = runner.damage_gauge,
            .return_target = resultReturnTargetForOutcome(.failed, active_mode),
        };

        switch (active_mode orelse .tutorial) {
            .postal => {
                result.score = runner.score.total;
                const entry = high_score.Entry{
                    .score = result.score,
                };
                const insert = self.high_score_tables.addArcade(entry);
                result.high_score_mode = .postal;
                result.high_score_rank = insert.rank;
                try self.saveHighScoreTables();
            },
            .challenge => {
                result.score = runner.score.total;
                const entry = high_score.Entry{
                    .score = result.score,
                };
                const insert = self.high_score_tables.addSurvival(entry);
                result.high_score_mode = .challenge;
                result.high_score_rank = insert.rank;
                try self.saveHighScoreTables();
            },
            .time_trial => {
                result.score = elapsed_millis;
                const entry = high_score.Entry{
                    .score = elapsed_millis,
                };
                const insert = self.high_score_tables.addTimeTrial(self.active_frontend_level_index, entry);
                result.time_trial_record_improved = insert.improved;
                try self.saveHighScoreTables();
            },
            .tutorial => {
                result.score = runner.score.total;
            },
        }

        self.completion_action_index = 0;
        self.pending_run_result = result;
        try self.enterGamePhase(.completion_screen);
    }

    fn continueCompletionScreen(self: *AppState) !void {
        if (self.postLevelHighScoreContext()) |context| {
            self.preparePostLevelHighScoreEntry();
            self.high_scores_menu_index = highScoreModeIndex(context.mode);
            try self.enterGamePhase(.high_scores_menu);
            return;
        }
        try self.finishPendingRunReturn();
    }

    fn cancelPostLevelHighScoreEntry(self: *AppState) !void {
        self.clearPostLevelHighScoreEntry();
        try self.finishPendingRunReturn();
    }

    fn finishPendingRunReturn(self: *AppState) !void {
        const result = self.pending_run_result orelse {
            try self.enterGamePhase(.main_menu);
            return;
        };
        self.clearPostLevelHighScoreEntry();
        self.pending_run_result = null;
        self.completion_action_index = 0;

        switch (result.return_target) {
            .main_menu => try self.enterGamePhase(.main_menu),
            .postal_route_map => try self.enterRouteMapMenu(.postal),
            .time_trial_route_map => try self.enterRouteMapMenu(.time_trial),
            .replay_current_level => if (result.mode) |mode|
                try self.enterFrontendLevelPath(mode, self.active_frontend_level_index)
            else
                try self.enterGamePhase(.main_menu),
        }
    }

    fn replayCompletedRun(self: *AppState) !void {
        const loaded_level = self.current_level orelse {
            try self.finishPendingRunReturn();
            return;
        };
        const level_path = loaded_level.source_path;
        const mode = self.pending_run_result.?.mode;

        self.clearPostLevelHighScoreEntry();
        self.pending_run_result = null;
        self.completion_action_index = 0;
        if (mode) |frontend_mode| {
            try self.enterFrontendLevelPath(frontend_mode, self.active_frontend_level_index);
            return;
        }
        try self.enterGameplayShell(level_path);
    }

    fn postLevelHighScoreContext(self: *const AppState) ?PendingHighScoreEntry {
        const result = self.pending_run_result orelse return null;
        const mode = result.high_score_mode orelse return null;
        const rank = result.high_score_rank orelse return null;
        return .{
            .mode = mode,
            .rank = rank,
        };
    }

    fn preparePostLevelHighScoreEntry(self: *AppState) void {
        self.clearPostLevelHighScoreEntry();
        self.post_level_high_score_action_index = 1;

        const context = self.postLevelHighScoreContext() orelse return;
        const entry = self.highScoreEntry(context.mode, context.rank) orelse return;
        const existing_name = entry.name();
        const clipped = existing_name[0..@min(existing_name.len, self.post_level_high_score_name_buf.len)];
        @memcpy(self.post_level_high_score_name_buf[0..clipped.len], clipped);
        self.post_level_high_score_name_len = clipped.len;
    }

    fn clearPostLevelHighScoreEntry(self: *AppState) void {
        @memset(&self.post_level_high_score_name_buf, 0);
        self.post_level_high_score_name_len = 0;
        self.post_level_high_score_action_index = 1;
    }

    fn postLevelHighScoreDraft(self: *const AppState) []const u8 {
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

    fn submitPostLevelHighScore(self: *AppState) !void {
        if (self.pending_run_result == null) {
            try self.enterGamePhase(.main_menu);
            return;
        }
        const context = self.postLevelHighScoreContext() orelse {
            try self.finishPendingRunReturn();
            return;
        };
        const entry = self.highScoreEntryMut(context.mode, context.rank) orelse {
            try self.finishPendingRunReturn();
            return;
        };

        entry.setName(std.mem.trimRight(u8, self.postLevelHighScoreDraft(), " "));
        try self.saveHighScoreTables();
        try self.finishPendingRunReturn();
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

    fn commitPostalRouteProgress(self: *AppState) !bool {
        const current_index: u32 = @intCast(self.active_frontend_level_index);
        self.runtime_config.setRouteSelectionIndex(current_index);
        const next_unlock = current_index + 1;
        var unlocked = false;
        if (next_unlock > self.runtime_config.routeUnlockLimit()) {
            self.runtime_config.setRouteUnlockLimit(next_unlock);
            self.setGameStatusMessage("Unlocked the next delivery route.");
            unlocked = true;
        }
        try self.saveRuntimeConfig();
        return unlocked;
    }

    fn initialFrontendRouteIndex(self: *const AppState, mode: FrontendLevelMode) usize {
        const available_limit = self.availableFrontendRouteLimit(mode);
        if (available_limit == 0) return 0;
        const saved_index: usize = @intCast(self.runtime_config.routeSelectionIndex());
        return std.math.clamp(saved_index, @as(usize, 1), available_limit);
    }

    fn availableFrontendRouteLimit(self: *const AppState, mode: FrontendLevelMode) usize {
        const highest_available = self.highestAvailableFrontendRouteIndex(mode);
        if (highest_available == 0) return 0;
        const saved_limit: usize = @intCast(self.runtime_config.routeUnlockLimit());
        return std.math.clamp(saved_limit, @as(usize, 1), highest_available);
    }

    fn highestAvailableFrontendRouteIndex(self: *const AppState, mode: FrontendLevelMode) usize {
        switch (mode) {
            .postal => {
                if (self.catalog.findLevelIndex("LEVELS/ARCADEEXTRA000.TXT") != null) return 0x33;
                return 0x32;
            },
            .time_trial => {
                var scratch: [64]u8 = undefined;
                var last_index: usize = 0x32;
                var extra_index: usize = 0x33;
                while (extra_index < 0x80) : (extra_index += 1) {
                    const path = frontendLevelPath(.time_trial, extra_index, &scratch) catch break;
                    if (self.catalog.findLevelIndex(path) == null) break;
                    last_index = extra_index;
                }
                return last_index;
            },
            .challenge, .tutorial => return 0,
        }
    }

    fn stepFrontendRouteSelection(self: *AppState, delta: isize) !void {
        const mode = self.frontend_route_mode orelse return;
        const route_count = self.availableFrontendRouteLimit(mode);
        if (route_count == 0) return;
        self.frontend_route_index = wrappedIndex(route_count, self.frontend_route_index - 1, delta) + 1;
        try self.reloadFrontendRouteLevel();
    }

    fn syncGamePhaseResources(self: *AppState) !void {
        switch (self.game_phase) {
            .boot => {
                self.stopAudioPreview();
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
                try self.playMusicByPath(intro_music_path);
                try self.loadTextScript(intro_script_path);
            },
            .main_menu, .new_game_menu, .options_menu, .high_scores_menu, .exit_prompt => {
                self.active_level_segment_index = null;
                self.clearLevelPromptQueue();
                self.mouse_level_lane_target = null;
                self.unloadTextScript();
                self.unloadLoadingScreen();
                try self.loadGameBackground(main_menu_background_path);
                try self.playMusicByPath(default_audio_path);
            },
            .route_map_menu => {
                self.active_level_segment_index = null;
                self.clearLevelPromptQueue();
                self.mouse_level_lane_target = null;
                self.unloadTextScript();
                self.unloadLoadingScreen();
                try self.loadGameBackground(route_map_background_path);
                try self.playMusicByPath(default_audio_path);
            },
            .credits => {
                self.active_level_segment_index = null;
                self.clearLevelPromptQueue();
                self.mouse_level_lane_target = null;
                self.unloadLoadingScreen();
                try self.loadGameBackground(intro_background_path);
                try self.playMusicByPath(intro_music_path);
                try self.loadTextScript(credits_script_path);
            },
            .help => {
                self.active_level_segment_index = null;
                self.clearLevelPromptQueue();
                self.mouse_level_lane_target = null;
                self.unloadTextScript();
                self.unloadLoadingScreen();
                try self.loadGameBackground(help_background_path);
                try self.playMusicByPath(default_audio_path);
            },
            .completion_screen => {
                self.clearLevelPromptQueue();
                self.mouse_level_lane_target = null;
                self.unloadTextScript();
                self.unloadLoadingScreen();
                try self.loadCurrentLevelBackground();
            },
            .level => {
                self.stopAudioPreview();
                self.clearLevelPromptQueue();
                self.mouse_level_lane_target = null;
                self.unloadTextScript();
                self.unloadLoadingScreen();
                try self.loadCurrentLevelBackground();
                try self.syncActiveLevelSegment(true);
            },
        }
    }

    fn loadGameLevel(self: *AppState, level_path: []const u8) !void {
        self.level_index = self.catalog.findLevelIndex(level_path) orelse return error.EntryNotFound;
        try self.reloadLevel();
    }

    fn playMusicByPath(self: *AppState, path: []const u8) !void {
        if (!self.audio_ready) return;
        if (self.current_music) |music| {
            if (std.ascii.eqlIgnoreCase(music.path, path)) {
                self.applyAudioConfigVolumes();
                if (!rl.isMusicStreamPlaying(music.music)) {
                    rl.playMusicStream(music.music);
                }
                return;
            }
        }

        self.stopAudioPreview();
        self.current_music = if (self.takePreloadedMusic(path)) |music|
            music
        else
            try self.catalog.loadMusicByPath(self.allocator, path);
        self.applyAudioConfigVolumes();
        rl.playMusicStream(self.current_music.?.music);
    }

    fn playSoundByPath(self: *AppState, path: []const u8) !void {
        if (!self.audio_ready) return;
        if (self.current_sound) |*sound| {
            sound.unload();
            self.current_sound = null;
        }

        self.current_sound = try self.catalog.loadSoundByPath(self.allocator, path);
        self.applyAudioConfigVolumes();
        rl.playSound(self.current_sound.?.sound);
    }

    fn syncActiveLevelSegment(self: *AppState, replay_sample_on_match: bool) !void {
        const loaded_level = self.current_level orelse {
            self.active_level_segment_index = null;
            self.clearLevelPromptQueue();
            return;
        };
        const loaded_track_preview = self.current_track_preview orelse {
            self.active_level_segment_index = null;
            self.clearLevelPromptQueue();
            return;
        };
        const runner = self.level_runner orelse {
            self.active_level_segment_index = null;
            self.clearLevelPromptQueue();
            return;
        };

        const row_location = loaded_track_preview.locateRow(runner.current_global_row) orelse {
            self.active_level_segment_index = null;
            self.clearLevelPromptQueue();
            return;
        };
        if (row_location.segment_index >= loaded_level.segments.len) {
            self.active_level_segment_index = null;
            self.clearLevelPromptQueue();
            return;
        }

        self.level_segment_index = row_location.segment_index;
        const segment_entry = &loaded_level.segments[row_location.segment_index];
        const previous_segment_index = self.active_level_segment_index;
        const segment_changed = previous_segment_index == null or previous_segment_index.? != row_location.segment_index;
        self.active_level_segment_index = row_location.segment_index;
        if (segment_changed) {
            if (previous_segment_index) |previous_index| {
                if (row_location.segment_index < previous_index) {
                    self.clearLevelPromptQueue();
                }
            }
            self.queueLevelSegmentPrompt(segment_entry);
        }

        if (segment_changed or replay_sample_on_match) {
            if (segment_entry.sample) |sample_path| {
                try self.playSoundByPath(sample_path);
            }
        }
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
            try background.Loaded.loadByPath(self.allocator, &self.catalog, script_path);
        self.current_game_background_runtime = background.Runtime.init(&loaded);
        self.current_game_background = loaded;
    }

    fn loadLoadingScreen(self: *AppState) !void {
        self.unloadLoadingScreen();
        self.current_loading_screen = try loading_screen.Loaded.load(self.allocator, &self.catalog);
    }

    fn loadTextScript(self: *AppState, path: []const u8) !void {
        self.unloadTextScript();
        self.current_text_script = if (self.takePreloadedTextScript(path)) |loaded|
            loaded
        else
            try intro.loadByPath(self.allocator, &self.catalog, path);
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

    fn takePreloadedMusic(self: *AppState, path: []const u8) ?assets.LoadedMusic {
        if (std.ascii.eqlIgnoreCase(path, intro_music_path)) {
            return takeOptional(assets.LoadedMusic, &self.preloaded_intro_music);
        }
        if (std.ascii.eqlIgnoreCase(path, default_audio_path)) {
            return takeOptional(assets.LoadedMusic, &self.preloaded_menu_music);
        }
        return null;
    }

    fn currentTextScriptDurationTicks(self: *const AppState) ?u64 {
        const script = self.current_text_script orelse return null;
        return script.durationTicks();
    }

    fn applyAudioConfigVolumes(self: *AppState) void {
        if (!self.audio_ready) return;

        const sound_volume = if (self.audio_muted) 0.0 else self.runtime_config.soundVolume();
        const music_volume = if (self.audio_muted) 0.0 else self.runtime_config.musicVolume();

        if (self.current_sound) |sound| {
            rl.setSoundVolume(sound.sound, sound_volume);
        }
        if (self.frontend_sound_fx.highlight) |sound| {
            rl.setSoundVolume(sound.sound, sound_volume);
        }
        if (self.frontend_sound_fx.select) |sound| {
            rl.setSoundVolume(sound.sound, sound_volume);
        }
        if (self.current_music) |music| {
            rl.setMusicVolume(music.music, music_volume);
        }
    }

    fn toggleFullscreenPreference(self: *AppState) void {
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

    fn stepOptionsMenuValue(self: *AppState, item: OptionsMenuItem, delta: f32) !void {
        switch (item) {
            .fullscreen => {
                if (delta != 0.0) {
                    self.playFrontendSelectSound();
                    self.toggleFullscreenPreference();
                }
            },
            .sound_volume => {
                const previous = self.runtime_config.soundVolume();
                self.runtime_config.setSoundVolume(self.runtime_config.soundVolume() + delta);
                self.applyAudioConfigVolumes();
                if (self.runtime_config.soundVolume() != previous) {
                    self.playFrontendSelectSound();
                }
            },
            .music_volume => {
                const previous = self.runtime_config.musicVolume();
                self.runtime_config.setMusicVolume(self.runtime_config.musicVolume() + delta);
                self.applyAudioConfigVolumes();
                if (self.runtime_config.musicVolume() != previous) {
                    self.playFrontendSelectSound();
                }
            },
            .back => if (delta != 0.0) {
                self.playFrontendSelectSound();
                try self.leaveOptionsMenu();
            },
        }
    }

    fn currentTextScriptProgress(self: *const AppState) ?f32 {
        const script = self.currentTextScript() orelse return null;
        return script.progressForTicks(self.game_phase_ticks);
    }

    fn currentTextScript(self: *const AppState) ?*const intro.Loaded {
        if (self.current_text_script) |*script| {
            return script;
        }
        return null;
    }

    fn maybeQueueAutoScreenshot(self: *AppState) !void {
        const auto_screenshot = self.auto_screenshot orelse return;
        if (self.auto_screenshot_taken) return;
        if (self.game_phase != auto_screenshot.phase) return;
        if (self.game_phase_ticks < auto_screenshot.tick) return;

        self.auto_screenshot_taken = true;
        try self.queueScreenshot(true);
    }

    fn queueScreenshot(self: *AppState, exit_after_capture: bool) !void {
        if (self.pending_screenshot != null) return;

        self.frame_capture_index += 1;
        const relative_path = try std.fmt.allocPrint(
            self.allocator,
            "{s}/snail-{s}-{s}-{d:0>6}-{d:0>3}.png",
            .{
                self.screenshot_dir,
                @tagName(self.command),
                @tagName(self.game_phase),
                self.game_phase_ticks,
                self.frame_capture_index,
            },
        );
        errdefer self.allocator.free(relative_path);
        const relative_path_z = try self.allocator.dupeZ(u8, relative_path);
        defer self.allocator.free(relative_path);
        errdefer self.allocator.free(relative_path_z);

        self.pending_screenshot = .{
            .relative_path_z = relative_path_z,
            .exit_after_capture = exit_after_capture,
        };
    }

    fn flushQueuedScreenshot(self: *AppState) !void {
        var request = self.pending_screenshot orelse return;
        self.pending_screenshot = null;
        defer request.deinit(self.allocator);

        const screenshot = try rl.loadImageFromScreen();
        defer screenshot.unload();
        if (!rl.exportImage(screenshot, request.relative_path_z)) {
            return error.ScreenshotExportFailed;
        }
        std.log.info("captured screenshot {s}", .{request.relative_path_z});

        if (request.exit_after_capture) {
            self.should_exit = true;
        }
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

    fn setMode(self: *AppState, mode: Mode) !void {
        if (self.mode == mode) return;

        if (self.mode == .audio) {
            self.stopAudioPreview();
        }
        self.mode = mode;
    }

    fn stepSelection(self: *AppState, delta: isize) !void {
        switch (self.mode) {
            .textures => {
                self.texture_index = wrappedIndex(self.catalog.texture_entries.len, self.texture_index, delta);
                try self.reloadTexture();
            },
            .audio => {
                self.stopAudioPreview();
                self.audio_index = wrappedIndex(self.catalog.audio_entries.len, self.audio_index, delta);
            },
            .models => {
                self.model_index = wrappedIndex(self.catalog.model_entries.len, self.model_index, delta);
                try self.reloadModel();
            },
            .objects => {
                self.object_index = wrappedIndex(self.catalog.object_entries.len, self.object_index, delta);
                try self.reloadObject();
            },
            .levels => {},
        }
    }

    fn stepLevelSegment(self: *AppState, delta: isize) !void {
        const loaded_level = self.current_level orelse return;
        self.level_segment_index = wrappedIndex(loaded_level.segments.len, self.level_segment_index, delta);
        try self.reloadLevelSegment();
    }

    fn previewSound(self: *AppState) !void {
        if (!self.audio_ready or self.catalog.audio_entries.len == 0) {
            return;
        }

        self.stopAudioPreview();
        const sound = try self.catalog.loadSound(self.allocator, self.catalog.audio_entries[self.audio_index]);
        self.current_sound = sound;
        self.applyAudioConfigVolumes();
        rl.playSound(self.current_sound.?.sound);
    }

    fn previewMusic(self: *AppState) !void {
        if (!self.audio_ready or self.catalog.audio_entries.len == 0) {
            return;
        }

        self.stopAudioPreview();
        const music = try self.catalog.loadMusic(self.allocator, self.catalog.audio_entries[self.audio_index]);
        self.current_music = music;
        self.applyAudioConfigVolumes();
        rl.playMusicStream(self.current_music.?.music);
    }

    fn stopAudioPreview(self: *AppState) void {
        if (self.current_sound) |*sound| {
            sound.unload();
            self.current_sound = null;
        }
        if (self.current_music) |*music| {
            music.unload();
            self.current_music = null;
        }
    }

    fn reloadTexture(self: *AppState) !void {
        if (self.current_texture) |*texture| {
            texture.unload();
            self.current_texture = null;
        }

        const texture = try self.catalog.loadTexture(self.allocator, self.catalog.texture_entries[self.texture_index]);
        self.current_texture = texture;
    }

    fn reloadModel(self: *AppState) !void {
        if (self.current_model) |*model| {
            model.deinit();
            self.current_model = null;
        }
        if (self.current_animation) |*animation| {
            animation.deinit();
            self.current_animation = null;
        }

        const entry = self.catalog.model_entries[self.model_index];
        if (self.animation_catalog.findClipIndexForModelPath(entry.path)) |clip_index| {
            const clip = &self.animation_catalog.clips[clip_index];
            if (clip.frames.len > 1) {
                const animation = try xanim.Player.load(
                    self.allocator,
                    &self.catalog,
                    clip,
                    self.model_flip_v,
                    xanim.frameNumberFromPath(entry.path),
                );
                self.current_animation = animation;
                return;
            }
        }

        self.current_model = try x2.LoadedModel.loadFromArchive(self.allocator, &self.catalog, entry, self.model_flip_v);
    }

    fn reloadObject(self: *AppState) !void {
        if (self.current_object) |*loaded_object| {
            loaded_object.deinit();
            self.current_object = null;
        }
        if (self.catalog.object_entries.len == 0) return;

        const entry = self.catalog.object_entries[self.object_index];
        self.current_object = try object.LoadedObject.loadFromArchive(
            self.allocator,
            &self.catalog,
            entry,
            self.object_flip_v,
        );
    }

    fn reloadLevel(self: *AppState) !void {
        if (self.current_level) |*loaded_level| {
            loaded_level.deinit();
            self.current_level = null;
        }
        if (self.current_segment) |*loaded_segment| {
            loaded_segment.deinit();
            self.current_segment = null;
        }
        if (self.current_track_preview) |*loaded_track_preview| {
            loaded_track_preview.deinit();
            self.current_track_preview = null;
        }
        self.level_runner = null;
        if (self.catalog.level_entries.len == 0) return;

        const entry = self.catalog.level_entries[self.level_index];
        self.current_level = try level.loadFromArchive(self.allocator, &self.catalog, entry);
        if (self.current_level) |*loaded_level| {
            self.current_track_preview = try track.LoadedLevelPreview.load(self.allocator, &self.catalog, loaded_level);
            if (self.current_track_preview) |*loaded_track_preview| {
                self.level_runner = gameplay.Runner.init(loaded_track_preview);
                self.level_runner.?.configureCompletionBonus(
                    loaded_level.parcels orelse 0,
                    completionBonusAppliesForMode(self.active_frontend_mode),
                );
                self.level_runner.?.configureSessionMode(runnerSessionModeForFrontendMode(self.active_frontend_mode));
            }
        }
        self.level_segment_index = 0;
        try self.reloadLevelSegment();
    }

    fn reloadLevelSegment(self: *AppState) !void {
        if (self.current_segment) |*loaded_segment| {
            loaded_segment.deinit();
            self.current_segment = null;
        }

        const loaded_level = self.current_level orelse return;
        if (loaded_level.segments.len == 0) return;
        if (self.level_segment_index >= loaded_level.segments.len) {
            self.level_segment_index = loaded_level.segments.len - 1;
        }

        var path_buffer: [512]u8 = undefined;
        const archive_path = try std.fmt.bufPrint(&path_buffer, "SEGMENTS/{s}", .{loaded_level.segments[self.level_segment_index].path});
        const entry = self.catalog.dat.entryByPath(archive_path) orelse return;
        self.current_segment = try segment.loadFromArchive(self.allocator, &self.catalog, entry);
    }

    fn activeModel(self: *const AppState) ?*const x2.LoadedModel {
        if (self.current_animation) |*animation| {
            return &animation.rendered;
        }
        if (self.current_model) |*model| {
            return model;
        }
        return null;
    }

    fn activeLevelSegmentEntry(self: *const AppState) ?*const level.SegmentEntry {
        const loaded_level = self.current_level orelse return null;
        if (loaded_level.segments.len == 0 or self.level_segment_index >= loaded_level.segments.len) return null;
        return &loaded_level.segments[self.level_segment_index];
    }
};

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    const options = try parseArgs(allocator);
    try runtime_state.ensureRootExists(options.runtime_root_path);
    try std.fs.cwd().makePath(options.screenshot_dir);
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
    var frame_timer = try std.time.Timer.start();
    var runtime_timer = try std.time.Timer.start();

    if (options.command == .smoke) {
        try state.warmupSmokeTest();
    }

    rl.setTargetFPS(144);
    var frames_left: usize = if (options.command == .smoke) 3 else std.math.maxInt(usize);

    while (!rl.windowShouldClose() and !state.should_exit and frames_left > 0) {
        if (options.timeout_seconds) |timeout_seconds| {
            const timeout_ns = @as(u64, timeout_seconds) * std.time.ns_per_s;
            if (runtime_timer.read() >= timeout_ns) {
                return error.RunTimeout;
            }
        }
        const frame_delta_seconds = @as(f64, @floatFromInt(frame_timer.lap())) / @as(f64, std.time.ns_per_s);
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
        .debug, .smoke => return drawDebugUi(state, archive_path),
    }
}

fn drawGameUi(state: *const AppState) !void {
    const full_bounds: rl.Rectangle = .{
        .x = 0.0,
        .y = 0.0,
        .width = @floatFromInt(screenWidth()),
        .height = @floatFromInt(screenHeight()),
    };
    const ui_layout = app_ui.virtualLayout(full_bounds);

    if (state.game_phase == .boot) {
        if (state.current_loading_screen) |loaded_screen| {
            loaded_screen.draw(full_bounds, bootPhaseProgress(state));
        } else {
            rl.drawRectangleRec(full_bounds, .black);
        }
        return drawGameBootUi(state, ui_layout);
    }

    if (state.current_game_background) |loaded_background| {
        if (state.current_game_background_runtime) |runtime| {
            switch (state.game_phase) {
                .intro, .credits => runtime.drawStretched(&loaded_background, full_bounds),
                else => _ = runtime.draw(&loaded_background, full_bounds),
            }
        } else {
            _ = loaded_background.draw(full_bounds);
        }
    } else {
        rl.drawRectangleRec(full_bounds, .black);
    }

    switch (state.game_phase) {
        .boot => unreachable,
        .intro => drawCurrentTextScript(state, ui_layout),
        .main_menu => try drawMainMenuUi(state, ui_layout),
        .new_game_menu => try drawNewGameMenuUi(state, ui_layout),
        .options_menu => try drawOptionsMenuUi(state, ui_layout),
        .route_map_menu => try drawRouteMapMenuUi(state, ui_layout),
        .high_scores_menu => try drawHighScoresMenuUi(state, ui_layout),
        .exit_prompt => try drawExitPromptUi(state, ui_layout),
        .completion_screen => try drawCompletionScreenUi(state, ui_layout),
        .credits => drawCurrentTextScript(state, ui_layout),
        .help => drawHelpUi(state, ui_layout),
        .level => try drawGameplayLevelUi(state, ui_layout),
    }

    drawFrontendCursorOverlay(state);
    state.frontend_transition.draw(full_bounds);
}

fn drawGameBootUi(state: *const AppState, layout: VirtualLayout) !void {
    if (state.current_loading_screen != null) return;

    const font_size = layout.fontSize(30);
    const title_width = measureAppText(state, "Loading...", font_size);
    const title_point = layout.mapPoint(320.0, 240.0);
    const title_x: i32 = @intFromFloat(title_point.x);
    const title_y: i32 = @intFromFloat(title_point.y);
    drawAppText(
        state,
        "Loading...",
        title_x - @divTrunc(title_width, 2),
        title_y - layout.scaleInt(18),
        font_size,
        .ray_white,
    );
}

fn optionsFullscreenTextRect(state: *const AppState) frontend_widget.Rect {
    return frontend_widget.type20TextRect(
        &state.ui_font,
        if (state.runtime_config.fullscreenEnabled()) "Full-screen On" else "Full-screen Off",
        options_fullscreen_anchor_y,
        options_button_center_offset_x,
    );
}

fn optionsBackTextRect(state: *const AppState) frontend_widget.Rect {
    return frontend_widget.type20TextRect(&state.ui_font, "Back", options_back_anchor_y, options_button_center_offset_x);
}

fn highScoreFooterTextRect(state: *const AppState, text: []const u8, center_offset_x: f32) frontend_widget.Rect {
    return frontend_widget.widgetTextRect(&state.ui_font, .footer_button, .center, text, high_score_footer_y, center_offset_x);
}

fn exitPromptTextRect(state: *const AppState, text: []const u8, center_offset_x: f32) frontend_widget.Rect {
    return frontend_widget.widgetTextRect(&state.ui_font, .menu_button, .center, text, exit_prompt_button_y, center_offset_x);
}

fn optionsSliderPanelRect(center_y: f32) frontend_widget.Rect {
    return .{
        .left = options_slider_center_x - options_slider_panel_width * 0.5,
        .top = center_y - options_slider_panel_height * 0.5,
        .width = options_slider_panel_width,
        .height = options_slider_panel_height,
    };
}

fn optionsSliderLessRect(center_y: f32) frontend_widget.Rect {
    return .{
        .left = options_slider_center_x - options_slider_arrow_offset_x - options_slider_arrow_size * 0.5,
        .top = center_y + options_slider_arrow_center_y_offset - options_slider_arrow_size * 0.5,
        .width = options_slider_arrow_size,
        .height = options_slider_arrow_size,
    };
}

fn optionsSliderMoreRect(center_y: f32) frontend_widget.Rect {
    return .{
        .left = options_slider_center_x + options_slider_arrow_offset_x - options_slider_arrow_size * 0.5,
        .top = center_y + options_slider_arrow_center_y_offset - options_slider_arrow_size * 0.5,
        .width = options_slider_arrow_size,
        .height = options_slider_arrow_size,
    };
}

fn drawMainMenuUi(state: *const AppState, layout: VirtualLayout) !void {
    var anchor_y: f32 = 90.0;
    for (main_menu_items, 0..) |item, index| {
        const text_rect = frontend_widget.type20TextRect(&state.ui_font, item.label(), anchor_y, frontend_widget.type20_center_offset_x);
        frontend_widget.drawType20Button(
            layout,
            .{
                .border = state.frontend_widget_art.border.?.texture,
            },
            &state.ui_font,
            item.label(),
            text_rect,
            state.main_menu_button_states[index],
            false,
        );
        anchor_y = frontend_widget.stackBelow(text_rect);
    }

    if (state.game_status_message) |message| {
        try drawFrontendStatusMessage(state, layout, message);
    }
}

fn drawNewGameMenuUi(state: *const AppState, layout: VirtualLayout) !void {
    var anchor_y: f32 = 80.0;
    for (new_game_menu_items[0..4], 0..) |item, index| {
        const text_rect = frontend_widget.type20TextRect(&state.ui_font, item.label(), anchor_y, frontend_widget.type20_center_offset_x);
        frontend_widget.drawType20Button(
            layout,
            .{
                .border = state.frontend_widget_art.border.?.texture,
            },
            &state.ui_font,
            item.label(),
            text_rect,
            state.new_game_button_states[index],
            false,
        );
        anchor_y = frontend_widget.stackBelow(text_rect);
    }
    frontend_widget.drawType20Button(
        layout,
        .{
            .border = state.frontend_widget_art.border.?.texture,
        },
        &state.ui_font,
        "Help",
        frontend_widget.type20TextRect(&state.ui_font, "Help", 350.0, -220.0),
        state.new_game_button_states[4],
        false,
    );
    frontend_widget.drawType20Button(
        layout,
        .{
            .border = state.frontend_widget_art.border.?.texture,
        },
        &state.ui_font,
        "Back",
        frontend_widget.type20TextRect(&state.ui_font, "Back", 350.0, frontend_widget.type20_center_offset_x),
        state.new_game_button_states[5],
        false,
    );

    if (state.game_status_message) |message| {
        try drawFrontendStatusMessage(state, layout, message);
    }
}

fn drawOptionsMenuUi(state: *const AppState, layout: VirtualLayout) !void {
    const local_mouse = state.currentFrontendMouseLocal();
    frontend_widget.drawType20Button(
        layout,
        .{
            .border = state.frontend_widget_art.border.?.texture,
        },
        &state.ui_font,
        if (state.runtime_config.fullscreenEnabled()) "Full-screen On" else "Full-screen Off",
        optionsFullscreenTextRect(state),
        state.options_button_states[options_fullscreen_button_index],
        false,
    );
    drawFrontendSliderPanel(
        state,
        layout,
        options_slider_center_x,
        options_sound_slider_center_y,
        "Sounds Volume",
        state.runtime_config.soundVolume(),
        state.options_menu_index == 1,
        if (local_mouse) |mouse| optionsSliderLessRect(options_sound_slider_center_y).contains(mouse) else false,
        if (local_mouse) |mouse| optionsSliderMoreRect(options_sound_slider_center_y).contains(mouse) else false,
    );
    drawFrontendSliderPanel(
        state,
        layout,
        options_slider_center_x,
        options_music_slider_center_y,
        "Music Volume",
        state.runtime_config.musicVolume(),
        state.options_menu_index == 2,
        if (local_mouse) |mouse| optionsSliderLessRect(options_music_slider_center_y).contains(mouse) else false,
        if (local_mouse) |mouse| optionsSliderMoreRect(options_music_slider_center_y).contains(mouse) else false,
    );
    frontend_widget.drawType20Button(
        layout,
        .{
            .border = state.frontend_widget_art.border.?.texture,
        },
        &state.ui_font,
        "Back",
        optionsBackTextRect(state),
        state.options_button_states[options_back_button_index],
        false,
    );

    if (state.game_status_message) |message| {
        try drawFrontendStatusMessage(state, layout, message);
    }
}

fn drawRouteMapMenuUi(state: *const AppState, layout: VirtualLayout) !void {
    const mode = state.frontend_route_mode orelse return;
    const route_actions = state.activeRouteMenuActions();
    const selected_action = route_actions[@min(state.route_menu_action_index, route_actions.len - 1)];
    drawFrontendHeading(state, layout, 16.0, 18.0, "Intergalactic Delivery Route", 18, .left, .{ .r = 216, .g = 138, .b = 28, .a = 255 });
    drawRouteMapLogo(state, layout);
    const route_galaxy_name = state.currentFrontendGalaxyName() orelse frontendRouteModeLabel(mode);
    const route_level_name = if (state.frontend_route_level) |loaded_level| loaded_level.name else "Route";
    const route_body = if (state.frontend_route_level) |loaded_level|
        loaded_level.galaxy_text orelse routeMenuHint(mode, selected_action) orelse ""
    else
        routeMenuHint(mode, selected_action) orelse "";
    const primary_action = if (selected_action == .back) routeMenuActionLabel(mode, .play) else routeMenuActionLabel(mode, selected_action);
    drawRouteMapStars(state, layout, mode);
    if (galaxy.routePointForRouteIndex(state.frontend_route_index)) |route_point| {
        drawRouteMapCard(state, layout, route_point, route_galaxy_name, route_level_name, route_body, primary_action, selected_action != .back);
    }
    drawFrontendMenuButton(
        state,
        layout,
        49.0,
        420.0,
        "Back",
        selected_action == .back,
        .{ .min_width = 88.0 },
    );

    if (state.game_status_message) |message| {
        try drawFrontendNoticeBlock(state, layout, 320.0, 438.0, message, .ray_white);
    }
}

fn drawHighScoresMenuUi(state: *const AppState, layout: VirtualLayout) !void {
    const pending_entry = state.postLevelHighScoreContext();
    const selected_mode = if (pending_entry) |context|
        context.mode
    else
        high_score_screen_modes[@min(state.high_scores_menu_index, high_score_screen_modes.len - 1)];
    const art: frontend_widget.Art = .{
        .border = state.frontend_widget_art.border.?.texture,
    };
    drawFrontendHeading(
        state,
        layout,
        app_ui.authored_width * 0.5,
        high_score_title_y,
        if (pending_entry != null) "Enter Your Name Here!" else highScoreScreenTitle(selected_mode),
        23,
        .center,
        .{ .r = 216, .g = 138, .b = 28, .a = 255 },
    );

    if (pending_entry) |context| {
        var draft_buffer: [high_score.name_capacity + 1]u8 = undefined;
        const draft_name = if (state.postLevelHighScoreDraft().len == 0)
            "_"
        else
            try std.fmt.bufPrint(&draft_buffer, "{s}_", .{state.postLevelHighScoreDraft()});
        drawHighScoreTable(state, layout, context.rank, draft_name, true, selected_mode);
        frontend_widget.drawTextButton(
            layout,
            art,
            &state.ui_font,
            .footer_button,
            post_level_high_score_actions[0].label(),
            highScoreFooterTextRect(state, post_level_high_score_actions[0].label(), high_score_entry_cancel_x),
            state.post_level_high_score_button_states[0],
            false,
        );
        frontend_widget.drawTextButton(
            layout,
            art,
            &state.ui_font,
            .footer_button,
            post_level_high_score_actions[1].label(),
            highScoreFooterTextRect(state, post_level_high_score_actions[1].label(), high_score_entry_submit_x),
            state.post_level_high_score_button_states[1],
            false,
        );
    } else {
        drawHighScoreTable(state, layout, null, null, false, selected_mode);
        frontend_widget.drawTextButton(
            layout,
            art,
            &state.ui_font,
            .footer_button,
            "Back",
            highScoreFooterTextRect(state, "Back", high_score_back_x),
            state.high_score_button_states[0],
            false,
        );
        frontend_widget.drawTextButton(
            layout,
            art,
            &state.ui_font,
            .footer_button,
            highScoreTableToggleLabel(selected_mode),
            highScoreFooterTextRect(state, highScoreTableToggleLabel(selected_mode), high_score_toggle_x),
            state.high_score_button_states[1],
            false,
        );
    }

    if (state.game_status_message) |message| {
        try drawFrontendStatusMessage(state, layout, message);
    }
}

fn drawExitPromptUi(state: *const AppState, layout: VirtualLayout) !void {
    const art: frontend_widget.Art = .{
        .border = state.frontend_widget_art.border.?.texture,
    };
    drawFrontendHeading(state, layout, 320.0, exit_prompt_title_y, "Do you really want to quit?", 26, .center, .ray_white);
    frontend_widget.drawType20Button(
        layout,
        art,
        &state.ui_font,
        exit_prompt_choices[0].label(),
        exitPromptTextRect(state, exit_prompt_choices[0].label(), exit_prompt_yes_x),
        state.exit_prompt_button_states[0],
        false,
    );
    frontend_widget.drawType20Button(
        layout,
        art,
        &state.ui_font,
        exit_prompt_choices[1].label(),
        exitPromptTextRect(state, exit_prompt_choices[1].label(), exit_prompt_no_x),
        state.exit_prompt_button_states[1],
        false,
    );
}

fn drawHighScoreTable(
    state: *const AppState,
    layout: VirtualLayout,
    highlight_index: ?usize,
    editing_name: ?[]const u8,
    hide_replay: bool,
    mode: high_score.Mode,
) void {
    const entries = state.high_score_tables.visibleEntries(mode);
    const art: frontend_widget.Art = .{
        .border = state.frontend_widget_art.border.?.texture,
    };
    const row_background_text = switch (mode) {
        .postal => "                                               ",
        .challenge => "                                           ",
    };

    var visible_row: usize = 0;
    for (entries, 0..) |table_entry, entry_index| {
        if (!table_entry.isActive() and !(highlight_index != null and highlight_index.? == entry_index)) continue;

        const row_y = high_score_row_start_y + @as(f32, @floatFromInt(visible_row)) * high_score_row_pitch;
        var row_state = frontend_widget.TextButtonState{};
        row_state.snapFor(.compact_score_row, highlight_index != null and highlight_index.? == entry_index);
        frontend_widget.drawTextButton(
            layout,
            art,
            &state.ui_font,
            .compact_score_row,
            row_background_text,
            frontend_widget.widgetTextRect(&state.ui_font, .compact_score_row, .left, row_background_text, row_y, -228.0),
            row_state,
            false,
        );

        var rank_buffer: [8]u8 = undefined;
        const rank_text = std.fmt.bufPrint(&rank_buffer, "{d}", .{entry_index + 1}) catch "";
        const display_name = if (highlight_index != null and highlight_index.? == entry_index and editing_name != null)
            editing_name.?
        else
            highScoreDisplayName(&table_entry);
        drawFrontendTextAligned(state, layout, 98.0, row_y, rank_text, 18, .{ .r = 216, .g = 138, .b = 28, .a = 255 }, .left);
        drawFrontendTextAligned(state, layout, 140.0, row_y, display_name, 18, .ray_white, .left);

        var score_buffer: [32]u8 = undefined;
        const score_text = std.fmt.bufPrint(&score_buffer, "{d}", .{table_entry.score}) catch "0";
        drawFrontendTextAligned(
            state,
            layout,
            if (mode == .postal) 480.0 else 445.0,
            row_y,
            score_text,
            18,
            .{ .r = 216, .g = 138, .b = 28, .a = 255 },
            .right,
        );
        const replay_text = if (!hide_replay and table_entry.has_replay) "Replay" else "";
        if (replay_text.len != 0) {
            drawFrontendTextAligned(
                state,
                layout,
                if (mode == .postal) 490.0 else 445.0,
                row_y,
                replay_text,
                18,
                .{ .r = 216, .g = 138, .b = 28, .a = 255 },
                .center,
            );
        }

        visible_row += 1;
    }
}

fn highScoreDisplayName(entry: *const high_score.Entry) []const u8 {
    const name = entry.name();
    if (name.len == 0) return "---";
    return name;
}

fn drawFooterMessage(state: *const AppState, layout: VirtualLayout, footer_panel: rl.Rectangle, message: []const u8) !void {
    rl.drawRectangleRounded(footer_panel, 0.2, 8, .{ .r = 0, .g = 0, .b = 0, .a = 172 });
    try drawWrappedText(
        state,
        message,
        @intFromFloat(footer_panel.x + layout.scaleFloat(20.0)),
        @intFromFloat(footer_panel.y + layout.scaleFloat(11.0)),
        @intFromFloat(footer_panel.width - layout.scaleFloat(32.0)),
        layout.fontSize(20),
        .ray_white,
    );
}

const FrontendTextAlign = enum {
    left,
    center,
    right,
};

const FrontendButtonOptions = struct {
    min_width: f32 = 0.0,
    show_cursor: bool = true,
};

const FrontendButtonColors = struct {
    fill: rl.Color,
    outline: rl.Color,
    text: rl.Color,
    shadow: rl.Color,
};

fn drawFrontendTextAligned(
    state: *const AppState,
    layout: VirtualLayout,
    local_x: f32,
    local_y: f32,
    text: []const u8,
    authored_size: i32,
    color: rl.Color,
    alignment: FrontendTextAlign,
) void {
    const point = layout.mapPoint(local_x, local_y);
    const font_size = layout.fontSize(authored_size);
    const width = measureAppText(state, text, font_size);
    const draw_x = switch (alignment) {
        .left => @as(i32, @intFromFloat(point.x)),
        .center => @as(i32, @intFromFloat(point.x)) - @divTrunc(width, 2),
        .right => @as(i32, @intFromFloat(point.x)) - width,
    };
    drawAppText(state, text, draw_x, @intFromFloat(point.y), font_size, color);
}

fn frontendButtonColors(active: bool) FrontendButtonColors {
    return if (active)
        .{
            .fill = .{ .r = 184, .g = 112, .b = 214, .a = 232 },
            .outline = .{ .r = 226, .g = 194, .b = 255, .a = 255 },
            .text = .ray_white,
            .shadow = .{ .r = 74, .g = 18, .b = 84, .a = 220 },
        }
    else
        .{
            .fill = .{ .r = 96, .g = 78, .b = 152, .a = 164 },
            .outline = .{ .r = 112, .g = 96, .b = 176, .a = 112 },
            .text = .{ .r = 216, .g = 138, .b = 28, .a = 255 },
            .shadow = .{ .r = 40, .g = 16, .b = 58, .a = 220 },
        };
}

fn measureFrontendLocalTextWidth(state: *const AppState, layout: VirtualLayout, text: []const u8, authored_size: i32) f32 {
    const pixel_width = measureAppText(state, text, layout.fontSize(authored_size));
    return @as(f32, @floatFromInt(pixel_width)) / layout.scale;
}

fn drawFrontendPill(
    layout: VirtualLayout,
    center_x: f32,
    center_y: f32,
    width: f32,
    height: f32,
    fill: rl.Color,
    outline: rl.Color,
) void {
    const shadow_rect = layout.mapRect(center_x - width * 0.5, center_y - height * 0.5 + 2.0, width, height);
    const rect = layout.mapRect(center_x - width * 0.5, center_y - height * 0.5, width, height);
    rl.drawRectangleRounded(shadow_rect, 0.4, 10, .{ .r = 30, .g = 6, .b = 34, .a = 110 });
    rl.drawRectangleRounded(rect, 0.4, 10, fill);
    rl.drawRectangleRoundedLinesEx(rect, 0.4, 10, layout.scaleFloat(1.0), outline);
}

fn drawFrontendCursorRocket(state: *const AppState, layout: VirtualLayout, local_x: f32, local_y: f32) void {
    const loaded_texture = state.frontend_cursor_texture orelse return;
    const destination = layout.mapRect(
        local_x - frontend_widget.cursor_hotspot_x,
        local_y - frontend_widget.cursor_hotspot_y,
        frontend_widget.cursor_size,
        frontend_widget.cursor_size,
    );
    rl.drawTexturePro(
        loaded_texture.texture,
        .{
            .x = 0.0,
            .y = 0.0,
            .width = @as(f32, @floatFromInt(loaded_texture.texture.width)),
            .height = @as(f32, @floatFromInt(loaded_texture.texture.height)),
        },
        destination,
        .{ .x = 0.0, .y = 0.0 },
        0.0,
        .white,
    );
}

fn drawFrontendCursorOverlay(state: *const AppState) void {
    if (state.command != .game) return;
    if (!frontendPhaseShowsCursor(state.game_phase)) return;
    const layout = state.currentUiLayout();
    const local_mouse = state.currentFrontendMouseLocal() orelse return;
    drawFrontendCursorRocket(state, layout, local_mouse.x, local_mouse.y);
}

fn frontendPhaseShowsCursor(phase: GamePhase) bool {
    return switch (phase) {
        .main_menu,
        .new_game_menu,
        .options_menu,
        .route_map_menu,
        .high_scores_menu,
        .exit_prompt,
        .completion_screen,
        .help,
        => true,
        .boot, .intro, .credits, .level => false,
    };
}

fn drawFrontendHeading(
    state: *const AppState,
    layout: VirtualLayout,
    local_x: f32,
    local_y: f32,
    text: []const u8,
    authored_size: i32,
    alignment: FrontendTextAlign,
    color: rl.Color,
) void {
    drawFrontendTextAligned(state, layout, local_x + 2.0, local_y + 2.0, text, authored_size, .{ .r = 30, .g = 10, .b = 28, .a = 224 }, alignment);
    drawFrontendTextAligned(state, layout, local_x, local_y, text, authored_size, color, alignment);
}

fn drawFrontendMenuButton(
    state: *const AppState,
    layout: VirtualLayout,
    center_x: f32,
    center_y: f32,
    text: []const u8,
    active: bool,
    options: FrontendButtonOptions,
) void {
    const authored_font_size: i32 = if (active) 28 else 26;
    const horizontal_padding: f32 = if (active) 54.0 else 42.0;
    const local_width = @max(measureFrontendLocalTextWidth(state, layout, text, authored_font_size) + horizontal_padding, options.min_width);
    const local_height: f32 = if (active) 38.0 else 34.0;
    const colors = frontendButtonColors(active);
    drawFrontendPill(layout, center_x, center_y, local_width, local_height, colors.fill, colors.outline);
    drawFrontendTextAligned(state, layout, center_x + 2.0, center_y - @as(f32, if (active) 13 else 12), text, authored_font_size, colors.shadow, .center);
    drawFrontendTextAligned(state, layout, center_x, center_y - @as(f32, if (active) 15 else 14), text, authored_font_size, colors.text, .center);
}

fn drawTextureLocalRectSource(
    layout: VirtualLayout,
    loaded_texture: assets.LoadedTexture,
    source: rl.Rectangle,
    local_x: f32,
    local_y: f32,
    local_width: f32,
    local_height: f32,
    tint: rl.Color,
) void {
    if (local_width <= 0.0 or local_height <= 0.0) return;
    rl.drawTexturePro(
        loaded_texture.texture,
        source,
        layout.mapRect(local_x, local_y, local_width, local_height),
        .{ .x = 0.0, .y = 0.0 },
        0.0,
        tint,
    );
}

fn drawTextureLocalRect(
    layout: VirtualLayout,
    loaded_texture: assets.LoadedTexture,
    local_x: f32,
    local_y: f32,
    local_width: f32,
    local_height: f32,
    tint: rl.Color,
) void {
    drawTextureLocalRectSource(
        layout,
        loaded_texture,
        .{
            .x = 0.0,
            .y = 0.0,
            .width = @as(f32, @floatFromInt(loaded_texture.texture.width)),
            .height = @as(f32, @floatFromInt(loaded_texture.texture.height)),
        },
        local_x,
        local_y,
        local_width,
        local_height,
        tint,
    );
}

fn drawTextureCenteredLocal(
    layout: VirtualLayout,
    loaded_texture: assets.LoadedTexture,
    center_x: f32,
    center_y: f32,
    local_width: f32,
    local_height: f32,
    tint: rl.Color,
) void {
    drawTextureLocalRect(
        layout,
        loaded_texture,
        center_x - local_width * 0.5,
        center_y - local_height * 0.5,
        local_width,
        local_height,
        tint,
    );
}

fn drawFrontendSliderPanel(
    state: *const AppState,
    layout: VirtualLayout,
    center_x: f32,
    center_y: f32,
    label: []const u8,
    value: f32,
    active: bool,
    less_hovered: bool,
    more_hovered: bool,
) void {
    const panel_width: f32 = 418.0;
    const panel_height: f32 = 86.0;
    const colors = frontendButtonColors(active);
    const normalized_value = std.math.clamp(value, 0.0, 1.0);

    drawFrontendPill(layout, center_x, center_y, panel_width, panel_height, colors.fill, colors.outline);
    drawFrontendTextAligned(state, layout, center_x + 2.0, center_y - 29.0, label, 22, colors.shadow, .center);
    drawFrontendTextAligned(state, layout, center_x, center_y - 31.0, label, 22, colors.text, .center);

    const bar_left = center_x - 128.0;
    const bar_top = center_y - 5.0;
    const bar_width: f32 = 256.0;
    const bar_height: f32 = 32.0;

    if (state.slider_art.bar) |loaded_texture| {
        drawTextureLocalRect(layout, loaded_texture, bar_left, bar_top, bar_width, bar_height, .white);
    } else {
        const bar_rect = layout.mapRect(bar_left, bar_top, bar_width, bar_height);
        rl.drawRectangleRounded(bar_rect, 0.45, 8, .{ .r = 188, .g = 94, .b = 44, .a = 232 });
    }
    if (state.slider_art.bar_full) |loaded_texture| {
        drawTextureLocalRectSource(
            layout,
            loaded_texture,
            .{
                .x = 0.0,
                .y = 0.0,
                .width = @as(f32, @floatFromInt(loaded_texture.texture.width)) * normalized_value,
                .height = @as(f32, @floatFromInt(loaded_texture.texture.height)),
            },
            bar_left,
            bar_top,
            bar_width * normalized_value,
            bar_height,
            .white,
        );
    } else {
        rl.drawRectangleRounded(
            .{
                .x = layout.mapPoint(bar_left, bar_top).x,
                .y = layout.mapPoint(bar_left, bar_top).y,
                .width = layout.scaleFloat(bar_width * normalized_value),
                .height = layout.scaleFloat(bar_height),
            },
            0.45,
            8,
            .{ .r = 252, .g = 198, .b = 40, .a = 255 },
        );
    }

    const less_texture = if (less_hovered)
        state.slider_art.less_hover orelse state.slider_art.less
    else
        state.slider_art.less;
    const more_texture = if (more_hovered)
        state.slider_art.more_hover orelse state.slider_art.more
    else
        state.slider_art.more;
    if (less_texture) |loaded_texture| {
        drawTextureCenteredLocal(layout, loaded_texture, center_x - 172.0, center_y + 10.0, 64.0, 64.0, .white);
    }
    if (more_texture) |loaded_texture| {
        drawTextureCenteredLocal(layout, loaded_texture, center_x + 172.0, center_y + 10.0, 64.0, 64.0, .white);
    }

    var value_buffer: [16]u8 = undefined;
    const value_text = std.fmt.bufPrint(&value_buffer, "{d:.0}%", .{value * 100.0}) catch "0%";
    drawFrontendTextAligned(state, layout, center_x + 2.0, center_y + 2.0, value_text, 20, .{ .r = 42, .g = 20, .b = 34, .a = 220 }, .center);
    drawFrontendTextAligned(state, layout, center_x, center_y, value_text, 20, .ray_white, .center);
}

fn drawRouteMapConnection(
    layout: VirtualLayout,
    start_point: galaxy.Point,
    end_point: galaxy.Point,
    line_texture: ?assets.LoadedTexture,
    authored_width: f32,
    tint: rl.Color,
) void {
    const start = layout.mapPoint(start_point.x, start_point.y);
    const end = layout.mapPoint(end_point.x, end_point.y);
    const dx = end.x - start.x;
    const dy = end.y - start.y;
    const length = std.math.sqrt(dx * dx + dy * dy);
    if (length <= 0.01) return;

    if (line_texture) |loaded_texture| {
        const scaled_width = layout.scaleFloat(authored_width);
        rl.drawTexturePro(
            loaded_texture.texture,
            .{
                .x = 0.0,
                .y = 0.0,
                .width = @as(f32, @floatFromInt(loaded_texture.texture.width)),
                .height = @as(f32, @floatFromInt(loaded_texture.texture.height)),
            },
            .{
                .x = start.x,
                .y = start.y,
                .width = length,
                .height = scaled_width,
            },
            .{ .x = 0.0, .y = scaled_width * 0.5 },
            @as(f32, @floatCast(std.math.atan2(dy, dx) * 180.0 / std.math.pi)),
            tint,
        );
    } else {
        rl.drawLineEx(start, end, layout.scaleFloat(authored_width), tint);
    }
}

fn drawRouteMapStars(state: *const AppState, layout: VirtualLayout, mode: FrontendLevelMode) void {
    const available_limit = state.availableFrontendRouteLimit(mode);
    const selected_galaxy_index = if (state.galaxy_names) |names|
        names.galaxyIndexForRouteIndex(state.frontend_route_index)
    else
        null;

    for (0..galaxy.map_galaxy_count) |galaxy_index| {
        const center = galaxy.galaxyCenter(galaxy_index);
        if (state.route_map_art.galaxies[galaxy_index]) |loaded_texture| {
            drawTextureCenteredLocal(layout, loaded_texture, center.x, center.y, 176.0, 176.0, .white);
        }
    }

    if (state.galaxy_names) |names| {
        if (selected_galaxy_index) |galaxy_index| {
            var route_cursor: usize = 0;
            for (0..galaxy_index) |prior_index| {
                route_cursor += names.starCountForGalaxyIndex(prior_index) orelse 0;
            }
            const star_count = names.starCountForGalaxyIndex(galaxy_index) orelse 0;

            if (star_count >= 2) {
                for (0..star_count - 1) |local_index| {
                    const start_index = route_cursor + local_index;
                    const end_index = start_index + 1;
                    const unlocked = end_index + 1 <= available_limit;
                    drawRouteMapConnection(
                        layout,
                        galaxy.routePoint(start_index),
                        galaxy.routePoint(end_index),
                        state.route_map_art.line,
                        6.0,
                        if (unlocked)
                            .white
                        else
                            .{ .r = 255, .g = 255, .b = 255, .a = 88 },
                    );
                }
            }

            for (0..star_count) |local_index| {
                const route_index = route_cursor + local_index;
                const point = galaxy.routePoint(route_index);
                const unlocked = route_index + 1 <= available_limit;
                const star_tint: rl.Color = if (unlocked)
                    .white
                else
                    .{ .r = 255, .g = 255, .b = 255, .a = 88 };
                if (state.route_map_art.level_star) |loaded_texture| {
                    drawTextureCenteredLocal(layout, loaded_texture, point.x, point.y, 32.0, 32.0, star_tint);
                }
            }
        }
    }

    if (galaxy.routePointForRouteIndex(state.frontend_route_index)) |selected_point| {
        if (state.route_map_art.level_select) |loaded_texture| {
            drawTextureCenteredLocal(layout, loaded_texture, selected_point.x, selected_point.y, 64.0, 64.0, .white);
        }
    }
}

fn drawRouteMapCard(
    state: *const AppState,
    layout: VirtualLayout,
    route_point: galaxy.Point,
    route_galaxy_name: []const u8,
    route_level_name: []const u8,
    route_body: []const u8,
    primary_action: []const u8,
    primary_active: bool,
) void {
    const card_width: f32 = 218.0;
    const card_height: f32 = 188.0;
    var card_left = route_point.x + 60.0;
    var card_top = route_point.y - 130.0;
    if (card_left + card_width > 630.0) {
        card_left = route_point.x - card_width - 28.0;
    }
    if (card_top < 50.0) {
        card_top = 50.0;
    } else if (card_top + card_height > 450.0) {
        card_top = 450.0 - card_height;
    }

    const pointer_anchor_x = if (card_left > route_point.x) card_left else card_left + card_width;
    const pointer_anchor_y = std.math.clamp(route_point.y, card_top + 28.0, card_top + card_height - 28.0);
    drawRouteMapConnection(layout, route_point, .{ .x = pointer_anchor_x, .y = pointer_anchor_y }, state.route_map_art.line_star, 6.0, .white);

    if (state.route_map_art.border) |loaded_texture| {
        drawTextureLocalRect(layout, loaded_texture, card_left, card_top, card_width, card_height, .white);
    } else {
        const card = layout.mapRect(card_left, card_top, card_width, card_height);
        rl.drawRectangleRounded(card, 0.16, 10, .{ .r = 18, .g = 16, .b = 118, .a = 188 });
        rl.drawRectangleRoundedLinesEx(card, 0.16, 10, layout.scaleFloat(2.0), .{ .r = 76, .g = 210, .b = 255, .a = 255 });
    }

    drawFrontendTextAligned(state, layout, card_left + 16.0, card_top + 14.0, route_galaxy_name, 16, .ray_white, .left);
    drawFrontendTextAligned(state, layout, card_left + 16.0, card_top + 44.0, route_level_name, 20, .ray_white, .left);
    drawWrappedText(
        state,
        route_body,
        @intFromFloat(layout.mapPoint(card_left + 16.0, card_top + 76.0).x),
        @intFromFloat(layout.mapPoint(card_left + 16.0, card_top + 76.0).y),
        @intFromFloat(layout.scaleFloat(card_width - 32.0)),
        layout.fontSize(20),
        .ray_white,
    ) catch {};
    drawFrontendMenuButton(state, layout, card_left + card_width * 0.5, card_top + 156.0, primary_action, primary_active, .{ .min_width = 132.0, .show_cursor = primary_active });
}

fn drawRouteMapLogo(state: *const AppState, layout: VirtualLayout) void {
    const loaded_texture = state.route_map_art.logo orelse return;
    drawTextureLocalRect(layout, loaded_texture, 370.0, 10.0, 251.0, 82.0, .white);
}

fn drawFrontendStatusMessage(state: *const AppState, layout: VirtualLayout, message: []const u8) !void {
    try drawFrontendNoticeBlock(state, layout, app_ui.authored_width * 0.5, 438.0, message, .ray_white);
}

fn drawFrontendNoticeBlock(
    state: *const AppState,
    layout: VirtualLayout,
    center_x: f32,
    local_y: f32,
    message: []const u8,
    color: rl.Color,
) !void {
    var line_buffer: [512]u8 = undefined;
    var line_index: i32 = 0;
    var parts = std.mem.tokenizeAny(u8, message, ">\n");
    while (parts.next()) |part| {
        const trimmed = std.mem.trim(u8, part, " \t\r");
        if (trimmed.len == 0) continue;
        const clipped = if (trimmed.len > line_buffer.len - 1) trimmed[0 .. line_buffer.len - 1] else trimmed;
        @memcpy(line_buffer[0..clipped.len], clipped);
        line_buffer[clipped.len] = 0;
        drawFrontendTextAligned(
            state,
            layout,
            center_x,
            local_y + @as(f32, @floatFromInt(line_index * 20)),
            line_buffer[0..clipped.len],
            20,
            color,
            .center,
        );
        line_index += 1;
    }
}

fn highScoreScreenTitle(mode: high_score.Mode) []const u8 {
    return switch (mode) {
        .postal => "Postal High Scores",
        .challenge => "Challenge High Scores",
    };
}

fn highScoreTableToggleLabel(mode: high_score.Mode) []const u8 {
    return switch (mode) {
        .postal => "Challenge Scores",
        .challenge => "Postal Scores",
    };
}

fn resultReturnTargetForOutcome(outcome: RunOutcome, mode: ?FrontendLevelMode) ResultReturnTarget {
    if (outcome == .failed) return .main_menu;
    return switch (mode orelse .tutorial) {
        .postal => .postal_route_map,
        .time_trial => .time_trial_route_map,
        .challenge => .replay_current_level,
        .tutorial => .main_menu,
    };
}

fn runnerSessionModeForFrontendMode(mode: ?FrontendLevelMode) gameplay.SessionMode {
    return switch (mode orelse .tutorial) {
        .postal => .postal,
        .time_trial => .time_trial,
        .challenge => .challenge,
        .tutorial => .tutorial,
    };
}

fn completionBonusAppliesForMode(mode: ?FrontendLevelMode) bool {
    return switch (mode orelse .tutorial) {
        .postal => true,
        .challenge, .time_trial, .tutorial => false,
    };
}

fn completionActionLabel(result: PendingRunResult, action: CompletionAction) []const u8 {
    return switch (action) {
        .continue_flow => "Continue",
        .replay_level => if (result.outcome == .failed) "Retry" else "Replay",
    };
}

fn completionElapsedMillis(runner: gameplay.Runner) u32 {
    return runner.stopwatch.elapsedMillis();
}

fn formatElapsedMillis(buffer: []u8, elapsed_millis: u32) ![]const u8 {
    const total_seconds = @divTrunc(elapsed_millis, 1000);
    const minutes = @divTrunc(total_seconds, 60);
    const seconds = @mod(total_seconds, 60);
    const centiseconds = @divTrunc(@mod(elapsed_millis, 1000), 10);
    return std.fmt.bufPrint(buffer, "{d:0>2}:{d:0>2}.{d:0>2}", .{ minutes, seconds, centiseconds });
}

// PORT(partial): this now follows the recovered `cRSubGoldy::ScoreAdd` constants for the
// score events the current runner actually models:
// ring collect (+100), parcel pickup/register (+100 each), and the postal-only completion bonus,
// and health pickup (+250).
// Slug kills (+500), garbage-side score events (+10), jetpack/speed-up scoring, and the rest
// of the original `cRSubGoldy::AI()` path remain unported.
fn bootPhaseProgress(state: *const AppState) f32 {
    if (boot_tasks.len == 0) return 1.0;
    return std.math.clamp(
        @as(f32, @floatFromInt(state.boot_task_index)) / @as(f32, @floatFromInt(boot_tasks.len)),
        0.0,
        1.0,
    );
}

fn drawCurrentTextScript(state: *const AppState, layout: VirtualLayout) void {
    const script = state.currentTextScript() orelse return;
    const progress = state.currentTextScriptProgress() orelse 0.0;
    script.drawCrawl(&state.ui_font, progress, .{
        .x = layout.x,
        .y = layout.y,
        .width = layout.width,
        .height = layout.height,
    });
}

fn drawHelpUi(state: *const AppState, layout: VirtualLayout) void {
    drawFrontendMenuButton(state, layout, 320.0, 420.0, "Back", true, .{ .min_width = 92.0 });
}

fn resultTitle(result: PendingRunResult) []const u8 {
    return switch (result.outcome) {
        .completed => if (result.mode) |mode|
            switch (mode) {
                .postal => "Delivery Complete",
                .time_trial => "Route Complete",
                .challenge => "Challenge Complete",
                .tutorial => "Tutorial Complete",
            }
        else
            "Level Complete",
        .failed => if (result.mode) |mode|
            switch (mode) {
                .postal => "Game Over",
                .time_trial => "Route Failed",
                .challenge => "Challenge Failed",
                .tutorial => "Tutorial Failed",
            }
        else
            "Run Failed",
    };
}

fn drawGameplayLevelUi(state: *const AppState, layout: VirtualLayout) !void {
    drawGameplayLevelViewport(state);

    const hud_panel = layout.mapRect(16.0, 14.0, 608.0, 84.0);
    const footer_panel = layout.mapRect(16.0, 392.0, 608.0, 72.0);

    rl.drawRectangleRounded(hud_panel, 0.08, 8, .{ .r = 0, .g = 0, .b = 0, .a = 176 });

    const loaded_level = state.current_level orelse return;
    const loaded_track_preview = state.current_track_preview orelse return;
    const title_point = layout.mapPoint(36.0, 28.0);
    const meta_point = layout.mapPoint(36.0, 58.0);
    const control_point = layout.mapPoint(36.0, 82.0);
    const parcel_target = loaded_level.parcels orelse 0;
    const parcel_count = if (state.level_runner) |runner| runner.counters.parcels else 0;
    const score_total = if (state.level_runner) |runner| runner.score.total else 0;
    const elapsed_millis = if (state.level_runner) |runner| runner.stopwatch.elapsedMillis() else 0;
    const accepts_input = if (state.level_runner) |runner| runner.acceptsGameplayInput() else false;
    const package_icon = game_font.IconGlyph.package.byte();
    const mouse_icon = game_font.IconGlyph.mouse.byte();
    const title_font_size = layout.fontSize(28);
    const body_font_size = layout.fontSize(18);

    var level_name_buffer: [128]u8 = undefined;
    const level_name_text = try std.fmt.bufPrintZ(&level_name_buffer, "{s}", .{loaded_level.name});
    drawAppText(state, level_name_text, @intFromFloat(title_point.x), @intFromFloat(title_point.y), title_font_size, .gold);

    var elapsed_buffer: [32]u8 = undefined;
    const elapsed_text = try formatElapsedMillis(&elapsed_buffer, elapsed_millis);
    var meta_buffer: [384]u8 = undefined;
    const meta_text = try std.fmt.bufPrintZ(
        &meta_buffer,
        "Mode {s}  background {s}  segment {d}/{d}  {c} {d}/{d}  score {d}  time {s}  rows {d}",
        .{
            loaded_level.mode,
            loaded_level.background orelse "<none>",
            if (state.active_level_segment_index) |segment_index| segment_index + 1 else 1,
            loaded_level.segments.len,
            package_icon,
            parcel_count,
            parcel_target,
            score_total,
            elapsed_text,
            loaded_track_preview.total_rows,
        },
    );
    drawAppText(state, meta_text, @intFromFloat(meta_point.x), @intFromFloat(meta_point.y), body_font_size, .ray_white);
    var control_buffer: [192]u8 = undefined;
    const control_text = if (!accepts_input)
        try std.fmt.bufPrintZ(&control_buffer, "Runner cutscene active  R reset  Esc menu", .{})
    else
        try std.fmt.bufPrintZ(&control_buffer, "{c}/Left/Right steer  Up/Down speed  Space pause  R reset  Esc menu", .{mouse_icon});
    drawAppText(state, control_text, @intFromFloat(control_point.x), @intFromFloat(control_point.y), body_font_size, .light_gray);

    if (state.level_runner) |runner| {
        drawGameplayStatusWidgets(state, layout, runner);
        rl.drawRectangleRounded(footer_panel, 0.2, 8, .{ .r = 0, .g = 0, .b = 0, .a = 172 });

        var runner_buffer: [384]u8 = undefined;
        const runner_text = try std.fmt.bufPrintZ(
            &runner_buffer,
            "Row {d:.2}/{d}  cursor {d}+{d:.2}  lane {d}->{d}  speed {d:.1}  event {s}  damage {d:.2}  warn {s}  lives {d}  jet {s}  phase {s}",
            .{
                runner.row_position,
                loaded_track_preview.total_rows,
                runner.runtime_track_index,
                runner.movement_progress,
                runner.lane_index,
                runner.resolved_lane_index,
                runner.speed_rows_per_second,
                runner.recentEventLabel(),
                runner.damage_gauge,
                runner.damageWarningLabel(),
                runner.visible_life_stock,
                if (runner.jetpack_active) "on" else "off",
                runner.phaseLabel(),
            },
        );
        drawAppText(state, runner_text, @intFromFloat(footer_panel.x + layout.scaleFloat(18.0)), @intFromFloat(footer_panel.y + layout.scaleFloat(18.0)), body_font_size, .ray_white);

        if (state.level_prompt_queue.active()) |prompt| {
            try drawWrappedText(
                state,
                prompt.message,
                @intFromFloat(footer_panel.x + layout.scaleFloat(18.0)),
                @intFromFloat(footer_panel.y + layout.scaleFloat(42.0)),
                @intFromFloat(footer_panel.width - layout.scaleFloat(30.0)),
                body_font_size,
                .gold,
            );
        }
    }

    const crosshair_color: rl.Color = .{ .r = 255, .g = 255, .b = 255, .a = 180 };
    const crosshair_radius = layout.scaleInt(12);
    const crosshair_thickness = @max(layout.scaleInt(2), 1);
    rl.drawRectangle(@divTrunc(screenWidth(), 2) - crosshair_radius, @divTrunc(screenHeight(), 2), crosshair_radius * 2, crosshair_thickness, crosshair_color);
    rl.drawRectangle(@divTrunc(screenWidth(), 2), @divTrunc(screenHeight(), 2) - crosshair_radius, crosshair_thickness, crosshair_radius * 2, crosshair_color);
}

fn drawGameplayStatusWidgets(state: *const AppState, layout: VirtualLayout, runner: gameplay.Runner) void {
    drawDamageGaugeWidget(state, layout, runner);
    if (runner.session_mode == .postal) {
        drawVisibleLifeStrip(state, layout, runner.visible_life_stock);
    }
}

fn drawDamageGaugeWidget(state: *const AppState, layout: VirtualLayout, runner: gameplay.Runner) void {
    const panel = layout.mapRect(586.0, 108.0, 28.0, 224.0);
    const fill_margin = layout.scaleFloat(4.0);
    const fill_height = @max(panel.height - fill_margin * 2.0, 0.0);
    const fill_width = @max(panel.width - fill_margin * 2.0, 0.0);
    const fill_ratio = std.math.clamp(runner.damage_gauge, 0.0, 1.0);
    const active_fill_height = fill_height * fill_ratio;
    const pulse = if (runner.damage_warning_state == .idle)
        @as(f32, 0.0)
    else
        (@sin(@as(f32, @floatCast(state.render_time_seconds * 8.0))) + 1.0) * 0.5;
    const outline_alpha: u8 = @intFromFloat(160.0 + 64.0 * pulse);
    const label_y: i32 = @intFromFloat(panel.y - layout.scaleFloat(20.0));
    const fill_color = damageGaugeColor(fill_ratio, runner.damage_warning_state, pulse);

    drawAppText(state, "Damage", @intFromFloat(panel.x - layout.scaleFloat(2.0)), label_y, layout.fontSize(16), .light_gray);
    rl.drawRectangleRounded(panel, 0.18, 8, .{ .r = 0, .g = 0, .b = 0, .a = 176 });

    const inner = rl.Rectangle{
        .x = panel.x + fill_margin,
        .y = panel.y + fill_margin,
        .width = fill_width,
        .height = fill_height,
    };
    rl.drawRectangleRounded(inner, 0.12, 6, .{ .r = 255, .g = 255, .b = 255, .a = 20 });

    if (active_fill_height > 0.0) {
        const fill_rect = rl.Rectangle{
            .x = inner.x,
            .y = inner.y + (fill_height - active_fill_height),
            .width = fill_width,
            .height = active_fill_height,
        };
        rl.drawRectangleRounded(fill_rect, 0.12, 6, fill_color);
    }

    rl.drawRectangleRoundedLinesEx(
        panel,
        0.18,
        8,
        layout.scaleFloat(2.0),
        .{ .r = 255, .g = 255, .b = 255, .a = outline_alpha },
    );
}

fn drawVisibleLifeStrip(state: *const AppState, layout: VirtualLayout, visible_life_stock: u32) void {
    const panel = layout.mapRect(448.0, 26.0, 158.0, 28.0);
    const slot_width = layout.scaleFloat(12.0);
    const slot_height = layout.scaleFloat(14.0);
    const gap = layout.scaleFloat(4.0);
    const start_x = panel.x + layout.scaleFloat(38.0);
    const slot_y = panel.y + layout.scaleFloat(7.0);

    drawAppText(state, "Lives", @intFromFloat(panel.x), @intFromFloat(panel.y + layout.scaleFloat(5.0)), layout.fontSize(16), .light_gray);

    for (0..9) |slot_index| {
        const filled = slot_index < visible_life_stock;
        const rect = rl.Rectangle{
            .x = start_x + (@as(f32, @floatFromInt(slot_index)) * (slot_width + gap)),
            .y = slot_y,
            .width = slot_width,
            .height = slot_height,
        };
        rl.drawRectangleRounded(
            rect,
            0.22,
            6,
            if (filled)
                .{ .r = 248, .g = 196, .b = 82, .a = 232 }
            else
                .{ .r = 255, .g = 255, .b = 255, .a = 24 },
        );
        rl.drawRectangleRoundedLinesEx(
            rect,
            0.22,
            6,
            layout.scaleFloat(1.0),
            if (filled)
                .{ .r = 255, .g = 234, .b = 172, .a = 255 }
            else
                .{ .r = 255, .g = 255, .b = 255, .a = 96 },
        );
    }
}

fn damageGaugeColor(fill_ratio: f32, warning_state: gameplay.DamageWarningState, pulse: f32) rl.Color {
    if (warning_state != .idle) {
        const green: u8 = @intFromFloat(160.0 + 72.0 * pulse);
        return .{ .r = 255, .g = green, .b = 88, .a = 232 };
    }
    if (fill_ratio >= 0.75) {
        return .{ .r = 232, .g = 78, .b = 72, .a = 224 };
    }
    if (fill_ratio >= 0.35) {
        return .{ .r = 244, .g = 170, .b = 64, .a = 216 };
    }
    return .{ .r = 94, .g = 204, .b = 122, .a = 208 };
}

fn drawCompletionScreenUi(state: *const AppState, layout: VirtualLayout) !void {
    drawGameplayLevelViewport(state);
    const result = state.pending_run_result orelse return;
    try drawCompletionSummaryPanel(state, layout, result);
}

fn drawCompletionSummaryPanel(state: *const AppState, layout: VirtualLayout, result: PendingRunResult) !void {
    const overlay_panel = layout.mapRect(120.0, 132.0, 400.0, 204.0);
    const title_point = layout.mapPoint(144.0, 156.0);
    const body_point = layout.mapPoint(144.0, 196.0);
    const footer_point = layout.mapPoint(144.0, 306.0);
    const title_x: i32 = @intFromFloat(title_point.x);
    const title_y: i32 = @intFromFloat(title_point.y);
    const body_x: i32 = @intFromFloat(body_point.x);
    const body_y: i32 = @intFromFloat(body_point.y);
    const footer_x: i32 = @intFromFloat(footer_point.x);
    const footer_y: i32 = @intFromFloat(footer_point.y);
    const title = resultTitle(result);
    var elapsed_buffer: [32]u8 = undefined;
    const elapsed_text = try formatElapsedMillis(&elapsed_buffer, result.elapsed_millis);

    rl.drawRectangleRounded(overlay_panel, 0.08, 8, .{ .r = 0, .g = 0, .b = 0, .a = 214 });
    drawAppText(state, title, title_x, title_y, layout.fontSize(28), .gold);

    var summary_buffer: [256]u8 = undefined;
    const summary_text = try std.fmt.bufPrint(
        &summary_buffer,
        "{s}>Time {s}>Packages {d}/{d}",
        .{
            if (result.outcome == .completed) result.level_name else "Run ended before route completion",
            elapsed_text,
            result.parcel_count,
            result.parcel_target,
        },
    );
    try drawWrappedText(
        state,
        summary_text,
        body_x,
        body_y,
        layout.scaleInt(332),
        layout.fontSize(20),
        .ray_white,
    );

    const score_y = body_y + layout.scaleInt(70);
    if (result.mode == .time_trial) {
        var time_buffer: [128]u8 = undefined;
        const time_text = try std.fmt.bufPrint(&time_buffer, "Route time {s}", .{elapsed_text});
        drawAppText(state, time_text, body_x, score_y, layout.fontSize(18), .sky_blue);
    } else {
        var score_buffer: [128]u8 = undefined;
        const score_text = try std.fmt.bufPrint(&score_buffer, "Score {d}{s}", .{
            result.score,
            if (result.score_is_partial) " (partial)" else "",
        });
        drawAppText(state, score_text, body_x, score_y, layout.fontSize(18), .sky_blue);

        var breakdown_buffer: [224]u8 = undefined;
        const breakdown_text = try std.fmt.bufPrint(
            &breakdown_buffer,
            "Rings {d}  Garbage {d}  Health {d}  Pickup {d}  Register {d}  Bonus {d}  Lives {d}  Damage {d:.2}",
            .{
                result.score_totals.ring_collect,
                result.score_totals.garbage_collision,
                result.score_totals.health_collect,
                result.score_totals.parcel_pickup,
                result.score_totals.parcel_register,
                result.score_totals.completion_bonus,
                result.visible_life_stock,
                result.damage_gauge,
            },
        );
        try drawWrappedText(
            state,
            breakdown_text,
            body_x,
            score_y + layout.scaleInt(22),
            layout.scaleInt(332),
            layout.fontSize(16),
            .light_gray,
        );
    }

    if (result.unlocked_next_route) {
        drawAppText(state, "Unlocked the next delivery route.", body_x, score_y + layout.scaleInt(24), layout.fontSize(18), .gold);
    } else if (result.time_trial_record_improved) {
        drawAppText(state, "Saved a new best route time.", body_x, score_y + layout.scaleInt(24), layout.fontSize(18), .gold);
    } else if (result.high_score_rank) |rank| {
        var rank_buffer: [96]u8 = undefined;
        const rank_text = try std.fmt.bufPrint(&rank_buffer, "New high score rank: {d}", .{rank + 1});
        drawAppText(state, rank_text, body_x, score_y + layout.scaleInt(24), layout.fontSize(18), .gold);
    }

    const continue_text = if (result.high_score_mode != null and result.high_score_rank != null)
        "Continue opens high scores"
    else switch (result.return_target) {
        .postal_route_map, .time_trial_route_map => "Continue returns to the route map",
        .replay_current_level => "Continue follows the current challenge return path",
        .main_menu => "Continue returns to the main menu",
    };
    drawAppText(state, continue_text, footer_x, footer_y - layout.scaleInt(18), layout.fontSize(16), .light_gray);
    drawActionButtons(
        state,
        layout,
        @intFromFloat(overlay_panel.x + overlay_panel.width * 0.5),
        footer_y,
        &[_][]const u8{
            completionActionLabel(result, completion_actions[0]),
            completionActionLabel(result, completion_actions[1]),
        },
        state.completion_action_index,
    );
}

fn drawActionButtons(
    state: *const AppState,
    layout: VirtualLayout,
    center_x: i32,
    top_y: i32,
    labels: []const []const u8,
    selected_index: usize,
) void {
    if (labels.len == 0) return;

    const button_width = layout.scaleInt(112);
    const button_height = layout.scaleInt(28);
    const gap = layout.scaleInt(12);
    const total_width = @as(i32, @intCast(labels.len)) * button_width + @as(i32, @intCast(labels.len - 1)) * gap;
    var button_x = center_x - @divTrunc(total_width, 2);

    for (labels, 0..) |label, index| {
        const active = index == selected_index;
        const rect = rl.Rectangle{
            .x = @floatFromInt(button_x),
            .y = @floatFromInt(top_y),
            .width = @floatFromInt(button_width),
            .height = @floatFromInt(button_height),
        };
        rl.drawRectangleRounded(
            rect,
            0.25,
            8,
            if (active)
                .orange
            else
                .{ .r = 255, .g = 255, .b = 255, .a = 24 },
        );
        const font_size = layout.fontSize(18);
        const label_width = measureAppText(state, label, font_size);
        drawAppText(
            state,
            label,
            button_x + @divTrunc(button_width - label_width, 2),
            top_y + @divTrunc(button_height - font_size, 2) - 1,
            font_size,
            if (active) .black else .ray_white,
        );
        button_x += button_width + gap;
    }
}

// PORT(debug): this browser is intentionally a tooling surface, not the shipping game path.
fn drawDebugUi(state: *const AppState, archive_path: []const u8) !void {
    if (state.mode == .models) {
        drawModelViewport(state);
    } else if (state.mode == .objects) {
        drawObjectViewport(state);
    } else if (state.mode == .levels) {
        drawLevelViewport(state);
    }

    drawAppText(state, "snail debug browser", 32, 24, 30, .ray_white);
    drawAppText(state, "1 textures  2 audio  3 x2  4 objects  5 levels  tab switch", 32, 62, 18, .light_gray);
    drawAppText(state, "arrows: browse current mode  levels up/down segment a/d lane w/s speed space pause r reset", 32, 84, 18, .light_gray);

    var archive_buffer: [512]u8 = undefined;
    const archive_text = try std.fmt.bufPrintZ(&archive_buffer, "Archive: {s}", .{archive_path});
    drawAppText(state, archive_text, 32, 110, 18, .dark_gray);
    var runtime_buffer: [512]u8 = undefined;
    const runtime_text = try std.fmt.bufPrintZ(&runtime_buffer, "Runtime: {s}", .{state.runtime_root_path});
    drawAppText(state, runtime_text, 32, 132, 18, .dark_gray);

    drawModeBadge(state, .textures, state.mode, "Textures", 32, 156);
    drawModeBadge(state, .audio, state.mode, "Audio", 156, 156);
    drawModeBadge(state, .models, state.mode, "X2", 280, 156);
    drawModeBadge(state, .objects, state.mode, "Objects", 404, 156);
    drawModeBadge(state, .levels, state.mode, "Levels", 528, 156);

    switch (state.mode) {
        .textures => drawTexturePanel(state),
        .audio => try drawAudioPanel(state),
        .models => try drawModelPanel(state),
        .objects => try drawObjectPanel(state),
        .levels => try drawLevelPanel(state),
    }
}

fn drawModeBadge(state: *const AppState, mode: Mode, active_mode: Mode, text: [:0]const u8, x: i32, y: i32) void {
    const color: rl.Color = if (mode == active_mode) .orange else .dark_gray;
    rl.drawRectangleRounded(.{ .x = @floatFromInt(x), .y = @floatFromInt(y), .width = 104, .height = 34 }, 0.22, 8, color);
    drawAppText(state, text, x + 20, y + 8, 18, .ray_white);
}

fn drawTexturePanel(state: *const AppState) void {
    const current = state.current_texture orelse return;
    const entry = state.catalog.texture_entries[state.texture_index];

    var summary_buffer: [256]u8 = undefined;
    const summary_text = std.fmt.bufPrintZ(
        &summary_buffer,
        "Texture {d}/{d}  {d}x{d}",
        .{
            state.texture_index + 1,
            state.catalog.texture_entries.len,
            current.texture.width,
            current.texture.height,
        },
    ) catch "Texture";
    drawAppText(state, summary_text, 32, 194, 24, .ray_white);

    var path_buffer: [512]u8 = undefined;
    const path_text = std.fmt.bufPrintZ(&path_buffer, "{s}", .{entry.path}) catch "";
    drawAppText(state, path_text, 32, 226, 18, .light_gray);

    const max_width = 860.0;
    const max_height = 430.0;
    const scale_x = max_width / @as(f32, @floatFromInt(current.texture.width));
    const scale_y = max_height / @as(f32, @floatFromInt(current.texture.height));
    const scale = @min(scale_x, scale_y);
    const draw_width = @as(f32, @floatFromInt(current.texture.width)) * scale;
    const draw_height = @as(f32, @floatFromInt(current.texture.height)) * scale;
    const draw_x = (@as(f32, @floatFromInt(screenWidth())) - draw_width) / 2.0;
    const draw_y = 280.0 + (max_height - draw_height) / 2.0;

    rl.drawRectangleLines(200, 268, 880, 454, .dark_gray);
    rl.drawTextureEx(current.texture, .{ .x = draw_x, .y = draw_y }, 0.0, scale, .white);
}

fn drawAudioPanel(state: *const AppState) !void {
    const entry = state.catalog.audio_entries[state.audio_index];

    var summary_buffer: [256]u8 = undefined;
    const summary_text = try std.fmt.bufPrintZ(
        &summary_buffer,
        "Audio {d}/{d}",
        .{ state.audio_index + 1, state.catalog.audio_entries.len },
    );
    drawAppText(state, summary_text, 32, 194, 24, .ray_white);

    var path_buffer: [512]u8 = undefined;
    const path_text = try std.fmt.bufPrintZ(&path_buffer, "{s}", .{entry.path});
    drawAppText(state, path_text, 32, 226, 18, .light_gray);

    const status_text: [:0]const u8 = blk: {
        if (!state.audio_ready) break :blk "Audio device unavailable";
        if (state.current_music != null) break :blk "Playing as music stream";
        if (state.current_sound) |sound| {
            if (rl.isSoundPlaying(sound.sound)) break :blk "Playing as one-shot sound";
        }
        break :blk "Stopped";
    };
    drawAppText(state, status_text, 32, 260, 22, .sky_blue);

    rl.drawRectangleRounded(.{ .x = 32, .y = 308, .width = 1216, .height = 380 }, 0.03, 8, .dark_blue);
    drawAppText(state, "Audio preview stays archive-backed: OGG bytes are decoded from SnailMail.dat in memory.", 56, 338, 24, .ray_white);
    drawAppText(state, "Space loads the current OGG as a sound effect and plays it once.", 56, 384, 22, .light_gray);
    drawAppText(state, "Enter loads the same OGG as a music stream and keeps updating it each frame.", 56, 420, 22, .light_gray);
    drawAppText(state, "This lets us exercise both playback paths before game logic exists.", 56, 456, 22, .light_gray);
}

fn drawModelPanel(state: *const AppState) !void {
    const entry = state.catalog.model_entries[state.model_index];
    const model = state.activeModel() orelse return;
    const parsed = &model.parsed;

    var summary_buffer: [256]u8 = undefined;
    const summary_text = try std.fmt.bufPrintZ(
        &summary_buffer,
        "X2 {d}/{d}  submeshes {d}  vertices {d}  faces {d}  triangles {d}",
        .{
            state.model_index + 1,
            state.catalog.model_entries.len,
            model.submeshes.len,
            parsed.vertices.len,
            parsed.faces.len,
            parsed.total_triangle_count,
        },
    );
    drawAppText(state, summary_text, 32, 194, 24, .ray_white);

    var path_buffer: [512]u8 = undefined;
    const path_text = try std.fmt.bufPrintZ(&path_buffer, "{s}", .{entry.path});
    drawAppText(state, path_text, 32, 226, 18, .light_gray);

    var detail_buffer: [256]u8 = undefined;
    const detail_text = try std.fmt.bufPrintZ(
        &detail_buffer,
        "frame {s}  mesh {s}  materials {d}  flipV {s}",
        .{
            parsed.frame_name,
            parsed.mesh_name,
            parsed.materials.len,
            if (state.model_flip_v) "on" else "off",
        },
    );
    drawAppText(state, detail_text, 32, 258, 20, .sky_blue);

    rl.drawRectangleRounded(.{ .x = 32, .y = 304, .width = 460, .height = 332 }, 0.03, 8, .dark_blue);
    drawAppText(state, "RWG loader notes", 56, 332, 26, .ray_white);

    var mesh_buffer: [384]u8 = undefined;
    const mesh_text = try std.fmt.bufPrintZ(&mesh_buffer, "Bounds center: {d:.2}, {d:.2}, {d:.2}", .{ model.center.x, model.center.y, model.center.z });
    drawAppText(state, mesh_text, 56, 378, 20, .light_gray);

    var material_buffer: [384]u8 = undefined;
    const material_text = try std.fmt.bufPrintZ(&material_buffer, "Preview radius: {d:.2}", .{model.radius});
    drawAppText(state, material_text, 56, 410, 20, .light_gray);

    var texture_buffer: [384]u8 = undefined;
    const texture_text = try std.fmt.bufPrintZ(
        &texture_buffer,
        "First texture: {s}",
        .{if (model.submeshes.len > 0 and model.submeshes[0].archive_texture_path != null) model.submeshes[0].archive_texture_path.? else "<none>"},
    );
    drawAppText(state, texture_text, 56, 442, 20, .light_gray);

    if (state.current_animation) |animation| {
        var anim_buffer: [384]u8 = undefined;
        const anim_text = try std.fmt.bufPrintZ(
            &anim_buffer,
            "Anim: {s}  mode {s}  sample {d:.2}  paused {s}",
            .{
                animation.clip.name,
                modeLabel(animation.clip.mode),
                animation.current_sample_number,
                if (animation.paused) "yes" else "no",
            },
        );
        drawAppText(state, anim_text, 56, 486, 20, .gold);

        var trigger_buffer: [384]u8 = undefined;
        const trigger_text = try std.fmt.bufPrintZ(
            &trigger_buffer,
            "Trigger steps {d}  first {s}  last {s}",
            .{
                animation.clip.trigger_steps.len,
                animation.clip.trigger_steps[0],
                animation.clip.trigger_steps[animation.clip.trigger_steps.len - 1],
            },
        );
        drawAppText(state, trigger_text, 56, 520, 20, .light_gray);
        drawAppText(state, "Binary Ninja + Ghidra + IDA agree the runtime interpolates numbered keyframes.", 56, 550, 20, .light_gray);
        drawAppText(state, "Duration and Mode come from X/_ANIMATION.TXT; frame numbers come from .x2 filenames.", 56, 580, 20, .light_gray);
        drawAppText(state, "Trigger lists are parsed strictly but not applied yet in this viewer.", 56, 610, 20, .light_gray);
    } else {
        drawAppText(state, "Binary Ninja + Ghidra + IDA agree on the loader shape:", 56, 486, 20, .gold);
        drawAppText(state, "TextureFilename resolves to X/<basename>.tga", 56, 520, 20, .light_gray);
        drawAppText(state, "MeshMaterialList assigns one material index per face", 56, 550, 20, .light_gray);
        drawAppText(state, "Faces with 4 indices are quads; others are triangles", 56, 580, 20, .light_gray);
        drawAppText(state, "This viewer triangulates quads and draws archive-backed textures directly.", 56, 610, 20, .light_gray);
    }
}

fn drawModelViewport(state: *const AppState) void {
    const model = state.activeModel() orelse return;
    const camera = model.previewCamera(@floatCast(state.render_time_seconds));
    camera.begin();
    defer rl.endMode3D();

    const grid_slices: i32 = @intFromFloat(@min(@max(model.radius * 6.0, 10.0), 80.0));
    const grid_spacing = @max(model.radius / 2.0, 0.5);
    rl.drawGrid(grid_slices, grid_spacing);
    model.draw();
}

fn drawObjectPanel(state: *const AppState) !void {
    const entry = state.catalog.object_entries[state.object_index];
    const loaded_object = state.current_object orelse return;

    var summary_buffer: [256]u8 = undefined;
    const summary_text = try std.fmt.bufPrintZ(
        &summary_buffer,
        "Object {d}/{d}  vertices {d}  faces {d}  textures {d}",
        .{
            state.object_index + 1,
            state.catalog.object_entries.len,
            loaded_object.parsed.vertices.len,
            loaded_object.parsed.faces.len,
            loaded_object.parsed.texture_names.len,
        },
    );
    drawAppText(state, summary_text, 32, 194, 24, .ray_white);

    var path_buffer: [512]u8 = undefined;
    const path_text = try std.fmt.bufPrintZ(&path_buffer, "{s}", .{entry.path});
    drawAppText(state, path_text, 32, 226, 18, .light_gray);

    var detail_buffer: [256]u8 = undefined;
    const detail_text = try std.fmt.bufPrintZ(
        &detail_buffer,
        "submeshes {d}  triangles {d}  flipV {s}",
        .{
            loaded_object.submeshes.len,
            triangleCountForObject(loaded_object),
            if (state.object_flip_v) "on" else "off",
        },
    );
    drawAppText(state, detail_text, 32, 258, 20, .sky_blue);

    rl.drawRectangleRounded(.{ .x = 32, .y = 304, .width = 460, .height = 332 }, 0.03, 8, .dark_blue);
    drawAppText(state, "Object notes", 56, 332, 26, .ray_white);

    var bounds_buffer: [384]u8 = undefined;
    const bounds_text = try std.fmt.bufPrintZ(
        &bounds_buffer,
        "Bounds center: {d:.2}, {d:.2}, {d:.2}",
        .{ loaded_object.center.x, loaded_object.center.y, loaded_object.center.z },
    );
    drawAppText(state, bounds_text, 56, 378, 20, .light_gray);

    var radius_buffer: [256]u8 = undefined;
    const radius_text = try std.fmt.bufPrintZ(&radius_buffer, "Preview radius: {d:.2}", .{loaded_object.radius});
    drawAppText(state, radius_text, 56, 410, 20, .light_gray);

    var texture_buffer: [384]u8 = undefined;
    const texture_text = try std.fmt.bufPrintZ(
        &texture_buffer,
        "First texture: {s}",
        .{if (loaded_object.submeshes.len > 0 and loaded_object.submeshes[0].archive_texture_path != null) loaded_object.submeshes[0].archive_texture_path.? else "<none>"},
    );
    drawAppText(state, texture_text, 56, 442, 20, .light_gray);

    drawAppText(state, "Simple text object format:", 56, 486, 20, .gold);
    drawAppText(state, "[VERTEX START] defines indexed positions", 56, 520, 20, .light_gray);
    drawAppText(state, "[FACEQUAD START] defines quads with four UV pairs", 56, 550, 20, .light_gray);
    drawAppText(state, "Texture tokens resolve to sibling TGA files in the same OBJECTS folder.", 56, 580, 20, .light_gray);
    drawAppText(state, "This viewer triangulates those quads into a textured mesh directly.", 56, 610, 20, .light_gray);
}

fn drawObjectViewport(state: *const AppState) void {
    const loaded_object = state.current_object orelse return;
    const camera = loaded_object.previewCamera(@floatCast(state.render_time_seconds));
    camera.begin();
    defer rl.endMode3D();

    const grid_slices: i32 = @intFromFloat(@min(@max(loaded_object.radius * 6.0, 10.0), 80.0));
    const grid_spacing = @max(loaded_object.radius / 2.0, 0.5);
    rl.drawGrid(grid_slices, grid_spacing);
    loaded_object.draw();
}

fn drawLevelPanel(state: *const AppState) !void {
    const level_entry = state.catalog.level_entries[state.level_index];
    const loaded_level = state.current_level orelse return;
    const loaded_track_preview = state.current_track_preview orelse return;
    var track_value_buffer: [32]u8 = undefined;
    var parcels_value_buffer: [32]u8 = undefined;
    var quota_value_buffer: [32]u8 = undefined;
    var speed_value_buffer: [32]u8 = undefined;
    var garbage_value_buffer: [32]u8 = undefined;
    var salt_value_buffer: [32]u8 = undefined;
    var garbage_scalar_buffer: [32]u8 = undefined;
    var salt_scalar_buffer: [32]u8 = undefined;

    var summary_buffer: [384]u8 = undefined;
    const summary_text = try std.fmt.bufPrintZ(
        &summary_buffer,
        "Level {d}/{d}  {s}  mode {s}  segments {d}",
        .{
            state.level_index + 1,
            state.catalog.level_entries.len,
            loaded_level.name,
            loaded_level.mode,
            loaded_track_preview.segments.len,
        },
    );
    drawAppText(state, summary_text, 32, 194, 24, .ray_white);

    var path_buffer: [512]u8 = undefined;
    const path_text = try std.fmt.bufPrintZ(&path_buffer, "{s}", .{level_entry.path});
    drawAppText(state, path_text, 32, 226, 18, .light_gray);

    var meta_buffer: [384]u8 = undefined;
    const meta_text = try std.fmt.bufPrintZ(
        &meta_buffer,
        "track {s}  parcels {s}  quota {s}  speed {s}  garbage {s}  salt {s}",
        .{
            trackToText(&track_value_buffer, loaded_level.track),
            optionalUsizeToText(&parcels_value_buffer, loaded_level.parcels),
            optionalUsizeToText(&quota_value_buffer, loaded_level.quota),
            optionalUsizeToText(&speed_value_buffer, loaded_level.speed),
            optionalUsizeToText(&garbage_value_buffer, loaded_level.garbage),
            optionalUsizeToText(&salt_value_buffer, loaded_level.salt),
        },
    );
    drawAppText(state, meta_text, 32, 258, 20, .sky_blue);

    const fallback_counts = loaded_track_preview.fallbackHazardCandidateCounts();
    var runtime_buffer: [384]u8 = undefined;
    const runtime_text = try std.fmt.bufPrintZ(
        &runtime_buffer,
        "build 0x{x:0>8}  garbage scalar {s}  salt scalar {s}  fallback G {d}  S {d}",
        .{
            loaded_track_preview.runtime_build_flags,
            optionalFloatToText(&garbage_scalar_buffer, loaded_level.normalizedGarbageScalar()),
            optionalFloatToText(&salt_scalar_buffer, loaded_level.normalizedSaltScalar()),
            fallback_counts.garbage,
            fallback_counts.salt,
        },
    );
    drawAppText(state, runtime_text, 32, 284, 18, .light_gray);

    rl.drawRectangleRounded(.{ .x = 32, .y = 304, .width = 460, .height = 408 }, 0.03, 8, .dark_blue);
    drawAppText(state, "Level and segment notes", 56, 332, 26, .ray_white);

    if (state.activeLevelSegmentEntry()) |segment_entry| {
        var segment_buffer: [384]u8 = undefined;
        const segment_text = try std.fmt.bufPrintZ(
            &segment_buffer,
            "Segment {d}/{d}: {s}",
            .{
                state.level_segment_index + 1,
                loaded_level.segments.len,
                segment_entry.path,
            },
        );
        drawAppText(state, segment_text, 56, 378, 20, .gold);

        var timing_buffer: [384]u8 = undefined;
        var duration_value_buffer: [32]u8 = undefined;
        var angle_value_buffer: [32]u8 = undefined;
        const timing_text = try std.fmt.bufPrintZ(
            &timing_buffer,
            "Duration {s}  Angle {s}  Sample {s}",
            .{
                optionalFloatToText(&duration_value_buffer, segment_entry.duration),
                optionalFloatToText(&angle_value_buffer, segment_entry.angle),
                segment_entry.sample orelse "<none>",
            },
        );
        drawAppText(state, timing_text, 56, 410, 20, .light_gray);

        if (segment_entry.message) |message| {
            drawAppText(state, "Tutorial message:", 56, 444, 20, .light_gray);
            try drawWrappedText(state, message, 56, 472, 412, 20, .ray_white);
        } else {
            drawAppText(state, "No per-segment tutorial metadata on this entry.", 56, 444, 20, .light_gray);
        }
    }

    if (state.current_segment) |loaded_segment| {
        var dim_buffer: [384]u8 = undefined;
        const dim_text = try std.fmt.bufPrintZ(
            &dim_buffer,
            "Grid {d}x{d}  semantic rows {d}  marked rows {d}  preview rows {d}",
            .{
                loaded_segment.width,
                loaded_segment.height,
                countAnnotatedRows(loaded_segment.rows),
                countMarkedRows(loaded_segment.rows),
                loaded_track_preview.total_rows,
            },
        );
        drawAppText(state, dim_text, 56, 620, 18, .light_gray);
    }

    if (state.level_runner) |runner| {
        var sim_buffer: [384]u8 = undefined;
        const sim_text = try std.fmt.bufPrintZ(
            &sim_buffer,
            "Sim row {d:.2}/{d}  cursor {d}+{d:.2}  rate {d:.2}  lane {d}->{d}  speed {d:.1}  tick {d}  mode {s}",
            .{
                runner.row_position,
                loaded_track_preview.total_rows,
                runner.runtime_track_index,
                runner.movement_progress,
                runner.movement_rate_scalar,
                runner.lane_index,
                runner.resolved_lane_index,
                runner.speed_rows_per_second,
                runner.tick_count,
                runner.movement_mode.label(),
            },
        );
        drawAppText(state, sim_text, 56, 646, 18, .gold);

        var cell_buffer: [384]u8 = undefined;
        var path_value_buffer: [96]u8 = undefined;
        var tile_value_buffer: [32]u8 = undefined;
        const cell_text = try std.fmt.bufPrintZ(
            &cell_buffer,
            "Cell {c} {s}  tile {s}  bounds {d}-{d}  attach {s}  path {s}",
            .{
                runner.current_cell,
                runner.gameplayCellLabel() orelse "<none>",
                optionalHexU8ToText(&tile_value_buffer, runner.runtimeTileHint()),
                runner.traversable_bounds.min,
                runner.traversable_bounds.max,
                runner.attachment_hint.label(),
                optionalTextToText(&path_value_buffer, runner.activePathName()),
            },
        );
        drawAppText(state, cell_text, 56, 670, 18, .light_gray);

        var event_buffer: [384]u8 = undefined;
        const event_text = try std.fmt.bufPrintZ(
            &event_buffer,
            "Event {s}  annotation {s}  paused {s}  attachment ticks {d}",
            .{
                runner.recentEventLabel(),
                runner.annotationLabel() orelse "<none>",
                if (runner.paused) "yes" else "no",
                runner.attachment_ticks,
            },
        );
        drawAppText(state, event_text, 56, 692, 16, .sky_blue);

        var counter_buffer: [384]u8 = undefined;
        const counter_text = try std.fmt.bufPrintZ(
            &counter_buffer,
            "H {d}  J {d}  G {d}  S {d}  Sl {d}  T {d}  P {d}  A {d}/{d}  NF {d}  JO {d}",
            .{
                runner.counters.health_pickups,
                runner.counters.jetpack_pickups,
                runner.counters.garbage_hits,
                runner.counters.salt_hits,
                runner.counters.slug_hits,
                runner.counters.trampoline_rows,
                runner.counters.parcels,
                runner.counters.attachments_begun,
                runner.counters.attachments_completed,
                runner.counters.no_fall_rows,
                runner.counters.jetpack_off_rows,
            },
        );
        drawAppText(state, counter_text, 56, 712, 16, .light_gray);
    }

    drawSegmentGrid(state.current_segment orelse return, 540, 194, 676, 482);
}

fn drawLevelViewport(state: *const AppState) void {
    const loaded_track_preview = state.current_track_preview orelse return;
    const camera = loaded_track_preview.previewCamera(@floatCast(state.render_time_seconds), state.level_segment_index);
    camera.begin();
    defer rl.endMode3D();

    const grid_slices: i32 = @intCast(@max(loaded_track_preview.total_rows, 10));
    rl.drawGrid(@min(grid_slices, 200), 1.0);
    loaded_track_preview.draw(state.level_segment_index);
    if (state.level_runner) |runner| {
        const position = runner.worldPosition(&loaded_track_preview, 0.58);
        const color: rl.Color = if (runner.movement_mode == .attachment)
            .gold
        else switch (runner.attachment_hint) {
            .none => .lime,
            .probe => .orange,
            .entry => .yellow,
        };
        rl.drawSphere(position, if (runner.attachment_hint == .none) 0.18 else 0.22, color);
        rl.drawLine3D(
            .{ .x = position.x, .y = 0.04, .z = position.z },
            position,
            color,
        );
    }
}

fn drawGameplayLevelViewport(state: *const AppState) void {
    const loaded_track_preview = state.current_track_preview orelse return;
    const runner = state.level_runner orelse {
        drawLevelViewport(state);
        return;
    };

    const camera = if (runner.acceptsGameplayInput())
        gameplayLevelCamera(&loaded_track_preview, runner)
    else if (runner.finished)
        completionCutsceneCamera(&loaded_track_preview, runner, runner.phaseProgress())
    else
        deathCutsceneCamera(&loaded_track_preview, runner, runner.phaseProgress());
    camera.begin();
    defer rl.endMode3D();

    const selected_segment_index = if (loaded_track_preview.locateRow(runner.current_global_row)) |row_location|
        row_location.segment_index
    else
        0;
    loaded_track_preview.draw(selected_segment_index);
}

fn gameplayLevelCamera(loaded_track_preview: *const track.LoadedLevelPreview, runner: gameplay.Runner) rl.Camera3D {
    if (loaded_track_preview.total_rows == 0) {
        return loaded_track_preview.previewCamera(0.0, 0);
    }

    const player_position = runner.worldPosition(loaded_track_preview, 0.82);
    const player_floor = loaded_track_preview.sampleFloorHeightAtGridPosition(
        runner.current_global_row,
        runner.resolved_lane_index,
        runner.row_position,
    ) orelse 0.0;
    const max_target_row_position = @max(@as(f32, @floatFromInt(loaded_track_preview.total_rows)) - 0.5, 0.5);
    const target_row_position = std.math.clamp(runner.row_position + 8.0, 0.5, max_target_row_position);
    const target_global_row = @min(@as(usize, @intFromFloat(@floor(target_row_position))), loaded_track_preview.total_rows - 1);
    const target_lane_index = if (loaded_track_preview.locateRow(target_global_row)) |row_location| blk: {
        const bounds = loaded_track_preview.laneBoundsForRow(row_location);
        break :blk std.math.clamp(runner.resolved_lane_index, bounds.min, bounds.max);
    } else runner.resolved_lane_index;
    const target_lane_center = @as(f32, @floatFromInt(target_lane_index)) + 0.5;
    const target_floor = loaded_track_preview.sampleFloorHeightAtGridPosition(
        target_global_row,
        target_lane_index,
        target_row_position,
    ) orelse 0.0;
    const target = loaded_track_preview.worldPositionForLane(target_lane_center, target_row_position, target_floor + 0.62);
    // PORT(partial): `cRCameraman::AI()` seeds the chase camera from the player's world X,
    // a fixed +1.8 Y offset, and a -0.5 Z offset before applying the richer matrix blend path.
    const position = rl.Vector3{
        .x = player_position.x * 0.5,
        .y = player_floor + 1.8,
        .z = player_position.z - 0.5,
    };

    return .{
        .position = position,
        .target = target,
        .up = .{ .x = 0.0, .y = 1.0, .z = 0.0 },
        .fovy = 68.0,
        .projection = .perspective,
    };
}

// PORT(partial): `cRCutScene::Init()` and `cRCutScene::AI()` own a distinct post-finish camera
// handoff before `initialize_completion_screen`. The original blend path is richer; for now we
// widen and raise the recovered chase view over the cutscene duration instead of jumping straight
// into the completion summary.
fn completionCutsceneCamera(
    loaded_track_preview: *const track.LoadedLevelPreview,
    runner: gameplay.Runner,
    progress: f32,
) rl.Camera3D {
    var camera = gameplayLevelCamera(loaded_track_preview, runner);
    const eased = progress * progress * (3.0 - 2.0 * progress);

    camera.position.y += 1.4 * eased;
    camera.position.z -= 2.2 * eased;
    camera.target.y += 0.4 * eased;
    camera.target.z += 0.8 * eased;
    return camera;
}

fn deathCutsceneCamera(
    loaded_track_preview: *const track.LoadedLevelPreview,
    runner: gameplay.Runner,
    progress: f32,
) rl.Camera3D {
    var camera = gameplayLevelCamera(loaded_track_preview, runner);
    const eased = progress * progress * (3.0 - 2.0 * progress);

    camera.position.x += 0.6 * eased;
    camera.position.y += 0.6 * eased;
    camera.position.z -= 1.4 * eased;
    camera.target.y -= 0.2 * eased;
    return camera;
}

fn laneTargetForRunnerMouse(
    loaded_track_preview: track.LoadedLevelPreview,
    runner: gameplay.Runner,
    mouse_x: f32,
) ?usize {
    const row_location = loaded_track_preview.locateRow(runner.current_global_row) orelse return null;
    return laneTargetForMouseX(mouse_x, @floatFromInt(screenWidth()), loaded_track_preview.laneBoundsForRow(row_location));
}

fn laneTargetForMouseX(mouse_x: f32, screen_width: f32, bounds: track.LaneBounds) usize {
    const lane_count = bounds.max - bounds.min + 1;
    if (lane_count <= 1 or screen_width <= 1.0) return bounds.min;

    const clamped_mouse_x = std.math.clamp(mouse_x, 0.0, screen_width - 1.0);
    const ratio = clamped_mouse_x / screen_width;
    const lane_offset = @min(
        @as(usize, @intFromFloat(@floor(ratio * @as(f32, @floatFromInt(lane_count))))),
        lane_count - 1,
    );
    return bounds.min + lane_offset;
}

fn drawSegmentGrid(loaded_segment: segment.Definition, x: i32, y: i32, width: i32, height: i32) void {
    rl.drawRectangleLines(x, y, width, height, .dark_gray);

    const usable_width = @as(f32, @floatFromInt(width - 16));
    const usable_height = @as(f32, @floatFromInt(height - 16));
    const cell_width = usable_width / @as(f32, @floatFromInt(@max(loaded_segment.width, 1)));
    const cell_height = usable_height / @as(f32, @floatFromInt(@max(loaded_segment.height, 1)));
    const cell_size = @min(cell_width, cell_height);

    const grid_width = cell_size * @as(f32, @floatFromInt(loaded_segment.width));
    const grid_height = cell_size * @as(f32, @floatFromInt(loaded_segment.height));
    const offset_x = @as(f32, @floatFromInt(x)) + 8.0 + (usable_width - grid_width) * 0.5;
    const offset_y = @as(f32, @floatFromInt(y)) + 8.0 + (usable_height - grid_height) * 0.5;

    for (loaded_segment.rows, 0..) |row, row_index| {
        const row_y = offset_y + @as(f32, @floatFromInt(row_index)) * cell_size;
        for (row.cells, 0..) |cell, col_index| {
            const draw_x = offset_x + @as(f32, @floatFromInt(col_index)) * cell_size;
            rl.drawRectangleRec(
                .{
                    .x = draw_x,
                    .y = row_y,
                    .width = cell_size,
                    .height = cell_size,
                },
                colorForSegmentCell(cell),
            );
        }

        if (row.annotation) |annotation| {
            rl.drawRectangleRec(
                .{
                    .x = offset_x,
                    .y = row_y,
                    .width = grid_width,
                    .height = @max(cell_size * 0.12, 2.0),
                },
                colorForSegmentAnnotation(annotation),
            );
        }

        if (row.marked) {
            const marker_width = @max(cell_size * 0.14, 3.0);
            const marker_height = @max(cell_size * 0.55, 4.0);
            const marker_y = row_y + (cell_size - marker_height) * 0.5;
            rl.drawRectangleRec(
                .{
                    .x = offset_x,
                    .y = marker_y,
                    .width = marker_width,
                    .height = marker_height,
                },
                .gold,
            );
            rl.drawRectangleRec(
                .{
                    .x = offset_x + grid_width - marker_width,
                    .y = marker_y,
                    .width = marker_width,
                    .height = marker_height,
                },
                .gold,
            );
        }
    }
}

fn triangleCountForObject(loaded_object: object.LoadedObject) usize {
    var total: usize = 0;
    for (loaded_object.submeshes) |submesh| {
        total += submesh.triangle_count;
    }
    return total;
}

fn countAnnotatedRows(rows: []const segment.Row) usize {
    var total: usize = 0;
    for (rows) |row| {
        if (row.annotation != null) total += 1;
    }
    return total;
}

fn countMarkedRows(rows: []const segment.Row) usize {
    var total: usize = 0;
    for (rows) |row| {
        if (row.marked) total += 1;
    }
    return total;
}

fn colorForSegmentAnnotation(annotation: segment.Annotation) rl.Color {
    return switch (annotation) {
        .path => .gold,
        .ring => |ring| switch (ring) {
            .none => .gray,
            .normal => .yellow,
            .powerup => .green,
            .explode => .orange,
            .slow => .purple,
        },
        .parcel => .green,
        .model => .purple,
        .jetpack_off => .red,
        .no_fall => .sky_blue,
    };
}

fn colorForSegmentCell(cell: u8) rl.Color {
    return switch (cell) {
        '@' => .dark_blue,
        '_' => .gray,
        '.' => .light_gray,
        'P' => .sky_blue,
        '#' => .orange,
        's' => .ray_white,
        '>' => .gold,
        '{', '}', ';' => .yellow,
        '[', 'M', 'R', 'J' => .red,
        '~' => .green,
        '$', '&', '(', ')', '-', '<', '=', '0', '1', '2', '3', '|', 'p' => .purple,
        ' ' => .black,
        else => .dark_purple,
    };
}

fn uiContext(state: *const AppState) app_ui.Context {
    return .{ .font = &state.ui_font };
}

fn drawAppText(state: *const AppState, text: []const u8, x: i32, y: i32, font_size: i32, color: rl.Color) void {
    app_ui.drawText(uiContext(state), text, x, y, font_size, color);
}

fn measureAppText(state: *const AppState, text: []const u8, font_size: i32) i32 {
    return app_ui.measureText(uiContext(state), text, font_size);
}

fn drawWrappedText(state: *const AppState, text: []const u8, x: i32, y: i32, max_width: i32, line_height: i32, color: rl.Color) !void {
    return app_ui.drawWrappedText(uiContext(state), text, x, y, max_width, line_height, color);
}

fn drawMenuItem(state: *const AppState, layout: VirtualLayout, index: usize, selected_index: usize, label: []const u8) void {
    app_ui.drawMenuItem(uiContext(state), layout, index, selected_index, label);
}

fn drawRouteSelectionDots(state: *const AppState, layout: VirtualLayout, panels: MenuPanels, current_index: usize, max_index: usize) void {
    app_ui.drawRouteSelectionDots(uiContext(state), layout, panels, current_index, max_index);
}

fn modeLabel(mode: xanim.Mode) [:0]const u8 {
    return switch (mode) {
        .loop => "loop",
        .once => "once",
        .pingpong => "pingpong",
    };
}

fn nextMode(mode: Mode) Mode {
    return switch (mode) {
        .textures => .audio,
        .audio => .models,
        .models => .objects,
        .objects => .levels,
        .levels => .textures,
    };
}

fn optionalUsizeToText(buffer: []u8, value: ?usize) []const u8 {
    return if (value != null) std.fmt.bufPrint(buffer, "{d}", .{value.?}) catch "?" else "-";
}

fn optionalTextToText(buffer: []u8, value: ?[]const u8) []const u8 {
    return if (value) |text| std.fmt.bufPrint(buffer, "{s}", .{text}) catch "?" else "-";
}

fn optionalHexU8ToText(buffer: []u8, value: ?u8) []const u8 {
    return if (value) |tile_type| std.fmt.bufPrint(buffer, "0x{x}", .{tile_type}) catch "?" else "-";
}

fn trackToText(buffer: []u8, value: level.Track) []const u8 {
    return switch (value) {
        .index => |track_index| std.fmt.bufPrint(buffer, "{d}", .{track_index}) catch "?",
        .random => "random",
    };
}

fn optionalFloatToText(buffer: []u8, value: ?f32) []const u8 {
    return if (value != null) std.fmt.bufPrint(buffer, "{d:.1}", .{value.?}) catch "?" else "-";
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

fn highScoreModeIndex(mode: high_score.Mode) usize {
    for (high_score_screen_modes, 0..) |candidate, index| {
        if (candidate == mode) return index;
    }
    return 0;
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
    try std.testing.expect(!completionBonusAppliesForMode(null));
}

test "failed runs return to the main menu while completions keep mode-specific exits" {
    try std.testing.expectEqual(ResultReturnTarget.postal_route_map, resultReturnTargetForOutcome(.completed, .postal));
    try std.testing.expectEqual(ResultReturnTarget.time_trial_route_map, resultReturnTargetForOutcome(.completed, .time_trial));
    try std.testing.expectEqual(ResultReturnTarget.replay_current_level, resultReturnTargetForOutcome(.completed, .challenge));
    try std.testing.expectEqual(ResultReturnTarget.main_menu, resultReturnTargetForOutcome(.failed, .postal));
    try std.testing.expectEqual(ResultReturnTarget.main_menu, resultReturnTargetForOutcome(.failed, .challenge));
    try std.testing.expectEqual(ResultReturnTarget.main_menu, resultReturnTargetForOutcome(.failed, .time_trial));
}

test "elapsed millis format as mm:ss.cc" {
    var buffer: [32]u8 = undefined;
    const text = try formatElapsedMillis(&buffer, 91_230);
    try std.testing.expectEqualStrings("01:31.23", text);
}

test "high score mode index follows screen order" {
    try std.testing.expectEqual(@as(usize, 0), highScoreModeIndex(.postal));
    try std.testing.expectEqual(@as(usize, 1), highScoreModeIndex(.challenge));
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

    const camera = gameplayLevelCamera(&loaded_track_preview, runner);
    const player_position = runner.worldPosition(&loaded_track_preview, 0.82);
    try std.testing.expect(camera.target.z > camera.position.z);
    try std.testing.expect(camera.position.z < player_position.z);
    try std.testing.expect(camera.position.y > 0.0);
    try std.testing.expect(camera.position.y > player_position.y);
    try std.testing.expect(camera.target.y >= 0.0);
    try std.testing.expectApproxEqAbs(@as(f32, 68.0), camera.fovy, 0.001);
}

test "completion cutscene camera widens the chase view" {
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

    const chase_camera = gameplayLevelCamera(&loaded_track_preview, runner);
    const cutscene_camera = completionCutsceneCamera(&loaded_track_preview, runner, 1.0);

    try std.testing.expect(cutscene_camera.position.y > chase_camera.position.y);
    try std.testing.expect(cutscene_camera.position.z < chase_camera.position.z);
    try std.testing.expect(cutscene_camera.target.z > chase_camera.target.z);
}

test "lane target mapping respects bounds" {
    const bounds: track.LaneBounds = .{ .min = 2, .max = 4 };
    try std.testing.expectEqual(@as(usize, 2), laneTargetForMouseX(0.0, 1280.0, bounds));
    try std.testing.expectEqual(@as(usize, 3), laneTargetForMouseX(640.0, 1280.0, bounds));
    try std.testing.expectEqual(@as(usize, 4), laneTargetForMouseX(1279.0, 1280.0, bounds));
}
