const std = @import("std");

const gameplay_assets = @import("assets.zig");
const jetpack = @import("jetpack.zig");

pub fn nativeJetpackVisualPresentationActive(thrust_visual_active: bool) bool {
    return thrust_visual_active;
}

// PORT(verified): native `SnailSkinTransitionState` from `change_snail_skin` @ 0x445fd0
// and `update_snail_skin_transition` @ 0x445f80. Slots: 0 = default, 1 = damage-red,
// 2 = invincible. `progress_step = 1 / (duration_s * 60)` when duration > 0, else 0
// (instant swap). When active and progress crosses 1.0, the native transition resets to
// slot 0 (default).
pub const SnailSkinSlot = enum(u8) {
    default = 0,
    damage = 1,
    invincible = 2,
};

pub const SnailSkinTransition = struct {
    selected_slot: SnailSkinSlot = .default,
    active: bool = false,
    progress: f32 = 0.0,
    progress_step: f32 = 0.0,

    pub fn change(self: *SnailSkinTransition, slot: SnailSkinSlot, duration_seconds: f32) void {
        self.active = true;
        self.progress = 0.0;
        self.selected_slot = slot;
        self.progress_step = if (duration_seconds > 0.0)
            1.0 / (duration_seconds * 60.0)
        else
            0.0;
    }

    pub fn tick(self: *SnailSkinTransition) void {
        if (!self.active) return;
        self.progress += self.progress_step;
        if (self.progress <= 1.0) return;
        self.progress = 0.0;
        self.active = false;
        self.selected_slot = .default;
    }
};

pub const WeaponChannelStates = struct {
    left: u8 = 0,
    right: u8 = 0,
    center: u8 = 0,
};

pub fn nativeWeaponChannelStates(movement_flags: u32) WeaponChannelStates {
    return switch (movement_flags) {
        1, 129 => .{ .center = 1 },
        2 => .{ .left = 1, .right = 1 },
        4 => .{ .left = 1, .right = 1, .center = 1 },
        8 => .{ .right = 2 },
        16, 144 => .{ .left = 2, .right = 2 },
        32, 64, 192 => .{ .center = 3 },
        else => .{ .center = 1 },
    };
}

pub const JetpackVisualState = struct {
    draw_ticks: u8 = 0,
    hide_ticks: u8 = 0,

    pub fn tick(self: *JetpackVisualState) void {
        if (self.draw_ticks > 0) self.draw_ticks -= 1;
        if (self.hide_ticks > 0) self.hide_ticks -= 1;
    }

    pub fn noteActiveChange(self: *JetpackVisualState, previous_active: bool, current_active: bool) void {
        if (previous_active == current_active) return;
        if (previous_active) self.hide_ticks = gameplay_assets.gameplay_jetpack_thrust_model_paths.len;
        if (current_active) self.draw_ticks = gameplay_assets.gameplay_jetpack_thrust_model_paths.len;
    }
};

