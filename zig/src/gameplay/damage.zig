//! Damage gauge + damage-warning actor + snail-skin hit flash owner.
//!
//! Native references:
//! - `update_damage_gauge` @ 0x440fd0
//! - `apply_damage_gauge_delta` @ 0x4413f0
//! - `update_warning` @ 0x446f80 (actor) / `start_warning` @ 0x446f30 /
//!   `stop_warning` @ 0x446f50
//!
//! The whole subsystem is isolated from the rest of Runner here, aside from
//! `SnailSkinTransition` which the hit-flash / state-2 drain branches poke.

const std = @import("std");
const presentation = @import("presentation.zig");

const SnailSkinTransition = presentation.SnailSkinTransition;

pub const gauge_pulse_step: f32 = 0.020833334;
pub const gauge_hit_flash_step: f32 = 0.033333335;
pub const warning_transition_step: f32 = 0.16666667;
pub const warning_drain_delta: f32 = -0.0016666667;
pub const warning_accelerated_drain_delta: f32 = -0.0066666668;
pub const warning_actor_step: f32 = 0.083333336;
// PORT(verified): native `update_warning` writes `*(widget + 520) = 0.999000013f` on the
// solid-state branch (`artifacts/ida/functions/00446f80-update_warning.c:14`,
// literal DWORD `0x3F7FBE77`). The difference from fully opaque is visually tiny,
// but keep the model exact for audit-ability.
pub const warning_actor_solid_alpha: f32 = 0.999000013;
pub const gauge_display_lerp: f32 = 0.2;

pub const WarningState = enum {
    idle,
    filling,
    draining,

    pub fn label(self: WarningState) []const u8 {
        return switch (self) {
            .idle => "idle",
            .filling => "fill",
            .draining => "drain",
        };
    }
};

pub const WarningActorState = enum(u8) {
    hidden = 0,
    solid = 1,
    fade_cycle = 2,
};

pub const Runtime = struct {
    display_fill: f32 = 0.0,
    pulse_progress: f32 = 0.0,
    pulse_step: f32 = gauge_pulse_step,
    hit_flash_progress: f32 = 0.0,
    hit_flash_step: f32 = gauge_hit_flash_step,
    warning_transition_progress: f32 = 0.0,
    warning_transition_step: f32 = warning_transition_step,
    skin_hold_ticks: u8 = 0,
};

/// Per-frame native global gates consumed by `update_damage_gauge`.
///
/// The original function reads these from scattered `Game` offsets. Keep them
/// explicit here so callers can wire concrete producers as we recover them,
/// instead of baking the old scaffold assumptions into the controller.
pub const UpdateContext = struct {
    /// `Game+0x4300b4` sign bit: blocks unforced damage-gauge deltas.
    unforced_delta_blocked: bool = false,
    /// `Game+0x42ff60 == 1`: blocks unforced negative state-2 deltas.
    negative_drain_delta_blocked: bool = false,
    /// `Game+0x74621`: suspends controller math and `update_warning`.
    suspended: bool = false,
    /// `Game+0x430199`: blocks state-0 full-gauge warning startup.
    warning_start_blocked: bool = false,
    /// `Game+0x4301bc`: blocks fresh startup, fast-forwards state 1, and
    /// applies the extra unforced drain in state 2.
    accelerated_drain_gate: bool = false,
    /// Native checks `Game+0x42fde8 == 0.49f` before entering/exiting drain.
    drain_transition_allowed: bool = true,
    /// `Game+0x4301c0 > 0`.
    drain_exit_gate_a: bool = false,
    /// `Game+0x42fe08 > 0`.
    drain_exit_gate_b: bool = false,
    /// `Game+0x434064 != 0`.
    drain_exit_gate_c: bool = false,
};

