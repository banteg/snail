const std = @import("std");
const rl = @import("raylib");
const app_ui = @import("../app_ui.zig");
const background = @import("../background.zig");
const debug_levels = @import("levels.zig");
const object = @import("../object.zig");
const track = @import("../track.zig");
const track_render = @import("../track_render.zig");
const x2 = @import("../x2.zig");
const xanim = @import("../xanim.zig");

pub const Mode = enum {
    textures,
    audio,
    models,
    objects,
    levels,
    segments,
    streaks,
};

pub const SegmentRenderMode = enum {
    game,
    raw,
};

pub const LightStreakView = struct {
    controller: background.LightStreakController = background.LightStreakController.init(),
    visible_requested: bool = true,
    paused: bool = false,
    show_textured: bool = true,
    show_lines: bool = true,
    alpha_multiplier: f32 = 1.0,
    size_multiplier: f32 = 1.0,
    stretch_multiplier: f32 = 1.0,
    camera_yaw_degrees: f32 = 0.0,
    camera_pitch_degrees: f32 = 0.0,
    camera_fov_degrees: f32 = 110.0,

    pub fn step(self: *LightStreakView) void {
        if (self.paused) return;
        self.controller.update(self.camera(), self.visible_requested);
    }

    pub fn stepOnce(self: *LightStreakView) void {
        self.controller.update(self.camera(), self.visible_requested);
    }

    pub fn reset(self: *LightStreakView) void {
        self.controller = background.LightStreakController.init();
    }

    pub fn camera(self: *const LightStreakView) background.LightStreakCamera {
        const yaw = std.math.degreesToRadians(self.camera_yaw_degrees);
        const pitch = std.math.degreesToRadians(self.camera_pitch_degrees);
        const forward = normalizeVector3(.{
            .x = @sin(yaw) * @cos(pitch),
            .y = @sin(pitch),
            .z = @cos(yaw) * @cos(pitch),
        });
        var up = rl.Vector3{ .x = 0.0, .y = 1.0, .z = 0.0 };
        if (@abs(dotVector3(forward, up)) > 0.95) {
            up = .{ .x = 0.0, .y = 0.0, .z = 1.0 };
        }
        var right = crossVector3(up, forward);
        if (vectorLength(right) <= 0.0001) {
            right = .{ .x = 1.0, .y = 0.0, .z = 0.0 };
        } else {
            right = normalizeVector3(right);
        }
        const corrected_up = normalizeVector3(crossVector3(forward, right));
        return .{
            .position = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
            .right = right,
            .up = corrected_up,
            .forward = forward,
            .fov_degrees = self.camera_fov_degrees,
        };
    }
};

pub fn nextMode(mode: Mode) Mode {
    return switch (mode) {
        .textures => .audio,
        .audio => .models,
        .models => .objects,
        .objects => .levels,
        .levels => .segments,
        .segments => .streaks,
        .streaks => .textures,
    };
}

pub fn initialize(state: anytype) !void {
    try state.high_score_tables.loadFromRuntimeRoot(state.allocator, state.runtime_root_path);
    try reloadTexture(state);
    try reloadModel(state);
    try reloadObject(state);
    try state.reloadLevel();
    try reloadStandaloneSegment(state);
}

pub fn primeAudioPreview(state: anytype) !void {
    if (!state.audio_ready or state.resources.catalog.audio_entries.len == 0) return;
    try previewSound(state);
    state.stopAudioPreview();
    try previewMusic(state);
}

