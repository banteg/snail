const std = @import("std");
const rl = @import("raylib");
const assets = @import("assets.zig");
const background = @import("background.zig");
const game_font = @import("game_font.zig");
const gameplay = @import("gameplay.zig");
const high_score = @import("high_score.zig");
const intro = @import("intro.zig");
const sim = @import("sim.zig");
const track = @import("track.zig");
const object = @import("object.zig");
const segment = @import("segment.zig");
const level = @import("level.zig");
const x2 = @import("x2.zig");
const xanim = @import("xanim.zig");

const window_width = 1280;
const window_height = 720;

const default_archive_path = "artifacts/bin/SnailMail.dat";
const splash_background_path = "BACKGROUNDS/SPLASH.TXT";
const intro_background_path = "BACKGROUNDS/SPACERED.TXT";
const main_menu_background_path = "BACKGROUNDS/MENUBG.TXT";
const help_background_path = "BACKGROUNDS/HELP.TXT";
const intro_script_path = "INTRO/INTRO.TXT";
const credits_script_path = "INTRO/CREDITS.TXT";
const intro_music_path = "MUSIC/INTROTEXT.OGG";
const default_texture_path = "OBJECTS/FONT/FONT-MENU-HOVER.TGA";
const default_audio_path = "MUSIC/MAINMENU.OGG";
const default_model_path = "X/TURBO-BOBALONG-000.X2";
const default_object_path = "OBJECTS/FONT3D/_OBJECT.TXT";
const default_level_path = "LEVELS/TUTORIAL.TXT";
const simulation_step_seconds = 1.0 / 60.0;
const boot_phase_duration_ticks: u64 = 75;
const status_message_duration_ticks: u32 = 180;

const Options = struct {
    archive_path: []const u8 = default_archive_path,
    command: AppCommand = .game,
};

const AppCommand = enum {
    game,
    debug,
    smoke,
};

// PORT(scaffold): the default `snail` path is now a forward-pass boot and menu shell.
// Replace this with the real menu flow once original assets, transitions, and actions are ported.
const GamePhase = enum {
    boot,
    intro,
    main_menu,
    new_game_menu,
    high_scores_menu,
    credits,
    help,
    level,
};

// PORT(partial): these top-level labels match the recovered front-end constructor at `sub_419b50`.
// Actions for `Options` and deeper score routing are still scaffolded until their handlers are ported.
const MainMenuItem = enum {
    new_game,
    high_scores,
    options,
    credits,
    exit,

    fn label(self: MainMenuItem) [:0]const u8 {
        return switch (self) {
            .new_game => "New Game",
            .high_scores => "High Scores",
            .options => "Options",
            .credits => "Credits",
            .exit => "Exit",
        };
    }
};

const main_menu_items = [_]MainMenuItem{ .new_game, .high_scores, .options, .credits, .exit };

// PORT(partial): these labels and mode actions match the recovered `sub_417bc0` / `sub_417eb0` new-game flow.
// `Help` is still only a partial screen port, and later progression beyond the first level remains unresolved.
const NewGameMenuItem = enum {
    tutorial,
    postal_mode,
    time_trial,
    challenge_mode,
    help,
    back,

    fn label(self: NewGameMenuItem) [:0]const u8 {
        return switch (self) {
            .tutorial => "Tutorial",
            .postal_mode => "Postal Mode",
            .time_trial => "Time Trial",
            .challenge_mode => "Challenge Mode",
            .help => "Help",
            .back => "Back",
        };
    }
};

const new_game_menu_items = [_]NewGameMenuItem{
    .tutorial,
    .postal_mode,
    .time_trial,
    .challenge_mode,
    .help,
    .back,
};

// PORT(partial): these mode ids match the recovered `sub_417eb0` launcher and `sub_443650` level-name switch.
// We only port the initial level handoff here, not the original front-end's level-select or progression flow yet.
const FrontendLevelMode = enum(i32) {
    postal = 0,
    challenge = 1,
    time_trial = 4,
    tutorial = 7,
};

const HighScoresMenuItem = enum {
    postal_high_scores,
    challenge_high_scores,
    back,

    fn label(self: HighScoresMenuItem) [:0]const u8 {
        return switch (self) {
            .postal_high_scores => "Postal High Scores",
            .challenge_high_scores => "Challenge High Scores",
            .back => "Back",
        };
    }
};

