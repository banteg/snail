//! Lockstep replay oracle (the crimson-port differential pattern).
//!
//! Drives a headless Runner with a real Windows replay (fixtures in
//! tests/fixtures/replays) and compares the port's z trajectory per tick
//! against the recording's ghost-z lane — the original sim's own output
//! while that run was being recorded. The recorded lateral/flags lanes are
//! the inputs; z motion is simulated, so divergence measures how far the
//! port's motion model is from native.
//!
//! The tolerated divergence is a RATCHET: as the native-mirror campaign
//! collapses invented models, tighten `lockstep_tolerance_z` and extend
//! `lockstep_pinned_ticks` toward the full replay. Never loosen them to
//! make a regression pass — that inverts the oracle.

const std = @import("std");
const assets = @import("assets.zig");
const frontend = @import("frontend.zig");
const gameplay = @import("gameplay.zig");
const high_score = @import("high_score.zig");
const level = @import("level.zig");
const selected_replay = @import("app/selected_replay.zig");
const track = @import("track.zig");

const io = std.Options.debug_io;
const simulation_step_seconds: f32 = 1.0 / 60.0;

const OracleRun = struct {
    catalog: assets.Catalog,
    level_definition: level.Definition,
    preview: track.LoadedLevelPreview,
    runner: gameplay.Runner,
    replay: high_score.DecodedReplay,

    fn deinit(self: *OracleRun) void {
        self.replay.deinit();
        self.preview.deinit();
        self.level_definition.deinit();
        self.catalog.deinit();
    }
};

fn loadFixtureTables(allocator: std.mem.Allocator, tables: *high_score.Tables) !void {
    const fixture_paths = [_][]const u8{
        "tests/fixtures/replays/ScoreA.windows-2026-04-17.dat",
        "tests/fixtures/replays/ScoreB.windows-2026-04-17.dat",
        "tests/fixtures/replays/ScoreC.windows-2026-04-17.dat",
    };
    for (fixture_paths) |path| {
        const bytes = try std.Io.Dir.cwd().readFileAlloc(io, path, allocator, .limited(1 << 20));
        defer allocator.free(bytes);
        try high_score.loadBankBytes(allocator, bytes, tables);
    }
}

/// Stage a replay run the way app/level_loader.reloadLevel does for a
/// selected record: level from replay_level_index, build options from the
/// entry's recorded tuning, session mode + base rate from the bank.
/// Seam: runtime parcel configuration (run_tuning.configureRuntimeParcels)
/// is app-layer and not wired here — parcels affect score, not motion.
fn stageOracleRun(
    allocator: std.mem.Allocator,
    entry: *const high_score.Entry,
    mode: frontend.FrontendLevelMode,
) !OracleRun {
    var path_buffer: [64]u8 = undefined;
    const level_path = try frontend.frontendLevelPath(mode, entry.replay_level_index, &path_buffer);

    var catalog = try assets.Catalog.init(allocator, "artifacts/bin/SnailMail.dat");
    errdefer catalog.deinit();
    const level_entry = catalog.level_entries[catalog.findLevelIndex(level_path).?];
    var level_definition = try level.loadFromArchive(allocator, &catalog, level_entry);
    errdefer level_definition.deinit();

    var preview = try track.LoadedLevelPreview.loadWithOptions(allocator, &catalog, &level_definition, .{
        .load_models = false,
        .runtime_build_flags = entry.runtime_build_flags,
        .runtime_build_seed = entry.runtime_build_seed,
        .random_length_scalar_override = switch (mode) {
            .challenge => entry.challenge_difficulty_scalar,
            else => null,
        },
        .garbage_scalar_override = entry.garbage_scalar,
        .salt_scalar_override = entry.salt_scalar,
    });
    errdefer preview.deinit();

    var replay = try entry.decodeReplay(allocator);
    errdefer replay.deinit();

    var runner = gameplay.Runner.init(&preview);
    runner.configureSessionMode(switch (mode) {
        .postal => .postal,
        .challenge => .challenge,
        .time_trial => .time_trial,
        .tutorial => .debug,
    });
    runner.configureBaseSubgameRate(entry.replay_speed_scalar);

    return .{
        .catalog = catalog,
        .level_definition = level_definition,
        .preview = preview,
        .runner = runner,
        .replay = replay,
    };
}