pub const WarningActor = struct {
    state: WarningActorState = .hidden,
    progress: f32 = 0.0,
    step: f32 = warning_actor_step,
    alpha: f32 = 0.0,
    sample_generation: u8 = 0,

    pub fn start(self: *WarningActor) void {
        self.state = .fade_cycle;
        self.progress = 1.0;
        self.alpha = 0.0;
    }

    pub fn stop(self: *WarningActor) void {
        self.* = .{};
    }

    pub fn tick(self: *WarningActor) void {
        switch (self.state) {
            .hidden => {},
            .solid => {
                self.alpha = warning_actor_solid_alpha;
                const next_progress = self.progress + self.step;
                self.progress = next_progress;
                if (next_progress > 1.0) {
                    self.progress = 0.0;
                    self.state = .fade_cycle;
                }
            },
            .fade_cycle => {
                if (self.progress >= 0.5) {
                    self.alpha = 0.0;
                } else {
                    self.alpha = 1.0 - (self.progress * 2.0);
                }
                const next_progress = self.progress + self.step;
                self.progress = next_progress;
                if (next_progress > 1.0) {
                    self.progress = 0.0;
                    self.state = .solid;
                    self.sample_generation +%= 1;
                }
            },
        }
    }
};

/// Complete damage subsystem owner. Mirrors native `Player+0x3c4`
/// (damage-gauge controller), the `WarningActor` border-sprite driver at
/// `+0x3bbb58`, and the slug-hit first-contact latch.
pub const Controller = struct {
    gauge: f32 = 0.0,
    runtime: Runtime = .{},
    warning_state: WarningState = .idle,
    warning_actor: WarningActor = .{},
    slug_hit_active: bool = false,

    /// Mirrors `apply_damage_gauge_delta` @ 0x4413f0. The hit-flash lane
    /// arms the snail-skin transition via `change_snail_skin(1, 0.2f)`.
    ///
    /// Native's voice-gated cutscene-animation dispatch
    /// (`artifacts/ida/functions/004413f0-apply_damage_gauge_delta.c:25-28`)
    /// only fires when the `damage_entry` voice returns zero (busy/failed)
    /// and the ouch fallback takes over; the port wires that dispatch from
    /// `main.zig`'s voice handler which is the only layer that knows whether
    /// the voice actually played.
    pub fn applyDelta(self: *Controller, delta: f32, skin: *SnailSkinTransition) void {
        self.applyDeltaNative(delta, skin, false);
    }

    pub fn applyDeltaNative(
        self: *Controller,
        delta: f32,
        skin: *SnailSkinTransition,
        force: bool,
    ) void {
        self.applyDeltaNativeWithContext(delta, skin, force, .{});
    }

    pub fn applyDeltaNativeWithContext(
        self: *Controller,
        delta: f32,
        skin: *SnailSkinTransition,
        force: bool,
        context: UpdateContext,
    ) void {
        if (!force and context.unforced_delta_blocked) return;
        if (self.warning_state == .draining) {
            if (delta > 0.0) return;
            if (!force and delta < 0.0 and context.negative_drain_delta_blocked) return;
        }

        const damage_entry = self.gauge <= 0.0 and delta > 0.0;
        self.gauge = std.math.clamp(self.gauge + delta, 0.0, 1.0);
        if (damage_entry) {
            self.runtime.hit_flash_progress = self.runtime.hit_flash_step;
            // PORT(verified): `change_snail_skin(1, 0.2f)` on damage entry
            // (`004413f0-apply_damage_gauge_delta.c:16`).
            skin.change(.damage, 0.2);
        }
    }

    /// Mirrors `update_damage_gauge` @ 0x440fd0: display fill lerp, pulse,
    /// hit-flash, warning state machine, state-2 drain delta + snail-skin
    /// refresh.
    pub fn updateController(self: *Controller, skin: *SnailSkinTransition) void {
        self.updateControllerWithContext(skin, .{});
    }

    pub fn updateControllerWithContext(
        self: *Controller,
        skin: *SnailSkinTransition,
        context: UpdateContext,
    ) void {
        if (context.suspended) return;

        self.runtime.display_fill +=
            (self.gauge - self.runtime.display_fill) * gauge_display_lerp;
        if (self.runtime.hit_flash_progress > 0.0) {
            self.runtime.hit_flash_progress += self.runtime.hit_flash_step;
            if (self.runtime.hit_flash_progress > 1.0) {
                self.runtime.hit_flash_progress = 0.0;
            }
        }

        switch (self.warning_state) {
            .idle => {
                if (self.gauge >= 1.0 and
                    !context.warning_start_blocked and
                    !context.accelerated_drain_gate)
                {
                    self.warning_state = .filling;
                    self.runtime.warning_transition_progress = 0.0;
                    self.runtime.warning_transition_step = warning_transition_step;
                    self.warning_actor.start();
                }
            },
            .filling => {
                if (context.accelerated_drain_gate) {
                    self.runtime.warning_transition_progress = 1.0;
                }
                self.runtime.warning_transition_progress +=
                    self.runtime.warning_transition_step;
                if (self.runtime.warning_transition_progress >= 1.0 and
                    context.drain_transition_allowed)
                {
                    self.warning_state = .draining;
                }
            },
            .draining => {
                skin.change(.damage, 0.2);
                self.applyDeltaNativeWithContext(warning_drain_delta, skin, true, context);
                if (context.accelerated_drain_gate) {
                    self.applyDeltaNativeWithContext(warning_accelerated_drain_delta, skin, false, context);
                }
                self.runtime.skin_hold_ticks = 5;

                if ((self.gauge <= 0.0 and context.drain_transition_allowed) or
                    context.drain_exit_gate_a or
                    context.drain_exit_gate_b or
                    context.drain_exit_gate_c)
                {
                    self.warning_state = .idle;
                    self.runtime.warning_transition_progress = 0.0;
                    self.runtime.skin_hold_ticks = 0;
                    self.warning_actor.stop();
                }
            },
        }

        if (self.warning_state == .idle and self.gauge <= 0.0) {
            self.warning_actor.stop();
        }

        self.runtime.pulse_progress += self.runtime.pulse_step;
        if (self.runtime.pulse_progress > 1.0) {
            self.runtime.pulse_progress -= 1.0;
        }
    }

    /// Orchestrates the full damage subsystem per tick: controller update then
    /// warning-actor tick. Called from Runner.step.
    pub fn update(self: *Controller, skin: *SnailSkinTransition) void {
        self.updateWithContext(skin, .{});
    }

    pub fn updateWithContext(
        self: *Controller,
        skin: *SnailSkinTransition,
        context: UpdateContext,
    ) void {
        self.updateControllerWithContext(skin, context);
        if (context.suspended) return;
        self.warning_actor.tick();
    }

    pub fn overlayAlpha(self: *const Controller) f32 {
        const fill_ratio = std.math.clamp(self.runtime.display_fill, 0.0, 1.0);
        if (fill_ratio <= 0.89999998 and self.warning_state == .idle) return 0.0;

        var overlay_envelope: f32 = 1.0;
        if (fill_ratio <= 0.89999998) {
            if (fill_ratio >= 0.1) return 0.0;
            overlay_envelope = fill_ratio * 10.0;
        } else if (self.warning_state == .idle) {
            overlay_envelope = (fill_ratio - 0.89999998) * 10.0;
        }

        const phase = self.runtime.pulse_progress * std.math.tau;
        return overlay_envelope -
            (((@sin(phase) + 1.0) * 0.5) * overlay_envelope * 0.5);
    }

    pub fn actorAlpha(self: *const Controller) f32 {
        return std.math.clamp(self.warning_actor.alpha, 0.0, 1.0);
    }

    pub fn displayFill(self: *const Controller) f32 {
        return std.math.clamp(self.runtime.display_fill, 0.0, 1.0);
    }

    pub fn warningLabel(self: *const Controller) []const u8 {
        return self.warning_state.label();
    }
};