const high_scores_menu_items = [_]HighScoresMenuItem{
    .postal_high_scores,
    .challenge_high_scores,
    .back,
};

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
    command: AppCommand,
    audio_ready: bool,
    should_exit: bool = false,
    simulation_clock: sim.FixedStepClock = sim.FixedStepClock.init(simulation_step_seconds),
    render_time_seconds: f64 = 0.0,
    game_phase: GamePhase = .boot,
    game_phase_ticks: u64 = 0,
    menu_index: usize = 0,
    new_game_menu_index: usize = 0,
    high_scores_menu_index: usize = 0,
    high_score_tables: high_score.Tables,
    game_status_message: ?[]const u8 = null,
    game_status_ticks: u32 = 0,
    active_level_segment_index: ?usize = null,
    active_level_message: ?[]const u8 = null,
    mouse_level_lane_target: ?usize = null,
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
    current_sound: ?assets.LoadedSound = null,
    current_music: ?assets.LoadedMusic = null,
    current_model: ?x2.LoadedModel = null,
    current_animation: ?xanim.Player = null,
    current_object: ?object.LoadedObject = null,
    current_level: ?level.Definition = null,
    current_segment: ?segment.Definition = null,
    current_track_preview: ?track.LoadedLevelPreview = null,
    current_game_background: ?background.Loaded = null,
    current_text_script: ?intro.Definition = null,
    level_runner: ?gameplay.Runner = null,
    pending_level_input: gameplay.RunnerInput = .{},

    fn init(allocator: std.mem.Allocator, options: Options, audio_ready: bool) !AppState {
        var catalog = try assets.Catalog.init(allocator, options.archive_path);
        errdefer catalog.deinit();
        var animation_catalog = try xanim.Catalog.load(allocator, &catalog);
        errdefer animation_catalog.deinit();
        var ui_font = try game_font.Loaded.load(allocator, &catalog);
        errdefer ui_font.deinit();

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
            .command = options.command,
            .audio_ready = audio_ready,
            .high_score_tables = high_score.Tables.initDefault(),
            .texture_index = texture_index,
            .audio_index = audio_index,
            .model_index = model_index,
            .object_index = object_index,
            .level_index = level_index,
        };
        errdefer state.deinit();

        switch (options.command) {
            .debug, .smoke => {
                try state.reloadTexture();
                try state.reloadModel();
                try state.reloadObject();
                try state.reloadLevel();
            },
            .game => try state.enterGamePhase(.boot),
        }
        return state;
    }

    fn deinit(self: *AppState) void {
        self.stopAudioPreview();
        self.unloadGameBackground();

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
            script.deinit();
            self.current_text_script = null;
        }

        if (self.current_texture) |*texture| {
            texture.unload();
            self.current_texture = null;
        }

        self.ui_font.deinit();
        self.animation_catalog.deinit();
        self.catalog.deinit();
    }

    fn warmupSmokeTest(self: *AppState) !void {
        if (!self.audio_ready or self.catalog.audio_entries.len == 0) {
            return;
        }

        try self.previewSound();
        self.stopAudioPreview();
        try self.previewMusic();
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

    fn simulateGameTick(self: *AppState, runner_input: gameplay.RunnerInput) !void {
        self.game_phase_ticks += 1;
        if (self.game_status_ticks > 0) {
            self.game_status_ticks -= 1;
            if (self.game_status_ticks == 0) {
                self.game_status_message = null;
            }
        }

        if (self.game_phase == .boot and self.game_phase_ticks >= boot_phase_duration_ticks) {
            try self.enterGamePhase(.intro);
        }

        if (self.game_phase == .intro or self.game_phase == .credits) {
            if (self.currentTextScriptDurationTicks()) |duration_ticks| {
                if (self.game_phase_ticks >= duration_ticks) {
                    try self.enterGamePhase(.main_menu);
                    return;
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
        }
    }

    fn handleGameInput(self: *AppState) !void {
        if (rl.isKeyPressed(.escape)) {
            switch (self.game_phase) {
                .level => try self.enterGamePhase(.main_menu),
                .boot, .main_menu => self.should_exit = true,
                .intro, .new_game_menu, .high_scores_menu, .credits, .help => try self.enterGamePhase(.main_menu),
            }
            return;
        }

        switch (self.game_phase) {
            .boot => {
                if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    try self.enterGamePhase(.intro);
                }
            },
            .intro => {
                if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    try self.enterGamePhase(.main_menu);
                }
            },
            .main_menu => {
                if (rl.isKeyPressed(.up)) {
                    self.menu_index = wrappedIndex(main_menu_items.len, self.menu_index, -1);
                }
                if (rl.isKeyPressed(.down)) {
                    self.menu_index = wrappedIndex(main_menu_items.len, self.menu_index, 1);
                }
                if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    try self.activateMainMenuItem(main_menu_items[self.menu_index]);
                }
            },
            .new_game_menu => {
                if (rl.isKeyPressed(.up)) {
                    self.new_game_menu_index = wrappedIndex(new_game_menu_items.len, self.new_game_menu_index, -1);
                }
                if (rl.isKeyPressed(.down)) {
                    self.new_game_menu_index = wrappedIndex(new_game_menu_items.len, self.new_game_menu_index, 1);
                }
                if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    try self.activateNewGameMenuItem(new_game_menu_items[self.new_game_menu_index]);
                }
            },
            .high_scores_menu => {
                if (rl.isKeyPressed(.up)) {
                    self.high_scores_menu_index = wrappedIndex(high_scores_menu_items.len, self.high_scores_menu_index, -1);
                }
                if (rl.isKeyPressed(.down)) {
                    self.high_scores_menu_index = wrappedIndex(high_scores_menu_items.len, self.high_scores_menu_index, 1);
                }
                if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    try self.activateHighScoresMenuItem(high_scores_menu_items[self.high_scores_menu_index]);
                }
            },
            .credits, .help => {
                if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    try self.enterGamePhase(.main_menu);
                }
            },
            .level => {
                if (rl.isKeyPressed(.enter)) {
                    if (self.level_runner) |runner| {
                        if (runner.finished) {
                            try self.enterGamePhase(.main_menu);
                            return;
                        }
                    }
                }
                if (rl.isKeyPressed(.left) or rl.isKeyPressed(.a)) {
                    self.mouse_level_lane_target = null;
                    self.pending_level_input.lane_delta -= 1;
                }
                if (rl.isKeyPressed(.right) or rl.isKeyPressed(.d)) {
                    self.mouse_level_lane_target = null;
                    self.pending_level_input.lane_delta += 1;
                }
                if (rl.isKeyPressed(.up) or rl.isKeyPressed(.w)) {
                    self.pending_level_input.speed_delta_rows_per_second += 2.0;
                }
                if (rl.isKeyPressed(.down) or rl.isKeyPressed(.s)) {
                    self.pending_level_input.speed_delta_rows_per_second -= 2.0;
                }
                if (rl.isKeyPressed(.space)) {
                    self.pending_level_input.toggle_pause = true;
                }
                if (rl.isKeyPressed(.r)) {
                    self.mouse_level_lane_target = null;
                    self.pending_level_input.reset = true;
                }
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
            },
        }
    }

    fn enterGamePhase(self: *AppState, phase: GamePhase) !void {
        self.game_phase = phase;
        self.game_phase_ticks = 0;
        try self.syncGamePhaseResources();
    }

    fn activateMainMenuItem(self: *AppState, item: MainMenuItem) !void {
        switch (item) {
            .new_game => try self.enterGamePhase(.new_game_menu),
            .high_scores => try self.enterGamePhase(.high_scores_menu),
            .options => self.setGameStatusMessage("Unavailable."),
            .credits => try self.enterGamePhase(.credits),
            .exit => self.should_exit = true,
        }
    }

    fn activateNewGameMenuItem(self: *AppState, item: NewGameMenuItem) !void {
        switch (item) {
            .tutorial => try self.enterFrontendLevelMode(.tutorial),
            .postal_mode => try self.enterFrontendLevelMode(.postal),
            .time_trial => try self.enterFrontendLevelMode(.time_trial),
            .challenge_mode => try self.enterFrontendLevelMode(.challenge),
            .help => try self.enterGamePhase(.help),
            .back => try self.enterGamePhase(.main_menu),
        }
    }

    fn activateHighScoresMenuItem(self: *AppState, item: HighScoresMenuItem) !void {
        switch (item) {
            .postal_high_scores => self.high_scores_menu_index = 0,
            .challenge_high_scores => self.high_scores_menu_index = 1,
            .back => try self.enterGamePhase(.main_menu),
        }
    }

    fn enterGameplayShell(self: *AppState, level_path: []const u8) !void {
        try self.loadGameLevel(level_path);
        try self.enterGamePhase(.level);
    }

    fn enterFrontendLevelMode(self: *AppState, mode: FrontendLevelMode) !void {
        var path_buffer: [64]u8 = undefined;
        const level_path = try frontendLevelPath(mode, 0, &path_buffer);
        try self.enterGameplayShell(level_path);
    }

    fn syncGamePhaseResources(self: *AppState) !void {
        switch (self.game_phase) {
            .boot => {
                self.stopAudioPreview();
                self.active_level_segment_index = null;
                self.active_level_message = null;
                self.mouse_level_lane_target = null;
                self.unloadTextScript();
                try self.loadGameBackground(splash_background_path);
            },
            .intro => {
                self.active_level_segment_index = null;
                self.active_level_message = null;
                self.mouse_level_lane_target = null;
                try self.loadGameBackground(intro_background_path);
                try self.playMusicByPath(intro_music_path);
                try self.loadTextScript(intro_script_path);
            },
            .main_menu, .new_game_menu, .high_scores_menu => {
                self.active_level_segment_index = null;
                self.active_level_message = null;
                self.mouse_level_lane_target = null;
                self.unloadTextScript();
                try self.loadGameBackground(main_menu_background_path);
                try self.playMusicByPath(default_audio_path);
            },
            .credits => {
                self.active_level_segment_index = null;
                self.active_level_message = null;
                self.mouse_level_lane_target = null;
                try self.loadGameBackground(intro_background_path);
                try self.playMusicByPath(intro_music_path);
                try self.loadTextScript(credits_script_path);
            },
            .help => {
                self.active_level_segment_index = null;
                self.active_level_message = null;
                self.mouse_level_lane_target = null;
                self.unloadTextScript();
                try self.loadGameBackground(help_background_path);
                try self.playMusicByPath(default_audio_path);
            },
            .level => {
                self.stopAudioPreview();
                self.mouse_level_lane_target = null;
                self.unloadTextScript();
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
                if (!rl.isMusicStreamPlaying(music.music)) {
                    rl.playMusicStream(music.music);
                }
                return;
            }
        }

        self.stopAudioPreview();
        self.current_music = try self.catalog.loadMusicByPath(self.allocator, path);
        rl.playMusicStream(self.current_music.?.music);
    }

    fn playSoundByPath(self: *AppState, path: []const u8) !void {
        if (!self.audio_ready) return;
        if (self.current_sound) |*sound| {
            sound.unload();
            self.current_sound = null;
        }

        self.current_sound = try self.catalog.loadSoundByPath(self.allocator, path);
        rl.playSound(self.current_sound.?.sound);
    }

    fn syncActiveLevelSegment(self: *AppState, replay_sample_on_match: bool) !void {
        const loaded_level = self.current_level orelse {
            self.active_level_segment_index = null;
            self.active_level_message = null;
            return;
        };
        const loaded_track_preview = self.current_track_preview orelse {
            self.active_level_segment_index = null;
            self.active_level_message = null;
            return;
        };
        const runner = self.level_runner orelse {
            self.active_level_segment_index = null;
            self.active_level_message = null;
            return;
        };

        const row_location = loaded_track_preview.locateRow(runner.current_global_row) orelse {
            self.active_level_segment_index = null;
            self.active_level_message = null;
            return;
        };
        if (row_location.segment_index >= loaded_level.segments.len) {
            self.active_level_segment_index = null;
            self.active_level_message = null;
            return;
        }

        self.level_segment_index = row_location.segment_index;
        const segment_entry = &loaded_level.segments[row_location.segment_index];
        const segment_changed = self.active_level_segment_index == null or self.active_level_segment_index.? != row_location.segment_index;
        self.active_level_segment_index = row_location.segment_index;
        self.active_level_message = segment_entry.message;

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
        self.current_game_background = try background.Loaded.loadByPath(self.allocator, &self.catalog, script_path);
    }

    fn loadTextScript(self: *AppState, path: []const u8) !void {
        self.unloadTextScript();
        self.current_text_script = try intro.loadByPath(self.allocator, &self.catalog, path);
    }

    fn unloadTextScript(self: *AppState) void {
        if (self.current_text_script) |*script| {
            script.deinit();
            self.current_text_script = null;
        }
    }

    fn currentTextScriptDurationTicks(self: *const AppState) ?u64 {
        const script = self.current_text_script orelse return null;
        const ticks = @as(u64, @intFromFloat(@max(script.duration * 60.0, 1.0)));
        return ticks;
    }

    fn currentTextScriptProgress(self: *const AppState) ?f32 {
        const duration_ticks = self.currentTextScriptDurationTicks() orelse return null;
        if (duration_ticks == 0) return 1.0;
        return std.math.clamp(
            @as(f32, @floatFromInt(self.game_phase_ticks)) / @as(f32, @floatFromInt(duration_ticks)),
            0.0,
            1.0,
        );
    }

    fn currentTextScript(self: *const AppState) ?*const intro.Definition {
        if (self.current_text_script) |*script| {
            return script;
        }
        return null;
    }

    fn currentTextScriptSkipLabel(self: *const AppState) [:0]const u8 {
        return switch (self.game_phase) {
            .intro => "Enter, Space, or Esc to continue",
            .credits => "Enter, Space, or Esc back",
            else => "",
        };
    }

    fn unloadGameBackground(self: *AppState) void {
        if (self.current_game_background) |*loaded_background| {
            loaded_background.deinit();
            self.current_game_background = null;
        }
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
        rl.playSound(sound.sound);
        self.current_sound = sound;
    }

    fn previewMusic(self: *AppState) !void {
        if (!self.audio_ready or self.catalog.audio_entries.len == 0) {
            return;
        }

        self.stopAudioPreview();
        const music = try self.catalog.loadMusic(self.allocator, self.catalog.audio_entries[self.audio_index]);
        rl.playMusicStream(music.music);
        self.current_music = music;
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

fn parseArgs(allocator: std.mem.Allocator) !Options {
    var argv = std.ArrayList([]const u8).empty;
    defer argv.deinit(allocator);

    var args = try std.process.argsWithAllocator(allocator);
    defer args.deinit();

    _ = args.skip();
    while (args.next()) |arg| {
        try argv.append(allocator, arg);
    }

    return parseArgsFromSlice(argv.items);
}

fn parseArgsFromSlice(args: []const []const u8) !Options {
    var options = Options{};

    var index: usize = 0;
    while (index < args.len) : (index += 1) {
        const arg = args[index];
        if (std.mem.eql(u8, arg, "--archive-path")) {
            index += 1;
            if (index >= args.len) return error.MissingArchivePath;
            options.archive_path = args[index];
            continue;
        }
        if (std.mem.eql(u8, arg, "game")) {
            options.command = .game;
            continue;
        }
        if (std.mem.eql(u8, arg, "debug")) {
            options.command = .debug;
            continue;
        }
        if (std.mem.eql(u8, arg, "browser")) {
            if (options.command != .debug) return error.UnknownCommand;
            continue;
        }
        if (std.mem.eql(u8, arg, "smoke")) {
            options.command = .smoke;
            continue;
        }
        return error.UnknownCommand;
    }

    return options;
}

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    const options = try parseArgs(allocator);

    rl.initWindow(window_width, window_height, "snail");
    defer rl.closeWindow();

    rl.initAudioDevice();
    const audio_ready = rl.isAudioDeviceReady();
    defer {
        if (audio_ready) {
            rl.closeAudioDevice();
        }
    }

    var state = try AppState.init(allocator, options, audio_ready);
    defer state.deinit();
    var frame_timer = try std.time.Timer.start();

    if (options.command == .smoke) {
        try state.warmupSmokeTest();
    }

    rl.setTargetFPS(144);
    var frames_left: usize = if (options.command == .smoke) 3 else std.math.maxInt(usize);

    while (!rl.windowShouldClose() and !state.should_exit and frames_left > 0) {
        const frame_delta_seconds = @as(f64, @floatFromInt(frame_timer.lap())) / @as(f64, std.time.ns_per_s);
        if (options.command == .smoke) {
            frames_left -= 1;
        }

        try state.handleInput();
        try state.update(frame_delta_seconds);

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
        .width = @floatFromInt(window_width),
        .height = @floatFromInt(window_height),
    };

    const art_layout = if (state.current_game_background) |loaded_background|
        loaded_background.draw(full_bounds)
    else blk: {
        rl.drawRectangleRec(full_bounds, .black);
        break :blk null;
    };

    switch (state.game_phase) {
        .boot => try drawGameBootUi(state, art_layout),
        .intro => try drawTextScriptUi(state),
        .main_menu => try drawMainMenuUi(state, art_layout),
        .new_game_menu => try drawNewGameMenuUi(state, art_layout),
        .high_scores_menu => try drawHighScoresMenuUi(state, art_layout),
        .credits => try drawTextScriptUi(state),
        .help => drawHelpUi(state),
        .level => try drawGameplayLevelUi(state, art_layout),
    }
}

