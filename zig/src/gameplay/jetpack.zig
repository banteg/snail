//! Jetpack fuel gauge + warning band + update math.
//!
//! Native `update_jetpack_gauge` at player `+0x2750` mirrored here:
//! - 1/600 per-tick countdown
//! - 0.94 near-empty band
//! - runtime-cell `flags_b & 0x80` warning snap seeded from `JetPack=Off`
//! - 5-row end-of-course warning-math skip (state stays live)
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
    warning_intensity: f32 = 0.0,
    pulse_envelope: f32 = 0.0,
    warning_band: WarningBand = .idle,
    wobble_x: f32 = 0.0,
    wobble_y: f32 = 0.0,
    wobble_alpha: f32 = 0.0,

    pub fn arm(self: *Gauge) void {
        // PORT(verified): native `arm_jetpack_gauge` @ 0x43a980 sets state=1, zeroes
        // progress and the three wobble fields, and calls `set_snail_jetpack(1)` plus
        // `initialize_jet_particles`. The pulse envelope is not written here; native
        // only populates it from `warning_intensity` during the first update tick.
        self.* = .{
            .active = true,
            .warning_band = .steady,
        };
    }

    pub fn disarm(self: *Gauge) void {
        self.* = .{};
    }

    /// Mirrors `update_jetpack_gauge` @ 0x43a390 state 1. `forced_warning` is the
    /// recovered `runtimeFlagB80At` runtime-cell bit for the current sample.
    /// `row_near_end` short-circuits the warning math for the 5-row auto-shutoff
    /// window; the gauge stays active.
    pub fn update(self: *Gauge, forced_warning: bool, row_near_end: bool) void {
        if (!self.active) return;

        self.progress += tick_step;
        // PORT(verified): native @ 0x43a3c9 skips the warning-band math when sum > 1.0
        // or when the player's world-z is within 5 rows of the course end, but the
        // state stays active — the gauge does not disarm here.
        if (self.progress > 1.0 or row_near_end) return;

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
            // PORT(verified): native @ 0x43a441 fires a one-shot
            // `set_snail_jetpack(0)` + `uninit_jet_particles` when previous progress
            // was <= 0.94 and current progress is > 0.94. Every observable side
            // effect is already covered by the Zig port's parallel scaffold:
            //   * sfx 0x10 (deactivate) fires via `nativeJetpackSoundCues.deactivate`
            //     on exactly this edge (see `gameplay/audio_cues.zig:141-150`).
            //   * thrust-cone mesh swap back to baseline is driven by
            //     `nativeJetpackVisualPresentationActive(runner)`, so crossing the
            //     edge already hides the thrust mesh via `GameplayJetpackVisualState`.
            //   * `uninit_jet_particles` targets a 15x2 sprite column pool the port
            //     does not own; there is nothing to tear down.
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
