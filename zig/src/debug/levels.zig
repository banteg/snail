const std = @import("std");
const rl = @import("raylib");
const attachment_builders = @import("../attachment_builders.zig");
const app_ui = @import("../app_ui.zig");
const gameplay = @import("../gameplay.zig");
const level = @import("../level.zig");
const segment = @import("../segment.zig");
const track = @import("../track.zig");

pub fn drawLevelPanel(state: anytype) !void {
    const level_entry = state.resources.catalog.level_entries[state.level_index];
    const loaded_level = state.current_level orelse return;
    const loaded_track_preview = state.current_track_preview orelse return;
    const screen_width = rl.getScreenWidth();
    const screen_height = rl.getScreenHeight();
    var track_value_buffer: [32]u8 = undefined;
    var quota_value_buffer: [32]u8 = undefined;
    var speed_value_buffer: [32]u8 = undefined;
    var garbage_value_buffer: [32]u8 = undefined;
    var salt_value_buffer: [32]u8 = undefined;
    var garbage_scalar_buffer: [32]u8 = undefined;
    var salt_scalar_buffer: [32]u8 = undefined;
    var segment_meta_buffer: [192]u8 = undefined;

    const summary_card = rl.Rectangle{ .x = 24, .y = 128, .width = 404, .height = if (state.level_runner != null) 340 else 238 };
    const grid_card = rl.Rectangle{
        .x = @floatFromInt(@max(screen_width - 276, 452)),
        .y = @floatFromInt(@max(screen_height - 252, 160)),
        .width = 244,
        .height = 220,
    };

    drawOverlayCard(summary_card);
    drawInsetCard(grid_card);

    var summary_buffer: [256]u8 = undefined;
    const summary_text = try std.fmt.bufPrintZ(
        &summary_buffer,
        "Level {d}/{d}  {s}",
        .{
            state.level_index + 1,
            state.resources.catalog.level_entries.len,
            loaded_level.name,
        },
    );
    drawText(state, summary_text, 44, 150, 22, .ray_white);

    var path_buffer: [512]u8 = undefined;
    const path_text = try std.fmt.bufPrintZ(&path_buffer, "{s}", .{level_entry.path});
    drawText(state, path_text, 44, 178, 16, .light_gray);

    var meta_buffer: [384]u8 = undefined;
    const meta_text = try std.fmt.bufPrintZ(
        &meta_buffer,
        "mode {s}  segments {d}  track {s}",
        .{
            loaded_level.mode,
            loaded_track_preview.segments.len,
            trackToText(&track_value_buffer, loaded_level.track),
        },
    );
    drawText(state, meta_text, 44, 202, 16, .sky_blue);

    const fallback_counts = loaded_track_preview.fallbackHazardCandidateCounts();
    var runtime_buffer: [384]u8 = undefined;
    const runtime_text = try std.fmt.bufPrintZ(
        &runtime_buffer,
        "quota {s}  speed {s}  garbage {s}  salt {s}",
        .{
            optionalUsizeToText(&quota_value_buffer, loaded_level.quota),
            optionalUsizeToText(&speed_value_buffer, loaded_level.speed),
            optionalUsizeToText(&garbage_value_buffer, loaded_level.garbage),
            optionalUsizeToText(&salt_value_buffer, loaded_level.salt),
        },
    );
    drawText(state, runtime_text, 44, 226, 16, .light_gray);

    const scalar_text = try std.fmt.bufPrintZ(
        &segment_meta_buffer,
        "build 0x{x:0>8}  scalars G {s} / S {s}  fallback {d}/{d}",
        .{
            loaded_track_preview.runtime_build_flags,
            optionalFloatToText(&garbage_scalar_buffer, loaded_level.normalizedGarbageScalar()),
            optionalFloatToText(&salt_scalar_buffer, loaded_level.normalizedSaltScalar()),
            fallback_counts.garbage,
            fallback_counts.salt,
        },
    );
    drawText(state, scalar_text, 44, 250, 14, .light_gray);

    if (state.activeLevelSegmentEntry()) |segment_entry| {
        var segment_buffer: [256]u8 = undefined;
        const segment_text = try std.fmt.bufPrintZ(
            &segment_buffer,
            "Segment {d}/{d}  {s}",
            .{
                state.level_segment_index + 1,
                loaded_level.segments.len,
                segment_entry.path,
            },
        );
        drawText(state, segment_text, 44, 286, 16, .gold);

        var timing_buffer: [256]u8 = undefined;
        var duration_value_buffer: [32]u8 = undefined;
        var angle_value_buffer: [32]u8 = undefined;
        const timing_text = try std.fmt.bufPrintZ(
            &timing_buffer,
            "duration {s}  angle {s}  sample {s}",
            .{
                optionalFloatToText(&duration_value_buffer, segment_entry.duration),
                optionalFloatToText(&angle_value_buffer, segment_entry.angle),
                segment_entry.sample orelse "<none>",
            },
        );
        drawText(state, timing_text, 44, 310, 14, .light_gray);

        if (segment_entry.message) |message| {
            var message_buffer: [160]u8 = undefined;
            const clipped_message = clippedText(&message_buffer, message, 58);
            drawText(state, "message", 44, 334, 14, .sky_blue);
            drawText(state, clipped_message, 124, 334, 14, .ray_white);
        }
    }

    if (state.current_segment) |loaded_segment| {
        var dim_buffer: [256]u8 = undefined;
        const dim_text = try std.fmt.bufPrintZ(
            &dim_buffer,
            "grid {d}x{d}  annotated {d}  marked {d}  rows {d}",
            .{
                loaded_segment.width,
                loaded_segment.height,
                countAnnotatedRows(loaded_segment.rows),
                countMarkedRows(loaded_segment.rows),
                loaded_track_preview.total_rows,
            },
        );
        drawText(state, dim_text, 44, if (state.level_runner != null) 354 else 334, 14, .light_gray);
    }

    if (state.level_runner) |runner| {
        var sim_buffer: [256]u8 = undefined;
        const sim_text = try std.fmt.bufPrintZ(
            &sim_buffer,
            "row {d:.2}/{d}  cursor {d}+{d:.2}  lane {d}->{d}",
            .{
                runner.row_position,
                loaded_track_preview.total_rows,
                runner.runtime_track_index,
                runner.movement_progress,
                runner.lane_index,
                runner.resolved_lane_index,
            },
        );
        drawText(state, sim_text, 44, 382, 14, .gold);

        var cell_buffer: [256]u8 = undefined;
        var path_value_buffer: [96]u8 = undefined;
        var tile_value_buffer: [32]u8 = undefined;
        const cell_text = try std.fmt.bufPrintZ(
            &cell_buffer,
            "cell {c}  tile {s}  attach {s}  path {s}",
            .{
                runner.current_cell,
                optionalHexU8ToText(&tile_value_buffer, runner.runtimeTileHint()),
                runner.attachment_hint.label(),
                optionalTextToText(&path_value_buffer, runner.activePathName()),
            },
        );
        drawText(state, cell_text, 44, 404, 14, .light_gray);

        var event_buffer: [256]u8 = undefined;
        const event_text = try std.fmt.bufPrintZ(
            &event_buffer,
            "event {s}  paused {s}  speed {d:.1}  tick {d}",
            .{
                runner.recentEventLabel(),
                if (runner.paused) "yes" else "no",
                runner.speed_rows_per_second,
                runner.tick_count,
            },
        );
        drawText(state, event_text, 44, 426, 14, .sky_blue);

        var counter_buffer: [256]u8 = undefined;
        const counter_text = try std.fmt.bufPrintZ(
            &counter_buffer,
            "H {d}  J {d}  G {d}  S {d}  Sl {d}  A {d}/{d}",
            .{
                runner.counters.health_pickups,
                runner.counters.jetpack_pickups,
                runner.counters.garbage_hits,
                runner.counters.salt_hits,
                runner.counters.slug_hits,
                runner.counters.attachments_begun,
                runner.counters.attachments_completed,
            },
        );
        drawText(state, counter_text, 44, 448, 14, .light_gray);
    }

    drawText(state, "segment grid", @intFromFloat(grid_card.x + 18.0), @intFromFloat(grid_card.y + 14.0), 14, .light_gray);
    drawSegmentGrid(
        &loaded_track_preview,
        state.current_segment orelse return,
        state.level_segment_index,
        false,
        @intFromFloat(grid_card.x + 12.0),
        @intFromFloat(grid_card.y + 34.0),
        @intFromFloat(grid_card.width - 24.0),
        @intFromFloat(grid_card.height - 46.0),
    );
}