pub const WeaponVisualState = struct {
    left_draw_ticks: u8 = 0,
    left_hide_ticks: u8 = 0,
    left_draw_selected_state: u8 = 0,
    left_hide_selected_state: u8 = 0,
    right_draw_ticks: u8 = 0,
    right_hide_ticks: u8 = 0,
    right_draw_selected_state: u8 = 0,
    right_hide_selected_state: u8 = 0,
    top_draw_ticks: u8 = 0,
    top_hide_ticks: u8 = 0,
    rocket_draw_ticks: u8 = 0,
    rocket_hide_ticks: u8 = 0,
    top_fire_ticks: u8 = 0,

    pub fn tick(self: *WeaponVisualState) void {
        if (self.left_draw_ticks > 0) self.left_draw_ticks -= 1;
        if (self.left_hide_ticks > 0) self.left_hide_ticks -= 1;
        if (self.right_draw_ticks > 0) self.right_draw_ticks -= 1;
        if (self.right_hide_ticks > 0) self.right_hide_ticks -= 1;
        if (self.top_draw_ticks > 0) self.top_draw_ticks -= 1;
        if (self.top_hide_ticks > 0) self.top_hide_ticks -= 1;
        if (self.rocket_draw_ticks > 0) self.rocket_draw_ticks -= 1;
        if (self.rocket_hide_ticks > 0) self.rocket_hide_ticks -= 1;
        if (self.top_fire_ticks > 0) self.top_fire_ticks -= 1;
    }

    pub fn noteWeaponChannelChange(self: *WeaponVisualState, previous_flags: u32, current_flags: u32) void {
        const previous = nativeWeaponChannelStates(previous_flags);
        const current = nativeWeaponChannelStates(current_flags);
        self.noteSideChannelChange(previous.left, current.left, true);
        self.noteSideChannelChange(previous.right, current.right, false);
        self.noteCenterChannelChange(previous.center, current.center);
    }

    fn noteSideChannelChange(self: *WeaponVisualState, previous: u8, current: u8, left_channel: bool) void {
        if (previous == current) return;
        const draw_ticks: *u8 = if (left_channel) &self.left_draw_ticks else &self.right_draw_ticks;
        const hide_ticks: *u8 = if (left_channel) &self.left_hide_ticks else &self.right_hide_ticks;
        const draw_selected_state: *u8 = if (left_channel) &self.left_draw_selected_state else &self.right_draw_selected_state;
        const hide_selected_state: *u8 = if (left_channel) &self.left_hide_selected_state else &self.right_hide_selected_state;
        if (previous != 0) {
            hide_ticks.* = sideWeaponDrawTickCount(previous);
            hide_selected_state.* = previous;
        }
        if (current != 0) {
            draw_ticks.* = sideWeaponDrawTickCount(current);
            draw_selected_state.* = current;
        }
    }

    fn noteCenterChannelChange(self: *WeaponVisualState, previous: u8, current: u8) void {
        if (previous == current) return;
        switch (previous) {
            1 => self.top_hide_ticks = @intCast(gameplay_assets.gameplay_blaster_top_draw_model_paths.len),
            3 => self.rocket_hide_ticks = @intCast(gameplay_assets.gameplay_rocket_launcher_draw_model_paths.len),
            else => {},
        }
        switch (current) {
            1 => self.top_draw_ticks = @intCast(gameplay_assets.gameplay_blaster_top_draw_model_paths.len),
            3 => self.rocket_draw_ticks = @intCast(gameplay_assets.gameplay_rocket_launcher_draw_model_paths.len),
            else => {},
        }
    }

    pub fn noteFire(self: *WeaponVisualState, movement_flags: u32) void {
        const channel_states = nativeWeaponChannelStates(movement_flags);
        if (channel_states.left != 0 and self.left_draw_ticks == 0) self.left_draw_ticks = 1;
        if (channel_states.right != 0 and self.right_draw_ticks == 0) self.right_draw_ticks = 1;
        switch (channel_states.center) {
            1 => self.top_fire_ticks = 3,
            3 => {
                if (self.rocket_draw_ticks == 0) self.rocket_draw_ticks = 1;
            },
            else => {},
        }
    }

    pub fn sideSelectedState(self: *const WeaponVisualState, current_selected_state: u8, left_channel: bool) u8 {
        if (current_selected_state != 0) return current_selected_state;
        const draw_ticks = if (left_channel) self.left_draw_ticks else self.right_draw_ticks;
        const hide_ticks = if (left_channel) self.left_hide_ticks else self.right_hide_ticks;
        const draw_selected_state = if (left_channel) self.left_draw_selected_state else self.right_draw_selected_state;
        const hide_selected_state = if (left_channel) self.left_hide_selected_state else self.right_hide_selected_state;
        if (draw_ticks > 0 and draw_selected_state != 0) return draw_selected_state;
        if (hide_ticks > 0 and hide_selected_state != 0) return hide_selected_state;
        return 0;
    }
};

fn sideWeaponDrawTickCount(state_value: u8) u8 {
    return switch (state_value) {
        1 => @intCast(@max(gameplay_assets.gameplay_blaster_left_draw_model_paths.len, gameplay_assets.gameplay_blaster_right_draw_model_paths.len)),
        2 => @intCast(@max(gameplay_assets.gameplay_laser_left_draw_model_paths.len, gameplay_assets.gameplay_laser_right_draw_model_paths.len)),
        else => @intCast(@max(
            @max(gameplay_assets.gameplay_blaster_left_draw_model_paths.len, gameplay_assets.gameplay_blaster_right_draw_model_paths.len),
            @max(gameplay_assets.gameplay_laser_left_draw_model_paths.len, gameplay_assets.gameplay_laser_right_draw_model_paths.len),
        )),
    };
}