fn drawGameBootUi(state: *const AppState, art_layout: ?background.Layout) !void {
    const panel = if (art_layout) |layout|
        layout.mapRect(36.0, 418.0, 568.0, 70.0)
    else
        rl.Rectangle{ .x = 72.0, .y = 596.0, .width = 1136.0, .height = 90.0 };

    rl.drawRectangleRounded(panel, 0.18, 8, .{ .r = 0, .g = 0, .b = 0, .a = 176 });

    const title_point = if (art_layout) |layout|
        layout.mapPoint(56.0, 438.0)
    else
        rl.Vector2{ .x = 96.0, .y = 624.0 };
    const prompt_point = if (art_layout) |layout|
        layout.mapPoint(250.0, 438.0)
    else
        rl.Vector2{ .x = 332.0, .y = 624.0 };
    const hint_point = if (art_layout) |layout|
        layout.mapPoint(250.0, 462.0)
    else
        rl.Vector2{ .x = 332.0, .y = 650.0 };

    drawAppText(state, "snail", @intFromFloat(title_point.x), @intFromFloat(title_point.y), 30, .orange);

    const prompt_color: rl.Color = if ((state.game_phase_ticks / 20) % 2 == 0) .gold else .light_gray;
    drawAppText(state, "Press Enter to continue", @intFromFloat(prompt_point.x), @intFromFloat(prompt_point.y), 22, prompt_color);
    drawAppText(state, "Esc quits", @intFromFloat(hint_point.x), @intFromFloat(hint_point.y), 18, .light_gray);
}

