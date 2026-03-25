const frontend_widget = @import("widget.zig");
const game_font = @import("../game_font.zig");

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
pub const center_offset_x: f32 = 0.0;
pub const play_offset_with_replay_x: f32 = 100.0;
pub const watch_replay_offset_x: f32 = -100.0;
pub const slider_adjust_step: i32 = 1;

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
        .difficulty => frontend_widget.type20TextRect(
            font,
            measurementLabel(.difficulty),
            difficulty_anchor_y,
            center_offset_x,
        ),
        .speed => frontend_widget.type20TextRect(
            font,
            measurementLabel(.speed),
            frontend_widget.sliderStackBelowLayout(sliderLayout(font, state, .difficulty)),
            center_offset_x,
        ),
        .play => frontend_widget.type20TextRect(
            font,
            "Play",
            frontend_widget.sliderStackBelowLayout(sliderLayout(font, state, .speed)),
            if (state.replay_available) play_offset_with_replay_x else center_offset_x,
        ),
        .watch_replay => frontend_widget.type20TextRect(
            font,
            "Watch Replay",
            frontend_widget.sliderStackBelowLayout(sliderLayout(font, state, .speed)),
            watch_replay_offset_x,
        ),
        .back => frontend_widget.type20TextRect(
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