pub fn handleInput(state: anytype) !void {
    if (rl.isKeyPressed(.tab)) {
        try setMode(state, nextMode(state.mode));
    }
    if (rl.isKeyPressed(.one)) {
        try setMode(state, .textures);
    }
    if (rl.isKeyPressed(.two)) {
        try setMode(state, .audio);
    }
    if (rl.isKeyPressed(.three)) {
        try setMode(state, .models);
    }
    if (rl.isKeyPressed(.four)) {
        try setMode(state, .objects);
    }
    if (rl.isKeyPressed(.five)) {
        try setMode(state, .levels);
    }
    if (rl.isKeyPressed(.six)) {
        try setMode(state, .segments);
    }
    if (rl.isKeyPressed(.seven)) {
        try setMode(state, .streaks);
    }

    if (state.mode == .levels) {
        if (rl.isKeyPressed(.left)) {
            state.level_index = wrappedIndex(state.resources.catalog.level_entries.len, state.level_index, -1);
            try state.reloadLevel();
        }
        if (rl.isKeyPressed(.right)) {
            state.level_index = wrappedIndex(state.resources.catalog.level_entries.len, state.level_index, 1);
            try state.reloadLevel();
        }
        if (rl.isKeyPressed(.up)) {
            try stepLevelSegment(state, -1);
        }
        if (rl.isKeyPressed(.down)) {
            try stepLevelSegment(state, 1);
        }
        if (rl.isKeyPressed(.a)) {
            state.pending_level_input.lane_delta -= 1;
        }
        if (rl.isKeyPressed(.d)) {
            state.pending_level_input.lane_delta += 1;
        }
        if (rl.isKeyPressed(.w)) {
            state.pending_level_input.speed_delta_rows_per_second += 2.0;
        }
        if (rl.isKeyPressed(.s)) {
            state.pending_level_input.speed_delta_rows_per_second -= 2.0;
        }
        if (rl.isKeyPressed(.space)) {
            state.pending_level_input.toggle_pause = true;
        }
        if (rl.isKeyPressed(.r)) {
            state.pending_level_input.reset = true;
        }
    } else if (state.mode == .segments) {
        if (rl.isKeyPressed(.left)) {
            try stepSelection(state, -1);
        }
        if (rl.isKeyPressed(.right)) {
            try stepSelection(state, 1);
        }
        if (rl.isKeyPressed(.up)) {
            try stepSelection(state, -10);
        }
        if (rl.isKeyPressed(.down)) {
            try stepSelection(state, 10);
        }
        if (rl.isKeyPressed(.v)) {
            state.segment_render_mode = switch (state.segment_render_mode) {
                .game => .raw,
                .raw => .game,
            };
        }
        if (rl.isKeyPressed(.o)) {
            state.segment_show_overlay = !state.segment_show_overlay;
        }
        if (rl.isKeyPressed(.g)) {
            state.segment_show_grid = !state.segment_show_grid;
        }
        if (rl.isKeyPressed(.a)) {
            state.segment_show_attachments = !state.segment_show_attachments;
        }
        if (rl.isKeyPressed(.t)) {
            state.segment_track_set_index = (state.segment_track_set_index + 1) % 4;
            try reloadStandaloneSegmentScene(state);
        }
    } else if (state.mode == .streaks) {
        handleLightStreakInput(&state.debug_light_streak_view);
    } else {
        if (rl.isKeyPressed(.left)) {
            try stepSelection(state, -1);
        }
        if (rl.isKeyPressed(.right)) {
            try stepSelection(state, 1);
        }
        if (rl.isKeyPressed(.up)) {
            try stepSelection(state, -10);
        }
        if (rl.isKeyPressed(.down)) {
            try stepSelection(state, 10);
        }
    }

    if (state.mode == .audio and state.audio_ready) {
        if (rl.isKeyPressed(.space)) {
            try previewSound(state);
        }
        if (rl.isKeyPressed(.enter)) {
            try previewMusic(state);
        }
        if (rl.isKeyPressed(.s)) {
            state.stopAudioPreview();
        }
    }

    if (state.mode == .models and rl.isKeyPressed(.f)) {
        state.model_flip_v = !state.model_flip_v;
        try reloadModel(state);
    }
    if (state.mode == .models and rl.isKeyPressed(.r)) {
        if (state.current_animation) |*animation| {
            try animation.restart();
        }
    }
    if (state.mode == .models and rl.isKeyPressed(.p)) {
        if (state.current_animation) |*animation| {
            animation.togglePause();
        }
    }
    if (state.mode == .objects and rl.isKeyPressed(.f)) {
        state.object_flip_v = !state.object_flip_v;
        try reloadObject(state);
    }
}

