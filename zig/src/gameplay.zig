const std = @import("std");
const rl = @import("raylib");
const assets = @import("assets.zig");
const level = @import("level.zig");
const segment = @import("segment.zig");
const track = @import("track.zig");

pub const RunnerInput = struct {
    lane_delta: i8 = 0,
    speed_delta_rows_per_second: f32 = 0.0,
    toggle_pause: bool = false,
    reset: bool = false,
};

pub const AttachmentHint = enum {
    none,
    probe,
    entry,

    pub fn label(self: AttachmentHint) []const u8 {
        return switch (self) {
            .none => "none",
            .probe => "probe",
            .entry => "entry",
        };
    }
};

pub const MovementMode = enum {
    track,
    attachment,

    pub fn label(self: MovementMode) []const u8 {
        return switch (self) {
            .track => "track",
            .attachment => "attachment",
        };
    }
};

pub const SessionMode = enum {
    debug,
    postal,
    challenge,
    time_trial,
    tutorial,

    pub fn label(self: SessionMode) []const u8 {
        return switch (self) {
            .debug => "debug",
            .postal => "postal",
            .challenge => "challenge",
            .time_trial => "time_trial",
            .tutorial => "tutorial",
        };
    }
};

pub const DeathCause = enum {
    damage,
    hazard,
    fall,

    pub fn label(self: DeathCause) []const u8 {
        return switch (self) {
            .damage => "damage",
            .hazard => "hazard",
            .fall => "fall",
        };
    }
};

pub const RunnerHandoff = union(enum) {
    none,
    completion,
    respawn: DeathCause,
    final_loss: DeathCause,
};

const RunnerPhase = union(enum) {
    active,
    completion_cutscene: u16,
    death_cutscene: struct {
        cause: DeathCause,
        ticks: u16,
    },
    death_resolution: struct {
        cause: DeathCause,
        final_loss: bool,
        ticks: u16,
    },
};

pub const RecentEvent = union(enum) {
    none,
    attachment_probe,
    attachment_begin,
    attachment_end,
    parcel: i32,
    trampoline,
    health_pickup,
    jetpack_pickup,
    garbage_hit,
    salt_hit,
    slug_hit,
    no_fall,
    jetpack_off,
    ring: segment.RingKind,

    pub fn label(self: RecentEvent) []const u8 {
        return switch (self) {
            .none => "none",
            .attachment_probe => "attachment_probe",
            .attachment_begin => "attachment_begin",
            .attachment_end => "attachment_end",
            .parcel => "parcel",
            .trampoline => "trampoline",
            .health_pickup => "health_pickup",
            .jetpack_pickup => "jetpack_pickup",
            .garbage_hit => "garbage_hit",
            .salt_hit => "salt_hit",
            .slug_hit => "slug_hit",
            .no_fall => "no_fall",
            .jetpack_off => "jetpack_off",
            .ring => |ring_kind| switch (ring_kind) {
                .none => "ring_none",
                .normal => "ring_normal",
                .powerup => "ring_powerup",
                .explode => "ring_explode",
                .slow => "ring_slow",
            },
        };
    }
};

pub const EncounterCounters = struct {
    attachments_begun: u32 = 0,
    attachments_completed: u32 = 0,
    parcels: u32 = 0,
    trampoline_rows: u32 = 0,
    health_pickups: u32 = 0,
    jetpack_pickups: u32 = 0,
    garbage_hits: u32 = 0,
    salt_hits: u32 = 0,
    slug_hits: u32 = 0,
    no_fall_rows: u32 = 0,
    jetpack_off_rows: u32 = 0,
    ring_normal: u32 = 0,
    ring_powerup: u32 = 0,
    ring_explode: u32 = 0,
    ring_slow: u32 = 0,
};

pub const ScoreTotals = struct {
    total: u32 = 0,
    ring_collect: u32 = 0,
    garbage_collision: u32 = 0,
    health_collect: u32 = 0,
    parcel_pickup: u32 = 0,
    parcel_register: u32 = 0,
    completion_bonus: u32 = 0,
};

pub const Stopwatch = struct {
    total_seconds: f32 = 0.0,
    minutes: u32 = 0,
    seconds: u32 = 0,
    centiseconds: u32 = 0,
    milliseconds: u32 = 0,
    fractional_seconds: f32 = 0.0,

    pub fn advance(self: *Stopwatch, tick_count: f32) void {
        const delta_seconds = tick_count * (1.0 / 60.0);
        self.total_seconds += delta_seconds;

        var fractional_seconds = self.fractional_seconds + delta_seconds;
        while (fractional_seconds >= 1.0) {
            fractional_seconds -= 1.0;
            self.seconds += 1;
            if (self.seconds >= 60) {
                self.seconds -= 60;
                self.minutes += 1;
            }
        }

        self.fractional_seconds = fractional_seconds;
        self.centiseconds = @intFromFloat(@floor(fractional_seconds * 100.0));
        self.milliseconds = @intFromFloat(@floor(fractional_seconds * 1000.0));
    }

    pub fn elapsedMillis(self: Stopwatch) u32 {
        return @intFromFloat(@round(self.total_seconds * 1000.0));
    }
};

pub const DamageWarningState = enum {
    idle,
    filling,
    draining,

    pub fn label(self: DamageWarningState) []const u8 {
        return switch (self) {
            .idle => "idle",
            .filling => "fill",
            .draining => "drain",
        };
    }
};

pub const JetpackWarningBand = enum {
    idle,
    steady,
    near_empty,

    pub fn label(self: JetpackWarningBand) []const u8 {
        return switch (self) {
            .idle => "idle",
            .steady => "steady",
            .near_empty => "near_empty",
        };
    }
};

pub const JetpackGauge = struct {
    active: bool = false,
    progress: f32 = 0.0,
    pulse_envelope: f32 = 0.0,
    warning_band: JetpackWarningBand = .idle,

    pub fn fuelRemaining(self: JetpackGauge) f32 {
        if (!self.active) return 0.0;
        return std.math.clamp(1.0 - self.progress, 0.0, 1.0);
    }
};

// PORT(partial): Windows now confirms the contact-damage controller is the separate
// player +0x3c4 block behind `apply_damage_gauge_delta` / `update_damage_gauge`,
// not the jetpack gauge at +0x2750. A separate +0.02 damage path from another pool
// is still unresolved, so only the identified gameplay hazards are modeled here.
const health_recover_delta: f32 = -0.5;
const garbage_damage_delta: f32 = 0.04;
const salt_damage_delta: f32 = 0.15;
const slug_damage_delta: f32 = 1.0;
const damage_warning_fill_step: f32 = 0.16666667;
const damage_warning_drain_delta: f32 = -0.0016666667;
const jetpack_gauge_tick_step: f32 = 0.0016666667;
const jetpack_warning_threshold: f32 = 0.94;
const jetpack_auto_shutoff_margin_rows: f32 = 5.0;
const jetpack_warning_phase_scale: f32 = 16.666668;
const score_life_threshold: u32 = 50_000;
const starting_visible_life_stock: u32 = 3;
const maximum_visible_life_stock: u32 = 9;
const completion_cutscene_duration_ticks: u16 = 72;
const death_cutscene_duration_ticks: u16 = 72;
const death_resolution_duration_ticks: u16 = 120;

