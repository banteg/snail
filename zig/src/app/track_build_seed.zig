const root_app = @import("../app.zig");
const frontend = @import("../frontend.zig");
const frontend_bridge = @import("../frontend/bridge.zig");

const FrontendLevelMode = frontend.FrontendLevelMode;

pub const Context = struct {
    command: root_app.AppCommand,
    active_frontend_mode: ?FrontendLevelMode,
    active_frontend_level_index: usize,
    level_index: usize,
    selected_level_record_override: ?frontend_bridge.SelectedLevelRecordOverride,
    math_random_state: *u32,
    current_runtime_build_seed: *u32,
    current_runtime_build_seed_level_index: *?usize,
    current_runtime_build_seed_mode: *?FrontendLevelMode,
};

pub fn nextInt15(random_state: *u32) u32 {
    random_state.* = (random_state.* *% 0x343fd) +% 0x269ec3;
    return (random_state.* >> 16) & 0x7fff;
}

pub fn seedForCurrentLoad(context: Context) u32 {
    if (context.command != .game) return 0;

    const mode = context.active_frontend_mode;
    if (context.selected_level_record_override) |record| {
        if (mode == record.mode and context.active_frontend_level_index == record.level_index) {
            context.current_runtime_build_seed.* = record.runtime_build_seed;
            context.current_runtime_build_seed_level_index.* = context.level_index;
            context.current_runtime_build_seed_mode.* = mode;
            return record.runtime_build_seed;
        }
    }
    if (context.current_runtime_build_seed_level_index.* == context.level_index and
        context.current_runtime_build_seed_mode.* == mode)
    {
        return context.current_runtime_build_seed.*;
    }

    const seed: u32 = switch (mode orelse return 0) {
        .tutorial, .time_trial => 0,
        .postal, .challenge => nextInt15(context.math_random_state),
    };
    context.current_runtime_build_seed.* = seed;
    context.current_runtime_build_seed_level_index.* = context.level_index;
    context.current_runtime_build_seed_mode.* = mode;
    return seed;
}

pub fn invalidate(context: Context) void {
    context.current_runtime_build_seed_level_index.* = null;
    context.current_runtime_build_seed_mode.* = null;
}
