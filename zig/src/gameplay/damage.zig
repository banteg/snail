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
const runner_state = @import("runner_state.zig");

const SnailSkinTransition = runner_state.SnailSkinTransition;

pub const gauge_pulse_step: f32 = 0.020833334;
pub const gauge_hit_flash_step: f32 = 0.033333335;
pub const warning_transition_step: f32 = 0.16666667;
pub const warning_drain_delta: f32 = -0.0016666667;
pub const warning_actor_step: f32 = 0.083333336;
pub const warning_actor_solid_alpha: f32 = 0.99900001;
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
    /// also arms the snail-skin transition via `change_snail_skin(1, 0.2f)`.
    pub fn applyDelta(self: *Controller, delta: f32, skin: *SnailSkinTransition) void {
        const damage_entry = self.gauge <= 0.0 and delta > 0.0;
        self.gauge = std.math.clamp(self.gauge + delta, 0.0, 1.0);
        if (damage_entry) {
            self.runtime.hit_flash_progress = self.runtime.hit_flash_step;
            // PORT(partial): native @ 0x44147e calls `change_snail_skin(1, 0.2f)`.
            // The voice + cutscene-dispatch side effects from the same branch are
            // wired via the existing damage_entry audio cue in main.zig.
            skin.change(.damage, 0.2);
        }
        if (self.gauge <= 0.0) {
            self.warning_state = .idle;
            self.runtime.warning_transition_progress = 0.0;
            self.runtime.skin_hold_ticks = 0;
            self.warning_actor.stop();
        }
    }

    /// Mirrors `update_damage_gauge` @ 0x440fd0: display fill lerp, pulse,
    /// hit-flash, warning state machine, state-2 drain delta + snail-skin
    /// refresh.
    pub fn updateController(self: *Controller, skin: *SnailSkinTransition) void {
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
                if (self.gauge >= 1.0) {
                    self.warning_state = .filling;
                    self.runtime.warning_transition_progress = 0.0;
                    self.runtime.warning_transition_step = warning_transition_step;
                    self.warning_actor.start();
                }
            },
            .filling => {
                self.runtime.warning_transition_progress +=
                    self.runtime.warning_transition_step;
                if (self.runtime.warning_transition_progress >= 1.0) {
                    self.warning_state = .draining;
                }
            },
            .draining => {
                // PORT(partial): native @ 0x441054 calls `change_snail_skin(1, 0.2f)`
                // each state-2 tick before applying the drain delta. The missing
                // 6x accelerated drain path remains a TODO (requires identifying
                // the writer for `*(+0x4301bc)`).
                skin.change(.damage, 0.2);
                self.applyDelta(warning_drain_delta, skin);
                self.runtime.skin_hold_ticks = 5;
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
        self.updateController(skin);
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