const RowSample = struct {
    global_row: usize,
    traversable_bounds: track.LaneBounds,
    resolved_lane_index: usize,
    cell: u8,
    gameplay_cell: ?track.GameplayCellKind,
    runtime_tile_hint: ?u8,
    annotation: ?segment.Annotation,
    path_center_lane: ?f32,
    path_name: ?[]const u8,
};

pub const Runner = struct {
    session_mode: SessionMode = .debug,
    lane_index: usize = 0,
    resolved_lane_index: usize = 0,
    lane_center: f32 = 0.5,
    runtime_track_index: usize = 0,
    movement_progress: f32 = 0.0,
    movement_rate_scalar: f32 = 0.0,
    row_position: f32 = 0.0,
    speed_rows_per_second: f32 = 12.0,
    paused: bool = false,
    finished: bool = false,
    phase: RunnerPhase = .active,
    pending_handoff: RunnerHandoff = .none,
    tick_count: u64 = 0,
    stopwatch: Stopwatch = .{},
    movement_mode: MovementMode = .track,
    current_global_row: usize = 0,
    current_cell: u8 = ' ',
    current_annotation: ?segment.Annotation.Tag = null,
    current_gameplay_cell: ?track.GameplayCellKind = null,
    current_runtime_tile_hint: ?u8 = null,
    current_path_name: ?[]const u8 = null,
    attachment_hint: AttachmentHint = .none,
    attachment_path_name: ?[]const u8 = null,
    attachment_ticks: u64 = 0,
    jetpack: JetpackGauge = .{},
    path_center_lane: ?f32 = null,
    traversable_bounds: track.LaneBounds = .{ .min = 0, .max = 0 },
    recent_event: RecentEvent = .none,
    counters: EncounterCounters = .{},
    score: ScoreTotals = .{},
    visible_life_stock: u32 = starting_visible_life_stock,
    damage_gauge: f32 = 0.0,
    slug_hit_active: bool = false,
    damage_warning_state: DamageWarningState = .idle,
    damage_warning_fill: f32 = 0.0,
    completion_bonus_enabled: bool = false,
    parcel_target: usize = 0,
    completion_bonus_applied: bool = false,
    last_processed_row: ?usize = null,

    pub fn init(preview: *const track.LoadedLevelPreview) Runner {
        var runner = Runner{};
        runner.reset(preview);
        return runner;
    }

    pub fn reset(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        const completion_bonus_enabled = self.completion_bonus_enabled;
        const parcel_target = self.parcel_target;
        const session_mode = self.session_mode;
        self.* = .{
            .session_mode = session_mode,
            .speed_rows_per_second = 12.0,
            .completion_bonus_enabled = completion_bonus_enabled,
            .parcel_target = parcel_target,
            .visible_life_stock = starting_visible_life_stock,
        };
        self.syncRowPosition(preview);
        self.refreshSample(preview);
        self.last_processed_row = self.current_global_row;
    }

    pub fn step(self: *Runner, preview: *const track.LoadedLevelPreview, input: RunnerInput, delta_seconds: f32) void {
        if (input.reset) {
            self.reset(preview);
            return;
        }

        if (input.toggle_pause and self.acceptsGameplayInput()) {
            self.paused = !self.paused;
        }

        if (self.acceptsGameplayInput()) {
            self.speed_rows_per_second = std.math.clamp(
                self.speed_rows_per_second + input.speed_delta_rows_per_second,
                2.0,
                48.0,
            );
        }

        if (preview.total_rows == 0) {
            self.finished = true;
            self.pending_handoff = .completion;
            return;
        }

        if (self.acceptsGameplayInput() and self.movement_mode != .attachment) {
            self.applyLaneDelta(input.lane_delta);
        }

        if (!self.paused and self.acceptsGameplayInput()) {
            self.movement_rate_scalar = self.speed_rows_per_second * delta_seconds;
            self.advanceMovement(preview);
            self.tick_count += 1;
            self.stopwatch.advance(1.0);
        }

        if (!self.paused and self.phase == .active) {
            self.processVisitedRows(preview);
            self.updateJetpackGauge(preview);
            self.updateDamageWarning();
        } else if (!self.paused) {
            self.updatePhaseController();
        }
        self.endAttachmentIfNeeded(preview);
        self.refreshSample(preview);
        if (!self.paused and self.phase == .active) {
            self.updateFallEntry(preview);
        }
        if (self.movement_mode == .attachment and self.phase == .active) {
            self.attachment_ticks += 1;
        }
    }

    pub fn worldPosition(self: *const Runner, preview: *const track.LoadedLevelPreview, y: f32) rl.Vector3 {
        const floor_y = preview.sampleFloorHeightAtGridPosition(
            self.current_global_row,
            self.resolved_lane_index,
            self.row_position,
        ) orelse 0.0;
        return preview.worldPositionForLane(self.lane_center, self.row_position, floor_y + y);
    }

    pub fn annotationLabel(self: *const Runner) ?[]const u8 {
        const tag = self.current_annotation orelse return null;
        return switch (tag) {
            .path => "path",
            .ring => "ring",
            .parcel => "parcel",
            .model => "model",
            .jetpack_off => "jetpack_off",
            .no_fall => "no_fall",
        };
    }

    pub fn gameplayCellLabel(self: *const Runner) ?[]const u8 {
        const kind = self.current_gameplay_cell orelse return null;
        return kind.label();
    }

    pub fn recentEventLabel(self: *const Runner) []const u8 {
        return self.recent_event.label();
    }

    pub fn activePathName(self: *const Runner) ?[]const u8 {
        return self.attachment_path_name orelse self.current_path_name;
    }

    pub fn runtimeTileHint(self: *const Runner) ?u8 {
        return self.current_runtime_tile_hint;
    }

    pub fn damageWarningLabel(self: *const Runner) []const u8 {
        return self.damage_warning_state.label();
    }

    pub fn jetpackWarningLabel(self: *const Runner) []const u8 {
        return self.jetpack.warning_band.label();
    }

    pub fn jetpackFuelRemaining(self: *const Runner) f32 {
        return self.jetpack.fuelRemaining();
    }

    pub fn phaseLabel(self: *const Runner) []const u8 {
        return switch (self.phase) {
            .active => "active",
            .completion_cutscene => "completion_cutscene",
            .death_cutscene => "death_cutscene",
            .death_resolution => "death_resolution",
        };
    }

    pub fn phaseProgress(self: *const Runner) f32 {
        return switch (self.phase) {
            .active => 0.0,
            .completion_cutscene => |ticks| progressForTicks(ticks, completion_cutscene_duration_ticks),
            .death_cutscene => |state| progressForTicks(state.ticks, death_cutscene_duration_ticks),
            .death_resolution => |state| progressForTicks(state.ticks, death_resolution_duration_ticks),
        };
    }

    pub fn deathCause(self: *const Runner) ?DeathCause {
        return switch (self.phase) {
            .death_cutscene => |state| state.cause,
            .death_resolution => |state| state.cause,
            else => null,
        };
    }

    pub fn acceptsGameplayInput(self: *const Runner) bool {
        return self.phase == .active and !self.finished;
    }

    pub fn consumeHandoff(self: *Runner) RunnerHandoff {
        const handoff = self.pending_handoff;
        self.pending_handoff = .none;
        return handoff;
    }

    pub fn configureCompletionBonus(self: *Runner, parcel_target: usize, enabled: bool) void {
        self.parcel_target = parcel_target;
        self.completion_bonus_enabled = enabled;
    }

    pub fn configureSessionMode(self: *Runner, session_mode: SessionMode) void {
        self.session_mode = session_mode;
    }

    fn applyLaneDelta(self: *Runner, lane_delta: i8) void {
        if (lane_delta == 0) return;
        if (lane_delta < 0) {
            const amount: usize = @intCast(-lane_delta);
            self.lane_index = if (amount > self.lane_index) 0 else self.lane_index - amount;
            return;
        }
        self.lane_index += @intCast(lane_delta);
    }

    fn refreshSample(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (preview.total_rows == 0) {
            self.current_global_row = 0;
            self.current_cell = ' ';
            self.current_annotation = null;
            self.current_gameplay_cell = null;
            self.current_runtime_tile_hint = null;
            self.current_path_name = null;
            self.attachment_hint = .none;
            self.path_center_lane = null;
            self.traversable_bounds = .{ .min = 0, .max = 0 };
            self.resolved_lane_index = 0;
            self.lane_center = 0.5;
            self.runtime_track_index = 0;
            self.movement_progress = 0.0;
            self.row_position = 0.0;
            return;
        }

        const sample = self.sampleRow(preview, currentRowIndex(preview, self.row_position)) orelse {
            self.current_global_row = 0;
            self.current_cell = ' ';
            self.current_annotation = null;
            self.current_gameplay_cell = null;
            self.current_runtime_tile_hint = null;
            self.current_path_name = null;
            self.attachment_hint = .none;
            self.path_center_lane = null;
            self.resolved_lane_index = 0;
            return;
        };

        self.current_global_row = sample.global_row;
        self.traversable_bounds = sample.traversable_bounds;
        self.resolved_lane_index = sample.resolved_lane_index;
        self.current_cell = sample.cell;
        self.current_annotation = if (sample.annotation) |annotation| annotation.tag() else null;
        self.current_gameplay_cell = sample.gameplay_cell;
        self.current_runtime_tile_hint = sample.runtime_tile_hint;
        self.current_path_name = sample.path_name;
        self.path_center_lane = sample.path_center_lane;
        self.attachment_hint = if (sample.gameplay_cell) |kind|
            switch (kind) {
                .attachment_entry => .entry,
                .attachment_probe => .probe,
                else => returnAttachmentHint(sample.path_center_lane),
            }
        else
            returnAttachmentHint(sample.path_center_lane);
        self.lane_center = if (self.movement_mode == .attachment and sample.path_center_lane != null)
            sample.path_center_lane.?
        else
            @as(f32, @floatFromInt(sample.resolved_lane_index)) + 0.5;
    }

    fn advanceMovement(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (preview.total_rows == 0 or self.finished) return;

        const last_row = preview.total_rows - 1;
        const max_progress: f32 = 0.999;
        var remaining = self.movement_rate_scalar;

        while (remaining > 0.0) {
            const progress_limit: f32 = if (self.runtime_track_index >= last_row) max_progress else 1.0;
            const available_progress = progress_limit - self.movement_progress;
            if (available_progress <= 0.0) {
                break;
            }

            if (remaining < available_progress) {
                self.movement_progress += remaining;
                remaining = 0.0;
                break;
            }

            remaining -= available_progress;
            if (self.runtime_track_index >= last_row) {
                self.movement_progress = max_progress;
                self.beginCompletionCutscene();
                remaining = 0.0;
                break;
            }

            self.runtime_track_index += 1;
            self.movement_progress = 0.0;
        }

        self.syncRowPosition(preview);
    }

    fn syncRowPosition(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (preview.total_rows == 0) {
            self.row_position = 0.0;
            return;
        }

        const last_row = preview.total_rows - 1;
        if (self.runtime_track_index > last_row) {
            self.runtime_track_index = last_row;
            self.movement_progress = 0.999;
        }
        self.row_position = @as(f32, @floatFromInt(self.runtime_track_index)) + self.movement_progress;
    }

    fn sampleRow(self: *const Runner, preview: *const track.LoadedLevelPreview, global_row: usize) ?RowSample {
        const row_location = preview.locateRow(global_row) orelse return null;
        const traversable = preview.laneBoundsForRow(row_location);
        const desired_lane = std.math.clamp(self.lane_index, traversable.min, traversable.max);

        var resolved_lane_index = desired_lane;
        var path_center_lane: ?f32 = null;
        if (preview.pathBoundsForRow(row_location)) |path_bounds| {
            path_center_lane = (@as(f32, @floatFromInt(path_bounds.min + path_bounds.max)) * 0.5) + 0.5;
            if (self.movement_mode == .attachment) {
                resolved_lane_index = (path_bounds.min + path_bounds.max) / 2;
            }
        }

        const cell = row_location.row.cells[resolved_lane_index];
        const annotation = row_location.row.annotation;
        const runtime_tile_hint = preview.runtimeTileAt(global_row, resolved_lane_index) orelse track.confirmedRuntimeTileHint(cell);
        const gameplay_cell = if (runtime_tile_hint) |tile_type|
            track.runtimeGameplayCellKindForTile(tile_type, preview.runtime_build_flags) orelse track.gameplayCellKind(cell)
        else
            track.gameplayCellKind(cell);
        return .{
            .global_row = global_row,
            .traversable_bounds = traversable,
            .resolved_lane_index = resolved_lane_index,
            .cell = cell,
            .gameplay_cell = gameplay_cell,
            .runtime_tile_hint = runtime_tile_hint,
            .annotation = annotation,
            .path_center_lane = path_center_lane,
            .path_name = pathNameFromAnnotation(annotation),
        };
    }

    fn processVisitedRows(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (preview.total_rows == 0) return;
        const current_row = currentRowIndex(preview, self.row_position);
        const last_row = self.last_processed_row orelse {
            self.last_processed_row = current_row;
            return;
        };
        if (current_row < last_row) {
            self.last_processed_row = current_row;
            return;
        }

        var row = last_row + 1;
        while (row <= current_row) : (row += 1) {
            self.processRow(preview, row);
        }
        self.last_processed_row = current_row;
    }

    fn processRow(self: *Runner, preview: *const track.LoadedLevelPreview, global_row: usize) void {
        const sample = self.sampleRow(preview, global_row) orelse return;

        if (sample.annotation) |annotation| {
            switch (annotation) {
                .path => |path_name| {
                    if (self.movement_mode == .attachment) {
                        self.attachment_path_name = path_name;
                    }
                },
                .ring => |ring_kind| {
                    if (sample.gameplay_cell) |kind| {
                        if (kind == .ring) {
                            self.recordRing(ring_kind);
                        }
                    }
                },
                .parcel => |parcel| {
                    self.counters.parcels += 1;
                    self.recordScore(&self.score.parcel_pickup, 100);
                    // PORT(partial): until parcel-flight objects and `RegisterParcel` timing are ported,
                    // the current runner collapses parcel pickup and parcel registration onto the same row event.
                    self.recordScore(&self.score.parcel_register, 100);
                    self.maybeRecordCompletionBonus();
                    self.recent_event = .{ .parcel = parcel.id };
                },
                .jetpack_off => {
                    self.counters.jetpack_off_rows += 1;
                    self.disarmJetpackGauge();
                    self.recent_event = .jetpack_off;
                },
                .no_fall => {
                    self.counters.no_fall_rows += 1;
                    self.recent_event = .no_fall;
                },
                .model => {},
            }
        }

        const gameplay_cell = sample.gameplay_cell orelse return;
        switch (gameplay_cell) {
            .attachment_probe => {
                if (self.movement_mode == .track) {
                    self.recent_event = .attachment_probe;
                }
            },
            .attachment_entry => {
                if (self.movement_mode != .attachment) {
                    self.movement_mode = .attachment;
                    self.attachment_path_name = sample.path_name;
                    self.counters.attachments_begun += 1;
                    self.recent_event = .attachment_begin;
                }
            },
            .ring => {},
            .trampoline => {
                self.counters.trampoline_rows += 1;
                self.recent_event = .trampoline;
            },
            .health => {
                self.counters.health_pickups += 1;
                self.recordScore(&self.score.health_collect, 250);
                self.applyDamageGaugeDelta(health_recover_delta);
                self.recent_event = .health_pickup;
            },
            .jetpack => {
                self.counters.jetpack_pickups += 1;
                self.armJetpackGauge();
                self.recent_event = .jetpack_pickup;
            },
            .garbage => {
                self.counters.garbage_hits += 1;
                self.recordScore(&self.score.garbage_collision, 10);
                self.applyDamageGaugeDelta(garbage_damage_delta);
                self.recent_event = .garbage_hit;
            },
            .salt => {
                self.counters.salt_hits += 1;
                self.applyDamageGaugeDelta(salt_damage_delta);
                self.recent_event = .salt_hit;
            },
            .slug => {
                self.counters.slug_hits += 1;
                self.recent_event = .slug_hit;
                // PORT(partial): Windows first sends slug contact through a dedicated hit/fall
                // branch that clears attachment-follow and enters the death cutscene state; the
                // +1.0 damage-gauge delta appears only on repeated slug contact while already in
                // that state. The runner mirrors that split locally: first hit arms the slug-hit
                // latch and enters the scripted handoff, later contacts add the recovered damage.
                if (self.slug_hit_active) {
                    self.applyDamageGaugeDelta(1.0);
                    return;
                }
                self.slug_hit_active = true;
                self.beginDeathCutscene(.hazard);
            },
        }
    }

    fn endAttachmentIfNeeded(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (self.movement_mode != .attachment or preview.total_rows == 0) return;
        const sample = self.sampleRow(preview, currentRowIndex(preview, self.row_position)) orelse return;
        if (sample.path_center_lane != null) return;

        self.movement_mode = .track;
        self.attachment_path_name = null;
        self.counters.attachments_completed += 1;
        self.recent_event = .attachment_end;
    }

    fn recordRing(self: *Runner, ring_kind: segment.RingKind) void {
        switch (ring_kind) {
            .none => {},
            .normal => self.counters.ring_normal += 1,
            .powerup => self.counters.ring_powerup += 1,
            .explode => self.counters.ring_explode += 1,
            .slow => self.counters.ring_slow += 1,
        }
        if (ring_kind != .none) {
            self.recordScore(&self.score.ring_collect, 100);
            self.recent_event = .{ .ring = ring_kind };
        }
    }

    pub fn applyCompletionBonus(self: *Runner, parcel_target: usize) void {
        self.parcel_target = parcel_target;
        self.completion_bonus_enabled = true;
        self.maybeRecordCompletionBonus();
    }

    fn recordScore(self: *Runner, slot: *u32, points: u32) void {
        const previous_total = self.score.total;
        slot.* = std.math.add(u32, slot.*, points) catch std.math.maxInt(u32);
        self.score.total = std.math.add(u32, self.score.total, points) catch std.math.maxInt(u32);
        self.updateVisibleLifeStockFromScore(previous_total, self.score.total);
    }

    fn applyDamageGaugeDelta(self: *Runner, delta: f32) void {
        self.damage_gauge = std.math.clamp(self.damage_gauge + delta, 0.0, 1.0);
        if (self.damage_gauge <= 0.0) {
            self.damage_warning_state = .idle;
            self.damage_warning_fill = 0.0;
        }
    }

    fn maybeRecordCompletionBonus(self: *Runner) void {
        if (self.completion_bonus_applied or !self.completion_bonus_enabled) return;
        if (self.parcel_target == 0 or self.counters.parcels < self.parcel_target) return;

        self.completion_bonus_applied = true;
        self.recordScore(&self.score.completion_bonus, 100);
    }

    // PORT(partial): recovered from Android `cRDamageGuage::AI()`. Filling the gauge enters a
    // warning/fill phase, then a slow auto-drain phase, instead of killing the player directly.
    // This still omits the original game-flag gates, warning actor, and the separate fall-side path.
    fn updateDamageWarning(self: *Runner) void {
        switch (self.damage_warning_state) {
            .idle => {
                if (self.damage_gauge >= 1.0) {
                    self.damage_warning_state = .filling;
                    self.damage_warning_fill = 0.0;
                }
            },
            .filling => {
                self.damage_warning_fill = std.math.clamp(self.damage_warning_fill + damage_warning_fill_step, 0.0, 1.0);
                if (self.damage_warning_fill >= 0.999) {
                    self.damage_warning_state = .draining;
                }
            },
            .draining => {
                self.applyDamageGaugeDelta(damage_warning_drain_delta);
            },
        }
    }

    // PORT(partial): Windows `update_jetpack_gauge` at player +0x2750 is a separate
    // timer/warning/shutoff controller from the contact-damage gauge. The runner mirrors
    // the 1/600 countdown, the 0.94 near-empty band, and the route-end auto-shutoff, but
    // it still omits the original wobble offsets, lift/fall suppression, and runtime-cell
    // flag 0x80 forced-warning path because the current preview does not expose those flags.
    fn updateJetpackGauge(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (!self.jetpack.active) return;

        self.jetpack.progress += jetpack_gauge_tick_step;
        if (self.jetpack.progress > 1.0 or self.rowPositionNearRouteEnd(preview)) {
            self.disarmJetpackGauge();
            return;
        }

        if (self.jetpack.progress <= jetpack_warning_threshold) {
            self.jetpack.warning_band = .steady;
            self.jetpack.pulse_envelope = 1.0;
            return;
        }

        const warning_phase = std.math.clamp(
            (1.0 - self.jetpack.progress) * jetpack_warning_phase_scale,
            0.0,
            1.0,
        );
        self.jetpack.warning_band = .near_empty;
        self.jetpack.pulse_envelope = 1.0 - ((@cos(warning_phase * std.math.pi) + 1.0) * 0.5);
    }

    fn armJetpackGauge(self: *Runner) void {
        self.jetpack = .{
            .active = true,
            .warning_band = .steady,
            .pulse_envelope = 1.0,
        };
    }

    fn disarmJetpackGauge(self: *Runner) void {
        self.jetpack = .{};
    }

    // PORT(partial): Windows enters the death selector once Goldy's world Y falls below -7.0.
    // The runner still does not simulate vertical motion, so it uses a conservative proxy:
    // no sampled floor at the current lane, outside attachment-follow, without an active
    // jetpack, and without an authored `NoFall` annotation triggers the same direct fall-side
    // death-resolution path. The separate scripted death cutscene remains reserved for hit-side
    // hazards like slug contact.
    fn updateFallEntry(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        if (self.movement_mode == .attachment) return;
        if (self.jetpack.active) return;
        if (self.current_annotation == .no_fall) return;
        if (!rowHasAnyFloor(preview, self.current_global_row)) return;
        if (preview.sampleFloorHeightAtGridPosition(
            self.current_global_row,
            self.resolved_lane_index,
            self.row_position,
        ) != null) return;

        self.beginDeathResolution(.fall);
    }

    // PORT(partial): Windows `populate_runtime_track_cells_from_segments` seeds Goldy's
    // visible life stock to 3, and `cRSubGoldy::ScoreAdd` awards one more whenever total
    // score crosses another 50,000-point bucket, capped at 9. The runner now also mirrors
    // the current postal/tutorial respawn decrement path, but not the original reload flow.
    fn updateVisibleLifeStockFromScore(self: *Runner, previous_total: u32, current_total: u32) void {
        const previous_bucket = @divTrunc(previous_total, score_life_threshold);
        const current_bucket = @divTrunc(current_total, score_life_threshold);
        if (current_bucket <= previous_bucket) return;
        const crossed_buckets = current_bucket - previous_bucket;
        const updated_lives = std.math.add(u32, self.visible_life_stock, crossed_buckets) catch std.math.maxInt(u32);
        self.visible_life_stock = @min(maximum_visible_life_stock, updated_lives);
    }

    fn beginCompletionCutscene(self: *Runner) void {
        if (self.phase != .active) return;
        self.finished = true;
        self.phase = .{ .completion_cutscene = 0 };
    }

    fn beginDeathCutscene(self: *Runner, cause: DeathCause) void {
        if (self.phase != .active or self.finished) return;
        self.paused = false;
        self.movement_mode = .track;
        self.attachment_path_name = null;
        self.phase = .{
            .death_cutscene = .{
                .cause = cause,
                .ticks = 0,
            },
        };
    }

    fn beginDeathResolution(self: *Runner, cause: DeathCause) void {
        if (self.phase != .active or self.finished) return;
        self.paused = false;
        self.movement_mode = .track;
        self.attachment_path_name = null;
        self.phase = .{
            .death_resolution = .{
                .cause = cause,
                .final_loss = self.deathUsesFinalLoss(),
                .ticks = 0,
            },
        };
    }

    fn updatePhaseController(self: *Runner) void {
        switch (self.phase) {
            .active => {},
            .completion_cutscene => |ticks| {
                if (ticks + 1 >= completion_cutscene_duration_ticks) {
                    self.pending_handoff = .completion;
                    return;
                }
                self.phase = .{ .completion_cutscene = ticks + 1 };
            },
            .death_cutscene => |state| {
                if (state.ticks + 1 >= death_cutscene_duration_ticks) {
                    self.phase = .{
                        .death_resolution = .{
                            .cause = state.cause,
                            .final_loss = self.deathUsesFinalLoss(),
                            .ticks = 0,
                        },
                    };
                    return;
                }
                self.phase = .{
                    .death_cutscene = .{
                        .cause = state.cause,
                        .ticks = state.ticks + 1,
                    },
                };
            },
            .death_resolution => |state| {
                if (state.ticks + 1 < death_resolution_duration_ticks) {
                    self.phase = .{
                        .death_resolution = .{
                            .cause = state.cause,
                            .final_loss = state.final_loss,
                            .ticks = state.ticks + 1,
                        },
                    };
                    return;
                }

                if (state.final_loss) {
                    self.pending_handoff = .{ .final_loss = state.cause };
                    return;
                }

                if (self.session_mode == .postal and self.visible_life_stock > 0) {
                    self.visible_life_stock -= 1;
                }
                self.pending_handoff = .{ .respawn = state.cause };
            },
        }
    }

    fn deathUsesFinalLoss(self: *const Runner) bool {
        return switch (self.session_mode) {
            .postal => self.visible_life_stock == 0,
            .challenge, .time_trial => true,
            .tutorial, .debug => false,
        };
    }

    pub fn applyRespawn(self: *Runner, preview: *const track.LoadedLevelPreview) void {
        const session_mode = self.session_mode;
        const score = self.score;
        const visible_life_stock = self.visible_life_stock;
        const tick_count = self.tick_count;
        const stopwatch = self.stopwatch;
        self.reset(preview);
        self.session_mode = session_mode;
        self.score = score;
        self.visible_life_stock = visible_life_stock;
        self.tick_count = tick_count;
        self.stopwatch = stopwatch;
    }

    fn rowPositionNearRouteEnd(self: *const Runner, preview: *const track.LoadedLevelPreview) bool {
        if (preview.total_rows == 0) return false;
        const route_end_row = @as(f32, @floatFromInt(preview.total_rows - 1));
        return self.row_position > route_end_row - jetpack_auto_shutoff_margin_rows;
    }
};