pub fn handleLightStreakInput(view: *LightStreakView) void {
    if (rl.isKeyPressed(.space)) {
        view.paused = !view.paused;
    }
    if (rl.isKeyPressed(.n)) {
        view.stepOnce();
    }
    if (rl.isKeyPressed(.r)) {
        view.reset();
    }
    if (rl.isKeyPressed(.h)) {
        view.visible_requested = !view.visible_requested;
    }
    if (rl.isKeyPressed(.t)) {
        view.show_textured = !view.show_textured;
    }
    if (rl.isKeyPressed(.l)) {
        view.show_lines = !view.show_lines;
    }
    if (rl.isKeyPressed(.q)) {
        view.alpha_multiplier = std.math.clamp(view.alpha_multiplier - 0.25, 0.0, 16.0);
    }
    if (rl.isKeyPressed(.e)) {
        view.alpha_multiplier = std.math.clamp(view.alpha_multiplier + 0.25, 0.0, 16.0);
    }
    if (rl.isKeyPressed(.z)) {
        view.size_multiplier = std.math.clamp(view.size_multiplier - 0.25, 0.0, 16.0);
    }
    if (rl.isKeyPressed(.x)) {
        view.size_multiplier = std.math.clamp(view.size_multiplier + 0.25, 0.0, 16.0);
    }
    if (rl.isKeyPressed(.c)) {
        view.stretch_multiplier = std.math.clamp(view.stretch_multiplier - 0.25, 0.0, 16.0);
    }
    if (rl.isKeyPressed(.v)) {
        view.stretch_multiplier = std.math.clamp(view.stretch_multiplier + 0.25, 0.0, 16.0);
    }
    if (rl.isKeyPressed(.a)) {
        view.camera_yaw_degrees -= 5.0;
    }
    if (rl.isKeyPressed(.d)) {
        view.camera_yaw_degrees += 5.0;
    }
    if (rl.isKeyPressed(.w)) {
        view.camera_pitch_degrees = std.math.clamp(view.camera_pitch_degrees + 5.0, -85.0, 85.0);
    }
    if (rl.isKeyPressed(.s)) {
        view.camera_pitch_degrees = std.math.clamp(view.camera_pitch_degrees - 5.0, -85.0, 85.0);
    }
    if (rl.isKeyPressed(.f)) {
        view.camera_fov_degrees = std.math.clamp(view.camera_fov_degrees - 5.0, 30.0, 160.0);
    }
    if (rl.isKeyPressed(.g)) {
        view.camera_fov_degrees = std.math.clamp(view.camera_fov_degrees + 5.0, 30.0, 160.0);
    }
}

fn setMode(state: anytype, mode: Mode) !void {
    if (state.mode == mode) return;
    if (state.mode == .audio) {
        state.stopAudioPreview();
    }
    state.mode = mode;
}

fn stepSelection(state: anytype, delta: isize) !void {
    switch (state.mode) {
        .textures => {
            state.texture_index = wrappedIndex(state.resources.catalog.texture_entries.len, state.texture_index, delta);
            try reloadTexture(state);
        },
        .audio => {
            state.stopAudioPreview();
            state.audio_index = wrappedIndex(state.resources.catalog.audio_entries.len, state.audio_index, delta);
        },
        .models => {
            state.model_index = wrappedIndex(state.resources.catalog.model_entries.len, state.model_index, delta);
            try reloadModel(state);
        },
        .objects => {
            state.object_index = wrappedIndex(state.resources.catalog.object_entries.len, state.object_index, delta);
            try reloadObject(state);
        },
        .levels => {},
        .segments => {
            state.segment_index = wrappedIndex(state.resources.catalog.segment_entries.len, state.segment_index, delta);
            try reloadStandaloneSegment(state);
        },
        .streaks => {},
    }
}

fn stepLevelSegment(state: anytype, delta: isize) !void {
    const loaded_level = state.current_level orelse return;
    state.level_segment_index = wrappedIndex(loaded_level.segments.len, state.level_segment_index, delta);
    try state.reloadLevelSegment();
}

fn previewSound(state: anytype) !void {
    if (!state.audio_ready or state.resources.catalog.audio_entries.len == 0) return;
    if (state.current_music) |*music| {
        music.unload();
        state.current_music = null;
    }
    const sound = (try state.current_sound.loadPath(
        &state.resources,
        state.resources.catalog.audio_entries[state.audio_index].path,
    )) orelse return;
    state.applyAudioConfigVolumes();
    rl.playSound(sound.sound);
}

