const std = @import("std");

const rl = @import("raylib");
const ui = @import("../ui.zig");
const frontend_art = @import("../frontend/art.zig");
const frontend_widget = @import("../frontend/widget.zig");
const game_font = @import("../game_font.zig");
const level_prompt = @import("../level_prompt.zig");

const VirtualLayout = ui.VirtualLayout;

const gameplay_prompt_anchor_y: f32 = 330.0;
const tutorial_prompt_anchor_y: f32 = 116.0;
const tutorial_prompt_interactive_anchor_y: f32 = 176.0;
pub const click_start_anchor_y: f32 = 200.0;

const click_start_text = "Click to Start";

const ActiveLayout = struct {
    lines: [frontend_widget.multiline_prompt_max_lines][]const u8 = [_][]const u8{""} ** frontend_widget.multiline_prompt_max_lines,
    line_count: usize = 0,
    widget_layout: frontend_widget.MultilinePromptLayout = .{},
};

pub const Context = struct {
    font: *const game_font.Loaded,
    widget_art: *const frontend_art.FrontendWidgetArt,
    mouse_local: ?rl.Vector2,
};

pub fn activeOkHitRect(context: Context, queue: *const level_prompt.Queue, tutorial: bool) ?frontend_widget.Rect {
    const prompt = queue.active() orelse return null;
    if (!prompt.interactive) return null;
    const prompt_layout = activeLayout(context, prompt, tutorial);
    const ok_text_rect = prompt_layout.widget_layout.ok_text_rect orelse return null;
    var idle_state = frontend_widget.TextButtonState{};
    idle_state.snapFor(.menu_button, false);
    return frontend_widget.hitRect(ok_text_rect, idle_state);
}

pub fn drawGameplayStack(context: Context, layout: VirtualLayout, queue: *const level_prompt.Queue) !void {
    try drawWidget(context, layout, queue, false);
}

pub fn drawClickStartWidget(context: Context, layout: VirtualLayout) void {
    // PORT(verified): `initialize_click_start` creates one centered menu_button widget at authored y=200.
    drawInvisibleMenuText(context, layout, click_start_text, click_start_anchor_y);
}

pub fn drawTutorialStack(context: Context, layout: VirtualLayout, queue: *const level_prompt.Queue) !void {
    try drawWidget(context, layout, queue, true);
}

fn promptLines(text: []const u8, lines: *[frontend_widget.multiline_prompt_max_lines][]const u8) []const []const u8 {
    var count: usize = 0;
    var start: usize = 0;
    for (text, 0..) |char, index| {
        if (char != '>') continue;
        if (count < lines.len) {
            lines[count] = text[start..index];
            count += 1;
        }
        start = index + 1;
    }
    if (count < lines.len) {
        lines[count] = text[start..];
        count += 1;
    }
    return lines[0..count];
}

fn anchorY(tutorial: bool, interactive: bool) f32 {
    if (!tutorial) return gameplay_prompt_anchor_y;
    return if (interactive) tutorial_prompt_interactive_anchor_y else tutorial_prompt_anchor_y;
}

fn activeLayout(context: Context, prompt: level_prompt.Entry, tutorial: bool) ActiveLayout {
    return layoutForText(context, prompt.message, tutorial, prompt.interactive);
}

fn layoutForText(context: Context, text: []const u8, tutorial: bool, interactive: bool) ActiveLayout {
    var prompt_layout = ActiveLayout{};
    const lines = promptLines(text, &prompt_layout.lines);
    prompt_layout.line_count = lines.len;
    prompt_layout.widget_layout = frontend_widget.menuPromptLayout(
        context.font,
        lines,
        anchorY(tutorial, interactive),
        interactive,
    );
    return prompt_layout;
}

fn drawMessageLines(context: Context, layout: VirtualLayout, prompt_layout: ActiveLayout) void {
    const widget_art: frontend_widget.Art = .{
        .border = context.widget_art.border.?.texture,
    };
    for (0..prompt_layout.line_count) |index| {
        const line = prompt_layout.lines[index];
        var text_state = frontend_widget.TextButtonState{};
        text_state.snapFor(.menu_button, true);
        frontend_widget.drawTextButtonWithOptions(
            layout,
            widget_art,
            context.font,
            .menu_button,
            line,
            prompt_layout.widget_layout.line_rects[index],
            text_state,
            false,
            .{ .flags = @intFromEnum(frontend_widget.WidgetFlags.invisible_background) },
        );
    }
}

fn drawInvisibleMenuText(context: Context, layout: VirtualLayout, text: []const u8, anchor_y: f32) void {
    var text_state = frontend_widget.TextButtonState{};
    text_state.snapFor(.menu_button, true);
    frontend_widget.drawTextButtonWithOptions(
        layout,
        .{ .border = context.widget_art.border.?.texture },
        context.font,
        .menu_button,
        text,
        frontend_widget.menuButtonTextRect(context.font, text, anchor_y, 0.0),
        text_state,
        false,
        .{ .flags = @intFromEnum(frontend_widget.WidgetFlags.invisible_background) },
    );
}

fn drawWidget(context: Context, layout: VirtualLayout, queue: *const level_prompt.Queue, tutorial: bool) !void {
    const prompt = queue.active() orelse return;
    const prompt_layout = activeLayout(context, prompt, tutorial);
    var frame_state = frontend_widget.TextButtonState{};
    frame_state.snapFor(.menu_button, false);
    const colors = frontend_widget.colorsForState(frame_state, false);
    frontend_widget.drawNineSliceFrame(
        layout,
        context.widget_art.border.?.texture,
        prompt_layout.widget_layout.frame_rect,
        frontend_widget.menu_button_border_edge,
        frontend_widget.menu_button_border_edge / 128.0,
        colors.fill,
    );
    drawMessageLines(context, layout, prompt_layout);

    if (prompt_layout.widget_layout.ok_text_rect) |ok_text_rect| {
        var idle_state = frontend_widget.TextButtonState{};
        idle_state.snapFor(.menu_button, false);
        const hit_rect = frontend_widget.hitRect(ok_text_rect, idle_state);
        const hovered = if (context.mouse_local) |mouse|
            hit_rect.contains(mouse)
        else
            false;
        var ok_state = frontend_widget.TextButtonState{};
        ok_state.snapFor(.menu_button, hovered);
        frontend_widget.drawTextButton(
            layout,
            .{ .border = context.widget_art.border.?.texture },
            context.font,
            .menu_button,
            "OK",
            ok_text_rect,
            ok_state,
            false,
        );
    }
}

test "click-start prompt uses native authored y" {
    try std.testing.expectEqual(@as(f32, 200.0), click_start_anchor_y);
}