fn currentRowIndex(preview: *const track.LoadedLevelPreview, row_position: f32) usize {
    return @intFromFloat(@floor(std.math.clamp(
        row_position,
        0.0,
        @as(f32, @floatFromInt(preview.total_rows - 1)),
    )));
}

fn returnAttachmentHint(path_center_lane: ?f32) AttachmentHint {
    return if (path_center_lane != null) .probe else .none;
}

fn pathNameFromAnnotation(annotation: ?segment.Annotation) ?[]const u8 {
    const value = annotation orelse return null;
    return switch (value) {
        .path => |path_name| path_name,
        else => null,
    };
}

fn progressForTicks(ticks: u16, total_ticks: u16) f32 {
    return std.math.clamp(
        @as(f32, @floatFromInt(ticks)) / @as(f32, @floatFromInt(total_ticks)),
        0.0,
        1.0,
    );
}

const TestFixture = struct {
    catalog: assets.Catalog,
    level_definition: level.Definition,
    preview: track.LoadedLevelPreview,

    fn load(level_path: []const u8) !TestFixture {
        var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
        errdefer catalog.deinit();

        const level_entry = catalog.level_entries[catalog.findLevelIndex(level_path).?];
        var level_definition = try level.loadFromArchive(std.testing.allocator, &catalog, level_entry);
        errdefer level_definition.deinit();

        var preview = try track.LoadedLevelPreview.loadWithOptions(
            std.testing.allocator,
            &catalog,
            &level_definition,
            .{ .load_models = false },
        );
        errdefer preview.deinit();

        return .{
            .catalog = catalog,
            .level_definition = level_definition,
            .preview = preview,
        };
    }

    fn deinit(self: *TestFixture) void {
        self.preview.deinit();
        self.level_definition.deinit();
        self.catalog.deinit();
    }
};

