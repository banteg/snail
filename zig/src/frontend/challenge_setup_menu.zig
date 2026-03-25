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
