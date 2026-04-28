const ui = @import("../ui.zig");
const frontend_activation = @import("activation.zig");
const frontend_options_menu = @import("options_menu.zig");
const frontend_widget = @import("widget.zig");
const game_font = @import("../game_font.zig");

const VirtualLayout = ui.VirtualLayout;

pub const Item = enum {
    difficulty,
    speed,
    play,
    watch_replay,
    back,
};

pub const items = [_]Item{
    .difficulty,
    .speed,
    .play,
    .watch_replay,
    .back,
};

pub const items_without_replay = [_]Item{
    .difficulty,
    .speed,
    .play,
    .back,
};

pub const button_count = items.len;
pub const difficulty_button_index: usize = 0;
pub const speed_button_index: usize = 1;
pub const play_button_index: usize = 2;
pub const watch_replay_button_index: usize = 3;
pub const back_button_index: usize = 4;
pub const difficulty_anchor_y: f32 = 80.0;
// PORT(verified): `initialize_subgame` sets the front-end center justify to `25` before the
// challenge setup widgets are constructed. Per-widget offsets are added on top of that value.
pub const center_offset_x: f32 = frontend_widget.menu_button_center_offset_x;
pub const play_offset_with_replay_x: f32 = center_offset_x + 100.0;
pub const watch_replay_offset_x: f32 = center_offset_x - 100.0;
// PORT(verified): challenge setup uses the shared front-end slider widget; one arrow
// activation moves the normalized target by 0.2, then the setup screen stores `% * 100`.
pub const slider_adjust_step: i32 = 20;

pub fn measurementLabel(item: Item) []const u8 {
    return switch (item) {
        .difficulty => "   Select Difficulty    >",
        .speed => "      Select Speed      >",
        .play => "Play",
        .watch_replay => "Watch Replay",
        .back => "Back",
    };
}

pub fn visibleLabel(item: Item) []const u8 {
    return switch (item) {
        .difficulty => "Select Difficulty",
        .speed => "Select Speed",
        .play => "Play",
        .watch_replay => "Watch Replay",
        .back => "Back",
    };
}

pub const LayoutState = struct {
    replay_available: bool,
    difficulty_value_text: []const u8,
    speed_value_text: []const u8,
    difficulty_row_state: frontend_widget.TextButtonState,
    speed_row_state: frontend_widget.TextButtonState,
};

pub fn sliderLayout(font: *const game_font.Loaded, state: LayoutState, item: Item) frontend_widget.SliderLayout {
    const title_rect = switch (item) {
        .difficulty => textRect(font, state, .difficulty),
        .speed => textRect(font, state, .speed),
        .play, .watch_replay, .back => unreachable,
    };
    const row_state = switch (item) {
        .difficulty => state.difficulty_row_state,
        .speed => state.speed_row_state,
        .play, .watch_replay, .back => unreachable,
    };
    return frontend_widget.sliderLayout(font, title_rect, row_state, switch (item) {
        .difficulty => state.difficulty_value_text,
        .speed => state.speed_value_text,
        .play, .watch_replay, .back => unreachable,
    });
}

pub fn textRect(font: *const game_font.Loaded, state: LayoutState, item: Item) frontend_widget.Rect {
    return switch (item) {
        .difficulty => frontend_widget.menuButtonTextRect(
            font,
            measurementLabel(.difficulty),
            difficulty_anchor_y,
            center_offset_x,
        ),
        .speed => frontend_widget.menuButtonTextRect(
            font,
            measurementLabel(.speed),
            frontend_widget.sliderStackBelowLayout(sliderLayout(font, state, .difficulty)),
            center_offset_x,
        ),
        .play => frontend_widget.menuButtonTextRect(
            font,
            "Play",
            frontend_widget.sliderStackBelowLayout(sliderLayout(font, state, .speed)),
            if (state.replay_available) play_offset_with_replay_x else center_offset_x,
        ),
        .watch_replay => frontend_widget.menuButtonTextRect(
            font,
            "Watch Replay",
            frontend_widget.sliderStackBelowLayout(sliderLayout(font, state, .speed)),
            watch_replay_offset_x,
        ),
        .back => frontend_widget.menuButtonTextRect(
            font,
            "Back",
            frontend_widget.stackBelow(if (state.replay_available)
                textRect(font, state, .watch_replay)
            else
                textRect(font, state, .play)),
            center_offset_x,
        ),
    };
}

pub fn drawMenuUi(
    state: anytype,
    layout: VirtualLayout,
    layout_state: LayoutState,
    active_target: ?frontend_activation.HoverTarget,
    slider_textures: frontend_widget.SliderTextures,
) void {
    drawSliderRow(
        state,
        layout,
        layout_state,
        .difficulty,
        @as(f32, @floatFromInt(state.runtime_config.challengeReplayDifficultyValue())) * 0.01,
        state.challenge_setup_difficulty_display_value,
        state.challenge_setup_button_states[difficulty_button_index],
        if (active_target) |target| target == .challenge_setup_difficulty_less else false,
        if (active_target) |target| target == .challenge_setup_difficulty_more else false,
        slider_textures,
    );
    drawSliderRow(
        state,
        layout,
        layout_state,
        .speed,
        @as(f32, @floatFromInt(state.runtime_config.challengeReplaySpeedValue())) * 0.01,
        state.challenge_setup_speed_display_value,
        state.challenge_setup_button_states[speed_button_index],
        if (active_target) |target| target == .challenge_setup_speed_less else false,
        if (active_target) |target| target == .challenge_setup_speed_more else false,
        slider_textures,
    );

    frontend_widget.drawMenuButton(
        layout,
        .{
            .border = state.frontend_widget_art.border.?.texture,
        },
        &state.ui_font,
        "Play",
        textRect(&state.ui_font, layout_state, .play),
        state.challenge_setup_button_states[play_button_index],
        false,
    );
    if (layout_state.replay_available) {
        frontend_widget.drawMenuButton(
            layout,
            .{
                .border = state.frontend_widget_art.border.?.texture,
            },
            &state.ui_font,
            "Watch Replay",
            textRect(&state.ui_font, layout_state, .watch_replay),
            state.challenge_setup_button_states[watch_replay_button_index],
            false,
        );
    }
    frontend_widget.drawMenuButton(
        layout,
        .{
            .border = state.frontend_widget_art.border.?.texture,
        },
        &state.ui_font,
        "Back",
        textRect(&state.ui_font, layout_state, .back),
        state.challenge_setup_button_states[back_button_index],
        false,
    );
}

fn drawSliderRow(
    state: anytype,
    layout: VirtualLayout,
    layout_state: LayoutState,
    item: Item,
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
        visibleLabel(item),
        textRect(&state.ui_font, layout_state, item),
        frontend_options_menu.sliderValueText(value, &value_buffer),
        value,
        displayed_value,
        row_state,
        less_hovered,
        more_hovered,
    );
}