const RowTarget = struct {
    row: usize,
    lane: usize,
};

fn findFirstGameplayCell(preview: *const track.LoadedLevelPreview, kind: track.GameplayCellKind) ?RowTarget {
    for (0..preview.total_rows) |global_row| {
        const row_location = preview.locateRow(global_row) orelse continue;
        for (row_location.row.cells, 0..) |_, lane| {
            if (preview.gameplayCellSampleAt(global_row, lane)) |sample| {
                if (sample.kind == kind) {
                    return .{
                        .row = global_row,
                        .lane = lane,
                    };
                }
            }
        }
    }
    return null;
}

fn findFirstAnnotationTag(preview: *const track.LoadedLevelPreview, tag: segment.Annotation.Tag) ?RowTarget {
    for (0..preview.total_rows) |global_row| {
        const row_location = preview.locateRow(global_row) orelse continue;
        const annotation = row_location.row.annotation orelse continue;
        if (annotation.tag() != tag) continue;
        const bounds = preview.laneBoundsForRow(row_location);
        return .{
            .row = global_row,
            .lane = bounds.min,
        };
    }
    return null;
}

fn findFirstFloorGap(preview: *const track.LoadedLevelPreview, require_no_fall: bool) ?RowTarget {
    for (1..preview.total_rows) |global_row| {
        const row_location = preview.locateRow(global_row) orelse continue;
        const annotation_tag = if (row_location.row.annotation) |annotation| annotation.tag() else null;
        const wants_no_fall = annotation_tag == .no_fall;
        if (wants_no_fall != require_no_fall) continue;
        if (!rowHasAnyFloor(preview, global_row)) continue;

        const bounds = preview.laneBoundsForRow(row_location);
        for (bounds.min..bounds.max + 1) |lane| {
            const gameplay_kind = if (preview.gameplayCellSampleAt(global_row, lane)) |sample| sample.kind else null;
            if (gameplay_kind == .attachment_entry or gameplay_kind == .attachment_probe) continue;
            if (preview.sampleFloorHeightAtGridPosition(
                global_row,
                lane,
                @as(f32, @floatFromInt(global_row)) + 0.5,
            ) != null) continue;
            return .{
                .row = global_row,
                .lane = lane,
            };
        }
    }
    return null;
}