const LockstepReport = struct {
    ticks_run: usize = 0,
    /// first tick where |port z - ghost z| exceeded the tolerance (null =
    /// the whole replay stayed within it)
    first_divergence_tick: ?usize = null,
    max_abs_dz: f32 = 0.0,
    max_abs_dz_tick: usize = 0,
    finished: bool = false,
};

fn runLockstep(run: *OracleRun, tolerance_z: f32, max_ticks: usize) LockstepReport {
    var report = LockstepReport{};
    const total = @min(run.replay.samples.len, max_ticks);
    while (report.ticks_run < total) {
        const directive = selected_replay.directiveForDecodedReplay(&run.replay, run.runner.replay_sample_index);
        run.runner.stepWithReplay(&run.preview, .{}, directive, simulation_step_seconds);
        const tick = report.ticks_run;
        report.ticks_run += 1;
        if (run.runner.finished) {
            report.finished = true;
            break;
        }
        const sample = run.replay.sampleAt(tick) orelse break;
        const ghost_z = sample.ghostWorldZ();
        const port_z = run.runner.playerWorldPosition(&run.preview).z;
        const dz = @abs(port_z - ghost_z);
        if (dz > report.max_abs_dz) {
            report.max_abs_dz = dz;
            report.max_abs_dz_tick = tick;
        }
        if (report.first_divergence_tick == null and dz > tolerance_z) {
            report.first_divergence_tick = tick;
        }
    }
    return report;
}

test "lockstep oracle: postal top run ratchet" {
    const allocator = std.testing.allocator;
    var tables = high_score.Tables.initDefault();
    defer tables.deinit(allocator);
    try loadFixtureTables(allocator, &tables);

    // postal[0]: 141030 points on ARCADE012, 5006 recorded ticks
    var run = try stageOracleRun(allocator, &tables.postal[0], .postal);
    defer run.deinit();

    const report = runLockstep(&run, 1.0, run.replay.samples.len);

    // the port consumes the whole replay without dying or finishing early
    try std.testing.expectEqual(run.replay.samples.len, report.ticks_run);
    try std.testing.expect(!report.finished);

    // RATCHET: tighten as the campaign collapses invented motion — never
    // loosen to pass. History:
    //   2026-06-12 v1: first_div(>1.0)=28, max_dz~917 (z model far behind)
    //   2026-06-12 v2: startup hold + native forward window (mode-
    //   independent clamp at completion_row_start, pre-integration order):
    //   first_div=144, start ramp in lockstep to ~0.001/tick
    //   2026-06-12 v3: terminal-segment position extension + native exhaust
    //   placement (the natural-exit +1.7 teleport removed): first_div=195
    //   2026-06-12 v4: exit-pending no longer arms at natural ends (native
    //   arms it only via the event-gated carryover arms), past-the-end
    //   re-begin guard, exit preserves live x: first_div=212
    //   2026-06-13 v5: containing-column cell sampling (the native
    //   trunc(x+4) convention via gridColumnAtWorldX at the live world x)
    //   carries the port through the t~204 gap natively: first_div=253.
    //   max_dz (~968 at the tail) is POST-divergence decoherence — once the
    //   runs structurally diverge, magnitude is noise; the primary ratchet
    //   is first_div, max_dz stays only as a runaway backstop
    //   2026-06-13 v6: the natural-exit +0.5 row-convention import fixed
    //   (commitAttachmentNaturalExit converts native world z into the
    //   half-shifted row_position space): first_div=254. Exit velocities
    //   now match native exactly; the remaining chain is the -0.117
    //   attachment-PHASE z offset (entry-side) which tips a marginal
    //   garbage clip at t~153 that native misses by under 0.117.
    const first_divergence = report.first_divergence_tick orelse run.replay.samples.len;
    try std.testing.expect(first_divergence >= 254);
    try std.testing.expect(report.max_abs_dz <= 1100.0);
}