fn drawMainMenuUi(state: *const AppState, art_layout: ?background.Layout) !void {
    const menu_panel = if (art_layout) |layout|
        layout.mapRect(56.0, 104.0, 220.0, 250.0)
    else
        rl.Rectangle{ .x = 96.0, .y = 220.0, .width = 360.0, .height = 260.0 };
    const detail_panel = if (art_layout) |layout|
        layout.mapRect(292.0, 104.0, 248.0, 250.0)
    else
        rl.Rectangle{ .x = 492.0, .y = 220.0, .width = 640.0, .height = 260.0 };
    const footer_panel = if (art_layout) |layout|
        layout.mapRect(56.0, 370.0, 484.0, 38.0)
    else
        rl.Rectangle{ .x = 96.0, .y = 516.0, .width = 1036.0, .height = 44.0 };

    rl.drawRectangleRounded(menu_panel, 0.08, 8, .{ .r = 0, .g = 0, .b = 0, .a = 148 });
    rl.drawRectangleRounded(detail_panel, 0.08, 8, .{ .r = 0, .g = 0, .b = 0, .a = 148 });

    const title_point = if (art_layout) |layout|
        layout.mapPoint(72.0, 78.0)
    else
        rl.Vector2{ .x = 96.0, .y = 176.0 };
    drawAppText(state, "Main Menu", @intFromFloat(title_point.x), @intFromFloat(title_point.y), 28, .ray_white);

    for (main_menu_items, 0..) |item, index| {
        drawMenuItem(state, art_layout, index, state.menu_index, item.label());
    }

    const selected = main_menu_items[state.menu_index];
    const detail_title = if (art_layout) |layout|
        layout.mapPoint(312.0, 126.0)
    else
        rl.Vector2{ .x = 520.0, .y = 252.0 };
    const control_note = if (art_layout) |layout|
        layout.mapPoint(312.0, 170.0)
    else
        rl.Vector2{ .x = 520.0, .y = 304.0 };
    const selection_note = if (art_layout) |layout|
        layout.mapPoint(312.0, 210.0)
    else
        rl.Vector2{ .x = 520.0, .y = 348.0 };
    const status_note = if (art_layout) |layout|
        layout.mapPoint(312.0, 276.0)
    else
        rl.Vector2{ .x = 520.0, .y = 424.0 };

    drawAppText(state, selected.label(), @intFromFloat(detail_title.x), @intFromFloat(detail_title.y), 30, .gold);
    drawAppText(state, "Up/Down select", @intFromFloat(control_note.x), @intFromFloat(control_note.y), 20, .ray_white);
    drawAppText(state, "Enter confirm", @intFromFloat(control_note.x), @intFromFloat(control_note.y + 26.0), 20, .ray_white);
    drawAppText(state, "Esc quit", @intFromFloat(selection_note.x), @intFromFloat(selection_note.y), 20, .light_gray);

    if (selected == .options) {
        drawAppText(state, "Unavailable", @intFromFloat(status_note.x), @intFromFloat(status_note.y), 18, .sky_blue);
    }

    if (state.game_status_message) |message| {
        rl.drawRectangleRounded(footer_panel, 0.2, 8, .{ .r = 0, .g = 0, .b = 0, .a = 172 });
        try drawWrappedText(state, message, @intFromFloat(footer_panel.x + 20.0), @intFromFloat(footer_panel.y + 11.0), @intFromFloat(footer_panel.width - 32.0), 20, .ray_white);
    }
}