fn rowHasAnyFloor(preview: *const track.LoadedLevelPreview, global_row: usize) bool {
    const row_location = preview.locateRow(global_row) orelse return false;
    for (row_location.row.cells, 0..) |_, lane| {
        if (preview.sampleFloorHeightAtGridPosition(
            global_row,
            lane,
            @as(f32, @floatFromInt(global_row)) + 0.5,
        ) != null) return true;
    }
    return false;
}

fn primeRunnerBeforeRow(runner: *Runner, preview: *const track.LoadedLevelPreview, target: RowTarget) void {
    std.debug.assert(target.row > 0);
    runner.reset(preview);
    runner.lane_index = target.lane;
    runner.runtime_track_index = target.row - 1;
    runner.movement_progress = 0.99;
    runner.syncRowPosition(preview);
    runner.refreshSample(preview);
    runner.last_processed_row = target.row - 1;
}

test "runner advances deterministically over fixed time" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const level_entry = catalog.level_entries[catalog.findLevelIndex("LEVELS/TUTORIAL.TXT").?];
    var level_definition = try level.loadFromArchive(std.testing.allocator, &catalog, level_entry);
    defer level_definition.deinit();

    var preview = try track.LoadedLevelPreview.load(std.testing.allocator, &catalog, &level_definition);
    defer preview.deinit();

    var runner = Runner.init(&preview);
    for (0..120) |_| {
        runner.step(&preview, .{}, 1.0 / 60.0);
    }

    try std.testing.expectApproxEqAbs(@as(f32, 24.0), runner.row_position, 0.001);
    try std.testing.expectEqual(@as(usize, 24), runner.runtime_track_index);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.movement_progress, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.2), runner.movement_rate_scalar, 0.0001);
    try std.testing.expectEqual(@as(u64, 120), runner.tick_count);
}