test "damage delta gate mirrors native draining state" {
    var controller = Controller{ .gauge = 0.5, .warning_state = .draining };
    var skin = SnailSkinTransition{};

    controller.applyDelta(0.15, &skin);
    try std.testing.expectApproxEqAbs(@as(f32, 0.5), controller.gauge, 0.0001);
    try std.testing.expect(!skin.active);

    controller.applyDeltaNative(warning_drain_delta, &skin, true);
    try std.testing.expectApproxEqAbs(@as(f32, 0.5) + warning_drain_delta, controller.gauge, 0.0001);
}

test "damage delta honors native global force gates" {
    var controller = Controller{ .gauge = 0.5 };
    var skin = SnailSkinTransition{};

    controller.applyDeltaNativeWithContext(0.15, &skin, false, .{ .unforced_delta_blocked = true });
    try std.testing.expectApproxEqAbs(@as(f32, 0.5), controller.gauge, 0.0001);

    controller.applyDeltaNativeWithContext(0.15, &skin, true, .{ .unforced_delta_blocked = true });
    try std.testing.expectApproxEqAbs(@as(f32, 0.65), controller.gauge, 0.0001);

    controller.warning_state = .draining;
    controller.applyDeltaNativeWithContext(warning_accelerated_drain_delta, &skin, false, .{ .negative_drain_delta_blocked = true });
    try std.testing.expectApproxEqAbs(@as(f32, 0.65), controller.gauge, 0.0001);
}

