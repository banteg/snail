const std = @import("std");
const rl = @import("raylib");
const assets = @import("assets.zig");
const x2 = @import("x2.zig");

const window_width = 1280;
const window_height = 720;

const default_archive_path = "artifacts/bin/SnailMail.dat";
const default_texture_path = "OBJECTS/FONT/FONT-MENU-HOVER.TGA";
const default_audio_path = "MUSIC/MAINMENU.OGG";
const default_model_path = "X/SIGNSTOP.X2";

const Options = struct {
    archive_path: []const u8 = default_archive_path,
    smoke_test: bool = false,
};

const Mode = enum {
    textures,
    audio,
    models,
};

const AppState = struct {
    allocator: std.mem.Allocator,
    catalog: assets.Catalog,
    audio_ready: bool,
    mode: Mode = .textures,
    texture_index: usize,
    audio_index: usize,
    model_index: usize,
    current_texture: ?assets.LoadedTexture = null,
    current_sound: ?assets.LoadedSound = null,
    current_music: ?assets.LoadedMusic = null,
    current_model_summary: ?x2.Summary = null,

    fn init(allocator: std.mem.Allocator, archive_path: []const u8, audio_ready: bool) !AppState {
        var catalog = try assets.Catalog.init(allocator, archive_path);
        errdefer catalog.deinit();

        const texture_index = catalog.findTextureIndex(default_texture_path) orelse 0;
        const audio_index = catalog.findAudioIndex(default_audio_path) orelse 0;
        const model_index = catalog.findModelIndex(default_model_path) orelse 0;

        var state = AppState{
            .allocator = allocator,
            .catalog = catalog,
            .audio_ready = audio_ready,
            .texture_index = texture_index,
            .audio_index = audio_index,
            .model_index = model_index,
        };
        errdefer state.deinit();

        try state.reloadTexture();
        try state.reloadModelSummary();
        return state;
    }

    fn deinit(self: *AppState) void {
        self.stopAudioPreview();

        if (self.current_model_summary) |*summary| {
            summary.deinit();
            self.current_model_summary = null;
        }

        if (self.current_texture) |*texture| {
            texture.unload();
            self.current_texture = null;
        }

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

    fn update(self: *AppState) void {
        if (self.current_music) |music| {
            rl.updateMusicStream(music.music);
        }
    }

    fn handleInput(self: *AppState) !void {
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
                try self.reloadModelSummary();
            },
        }
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

    fn reloadModelSummary(self: *AppState) !void {
        if (self.current_model_summary) |*summary| {
            summary.deinit();
            self.current_model_summary = null;
        }

        const entry = self.catalog.model_entries[self.model_index];
        const decoded = try self.catalog.readEntryAlloc(self.allocator, entry);
        defer self.allocator.free(decoded);

        const summary = try x2.parseSummary(self.allocator, decoded);
        self.current_model_summary = summary;
    }
};

fn parseArgs(allocator: std.mem.Allocator) !Options {
    var options = Options{};
    var args = try std.process.argsWithAllocator(allocator);
    defer args.deinit();

    _ = args.skip();
    while (args.next()) |arg| {
        if (std.mem.eql(u8, arg, "--smoke-test")) {
            options.smoke_test = true;
            continue;
        }
        if (std.mem.eql(u8, arg, "--archive-path")) {
            options.archive_path = args.next() orelse return error.MissingArchivePath;
            continue;
        }
    }
    return options;
}

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    const options = try parseArgs(allocator);

    rl.initWindow(window_width, window_height, "Snail Mail");
    defer rl.closeWindow();

    rl.initAudioDevice();
    const audio_ready = rl.isAudioDeviceReady();
    defer {
        if (audio_ready) {
            rl.closeAudioDevice();
        }
    }

    var state = try AppState.init(allocator, options.archive_path, audio_ready);
    defer state.deinit();

    if (options.smoke_test) {
        try state.warmupSmokeTest();
    }

    rl.setTargetFPS(144);
    var frames_left: usize = if (options.smoke_test) 3 else std.math.maxInt(usize);

    while (!rl.windowShouldClose() and frames_left > 0) {
        if (options.smoke_test) {
            frames_left -= 1;
        }

        try state.handleInput();
        state.update();

        rl.beginDrawing();
        defer rl.endDrawing();

        rl.clearBackground(.black);
        try drawUi(&state, options.archive_path);
    }
}

fn drawUi(state: *const AppState, archive_path: []const u8) !void {
    rl.drawText("Snail Mail archive browser", 32, 24, 30, .ray_white);
    rl.drawText("1 textures  2 audio  3 x2 models  left/right cycle  up/down jump  tab switch", 32, 62, 18, .light_gray);
    rl.drawText("audio: space sound  enter music  s stop", 32, 84, 18, .light_gray);

    var archive_buffer: [512]u8 = undefined;
    const archive_text = try std.fmt.bufPrintZ(&archive_buffer, "Archive: {s}", .{archive_path});
    rl.drawText(archive_text, 32, 110, 18, .dark_gray);

    drawModeBadge(.textures, state.mode, "Textures", 32, 144);
    drawModeBadge(.audio, state.mode, "Audio", 184, 144);
    drawModeBadge(.models, state.mode, "X2", 304, 144);

    switch (state.mode) {
        .textures => drawTexturePanel(state),
        .audio => try drawAudioPanel(state),
        .models => try drawModelPanel(state),
    }
}