test "runner keeps discrete track cursor and fractional movement progress" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const level_entry = catalog.level_entries[catalog.findLevelIndex("LEVELS/TUTORIAL.TXT").?];
    var level_definition = try level.loadFromArchive(std.testing.allocator, &catalog, level_entry);
    defer level_definition.deinit();

    var preview = try track.LoadedLevelPreview.load(std.testing.allocator, &catalog, &level_definition);
    defer preview.deinit();

    var runner = Runner.init(&preview);
    runner.step(&preview, .{}, 1.0 / 60.0);
    try std.testing.expectEqual(@as(usize, 0), runner.runtime_track_index);
    try std.testing.expectApproxEqAbs(@as(f32, 0.2), runner.movement_progress, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.2), runner.row_position, 0.0001);

    for (0..4) |_| {
        runner.step(&preview, .{}, 1.0 / 60.0);
    }

    try std.testing.expectEqual(@as(usize, 1), runner.runtime_track_index);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.movement_progress, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), runner.row_position, 0.0001);
}

test "runner discovers attachment hint rows in shipped corpus" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const level_entry = catalog.level_entries[catalog.findLevelIndex("LEVELS/ARCADE000.TXT").?];
    var level_definition = try level.loadFromArchive(std.testing.allocator, &catalog, level_entry);
    defer level_definition.deinit();

    var preview = try track.LoadedLevelPreview.load(std.testing.allocator, &catalog, &level_definition);
    defer preview.deinit();

    var runner = Runner.init(&preview);
    var found_attachment_hint = false;
    for (0..1024) |_| {
        runner.step(&preview, .{}, 1.0 / 60.0);
        if (runner.attachment_hint != .none) {
            found_attachment_hint = true;
            break;
        }
    }

    try std.testing.expect(found_attachment_hint);
}

test "runner records pickup and hazard encounters from shipped tutorial" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const step_seconds = 1.0 / 60.0;

    const health = findFirstGameplayCell(&fixture.preview, .health).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, health);
    runner.step(&fixture.preview, .{}, step_seconds);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.health_pickups);
    try std.testing.expectEqual(@as(u32, 250), runner.score.total);
    try std.testing.expectEqual(@as(u32, 250), runner.score.health_collect);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.damage_gauge, 0.0001);
    try std.testing.expectEqualStrings("health_pickup", runner.recentEventLabel());

    runner = Runner.init(&fixture.preview);
    const salt = findFirstGameplayCell(&fixture.preview, .salt).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, salt);
    runner.step(&fixture.preview, .{}, step_seconds);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.salt_hits);
    try std.testing.expectApproxEqAbs(salt_damage_delta, runner.damage_gauge, 0.0001);
    try std.testing.expectEqualStrings("salt_hit", runner.recentEventLabel());

    runner = Runner.init(&fixture.preview);
    const slug = findFirstGameplayCell(&fixture.preview, .slug).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, slug);
    runner.step(&fixture.preview, .{}, step_seconds);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.slug_hits);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.damage_gauge, 0.0001);
    try std.testing.expectEqualStrings("slug_hit", runner.recentEventLabel());
    try std.testing.expectEqualStrings("death_cutscene", runner.phaseLabel());

    runner = Runner.init(&fixture.preview);
    const garbage = findFirstGameplayCell(&fixture.preview, .garbage).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, garbage);
    runner.step(&fixture.preview, .{}, step_seconds);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.garbage_hits);
    try std.testing.expectEqual(@as(u32, 10), runner.score.total);
    try std.testing.expectEqual(@as(u32, 10), runner.score.garbage_collision);
    try std.testing.expectApproxEqAbs(garbage_damage_delta, runner.damage_gauge, 0.0001);
    try std.testing.expectEqualStrings("garbage_hit", runner.recentEventLabel());
}