fn previewMusic(state: anytype) !void {
    if (!state.audio_ready or state.resources.catalog.audio_entries.len == 0) return;
    state.stopAudioPreview();
    state.current_music = try state.resources.catalog.loadMusic(state.allocator, state.resources.catalog.audio_entries[state.audio_index]);
    state.applyAudioConfigVolumes();
    rl.playMusicStream(state.current_music.?.music);
}

fn reloadTexture(state: anytype) !void {
    if (state.current_texture) |*texture| {
        texture.unload();
        state.current_texture = null;
    }
    state.current_texture = try state.resources.catalog.loadTexture(state.allocator, state.resources.catalog.texture_entries[state.texture_index]);
}

fn reloadModel(state: anytype) !void {
    if (state.current_model) |*model| {
        model.deinit();
        state.current_model = null;
    }
    if (state.current_animation) |*animation| {
        animation.deinit();
        state.current_animation = null;
    }

    const entry = state.resources.catalog.model_entries[state.model_index];
    if (state.animation_catalog.findClipIndexForModelPath(entry.path)) |clip_index| {
        const clip = &state.animation_catalog.clips[clip_index];
        if (clip.frames.len > 1) {
            state.current_animation = try xanim.Player.load(
                state.allocator,
                &state.resources.catalog,
                clip,
                state.model_flip_v,
                xanim.frameNumberFromPath(entry.path),
            );
            return;
        }
    }

    state.current_model = try x2.Uploaded.loadFromArchive(
        state.allocator,
        &state.resources.catalog,
        entry,
        state.model_flip_v,
    );
}

fn reloadObject(state: anytype) !void {
    if (state.current_object) |*loaded_object| {
        loaded_object.deinit();
        state.current_object = null;
    }
    if (state.resources.catalog.object_entries.len == 0) return;

    const entry = state.resources.catalog.object_entries[state.object_index];
    state.current_object = try object.LoadedObject.loadFromArchive(
        state.allocator,
        &state.resources.catalog,
        entry,
        state.object_flip_v,
    );
}

fn reloadStandaloneSegment(state: anytype) !void {
    if (state.current_standalone_segment_scene) |*scene| {
        scene.deinit();
        state.current_standalone_segment_scene = null;
    }
    if (state.current_standalone_segment_preview) |*loaded_track_preview| {
        loaded_track_preview.deinit();
        state.current_standalone_segment_preview = null;
    }
    if (state.resources.catalog.segment_entries.len == 0) return;
    if (state.segment_index >= state.resources.catalog.segment_entries.len) {
        state.segment_index = state.resources.catalog.segment_entries.len - 1;
    }

    const entry = state.resources.catalog.segment_entries[state.segment_index];
    state.current_standalone_segment_preview = try track.LoadedLevelPreview.loadStandaloneSegment(
        state.allocator,
        &state.resources.catalog,
        entry,
    );
    try reloadStandaloneSegmentScene(state);
}

fn reloadStandaloneSegmentScene(state: anytype) !void {
    if (state.current_standalone_segment_scene) |*scene| {
        scene.deinit();
        state.current_standalone_segment_scene = null;
    }
    _ = state.current_standalone_segment_preview orelse return;
    state.current_standalone_segment_scene = try track_render.Scene.buildStandaloneSegmentScene(
        state.allocator,
        &state.resources.catalog,
        state.segment_track_set_index,
    );
}

pub fn drawUi(state: anytype, archive_path: []const u8) !void {
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
    drawAppText(state, "1 textures  2 audio  3 x2  4 objects  5 levels  6 segments  7 streaks", 24, 48, 16, .light_gray);
    const controls_text: []const u8 = switch (state.mode) {
        .levels => "tab mode  arrows browse  levels: left/right level up/down segment  gameplay: a/d lane w/s speed space pause r reset",
        .segments => "tab mode  arrows browse  segments: v render o overlay g grid a attachments t track",
        .streaks => "streaks: space pause  n step  r reset  h fade  t texture  l lines  q/e alpha  z/x size  c/v stretch  a/d yaw  w/s pitch  f/g fov",
        else => "tab mode  arrows browse",
    };
    drawAppText(state, controls_text, 24, 70, 16, .light_gray);

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
    drawModeBadge(state, .streaks, state.mode, "Streaks", 696, 114);

    switch (state.mode) {
        .textures => drawTexturePanel(state),
        .audio => try drawAudioPanel(state),
        .models => try drawModelPanel(state),
        .objects => try drawObjectPanel(state),
        .levels => try debug_levels.drawLevelPanel(state),
        .segments => try debug_levels.drawSegmentPanel(state),
        .streaks => try drawLightStreakDebugPanel(state),
    }
}