fn drawNewGameMenuUi(state: *const AppState, art_layout: ?background.Layout) !void {
    const panels = menuPanels(art_layout);
    rl.drawRectangleRounded(panels.menu_panel, 0.08, 8, .{ .r = 0, .g = 0, .b = 0, .a = 148 });
    rl.drawRectangleRounded(panels.detail_panel, 0.08, 8, .{ .r = 0, .g = 0, .b = 0, .a = 148 });
    drawAppText(state, "New Game", panels.title_x, panels.title_y, 28, .ray_white);

    for (new_game_menu_items, 0..) |item, index| {
        drawMenuItem(state, art_layout, index, state.new_game_menu_index, item.label());
    }

    const selected = new_game_menu_items[state.new_game_menu_index];
    drawAppText(state, selected.label(), panels.detail_title_x, panels.detail_title_y, 30, .gold);
    if (newGameMenuHint(selected)) |hint| {
        try drawWrappedText(state, hint, panels.detail_body_x, panels.detail_body_y, panels.detail_width, 22, .light_gray);
    }
    drawAppText(state, "Up/Down select", panels.control_x, panels.control_y, 20, .ray_white);
    drawAppText(state, "Enter confirm", panels.control_x, panels.control_y + 26, 20, .ray_white);
    drawAppText(state, "Esc back", panels.control_x, panels.control_y + 66, 20, .light_gray);

    if (state.game_status_message) |message| {
        rl.drawRectangleRounded(panels.footer_panel, 0.2, 8, .{ .r = 0, .g = 0, .b = 0, .a = 172 });
        try drawWrappedText(state, message, @intFromFloat(panels.footer_panel.x + 20.0), @intFromFloat(panels.footer_panel.y + 11.0), @intFromFloat(panels.footer_panel.width - 32.0), 20, .ray_white);
    }
}

fn drawHighScoresMenuUi(state: *const AppState, art_layout: ?background.Layout) !void {
    const panels = menuPanels(art_layout);
    rl.drawRectangleRounded(panels.menu_panel, 0.08, 8, .{ .r = 0, .g = 0, .b = 0, .a = 148 });
    rl.drawRectangleRounded(panels.detail_panel, 0.08, 8, .{ .r = 0, .g = 0, .b = 0, .a = 148 });
    drawAppText(state, "High Scores", panels.title_x, panels.title_y, 28, .ray_white);

    for (high_scores_menu_items, 0..) |item, index| {
        drawMenuItem(state, art_layout, index, state.high_scores_menu_index, item.label());
    }

    const selected = high_scores_menu_items[state.high_scores_menu_index];
    drawAppText(state, selected.label(), panels.detail_title_x, panels.detail_title_y, 30, .gold);

    switch (selected) {
        .postal_high_scores => drawHighScoreTable(state, .postal, panels),
        .challenge_high_scores => drawHighScoreTable(state, .challenge, panels),
        .back => {
            try drawWrappedText(state, "Return to the main menu.", panels.detail_body_x, panels.detail_body_y, panels.detail_width, 22, .light_gray);
        },
    }

    drawAppText(state, "Up/Down select", panels.control_x, panels.control_y, 20, .ray_white);
    drawAppText(state, "Enter confirm", panels.control_x, panels.control_y + 26, 20, .ray_white);
    drawAppText(state, "Esc back", panels.control_x, panels.control_y + 66, 20, .light_gray);

    if (state.game_status_message) |message| {
        rl.drawRectangleRounded(panels.footer_panel, 0.2, 8, .{ .r = 0, .g = 0, .b = 0, .a = 172 });
        try drawWrappedText(state, message, @intFromFloat(panels.footer_panel.x + 20.0), @intFromFloat(panels.footer_panel.y + 11.0), @intFromFloat(panels.footer_panel.width - 32.0), 20, .ray_white);
    }
}

fn drawHighScoreTable(state: *const AppState, mode: high_score.Mode, panels: MenuPanels) void {
    const entries = state.high_score_tables.entries(mode);
    const row_start_y = panels.detail_body_y + 28;
    const row_height = 18;
    const rank_x = panels.detail_body_x;
    const name_x = panels.detail_body_x + 44;
    const score_x = panels.detail_body_x + 292;
    const replay_x = panels.detail_body_x + 438;

    drawAppText(state, mode.label(), panels.detail_body_x, panels.detail_body_y, 18, .sky_blue);
    drawAppText(state, "#", rank_x, panels.detail_body_y + 26, 16, .light_gray);
    drawAppText(state, "Name", name_x, panels.detail_body_y + 26, 16, .light_gray);
    drawAppText(state, "Score", score_x, panels.detail_body_y + 26, 16, .light_gray);
    drawAppText(state, "Replay", replay_x, panels.detail_body_y + 26, 16, .light_gray);

    for (entries, 0..) |entry, index| {
        const row_y = row_start_y + @as(i32, @intCast(index)) * row_height;
        if ((index & 1) == 0) {
            rl.drawRectangleRounded(
                .{
                    .x = @floatFromInt(panels.detail_body_x - 8),
                    .y = @floatFromInt(row_y - 2),
                    .width = @floatFromInt(panels.detail_width - 4),
                    .height = 18.0,
                },
                0.16,
                4,
                .{ .r = 255, .g = 255, .b = 255, .a = 12 },
            );
        }

        var rank_buffer: [8]u8 = undefined;
        const rank_text = std.fmt.bufPrint(&rank_buffer, "{d}.", .{index + 1}) catch "";
        drawAppText(state, rank_text, rank_x, row_y, 16, .ray_white);
        drawAppText(state, highScoreDisplayName(&entry), name_x, row_y, 16, .ray_white);

        var score_buffer: [32]u8 = undefined;
        const score_text = std.fmt.bufPrint(&score_buffer, "{d}", .{entry.score}) catch "0";
        drawAppText(state, score_text, score_x, row_y, 16, .gold);
        drawAppText(state, if (entry.has_replay) "Replay" else "-", replay_x, row_y, 16, .light_gray);
    }
}