test "repeated slug contact adds the recovered +1.0 damage delta" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const slug = findFirstGameplayCell(&fixture.preview, .slug).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, slug);

    runner.processRow(&fixture.preview, slug.row);
    try std.testing.expectEqualStrings("death_cutscene", runner.phaseLabel());
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.damage_gauge, 0.0001);

    runner.processRow(&fixture.preview, slug.row);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), runner.damage_gauge, 0.0001);
}

test "full damage enters warning fill and auto-drain" {
    var runner = Runner{};
    runner.damage_gauge = 1.0;

    runner.updateDamageWarning();
    try std.testing.expectEqual(DamageWarningState.filling, runner.damage_warning_state);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.damage_warning_fill, 0.0001);

    for (0..6) |_| {
        runner.updateDamageWarning();
    }
    try std.testing.expectEqual(DamageWarningState.draining, runner.damage_warning_state);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), runner.damage_warning_fill, 0.0001);

    const gauge_before_drain = runner.damage_gauge;
    runner.updateDamageWarning();
    try std.testing.expect(runner.damage_gauge < gauge_before_drain);
}

test "runner accumulates ring and parcel score totals from shipped levels" {
    var arcade_fixture = try TestFixture.load("LEVELS/ARCADE003.TXT");
    defer arcade_fixture.deinit();

    var runner = Runner{};
    const step_seconds = 1.0 / 60.0;

    runner.recordRing(.normal);
    try std.testing.expectEqual(@as(u32, 100), runner.score.total);
    try std.testing.expectEqual(@as(u32, 100), runner.score.ring_collect);

    runner = Runner.init(&arcade_fixture.preview);
    const parcel = findFirstAnnotationTag(&arcade_fixture.preview, .parcel).?;
    primeRunnerBeforeRow(&runner, &arcade_fixture.preview, parcel);
    runner.step(&arcade_fixture.preview, .{}, step_seconds);
    try std.testing.expectEqual(@as(u32, 200), runner.score.total);
    try std.testing.expectEqual(@as(u32, 100), runner.score.parcel_pickup);
    try std.testing.expectEqual(@as(u32, 100), runner.score.parcel_register);

    runner = Runner.init(&arcade_fixture.preview);
    runner.configureCompletionBonus(1, true);
    primeRunnerBeforeRow(&runner, &arcade_fixture.preview, parcel);
    runner.step(&arcade_fixture.preview, .{}, step_seconds);
    try std.testing.expectEqual(@as(u32, 300), runner.score.total);
    try std.testing.expectEqual(@as(u32, 100), runner.score.completion_bonus);
}

test "runner applies the completion bonus once" {
    var runner = Runner{};
    runner.counters.parcels = 3;

    runner.applyCompletionBonus(3);
    try std.testing.expectEqual(@as(u32, 100), runner.score.total);
    try std.testing.expectEqual(@as(u32, 100), runner.score.completion_bonus);

    runner.applyCompletionBonus(3);
    try std.testing.expectEqual(@as(u32, 100), runner.score.total);
}

test "runner seeds visible life stock at 3 and caps score-side awards at 9" {
    var runner = Runner{};

    runner.recordScore(&runner.score.ring_collect, 49_900);
    try std.testing.expectEqual(@as(u32, 49_900), runner.score.total);
    try std.testing.expectEqual(@as(u32, 3), runner.visible_life_stock);

    runner.recordScore(&runner.score.health_collect, 100);
    try std.testing.expectEqual(@as(u32, 50_000), runner.score.total);
    try std.testing.expectEqual(@as(u32, 4), runner.visible_life_stock);

    runner.recordScore(&runner.score.health_collect, 400_000);
    try std.testing.expectEqual(@as(u32, 450_000), runner.score.total);
    try std.testing.expectEqual(@as(u32, 9), runner.visible_life_stock);
}

test "stopwatch advances minutes seconds and subsecond counters at 60fps" {
    var stopwatch = Stopwatch{};
    stopwatch.advance(90.0);

    try std.testing.expectApproxEqAbs(@as(f32, 1.5), stopwatch.total_seconds, 0.0001);
    try std.testing.expectEqual(@as(u32, 0), stopwatch.minutes);
    try std.testing.expectEqual(@as(u32, 1), stopwatch.seconds);
    try std.testing.expectEqual(@as(u32, 50), stopwatch.centiseconds);
    try std.testing.expectEqual(@as(u32, 500), stopwatch.milliseconds);
    try std.testing.expectEqual(@as(u32, 1500), stopwatch.elapsedMillis());
}

