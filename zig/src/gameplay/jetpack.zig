//! Jetpack fuel gauge + warning band + update math.
//!
//! Native `update_jetpack_gauge` at player `+0x2750` mirrored here:
//! - 1/600 per-tick countdown
//! - 0.94 near-empty band
//! - runtime-cell `flags_b & 0x80` warning snap seeded from `JetPack=Off`
//! - fuel-out and 5-row end-of-course auto-shutoff
//! - recovered warning-intensity / pulse / wobble fields

const std = @import("std");

pub const tick_step: f32 = 0.0016666667;
pub const warning_threshold: f32 = 0.94;
pub const warning_phase_scale: f32 = 16.666668;
pub const auto_shutoff_margin_rows: f32 = 5.0;

pub const WarningBand = enum {
    idle,
    steady,
    near_empty,

    pub fn label(self: WarningBand) []const u8 {
        return switch (self) {
            .idle => "idle",
            .steady => "steady",
            .near_empty => "near_empty",
        };
    }
};

pub const Gauge = struct {
    active: bool = false,
    progress: f32 = 0.0,
    thrust_visual_active: bool = false,
    jet_particles_active: bool = false,
    jet_particle_generation: u32 = 0,
    jet_particle_shutdown_generation: u32 = 0,
    warning_intensity: f32 = 0.0,
    pulse_envelope: f32 = 0.0,
    warning_band: WarningBand = .idle,
    wobble_x: f32 = 0.0,
    wobble_y: f32 = 0.0,
    wobble_alpha: f32 = 0.0,

    pub fn arm(self: *Gauge) void {
        // PORT(verified): native `arm_jetpack_gauge` @ 0x43a980 returns immediately
        // unless state is idle, then sets state=1, zeroes progress and the three
        // wobble fields, and calls `set_snail_jetpack(1)` plus `initialize_jet_particles`.
        if (self.active) return;

        const particle_generation = self.jet_particle_generation +% 1;
        const particle_shutdown_generation = self.jet_particle_shutdown_generation;
        self.* = .{
            .active = true,
            .thrust_visual_active = true,
            .jet_particles_active = true,
            .jet_particle_generation = particle_generation,
            .jet_particle_shutdown_generation = particle_shutdown_generation,
            .warning_band = .steady,
        };
    }

    pub fn disarm(self: *Gauge) void {
        const particle_generation = self.jet_particle_generation;
        const particle_shutdown_generation = if (self.jet_particles_active)
            self.jet_particle_shutdown_generation +% 1
        else
            self.jet_particle_shutdown_generation;
        self.* = .{};
        self.jet_particle_generation = particle_generation;
        self.jet_particle_shutdown_generation = particle_shutdown_generation;
    }

    /// Mirrors `update_jetpack_gauge` @ 0x43a390 state 1. `forced_warning` is the
    /// recovered `runtimeFlagB80At` runtime-cell bit for the current sample.
    /// `row_near_end` mirrors the 5-row native auto-shutoff window.
    pub fn update(self: *Gauge, forced_warning: bool, row_near_end: bool) void {
        if (!self.active) return;

        const previous_progress = self.progress;
        self.progress += tick_step;
        // PORT(verified): native @ 0x43a3c9 disarms when fuel is spent or the
        // player's world-z is within 5 rows of the course end. `disarm` is the
        // port's state-zeroing equivalent, including particle shutdown.
        if (self.progress > 1.0 or row_near_end) {
            self.disarm();
            return;
        }

        var warning_phase: f32 = 1.0;
        self.warning_band = .steady;

        if (self.progress < 0.1) {
            warning_phase = self.progress * 10.0;
        } else if (self.progress <= warning_threshold) {
            if (forced_warning) {
                self.progress = warning_threshold;
                self.warning_band = .near_empty;
            }
            warning_phase = 1.0;
        } else {
            self.warning_band = .near_empty;
            warning_phase = std.math.clamp(
                (1.0 - self.progress) * warning_phase_scale,
                0.0,
                1.0,
            );
            // PORT(verified): native @ 0x43a441 fires this one-shot side effect only
            // on the 0.94 crossing. Gauge state stays live, but `set_snail_jetpack(0)`
            // hides the thrust channel and `uninit_jet_particles` kills the 15x2
            // sprite bank.
            if (previous_progress <= warning_threshold and self.progress > warning_threshold) {
                self.thrust_visual_active = false;
                if (self.jet_particles_active) {
                    self.jet_particles_active = false;
                    self.jet_particle_shutdown_generation +%= 1;
                }
            }
        }

        const warning_intensity = 1.0 - ((@cos(warning_phase * std.math.pi) + 1.0) * 0.5);
        self.warning_intensity = warning_intensity;
        self.pulse_envelope = warning_intensity;
        self.wobble_x = @sin(self.progress * 25.1327419) * warning_intensity * 0.25;
        self.wobble_y = ((@sin(self.progress * 37.6991119) * 0.25) + 1.0) * warning_intensity;
        self.wobble_alpha = 0.0;
    }

    pub fn fuelRemaining(self: Gauge) f32 {
        if (!self.active) return 0.0;
        return std.math.clamp(1.0 - self.progress, 0.0, 1.0);
    }
};

test "arm starts jet particles once and does not refill while active" {
    var gauge = Gauge{};

    gauge.arm();
    try std.testing.expect(gauge.active);
    try std.testing.expect(gauge.thrust_visual_active);
    try std.testing.expect(gauge.jet_particles_active);
    try std.testing.expectEqual(@as(u32, 1), gauge.jet_particle_generation);

    gauge.progress = 0.5;
    gauge.arm();
    try std.testing.expectApproxEqAbs(@as(f32, 0.5), gauge.progress, 0.0001);
    try std.testing.expectEqual(@as(u32, 1), gauge.jet_particle_generation);
}

test "near empty edge shuts down thrust particles without disarming gauge" {
    var gauge = Gauge{};
    gauge.arm();
    gauge.progress = warning_threshold;

    gauge.update(false, false);

    try std.testing.expect(gauge.active);
    try std.testing.expect(!gauge.thrust_visual_active);
    try std.testing.expect(!gauge.jet_particles_active);
    try std.testing.expectEqual(@as(u32, 1), gauge.jet_particle_shutdown_generation);
    try std.testing.expectEqual(WarningBand.near_empty, gauge.warning_band);
}

test "fuel out disarms gauge" {
    var gauge = Gauge{};
    gauge.arm();
    gauge.progress = 1.0;
    gauge.wobble_y = 1.0;

    gauge.update(false, false);

    try std.testing.expect(!gauge.active);
    try std.testing.expect(!gauge.thrust_visual_active);
    try std.testing.expect(!gauge.jet_particles_active);
    try std.testing.expectEqual(@as(u32, 1), gauge.jet_particle_shutdown_generation);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), gauge.wobble_y, 0.0001);
}