fn highScoreDisplayName(entry: *const high_score.Entry) []const u8 {
    const name = entry.name();
    if (name.len == 0) return "---";
    return name;
}

// PORT(partial): intro and credits now share the recovered text-screen flow.
// The original loader also supports `*texture.tga(width,height)` directives and richer transforms we have not ported yet.
fn drawTextScriptUi(state: *const AppState) !void {
    const script = state.currentTextScript() orelse return;
    const progress = state.currentTextScriptProgress() orelse 0.0;
    const viewport = rl.Rectangle{
        .x = 164.0,
        .y = 84.0,
        .width = @as(f32, @floatFromInt(window_width)) - 328.0,
        .height = @as(f32, @floatFromInt(window_height)) - 168.0,
    };

    rl.drawRectangleRounded(viewport, 0.04, 8, .{ .r = 0, .g = 0, .b = 0, .a = 132 });

    const line_height: i32 = 28;
    const line_count = countLines(script.text);
    const total_height = @as(f32, @floatFromInt(@max(line_count, 1) * line_height));
    const start_y = viewport.y + viewport.height + 40.0;
    const end_y = viewport.y - total_height - 40.0;
    const base_y = std.math.lerp(start_y, end_y, progress);
    try drawCenteredMultilineText(
        state,
        script.text,
        @intFromFloat(viewport.x + viewport.width / 2.0),
        @intFromFloat(base_y),
        line_height,
        .ray_white,
    );

    const hint = state.currentTextScriptSkipLabel();
    const hint_width = measureAppText(state, hint, 18);
    rl.drawRectangleRounded(
        .{
            .x = @as(f32, @floatFromInt(window_width - hint_width - 68)),
            .y = @as(f32, @floatFromInt(window_height - 54)),
            .width = @as(f32, @floatFromInt(hint_width + 32)),
            .height = 30.0,
        },
        0.2,
        8,
        .{ .r = 0, .g = 0, .b = 0, .a = 176 },
    );
    drawAppText(state, hint, window_width - hint_width - 52, window_height - 46, 18, .light_gray);
}

fn drawHelpUi(state: *const AppState) void {
    rl.drawRectangleRounded(.{ .x = 72.0, .y = 646.0, .width = 260.0, .height = 34.0 }, 0.2, 8, .{ .r = 0, .g = 0, .b = 0, .a = 176 });
    drawAppText(state, "Enter or Esc back", 96, 654, 18, .ray_white);
}

const MenuPanels = struct {
    menu_panel: rl.Rectangle,
    detail_panel: rl.Rectangle,
    footer_panel: rl.Rectangle,
    title_x: i32,
    title_y: i32,
    detail_title_x: i32,
    detail_title_y: i32,
    detail_body_x: i32,
    detail_body_y: i32,
    detail_width: i32,
    control_x: i32,
    control_y: i32,
};

fn menuPanels(art_layout: ?background.Layout) MenuPanels {
    return if (art_layout) |layout|
        .{
            .menu_panel = layout.mapRect(56.0, 104.0, 220.0, 250.0),
            .detail_panel = layout.mapRect(292.0, 104.0, 248.0, 250.0),
            .footer_panel = layout.mapRect(56.0, 370.0, 484.0, 38.0),
            .title_x = @intFromFloat(layout.mapPoint(72.0, 78.0).x),
            .title_y = @intFromFloat(layout.mapPoint(72.0, 78.0).y),
            .detail_title_x = @intFromFloat(layout.mapPoint(312.0, 126.0).x),
            .detail_title_y = @intFromFloat(layout.mapPoint(312.0, 126.0).y),
            .detail_body_x = @intFromFloat(layout.mapPoint(312.0, 168.0).x),
            .detail_body_y = @intFromFloat(layout.mapPoint(312.0, 168.0).y),
            .detail_width = @intFromFloat(layout.mapRect(292.0, 104.0, 248.0, 250.0).width - 36.0),
            .control_x = @intFromFloat(layout.mapPoint(312.0, 250.0).x),
            .control_y = @intFromFloat(layout.mapPoint(312.0, 250.0).y),
        }
    else
        .{
            .menu_panel = .{ .x = 96.0, .y = 220.0, .width = 360.0, .height = 260.0 },
            .detail_panel = .{ .x = 492.0, .y = 220.0, .width = 640.0, .height = 260.0 },
            .footer_panel = .{ .x = 96.0, .y = 516.0, .width = 1036.0, .height = 44.0 },
            .title_x = 96,
            .title_y = 176,
            .detail_title_x = 520,
            .detail_title_y = 252,
            .detail_body_x = 520,
            .detail_body_y = 304,
            .detail_width = 580,
            .control_x = 520,
            .control_y = 400,
        };
}

fn drawMenuItem(state: *const AppState, art_layout: ?background.Layout, index: usize, selected_index: usize, label: [:0]const u8) void {
    const active = index == selected_index;
    const row_rect = if (art_layout) |layout|
        layout.mapRect(68.0, 128.0 + @as(f32, @floatFromInt(index)) * 42.0, 196.0, 32.0)
    else
        rl.Rectangle{
            .x = 112.0,
            .y = 252.0 + @as(f32, @floatFromInt(index)) * 48.0,
            .width = 328.0,
            .height = 36.0,
        };
    const label_point = if (art_layout) |layout|
        layout.mapPoint(84.0, 136.0 + @as(f32, @floatFromInt(index)) * 42.0)
    else
        rl.Vector2{ .x = 132.0, .y = 260.0 + @as(f32, @floatFromInt(index)) * 48.0 };

    if (active) {
        rl.drawRectangleRounded(row_rect, 0.25, 8, .orange);
    }
    drawAppText(state, label, @intFromFloat(label_point.x), @intFromFloat(label_point.y), 24, if (active) .black else .ray_white);
}