test "postal death hands off respawn after the death controller finishes" {
    var fixture = try TestFixture.load("LEVELS/ARCADE001.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.configureSessionMode(.postal);
    runner.recordScore(&runner.score.ring_collect, 200);
    runner.runtime_track_index = 24;
    runner.movement_progress = 0.5;
    runner.syncRowPosition(&fixture.preview);
    runner.refreshSample(&fixture.preview);
    runner.beginDeathCutscene(.hazard);

    for (0..death_cutscene_duration_ticks + death_resolution_duration_ticks) |_| {
        runner.step(&fixture.preview, .{}, 1.0 / 60.0);
    }

    const handoff = runner.consumeHandoff();
    try std.testing.expectEqualStrings("death_resolution", runner.phaseLabel());
    try std.testing.expectEqual(DeathCause.hazard, handoff.respawn);
    try std.testing.expectEqual(@as(u32, 2), runner.visible_life_stock);
    try std.testing.expectEqual(@as(u32, 200), runner.score.total);
    try std.testing.expectApproxEqAbs(@as(f32, 24.5), runner.row_position, 0.0001);
}

test "applyRespawn preserves score timer and remaining lives while resetting movement" {
    var fixture = try TestFixture.load("LEVELS/ARCADE001.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.configureSessionMode(.postal);
    runner.recordScore(&runner.score.ring_collect, 200);
    runner.visible_life_stock = 2;
    runner.tick_count = 90;
    runner.stopwatch.advance(90.0);
    runner.runtime_track_index = 24;
    runner.movement_progress = 0.5;
    runner.syncRowPosition(&fixture.preview);
    runner.refreshSample(&fixture.preview);

    runner.applyRespawn(&fixture.preview);

    try std.testing.expectEqualStrings("active", runner.phaseLabel());
    try std.testing.expectEqual(@as(u32, 2), runner.visible_life_stock);
    try std.testing.expectEqual(@as(u32, 200), runner.score.total);
    try std.testing.expectEqual(@as(u64, 90), runner.tick_count);
    try std.testing.expectEqual(@as(u32, 1500), runner.stopwatch.elapsedMillis());
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.row_position, 0.0001);
    try std.testing.expectEqual(@as(u32, 0), runner.counters.parcels);
}

test "challenge death hands off final loss" {
    var fixture = try TestFixture.load("LEVELS/CHALLENGE000.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.configureSessionMode(.challenge);
    runner.beginDeathCutscene(.hazard);

    for (0..death_cutscene_duration_ticks + death_resolution_duration_ticks) |_| {
        runner.step(&fixture.preview, .{}, 1.0 / 60.0);
    }

    const handoff = runner.consumeHandoff();
    try std.testing.expectEqualStrings("death_resolution", runner.phaseLabel());
    try std.testing.expectEqual(DeathCause.hazard, handoff.final_loss);
}

test "death cutscene entry clears attachment-follow state" {
    var fixture = try TestFixture.load("LEVELS/CHALLENGE000.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.movement_mode = .attachment;
    runner.attachment_path_name = "SUPERTRAMP";
    runner.beginDeathCutscene(.hazard);

    try std.testing.expectEqual(MovementMode.track, runner.movement_mode);
    try std.testing.expect(runner.attachment_path_name == null);
    try std.testing.expectEqualStrings("death_cutscene", runner.phaseLabel());
}

test "runner completion reaches a handoff after the local cutscene" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.runtime_track_index = fixture.preview.total_rows - 1;
    runner.movement_progress = 0.95;
    runner.syncRowPosition(&fixture.preview);
    runner.refreshSample(&fixture.preview);
    runner.beginCompletionCutscene();

    try std.testing.expectEqualStrings("completion_cutscene", runner.phaseLabel());
    for (0..completion_cutscene_duration_ticks + 1) |_| {
        runner.step(&fixture.preview, .{}, 1.0 / 60.0);
    }

    try std.testing.expectEqual(RunnerHandoff.completion, runner.consumeHandoff());
}

test "runner records attachment entry and jetpack pickup from shipped levels" {
    var challenge_fixture = try TestFixture.load("LEVELS/CHALLENGE000.TXT");
    defer challenge_fixture.deinit();

    var runner = Runner.init(&challenge_fixture.preview);
    const step_seconds = 1.0 / 60.0;

    const attachment = findFirstGameplayCell(&challenge_fixture.preview, .attachment_entry).?;
    primeRunnerBeforeRow(&runner, &challenge_fixture.preview, attachment);
    runner.step(&challenge_fixture.preview, .{}, step_seconds);
    try std.testing.expectEqual(MovementMode.attachment, runner.movement_mode);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.attachments_begun);
    try std.testing.expectEqualStrings("attachment_begin", runner.recentEventLabel());
    try std.testing.expect(runner.activePathName() != null);

    var jetpack_fixture = try TestFixture.load("LEVELS/ARCADE007.TXT");
    defer jetpack_fixture.deinit();

    runner = Runner.init(&jetpack_fixture.preview);
    const jetpack = findFirstGameplayCell(&jetpack_fixture.preview, .jetpack).?;
    primeRunnerBeforeRow(&runner, &jetpack_fixture.preview, jetpack);
    runner.step(&jetpack_fixture.preview, .{}, step_seconds);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.jetpack_pickups);
    try std.testing.expect(runner.jetpack.active);
    try std.testing.expect(runner.jetpackFuelRemaining() > 0.99);
    try std.testing.expectEqual(JetpackWarningBand.steady, runner.jetpack.warning_band);
    try std.testing.expectEqualStrings("jetpack_pickup", runner.recentEventLabel());

    const jetpack_off = findFirstAnnotationTag(&jetpack_fixture.preview, .jetpack_off).?;
    primeRunnerBeforeRow(&runner, &jetpack_fixture.preview, jetpack_off);
    runner.step(&jetpack_fixture.preview, .{}, step_seconds);
    try std.testing.expectEqual(@as(u32, 1), runner.counters.jetpack_off_rows);
    try std.testing.expect(!runner.jetpack.active);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), runner.jetpackFuelRemaining(), 0.0001);
    try std.testing.expectEqualStrings("jetpack_off", runner.recentEventLabel());
}

test "jetpack gauge enters near-empty warning and auto-shuts off near route end" {
    var fixture = try TestFixture.load("LEVELS/ARCADE007.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    runner.armJetpackGauge();
    runner.jetpack.progress = 0.94;
    runner.updateJetpackGauge(&fixture.preview);
    try std.testing.expectEqual(JetpackWarningBand.near_empty, runner.jetpack.warning_band);
    try std.testing.expect(runner.jetpack.pulse_envelope > 0.0);

    runner.armJetpackGauge();
    runner.runtime_track_index = fixture.preview.total_rows - 3;
    runner.movement_progress = 0.0;
    runner.syncRowPosition(&fixture.preview);
    runner.refreshSample(&fixture.preview);
    runner.updateJetpackGauge(&fixture.preview);
    try std.testing.expect(!runner.jetpack.active);
}

test "fatal floor gaps enter direct death resolution" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const gap = findFirstFloorGap(&fixture.preview, false).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, gap);
    runner.step(&fixture.preview, .{}, 1.0 / 60.0);

    try std.testing.expectEqualStrings("death_resolution", runner.phaseLabel());
    try std.testing.expectEqual(DeathCause.fall, runner.deathCause().?);
}

test "authored no-fall rows suppress the fall death path" {
    var fixture = try TestFixture.load("LEVELS/ARCADE021.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const gap = findFirstFloorGap(&fixture.preview, true).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, gap);
    runner.step(&fixture.preview, .{}, 1.0 / 60.0);

    try std.testing.expectEqualStrings("active", runner.phaseLabel());
    try std.testing.expectEqualStrings("no_fall", runner.recentEventLabel());
}

test "active jetpack suppresses fall entry over a floor gap" {
    var fixture = try TestFixture.load("LEVELS/TUTORIAL.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const gap = findFirstFloorGap(&fixture.preview, false).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, gap);
    runner.armJetpackGauge();
    runner.step(&fixture.preview, .{}, 1.0 / 60.0);

    try std.testing.expectEqualStrings("active", runner.phaseLabel());
    try std.testing.expect(runner.jetpack.active);
}

test "runner records trampoline rows from shipped levels" {
    var fixture = try TestFixture.load("LEVELS/ARCADE021.TXT");
    defer fixture.deinit();

    var runner = Runner.init(&fixture.preview);
    const trampoline = findFirstGameplayCell(&fixture.preview, .trampoline).?;
    primeRunnerBeforeRow(&runner, &fixture.preview, trampoline);
    runner.step(&fixture.preview, .{}, 1.0 / 60.0);

    try std.testing.expectEqual(@as(u32, 1), runner.counters.trampoline_rows);
    try std.testing.expectEqualStrings("trampoline", runner.recentEventLabel());
    try std.testing.expectEqualStrings("trampoline", runner.gameplayCellLabel().?);
}
