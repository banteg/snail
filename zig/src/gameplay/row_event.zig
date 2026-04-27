const std = @import("std");
const rl = @import("raylib");

pub const postal_completion_bonus_score: u32 = 50_000;

pub const display_stage_progress_step: f32 = 1.0 / 24.0;
pub const display_hold_progress_step: f32 = 1.0 / 60.0;
pub const display_final_delay_progress_step: f32 = 1.0 / 60.0;

pub const widget_local_x: f32 = 7.30000019;
pub const widget_local_y: f32 = 2.0;
pub const widget_local_z: f32 = 6.0;

pub const DisplayState = enum(u32) {
    inactive = 0,
    staging = 1,
    hold = 2,
    final_delivery = 3,
    bonus_prompt = 4,
    complete = 5,
    final_delivery_delay = 6,
};

pub const DisplayController = struct {
    state: DisplayState = .inactive,
    gate_18: u8 = 0,
    parcel_target_count: u32 = 0,
    bonus_enabled: bool = false,
    staged_parcel_count: u32 = 0,
    delivered_parcel_count: u32 = 0,
    progress: f32 = 0.0,
    progress_step: f32 = 0.0,
    widget_world_x: f32 = 0.0,
    widget_world_y: f32 = 0.0,
    widget_world_z: f32 = 0.0,
    bonus_blink_progress: f32 = 0.0,
    bonus_blink_step: f32 = 0.0,
    bonus_score: u32 = postal_completion_bonus_score,
    display_token: u32 = 0,

    pub fn configureForRun(self: *DisplayController, parcel_target: usize, bonus_enabled: bool) void {
        const delivered_parcel_count = self.delivered_parcel_count;
        const staged_parcel_count = self.staged_parcel_count;
        self.* = .{
            .parcel_target_count = @intCast(parcel_target),
            .bonus_enabled = bonus_enabled,
            .staged_parcel_count = staged_parcel_count,
            .delivered_parcel_count = delivered_parcel_count,
            .bonus_score = postal_completion_bonus_score,
            .bonus_blink_step = 1.0,
        };
    }

    pub fn reconfigureCompletion(self: *DisplayController, parcel_target: usize, bonus_enabled: bool) void {
        self.parcel_target_count = @intCast(parcel_target);
        self.bonus_enabled = bonus_enabled;
        self.bonus_score = postal_completion_bonus_score;
    }

    pub fn registeredParcelCount(self: DisplayController) u32 {
        return self.delivered_parcel_count;
    }

    pub fn deliveredCountText(self: DisplayController, buffer: *[2]u8) []const u8 {
        return formatDeliveredCount(buffer, self.delivered_parcel_count);
    }

    pub fn counterVisible(self: DisplayController, session_is_tutorial: bool) bool {
        return self.parcel_target_count != 0 and !session_is_tutorial;
    }

    pub fn widgetWorldPosition(self: DisplayController) rl.Vector3 {
        return .{
            .x = self.widget_world_x,
            .y = self.widget_world_y,
            .z = self.widget_world_z,
        };
    }

    pub fn bonusVisible(self: DisplayController) bool {
        if (!self.bonus_enabled) return false;
        return switch (self.state) {
            .final_delivery, .bonus_prompt, .complete => true,
            else => false,
        };
    }

    pub fn bonusBlinkAlpha(self: DisplayController) f32 {
        if (!self.bonusVisible()) return 0.0;
        const pulse = (@sin(self.bonus_blink_progress * std.math.tau) + 1.0) * 0.5;
        return 0.35 + (pulse * 0.65);
    }

    pub fn resetTransient(self: *DisplayController) void {
        self.state = .inactive;
        self.progress = 0.0;
        self.progress_step = 0.0;
        self.gate_18 = 0;
        self.display_token = 0;
        self.bonus_blink_progress = 0.0;
    }

    pub fn armStagingIfNeeded(self: *DisplayController, has_pending_stage: bool, has_active_delivery: bool) void {
        if (!has_pending_stage) return;
        if (has_active_delivery) return;
        switch (self.state) {
            .inactive => {
                self.state = .staging;
                self.progress = 0.0;
                self.progress_step = display_stage_progress_step;
            },
            .staging, .hold, .final_delivery, .bonus_prompt, .complete, .final_delivery_delay => {},
        }
    }

    pub fn armPromptGate(self: *DisplayController, accept_pressed: bool) void {
        if (!accept_pressed) return;
        self.gate_18 = 1;
    }

    pub fn stepProgress(self: *DisplayController) bool {
        self.progress = std.math.clamp(
            self.progress + self.progress_step,
            0.0,
            1.0,
        );
        return self.progress >= 1.0;
    }

    pub fn stepBonusPrompt(self: *DisplayController, completion_cell_active: bool) void {
        self.bonus_blink_progress += self.bonus_blink_step;
        if (self.bonus_blink_progress > 1.0) {
            self.bonus_blink_progress = 0.0;
        }
        if (completion_cell_active) {
            self.state = .complete;
        }
    }
};

pub fn formatDeliveredCount(buffer: *[2]u8, delivered_parcel_count: u32) []const u8 {
    // PORT(verified): `update_row_event_display` (0x404cf0) writes exactly two
    // ASCII bytes into widget B: a space-padded tens digit plus the ones digit.
    buffer[0] = if (delivered_parcel_count >= 10)
        @intCast(@divTrunc(delivered_parcel_count, 10) + '0')
    else
        ' ';
    buffer[1] = @intCast(@mod(delivered_parcel_count, 10) + '0');
    return buffer[0..];
}

test "row event delivered count text mirrors native widget bytes" {
    var buffer: [2]u8 = undefined;

    try std.testing.expectEqualStrings(" 0", formatDeliveredCount(&buffer, 0));
    try std.testing.expectEqualStrings(" 9", formatDeliveredCount(&buffer, 9));
    try std.testing.expectEqualStrings("10", formatDeliveredCount(&buffer, 10));
    try std.testing.expectEqualStrings("12", formatDeliveredCount(&buffer, 12));
}