pub fn drawLevelViewport(state: anytype) void {
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

pub fn drawSegmentPanel(state: anytype) !void {
    if (state.resources.catalog.segment_entries.len == 0) return;
    const entry = state.resources.catalog.segment_entries[state.segment_index];
    const preview = state.current_standalone_segment_preview orelse return;
    const loaded_segment = preview.activeSegment(0) orelse return;
    const screen_width = rl.getScreenWidth();
    const screen_height = rl.getScreenHeight();
    const summary_card = rl.Rectangle{ .x = 24, .y = 128, .width = 352, .height = 164 };
    const grid_card = rl.Rectangle{
        .x = @floatFromInt(@max(screen_width - 272, 392)),
        .y = @floatFromInt(@max(screen_height - 246, 160)),
        .width = 240,
        .height = 214,
    };

    drawOverlayCard(summary_card);
    drawInsetCard(grid_card);

    var summary_buffer: [256]u8 = undefined;
    const summary_text = try std.fmt.bufPrintZ(
        &summary_buffer,
        "Segment {d}/{d}  {s}",
        .{
            state.segment_index + 1,
            state.resources.catalog.segment_entries.len,
            loaded_segment.name,
        },
    );
    drawText(state, summary_text, 44, 150, 22, .ray_white);

    var path_buffer: [512]u8 = undefined;
    const path_text = try std.fmt.bufPrintZ(&path_buffer, "{s}", .{entry.path});
    drawText(state, path_text, 44, 178, 16, .light_gray);

    var meta_buffer: [256]u8 = undefined;
    const meta_text = try std.fmt.bufPrintZ(
        &meta_buffer,
        "id {d}  {d}x{d}  rows {d}  annotated {d}",
        .{
            loaded_segment.segment_id,
            loaded_segment.width,
            loaded_segment.height,
            loaded_segment.rows.len,
            countAnnotatedRows(loaded_segment.rows),
        },
    );
    drawText(state, meta_text, 44, 202, 16, .sky_blue);

    var runtime_buffer: [256]u8 = undefined;
    const runtime_text = try std.fmt.bufPrintZ(
        &runtime_buffer,
        "render {s}  track {d}  overlay {s}  grid {s}  attachments {s}",
        .{
            @tagName(state.segment_render_mode),
            state.segment_track_set_index,
            if (state.segment_show_overlay) "on" else "off",
            if (state.segment_show_grid) "on" else "off",
            if (state.segment_show_attachments) "on" else "off",
        },
    );
    drawText(state, runtime_text, 44, 226, 14, .gold);

    var build_buffer: [256]u8 = undefined;
    const build_text = try std.fmt.bufPrintZ(
        &build_buffer,
        "marked {d}  fallback {d}/{d}  build 0x{x:0>8}  attachments {d}",
        .{
            countMarkedRows(loaded_segment.rows),
            preview.fallbackHazardCandidateCounts().garbage,
            preview.fallbackHazardCandidateCounts().salt,
            preview.runtime_build_flags,
            preview.attachmentPathCountForSegment(state.segment_index),
        },
    );
    drawText(state, build_text, 44, 248, 14, .light_gray);

    var details_y: i32 = 270;
    if (state.segment_show_attachments) {
        details_y = try drawSegmentAttachmentSummary(state, &preview, state.segment_index, details_y);
    }

    if (findFirstAnnotatedRow(loaded_segment.rows)) |annotated_row| {
        var row_buffer: [256]u8 = undefined;
        const row_text = try std.fmt.bufPrintZ(
            &row_buffer,
            "first annotation row {d}: {s}",
            .{ annotated_row.index + 1, annotationLabel(annotated_row.row.annotation.?) },
        );
        drawText(state, row_text, 44, details_y, 14, .light_gray);

        if (annotationDescription(annotated_row.row.annotation.?)) |description| {
            var description_buffer: [160]u8 = undefined;
            drawText(state, clippedText(&description_buffer, description, 54), 44, details_y + 22, 14, .ray_white);
        }
    } else {
        drawText(state, "No row annotations on this segment.", 44, details_y, 14, .light_gray);
    }

    drawText(state, "segment grid", @intFromFloat(grid_card.x + 18.0), @intFromFloat(grid_card.y + 14.0), 14, .light_gray);
    drawSegmentGrid(
        &preview,
        loaded_segment.*,
        state.segment_index,
        state.segment_show_attachments,
        @intFromFloat(grid_card.x + 12.0),
        @intFromFloat(grid_card.y + 34.0),
        @intFromFloat(grid_card.width - 24.0),
        @intFromFloat(grid_card.height - 46.0),
    );
}

pub fn drawSegmentViewport(state: anytype) void {
    if (state.resources.catalog.segment_entries.len == 0) return;
    const preview = state.current_standalone_segment_preview orelse return;
    const camera = preview.previewCamera(@floatCast(state.render_time_seconds), 0);
    camera.begin();
    defer rl.endMode3D();

    if (state.segment_show_grid) {
        const grid_slices: i32 = @intCast(@max(preview.total_rows, 10));
        rl.drawGrid(@min(grid_slices, 80), 1.0);
    }

    switch (state.segment_render_mode) {
        .game => {
            if (state.current_standalone_segment_scene) |scene| {
                scene.draw(&preview, 0);
            } else {
                preview.drawRawDebug(0);
            }
            if (state.segment_show_overlay) {
                preview.drawDebugOverlay(0);
            }
        },
        .raw => preview.drawRawDebug(0),
    }
}

fn uiContext(state: anytype) app_ui.Context {
    return .{ .font = &state.ui_font };
}

fn drawText(state: anytype, text: []const u8, x: i32, y: i32, font_size: i32, color: rl.Color) void {
    app_ui.drawText(uiContext(state), text, x, y, font_size, color);
}

fn drawWrappedText(state: anytype, text: []const u8, x: i32, y: i32, max_width: i32, line_height: i32, color: rl.Color) !void {
    return app_ui.drawWrappedText(uiContext(state), text, x, y, max_width, line_height, color);
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

fn drawSegmentGrid(
    preview: *const track.LoadedLevelPreview,
    loaded_segment: segment.Definition,
    segment_index: usize,
    show_attachments: bool,
    x: i32,
    y: i32,
    width: i32,
    height: i32,
) void {
    rl.drawRectangleLines(x, y, width, height, .{ .r = 255, .g = 255, .b = 255, .a = 38 });

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
        if (show_attachments) {
            if (attachmentRowForSegment(preview, segment_index, row_index)) |path_row| {
                const highlight_rect = rl.Rectangle{
                    .x = offset_x - 2.0,
                    .y = row_y - 1.0,
                    .width = grid_width + 4.0,
                    .height = cell_size + 2.0,
                };
                rl.drawRectangleRounded(highlight_rect, 0.12, 6, .{ .r = 255, .g = 180, .b = 0, .a = 22 });
                rl.drawRectangleRoundedLinesEx(highlight_rect, 0.12, 6, 1.0, .{ .r = 255, .g = 208, .b = 96, .a = 128 });

                var label_buffer: [32]u8 = undefined;
                const label_source = if (path_row.public_path) |public_path| public_path.authoredName() else path_row.raw_name;
                const label = clippedText(&label_buffer, label_source, 10);
                var label_z_buffer: [32]u8 = undefined;
                const label_z = std.fmt.bufPrintZ(&label_z_buffer, "{s}", .{label}) catch "path";
                rl.drawText(label_z, @intFromFloat(offset_x + grid_width + 6.0), @intFromFloat(row_y + 1.0), 10, .gold);
            }
        }

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

fn drawSegmentAttachmentSummary(state: anytype, preview: *const track.LoadedLevelPreview, segment_index: usize, start_y: i32) !i32 {
    var total: usize = 0;
    var drawn: usize = 0;
    var y = start_y;

    for (preview.attachment_scaffold.authored_rows) |path_row| {
        if (path_row.segment_index != segment_index) continue;
        total += 1;
        if (drawn >= 4) continue;

        var line_buffer: [256]u8 = undefined;
        const line = if (path_row.spec()) |spec|
            try std.fmt.bufPrintZ(
                &line_buffer,
                "path {d}: {s}  {s}/{s}",
                .{
                    path_row.row_index + 1,
                    path_row.raw_name,
                    spec.family.label(),
                    spec.status.label(),
                },
            )
        else
            try std.fmt.bufPrintZ(
                &line_buffer,
                "path {d}: {s}  unresolved",
                .{ path_row.row_index + 1, path_row.raw_name },
            );
        drawText(state, line, 44, y, 14, .gold);
        y += 20;
        drawn += 1;
    }

    if (total > drawn) {
        var more_buffer: [64]u8 = undefined;
        const more_text = try std.fmt.bufPrintZ(&more_buffer, "+{d} more path rows", .{total - drawn});
        drawText(state, more_text, 44, y, 14, .light_gray);
        y += 20;
    } else if (total == 0) {
        drawText(state, "No Path= rows in this segment.", 44, y, 14, .light_gray);
        y += 20;
    }

    return y + 2;
}

fn attachmentRowForSegment(preview: *const track.LoadedLevelPreview, segment_index: usize, row_index: usize) ?attachment_builders.AuthoredPathRow {
    for (preview.attachment_scaffold.authored_rows) |path_row| {
        if (path_row.segment_index == segment_index and path_row.row_index == row_index) {
            return path_row;
        }
    }
    return null;
}

fn drawOverlayCard(rect: rl.Rectangle) void {
    rl.drawRectangleRounded(rect, 0.08, 8, .{ .r = 0, .g = 0, .b = 0, .a = 170 });
    rl.drawRectangleRoundedLinesEx(rect, 0.08, 8, 1.0, .{ .r = 255, .g = 255, .b = 255, .a = 28 });
}

fn drawInsetCard(rect: rl.Rectangle) void {
    rl.drawRectangleRounded(rect, 0.06, 8, .{ .r = 8, .g = 18, .b = 34, .a = 188 });
    rl.drawRectangleRoundedLinesEx(rect, 0.06, 8, 1.0, .{ .r = 255, .g = 255, .b = 255, .a = 32 });
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

const AnnotatedRow = struct {
    index: usize,
    row: segment.Row,
};

fn findFirstAnnotatedRow(rows: []const segment.Row) ?AnnotatedRow {
    for (rows, 0..) |row, index| {
        if (row.annotation != null) {
            return .{ .index = index, .row = row };
        }
    }
    return null;
}

fn annotationLabel(annotation: segment.Annotation) []const u8 {
    return switch (annotation) {
        .path => "Path",
        .ring => "Ring",
        .parcel => "Parcel",
        .model => "3DModel",
        .jetpack_off => "JetPack=Off",
        .no_fall => "NoFall",
    };
}

fn annotationDescription(annotation: segment.Annotation) ?[]const u8 {
    return switch (annotation) {
        .path => |name| name,
        .ring => |kind| switch (kind) {
            .none => "Ring=None",
            .normal => "Ring=Normal",
            .powerup => "Ring=PowerUp",
            .explode => "Ring=Explode",
            .slow => "Ring=Slow",
        },
        .parcel => |parcel| blk: {
            _ = parcel;
            break :blk "Parcel annotation";
        },
        .model => |model| model.name,
        .jetpack_off => "JetPack=Off",
        .no_fall => "NoFall",
    };
}

fn clippedText(buffer: []u8, text: []const u8, max_chars: usize) []const u8 {
    if (text.len <= max_chars) return text;
    const clip_len = @min(buffer.len, @max(max_chars, 3));
    if (clip_len <= 3) return text[0..clip_len];
    @memcpy(buffer[0 .. clip_len - 3], text[0 .. clip_len - 3]);
    buffer[clip_len - 3] = '.';
    buffer[clip_len - 2] = '.';
    buffer[clip_len - 1] = '.';
    return buffer[0..clip_len];
}