test "weapon visual state keeps native side blaster and laser families distinct" {
    var visuals = WeaponVisualState{};

    visuals.noteWeaponChannelChange(0, 2);
    try std.testing.expectEqual(@as(u8, 1), visuals.left_draw_selected_state);
    try std.testing.expectEqual(@as(u8, 1), visuals.right_draw_selected_state);
    try std.testing.expectEqual(sideWeaponDrawTickCount(1), visuals.left_draw_ticks);
    try std.testing.expectEqual(sideWeaponDrawTickCount(1), visuals.right_draw_ticks);
    try std.testing.expectEqual(@as(u8, 1), visuals.sideSelectedState(1, true));
    try std.testing.expectEqual(@as(u8, 1), visuals.sideSelectedState(1, false));

    visuals = .{};
    visuals.noteWeaponChannelChange(0, 16);
    try std.testing.expectEqual(@as(u8, 2), visuals.left_draw_selected_state);
    try std.testing.expectEqual(@as(u8, 2), visuals.right_draw_selected_state);
    try std.testing.expectEqual(sideWeaponDrawTickCount(2), visuals.left_draw_ticks);
    try std.testing.expectEqual(sideWeaponDrawTickCount(2), visuals.right_draw_ticks);
    try std.testing.expectEqual(@as(u8, 2), visuals.sideSelectedState(2, true));
    try std.testing.expectEqual(@as(u8, 2), visuals.sideSelectedState(2, false));

    visuals = .{};
    visuals.noteWeaponChannelChange(2, 0);
    try std.testing.expectEqual(@as(u8, 1), visuals.left_hide_selected_state);
    try std.testing.expectEqual(@as(u8, 1), visuals.right_hide_selected_state);
    try std.testing.expectEqual(@as(u8, 1), visuals.sideSelectedState(0, true));
    try std.testing.expectEqual(@as(u8, 1), visuals.sideSelectedState(0, false));
}

test "native jetpack visual presentation follows the recovered 0.94 shutoff edge" {
    var gauge = jetpack.Gauge{};
    try std.testing.expect(!nativeJetpackVisualPresentationActive(gauge.thrust_visual_active));

    gauge.arm();
    gauge.progress = 0.25;
    try std.testing.expect(nativeJetpackVisualPresentationActive(gauge.thrust_visual_active));

    gauge.progress = gameplay_assets.native_jetpack_visual_shutoff_threshold;
    try std.testing.expect(nativeJetpackVisualPresentationActive(gauge.thrust_visual_active));

    gauge.update(false, false);
    try std.testing.expect(!nativeJetpackVisualPresentationActive(gauge.thrust_visual_active));
    try std.testing.expect(gauge.active);

    gauge.disarm();
    try std.testing.expect(!nativeJetpackVisualPresentationActive(gauge.thrust_visual_active));
}

test "jetpack visual state keeps native draw and hide legs around the shutoff edge" {
    var visuals = JetpackVisualState{};

    visuals.noteActiveChange(false, true);
    try std.testing.expectEqual(@as(u8, gameplay_assets.gameplay_jetpack_thrust_model_paths.len), visuals.draw_ticks);
    try std.testing.expectEqual(@as(u8, 0), visuals.hide_ticks);
    visuals.tick();
    try std.testing.expectEqual(@as(u8, gameplay_assets.gameplay_jetpack_thrust_model_paths.len - 1), visuals.draw_ticks);

    visuals.noteActiveChange(true, false);
    try std.testing.expectEqual(@as(u8, gameplay_assets.gameplay_jetpack_thrust_model_paths.len), visuals.hide_ticks);
    visuals.tick();
    try std.testing.expectEqual(@as(u8, gameplay_assets.gameplay_jetpack_thrust_model_paths.len - 1), visuals.hide_ticks);
}