fn newGameMenuHint(item: NewGameMenuItem) ?[]const u8 {
    return switch (item) {
        .postal_mode => "Start the postal-mode level flow.",
        .time_trial => "Start the time-trial level flow.",
        .challenge_mode => "Start the challenge-mode level flow.",
        .help => "Open the help screen.",
        else => null,
    };
}

fn frontendLevelPath(mode: FrontendLevelMode, level_index: usize, path_buffer: []u8) ![]const u8 {
    return switch (mode) {
        .tutorial => "LEVELS/TUTORIAL.TXT",
        .challenge => "LEVELS/CHALLENGE000.TXT",
        .postal => if (level_index <= 0x32)
            try std.fmt.bufPrint(path_buffer, "LEVELS/ARCADE{d:0>3}.TXT", .{level_index})
        else
            "LEVELS/ARCADEEXTRA000.TXT",
        .time_trial => if (level_index <= 0x32)
            try std.fmt.bufPrint(path_buffer, "LEVELS/ARCADE{d:0>3}.TXT", .{level_index})
        else
            try std.fmt.bufPrint(path_buffer, "LEVELS/TIMETRIALEXTRA{d:0>3}.TXT", .{level_index - 0x32}),
    };
}

test "frontend level mode paths follow recovered launch mapping" {
    var scratch: [64]u8 = undefined;

    try std.testing.expectEqualStrings("LEVELS/TUTORIAL.TXT", try frontendLevelPath(.tutorial, 0, &scratch));
    try std.testing.expectEqualStrings("LEVELS/CHALLENGE000.TXT", try frontendLevelPath(.challenge, 0, &scratch));
    try std.testing.expectEqualStrings("LEVELS/ARCADE000.TXT", try frontendLevelPath(.postal, 0, &scratch));
    try std.testing.expectEqualStrings("LEVELS/ARCADE012.TXT", try frontendLevelPath(.postal, 12, &scratch));
    try std.testing.expectEqualStrings("LEVELS/ARCADE000.TXT", try frontendLevelPath(.time_trial, 0, &scratch));
    try std.testing.expectEqualStrings("LEVELS/TIMETRIALEXTRA001.TXT", try frontendLevelPath(.time_trial, 0x33, &scratch));
}

fn drawGameplayLevelUi(state: *const AppState, art_layout: ?background.Layout) !void {
    drawGameplayLevelViewport(state);

    const hud_panel = if (art_layout) |layout|
        layout.mapRect(16.0, 14.0, 608.0, 84.0)
    else
        rl.Rectangle{ .x = 24.0, .y = 24.0, .width = 624.0, .height = 112.0 };
    const footer_panel = if (art_layout) |layout|
        layout.mapRect(16.0, 408.0, 608.0, 84.0)
    else
        rl.Rectangle{ .x = 24.0, .y = 612.0, .width = 960.0, .height = 84.0 };

    rl.drawRectangleRounded(hud_panel, 0.08, 8, .{ .r = 0, .g = 0, .b = 0, .a = 176 });

    const loaded_level = state.current_level orelse return;
    const loaded_track_preview = state.current_track_preview orelse return;
    const title_point = rl.Vector2{ .x = hud_panel.x + 20.0, .y = hud_panel.y + 14.0 };
    const meta_point = rl.Vector2{ .x = hud_panel.x + 20.0, .y = hud_panel.y + 44.0 };
    const control_point = rl.Vector2{ .x = hud_panel.x + 20.0, .y = hud_panel.y + 68.0 };
    const parcel_target = loaded_level.parcels orelse 0;
    const parcel_count = if (state.level_runner) |runner| runner.counters.parcels else 0;
    const finished = if (state.level_runner) |runner| runner.finished else false;
    const package_icon = game_font.IconGlyph.package.byte();
    const mouse_icon = game_font.IconGlyph.mouse.byte();

    var level_name_buffer: [128]u8 = undefined;
    const level_name_text = try std.fmt.bufPrintZ(&level_name_buffer, "{s}", .{loaded_level.name});
    drawAppText(state, level_name_text, @intFromFloat(title_point.x), @intFromFloat(title_point.y), 28, .gold);

    var meta_buffer: [384]u8 = undefined;
    const meta_text = try std.fmt.bufPrintZ(
        &meta_buffer,
        "Mode {s}  background {s}  segment {d}/{d}  {c} {d}/{d}  rows {d}",
        .{
            loaded_level.mode,
            loaded_level.background orelse "<none>",
            if (state.active_level_segment_index) |segment_index| segment_index + 1 else 1,
            loaded_level.segments.len,
            package_icon,
            parcel_count,
            parcel_target,
            loaded_track_preview.total_rows,
        },
    );
    drawAppText(state, meta_text, @intFromFloat(meta_point.x), @intFromFloat(meta_point.y), 18, .ray_white);
    var control_buffer: [192]u8 = undefined;
    const control_text = if (finished)
        try std.fmt.bufPrintZ(&control_buffer, "{c}/Left/Right steer  Enter menu  Esc menu", .{mouse_icon})
    else
        try std.fmt.bufPrintZ(&control_buffer, "{c}/Left/Right steer  Up/Down speed  Space pause  R reset  Esc menu", .{mouse_icon});
    drawAppText(state, control_text, @intFromFloat(control_point.x), @intFromFloat(control_point.y), 18, .light_gray);

    if (state.level_runner) |runner| {
        rl.drawRectangleRounded(footer_panel, 0.2, 8, .{ .r = 0, .g = 0, .b = 0, .a = 172 });

        var runner_buffer: [384]u8 = undefined;
        const runner_text = try std.fmt.bufPrintZ(
            &runner_buffer,
            "Row {d:.2}/{d}  cursor {d}+{d:.2}  lane {d}->{d}  speed {d:.1}  event {s}  finished {s}",
            .{
                runner.row_position,
                loaded_track_preview.total_rows,
                runner.runtime_track_index,
                runner.movement_progress,
                runner.lane_index,
                runner.resolved_lane_index,
                runner.speed_rows_per_second,
                runner.recentEventLabel(),
                if (runner.finished) "yes" else "no",
            },
        );
        drawAppText(state, runner_text, @intFromFloat(footer_panel.x + 18.0), @intFromFloat(footer_panel.y + 18.0), 18, .ray_white);

        if (state.active_level_message) |message| {
            try drawWrappedText(
                state,
                message,
                @intFromFloat(footer_panel.x + 18.0),
                @intFromFloat(footer_panel.y + 44.0),
                @intFromFloat(footer_panel.width - 30.0),
                18,
                .gold,
            );
        }
    }

    const crosshair_color: rl.Color = .{ .r = 255, .g = 255, .b = 255, .a = 180 };
    rl.drawRectangle(window_width / 2 - 12, window_height / 2, 24, 2, crosshair_color);
    rl.drawRectangle(window_width / 2, window_height / 2 - 12, 2, 24, crosshair_color);
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

    drawModeBadge(state, .textures, state.mode, "Textures", 32, 144);
    drawModeBadge(state, .audio, state.mode, "Audio", 156, 144);
    drawModeBadge(state, .models, state.mode, "X2", 280, 144);
    drawModeBadge(state, .objects, state.mode, "Objects", 404, 144);
    drawModeBadge(state, .levels, state.mode, "Levels", 528, 144);

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
    const draw_x = (@as(f32, window_width) - draw_width) / 2.0;
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

    const camera = gameplayLevelCamera(&loaded_track_preview, runner);
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

    const eye = runner.worldPosition(loaded_track_preview, 0.82);
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

    return .{
        .position = eye,
        .target = target,
        .up = .{ .x = 0.0, .y = 1.0, .z = 0.0 },
        .fovy = 68.0,
        .projection = .perspective,
    };
}

