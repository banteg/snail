const std = @import("std");
const rl = @import("raylib");
const app_ui = @import("app_ui.zig");
const gameplay = @import("gameplay.zig");
const level = @import("level.zig");
const segment = @import("segment.zig");
const track = @import("track.zig");

pub fn drawLevelPanel(state: anytype) !void {
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
    drawText(state, summary_text, 32, 194, 24, .ray_white);

    var path_buffer: [512]u8 = undefined;
    const path_text = try std.fmt.bufPrintZ(&path_buffer, "{s}", .{level_entry.path});
    drawText(state, path_text, 32, 226, 18, .light_gray);

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
    drawText(state, meta_text, 32, 258, 20, .sky_blue);

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
    drawText(state, runtime_text, 32, 284, 18, .light_gray);

    rl.drawRectangleRounded(.{ .x = 32, .y = 304, .width = 460, .height = 408 }, 0.03, 8, .dark_blue);
    drawText(state, "Level and segment notes", 56, 332, 26, .ray_white);

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
        drawText(state, segment_text, 56, 378, 20, .gold);

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
        drawText(state, timing_text, 56, 410, 20, .light_gray);

        if (segment_entry.message) |message| {
            drawText(state, "Tutorial message:", 56, 444, 20, .light_gray);
            try drawWrappedText(state, message, 56, 472, 412, 20, .ray_white);
        } else {
            drawText(state, "No per-segment tutorial metadata on this entry.", 56, 444, 20, .light_gray);
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
        drawText(state, dim_text, 56, 620, 18, .light_gray);
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
        drawText(state, sim_text, 56, 646, 18, .gold);

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
        drawText(state, cell_text, 56, 670, 18, .light_gray);

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
        drawText(state, event_text, 56, 692, 16, .sky_blue);

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
        drawText(state, counter_text, 56, 712, 16, .light_gray);
    }

    drawSegmentGrid(state.current_segment orelse return, 540, 194, 676, 482);
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
    if (state.catalog.segment_entries.len == 0) return;
    const entry = state.catalog.segment_entries[state.segment_index];
    const preview = state.current_standalone_segment_preview orelse return;
    const loaded_segment = preview.activeSegment(0) orelse return;

    var summary_buffer: [384]u8 = undefined;
    const summary_text = try std.fmt.bufPrintZ(
        &summary_buffer,
        "Segment {d}/{d}  id {d}  {s}  {d}x{d}",
        .{
            state.segment_index + 1,
            state.catalog.segment_entries.len,
            loaded_segment.segment_id,
            loaded_segment.name,
            loaded_segment.width,
            loaded_segment.height,
        },
    );
    drawText(state, summary_text, 32, 194, 24, .ray_white);

    var path_buffer: [512]u8 = undefined;
    const path_text = try std.fmt.bufPrintZ(&path_buffer, "{s}", .{entry.path});
    drawText(state, path_text, 32, 226, 18, .light_gray);

    var meta_buffer: [384]u8 = undefined;
    const meta_text = try std.fmt.bufPrintZ(
        &meta_buffer,
        "rows {d}  marked {d}  annotated {d}  runtime rows {d}  build 0x{x:0>8}",
        .{
            loaded_segment.rows.len,
            countMarkedRows(loaded_segment.rows),
            countAnnotatedRows(loaded_segment.rows),
            preview.total_rows,
            preview.runtime_build_flags,
        },
    );
    drawText(state, meta_text, 32, 258, 20, .sky_blue);

    rl.drawRectangleRounded(.{ .x = 32, .y = 304, .width = 460, .height = 408 }, 0.03, 8, .dark_blue);
    drawText(state, "Segment notes", 56, 332, 26, .ray_white);

    var runtime_buffer: [384]u8 = undefined;
    const runtime_text = try std.fmt.bufPrintZ(
        &runtime_buffer,
        "fallback G {d}  S {d}  width {d}  total rows {d}",
        .{
            preview.fallbackHazardCandidateCounts().garbage,
            preview.fallbackHazardCandidateCounts().salt,
            preview.max_width,
            preview.total_rows,
        },
    );
    drawText(state, runtime_text, 56, 378, 20, .gold);

    if (findFirstAnnotatedRow(loaded_segment.rows)) |annotated_row| {
        var row_buffer: [384]u8 = undefined;
        const row_text = try std.fmt.bufPrintZ(
            &row_buffer,
            "First annotation row {d}: {s}",
            .{ annotated_row.index + 1, annotationLabel(annotated_row.row.annotation.?) },
        );
        drawText(state, row_text, 56, 410, 20, .light_gray);

        if (annotationDescription(annotated_row.row.annotation.?)) |description| {
            try drawWrappedText(state, description, 56, 442, 412, 20, .ray_white);
        }
    } else {
        drawText(state, "No row annotations on this segment.", 56, 410, 20, .light_gray);
    }

    drawSegmentGrid(loaded_segment.*, 540, 194, 676, 482);
}

pub fn drawSegmentViewport(state: anytype) void {
    if (state.catalog.segment_entries.len == 0) return;
    const preview = state.current_standalone_segment_preview orelse return;
    const camera = preview.previewCamera(@floatCast(state.render_time_seconds), 0);
    camera.begin();
    defer rl.endMode3D();

    const grid_slices: i32 = @intCast(@max(preview.total_rows, 10));
    rl.drawGrid(@min(grid_slices, 80), 1.0);
    preview.draw(0);
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