test "damage warning start and drain transition honor native gates" {
    var controller = Controller{ .gauge = 1.0 };
    var skin = SnailSkinTransition{};

    controller.updateWithContext(&skin, .{ .warning_start_blocked = true });
    try std.testing.expectEqual(WarningState.idle, controller.warning_state);
    try std.testing.expectEqual(WarningActorState.hidden, controller.warning_actor.state);

    controller.updateWithContext(&skin, .{ .accelerated_drain_gate = true });
    try std.testing.expectEqual(WarningState.idle, controller.warning_state);

    controller.update(&skin);
    try std.testing.expectEqual(WarningState.filling, controller.warning_state);

    controller.runtime.warning_transition_progress = 1.0;
    controller.updateWithContext(&skin, .{ .drain_transition_allowed = false });
    try std.testing.expectEqual(WarningState.filling, controller.warning_state);

    controller.update(&skin);
    try std.testing.expectEqual(WarningState.draining, controller.warning_state);
}

test "damage drain uses native accelerated and exit gates" {
    var controller = Controller{ .gauge = 1.0, .warning_state = .draining };
    var skin = SnailSkinTransition{};

    controller.updateControllerWithContext(&skin, .{ .accelerated_drain_gate = true });
    try std.testing.expectApproxEqAbs(
        @as(f32, 1.0) + warning_drain_delta + warning_accelerated_drain_delta,
        controller.gauge,
        0.0001,
    );
    try std.testing.expectEqual(WarningState.draining, controller.warning_state);

    controller.gauge = 0.001;
    controller.updateControllerWithContext(&skin, .{ .drain_transition_allowed = false });
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), controller.gauge, 0.0001);
    try std.testing.expectEqual(WarningState.draining, controller.warning_state);

    controller.updateControllerWithContext(&skin, .{ .drain_exit_gate_a = true });
    try std.testing.expectEqual(WarningState.idle, controller.warning_state);
    try std.testing.expectEqual(WarningActorState.hidden, controller.warning_actor.state);
}

test "damage suspend gate freezes controller and warning actor" {
    var controller = Controller{
        .gauge = 1.0,
        .runtime = .{ .display_fill = 0.25, .hit_flash_progress = 0.2, .pulse_progress = 0.5 },
        .warning_actor = .{ .state = .fade_cycle, .progress = 0.25, .alpha = 0.5 },
    };
    var skin = SnailSkinTransition{};

    controller.updateWithContext(&skin, .{ .suspended = true });
    try std.testing.expectApproxEqAbs(@as(f32, 0.25), controller.runtime.display_fill, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.2), controller.runtime.hit_flash_progress, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.5), controller.runtime.pulse_progress, 0.0001);
    try std.testing.expectEqual(WarningState.idle, controller.warning_state);
    try std.testing.expectEqual(WarningActorState.fade_cycle, controller.warning_actor.state);
    try std.testing.expectApproxEqAbs(@as(f32, 0.25), controller.warning_actor.progress, 0.0001);
}