fn laneTargetForRunnerMouse(
    loaded_track_preview: track.LoadedLevelPreview,
    runner: gameplay.Runner,
    mouse_x: f32,
) ?usize {
    const row_location = loaded_track_preview.locateRow(runner.current_global_row) orelse return null;
    return laneTargetForMouseX(mouse_x, @floatFromInt(window_width), loaded_track_preview.laneBoundsForRow(row_location));
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

fn drawAppText(state: *const AppState, text: []const u8, x: i32, y: i32, font_size: i32, color: rl.Color) void {
    state.ui_font.drawText(text, @floatFromInt(x), @floatFromInt(y), @floatFromInt(font_size), color);
}

fn measureAppText(state: *const AppState, text: []const u8, font_size: i32) i32 {
    return @intFromFloat(@ceil(state.ui_font.measureText(text, @floatFromInt(font_size))));
}

fn drawWrappedText(state: *const AppState, text: []const u8, x: i32, y: i32, max_width: i32, line_height: i32, color: rl.Color) !void {
    var line_buffer: [512]u8 = undefined;
    var line_index: i32 = 0;

    var parts = std.mem.splitScalar(u8, text, '>');
    while (parts.next()) |part| {
        const clipped = if (part.len > line_buffer.len - 1) part[0 .. line_buffer.len - 1] else part;
        @memcpy(line_buffer[0..clipped.len], clipped);
        line_buffer[clipped.len] = 0;
        _ = max_width;
        drawAppText(state, line_buffer[0..clipped.len], x, y + line_index * line_height, 18, color);
        line_index += 1;
    }
}

fn drawMultilineText(state: *const AppState, text: []const u8, x: i32, y: i32, max_width: i32, line_height: i32, color: rl.Color) !void {
    var line_buffer: [512]u8 = undefined;
    var line_index: i32 = 0;

    var parts = std.mem.splitScalar(u8, text, '\n');
    while (parts.next()) |part| {
        const clipped = if (part.len > line_buffer.len - 1) part[0 .. line_buffer.len - 1] else part;
        @memcpy(line_buffer[0..clipped.len], clipped);
        line_buffer[clipped.len] = 0;
        _ = max_width;
        drawAppText(state, line_buffer[0..clipped.len], x, y + line_index * line_height, 18, color);
        line_index += 1;
    }
}

fn drawCenteredMultilineText(state: *const AppState, text: []const u8, center_x: i32, y: i32, line_height: i32, color: rl.Color) !void {
    var line_buffer: [512]u8 = undefined;
    var line_index: i32 = 0;

    var parts = std.mem.splitScalar(u8, text, '\n');
    while (parts.next()) |part| {
        const clipped = if (part.len > line_buffer.len - 1) part[0 .. line_buffer.len - 1] else part;
        @memcpy(line_buffer[0..clipped.len], clipped);
        line_buffer[clipped.len] = 0;
        const text_width = measureAppText(state, line_buffer[0..clipped.len], 18);
        drawAppText(
            state,
            line_buffer[0..clipped.len],
            center_x - @divTrunc(text_width, 2),
            y + line_index * line_height,
            18,
            color,
        );
        line_index += 1;
    }
}

fn countLines(text: []const u8) i32 {
    var line_count: i32 = 1;
    for (text) |byte| {
        if (byte == '\n') line_count += 1;
    }
    return line_count;
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

test "parse args defaults to game shell" {
    const options = try parseArgsFromSlice(&.{});
    try std.testing.expectEqual(AppCommand.game, options.command);
    try std.testing.expectEqualStrings(default_archive_path, options.archive_path);
}

test "parse args handles debug and smoke subcommands" {
    var options = try parseArgsFromSlice(&.{ "debug", "--archive-path", "custom.dat" });
    try std.testing.expectEqual(AppCommand.debug, options.command);
    try std.testing.expectEqualStrings("custom.dat", options.archive_path);

    options = try parseArgsFromSlice(&.{"smoke"});
    try std.testing.expectEqual(AppCommand.smoke, options.command);
}

test "parse args rejects unknown commands" {
    try std.testing.expectError(error.UnknownCommand, parseArgsFromSlice(&.{"weird"}));
    try std.testing.expectError(error.UnknownCommand, parseArgsFromSlice(&.{"browser"}));
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
    try std.testing.expect(camera.target.z > camera.position.z);
    try std.testing.expect(camera.position.y > 0.0);
    try std.testing.expect(camera.target.y >= 0.0);
    try std.testing.expectApproxEqAbs(@as(f32, 68.0), camera.fovy, 0.001);
}

test "lane target mapping respects bounds" {
    const bounds: track.LaneBounds = .{ .min = 2, .max = 4 };
    try std.testing.expectEqual(@as(usize, 2), laneTargetForMouseX(0.0, 1280.0, bounds));
    try std.testing.expectEqual(@as(usize, 3), laneTargetForMouseX(640.0, 1280.0, bounds));
    try std.testing.expectEqual(@as(usize, 4), laneTargetForMouseX(1279.0, 1280.0, bounds));
}