fn drawModeBadge(mode: Mode, active_mode: Mode, text: [:0]const u8, x: i32, y: i32) void {
    const color: rl.Color = if (mode == active_mode) .orange else .dark_gray;
    rl.drawRectangleRounded(.{ .x = @floatFromInt(x), .y = @floatFromInt(y), .width = 108, .height = 34 }, 0.22, 8, color);
    rl.drawText(text, x + 20, y + 8, 18, .ray_white);
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
    rl.drawText(summary_text, 32, 194, 24, .ray_white);

    var path_buffer: [512]u8 = undefined;
    const path_text = std.fmt.bufPrintZ(&path_buffer, "{s}", .{entry.path}) catch "";
    rl.drawText(path_text, 32, 226, 18, .light_gray);

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
    rl.drawText(summary_text, 32, 194, 24, .ray_white);

    var path_buffer: [512]u8 = undefined;
    const path_text = try std.fmt.bufPrintZ(&path_buffer, "{s}", .{entry.path});
    rl.drawText(path_text, 32, 226, 18, .light_gray);

    const status_text: [:0]const u8 = blk: {
        if (!state.audio_ready) break :blk "Audio device unavailable";
        if (state.current_music != null) break :blk "Playing as music stream";
        if (state.current_sound) |sound| {
            if (rl.isSoundPlaying(sound.sound)) break :blk "Playing as one-shot sound";
        }
        break :blk "Stopped";
    };
    rl.drawText(status_text, 32, 260, 22, .sky_blue);

    rl.drawRectangleRounded(.{ .x = 32, .y = 308, .width = 1216, .height = 380 }, 0.03, 8, .dark_blue);
    rl.drawText("Audio preview stays archive-backed: OGG bytes are decoded from SnailMail.dat in memory.", 56, 338, 24, .ray_white);
    rl.drawText("Space loads the current OGG as a sound effect and plays it once.", 56, 384, 22, .light_gray);
    rl.drawText("Enter loads the same OGG as a music stream and keeps updating it each frame.", 56, 420, 22, .light_gray);
    rl.drawText("This lets us exercise both playback paths before game logic exists.", 56, 456, 22, .light_gray);
}

fn drawModelPanel(state: *const AppState) !void {
    const entry = state.catalog.model_entries[state.model_index];
    const summary = state.current_model_summary orelse return;

    var summary_buffer: [256]u8 = undefined;
    const summary_text = try std.fmt.bufPrintZ(
        &summary_buffer,
        "X2 {d}/{d}  meshes {d}  vertices {d}  faces {d}",
        .{
            state.model_index + 1,
            state.catalog.model_entries.len,
            summary.mesh_count,
            summary.total_vertices,
            summary.total_faces,
        },
    );
    rl.drawText(summary_text, 32, 194, 24, .ray_white);

    var path_buffer: [512]u8 = undefined;
    const path_text = try std.fmt.bufPrintZ(&path_buffer, "{s}", .{entry.path});
    rl.drawText(path_text, 32, 226, 18, .light_gray);

    var detail_buffer: [256]u8 = undefined;
    const detail_text = try std.fmt.bufPrintZ(
        &detail_buffer,
        "frames {d}  materials {d}  texcoord blocks {d}  trailing NULs {d}",
        .{
            summary.frame_count,
            summary.material_count,
            summary.mesh_texture_coord_block_count,
            summary.trailing_nul_count,
        },
    );
    rl.drawText(detail_text, 32, 258, 20, .sky_blue);

    rl.drawRectangleRounded(.{ .x = 32, .y = 304, .width = 1216, .height = 388 }, 0.03, 8, .dark_blue);
    rl.drawText("Current parser result", 56, 332, 26, .ray_white);

    const mesh_name = if (summary.meshes.len > 0) summary.meshes[0].name else "<none>";
    const material_name = if (summary.materials.len > 0) summary.materials[0].name else "<none>";
    const texture_name = if (summary.texture_filenames.len > 0) summary.texture_filenames[0] else "<none>";

    var mesh_buffer: [384]u8 = undefined;
    const mesh_text = try std.fmt.bufPrintZ(&mesh_buffer, "First mesh: {s}", .{mesh_name});
    rl.drawText(mesh_text, 56, 378, 22, .light_gray);

    var material_buffer: [384]u8 = undefined;
    const material_text = try std.fmt.bufPrintZ(&material_buffer, "First material: {s}", .{material_name});
    rl.drawText(material_text, 56, 414, 22, .light_gray);

    var texture_buffer: [384]u8 = undefined;
    const texture_text = try std.fmt.bufPrintZ(&texture_buffer, "Referenced texture: {s}", .{texture_name});
    rl.drawText(texture_text, 56, 450, 22, .light_gray);

    rl.drawText("The .x2 files are text meshes, not opaque binary blobs.", 56, 500, 22, .gold);
    rl.drawText("Next step is to map these parsed sections to original RWG loading semantics and build a real model loader.", 56, 536, 22, .light_gray);
}

fn nextMode(mode: Mode) Mode {
    return switch (mode) {
        .textures => .audio,
        .audio => .models,
        .models => .textures,
    };
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
