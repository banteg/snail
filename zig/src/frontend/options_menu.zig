const app_ui = @import("../app_ui.zig");
const frontend_activation = @import("activation.zig");
const frontend = @import("../frontend.zig");
const frontend_widget = @import("widget.zig");
const game_font = @import("../game_font.zig");
const std = @import("std");

const VirtualLayout = app_ui.VirtualLayout;

// PORT(verified): `initialize_options_menu` seeds the fullscreen row at `y = 75`, then nudges
// the widget down by `+8`, so the final authored-space anchor is `83`.
pub const fullscreen_anchor_y: f32 = 83.0;
pub const button_count: usize = 4;
pub const fullscreen_button_index: usize = 0;
pub const sound_button_index: usize = 1;
pub const music_button_index: usize = 2;
pub const back_button_index: usize = 3;
pub const slider_adjust_step: f32 = 0.2;
pub const slider_display_lerp: f32 = 0.8;
// PORT(verified): `initialize_options_menu` keeps the options rows on the centered shell-font path.
// The constructor's `90.0` seed is only the left-measure start fed into `sub_44abe0`; the final
// centered X comes from `arg13 + 320 - width*0.5`, and `arg13` stays `0.0` for this screen.
pub const button_center_offset_x: f32 = 0.0;

pub const LayoutState = struct {
    fullscreen_enabled: bool,
    sound_value: f32,
    music_value: f32,
    sound_row_state: frontend_widget.TextButtonState,
    music_row_state: frontend_widget.TextButtonState,
};

pub fn measurementLabel(state: LayoutState, item: frontend.OptionsMenuItem) []const u8 {
    return switch (item) {
        .fullscreen => if (state.fullscreen_enabled) "Full-screen On" else "Full-screen Off",
        .sound_volume => "     Sounds Volume     >",
        .music_volume => "      Music Volume      >",
        .back => "Back",
    };
}

pub fn visibleLabel(state: LayoutState, item: frontend.OptionsMenuItem) []const u8 {
    return switch (item) {
        .fullscreen => measurementLabel(state, .fullscreen),
        .sound_volume => "Sounds Volume",
        .music_volume => "Music Volume",
        .back => "Back",
    };
}

pub fn sliderValueText(value: f32, buffer: []u8) []const u8 {
    return std.fmt.bufPrint(buffer, "{d:0>2.0}%", .{std.math.clamp(value, 0.0, 1.0) * 100.0}) catch "00%";
}

pub fn sliderLayout(font: *const game_font.Loaded, state: LayoutState, item: frontend.OptionsMenuItem) frontend_widget.SliderLayout {
    var value_buffer: [16]u8 = undefined;
    const title_rect = switch (item) {
        .sound_volume => textRect(font, state, .sound_volume),
        .music_volume => textRect(font, state, .music_volume),
        else => unreachable,
    };
    const value = switch (item) {
        .sound_volume => state.sound_value,
        .music_volume => state.music_value,
        else => unreachable,
    };
    const row_state = switch (item) {
        .sound_volume => state.sound_row_state,
        .music_volume => state.music_row_state,
        else => unreachable,
    };
    return frontend_widget.sliderLayout(font, title_rect, row_state, sliderValueText(value, &value_buffer));
}

pub fn textRect(font: *const game_font.Loaded, state: LayoutState, item: frontend.OptionsMenuItem) frontend_widget.Rect {
    return switch (item) {
        .fullscreen => frontend_widget.type20TextRect(
            font,
            measurementLabel(state, .fullscreen),
            fullscreen_anchor_y,
            button_center_offset_x,
        ),
        .sound_volume => frontend_widget.type20TextRect(
            font,
            measurementLabel(state, .sound_volume),
            textRect(font, state, .fullscreen).top + textRect(font, state, .fullscreen).height + frontend_widget.type20_stack_gap,
            button_center_offset_x,
        ),
        .music_volume => frontend_widget.type20TextRect(
            font,
            measurementLabel(state, .music_volume),
            frontend_widget.sliderStackBelowLayout(sliderLayout(font, state, .sound_volume)),
            button_center_offset_x,
        ),
        .back => frontend_widget.type20TextRect(
            font,
            "Back",
            frontend_widget.sliderStackBelowLayout(sliderLayout(font, state, .music_volume)),
            button_center_offset_x,
        ),
    };
}

pub fn drawMenuUi(
    state: anytype,
    layout: VirtualLayout,
    menu_layout: LayoutState,
    active_target: ?frontend_activation.HoverTarget,
    slider_textures: frontend_widget.SliderTextures,
) void {
    frontend_widget.drawType20Button(
        layout,
        .{
            .border = state.frontend_widget_art.border.?.texture,
        },
        &state.ui_font,
        visibleLabel(menu_layout, .fullscreen),
        textRect(&state.ui_font, menu_layout, .fullscreen),
        state.options_button_states[fullscreen_button_index],
        false,
    );
    drawSliderRow(
        state,
        layout,
        menu_layout,
        .sound_volume,
        state.runtime_config.soundVolume(),
        state.options_sound_display_value,
        state.options_button_states[sound_button_index],
        if (active_target) |target| target == .options_sound_less else false,
        if (active_target) |target| target == .options_sound_more else false,
        slider_textures,
    );
    drawSliderRow(
        state,
        layout,
        menu_layout,
        .music_volume,
        state.runtime_config.musicVolume(),
        state.options_music_display_value,
        state.options_button_states[music_button_index],
        if (active_target) |target| target == .options_music_less else false,
        if (active_target) |target| target == .options_music_more else false,
        slider_textures,
    );
    frontend_widget.drawType20Button(
        layout,
        .{
            .border = state.frontend_widget_art.border.?.texture,
        },
        &state.ui_font,
        "Back",
        textRect(&state.ui_font, menu_layout, .back),
        state.options_button_states[back_button_index],
        false,
    );
}

fn drawSliderRow(
    state: anytype,
    layout: VirtualLayout,
    menu_layout: LayoutState,
    item: frontend.OptionsMenuItem,
    value: f32,
    displayed_value: f32,
    row_state: frontend_widget.TextButtonState,
    less_hovered: bool,
    more_hovered: bool,
    slider_textures: frontend_widget.SliderTextures,
) void {
    var value_buffer: [16]u8 = undefined;
    frontend_widget.drawSliderMenuRow(
        layout,
        .{
            .border = state.frontend_widget_art.border.?.texture,
        },
        slider_textures,
        &state.ui_font,
        visibleLabel(menu_layout, item),
        textRect(&state.ui_font, menu_layout, item),
        sliderValueText(value, &value_buffer),
        value,
        displayed_value,
        row_state,
        less_hovered,
        more_hovered,
    );
}
