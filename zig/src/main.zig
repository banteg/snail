const std = @import("std");
const rl = @import("raylib");
const app = @import("app.zig");
const app_ui = @import("app_ui.zig");
const assets = @import("assets.zig");
const background = @import("background.zig");
const config = @import("config.zig");
const debug_levels = @import("debug_levels.zig");
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
const track_render = @import("track_render.zig");
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
const completion_parcel_icon_texture_path = app.completion_parcel_icon_texture_path;
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
const pause_menu_items = frontend.pause_menu_items;
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

    fn textures(self: SliderArt) frontend_widget.SliderTextures {
        return .{
            .less = if (self.less) |texture| texture.texture else null,
            .less_hover = if (self.less_hover) |texture| texture.texture else null,
            .more = if (self.more) |texture| texture.texture else null,
            .more_hover = if (self.more_hover) |texture| texture.texture else null,
            .bar = if (self.bar) |texture| texture.texture else null,
            .bar_full = if (self.bar_full) |texture| texture.texture else null,
        };
    }
};

const FrontendWidgetArt = struct {
    border: ?assets.LoadedTexture = null,
    parcel_icon: ?assets.LoadedTexture = null,

    fn unload(self: *FrontendWidgetArt) void {
        if (self.border) |*texture| {
            texture.unload();
            self.border = null;
        }
        if (self.parcel_icon) |*texture| {
            texture.unload();
            self.parcel_icon = null;
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
    art.parcel_icon = try catalog.loadTextureByPath(allocator, completion_parcel_icon_texture_path);

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
};

const high_score_screen_modes = [_]high_score.Mode{
    .postal,
    .challenge,
};

const ExitPromptMode = enum {
    quit_app,
    abandon_run,
    leave_route_map,
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

const route_menu_actions_closed = [_]RouteMenuAction{
    .back,
};

const RouteMapHoverState = enum(u8) {
    none = 0,
    card = 1,
    route = 2,
};

const RouteMapScreenMode = enum(u8) {
    normal = 0,
    post_completion_exit = 1,
    replay = 2,
};

// PORT(verified): `initialize_main_menu` seeds the first button at `y = 90`, then chains
// High Scores, Options, Credits, and Exit with `sub_4027B0`. Windows seeds Exit with
// `y = 390` first, but immediately overrides it by chaining from Credits.
const main_menu_start_y: f32 = 90.0;
// PORT(verified): `initialize_new_game_menu` seeds Tutorial at `y = 80`, chains Postal,
// Time Trial, and Challenge Mode with `stack_widget_below`, places Help explicitly at
// `(center - 220, y = 350)`, then seeds Back at `y = 350` but immediately stacks it below
// Challenge Mode. The explicit `350` for Back is only a constructor seed.
const new_game_start_y: f32 = 80.0;
const new_game_help_anchor_y: f32 = 350.0;
const new_game_help_center_offset_x: f32 = -220.0;
const new_game_back_center_offset_x: f32 = 0.0;
// PORT(verified): `initialize_help` places the lone Back control at `(center, y=420)`.
const help_back_anchor_y: f32 = 420.0;
const options_button_count = 4;
const options_fullscreen_button_index: usize = 0;
const options_sound_button_index: usize = 1;
const options_music_button_index: usize = 2;
const options_back_button_index: usize = 3;
// PORT(verified): `initialize_options` seeds the fullscreen row at `y = 75`, then nudges
// the widget down by `+8`, so the final authored-space anchor is `83`.
const options_fullscreen_anchor_y: f32 = 83.0;
// PORT(verified): `initialize_options` keeps the options rows on the centered shell-font path.
// The constructor's `90.0` seed is only the left-measure start fed into `sub_44abe0`; the final
// centered X comes from `arg13 + 320 - width*0.5`, and `arg13` stays `0.0` for this screen.
const options_button_center_offset_x: f32 = 0.0;
const options_slider_adjust_step: f32 = 0.2;
const options_slider_display_lerp: f32 = 0.8;
// PORT(verified): `initialize_galaxy` places the Star Map title at `(15,15)` with shell-font
// scale `0.83`, the bottom Back/Exit control at `(20,420)` with absolute alignment, and
// `open_galaxy_route` seeds the selected route card from `(route_x + 60, route_y - 130)`.
const route_map_title_x: f32 = 15.0;
const route_map_title_y: f32 = 15.0;
const route_map_title_scale: f32 = 0.83;
// PORT(verified): `initialize_galaxy` seeds sprite `138` at `(300,10)`. The shipped
// `SPACEMAPLOGO.TGA` art is `256x64`, and the Windows sprite path uses that authored size.
const route_map_logo_x: f32 = 300.0;
const route_map_logo_y: f32 = 10.0;
const route_map_logo_width: f32 = 256.0;
const route_map_logo_height: f32 = 64.0;
const route_map_back_x: f32 = 20.0;
const route_map_back_y: f32 = 420.0;
const route_map_card_title_scale: f32 = 0.9;
const route_map_card_subtitle_scale: f32 = 0.9;
const route_map_card_body_scale: f32 = 0.7;
// PORT(verified): `open_galaxy_route` expands the selected card bounds by `8` on the
// left/right and bottom edges only. The top edge stays anchored to the title widget.
const route_map_card_horizontal_padding: f32 = 8.0;
const route_map_card_bottom_padding: f32 = 8.0;
const route_map_card_horizontal_pointer_gap: f32 = 6.0;
const route_map_card_star_gap: f32 = 16.0;
const route_map_card_right_limit: f32 = 631.0;
const route_map_card_min_top: f32 = 49.0;
const route_map_card_bottom_y: f32 = 450.0;
const route_map_card_text_gap: f32 = 0.0;
const route_map_primary_button_gap: f32 = 20.0;
const route_map_replay_button_gap: f32 = 10.0;
// PORT(verified): `sub_401130` renders the selected route card (`69516`) as a type-20 style
// 9-slice frame with a recovered authored edge size of `26.0`, not as a stretched quad.
const route_map_card_frame_edge: f32 = 26.0;
// PORT(verified): `update_galaxy` draws galaxy sprites `139..148` as `256x256` quads
// centered on the transformed `sub_4088E0` points, and the inter-route connector uses
// `LINE.TGA` at width `4.0`.
const route_map_galaxy_size: f32 = 256.0;
const route_map_path_line_width: f32 = 4.0;
const high_score_button_count = 2;
const high_score_replay_button_count = high_score.visible_entry_count;
const help_button_count = 1;
const route_map_button_count = 3;
const route_map_primary_button_index: usize = 0;
const route_map_replay_button_index: usize = 1;
const route_map_back_button_index: usize = 2;
// PORT(verified): `cRSubPause::Init()` creates the centered pause stack with `End Game`
// at `y = 145`, then chains `Options` and `Resume` below it with the shared shell-font
// widget stack helper.
const pause_menu_start_y: f32 = 145.0;
const pause_menu_center_offset_x: f32 = 0.0;
const pause_menu_button_count = pause_menu_items.len;
const exit_prompt_button_count = 2;
// PORT(verified): `initialize_high_score_screen` uses title `y = 64`, row start `111`,
// row pitch `27`, and footer row `111 + 10*27 = 381`. Each visible row is a separate
// type-22 widget bundle anchored at `x = -228/-222/-180/+160/+125` for postal or
// `x = -228/-222/-180/+125/+170` for challenge, rather than a single freehand text strip.
const high_score_title_y: f32 = 64.0;
const high_score_row_start_y: f32 = 111.0;
const high_score_row_pitch: f32 = 27.0;
const high_score_footer_y: f32 = 381.0;
const high_score_rank_marker_x: f32 = -228.0;
const high_score_rank_number_x: f32 = -222.0;
const high_score_name_x: f32 = -180.0;
const high_score_postal_score_x: f32 = 160.0;
const high_score_postal_replay_x: f32 = 125.0;
const high_score_challenge_score_x: f32 = 125.0;
const high_score_challenge_replay_x: f32 = 170.0;
const high_score_entry_cancel_x: f32 = -110.0;
const high_score_entry_submit_x: f32 = 55.0;
const high_score_back_x: f32 = -132.0;
const high_score_toggle_x: f32 = 33.0;
// PORT(verified): `initialize_completion_screen` uses title `80`, package line `160`,
// parcel icon sprite `122` at `(100, 144)`, optional bonus widget `302`, and continue `320/400`.
const completion_title_y: f32 = 80.0;
const completion_package_y: f32 = 160.0;
const completion_parcel_icon_x: f32 = 100.0;
const completion_parcel_icon_y: f32 = 144.0;
const completion_parcel_icon_width: f32 = 32.0;
const completion_parcel_icon_height: f32 = 64.0;
const completion_bonus_y: f32 = 302.0;
const completion_continue_y: f32 = 320.0;
const completion_continue_y_with_bonus: f32 = 400.0;
// PORT(verified): the shared centered exit prompt path in `initialize_exit_prompt`
// seeds the Yes/No buttons at `330`, but then stacks both beneath the title at
// `y = stack_widget_below(title)` while keeping their `x = -80/+80` offsets.
const exit_prompt_title_y: f32 = 200.0;
const exit_prompt_yes_x: f32 = -80.0;
const exit_prompt_no_x: f32 = 80.0;
const frontend_activation_delay_step: f32 = 1.0 / 12.0;
const frontend_canvas_width: i32 = 640;
const frontend_canvas_height: i32 = 480;

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
    options_sound_less,
    options_sound_more,
    options_music_volume,
    options_music_less,
    options_music_more,
    options_back,
    pause_menu_end_game,
    pause_menu_options,
    pause_menu_resume,
    route_map_play,
    route_map_watch_best_trial,
    route_map_back,
    help_back,
    high_scores_back,
    high_scores_switch_table,
    high_scores_replay_0,
    high_scores_replay_1,
    high_scores_replay_2,
    high_scores_replay_3,
    high_scores_replay_4,
    high_scores_replay_5,
    high_scores_replay_6,
    high_scores_replay_7,
    high_scores_replay_8,
    high_scores_replay_9,
    post_level_high_scores_cancel,
    post_level_high_scores_submit,
    completion_continue,
    exit_prompt_yes,
    exit_prompt_no,
};

const FrontendQueuedAction = union(enum) {
    main_menu: MainMenuItem,
    new_game_menu: NewGameMenuItem,
    options_menu: OptionsMenuItem,
    pause_menu: PauseMenuItem,
    route_map_menu: RouteMenuAction,
    help_menu: HelpMenuAction,
    high_scores_menu: HighScoreMenuAction,
    high_score_replay: usize,
    post_level_high_scores: PostLevelHighScoreAction,
    completion_screen: CompletionAction,
    exit_prompt: ExitPromptChoice,
};

const HelpMenuAction = enum {
    back,
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

fn hoverTargetForOptionsSliderArrow(item: OptionsMenuItem, direction: frontend_widget.SliderDirection) FrontendHoverTarget {
    return switch (item) {
        .sound_volume => switch (direction) {
            .less => .options_sound_less,
            .more => .options_sound_more,
        },
        .music_volume => switch (direction) {
            .less => .options_music_less,
            .more => .options_music_more,
        },
        else => unreachable,
    };
}

fn sliderHoverTargetBelongsToOptionsRow(target: FrontendHoverTarget, item: OptionsMenuItem) bool {
    return switch (item) {
        .sound_volume => switch (target) {
            .options_sound_volume, .options_sound_less, .options_sound_more => true,
            else => false,
        },
        .music_volume => switch (target) {
            .options_music_volume, .options_music_less, .options_music_more => true,
            else => false,
        },
        else => false,
    };
}

fn hoverTargetForPauseMenu(index: usize) FrontendHoverTarget {
    return switch (index) {
        0 => .pause_menu_end_game,
        1 => .pause_menu_options,
        2 => .pause_menu_resume,
        else => unreachable,
    };
}

fn hoverTargetForRouteMenuAction(action: RouteMenuAction) FrontendHoverTarget {
    return switch (action) {
        .play => .route_map_play,
        .watch_best_trial => .route_map_watch_best_trial,
        .back => .route_map_back,
    };
}

fn newGameMenuItemForFrontendMode(mode: FrontendLevelMode) NewGameMenuItem {
    return switch (mode) {
        .tutorial => .tutorial,
        .postal => .postal_mode,
        .time_trial => .time_trial,
        .challenge => .challenge_mode,
    };
}

fn newGameMenuIndexForItem(target: NewGameMenuItem) usize {
    for (new_game_menu_items, 0..) |item, index| {
        if (item == target) return index;
    }
    return 0;
}

fn defaultRouteMapScreenMode(mode: FrontendLevelMode) RouteMapScreenMode {
    // PORT(verified): `initialize_galaxy` uses internal mode `2` for the Time Trial / replay
    // Star Map path, while normal Postal entry starts in mode `0`.
    return switch (mode) {
        .postal => .normal,
        .time_trial => .replay,
        .challenge, .tutorial => unreachable,
    };
}

fn hoverTargetForHighScores(index: usize) FrontendHoverTarget {
    return switch (index) {
        0 => .high_scores_back,
        1 => .high_scores_switch_table,
        else => unreachable,
    };
}

fn hoverTargetForHighScoreReplay(index: usize) FrontendHoverTarget {
    return switch (index) {
        0 => .high_scores_replay_0,
        1 => .high_scores_replay_1,
        2 => .high_scores_replay_2,
        3 => .high_scores_replay_3,
        4 => .high_scores_replay_4,
        5 => .high_scores_replay_5,
        6 => .high_scores_replay_6,
        7 => .high_scores_replay_7,
        8 => .high_scores_replay_8,
        9 => .high_scores_replay_9,
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
        .pause_menu => |item| switch (item) {
            .end_game => .pause_menu_end_game,
            .options => .pause_menu_options,
            .@"resume" => .pause_menu_resume,
        },
        .route_map_menu => |item| switch (item) {
            .play => .route_map_play,
            .watch_best_trial => .route_map_watch_best_trial,
            .back => .route_map_back,
        },
        .help_menu => .help_back,
        .high_scores_menu => |item| switch (item) {
            .back => .high_scores_back,
            .switch_table => .high_scores_switch_table,
        },
        .high_score_replay => |index| hoverTargetForHighScoreReplay(index),
        .post_level_high_scores => |item| switch (item) {
            .cancel => .post_level_high_scores_cancel,
            .submit => .post_level_high_scores_submit,
        },
        .completion_screen => .completion_continue,
        .exit_prompt => |choice| switch (choice) {
            .yes => .exit_prompt_yes,
            .no => .exit_prompt_no,
        },
    };
}

fn queuedActivationRequiresFade(action: FrontendQueuedAction) bool {
    return switch (action) {
        .exit_prompt => |choice| switch (choice) {
            .yes => true,
            .no => false,
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
    segments,
};

const DebugSegmentRenderMode = enum {
    game,
    raw,
};

const AppState = struct {
    allocator: std.mem.Allocator,
    catalog: assets.Catalog,
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
    pause_menu_index: usize = 0,
    pause_menu_button_states: [pause_menu_button_count]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** pause_menu_button_count,
    options_return_phase: GamePhase = .main_menu,
    help_button_states: [help_button_count]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** help_button_count,
    route_map_button_states: [route_map_button_count]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** route_map_button_count,
    high_scores_menu_index: usize = 0,
    high_scores_action_index: usize = 1,
    high_score_button_states: [high_score_button_count]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** high_score_button_count,
    high_score_replay_button_states: [high_score_replay_button_count]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** high_score_replay_button_count,
    exit_prompt_choice_index: usize = 0,
    exit_prompt_button_states: [exit_prompt_button_count]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** exit_prompt_button_count,
    exit_prompt_return_phase: GamePhase = .main_menu,
    exit_prompt_mode: ExitPromptMode = .quit_app,
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
    route_map_screen_mode: RouteMapScreenMode = .normal,
    frontend_route_index: usize = 0,
    start_route_index_override: ?usize = null,
    route_menu_action_index: usize = 0,
    route_map_open_index: ?usize = null,
    route_map_hover_state: RouteMapHoverState = .none,
    route_map_hovered_index: ?usize = null,
    active_frontend_mode: ?FrontendLevelMode = null,
    active_frontend_level_index: usize = 0,
    route_map_route_highlight_alpha: [galaxy.map_route_count + 1]f32 = [_]f32{0.0} ** (galaxy.map_route_count + 1),
    route_map_route_highlight_target: [galaxy.map_route_count + 1]f32 = [_]f32{0.0} ** (galaxy.map_route_count + 1),
    mode: Mode = .textures,
    model_flip_v: bool = true,
    object_flip_v: bool = true,
    texture_index: usize,
    audio_index: usize,
    model_index: usize,
    object_index: usize,
    level_index: usize,
    segment_index: usize = 0,
    segment_render_mode: DebugSegmentRenderMode = .game,
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
    hovered_frontend_target: ?FrontendHoverTarget = null,
    keyboard_frontend_focus_visible: bool = false,
    pending_frontend_activation: ?FrontendQueuedActivation = null,
    completion_continue_button_state: frontend_widget.TextButtonState = .{},
    slider_art: SliderArt = .{},
    route_map_art: RouteMapArt = .{},
    options_sound_display_value: f32 = 0.0,
    options_music_display_value: f32 = 0.0,
    current_sound: ?assets.LoadedSound = null,
    current_music: ?assets.LoadedMusic = null,
    current_model: ?x2.Uploaded = null,
    current_animation: ?xanim.Player = null,
    current_object: ?object.LoadedObject = null,
    current_level: ?level.Definition = null,
    current_segment: ?segment.Definition = null,
    current_track_preview: ?track.LoadedLevelPreview = null,
    current_standalone_segment_preview: ?track.LoadedLevelPreview = null,
    current_standalone_segment_scene: ?track_render.Scene = null,
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
        const frontend_canvas = if (options.command == .game) blk: {
            const canvas = try rl.loadRenderTexture(frontend_canvas_width, frontend_canvas_height);
            rl.setTextureWrap(canvas.texture, .clamp);
            rl.setTextureFilter(canvas.texture, .bilinear);
            break :blk canvas;
        } else null;
        errdefer if (frontend_canvas) |canvas| canvas.unload();
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
        var galaxy_names: ?galaxy.Definition = try galaxy.loadByPath(allocator, &catalog, galaxy_names_path);
        errdefer if (galaxy_names) |*names| names.deinit();

        const texture_index = catalog.findTextureIndex(default_texture_path) orelse 0;
        const audio_index = catalog.findAudioIndex(default_audio_path) orelse 0;
        const model_index = catalog.findModelIndex(default_model_path) orelse 0;
        const object_index = catalog.findObjectIndex(default_object_path) orelse 0;
        const level_index = catalog.findLevelIndex(default_level_path) orelse 0;
        const segment_index: usize = 0;

        var state = AppState{
            .allocator = allocator,
            .catalog = catalog,
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
            .slider_art = slider_art,
            .route_map_art = route_map_art,
            .galaxy_names = galaxy_names,
        };
        errdefer state.deinit();
        galaxy_names = null;
        state.applyAudioConfigVolumes();

        switch (options.command) {
            .debug, .smoke => {
                try state.high_score_tables.loadFromRuntimeRoot(allocator, options.runtime_root_path);
                try state.reloadTexture();
                try state.reloadModel();
                try state.reloadObject();
                try state.reloadLevel();
                try state.reloadStandaloneSegment();
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
                self.preloaded_intro_script = try self.loadConfiguredTextScriptEntry(intro_script_path);
            },
            .load_credits_script => {
                self.unloadPreloadedTextScript(&self.preloaded_credits_script);
                self.preloaded_credits_script = try self.loadConfiguredTextScriptEntry(credits_script_path);
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
        if (rl.isKeyPressed(.six)) {
            try self.setMode(.segments);
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
        } else if (self.mode == .segments) {
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
            if (rl.isKeyPressed(.v)) {
                self.segment_render_mode = switch (self.segment_render_mode) {
                    .game => .raw,
                    .raw => .game,
                };
            }
            if (rl.isKeyPressed(.o)) {
                self.segment_show_overlay = !self.segment_show_overlay;
            }
            if (rl.isKeyPressed(.g)) {
                self.segment_show_grid = !self.segment_show_grid;
            }
            if (rl.isKeyPressed(.a)) {
                self.segment_show_attachments = !self.segment_show_attachments;
            }
            if (rl.isKeyPressed(.t)) {
                self.segment_track_set_index = (self.segment_track_set_index + 1) % 4;
                try self.reloadStandaloneSegmentScene();
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
        if (self.mouse_local_override) |mouse| {
            return .{ .x = mouse.x, .y = mouse.y };
        }
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
            self.keyboard_frontend_focus_visible = false;
            self.playFrontendHoverSound();
        }
    }

    fn noteFrontendKeyboardNavigation(self: *AppState) void {
        self.keyboard_frontend_focus_visible = true;
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
        return self.keyboard_frontend_focus_visible and fallback_selected;
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
            .pause_menu => |item| try self.performPauseMenuItem(item),
            .route_map_menu => |item| try self.performRouteMenuAction(item),
            .help_menu => |item| try self.performHelpMenuItem(item),
            .high_scores_menu => |item| try self.performHighScoreMenuAction(item),
            .high_score_replay => |index| try self.performHighScoreReplay(index),
            .post_level_high_scores => |item| try self.performPostLevelHighScoreAction(item),
            .completion_screen => |item| try self.performCompletionAction(item),
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
        for (&self.options_button_states, 0..) |*state, index| {
            const item = options_menu_items[index];
            const hot = switch (item) {
                .sound_volume, .music_volume => blk: {
                    const active_target = self.activeFrontendButtonTarget();
                    break :blk options_active and ((active_target != null and sliderHoverTargetBelongsToOptionsRow(active_target.?, item)) or (self.keyboard_frontend_focus_visible and self.options_menu_index == index));
                },
                else => options_active and self.frontendButtonHot(hoverTargetForOptions(index), self.options_menu_index == index),
            };
            state.stepFor(.menu_button, hot);
        }
        self.options_sound_display_value = stepOptionsSliderDisplay(self.options_sound_display_value, self.runtime_config.soundVolume());
        self.options_music_display_value = stepOptionsSliderDisplay(self.options_music_display_value, self.runtime_config.musicVolume());
        const pause_menu_active = self.game_phase == .pause_menu and !self.frontend_transition.blocksInput();
        for (&self.pause_menu_button_states, 0..) |*state, index| {
            state.stepFor(.menu_button, pause_menu_active and self.frontendButtonHot(hoverTargetForPauseMenu(index), self.pause_menu_index == index));
        }
        const route_map_active = self.game_phase == .route_map_menu and !self.frontend_transition.blocksInput();
        const route_map_card_open = self.routeMapCardIsOpen();
        self.route_map_button_states[route_map_primary_button_index].stepFor(
            .menu_button,
            route_map_active and route_map_card_open and self.frontendButtonHot(hoverTargetForRouteMenuAction(.play), self.activeRouteMenuHotAction() == .play),
        );
        self.route_map_button_states[route_map_replay_button_index].stepFor(
            .route_map_secondary_action,
            route_map_active and route_map_card_open and self.routeMapShowsReplay() and self.frontendButtonHot(hoverTargetForRouteMenuAction(.watch_best_trial), self.activeRouteMenuHotAction() == .watch_best_trial),
        );
        self.route_map_button_states[route_map_back_button_index].stepFor(
            .menu_button,
            route_map_active and self.frontendButtonHot(hoverTargetForRouteMenuAction(.back), self.activeRouteMenuHotAction() == .back),
        );
        const help_active = self.game_phase == .help and !self.frontend_transition.blocksInput();
        self.help_button_states[0].stepFor(.menu_button, help_active and self.frontendButtonHot(.help_back, true));

        const high_scores_active = self.game_phase == .high_scores_menu and !self.frontend_transition.blocksInput();
        for (&self.high_score_button_states, 0..) |*state, index| {
            state.stepFor(.footer_button, high_scores_active and self.postLevelHighScoreContext() == null and self.frontendButtonHot(hoverTargetForHighScores(index), self.high_scores_action_index == index));
        }
        for (&self.high_score_replay_button_states, 0..) |*state, index| {
            state.stepFor(
                .compact_score_row,
                high_scores_active and self.postLevelHighScoreContext() == null and self.highScoreReplayAvailable(index) and self.frontendButtonHot(hoverTargetForHighScoreReplay(index), false),
            );
        }
        for (&self.post_level_high_score_button_states, 0..) |*state, index| {
            state.stepFor(.footer_button, high_scores_active and self.postLevelHighScoreContext() != null and self.frontendButtonHot(hoverTargetForPostLevelHighScores(index), self.post_level_high_score_action_index == index));
        }
        const completion_active = self.game_phase == .completion_screen and !self.frontend_transition.blocksInput();
        self.completion_continue_button_state.stepFor(
            .menu_button,
            completion_active and self.frontendButtonHot(.completion_continue, true),
        );

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
        for (&self.options_button_states, 0..) |*state, index| {
            const item = options_menu_items[index];
            const hot = switch (item) {
                .sound_volume, .music_volume => blk: {
                    const active_target = self.activeFrontendButtonTarget();
                    break :blk self.game_phase == .options_menu and ((active_target != null and sliderHoverTargetBelongsToOptionsRow(active_target.?, item)) or (self.keyboard_frontend_focus_visible and self.options_menu_index == index));
                },
                else => self.game_phase == .options_menu and self.frontendButtonHot(hoverTargetForOptions(index), self.options_menu_index == index),
            };
            state.snapFor(.menu_button, hot);
        }
        for (&self.pause_menu_button_states, 0..) |*state, index| {
            state.snapFor(.menu_button, self.game_phase == .pause_menu and self.frontendButtonHot(hoverTargetForPauseMenu(index), self.pause_menu_index == index));
        }
        const route_map_card_open = self.routeMapCardIsOpen();
        self.route_map_button_states[route_map_primary_button_index].snapFor(
            .menu_button,
            self.game_phase == .route_map_menu and route_map_card_open and self.frontendButtonHot(hoverTargetForRouteMenuAction(.play), self.activeRouteMenuHotAction() == .play),
        );
        self.route_map_button_states[route_map_replay_button_index].snapFor(
            .route_map_secondary_action,
            self.game_phase == .route_map_menu and route_map_card_open and self.routeMapShowsReplay() and self.frontendButtonHot(hoverTargetForRouteMenuAction(.watch_best_trial), self.activeRouteMenuHotAction() == .watch_best_trial),
        );
        self.route_map_button_states[route_map_back_button_index].snapFor(
            .menu_button,
            self.game_phase == .route_map_menu and self.frontendButtonHot(hoverTargetForRouteMenuAction(.back), self.activeRouteMenuHotAction() == .back),
        );
        self.help_button_states[0].snapFor(.menu_button, self.game_phase == .help and self.frontendButtonHot(.help_back, true));
        for (&self.high_score_button_states, 0..) |*state, index| {
            state.snapFor(.footer_button, self.game_phase == .high_scores_menu and self.postLevelHighScoreContext() == null and self.frontendButtonHot(hoverTargetForHighScores(index), self.high_scores_action_index == index));
        }
        for (&self.high_score_replay_button_states, 0..) |*state, index| {
            state.snapFor(
                .compact_score_row,
                self.game_phase == .high_scores_menu and self.postLevelHighScoreContext() == null and self.highScoreReplayAvailable(index) and self.frontendButtonHot(hoverTargetForHighScoreReplay(index), false),
            );
        }
        for (&self.post_level_high_score_button_states, 0..) |*state, index| {
            state.snapFor(.footer_button, self.game_phase == .high_scores_menu and self.postLevelHighScoreContext() != null and self.frontendButtonHot(hoverTargetForPostLevelHighScores(index), self.post_level_high_score_action_index == index));
        }
        self.completion_continue_button_state.snapFor(
            .menu_button,
            self.game_phase == .completion_screen and self.frontendButtonHot(.completion_continue, true),
        );
        for (&self.exit_prompt_button_states, 0..) |*state, index| {
            state.snapFor(.menu_button, self.game_phase == .exit_prompt and self.frontendButtonHot(hoverTargetForExitPrompt(index), self.exit_prompt_choice_index == index));
        }
    }

    fn updateMainMenuMouseSelection(self: *AppState) !void {
        const local_mouse = self.currentFrontendMouseLocal() orelse {
            self.setFrontendHoverTarget(null);
            return;
        };
        var hovered_index: ?usize = null;

        for (main_menu_items, 0..) |item, index| {
            const text_rect = mainMenuTextRect(&self.ui_font, item);
            if (frontend_widget.hitRect(text_rect, self.main_menu_button_states[index]).contains(local_mouse)) {
                hovered_index = index;
            }
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

        for (new_game_menu_items[0..4], 0..) |item, index| {
            const text_rect = newGameMenuTextRect(&self.ui_font, item);
            if (frontend_widget.hitRect(text_rect, self.new_game_button_states[index]).contains(local_mouse)) {
                hovered_index = index;
            }
        }

        const help_rect = newGameHelpTextRect(&self.ui_font);
        if (frontend_widget.hitRect(help_rect, self.new_game_button_states[4]).contains(local_mouse)) {
            hovered_index = 4;
        }

        const back_rect = newGameBackTextRect(&self.ui_font);
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

        const fullscreen_rect = optionsTextRect(self, .fullscreen);
        if (frontend_widget.hitRect(fullscreen_rect, self.options_button_states[options_fullscreen_button_index]).contains(local_mouse)) {
            self.setFrontendHoverTarget(hoverTargetForOptions(0));
            self.options_menu_index = 0;
            if (rl.isMouseButtonPressed(.left)) {
                self.queueFrontendActivation(.{ .options_menu = .fullscreen });
            }
            return;
        }

        const sound_slider = optionsSliderLayout(self, .sound_volume);
        if (sound_slider.less_rect.contains(local_mouse)) {
            self.setFrontendHoverTarget(hoverTargetForOptionsSliderArrow(.sound_volume, .less));
            self.options_menu_index = 1;
            if (rl.isMouseButtonPressed(.left)) {
                try self.stepOptionsMenuValue(.sound_volume, -options_slider_adjust_step);
            }
            return;
        }
        if (sound_slider.more_rect.contains(local_mouse)) {
            self.setFrontendHoverTarget(hoverTargetForOptionsSliderArrow(.sound_volume, .more));
            self.options_menu_index = 1;
            if (rl.isMouseButtonPressed(.left)) {
                try self.stepOptionsMenuValue(.sound_volume, options_slider_adjust_step);
            }
            return;
        }
        if (sound_slider.frame_rect.contains(local_mouse)) {
            self.setFrontendHoverTarget(hoverTargetForOptions(1));
            self.options_menu_index = 1;
            return;
        }

        const music_slider = optionsSliderLayout(self, .music_volume);
        if (music_slider.less_rect.contains(local_mouse)) {
            self.setFrontendHoverTarget(hoverTargetForOptionsSliderArrow(.music_volume, .less));
            self.options_menu_index = 2;
            if (rl.isMouseButtonPressed(.left)) {
                try self.stepOptionsMenuValue(.music_volume, -options_slider_adjust_step);
            }
            return;
        }
        if (music_slider.more_rect.contains(local_mouse)) {
            self.setFrontendHoverTarget(hoverTargetForOptionsSliderArrow(.music_volume, .more));
            self.options_menu_index = 2;
            if (rl.isMouseButtonPressed(.left)) {
                try self.stepOptionsMenuValue(.music_volume, options_slider_adjust_step);
            }
            return;
        }
        if (music_slider.frame_rect.contains(local_mouse)) {
            self.setFrontendHoverTarget(hoverTargetForOptions(2));
            self.options_menu_index = 2;
            return;
        }

        const back_rect = optionsTextRect(self, .back);
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

    fn updatePauseMenuMouseSelection(self: *AppState) void {
        const local_mouse = self.currentFrontendMouseLocal() orelse {
            self.setFrontendHoverTarget(null);
            return;
        };
        var hovered_index: ?usize = null;

        for (pause_menu_items, 0..) |item, index| {
            const text_rect = pauseMenuTextRect(&self.ui_font, item);
            if (frontend_widget.hitRect(text_rect, self.pause_menu_button_states[index]).contains(local_mouse)) {
                hovered_index = index;
            }
        }

        if (hovered_index) |index| {
            self.setFrontendHoverTarget(hoverTargetForPauseMenu(index));
            self.pause_menu_index = index;
            if (rl.isMouseButtonPressed(.left)) {
                self.queueFrontendActivation(.{ .pause_menu = pause_menu_items[index] });
            }
        } else {
            self.setFrontendHoverTarget(null);
        }
    }

    fn updateRouteMapMouseSelection(self: *AppState) !void {
        const local_mouse = self.currentFrontendMouseLocal() orelse {
            self.route_map_hover_state = .none;
            self.route_map_hovered_index = null;
            self.setFrontendHoverTarget(null);
            return;
        };
        const mode = self.frontend_route_mode orelse {
            self.route_map_hover_state = .none;
            self.route_map_hovered_index = null;
            self.setFrontendHoverTarget(null);
            return;
        };

        const back_rect = routeMapBackTextRect(self);
        if (frontend_widget.hitRect(back_rect, self.route_map_button_states[route_map_back_button_index]).contains(local_mouse)) {
            self.route_map_hover_state = .none;
            self.route_map_hovered_index = null;
            self.setFrontendHoverTarget(hoverTargetForRouteMenuAction(.back));
            if (self.routeMenuActionIndexForAction(.back)) |index| {
                self.route_menu_action_index = index;
            }
            if (rl.isMouseButtonPressed(.left)) {
                self.queueFrontendActivation(.{ .route_map_menu = .back });
            }
            return;
        }

        const hovered_route_index = if (routeMapAllowsRouteSwitching(self.route_map_screen_mode))
            routeMapHoveredRouteIndex(self, local_mouse, self.availableFrontendRouteLimit(mode))
        else
            null;
        self.route_map_hover_state = if (hovered_route_index != null) .route else .none;
        self.route_map_hovered_index = hovered_route_index;

        if (self.currentRouteMapOpenIndex()) |route_index| {
            const route_galaxy_name = self.currentFrontendGalaxyName() orelse frontendRouteModeLabel(mode);
            const route_level_name = if (self.frontend_route_level) |loaded_level| loaded_level.name else "Route";
            const route_body = routeMapBodyText(if (self.frontend_route_level) |loaded_level| loaded_level.galaxy_text else null);
            if (routeMapPointForRouteIndex(self, route_index)) |route_point| {
                const card_layout = routeMapCardLayout(
                    &self.ui_font,
                    route_point,
                    route_galaxy_name,
                    route_level_name,
                    route_body,
                    routeMenuActionLabel(mode, .play),
                    if (self.routeMapShowsReplay()) routeMenuActionLabel(mode, .watch_best_trial) else null,
                );

                if (frontend_widget.hitRect(card_layout.primary_text_rect, self.route_map_button_states[route_map_primary_button_index]).contains(local_mouse)) {
                    self.route_map_hover_state = .card;
                    self.route_map_hovered_index = null;
                    self.setFrontendHoverTarget(hoverTargetForRouteMenuAction(.play));
                    if (self.routeMenuActionIndexForAction(.play)) |index| {
                        self.route_menu_action_index = index;
                    }
                    if (rl.isMouseButtonPressed(.left)) {
                        self.queueFrontendActivation(.{ .route_map_menu = .play });
                    }
                    return;
                }

                if (card_layout.replay_text_rect) |replay_rect| {
                    if (frontend_widget.hitRect(replay_rect, self.route_map_button_states[route_map_replay_button_index]).contains(local_mouse)) {
                        self.route_map_hover_state = .card;
                        self.route_map_hovered_index = null;
                        self.setFrontendHoverTarget(hoverTargetForRouteMenuAction(.watch_best_trial));
                        if (self.routeMenuActionIndexForAction(.watch_best_trial)) |index| {
                            self.route_menu_action_index = index;
                        }
                        if (rl.isMouseButtonPressed(.left)) {
                            self.queueFrontendActivation(.{ .route_map_menu = .watch_best_trial });
                        }
                        return;
                    }
                }

                if (card_layout.card_rect.contains(local_mouse)) {
                    self.route_map_hover_state = .card;
                    self.route_map_hovered_index = null;
                    self.setFrontendHoverTarget(null);
                    return;
                }
            }
        }

        if (hovered_route_index) |route_index| {
            self.setFrontendHoverTarget(null);
            if (rl.isMouseButtonPressed(.left) and self.currentRouteMapOpenIndex() != route_index) {
                try self.openFrontendRouteCard(route_index);
                self.playFrontendSelectSound();
            }
            return;
        }

        if (self.routeMapCanCloseCard() and rl.isMouseButtonPressed(.left)) {
            self.closeFrontendRouteCard();
            self.playFrontendSelectSound();
            self.setFrontendHoverTarget(null);
            return;
        }

        self.setFrontendHoverTarget(null);
    }

    fn updateHelpMouseSelection(self: *AppState) void {
        const local_mouse = self.currentFrontendMouseLocal() orelse {
            self.setFrontendHoverTarget(null);
            return;
        };

        const back_rect = helpBackTextRect(&self.ui_font);
        if (frontend_widget.hitRect(back_rect, self.help_button_states[0]).contains(local_mouse)) {
            self.setFrontendHoverTarget(.help_back);
            if (rl.isMouseButtonPressed(.left)) {
                self.queueFrontendActivation(.{ .help_menu = .back });
            }
            return;
        }

        self.setFrontendHoverTarget(null);
    }

    fn highScoreReplayAvailable(self: *const AppState, entry_index: usize) bool {
        const selected_mode = high_score_screen_modes[@min(self.high_scores_menu_index, high_score_screen_modes.len - 1)];
        if (!highScoreRowsShowReplay(selected_mode, self.postLevelHighScoreContext() != null)) return false;
        const entries = self.high_score_tables.visibleEntries(selected_mode);
        return entry_index < entries.len and entries[entry_index].has_replay;
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
            const selected_mode = high_score_screen_modes[@min(self.high_scores_menu_index, high_score_screen_modes.len - 1)];
            const entries = self.high_score_tables.visibleEntries(selected_mode);
            if (highScoreRowsShowReplay(selected_mode, false)) {
                for (entries, 0..) |entry, entry_index| {
                    if (!entry.has_replay) continue;
                    const replay_rect = highScoreReplayTextRect(self, selected_mode, high_score_row_start_y + @as(f32, @floatFromInt(entry_index)) * high_score_row_pitch);
                    if (frontend_widget.hitRect(replay_rect, self.high_score_replay_button_states[entry_index]).contains(local_mouse)) {
                        self.setFrontendHoverTarget(hoverTargetForHighScoreReplay(entry_index));
                        if (rl.isMouseButtonPressed(.left)) {
                            self.queueFrontendActivation(.{ .high_score_replay = entry_index });
                        }
                        return;
                    }
                }
            }

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

    fn updateCompletionScreenMouseSelection(self: *AppState) void {
        const result = self.pending_run_result orelse {
            self.setFrontendHoverTarget(null);
            return;
        };
        const local_mouse = self.currentFrontendMouseLocal() orelse {
            self.setFrontendHoverTarget(null);
            return;
        };
        const continue_rect = completionContinueTextRect(&self.ui_font, result);
        if (frontend_widget.hitRect(continue_rect, self.completion_continue_button_state).contains(local_mouse)) {
            self.setFrontendHoverTarget(.completion_continue);
            if (rl.isMouseButtonPressed(.left)) {
                self.queueFrontendActivation(.{ .completion_screen = .continue_flow });
            }
            return;
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

    fn handleGameInput(self: *AppState) !void {
        if (rl.isKeyPressed(.escape)) {
            switch (self.game_phase) {
                .level => try self.enterPauseMenu(),
                .boot => self.should_exit = true,
                .main_menu => try self.beginExitPrompt(.main_menu),
                .intro, .credits => self.frontend_transition.beginFadeOut(.main_menu),
                .new_game_menu, .help => try self.enterGamePhase(.main_menu),
                .high_scores_menu => if (self.postLevelHighScoreContext() != null)
                    try self.cancelPostLevelHighScoreEntry()
                else
                    try self.enterGamePhase(.main_menu),
                .options_menu => try self.leaveOptionsMenu(),
                .pause_menu => try self.resumeFromPauseMenu(),
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
                    self.noteFrontendKeyboardNavigation();
                }
                if (rl.isKeyPressed(.down)) {
                    self.menu_index = wrappedIndex(main_menu_items.len, self.menu_index, 1);
                    self.noteFrontendKeyboardNavigation();
                }
                if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    self.queueFrontendActivation(.{ .main_menu = main_menu_items[self.menu_index] });
                }
            },
            .new_game_menu => {
                try self.updateNewGameMenuMouseSelection();
                if (rl.isKeyPressed(.up)) {
                    self.new_game_menu_index = wrappedIndex(new_game_menu_items.len, self.new_game_menu_index, -1);
                    self.noteFrontendKeyboardNavigation();
                }
                if (rl.isKeyPressed(.down)) {
                    self.new_game_menu_index = wrappedIndex(new_game_menu_items.len, self.new_game_menu_index, 1);
                    self.noteFrontendKeyboardNavigation();
                }
                if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    self.queueFrontendActivation(.{ .new_game_menu = new_game_menu_items[self.new_game_menu_index] });
                }
            },
            .options_menu => {
                try self.updateOptionsMouseSelection();
                if (rl.isKeyPressed(.up)) {
                    self.options_menu_index = wrappedIndex(options_menu_items.len, self.options_menu_index, -1);
                    self.noteFrontendKeyboardNavigation();
                }
                if (rl.isKeyPressed(.down)) {
                    self.options_menu_index = wrappedIndex(options_menu_items.len, self.options_menu_index, 1);
                    self.noteFrontendKeyboardNavigation();
                }

                const selected = options_menu_items[self.options_menu_index];
                if (rl.isKeyPressed(.left) or rl.isKeyPressed(.a)) {
                    self.noteFrontendKeyboardNavigation();
                    try self.stepOptionsMenuValue(selected, -options_slider_adjust_step);
                }
                if (rl.isKeyPressed(.right) or rl.isKeyPressed(.d)) {
                    self.noteFrontendKeyboardNavigation();
                    try self.stepOptionsMenuValue(selected, options_slider_adjust_step);
                }
                if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    switch (selected) {
                        .fullscreen, .back => self.queueFrontendActivation(.{ .options_menu = selected }),
                        .sound_volume, .music_volume => {},
                    }
                }
            },
            .pause_menu => {
                self.updatePauseMenuMouseSelection();
                if (rl.isKeyPressed(.up)) {
                    self.pause_menu_index = wrappedIndex(pause_menu_items.len, self.pause_menu_index, -1);
                    self.noteFrontendKeyboardNavigation();
                }
                if (rl.isKeyPressed(.down)) {
                    self.pause_menu_index = wrappedIndex(pause_menu_items.len, self.pause_menu_index, 1);
                    self.noteFrontendKeyboardNavigation();
                }
                if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    self.queueFrontendActivation(.{ .pause_menu = pause_menu_items[self.pause_menu_index] });
                }
            },
            .route_map_menu => {
                try self.updateRouteMapMouseSelection();
                const route_actions = self.activeRouteMenuActions();
                if (rl.isKeyPressed(.up)) {
                    self.route_menu_action_index = wrappedIndex(route_actions.len, self.route_menu_action_index, -1);
                    self.noteFrontendKeyboardNavigation();
                }
                if (rl.isKeyPressed(.down)) {
                    self.route_menu_action_index = wrappedIndex(route_actions.len, self.route_menu_action_index, 1);
                    self.noteFrontendKeyboardNavigation();
                }
                if (routeMapAllowsRouteSwitching(self.route_map_screen_mode) and rl.isKeyPressed(.left)) {
                    self.noteFrontendKeyboardNavigation();
                    try self.stepFrontendRouteSelection(-1);
                }
                if (routeMapAllowsRouteSwitching(self.route_map_screen_mode) and rl.isKeyPressed(.right)) {
                    self.noteFrontendKeyboardNavigation();
                    try self.stepFrontendRouteSelection(1);
                }
                if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    self.queueFrontendActivation(.{ .route_map_menu = route_actions[self.route_menu_action_index] });
                }
                self.syncRouteMapHighlightTargets();
                self.stepRouteMapHighlightAnimations();
            },
            .high_scores_menu => {
                try self.updateHighScoresMouseSelection();
                if (self.postLevelHighScoreContext() != null) {
                    self.collectPostLevelHighScoreTextInput();
                    if (rl.isKeyPressed(.up) or rl.isKeyPressed(.left)) {
                        self.post_level_high_score_action_index = wrappedIndex(post_level_high_score_actions.len, self.post_level_high_score_action_index, -1);
                        self.noteFrontendKeyboardNavigation();
                    }
                    if (rl.isKeyPressed(.down) or rl.isKeyPressed(.right)) {
                        self.post_level_high_score_action_index = wrappedIndex(post_level_high_score_actions.len, self.post_level_high_score_action_index, 1);
                        self.noteFrontendKeyboardNavigation();
                    }
                    if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                        self.queueFrontendActivation(.{ .post_level_high_scores = post_level_high_score_actions[self.post_level_high_score_action_index] });
                    }
                } else {
                    if (rl.isKeyPressed(.up) or rl.isKeyPressed(.left)) {
                        self.high_scores_action_index = wrappedIndex(high_score_menu_actions.len, self.high_scores_action_index, -1);
                        self.noteFrontendKeyboardNavigation();
                    }
                    if (rl.isKeyPressed(.down) or rl.isKeyPressed(.right)) {
                        self.high_scores_action_index = wrappedIndex(high_score_menu_actions.len, self.high_scores_action_index, 1);
                        self.noteFrontendKeyboardNavigation();
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
                    self.noteFrontendKeyboardNavigation();
                }
                if (rl.isKeyPressed(.down) or rl.isKeyPressed(.right)) {
                    self.exit_prompt_choice_index = wrappedIndex(exit_prompt_choices.len, self.exit_prompt_choice_index, 1);
                    self.noteFrontendKeyboardNavigation();
                }
                if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    self.queueFrontendActivation(.{ .exit_prompt = exit_prompt_choices[self.exit_prompt_choice_index] });
                }
            },
            .completion_screen => {
                self.updateCompletionScreenMouseSelection();
                if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    self.noteFrontendKeyboardNavigation();
                    self.queueFrontendActivation(.{ .completion_screen = .continue_flow });
                }
            },
            .credits => {
                if (rl.isMouseButtonPressed(.left)) {
                    self.frontend_transition.beginFadeOut(.main_menu);
                }
            },
            .help => {
                self.updateHelpMouseSelection();
                if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    self.queueFrontendActivation(.{ .help_menu = .back });
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
                    try self.enterPauseMenu();
                    return;
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
        self.keyboard_frontend_focus_visible = false;
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
            .high_scores_menu,
            .help,
            .credits,
            => try self.enterGamePhase(phase),
            .options_menu => {
                if (self.start_pause_context) {
                    try self.loadGameLevel(default_level_path);
                    self.options_return_phase = .pause_menu;
                } else {
                    self.options_return_phase = .main_menu;
                }
                try self.enterGamePhase(.options_menu);
            },
            .pause_menu => {
                try self.enterGameplayShell(default_level_path);
                try self.enterPauseMenu();
            },
            .exit_prompt => {
                if (self.start_pause_context) {
                    try self.loadGameLevel(default_level_path);
                    try self.beginEndGamePrompt(.pause_menu);
                } else {
                    try self.beginExitPrompt(.main_menu);
                }
            },
            .route_map_menu => try self.enterRouteMapMenu(.postal),
            .level => try self.enterGameplayShell(default_level_path),
            .completion_screen => {
                try self.loadGameLevel(default_level_path);
                self.active_frontend_mode = .postal;
                self.active_frontend_level_index = 1;
                self.pending_run_result = .{
                    .outcome = .completed,
                    .level_name = "Snail Mail 101",
                    .mode = .postal,
                    .elapsed_millis = 62_340,
                    .parcel_count = 1,
                    .parcel_target = 1,
                    .score = 50_300,
                    .score_is_partial = true,
                    .score_totals = .{
                        .parcel_pickup = 100,
                        .parcel_register = 100,
                        .completion_bonus = 50_000,
                        .total = 50_300,
                    },
                    .visible_life_stock = 3,
                    .return_target = .postal_route_map,
                };
                try self.enterGamePhase(.completion_screen);
            },
        }
    }

    fn performMainMenuItem(self: *AppState, item: MainMenuItem) !void {
        switch (item) {
            .new_game => try self.enterGamePhase(.new_game_menu),
            .high_scores => {
                self.high_scores_action_index = 1;
                try self.enterGamePhase(.high_scores_menu);
            },
            .options => {
                self.options_return_phase = .main_menu;
                try self.enterGamePhase(.options_menu);
            },
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

    fn performPauseMenuItem(self: *AppState, item: PauseMenuItem) !void {
        switch (item) {
            .end_game => try self.beginEndGamePrompt(.pause_menu),
            .options => {
                self.options_return_phase = .pause_menu;
                try self.enterGamePhase(.options_menu);
            },
            .@"resume" => try self.resumeFromPauseMenu(),
        }
    }

    fn performHelpMenuItem(self: *AppState, item: HelpMenuAction) !void {
        switch (item) {
            .back => try self.returnToNewGameMenu(.help),
        }
    }

    fn activateOptionsMenuItem(self: *AppState, item: OptionsMenuItem) !void {
        self.playFrontendSelectSound();
        try self.performOptionsMenuItem(item);
    }

    fn beginExitPrompt(self: *AppState, return_phase: GamePhase) !void {
        self.exit_prompt_choice_index = 1;
        self.exit_prompt_return_phase = return_phase;
        self.exit_prompt_mode = .quit_app;
        try self.enterGamePhase(.exit_prompt);
    }

    fn beginEndGamePrompt(self: *AppState, return_phase: GamePhase) !void {
        self.exit_prompt_choice_index = 1;
        self.exit_prompt_return_phase = return_phase;
        self.exit_prompt_mode = .abandon_run;
        try self.enterGamePhase(.exit_prompt);
    }

    // PORT(verified): the special postal-return Star Map mode (`initialize_galaxy` with
    // `this + 4 == 1`) routes its bottom `Exit` control through the shared exit-prompt
    // controller before returning to the outer front-end flow.
    fn beginRouteMapExitPrompt(self: *AppState) !void {
        self.exit_prompt_choice_index = 1;
        self.exit_prompt_return_phase = .route_map_menu;
        self.exit_prompt_mode = .leave_route_map;
        try self.enterGamePhase(.exit_prompt);
    }

    fn performExitPromptChoice(self: *AppState, choice: ExitPromptChoice) !void {
        switch (choice) {
            .no => try self.enterGamePhase(self.exit_prompt_return_phase),
            .yes => switch (self.exit_prompt_mode) {
                .quit_app => self.should_exit = true,
                .abandon_run => try self.abandonActiveRun(),
                .leave_route_map => try self.returnToNewGameMenu(.route_map_menu),
            },
        }
    }

    fn activateExitPromptChoice(self: *AppState, choice: ExitPromptChoice) !void {
        self.playFrontendSelectSound();
        try self.performExitPromptChoice(choice);
    }

    fn performRouteMenuAction(self: *AppState, action: RouteMenuAction) !void {
        switch (action) {
            .play => try self.enterSelectedFrontendRoute(),
            .watch_best_trial => self.setGameStatusMessage("Best-trial replay playback is not ported."),
            .back => if (self.route_map_screen_mode == .post_completion_exit)
                try self.beginRouteMapExitPrompt()
            else
                try self.returnToNewGameMenu(.route_map_menu),
        }
    }

    fn performCompletionAction(self: *AppState, action: CompletionAction) !void {
        switch (action) {
            .continue_flow => try self.continueCompletionScreen(),
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

    fn performHighScoreReplay(self: *AppState, entry_index: usize) !void {
        if (!self.highScoreReplayAvailable(entry_index)) return;
        self.setGameStatusMessage("High-score replay playback is not ported.");
    }

    fn activateHighScoreMenuAction(self: *AppState, action: HighScoreMenuAction) !void {
        self.playFrontendSelectSound();
        try self.performHighScoreMenuAction(action);
    }

    fn enterPauseMenu(self: *AppState) !void {
        self.pause_menu_index = 0;
        try self.enterGamePhase(.pause_menu);
    }

    fn resumeFromPauseMenu(self: *AppState) !void {
        try self.enterGamePhase(.level);
    }

    fn abandonActiveRun(self: *AppState) !void {
        self.pending_run_result = null;
        self.clearPostLevelHighScoreEntry();

        if (self.active_frontend_mode) |mode| {
            switch (mode) {
                .postal => return self.enterRouteMapMenu(.postal),
                .time_trial => return self.enterRouteMapMenu(.time_trial),
                .challenge, .tutorial => {},
            }
        }

        self.active_frontend_mode = null;
        self.active_frontend_level_index = 0;
        try self.enterGamePhase(.main_menu);
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
        try self.enterGamePhase(self.options_return_phase);
    }

    // PORT(verified): `update_help` writes frontend state `2` on Back, and the frontend
    // state machine handles that by rebuilding the New Game screen/controller path rather than
    // jumping straight to the main menu. The normal Star Map `update_galaxy -> return 3`
    // path in `update_subgame` also tears down the galaxy screen and returns to the New Game
    // flow. Preserve that return target in the port instead of routing Help/Star Map Back to
    // the main menu.
    fn returnToNewGameMenu(self: *AppState, from_phase: GamePhase) !void {
        switch (from_phase) {
            .help => self.new_game_menu_index = newGameMenuIndexForItem(.help),
            .route_map_menu => {
                if (self.frontend_route_mode) |mode| {
                    self.new_game_menu_index = newGameMenuIndexForItem(newGameMenuItemForFrontendMode(mode));
                }
            },
            else => {},
        }
        try self.enterGamePhase(.new_game_menu);
    }

    fn enterFrontendLevelMode(self: *AppState, mode: FrontendLevelMode) !void {
        switch (mode) {
            .postal, .time_trial => try self.enterRouteMapMenu(mode),
            .challenge, .tutorial => try self.enterFrontendLevelPath(mode, 0),
        }
    }

    fn enterRouteMapMenu(self: *AppState, mode: FrontendLevelMode) !void {
        try self.enterRouteMapMenuWithScreenMode(mode, defaultRouteMapScreenMode(mode));
    }

    fn enterRouteMapMenuWithScreenMode(self: *AppState, mode: FrontendLevelMode, screen_mode: RouteMapScreenMode) !void {
        self.frontend_route_mode = mode;
        self.route_map_screen_mode = screen_mode;
        self.frontend_route_index = self.initialFrontendRouteIndex(mode);
        if (self.start_route_index_override) |override| {
            const highest_available = self.highestAvailableFrontendRouteIndex(mode);
            if (highest_available > 0) {
                self.frontend_route_index = std.math.clamp(override, @as(usize, 1), highest_available);
            }
            self.start_route_index_override = null;
        }
        try self.openFrontendRouteCard(self.frontend_route_index);
        self.resetRouteMapHighlightAnimations();
        self.syncRouteMapHighlightTargets();
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
        return names.nameForRouteIndex(self.currentRouteMapOpenIndex() orelse self.frontend_route_index);
    }

    fn routeMapShowsReplay(self: *const AppState) bool {
        // PORT(verified): `open_galaxy_route` only reveals "Watch Best Trial" when the Star
        // Map is in internal mode `2` and the route's completion slot has replay data.
        if (self.route_map_screen_mode != .replay) return false;
        const route_index = self.currentRouteMapOpenIndex() orelse return false;
        return routeMapHasReplayEntry(self.frontend_route_mode, route_index, &self.high_score_tables);
    }

    fn routeMapCardIsOpen(self: *const AppState) bool {
        return self.route_map_open_index != null;
    }

    // PORT(verified): `open_galaxy_route` stores the active route index at `this + 69504`,
    // while `close_galaxy_route` clears that slot back to `-1`. Model the open-card route
    // separately instead of assuming the saved/default route is always the open one.
    fn currentRouteMapOpenIndex(self: *const AppState) ?usize {
        return self.route_map_open_index;
    }

    // PORT(verified): the late `update_galaxy` close-card branch only fires when the
    // open-route flag is set and the authored route count is greater than `1`
    // (`dword_4DF9B8 > 1`). Preserve that gate so the first available route stays pinned
    // open instead of letting the user dismiss the card into an empty Star Map.
    fn routeMapCanCloseCard(self: *const AppState) bool {
        if (!self.routeMapCardIsOpen()) return false;
        if (!routeMapAllowsRouteSwitching(self.route_map_screen_mode)) return false;
        const mode = self.frontend_route_mode orelse return false;
        return self.availableFrontendRouteLimit(mode) > 1;
    }

    fn openFrontendRouteCard(self: *AppState, route_index: usize) !void {
        self.route_map_open_index = route_index;
        self.route_map_hover_state = .none;
        self.route_map_hovered_index = null;
        self.frontend_route_index = route_index;
        self.syncRouteMapHighlightTargets();
        try self.reloadFrontendRouteLevel();
        if (self.routeMenuActionIndexForAction(.play)) |index| {
            self.route_menu_action_index = index;
        } else {
            self.route_menu_action_index = 0;
        }
    }

    fn closeFrontendRouteCard(self: *AppState) void {
        self.route_map_open_index = null;
        self.route_map_hover_state = .none;
        self.route_map_hovered_index = null;
        self.route_menu_action_index = 0;
        self.syncRouteMapHighlightTargets();
    }

    fn resetRouteMapHighlightAnimations(self: *AppState) void {
        @memset(&self.route_map_route_highlight_alpha, 0.0);
        @memset(&self.route_map_route_highlight_target, 0.0);
    }

    // PORT(verified): `update_galaxy` ticks each route entry through `sub_409BD0`, which
    // eases the current highlight alpha at `+40` toward the target at `+44` with a `0.1`
    // step. The target is `1.0` for the hovered route in hover state `2`, otherwise for the
    // open route while the card is up.
    fn syncRouteMapHighlightTargets(self: *AppState) void {
        @memset(&self.route_map_route_highlight_target, 0.0);
        const highlighted_route_index = switch (self.route_map_hover_state) {
            .route => self.route_map_hovered_index,
            .card, .none => self.currentRouteMapOpenIndex(),
        } orelse return;
        if (highlighted_route_index < self.route_map_route_highlight_target.len) {
            self.route_map_route_highlight_target[highlighted_route_index] = 1.0;
        }
    }

    fn stepRouteMapHighlightAnimations(self: *AppState) void {
        for (1..self.route_map_route_highlight_alpha.len) |route_index| {
            const current = self.route_map_route_highlight_alpha[route_index];
            const target = self.route_map_route_highlight_target[route_index];
            self.route_map_route_highlight_alpha[route_index] = current + (target - current) * 0.1;
        }
    }

    // PORT(verified): `update_galaxy` and `close_galaxy_route` gate the Star Map card actions
    // on the route-open flag at `this + 8`. When the card is closed, only the absolute Back
    // control remains actionable; Play and Watch Best Trial are hidden until `open_galaxy_route`.
    fn activeRouteMenuActions(self: *const AppState) []const RouteMenuAction {
        if (!self.routeMapCardIsOpen()) return &route_menu_actions_closed;
        return if (self.routeMapShowsReplay())
            &route_menu_actions_with_replay
        else
            &route_menu_actions_without_replay;
    }

    fn activeRouteMenuHotAction(self: *const AppState) RouteMenuAction {
        const actions = self.activeRouteMenuActions();
        return actions[@min(self.route_menu_action_index, actions.len - 1)];
    }

    fn routeMenuActionIndexForAction(self: *const AppState, action: RouteMenuAction) ?usize {
        for (self.activeRouteMenuActions(), 0..) |candidate, index| {
            if (candidate == action) return index;
        }
        return null;
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
        try self.enterFrontendLevelPath(mode, self.currentRouteMapOpenIndex() orelse self.frontend_route_index);
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
                // PORT(verified): normal postal completion uses `complete_subgame(..., 0)`,
                // not the arcade-high-score commit path. Only the last postal route upgrades
                // to `complete_subgame(..., 1)`, so keep postal score insertion gated on the
                // final shipped route instead of every completed delivery.
                if (postalCompletionCommitsHighScore(
                    self.active_frontend_level_index,
                    self.highestAvailableFrontendRouteIndex(.postal),
                )) {
                    const entry = high_score.Entry{
                        .score = result.score,
                        .replay_level_index = @intCast(self.active_frontend_level_index),
                    };
                    const insert = self.high_score_tables.addArcade(self.allocator, entry);
                    result.high_score_mode = .postal;
                    result.high_score_rank = insert.rank;
                }
                result.unlocked_next_route = try self.commitPostalRouteProgress();
                try self.saveHighScoreTables();
            },
            .challenge => {
                result.score = runner.score.total;
                result.score_is_partial = true;

                const entry = high_score.Entry{
                    .score = result.score,
                    .replay_level_index = @intCast(self.active_frontend_level_index),
                };
                const insert = self.high_score_tables.addSurvival(self.allocator, entry);
                result.high_score_mode = .challenge;
                result.high_score_rank = insert.rank;
                try self.saveHighScoreTables();
            },
            .time_trial => {
                result.score = elapsed_millis;
                const entry = high_score.Entry{
                    .score = elapsed_millis,
                    .replay_level_index = @intCast(self.active_frontend_level_index),
                };
                const insert = self.high_score_tables.addTimeTrial(self.allocator, self.active_frontend_level_index, entry, true);
                result.time_trial_record_improved = insert.improved;
                try self.saveHighScoreTables();
            },
            .tutorial => {},
        }

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
                    .replay_level_index = @intCast(self.active_frontend_level_index),
                };
                const insert = self.high_score_tables.addArcade(self.allocator, entry);
                result.high_score_mode = .postal;
                result.high_score_rank = insert.rank;
                try self.saveHighScoreTables();
            },
            .challenge => {
                result.score = runner.score.total;
                const entry = high_score.Entry{
                    .score = result.score,
                    .replay_level_index = @intCast(self.active_frontend_level_index),
                };
                const insert = self.high_score_tables.addSurvival(self.allocator, entry);
                result.high_score_mode = .challenge;
                result.high_score_rank = insert.rank;
                try self.saveHighScoreTables();
            },
            .time_trial => {
                // PORT(verified): `add_time_trial_high_score(..., success_flag)` only copies
                // failed runs into scratch memory. It does not replace the persistent ScoreC
                // route record unless the run completed successfully.
                result.score = elapsed_millis;
                _ = self.high_score_tables.addTimeTrial(
                    self.allocator,
                    self.active_frontend_level_index,
                    .{
                        .score = elapsed_millis,
                        .replay_level_index = @intCast(self.active_frontend_level_index),
                    },
                    false,
                );
            },
            .tutorial => {
                result.score = runner.score.total;
            },
        }

        self.pending_run_result = result;
        try self.enterGamePhase(.completion_screen);
    }

    fn beginRespawnRun(self: *AppState) !void {
        const previous_runner = self.level_runner orelse return;
        const preserved_session_mode = previous_runner.session_mode;
        const preserved_score = previous_runner.score;
        // PORT(verified): `update_subgoldy_resurrect` decrements visible lives only on the
        // committed postal respawn branch, after fade completion. Keep that decrement at the
        // app-side rebuild handoff instead of consuming it inside the runner.
        const preserved_visible_life_stock = switch (previous_runner.session_mode) {
            .postal => previous_runner.visible_life_stock -| 1,
            .challenge, .time_trial, .tutorial, .debug => previous_runner.visible_life_stock,
        };
        const preserved_tick_count = previous_runner.tick_count;
        const preserved_stopwatch = previous_runner.stopwatch;

        try self.reloadLevel();
        if (self.level_runner) |*runner| {
            runner.session_mode = preserved_session_mode;
            runner.score = preserved_score;
            runner.visible_life_stock = preserved_visible_life_stock;
            runner.tick_count = preserved_tick_count;
            runner.stopwatch = preserved_stopwatch;
        }
        self.clearLevelPromptQueue();
        try self.syncActiveLevelSegment(false);
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

        switch (result.return_target) {
            .main_menu => try self.enterGamePhase(.main_menu),
            // PORT(verified): Windows re-enters the postal Star Map through the special
            // `initialize_galaxy` mode `1` after a completed route. That path keeps the
            // current route card open and relabels the bottom control to `Exit`.
            .postal_route_map => try self.enterRouteMapMenuWithScreenMode(.postal, .post_completion_exit),
            .time_trial_route_map => try self.enterRouteMapMenu(.time_trial),
            .replay_current_level => if (result.mode) |mode|
                try self.enterFrontendLevelPath(mode, self.active_frontend_level_index)
            else
                try self.enterGamePhase(.main_menu),
        }
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
        if (highest_available == 0) return false;
        return current_index >= highest_available;
    }

    fn nextPostalUnlockLimit(current_index: usize, highest_available: usize, saved_limit: usize) usize {
        if (highest_available == 0) return 0;
        const clamped_saved = std.math.clamp(saved_limit, @as(usize, 1), highest_available);
        const clamped_current = std.math.clamp(current_index, @as(usize, 1), highest_available);
        if (clamped_current < highest_available) {
            return @max(clamped_saved, clamped_current + 1);
        }
        return clamped_saved;
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
        const next_route_index = wrappedIndex(route_count, self.frontend_route_index - 1, delta) + 1;
        try self.openFrontendRouteCard(next_route_index);
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
            .main_menu, .new_game_menu, .high_scores_menu => {
                self.active_level_segment_index = null;
                self.clearLevelPromptQueue();
                self.mouse_level_lane_target = null;
                self.unloadTextScript();
                self.unloadLoadingScreen();
                try self.loadGameBackground(main_menu_background_path);
                try self.playMusicByPath(default_audio_path);
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
                    try self.playMusicByPath(default_audio_path);
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
                    try self.playMusicByPath(default_audio_path);
                } else {
                    self.active_level_segment_index = null;
                    self.clearLevelPromptQueue();
                    self.mouse_level_lane_target = null;
                    try self.loadGameBackground(main_menu_background_path);
                    try self.playMusicByPath(default_audio_path);
                }
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
            try self.loadConfiguredTextScriptEntry(path);
    }

    fn loadConfiguredTextScriptEntry(self: *AppState, path: []const u8) !intro.Loaded {
        if (std.ascii.eqlIgnoreCase(path, credits_script_path)) {
            return try intro.loadByPathWithOptions(
                self.allocator,
                &self.catalog,
                path,
                .{ .add_remake_credit = self.credits_with_remake },
            );
        }
        return try intro.loadByPath(self.allocator, &self.catalog, path);
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
                self.runtime_config.setMusicVolume(self.runtime_config.musicVolume() + delta);
                self.applyAudioConfigVolumes();
            },
            .back => if (delta != 0.0) {
                self.playFrontendSelectSound();
                try self.leaveOptionsMenu();
            },
        }
    }

    fn stepOptionsSliderDisplay(current: f32, target: f32) f32 {
        const next = current + (target - current) * options_slider_display_lerp;
        if (@abs(target - next) < 0.001) return target;
        return next;
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

        var screenshot = if (self.command == .game and frontendPhaseUsesCanvas(self) and self.frontend_canvas != null)
            try rl.loadImageFromTexture(self.frontend_canvas.?.texture)
        else
            try rl.loadImageFromScreen();
        defer screenshot.unload();
        if (self.command == .game and frontendPhaseUsesCanvas(self) and self.frontend_canvas != null) {
            screenshot.flipVertical();
        }
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
            .segments => {
                self.segment_index = wrappedIndex(self.catalog.segment_entries.len, self.segment_index, delta);
                try self.reloadStandaloneSegment();
            },
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

        self.current_model = try x2.Uploaded.loadFromArchive(
            self.allocator,
            &self.catalog,
            entry,
            self.model_flip_v,
        );
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

    fn reloadStandaloneSegment(self: *AppState) !void {
        if (self.current_standalone_segment_scene) |*scene| {
            scene.deinit();
            self.current_standalone_segment_scene = null;
        }
        if (self.current_standalone_segment_preview) |*loaded_track_preview| {
            loaded_track_preview.deinit();
            self.current_standalone_segment_preview = null;
        }
        if (self.catalog.segment_entries.len == 0) return;
        if (self.segment_index >= self.catalog.segment_entries.len) {
            self.segment_index = self.catalog.segment_entries.len - 1;
        }

        const entry = self.catalog.segment_entries[self.segment_index];
        self.current_standalone_segment_preview = try track.LoadedLevelPreview.loadStandaloneSegment(
            self.allocator,
            &self.catalog,
            entry,
        );
        try self.reloadStandaloneSegmentScene();
    }

    fn reloadStandaloneSegmentScene(self: *AppState) !void {
        if (self.current_standalone_segment_scene) |*scene| {
            scene.deinit();
            self.current_standalone_segment_scene = null;
        }
        _ = self.current_standalone_segment_preview orelse return;
        self.current_standalone_segment_scene = try track_render.Scene.buildStandaloneSegmentScene(
            self.allocator,
            &self.catalog,
            self.segment_track_set_index,
        );
    }

    fn activeModel(self: *const AppState) ?*const x2.Uploaded {
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

fn phaseUsesGameplayBackdrop(state: *const AppState) bool {
    return switch (state.game_phase) {
        .pause_menu => true,
        .options_menu => state.options_return_phase == .pause_menu,
        .exit_prompt => state.exit_prompt_return_phase == .pause_menu,
        else => false,
    };
}

fn frontendPhaseUsesCanvas(state: *const AppState) bool {
    if (phaseUsesGameplayBackdrop(state)) return false;
    return switch (state.game_phase) {
        .main_menu,
        .new_game_menu,
        .options_menu,
        .route_map_menu,
        .high_scores_menu,
        .exit_prompt,
        .completion_screen,
        .help,
        => true,
        .boot, .intro, .credits, .pause_menu, .level => false,
    };
}

fn drawGamePhaseContents(state: *const AppState, bounds: rl.Rectangle, ui_layout: VirtualLayout) !void {
    if (phaseUsesGameplayBackdrop(state)) {
        drawGameplayLevelViewport(state);
    } else if (state.current_game_background) |loaded_background| {
        if (state.current_game_background_runtime) |runtime| {
            switch (state.game_phase) {
                .intro, .credits => runtime.drawStretched(&loaded_background, bounds),
                else => _ = runtime.draw(&loaded_background, bounds),
            }
        } else {
            _ = loaded_background.draw(bounds);
        }
    } else {
        rl.drawRectangleRec(bounds, .black);
    }

    switch (state.game_phase) {
        .boot => unreachable,
        .intro => drawCurrentTextScript(state, ui_layout),
        .main_menu => try drawMainMenuUi(state, ui_layout),
        .new_game_menu => try drawNewGameMenuUi(state, ui_layout),
        .options_menu => try drawOptionsMenuUi(state, ui_layout),
        .pause_menu => try drawPauseMenuUi(state, ui_layout),
        .route_map_menu => try drawRouteMapMenuUi(state, ui_layout),
        .high_scores_menu => try drawHighScoresMenuUi(state, ui_layout),
        .exit_prompt => try drawExitPromptUi(state, ui_layout),
        .completion_screen => try drawCompletionScreenUi(state, ui_layout),
        .credits => drawCurrentTextScript(state, ui_layout),
        .help => drawHelpUi(state, ui_layout),
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
    const ui_layout = app_ui.virtualLayout(full_bounds);

    if (state.game_phase == .boot) {
        if (state.current_loading_screen) |loaded_screen| {
            loaded_screen.draw(full_bounds, bootPhaseProgress(state));
        } else {
            rl.drawRectangleRec(full_bounds, .black);
        }
        return drawGameBootUi(state, ui_layout);
    }

    if (frontendPhaseUsesCanvas(state)) {
        if (state.frontend_canvas) |canvas| {
            const authored_bounds: rl.Rectangle = .{
                .x = 0.0,
                .y = 0.0,
                .width = app_ui.authored_width,
                .height = app_ui.authored_height,
            };
            const authored_layout = app_ui.virtualLayout(authored_bounds);

            {
                canvas.begin();
                defer canvas.end();
                rl.clearBackground(.black);
                try drawGamePhaseContents(state, authored_bounds, authored_layout);
                drawFrontendCursorOverlay(state, authored_layout);
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
            drawFrontendCursorOverlay(state, ui_layout);
        }
    } else {
        try drawGamePhaseContents(state, full_bounds, ui_layout);
        drawFrontendCursorOverlay(state, ui_layout);
    }

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

fn optionsMenuMeasurementLabel(state: *const AppState, item: OptionsMenuItem) []const u8 {
    return switch (item) {
        .fullscreen => if (state.runtime_config.fullscreenEnabled()) "Full-screen On" else "Full-screen Off",
        .sound_volume => "     Sounds Volume     >",
        .music_volume => "      Music Volume      >",
        .back => "Back",
    };
}

fn optionsMenuVisibleLabel(state: *const AppState, item: OptionsMenuItem) []const u8 {
    return switch (item) {
        .fullscreen => optionsMenuMeasurementLabel(state, .fullscreen),
        .sound_volume => "Sounds Volume",
        .music_volume => "Music Volume",
        .back => "Back",
    };
}

fn optionsSliderLayout(state: *const AppState, item: OptionsMenuItem) frontend_widget.SliderLayout {
    var value_buffer: [16]u8 = undefined;
    const title_rect = switch (item) {
        .sound_volume => optionsTextRect(state, .sound_volume),
        .music_volume => optionsTextRect(state, .music_volume),
        else => unreachable,
    };
    const value = switch (item) {
        .sound_volume => state.runtime_config.soundVolume(),
        .music_volume => state.runtime_config.musicVolume(),
        else => unreachable,
    };
    const value_text = optionsSliderValueText(value, &value_buffer);
    const button_index = switch (item) {
        .sound_volume => options_sound_button_index,
        .music_volume => options_music_button_index,
        else => unreachable,
    };
    return frontend_widget.sliderLayout(
        &state.ui_font,
        title_rect,
        state.options_button_states[button_index],
        value_text,
    );
}

fn optionsTextRect(state: *const AppState, item: OptionsMenuItem) frontend_widget.Rect {
    return switch (item) {
        .fullscreen => frontend_widget.type20TextRect(
            &state.ui_font,
            optionsMenuMeasurementLabel(state, .fullscreen),
            options_fullscreen_anchor_y,
            options_button_center_offset_x,
        ),
        .sound_volume => frontend_widget.type20TextRect(
            &state.ui_font,
            optionsMenuMeasurementLabel(state, .sound_volume),
            optionsTextRect(state, .fullscreen).top + optionsTextRect(state, .fullscreen).height + frontend_widget.type20_stack_gap,
            options_button_center_offset_x,
        ),
        .music_volume => frontend_widget.type20TextRect(
            &state.ui_font,
            optionsMenuMeasurementLabel(state, .music_volume),
            // PORT(verified): `initialize_options` stacks Music below the full slider parent,
            // not below a hardcoded surrogate row height. The parent frame height comes from
            // the child-arrow/value layout in the shared widget pipeline.
            frontend_widget.sliderStackBelowLayout(optionsSliderLayout(state, .sound_volume)),
            options_button_center_offset_x,
        ),
        .back => frontend_widget.type20TextRect(
            &state.ui_font,
            "Back",
            // PORT(verified): the Back button is chained from the Music slider widget after
            // its children are attached, so this needs the live computed slider frame height.
            frontend_widget.sliderStackBelowLayout(optionsSliderLayout(state, .music_volume)),
            options_button_center_offset_x,
        ),
    };
}

fn optionsSliderValueText(value: f32, buffer: []u8) []const u8 {
    return std.fmt.bufPrint(buffer, "{d:0>2.0}%", .{std.math.clamp(value, 0.0, 1.0) * 100.0}) catch "00%";
}

fn mainMenuTextRect(font: *const game_font.Loaded, item: MainMenuItem) frontend_widget.Rect {
    return switch (item) {
        .new_game => frontend_widget.type20TextRect(font, item.label(), main_menu_start_y, frontend_widget.type20_center_offset_x),
        .high_scores => frontend_widget.type20TextRect(font, item.label(), frontend_widget.stackBelow(mainMenuTextRect(font, .new_game)), frontend_widget.type20_center_offset_x),
        .options => frontend_widget.type20TextRect(font, item.label(), frontend_widget.stackBelow(mainMenuTextRect(font, .high_scores)), frontend_widget.type20_center_offset_x),
        .credits => frontend_widget.type20TextRect(font, item.label(), frontend_widget.stackBelow(mainMenuTextRect(font, .options)), frontend_widget.type20_center_offset_x),
        .exit => frontend_widget.type20TextRect(font, item.label(), frontend_widget.stackBelow(mainMenuTextRect(font, .credits)), frontend_widget.type20_center_offset_x),
    };
}

fn newGameMenuTextRect(font: *const game_font.Loaded, item: NewGameMenuItem) frontend_widget.Rect {
    return switch (item) {
        .tutorial => frontend_widget.type20TextRect(font, item.label(), new_game_start_y, frontend_widget.type20_center_offset_x),
        .postal_mode => frontend_widget.type20TextRect(font, item.label(), frontend_widget.stackBelow(newGameMenuTextRect(font, .tutorial)), frontend_widget.type20_center_offset_x),
        .time_trial => frontend_widget.type20TextRect(font, item.label(), frontend_widget.stackBelow(newGameMenuTextRect(font, .postal_mode)), frontend_widget.type20_center_offset_x),
        .challenge_mode => frontend_widget.type20TextRect(font, item.label(), frontend_widget.stackBelow(newGameMenuTextRect(font, .time_trial)), frontend_widget.type20_center_offset_x),
        .help => newGameHelpTextRect(font),
        .back => newGameBackTextRect(font),
    };
}

fn newGameHelpTextRect(font: *const game_font.Loaded) frontend_widget.Rect {
    return frontend_widget.type20TextRect(font, "Help", new_game_help_anchor_y, new_game_help_center_offset_x);
}

fn newGameBackTextRect(font: *const game_font.Loaded) frontend_widget.Rect {
    return frontend_widget.type20TextRect(
        font,
        "Back",
        frontend_widget.stackBelow(newGameMenuTextRect(font, .challenge_mode)),
        new_game_back_center_offset_x,
    );
}

fn helpBackTextRect(font: *const game_font.Loaded) frontend_widget.Rect {
    return frontend_widget.type20TextRect(font, "Back", help_back_anchor_y, 0.0);
}

fn pauseMenuTextRect(font: *const game_font.Loaded, item: PauseMenuItem) frontend_widget.Rect {
    return switch (item) {
        .end_game => frontend_widget.type20TextRect(font, item.label(), pause_menu_start_y, pause_menu_center_offset_x),
        .options => frontend_widget.type20TextRect(font, item.label(), frontend_widget.stackBelow(pauseMenuTextRect(font, .end_game)), pause_menu_center_offset_x),
        .@"resume" => frontend_widget.type20TextRect(font, item.label(), frontend_widget.stackBelow(pauseMenuTextRect(font, .options)), pause_menu_center_offset_x),
    };
}

fn routeMapBackTextRect(state: *const AppState) frontend_widget.Rect {
    return frontend_widget.widgetTextRect(&state.ui_font, .menu_button, .absolute, routeMapBackLabel(state), route_map_back_y, route_map_back_x);
}

fn routeMapBackLabel(state: *const AppState) []const u8 {
    return routeMapBackLabelForScreenMode(state.route_map_screen_mode);
}

fn routeMapBackLabelForScreenMode(screen_mode: RouteMapScreenMode) []const u8 {
    return switch (screen_mode) {
        .post_completion_exit => "Exit",
        .normal, .replay => "Back",
    };
}

fn routeMapAllowsRouteSwitching(screen_mode: RouteMapScreenMode) bool {
    // PORT(verified): `update_galaxy` skips the open/switch/close route branch entirely
    // for internal mode `1`, keeping the postal-return Star Map locked on its current
    // route card while still allowing Play/Exit.
    return screen_mode != .post_completion_exit;
}

fn routeMapBodyText(maybe_text: ?[]const u8) []const u8 {
    // PORT(verified): `open_galaxy_route` copies the route body from the per-route record
    // once when the card opens. `update_galaxy` does not swap that body text based on
    // hover state or selected action.
    return maybe_text orelse "";
}

fn highScoreFooterTextRect(state: *const AppState, text: []const u8, center_offset_x: f32) frontend_widget.Rect {
    return frontend_widget.widgetTextRect(&state.ui_font, .footer_button, .center, text, high_score_footer_y, center_offset_x);
}

fn highScoreRowBackgroundText(mode: high_score.Mode) []const u8 {
    return switch (mode) {
        .postal => "                                               ",
        .challenge => "                                           ",
    };
}

fn highScoreRowBackgroundTextRect(state: *const AppState, mode: high_score.Mode, row_y: f32) frontend_widget.Rect {
    return frontend_widget.widgetTextRect(&state.ui_font, .compact_score_row, .left, highScoreRowBackgroundText(mode), row_y, high_score_rank_marker_x);
}

fn highScoreRankTextRect(state: *const AppState, row_y: f32, rank_text: []const u8) frontend_widget.Rect {
    return frontend_widget.widgetTextRect(&state.ui_font, .compact_score_row, .left, rank_text, row_y, high_score_rank_number_x);
}

fn highScoreNameTextRect(state: *const AppState, row_y: f32, display_name: []const u8) frontend_widget.Rect {
    return frontend_widget.widgetTextRect(&state.ui_font, .compact_score_row, .left, display_name, row_y, high_score_name_x);
}

fn highScoreScoreTextRect(state: *const AppState, mode: high_score.Mode, row_y: f32, score_text: []const u8) frontend_widget.Rect {
    return frontend_widget.widgetTextRect(
        &state.ui_font,
        .compact_score_row,
        .right,
        score_text,
        row_y,
        switch (mode) {
            .postal => high_score_postal_score_x,
            .challenge => high_score_challenge_score_x,
        },
    );
}

fn highScoreReplayTextRect(state: *const AppState, mode: high_score.Mode, row_y: f32) frontend_widget.Rect {
    return frontend_widget.widgetTextRect(
        &state.ui_font,
        .compact_score_row,
        .center,
        "Replay",
        row_y,
        switch (mode) {
            .postal => high_score_postal_replay_x,
            .challenge => high_score_challenge_replay_x,
        },
    );
}

fn completionTitleTextRect(font: *const game_font.Loaded, text: []const u8) frontend_widget.Rect {
    return frontend_widget.type20TextRect(font, text, completion_title_y, 0.0);
}

fn completionPackageTextRect(font: *const game_font.Loaded, text: []const u8) frontend_widget.Rect {
    return frontend_widget.type20TextRect(font, text, completion_package_y, 0.0);
}

fn completionBonusTextRect(font: *const game_font.Loaded, text: []const u8) frontend_widget.Rect {
    return frontend_widget.type20TextRect(font, text, completion_bonus_y, 0.0);
}

fn completionContinueAnchorY(result: PendingRunResult) f32 {
    return if (completionHasBonusLine(result)) completion_continue_y_with_bonus else completion_continue_y;
}

fn completionContinueTextRect(font: *const game_font.Loaded, result: PendingRunResult) frontend_widget.Rect {
    return frontend_widget.type20TextRect(font, "Click to Continue", completionContinueAnchorY(result), 0.0);
}

fn exitPromptTextRect(state: *const AppState, text: []const u8, center_offset_x: f32) frontend_widget.Rect {
    // PORT(verified): `initialize_exit_prompt` seeds the Yes/No widgets at `330`, but then
    // immediately runs both through `stack_widget_below(title)`. The live authored Y comes
    // from the title height plus the shared shell-font stack gap, not the constructor seed.
    const title_rect = frontend_widget.widgetTextRect(
        &state.ui_font,
        .menu_button,
        .center,
        "Do you really want to quit?",
        exit_prompt_title_y,
        0.0,
    );
    return frontend_widget.widgetTextRect(
        &state.ui_font,
        .menu_button,
        .center,
        text,
        frontend_widget.stackBelow(title_rect),
        center_offset_x,
    );
}

fn drawMainMenuUi(state: *const AppState, layout: VirtualLayout) !void {
    for (main_menu_items, 0..) |item, index| {
        const text_rect = mainMenuTextRect(&state.ui_font, item);
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
    }

    if (state.game_status_message) |message| {
        try drawFrontendStatusMessage(state, layout, message);
    }
}

fn drawNewGameMenuUi(state: *const AppState, layout: VirtualLayout) !void {
    for (new_game_menu_items[0..4], 0..) |item, index| {
        const text_rect = newGameMenuTextRect(&state.ui_font, item);
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
    }
    frontend_widget.drawType20Button(
        layout,
        .{
            .border = state.frontend_widget_art.border.?.texture,
        },
        &state.ui_font,
        "Help",
        newGameHelpTextRect(&state.ui_font),
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
        newGameBackTextRect(&state.ui_font),
        state.new_game_button_states[5],
        false,
    );

    if (state.game_status_message) |message| {
        try drawFrontendStatusMessage(state, layout, message);
    }
}

fn drawOptionsMenuUi(state: *const AppState, layout: VirtualLayout) !void {
    frontend_widget.drawType20Button(
        layout,
        .{
            .border = state.frontend_widget_art.border.?.texture,
        },
        &state.ui_font,
        optionsMenuVisibleLabel(state, .fullscreen),
        optionsTextRect(state, .fullscreen),
        state.options_button_states[options_fullscreen_button_index],
        false,
    );
    const active_target = state.activeFrontendButtonTarget();
    drawOptionsSliderRow(
        state,
        layout,
        .sound_volume,
        state.runtime_config.soundVolume(),
        state.options_sound_display_value,
        state.options_button_states[options_sound_button_index],
        if (active_target) |target| target == .options_sound_less else false,
        if (active_target) |target| target == .options_sound_more else false,
    );
    drawOptionsSliderRow(
        state,
        layout,
        .music_volume,
        state.runtime_config.musicVolume(),
        state.options_music_display_value,
        state.options_button_states[options_music_button_index],
        if (active_target) |target| target == .options_music_less else false,
        if (active_target) |target| target == .options_music_more else false,
    );
    frontend_widget.drawType20Button(
        layout,
        .{
            .border = state.frontend_widget_art.border.?.texture,
        },
        &state.ui_font,
        "Back",
        optionsTextRect(state, .back),
        state.options_button_states[options_back_button_index],
        false,
    );

    if (state.game_status_message) |message| {
        try drawFrontendStatusMessage(state, layout, message);
    }
}

fn drawPauseMenuUi(state: *const AppState, layout: VirtualLayout) !void {
    for (pause_menu_items, 0..) |item, index| {
        frontend_widget.drawType20Button(
            layout,
            .{
                .border = state.frontend_widget_art.border.?.texture,
            },
            &state.ui_font,
            item.label(),
            pauseMenuTextRect(&state.ui_font, item),
            state.pause_menu_button_states[index],
            false,
        );
    }
}

const RouteMapCardLayout = struct {
    card_rect: frontend_widget.Rect,
    title_rect: frontend_widget.Rect,
    subtitle_rect: frontend_widget.Rect,
    body_rect: frontend_widget.Rect,
    primary_text_rect: frontend_widget.Rect,
    replay_text_rect: ?frontend_widget.Rect,
    pointer_start: galaxy.Point,
    pointer_end: galaxy.Point,
};

fn drawRouteMapMenuUi(state: *const AppState, layout: VirtualLayout) !void {
    const mode = state.frontend_route_mode orelse return;
    const widget_art: frontend_widget.Art = .{
        .border = state.frontend_widget_art.border.?.texture,
    };
    // PORT(verified): `initialize_galaxy` passes an explicit white color into the title
    // widget constructor instead of reusing the orange menu-heading tint.
    drawUiFontTextAbsolute(state, layout, "Intergalactic Delivery Route", route_map_title_x, route_map_title_y, route_map_title_scale, .ray_white);
    drawRouteMapLogo(state, layout);
    drawRouteMapStars(state, layout, mode);
    if (state.currentRouteMapOpenIndex()) |route_index| {
        const route_galaxy_name = state.currentFrontendGalaxyName() orelse frontendRouteModeLabel(mode);
        const route_level_name = if (state.frontend_route_level) |loaded_level| loaded_level.name else "Route";
        const route_body = routeMapBodyText(if (state.frontend_route_level) |loaded_level| loaded_level.galaxy_text else null);
        const primary_label = routeMenuActionLabel(mode, .play);
        const replay_label = if (state.routeMapShowsReplay()) routeMenuActionLabel(mode, .watch_best_trial) else null;
        if (routeMapPointForRouteIndex(state, route_index)) |route_point| {
            const card_layout = routeMapCardLayout(
                &state.ui_font,
                route_point,
                route_galaxy_name,
                route_level_name,
                route_body,
                primary_label,
                replay_label,
            );
            drawRouteMapConnection(layout, card_layout.pointer_start, card_layout.pointer_end, state.route_map_art.line_star, 4.0, .white);
            drawRouteMapCard(state, layout, card_layout, route_galaxy_name, route_level_name, route_body, primary_label, replay_label);
        }
    }

    frontend_widget.drawType20Button(
        layout,
        widget_art,
        &state.ui_font,
        routeMapBackLabel(state),
        routeMapBackTextRect(state),
        state.route_map_button_states[route_map_back_button_index],
        false,
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
    var title_state = frontend_widget.TextButtonState{};
    title_state.snapFor(.footer_button, false);
    const title_text = if (pending_entry != null) "Enter your name here!" else highScoreScreenTitle(selected_mode);
    frontend_widget.drawTextButton(
        layout,
        art,
        &state.ui_font,
        .footer_button,
        title_text,
        frontend_widget.widgetTextRect(&state.ui_font, .footer_button, .center, title_text, high_score_title_y, 0.0),
        title_state,
        false,
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
    const row_background_text = highScoreRowBackgroundText(mode);
    const text_only_score_cell: frontend_widget.DrawOptions = .{
        // PORT(verified): `initialize_high_score_screen` gives the rank, name,
        // and numeric score cells flags `0x20400000`, so those type-22 widgets
        // render as text-only entries on top of the shared row background.
        .flags = 0x20400000,
    };

    for (entries, 0..) |table_entry, entry_index| {
        const row_highlighted = highlight_index != null and highlight_index.? == entry_index;
        if (!table_entry.isActive() and !row_highlighted) continue;

        const row_y = high_score_row_start_y + @as(f32, @floatFromInt(entry_index)) * high_score_row_pitch;
        var row_state = frontend_widget.TextButtonState{};
        row_state.snapFor(.compact_score_row, row_highlighted);
        frontend_widget.drawTextButton(
            layout,
            art,
            &state.ui_font,
            .compact_score_row,
            row_background_text,
            highScoreRowBackgroundTextRect(state, mode, row_y),
            row_state,
            false,
        );

        var rank_buffer: [8]u8 = undefined;
        const rank_text = std.fmt.bufPrint(&rank_buffer, "{d}", .{entry_index + 1}) catch "";
        const display_name = if (row_highlighted and editing_name != null)
            editing_name.?
        else
            highScoreDisplayName(&table_entry);

        frontend_widget.drawTextButtonWithOptions(
            layout,
            art,
            &state.ui_font,
            .compact_score_row,
            rank_text,
            highScoreRankTextRect(state, row_y, rank_text),
            row_state,
            false,
            text_only_score_cell,
        );
        frontend_widget.drawTextButtonWithOptions(
            layout,
            art,
            &state.ui_font,
            .compact_score_row,
            display_name,
            highScoreNameTextRect(state, row_y, display_name),
            row_state,
            false,
            text_only_score_cell,
        );

        var score_buffer: [32]u8 = undefined;
        const score_text = if (table_entry.isActive())
            (std.fmt.bufPrint(&score_buffer, "{d}", .{table_entry.score}) catch "0")
        else
            "";
        frontend_widget.drawTextButtonWithOptions(
            layout,
            art,
            &state.ui_font,
            .compact_score_row,
            score_text,
            highScoreScoreTextRect(state, mode, row_y, score_text),
            row_state,
            false,
            text_only_score_cell,
        );
        if (highScoreRowsShowReplay(mode, hide_replay) and table_entry.has_replay) {
            frontend_widget.drawTextButton(
                layout,
                art,
                &state.ui_font,
                .compact_score_row,
                "Replay",
                highScoreReplayTextRect(state, mode, row_y),
                state.high_score_replay_button_states[entry_index],
                false,
            );
        }
    }
}

fn highScoreDisplayName(entry: *const high_score.Entry) []const u8 {
    const name = entry.name();
    if (name.len == 0) return "---";
    return name;
}

fn highScoreRowsShowReplay(mode: high_score.Mode, in_name_entry: bool) bool {
    // PORT(verified): `initialize_high_score_screen` only enables the row Replay widgets for the
    // Challenge table, and `update_high_score_screen` suppresses them while inline name-entry is active.
    return mode == .challenge and !in_name_entry;
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

fn drawFrontendCursorOverlay(state: *const AppState, layout: VirtualLayout) void {
    if (state.command != .game) return;
    if (!frontendPhaseShowsCursor(state.game_phase)) return;
    const local_mouse = state.currentFrontendMouseLocal() orelse return;
    drawFrontendCursorRocket(state, layout, local_mouse.x, local_mouse.y);
}

fn frontendPhaseShowsCursor(phase: GamePhase) bool {
    return switch (phase) {
        .main_menu,
        .new_game_menu,
        .options_menu,
        .pause_menu,
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

fn scaledUiFontSize(font: *const game_font.Loaded, text_scale: f32) f32 {
    return font.nominal_height * text_scale;
}

fn multilineUiTextHeight(font: *const game_font.Loaded, text: []const u8, text_scale: f32) f32 {
    if (text.len == 0) return 0.0;
    var line_count: usize = 1;
    for (text) |byte| {
        if (byte == '\n') line_count += 1;
    }
    return @as(f32, @floatFromInt(line_count)) * scaledUiFontSize(font, text_scale);
}

fn uiFontTextRectAbsolute(font: *const game_font.Loaded, text: []const u8, left: f32, top: f32, text_scale: f32) frontend_widget.Rect {
    const font_size = scaledUiFontSize(font, text_scale);
    return .{
        .left = left,
        .top = top,
        .width = font.measureText(text, font_size),
        .height = multilineUiTextHeight(font, text, text_scale),
    };
}

fn drawUiFontTextAbsolute(
    state: *const AppState,
    layout: VirtualLayout,
    text: []const u8,
    left: f32,
    top: f32,
    text_scale: f32,
    color: rl.Color,
) void {
    const point = layout.mapPoint(left, top);
    state.ui_font.drawText(text, point.x, point.y, layout.scaleFloat(scaledUiFontSize(&state.ui_font, text_scale)), color);
}

fn drawUiFontTextRect(
    state: *const AppState,
    layout: VirtualLayout,
    text: []const u8,
    rect: frontend_widget.Rect,
    text_scale: f32,
    color: rl.Color,
) void {
    drawUiFontTextAbsolute(state, layout, text, rect.left, rect.top, text_scale, color);
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

fn drawOptionsSliderRow(
    state: *const AppState,
    layout: VirtualLayout,
    item: OptionsMenuItem,
    value: f32,
    displayed_value: f32,
    row_state: frontend_widget.TextButtonState,
    less_hovered: bool,
    more_hovered: bool,
) void {
    var value_buffer: [16]u8 = undefined;
    const title_rect = optionsTextRect(state, item);
    const value_text = optionsSliderValueText(value, &value_buffer);
    frontend_widget.drawSliderMenuRow(
        layout,
        .{
            .border = state.frontend_widget_art.border.?.texture,
        },
        state.slider_art.textures(),
        &state.ui_font,
        optionsMenuVisibleLabel(state, item),
        title_rect,
        value_text,
        value,
        displayed_value,
        row_state,
        less_hovered,
        more_hovered,
    );
}

fn routeMapCardLayout(
    font: *const game_font.Loaded,
    route_point: galaxy.Point,
    route_galaxy_name: []const u8,
    route_level_name: []const u8,
    route_body: []const u8,
    primary_action: []const u8,
    replay_action: ?[]const u8,
) RouteMapCardLayout {
    var title_left = route_point.x + 60.0;
    var title_top = route_point.y - 130.0;

    while (true) {
        const title_rect = uiFontTextRectAbsolute(font, route_galaxy_name, title_left, title_top, route_map_card_title_scale);
        const subtitle_rect = uiFontTextRectAbsolute(
            font,
            route_level_name,
            title_left,
            frontend_widget.stackBelowWithGap(title_rect, route_map_card_text_gap),
            route_map_card_subtitle_scale,
        );
        const body_rect = uiFontTextRectAbsolute(
            font,
            route_body,
            title_left,
            frontend_widget.stackBelowWithGap(subtitle_rect, route_map_card_text_gap),
            route_map_card_body_scale,
        );
        // PORT(verified): `open_galaxy_route` chains the selected route card with the shared
        // `stack_widget_below` helper: title -> subtitle -> body -> replay? -> primary. The
        // title/subtitle/body use zero extra gap, the replay row uses `10`, and the primary
        // action uses `20`. Windows first centers the action widgets from the title width,
        // then recenters them from the final card box after the clamp loop.
        const title_center_offset = title_rect.left + title_rect.width * 0.5 - 320.0;

        var primary_text_rect = frontend_widget.widgetTextRect(
            font,
            .menu_button,
            .center,
            primary_action,
            frontend_widget.stackBelowWithGap(body_rect, route_map_primary_button_gap),
            title_center_offset,
        );
        var replay_text_rect: ?frontend_widget.Rect = null;
        if (replay_action) |label| {
            replay_text_rect = frontend_widget.widgetTextRect(
                font,
                .route_map_secondary_action,
                .center,
                label,
                frontend_widget.stackBelowWithGap(body_rect, route_map_replay_button_gap),
                title_center_offset,
            );
            primary_text_rect = frontend_widget.widgetTextRect(
                font,
                .menu_button,
                .center,
                primary_action,
                frontend_widget.stackBelowWithGap(replay_text_rect.?, route_map_primary_button_gap),
                title_center_offset,
            );
        }

        var left = @min(title_rect.left, @min(subtitle_rect.left, @min(body_rect.left, primary_text_rect.left)));
        const top = @min(title_rect.top, @min(subtitle_rect.top, @min(body_rect.top, primary_text_rect.top)));
        var right = @max(
            title_rect.left + title_rect.width,
            @max(
                subtitle_rect.left + subtitle_rect.width,
                @max(body_rect.left + body_rect.width, primary_text_rect.left + primary_text_rect.width),
            ),
        );
        var bottom = @max(
            title_rect.top + title_rect.height,
            @max(
                subtitle_rect.top + subtitle_rect.height,
                @max(body_rect.top + body_rect.height, primary_text_rect.top + primary_text_rect.height),
            ),
        );
        // PORT(verified): `open_galaxy_route` clamps the selected card against the title,
        // subtitle, body, and primary action widgets only. The replay action is recentered
        // from the finished card box afterwards, but it does not expand the box bounds.
        left -= route_map_card_horizontal_padding;
        right += route_map_card_horizontal_padding;
        bottom += route_map_card_bottom_padding;

        var adjusted = false;
        if (right > route_map_card_right_limit) {
            title_left = route_point.x - (right - left) - 40.0;
            adjusted = true;
        }
        if (top < route_map_card_min_top) {
            title_top = 50.0;
            adjusted = true;
        }
        if (bottom > route_map_card_bottom_y) {
            title_top = route_map_card_bottom_y - (bottom - top);
            adjusted = true;
        }
        if (adjusted) continue;

        const card_rect: frontend_widget.Rect = .{
            .left = left,
            .top = top,
            .width = right - left,
            .height = bottom - top,
        };
        const card_center_offset = card_rect.left + card_rect.width * 0.5 - 320.0;
        primary_text_rect = frontend_widget.widgetTextRect(
            font,
            .menu_button,
            .center,
            primary_action,
            primary_text_rect.top,
            card_center_offset,
        );
        if (replay_action) |label| {
            if (replay_text_rect) |replay_rect| {
                replay_text_rect = frontend_widget.widgetTextRect(
                    font,
                    .route_map_secondary_action,
                    .center,
                    label,
                    replay_rect.top,
                    card_center_offset,
                );
            }
        }
        const pointer_start_x = if (card_rect.left <= route_point.x)
            route_point.x - route_map_card_star_gap
        else
            route_point.x + route_map_card_star_gap;
        const pointer_end_x = if (card_rect.left <= route_point.x)
            card_rect.left + card_rect.width + route_map_card_horizontal_pointer_gap
        else
            card_rect.left - route_map_card_horizontal_pointer_gap;
        return .{
            .card_rect = card_rect,
            .title_rect = title_rect,
            .subtitle_rect = subtitle_rect,
            .body_rect = body_rect,
            .primary_text_rect = primary_text_rect,
            .replay_text_rect = replay_text_rect,
            .pointer_start = .{ .x = pointer_start_x, .y = route_point.y },
            .pointer_end = .{ .x = pointer_end_x, .y = route_point.y },
        };
    }
}

fn routeMapPointForRouteIndex(state: *const AppState, route_index: usize) ?galaxy.Point {
    if (state.galaxy_names) |names| {
        if (names.routePointForRouteIndex(route_index)) |point| return point;
    }
    return galaxy.routePointForRouteIndex(route_index);
}

fn routeMapHoveredRouteIndex(state: *const AppState, local_mouse: rl.Vector2, route_limit: usize) ?usize {
    if (route_limit == 0) return null;

    const selection_radius_squared = 17.0 * 17.0;
    for (1..@min(route_limit, galaxy.map_route_count) + 1) |route_index| {
        const point = routeMapPointForRouteIndex(state, route_index) orelse continue;
        const dx = point.x - local_mouse.x;
        const dy = point.y - local_mouse.y;
        if (dx * dx + dy * dy < selection_radius_squared) {
            return route_index;
        }
    }
    return null;
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
    const active_route_index = state.currentRouteMapOpenIndex() orelse state.frontend_route_index;
    const selected_galaxy_index = if (state.galaxy_names) |names|
        names.galaxyIndexForRouteIndex(state.frontend_route_index)
    else
        null;
    for (0..galaxy.map_galaxy_count) |galaxy_index| {
        const center = galaxy.galaxyCenter(galaxy_index);
        if (state.route_map_art.galaxies[galaxy_index]) |loaded_texture| {
            drawTextureCenteredLocal(layout, loaded_texture, center.x, center.y, route_map_galaxy_size, route_map_galaxy_size, .white);
        }
    }

    if (state.galaxy_names) |names| {
        if (selected_galaxy_index) |galaxy_index| {
            var route_cursor: usize = 0;
            for (0..galaxy_index) |prior_index| {
                route_cursor += names.starCountForGalaxyIndex(prior_index) orelse 0;
            }
            const star_count = names.starCountForGalaxyIndex(galaxy_index) orelse 0;
            var visible_star_count = if (available_limit > route_cursor)
                @min(star_count, available_limit - route_cursor)
            else
                0;
            // PORT(verified): the postal post-completion Star Map variant (`this + 4 == 1`)
            // stops drawing future route stars once it reaches the current route. Only the
            // normal/replay variants keep the remainder of the available route strip visible.
            if (state.route_map_screen_mode == .post_completion_exit and active_route_index > route_cursor) {
                visible_star_count = @min(visible_star_count, active_route_index - route_cursor);
            }

            if (visible_star_count >= 2) {
                for (0..visible_star_count - 1) |local_index| {
                    const start_route_index = route_cursor + local_index + 1;
                    const end_route_index = start_route_index + 1;
                    // PORT(verified): `update_galaxy` iterates route links only up to the
                    // live available-route count in `dword_4DF9B8`, then shades them in two
                    // authored bands: `0.8` before the current route and `0.2` afterwards.
                    // The postal post-completion variant omits the later `0.2` links entirely.
                    if (state.route_map_screen_mode == .post_completion_exit and start_route_index >= active_route_index) continue;
                    const line_tint: rl.Color = if (start_route_index < active_route_index)
                        .{ .r = 255, .g = 255, .b = 255, .a = 204 }
                    else
                        .{ .r = 255, .g = 255, .b = 255, .a = 51 };
                    drawRouteMapConnection(
                        layout,
                        names.routePointForRouteIndex(start_route_index).?,
                        names.routePointForRouteIndex(end_route_index).?,
                        state.route_map_art.line,
                        route_map_path_line_width,
                        line_tint,
                    );
                }
            }

            for (0..visible_star_count) |local_index| {
                const route_index = route_cursor + local_index + 1;
                const point = names.routePointForRouteIndex(route_index).?;
                if (state.route_map_art.level_star) |loaded_texture| {
                    drawTextureCenteredLocal(layout, loaded_texture, point.x, point.y, 32.0, 32.0, .white);
                }
            }
        }
    }

    for (1..@min(available_limit, galaxy.map_route_count) + 1) |route_index| {
        const highlight_alpha = state.route_map_route_highlight_alpha[route_index];
        if (highlight_alpha <= 0.001) continue;
        if (routeMapPointForRouteIndex(state, route_index)) |selected_point| {
            if (state.route_map_art.level_select) |loaded_texture| {
                drawTextureCenteredLocal(
                    layout,
                    loaded_texture,
                    selected_point.x,
                    selected_point.y,
                    64.0,
                    64.0,
                    .{
                        .r = 255,
                        .g = 255,
                        .b = 255,
                        .a = @intFromFloat(std.math.clamp(highlight_alpha * 255.0, 0.0, 255.0)),
                    },
                );
            }
        }
    }
}

fn drawRouteMapCard(
    state: *const AppState,
    layout: VirtualLayout,
    card_layout: RouteMapCardLayout,
    route_galaxy_name: []const u8,
    route_level_name: []const u8,
    route_body: []const u8,
    primary_action: []const u8,
    replay_action: ?[]const u8,
) void {
    if (state.route_map_art.border) |loaded_texture| {
        frontend_widget.drawNineSliceFrame(
            layout,
            loaded_texture.texture,
            card_layout.card_rect,
            route_map_card_frame_edge,
            route_map_card_frame_edge / 128.0,
            .white,
        );
    }

    drawUiFontTextRect(state, layout, route_galaxy_name, card_layout.title_rect, route_map_card_title_scale, .ray_white);
    drawUiFontTextRect(state, layout, route_level_name, card_layout.subtitle_rect, route_map_card_subtitle_scale, .ray_white);
    drawUiFontTextRect(state, layout, route_body, card_layout.body_rect, route_map_card_body_scale, .ray_white);

    const widget_art: frontend_widget.Art = .{
        .border = state.frontend_widget_art.border.?.texture,
    };
    frontend_widget.drawType20Button(
        layout,
        widget_art,
        &state.ui_font,
        primary_action,
        card_layout.primary_text_rect,
        state.route_map_button_states[route_map_primary_button_index],
        false,
    );
    if (replay_action) |label| {
        if (card_layout.replay_text_rect) |replay_text_rect| {
            frontend_widget.drawTextButton(
                layout,
                widget_art,
                &state.ui_font,
                .route_map_secondary_action,
                label,
                replay_text_rect,
                state.route_map_button_states[route_map_replay_button_index],
                false,
            );
        }
    }
}

fn drawRouteMapLogo(state: *const AppState, layout: VirtualLayout) void {
    const loaded_texture = state.route_map_art.logo orelse return;
    drawTextureLocalRect(
        layout,
        loaded_texture,
        route_map_logo_x,
        route_map_logo_y,
        route_map_logo_width,
        route_map_logo_height,
        .white,
    );
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
        .postal => "Challenge Score",
        .challenge => "Postal Scores",
    };
}

fn completionHasBonusLine(result: PendingRunResult) bool {
    return result.outcome == .completed and result.score_totals.completion_bonus > 0;
}

fn completionPackageLine(buffer: []u8, result: PendingRunResult) ![]const u8 {
    return if (result.parcel_count == 1)
        std.fmt.bufPrint(buffer, "1 Package Delivered!", .{})
    else
        std.fmt.bufPrint(buffer, "{d:0>2} Packages Delivered!", .{result.parcel_count});
}

fn completionBonusLine(buffer: []u8, result: PendingRunResult) !?[]const u8 {
    if (!completionHasBonusLine(result)) return null;
    if (result.score_totals.completion_bonus == 50_000 and result.parcel_count == result.parcel_target) {
        return try std.fmt.bufPrint(buffer, "Perfect Score! 50,000 Bonus Points!", .{});
    }
    return try std.fmt.bufPrint(buffer, "{d} Bonus Points!", .{result.score_totals.completion_bonus});
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
    frontend_widget.drawType20Button(
        layout,
        .{
            .border = state.frontend_widget_art.border.?.texture,
        },
        &state.ui_font,
        "Back",
        helpBackTextRect(&state.ui_font),
        state.help_button_states[0],
        false,
    );
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
            "Row {d:.2}/{d}  cursor {d}+{d:.2}  lane {d}->{d}  speed {d:.1}  event {s}  damage {d:.2}  warn {s}  lives {d}  jet {d:.2} {s}  phase {s}",
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
                runner.jetpackFuelRemaining(),
                runner.jetpackWarningLabel(),
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
    drawJetpackGaugeWidget(state, layout, runner);
    drawDamageGaugeWidget(state, layout, runner);
    if (runner.session_mode == .postal) {
        drawVisibleLifeStrip(state, layout, runner.visible_life_stock);
    }
}

fn drawJetpackGaugeWidget(state: *const AppState, layout: VirtualLayout, runner: gameplay.Runner) void {
    if (!runner.jetpack.active) return;

    const panel = layout.mapRect(548.0, 108.0, 28.0, 224.0);
    const fill_margin = layout.scaleFloat(4.0);
    const fill_height = @max(panel.height - fill_margin * 2.0, 0.0);
    const fill_width = @max(panel.width - fill_margin * 2.0, 0.0);
    const fill_ratio = runner.jetpackFuelRemaining();
    const active_fill_height = fill_height * fill_ratio;
    const pulse = if (runner.jetpack.warning_band == .near_empty) runner.jetpack.pulse_envelope else @as(f32, 0.0);
    const outline_alpha: u8 = @intFromFloat(160.0 + 64.0 * pulse);
    const label_y: i32 = @intFromFloat(panel.y - layout.scaleFloat(20.0));
    const fill_color = jetpackGaugeColor(runner.jetpack.warning_band, pulse);

    drawAppText(state, "Jet", @intFromFloat(panel.x + layout.scaleFloat(2.0)), label_y, layout.fontSize(16), .light_gray);
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

fn jetpackGaugeColor(warning_band: gameplay.JetpackWarningBand, pulse: f32) rl.Color {
    return switch (warning_band) {
        .idle => .{ .r = 94, .g = 204, .b = 122, .a = 0 },
        .steady => .{ .r = 90, .g = 172, .b = 255, .a = 224 },
        .near_empty => .{
            .r = 255,
            .g = @intFromFloat(164.0 + 72.0 * pulse),
            .b = 84,
            .a = 232,
        },
    };
}

fn drawCompletionScreenUi(state: *const AppState, layout: VirtualLayout) !void {
    drawGameplayLevelViewport(state);
    const result = state.pending_run_result orelse return;
    if (result.outcome == .completed) {
        try drawCompletedRunScreenUi(state, layout, result);
    } else {
        try drawFailedRunScreenUi(state, layout, result);
    }
}

fn drawCompletionParcelIcon(state: *const AppState, layout: VirtualLayout) void {
    const loaded_texture = state.frontend_widget_art.parcel_icon orelse return;
    drawTextureLocalRect(
        layout,
        loaded_texture,
        completion_parcel_icon_x,
        completion_parcel_icon_y,
        completion_parcel_icon_width,
        completion_parcel_icon_height,
        .white,
    );
}

fn drawCompletedRunScreenUi(state: *const AppState, layout: VirtualLayout, result: PendingRunResult) !void {
    const widget_art: frontend_widget.Art = .{
        .border = state.frontend_widget_art.border.?.texture,
    };
    var idle_state = frontend_widget.TextButtonState{};
    idle_state.snapFor(.menu_button, false);
    const completion_text_only: frontend_widget.DrawOptions = .{
        // PORT(verified): `initialize_completion_screen` builds the title,
        // package line, bonus line, and continue prompt with flags
        // `0x20400002`, which suppress the pill background while keeping the
        // type-20 shell-font metrics.
        .flags = 0x20400002,
    };

    const title_text = resultTitle(result);
    frontend_widget.drawTextButtonWithOptions(
        layout,
        widget_art,
        &state.ui_font,
        .menu_button,
        title_text,
        completionTitleTextRect(&state.ui_font, title_text),
        idle_state,
        false,
        completion_text_only,
    );

    var package_buffer: [64]u8 = undefined;
    const package_text = switch (result.mode orelse .tutorial) {
        .postal => try completionPackageLine(&package_buffer, result),
        .time_trial, .challenge, .tutorial => result.level_name,
    };
    frontend_widget.drawTextButtonWithOptions(
        layout,
        widget_art,
        &state.ui_font,
        .menu_button,
        package_text,
        completionPackageTextRect(&state.ui_font, package_text),
        idle_state,
        false,
        completion_text_only,
    );

    if ((result.mode orelse .tutorial) == .postal) {
        drawCompletionParcelIcon(state, layout);
    }

    if (try completionBonusLine(&package_buffer, result)) |bonus_text| {
        frontend_widget.drawTextButtonWithOptions(
            layout,
            widget_art,
            &state.ui_font,
            .menu_button,
            bonus_text,
            completionBonusTextRect(&state.ui_font, bonus_text),
            idle_state,
            false,
            completion_text_only,
        );
    }

    frontend_widget.drawTextButtonWithOptions(
        layout,
        widget_art,
        &state.ui_font,
        .menu_button,
        "Click to Continue",
        completionContinueTextRect(&state.ui_font, result),
        state.completion_continue_button_state,
        false,
        completion_text_only,
    );
}

fn drawFailedRunScreenUi(state: *const AppState, layout: VirtualLayout, result: PendingRunResult) !void {
    const overlay_panel = layout.mapRect(120.0, 132.0, 400.0, 204.0);
    const title_point = layout.mapPoint(144.0, 156.0);
    const body_point = layout.mapPoint(144.0, 196.0);
    const title_x: i32 = @intFromFloat(title_point.x);
    const title_y: i32 = @intFromFloat(title_point.y);
    const body_x: i32 = @intFromFloat(body_point.x);
    const body_y: i32 = @intFromFloat(body_point.y);
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

    frontend_widget.drawType20Button(
        layout,
        .{
            .border = state.frontend_widget_art.border.?.texture,
        },
        &state.ui_font,
        "Click to Continue",
        completionContinueTextRect(&state.ui_font, result),
        state.completion_continue_button_state,
        false,
    );
}

// PORT(debug): this browser is intentionally a tooling surface, not the shipping game path.
fn drawDebugUi(state: *const AppState, archive_path: []const u8) !void {
    if (state.mode == .models) {
        drawModelViewport(state);
    } else if (state.mode == .objects) {
        drawObjectViewport(state);
    } else if (state.mode == .levels) {
        debug_levels.drawLevelViewport(state);
    } else if (state.mode == .segments) {
        debug_levels.drawSegmentViewport(state);
    }

    drawAppText(state, "snail debug browser", 24, 18, 24, .ray_white);
    drawAppText(state, "1 textures  2 audio  3 x2  4 objects  5 levels  6 segments", 24, 48, 16, .light_gray);
    drawAppText(state, "tab mode  arrows browse  levels: up/down segment  gameplay: a/d lane w/s speed space pause r reset  segments: v render o overlay g grid a attachments t track", 24, 70, 16, .light_gray);

    var source_buffer: [256]u8 = undefined;
    const source_text = try std.fmt.bufPrintZ(
        &source_buffer,
        "{s}  runtime {s}",
        .{ std.fs.path.basename(archive_path), std.fs.path.basename(state.runtime_root_path) },
    );
    drawAppText(state, source_text, 24, 92, 14, .dark_gray);

    drawModeBadge(state, .textures, state.mode, "Textures", 24, 114);
    drawModeBadge(state, .audio, state.mode, "Audio", 136, 114);
    drawModeBadge(state, .models, state.mode, "X2", 248, 114);
    drawModeBadge(state, .objects, state.mode, "Objects", 360, 114);
    drawModeBadge(state, .levels, state.mode, "Levels", 472, 114);
    drawModeBadge(state, .segments, state.mode, "Segments", 584, 114);

    switch (state.mode) {
        .textures => drawTexturePanel(state),
        .audio => try drawAudioPanel(state),
        .models => try drawModelPanel(state),
        .objects => try drawObjectPanel(state),
        .levels => try debug_levels.drawLevelPanel(state),
        .segments => try debug_levels.drawSegmentPanel(state),
    }
}

fn drawModeBadge(state: *const AppState, mode: Mode, active_mode: Mode, text: [:0]const u8, x: i32, y: i32) void {
    const color: rl.Color = if (mode == active_mode) .orange else .dark_gray;
    rl.drawRectangleRounded(.{ .x = @floatFromInt(x), .y = @floatFromInt(y), .width = 94, .height = 28 }, 0.22, 8, color);
    drawAppText(state, text, x + 16, y + 6, 16, .ray_white);
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
    const parsed = &model.doc;

    var summary_buffer: [256]u8 = undefined;
    const summary_text = try std.fmt.bufPrintZ(
        &summary_buffer,
        "X2 {d}/{d}  submeshes {d}  vertices {d}  faces {d}  triangles {d}",
        .{
            state.model_index + 1,
            state.catalog.model_entries.len,
            model.submeshes.len,
            parsed.vertices.len,
            parsed.polygons.len,
            parsed.triangle_count,
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
    const mesh_text = try std.fmt.bufPrintZ(&mesh_buffer, "Bounds center: {d:.2}, {d:.2}, {d:.2}", .{ model.bounds.center.x, model.bounds.center.y, model.bounds.center.z });
    drawAppText(state, mesh_text, 56, 378, 20, .light_gray);

    var material_buffer: [384]u8 = undefined;
    const material_text = try std.fmt.bufPrintZ(&material_buffer, "Preview radius: {d:.2}", .{model.bounds.radius});
    drawAppText(state, material_text, 56, 410, 20, .light_gray);

    var texture_buffer: [384]u8 = undefined;
    const texture_text = try std.fmt.bufPrintZ(
        &texture_buffer,
        "First texture: {s}",
        .{if (model.submeshes.len > 0)
            (if (model.submeshes[0].texture) |texture| texture.path else model.submeshes[0].texture_filename orelse "<none>")
        else
            "<none>"},
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

    const grid_slices: i32 = @intFromFloat(@min(@max(model.bounds.radius * 6.0, 10.0), 80.0));
    const grid_spacing = @max(model.bounds.radius / 2.0, 0.5);
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

fn drawGameplayLevelViewport(state: *const AppState) void {
    const loaded_track_preview = state.current_track_preview orelse return;
    const runner = state.level_runner orelse {
        debug_levels.drawLevelViewport(state);
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
    const player_forward = runner.worldForward(loaded_track_preview);
    const player_up = runner.worldUp(loaded_track_preview);
    const player_floor = loaded_track_preview.sampleFloorHeightAtGridPosition(
        runner.current_global_row,
        runner.resolved_lane_index,
        runner.row_position,
    ) orelse 0.0;
    const target = rl.Vector3{
        .x = player_position.x + (player_forward.x * 8.0) + (player_up.x * 0.62),
        .y = player_position.y + (player_forward.y * 8.0) + (player_up.y * 0.62),
        .z = player_position.z + (player_forward.z * 8.0) + (player_up.z * 0.62),
    };
    // PORT(partial): `cRCameraman::AI()` seeds the chase camera from the player's world X,
    // a fixed +1.8 Y offset, and a -0.5 Z offset before applying the richer matrix blend path.
    const attachment_camera = runner.movement_mode == .attachment and runner.attachment_follow.active;
    const position = if (attachment_camera)
        rl.Vector3{
            .x = player_position.x - (player_forward.x * 2.2) + (player_up.x * 1.6),
            .y = player_position.y - (player_forward.y * 2.2) + (player_up.y * 1.6),
            .z = player_position.z - (player_forward.z * 2.2) + (player_up.z * 1.6),
        }
    else
        rl.Vector3{
            .x = player_position.x * 0.5,
            .y = player_floor + 1.8,
            .z = player_position.z - 0.5,
        };
    const up = if (attachment_camera) player_up else rl.Vector3{ .x = 0.0, .y = 1.0, .z = 0.0 };

    return .{
        .position = position,
        .target = target,
        .up = up,
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

fn triangleCountForObject(loaded_object: object.LoadedObject) usize {
    var total: usize = 0;
    for (loaded_object.submeshes) |submesh| {
        total += submesh.triangle_count;
    }
    return total;
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
        .levels => .segments,
        .segments => .textures,
    };
}

fn optionalUsizeToText(buffer: []u8, value: ?usize) []const u8 {
    return if (value != null) std.fmt.bufPrint(buffer, "{d}", .{value.?}) catch "?" else "-";
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
    try std.testing.expect(!highScoreRowsShowReplay(.postal, false));
    try std.testing.expect(highScoreRowsShowReplay(.challenge, false));
    try std.testing.expect(!highScoreRowsShowReplay(.challenge, true));
}

test "route map screen modes follow windows route-map entry paths" {
    try std.testing.expectEqual(RouteMapScreenMode.normal, defaultRouteMapScreenMode(.postal));
    try std.testing.expectEqual(RouteMapScreenMode.replay, defaultRouteMapScreenMode(.time_trial));
    try std.testing.expect(routeMapAllowsRouteSwitching(.normal));
    try std.testing.expect(routeMapAllowsRouteSwitching(.replay));
    try std.testing.expect(!routeMapAllowsRouteSwitching(.post_completion_exit));
    try std.testing.expectEqualStrings("Back", routeMapBackLabelForScreenMode(.normal));
    try std.testing.expectEqualStrings("Back", routeMapBackLabelForScreenMode(.replay));
    try std.testing.expectEqualStrings("Exit", routeMapBackLabelForScreenMode(.post_completion_exit));
}

test "route map body text stays empty without route script copy" {
    try std.testing.expectEqualStrings("", routeMapBodyText(null));
    try std.testing.expectEqualStrings("My first route!", routeMapBodyText("My first route!"));
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

test "new game menu mapping matches frontend route modes" {
    try std.testing.expectEqual(NewGameMenuItem.postal_mode, newGameMenuItemForFrontendMode(.postal));
    try std.testing.expectEqual(NewGameMenuItem.time_trial, newGameMenuItemForFrontendMode(.time_trial));
    try std.testing.expectEqual(NewGameMenuItem.challenge_mode, newGameMenuItemForFrontendMode(.challenge));
    try std.testing.expectEqual(NewGameMenuItem.tutorial, newGameMenuItemForFrontendMode(.tutorial));
    try std.testing.expectEqual(@as(usize, 1), newGameMenuIndexForItem(.postal_mode));
    try std.testing.expectEqual(@as(usize, 2), newGameMenuIndexForItem(.time_trial));
    try std.testing.expectEqual(@as(usize, 4), newGameMenuIndexForItem(.help));
}

test "postal unlock limit stops at the highest available route" {
    try std.testing.expectEqual(@as(usize, 2), AppState.nextPostalUnlockLimit(1, 0x32, 1));
    try std.testing.expectEqual(@as(usize, 0x32), AppState.nextPostalUnlockLimit(0x32, 0x32, 0x32));
    try std.testing.expectEqual(@as(usize, 0x33), AppState.nextPostalUnlockLimit(0x33, 0x33, 0x33));
    try std.testing.expectEqual(@as(usize, 0x32), AppState.nextPostalUnlockLimit(0x33, 0x32, 0x40));
}

test "postal high-score commit gates on the final shipped route" {
    try std.testing.expect(!AppState.postalCompletionCommitsHighScore(1, 0x32));
    try std.testing.expect(!AppState.postalCompletionCommitsHighScore(0x31, 0x32));
    try std.testing.expect(AppState.postalCompletionCommitsHighScore(0x32, 0x32));
    try std.testing.expect(AppState.postalCompletionCommitsHighScore(0x33, 0x33));
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