fn drawModeBadge(state: anytype, mode: Mode, active_mode: Mode, text: [:0]const u8, x: i32, y: i32) void {
    const color: rl.Color = if (mode == active_mode) .orange else .dark_gray;
    rl.drawRectangleRounded(.{ .x = @floatFromInt(x), .y = @floatFromInt(y), .width = 94, .height = 28 }, 0.22, 8, color);
    drawAppText(state, text, x + 16, y + 6, 16, .ray_white);
}

fn drawTexturePanel(state: anytype) void {
    const current = state.current_texture orelse return;
    const entry = state.resources.catalog.texture_entries[state.texture_index];

    var summary_buffer: [256]u8 = undefined;
    const summary_text = std.fmt.bufPrintZ(
        &summary_buffer,
        "Texture {d}/{d}  {d}x{d}",
        .{
            state.texture_index + 1,
            state.resources.catalog.texture_entries.len,
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

fn drawAudioPanel(state: anytype) !void {
    const entry = state.resources.catalog.audio_entries[state.audio_index];

    var summary_buffer: [256]u8 = undefined;
    const summary_text = try std.fmt.bufPrintZ(
        &summary_buffer,
        "Audio {d}/{d}",
        .{ state.audio_index + 1, state.resources.catalog.audio_entries.len },
    );
    drawAppText(state, summary_text, 32, 194, 24, .ray_white);

    var path_buffer: [512]u8 = undefined;
    const path_text = try std.fmt.bufPrintZ(&path_buffer, "{s}", .{entry.path});
    drawAppText(state, path_text, 32, 226, 18, .light_gray);

    const status_text: [:0]const u8 = blk: {
        if (!state.audio_ready) break :blk "Audio device unavailable";
        if (state.current_music != null) break :blk "Playing as music stream";
        if (state.current_sound.current) |sound| {
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

fn drawLightStreakDebugPanel(state: anytype) !void {
    const debug = &state.debug_light_streak_view;
    const camera = debug.camera();
    const textured_bounds = rl.Rectangle{ .x = 32.0, .y = 170.0, .width = 520.0, .height = 390.0 };
    const line_bounds = rl.Rectangle{ .x = 728.0, .y = 170.0, .width = 520.0, .height = 390.0 };

    drawLightStreakDebugViewportFrame(state, textured_bounds, "STARTAIL textured", debug.show_textured);
    drawLightStreakDebugViewportFrame(state, line_bounds, "Line fallback", debug.show_lines);

    const draw_options = background.LightStreakDrawOptions{
        .alpha_multiplier = debug.alpha_multiplier,
        .size_multiplier = debug.size_multiplier,
        .stretch_multiplier = debug.stretch_multiplier,
    };

    const textured_stats = if (debug.show_textured)
        debug.controller.drawWithOptions(
            textured_bounds,
            camera,
            if (state.current_background_light_streak_texture) |loaded| loaded.texture else null,
            .{
                .mode = .textured,
                .alpha_multiplier = draw_options.alpha_multiplier,
                .size_multiplier = draw_options.size_multiplier,
                .stretch_multiplier = draw_options.stretch_multiplier,
                .draw_debug_centers = true,
                .draw_debug_quads = true,
            },
        )
    else
        background.LightStreakDrawStats{};
    const line_stats = if (debug.show_lines)
        debug.controller.drawWithOptions(
            line_bounds,
            camera,
            null,
            .{
                .mode = .lines,
                .alpha_multiplier = draw_options.alpha_multiplier,
                .size_multiplier = draw_options.size_multiplier,
                .stretch_multiplier = draw_options.stretch_multiplier,
                .draw_debug_centers = true,
            },
        )
    else
        background.LightStreakDrawStats{};

    try drawLightStreakDebugStats(state, textured_bounds, textured_stats, 574);
    try drawLightStreakDebugStats(state, line_bounds, line_stats, 574);

    const texture_preview_bounds = rl.Rectangle{ .x = 32.0, .y = 622.0, .width = 80.0, .height = 80.0 };
    rl.drawRectangleRec(texture_preview_bounds, .black);
    rl.drawRectangleLinesEx(texture_preview_bounds, 1.0, .dark_gray);
    if (state.current_background_light_streak_texture) |loaded| {
        const preview_size = 64.0;
        const preview_x = texture_preview_bounds.x + (texture_preview_bounds.width - preview_size) * 0.5;
        const preview_y = texture_preview_bounds.y + (texture_preview_bounds.height - preview_size) * 0.5;
        rl.drawTexturePro(
            loaded.texture,
            .{
                .x = 0.0,
                .y = 0.0,
                .width = @floatFromInt(loaded.texture.width),
                .height = @floatFromInt(loaded.texture.height),
            },
            .{
                .x = preview_x,
                .y = preview_y,
                .width = preview_size,
                .height = preview_size,
            },
            .{ .x = 0.0, .y = 0.0 },
            0.0,
            .white,
        );

        var sprite_buffer: [128]u8 = undefined;
        const sprite_text = try std.fmt.bufPrintZ(
            &sprite_buffer,
            "STARTAIL {d}x{d}",
            .{ loaded.texture.width, loaded.texture.height },
        );
        drawAppText(state, sprite_text, 32, 706, 16, .light_gray);
    }

    drawAppText(state, "Both panes use the same controller state and camera; only the draw path changes.", 136, 628, 18, .ray_white);

    var controller_buffer: [256]u8 = undefined;
    const controller_text = try std.fmt.bufPrintZ(
        &controller_buffer,
        "Controller {s}  fade {d:.2}  visible {s}  paused {s}",
        .{
            debug.controller.debugStateLabel(),
            debug.controller.debugFade(),
            if (debug.visible_requested) "on" else "off",
            if (debug.paused) "yes" else "no",
        },
    );
    drawAppText(state, controller_text, 136, 652, 16, .light_gray);

    var camera_buffer: [256]u8 = undefined;
    const camera_text = try std.fmt.bufPrintZ(
        &camera_buffer,
        "Camera yaw {d:.1}  pitch {d:.1}  fov {d:.1}",
        .{ debug.camera_yaw_degrees, debug.camera_pitch_degrees, debug.camera_fov_degrees },
    );
    drawAppText(state, camera_text, 136, 674, 16, .light_gray);

    var scale_buffer: [256]u8 = undefined;
    const scale_text = try std.fmt.bufPrintZ(
        &scale_buffer,
        "Multipliers alpha {d:.2}  size {d:.2}  stretch {d:.2}",
        .{ debug.alpha_multiplier, debug.size_multiplier, debug.stretch_multiplier },
    );
    drawAppText(state, scale_text, 136, 696, 16, .light_gray);

    drawAppText(state, "Use this to answer two questions: are stars being generated/projected at all, and does STARTAIL differ from the line fallback?", 136, 718, 14, .gold);
}

fn drawLightStreakDebugViewportFrame(state: anytype, bounds: rl.Rectangle, label: []const u8, enabled: bool) void {
    rl.drawRectangleRec(bounds, .black);
    rl.drawRectangleLinesEx(bounds, 2.0, if (enabled) .dark_gray else .gray);
    const center_x = bounds.x + bounds.width * 0.5;
    const center_y = bounds.y + bounds.height * 0.5;
    rl.drawLineV(.{ .x = center_x - 12.0, .y = center_y }, .{ .x = center_x + 12.0, .y = center_y }, .dark_gray);
    rl.drawLineV(.{ .x = center_x, .y = center_y - 12.0 }, .{ .x = center_x, .y = center_y + 12.0 }, .dark_gray);
    drawAppText(state, label, @intFromFloat(bounds.x + 14.0), @intFromFloat(bounds.y + 12.0), 20, if (enabled) .ray_white else .gray);
}

fn drawLightStreakDebugStats(state: anytype, bounds: rl.Rectangle, stats: background.LightStreakDrawStats, base_y: i32) !void {
    var summary_buffer: [192]u8 = undefined;
    const summary_text = try std.fmt.bufPrintZ(
        &summary_buffer,
        "entries {d}  alpha>0 {d}  projected {d}  drawn {d}",
        .{ stats.total_entries, stats.alpha_visible_entries, stats.center_projected_entries, stats.drawn_entries },
    );
    drawAppText(state, summary_text, @intFromFloat(bounds.x), base_y, 16, .light_gray);

    var detail_buffer: [192]u8 = undefined;
    const detail_text = try std.fmt.bufPrintZ(
        &detail_buffer,
        "avg alpha {d:.3}  max alpha {d:.3}  avg stretch {d:.2}",
        .{ stats.average_alpha, stats.max_alpha, stats.average_stretch },
    );
    drawAppText(state, detail_text, @intFromFloat(bounds.x), base_y + 22, 16, .light_gray);
}

fn drawModelPanel(state: anytype) !void {
    const entry = state.resources.catalog.model_entries[state.model_index];
    const model = state.activeModel() orelse return;
    const parsed = &model.doc;

    var summary_buffer: [256]u8 = undefined;
    const summary_text = try std.fmt.bufPrintZ(
        &summary_buffer,
        "X2 {d}/{d}  submeshes {d}  vertices {d}  faces {d}  triangles {d}",
        .{
            state.model_index + 1,
            state.resources.catalog.model_entries.len,
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

fn drawModelViewport(state: anytype) void {
    const model = state.activeModel() orelse return;
    const camera = model.previewCamera(@floatCast(state.render_time_seconds));
    camera.begin();
    defer rl.endMode3D();

    const grid_slices: i32 = @intFromFloat(@min(@max(model.bounds.radius * 6.0, 10.0), 80.0));
    const grid_spacing = @max(model.bounds.radius / 2.0, 0.5);
    rl.drawGrid(grid_slices, grid_spacing);
    model.draw();
}

fn drawObjectPanel(state: anytype) !void {
    const entry = state.resources.catalog.object_entries[state.object_index];
    const loaded_object = state.current_object orelse return;

    var summary_buffer: [256]u8 = undefined;
    const summary_text = try std.fmt.bufPrintZ(
        &summary_buffer,
        "Object {d}/{d}  vertices {d}  faces {d}  textures {d}",
        .{
            state.object_index + 1,
            state.resources.catalog.object_entries.len,
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

fn drawObjectViewport(state: anytype) void {
    const loaded_object = state.current_object orelse return;
    const camera = loaded_object.previewCamera(@floatCast(state.render_time_seconds));
    camera.begin();
    defer rl.endMode3D();

    const grid_slices: i32 = @intFromFloat(@min(@max(loaded_object.radius * 6.0, 10.0), 80.0));
    const grid_spacing = @max(loaded_object.radius / 2.0, 0.5);
    rl.drawGrid(grid_slices, grid_spacing);
    loaded_object.draw();
}

fn uiContext(state: anytype) app_ui.Context {
    return .{ .font = &state.ui_font };
}

fn drawAppText(state: anytype, text: []const u8, x: i32, y: i32, font_size: i32, color: rl.Color) void {
    app_ui.drawText(uiContext(state), text, x, y, font_size, color);
}

fn triangleCountForObject(loaded_object: object.LoadedObject) usize {
    var total: usize = 0;
    for (loaded_object.submeshes) |submesh| {
        total += submesh.triangle_count;
    }
    return total;
}

fn modeLabel(mode: xanim.Mode) [:0]const u8 {
    return switch (mode) {
        .loop => "loop",
        .once => "once",
        .pingpong => "pingpong",
    };
}

fn screenWidth() i32 {
    return rl.getScreenWidth();
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

fn vectorLength(v: rl.Vector3) f32 {
    return std.math.sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

fn normalizeVector3(v: rl.Vector3) rl.Vector3 {
    const len = vectorLength(v);
    if (len <= 0.000001) return .{ .x = 0.0, .y = 0.0, .z = 0.0 };
    return .{
        .x = v.x / len,
        .y = v.y / len,
        .z = v.z / len,
    };
}

fn crossVector3(a: rl.Vector3, b: rl.Vector3) rl.Vector3 {
    return .{
        .x = a.y * b.z - a.z * b.y,
        .y = a.z * b.x - a.x * b.z,
        .z = a.x * b.y - a.y * b.x,
    };
}

fn dotVector3(a: rl.Vector3, b: rl.Vector3) f32 {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

test "next mode cycles through streak debug browser" {
    try std.testing.expectEqual(Mode.streaks, nextMode(.segments));
    try std.testing.expectEqual(Mode.textures, nextMode(.streaks));
}
