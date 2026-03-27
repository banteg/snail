const std = @import("std");
const rl = @import("raylib");
const assets = @import("assets.zig");
const attachment_builders = @import("attachment_builders.zig");
const archive = @import("archive.zig");
const level = @import("level.zig");
const segment = @import("segment.zig");
const x2 = @import("x2.zig");

const LoadedModelAsset = struct {
    path: []const u8,
    loaded: x2.Uploaded,

    fn deinit(self: *LoadedModelAsset, allocator: std.mem.Allocator) void {
        self.loaded.deinit();
        allocator.free(self.path);
    }
};

const PlacedModel = struct {
    asset_index: usize,
    segment_index: usize,
    row_index: usize,
    offset: segment.Vec3,
};

pub const LaneBounds = struct {
    min: usize,
    max: usize,
};

pub const RowLocation = struct {
    global_row: usize,
    segment_index: usize,
    row_index: usize,
    row: segment.Row,
};

pub const GameplayCellKind = enum {
    attachment_probe,
    attachment_entry,
    ring,
    trampoline,
    slug,
    garbage,
    salt,
    health,
    jetpack,

    pub fn label(self: GameplayCellKind) []const u8 {
        return switch (self) {
            .attachment_probe => "attachment_probe",
            .attachment_entry => "attachment_entry",
            .ring => "ring",
            .trampoline => "trampoline",
            .slug => "slug",
            .garbage => "garbage",
            .salt => "salt",
            .health => "health",
            .jetpack => "jetpack",
        };
    }
};

pub fn confirmedRuntimeTileHint(cell: u8) ?u8 {
    return switch (cell) {
        '.' => 0x01,
        '_' => 0x0f,
        '|' => 0x0e,
        '(' => 0x16,
        '-' => 0x15,
        'p' => 0x1d,
        'P' => 0x1e,
        '$' => 0x17,
        '&' => 0x22,
        'J' => 0x19,
        'M' => 0x12,
        'R' => 0x23,
        's' => 0x21,
        else => null,
    };
}

pub fn isFloorCacheRuntimeTileFamily(tile_type: u8) bool {
    return switch (tile_type) {
        0x0f, 0x10, 0x12, 0x13, 0x17, 0x18, 0x19, 0x1a => true,
        else => false,
    };
}

pub fn isRampRuntimeTileFamily(tile_type: u8) bool {
    return switch (tile_type) {
        0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d => true,
        else => false,
    };
}

pub fn isSlideRuntimeTileFamily(tile_type: u8) bool {
    return switch (tile_type) {
        0x01, 0x14, 0x15, 0x1b, 0x21, 0x22 => true,
        else => false,
    };
}

pub fn isOpenNeighborRuntimeTileFamily(tile_type: u8) bool {
    return switch (tile_type) {
        0x00, 0x0e, 0x1c, 0x1d, 0x23 => true,
        else => false,
    };
}

pub fn sampleFloorHeightForRuntimeTile(tile_type: u8, world_z: f32, special_floor_height: ?f32) ?f32 {
    const row_fraction = world_z - @floor(world_z);
    return switch (tile_type) {
        0x01, 0x0e, 0x0f => 0.0,
        0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x0b, 0x0c, 0x0d => row_fraction * 0.4,
        0x08, 0x09, 0x0a => (row_fraction * 0.4) + 0.5,
        0x16 => special_floor_height,
        else => null,
    };
}

pub fn specialFloorHeightForShippedRuntimeTile(tile_type: u8) ?f32 {
    return switch (tile_type) {
        // The track builder seeds trampoline-family tile 0x16 from the cell's +0x14 slot.
        // In the shipped gameplay branch we have recovered so far, that slot is forced to -3.0.
        0x16 => -3.0,
        else => null,
    };
}

// PORT(verified): `set_subgame_features` picks distinct runtime-flag presets by mode:
// postal/challenge `0x00f5cfff`, time-trial `0x0075cfff`, tutorial `0x00e4cfff`.
pub const postalChallengeRuntimeBuildFlags: u32 = 0x00f5cfff;
pub const timeTrialRuntimeBuildFlags: u32 = 0x0075cfff;
pub const tutorialRuntimeBuildFlags: u32 = 0x00e4cfff;
pub const defaultRuntimeBuildFlags: u32 = postalChallengeRuntimeBuildFlags;
pub const runtime_row_flag_no_fall: u32 = 0x0000_0100;
pub const runtime_row_flag_ring_none: u32 = 0x0000_0200;
pub const runtime_row_flag_ring_normal: u32 = 0x0000_0400;
pub const runtime_row_flag_ring_explode: u32 = 0x0000_0800;
pub const runtime_row_flag_ring_slow: u32 = 0x0000_1000;
pub const runtime_row_flag_ring_powerup: u32 = 0x0000_2000;
pub const runtime_row_flag_jetpack_off: u32 = 0x0000_8000;
pub const runtime_build_flag_movement_fire: u32 = 0x0040_0000;
pub const ramp_special_ring_forward_row_offset: usize = 6;
pub const ramp_default_ring_forward_row_offset: usize = 6;
pub const ramp_explode_ring_forward_row_offset: usize = 17;
// PORT(verified): Windows runtime traces consistently report `track_row_start = 31`
// on fresh gameplay starts, and `update_cameraman` uses the same game-side scalar for
// its early intro-pitch / vertical-lift blend threshold.
pub const defaultRuntimeActiveRowStart: usize = 31;

// PORT(fallback): these are candidate overlays for trace-confirmed ambient hazard families.
// They are not the original gameplay-side spawn timing inside update_subgame.
const runtime_spawn_hint_garbage_fallback: u8 = 0x01;
const runtime_spawn_hint_salt_fallback: u8 = 0x02;

pub const FallbackHazardCandidateCounts = struct {
    garbage: usize = 0,
    salt: usize = 0,
};

pub const GameplayCellSample = struct {
    global_row: usize,
    lane_index: usize,
    cell: u8,
    kind: GameplayCellKind,
    annotation: ?segment.Annotation.Tag = null,
    marked: bool = false,
};

pub const LoadOptions = struct {
    load_models: bool = true,
    runtime_build_flags: u32 = defaultRuntimeBuildFlags,
    runtime_build_seed: u32 = 0,
    runtime_active_row_start: usize = defaultRuntimeActiveRowStart,
    runtime_active_row_end: ?usize = null,
    course_end_threshold_override: ?f32 = null,
    random_length_scalar_override: ?f32 = null,
    garbage_scalar_override: ?f32 = null,
    salt_scalar_override: ?f32 = null,
};

fn appendLoadedLevelSegment(
    allocator: std.mem.Allocator,
    catalog: *const assets.Catalog,
    segments: []segment.Definition,
    logical_segment_indices: []?usize,
    row_offsets: []usize,
    loaded_count: *usize,
    total_rows: *usize,
    max_width: *usize,
    segment_path: []const u8,
    logical_segment_index: ?usize,
    load_models: bool,
    model_assets_list: *std.ArrayList(LoadedModelAsset),
    model_asset_index_by_path: *archive.CaseInsensitiveStringHashMap(usize),
    placed_models_list: *std.ArrayList(PlacedModel),
) !void {
    const index = loaded_count.*;
    row_offsets[index] = total_rows.*;
    logical_segment_indices[index] = logical_segment_index;

    var path_buffer: [512]u8 = undefined;
    const archive_path = try std.fmt.bufPrint(&path_buffer, "SEGMENTS/{s}", .{segment_path});
    const entry = catalog.dat.entryByPath(archive_path) orelse return error.SegmentEntryMissing;
    segments[index] = try segment.loadFromArchive(allocator, catalog, entry);
    loaded_count.* = index + 1;

    total_rows.* += segments[index].height;
    max_width.* = @max(max_width.*, segments[index].width);

    for (segments[index].rows, 0..) |row, row_index| {
        if (!load_models) continue;

        const annotation = row.annotation orelse continue;
        const model_annotation = switch (annotation) {
            .model => |model| model,
            else => continue,
        };

        const archive_model_path = try resolveSegmentModelArchivePath(allocator, model_annotation.name);
        errdefer allocator.free(archive_model_path);

        const asset_index = if (model_asset_index_by_path.get(archive_model_path)) |existing_index| blk: {
            allocator.free(archive_model_path);
            break :blk existing_index;
        } else blk: {
            const model_entry = catalog.dat.entryByPath(archive_model_path) orelse {
                allocator.free(archive_model_path);
                continue;
            };

            const loaded_model = try x2.Uploaded.loadFromArchive(allocator, catalog, model_entry, true);
            try model_assets_list.append(allocator, .{
                .path = archive_model_path,
                .loaded = loaded_model,
            });
            const new_index = model_assets_list.items.len - 1;
            try model_asset_index_by_path.put(archive_model_path, new_index);
            break :blk new_index;
        };

        try placed_models_list.append(allocator, .{
            .asset_index = asset_index,
            .segment_index = index,
            .row_index = row_index,
            .offset = model_annotation.offset,
        });
    }
}

pub const LoadedLevelRenderCachePreview = struct {
    warn_surface_grid: []bool,
    surface_swap_grid: []bool,
    flag_b40_grid: []bool,
    edge_masks: []u8,

    fn deinit(self: *LoadedLevelRenderCachePreview, allocator: std.mem.Allocator) void {
        allocator.free(self.edge_masks);
        allocator.free(self.flag_b40_grid);
        allocator.free(self.surface_swap_grid);
        allocator.free(self.warn_surface_grid);
    }

    fn warnSurfaceAt(self: *const LoadedLevelRenderCachePreview, total_rows: usize, max_width: usize, global_row: usize, lane_index: usize) bool {
        if (global_row >= total_rows or max_width == 0 or lane_index >= max_width) return false;
        return self.warn_surface_grid[runtimeTileIndex(max_width, global_row, lane_index)];
    }

    fn surfaceSwapAt(self: *const LoadedLevelRenderCachePreview, total_rows: usize, max_width: usize, global_row: usize, lane_index: usize) bool {
        if (global_row >= total_rows or max_width == 0 or lane_index >= max_width) return false;
        return self.surface_swap_grid[runtimeTileIndex(max_width, global_row, lane_index)];
    }

    fn flagB40At(self: *const LoadedLevelRenderCachePreview, total_rows: usize, max_width: usize, global_row: usize, lane_index: usize) bool {
        if (global_row >= total_rows or max_width == 0 or lane_index >= max_width) return false;
        return self.flag_b40_grid[runtimeTileIndex(max_width, global_row, lane_index)];
    }

    fn edgeMaskAt(self: *const LoadedLevelRenderCachePreview, total_rows: usize, max_width: usize, global_row: usize, lane_index: usize) ?u8 {
        if (global_row >= total_rows or max_width == 0 or lane_index >= max_width) return null;
        return self.edge_masks[runtimeTileIndex(max_width, global_row, lane_index)];
    }
};

pub const LoadedLevelPreview = struct {
    allocator: std.mem.Allocator,
    segments: []segment.Definition,
    segment_logical_indices: []?usize,
    row_offsets: []usize,
    attachment_scaffold: attachment_builders.Scaffold,
    model_assets: []LoadedModelAsset,
    placed_models: []PlacedModel,
    runtime_build_flags: u32,
    runtime_build_seed: u32,
    runtime_build_final_random_state: u32,
    runtime_active_row_start: usize,
    runtime_active_row_end: usize,
    course_end_threshold: f32,
    garbage_scalar: f32,
    salt_scalar: f32,
    parcel_target_count: usize,
    runtime_tiles: []u8,
    runtime_row_flags: []u32,
    runtime_row_ring_speeds: []f32,
    runtime_ring_effect_kinds: []u8,
    runtime_warning_zone_grid: []bool,
    render_cache: LoadedLevelRenderCachePreview,
    runtime_flag_b01_grid: []bool,
    runtime_flag_b80_grid: []bool,
    runtime_spawn_hints: []u8,
    total_rows: usize,
    max_width: usize,

    pub fn load(
        allocator: std.mem.Allocator,
        catalog: *const assets.Catalog,
        level_definition: *const level.Definition,
    ) !LoadedLevelPreview {
        return loadWithOptions(allocator, catalog, level_definition, .{});
    }

    pub fn loadStandaloneSegment(
        allocator: std.mem.Allocator,
        catalog: *const assets.Catalog,
        entry: archive.Entry,
    ) !LoadedLevelPreview {
        return loadStandaloneSegmentWithOptions(allocator, catalog, entry, .{});
    }

    pub fn loadWithOptions(
        allocator: std.mem.Allocator,
        catalog: *const assets.Catalog,
        level_definition: *const level.Definition,
        options: LoadOptions,
    ) !LoadedLevelPreview {
        const segment_count =
            level_definition.first_segments.len +
            level_definition.segments.len +
            level_definition.last_segments.len;
        const segments = try allocator.alloc(segment.Definition, segment_count);
        errdefer allocator.free(segments);

        const segment_logical_indices = try allocator.alloc(?usize, segment_count);
        errdefer allocator.free(segment_logical_indices);

        const row_offsets = try allocator.alloc(usize, segment_count);
        errdefer allocator.free(row_offsets);

        var model_assets_list: std.ArrayList(LoadedModelAsset) = .empty;
        defer model_assets_list.deinit(allocator);
        errdefer {
            for (model_assets_list.items) |*asset| {
                asset.deinit(allocator);
            }
        }
        var model_asset_index_by_path = archive.CaseInsensitiveStringHashMap(usize).init(allocator);
        defer model_asset_index_by_path.deinit();

        var placed_models_list: std.ArrayList(PlacedModel) = .empty;
        defer placed_models_list.deinit(allocator);

        var loaded_count: usize = 0;
        errdefer {
            for (segments[0..loaded_count]) |*loaded_segment| {
                loaded_segment.deinit();
            }
        }

        var total_rows: usize = 0;
        var max_width: usize = 0;
        for (level_definition.first_segments) |segment_path| {
            try appendLoadedLevelSegment(
                allocator,
                catalog,
                segments,
                segment_logical_indices,
                row_offsets,
                &loaded_count,
                &total_rows,
                &max_width,
                segment_path,
                null,
                options.load_models,
                &model_assets_list,
                &model_asset_index_by_path,
                &placed_models_list,
            );
        }
        for (level_definition.segments, 0..) |segment_entry, logical_index| {
            try appendLoadedLevelSegment(
                allocator,
                catalog,
                segments,
                segment_logical_indices,
                row_offsets,
                &loaded_count,
                &total_rows,
                &max_width,
                segment_entry.path,
                logical_index,
                options.load_models,
                &model_assets_list,
                &model_asset_index_by_path,
                &placed_models_list,
            );
        }
        for (level_definition.last_segments) |segment_path| {
            try appendLoadedLevelSegment(
                allocator,
                catalog,
                segments,
                segment_logical_indices,
                row_offsets,
                &loaded_count,
                &total_rows,
                &max_width,
                segment_path,
                null,
                options.load_models,
                &model_assets_list,
                &model_asset_index_by_path,
                &placed_models_list,
            );
        }

        const runtime_build_flags = options.runtime_build_flags;
        const runtime_active_row_start = options.runtime_active_row_start;
        const runtime_active_row_end = options.runtime_active_row_end orelse total_rows;
        const course_end_threshold = options.course_end_threshold_override orelse
            nativeCourseEndThresholdForLevel(level_definition, row_offsets, total_rows, options.random_length_scalar_override);
        const runtime_build_config: RuntimeBuildConfig = .{
            .build_flags = runtime_build_flags,
            .build_seed = options.runtime_build_seed,
            .active_row_start = runtime_active_row_start,
            .active_row_end = runtime_active_row_end,
        };
        const runtime_tiles = try buildRuntimeTileGrid(
            allocator,
            segments,
            row_offsets,
            total_rows,
            max_width,
            runtime_build_config,
        );
        errdefer allocator.free(runtime_tiles);
        const runtime_row_flags = try buildRuntimeRowFlags(
            allocator,
            segments,
            row_offsets,
            total_rows,
        );
        errdefer allocator.free(runtime_row_flags);
        const runtime_row_ring_speeds = try buildRuntimeRowRingSpeeds(
            allocator,
            segments,
            row_offsets,
            total_rows,
        );
        errdefer allocator.free(runtime_row_ring_speeds);
        const runtime_ring_effect_kinds = try buildRuntimeRingEffectGrid(
            allocator,
            runtime_tiles,
            runtime_row_flags,
            total_rows,
            max_width,
            runtime_build_flags,
        );
        errdefer allocator.free(runtime_ring_effect_kinds);
        const runtime_warning_zone_grid = try buildRuntimeWarningZoneGrid(
            allocator,
            runtime_tiles,
            total_rows,
            max_width,
        );
        errdefer allocator.free(runtime_warning_zone_grid);
        const render_cache_warn_surface_grid = try buildRenderCacheWarnSurfaceGrid(
            allocator,
            runtime_tiles,
            total_rows,
            max_width,
        );
        errdefer allocator.free(render_cache_warn_surface_grid);
        const render_cache_surface_swap_grid = try buildRenderCacheSurfaceSwapGrid(
            allocator,
            runtime_tiles,
            render_cache_warn_surface_grid,
            total_rows,
            max_width,
        );
        errdefer allocator.free(render_cache_surface_swap_grid);
        const runtime_flag_b40_grid = try buildRuntimeFlagB40Grid(
            allocator,
            runtime_tiles,
            render_cache_warn_surface_grid,
            total_rows,
            max_width,
        );
        errdefer allocator.free(runtime_flag_b40_grid);
        const runtime_flag_b01_grid = try buildRuntimeFlagB01Grid(
            allocator,
            segments,
            row_offsets,
            total_rows,
            max_width,
        );
        errdefer allocator.free(runtime_flag_b01_grid);
        const runtime_flag_b80_grid = try buildRuntimeFlagB80Grid(
            allocator,
            segments,
            row_offsets,
            total_rows,
            max_width,
        );
        errdefer allocator.free(runtime_flag_b80_grid);
        const mirror_state_build = try buildAttachmentSourceRowMirrorStates(
            allocator,
            segments,
            row_offsets,
            total_rows,
            runtime_build_config,
        );
        defer allocator.free(mirror_state_build.states);
        var attachment_scaffold = try attachment_builders.Scaffold.collect(
            allocator,
            segments,
            row_offsets,
            runtime_tiles,
            total_rows,
            max_width,
            mirror_state_build.states,
        );
        errdefer attachment_scaffold.deinit();
        const runtime_edge_masks = try buildRuntimeEdgeMaskGrid(allocator, runtime_tiles, total_rows, max_width);
        errdefer allocator.free(runtime_edge_masks);
        const runtime_spawn_hints = try buildRuntimeSpawnHintGrid(
            allocator,
            runtime_tiles,
            runtime_warning_zone_grid,
            total_rows,
            max_width,
            runtime_build_flags,
        );
        errdefer allocator.free(runtime_spawn_hints);

        return .{
            .allocator = allocator,
            .segments = segments,
            .segment_logical_indices = segment_logical_indices,
            .row_offsets = row_offsets,
            .attachment_scaffold = attachment_scaffold,
            .model_assets = try model_assets_list.toOwnedSlice(allocator),
            .placed_models = try placed_models_list.toOwnedSlice(allocator),
            .runtime_build_flags = runtime_build_flags,
            .runtime_build_seed = options.runtime_build_seed,
            .runtime_build_final_random_state = mirror_state_build.final_random_state,
            .runtime_active_row_start = runtime_active_row_start,
            .runtime_active_row_end = runtime_active_row_end,
            .course_end_threshold = course_end_threshold,
            .garbage_scalar = options.garbage_scalar_override orelse level_definition.normalizedGarbageScalar() orelse 0.0,
            .salt_scalar = options.salt_scalar_override orelse level_definition.normalizedSaltScalar() orelse 0.0,
            .parcel_target_count = countActiveParcelAnnotations(segments),
            .runtime_tiles = runtime_tiles,
            .runtime_row_flags = runtime_row_flags,
            .runtime_row_ring_speeds = runtime_row_ring_speeds,
            .runtime_ring_effect_kinds = runtime_ring_effect_kinds,
            .runtime_warning_zone_grid = runtime_warning_zone_grid,
            .render_cache = .{
                .warn_surface_grid = render_cache_warn_surface_grid,
                .surface_swap_grid = render_cache_surface_swap_grid,
                .flag_b40_grid = runtime_flag_b40_grid,
                .edge_masks = runtime_edge_masks,
            },
            .runtime_flag_b01_grid = runtime_flag_b01_grid,
            .runtime_flag_b80_grid = runtime_flag_b80_grid,
            .runtime_spawn_hints = runtime_spawn_hints,
            .total_rows = total_rows,
            .max_width = max_width,
        };
    }

    pub fn loadStandaloneSegmentWithOptions(
        allocator: std.mem.Allocator,
        catalog: *const assets.Catalog,
        entry: archive.Entry,
        options: LoadOptions,
    ) !LoadedLevelPreview {
        const segments = try allocator.alloc(segment.Definition, 1);
        errdefer allocator.free(segments);

        const segment_logical_indices = try allocator.alloc(?usize, 1);
        errdefer allocator.free(segment_logical_indices);

        const row_offsets = try allocator.alloc(usize, 1);
        errdefer allocator.free(row_offsets);
        row_offsets[0] = 0;
        segment_logical_indices[0] = 0;

        segments[0] = try segment.loadFromArchive(allocator, catalog, entry);
        errdefer segments[0].deinit();

        var model_assets_list: std.ArrayList(LoadedModelAsset) = .empty;
        defer model_assets_list.deinit(allocator);
        errdefer {
            for (model_assets_list.items) |*asset| {
                asset.deinit(allocator);
            }
        }
        var model_asset_index_by_path = archive.CaseInsensitiveStringHashMap(usize).init(allocator);
        defer model_asset_index_by_path.deinit();

        var placed_models_list: std.ArrayList(PlacedModel) = .empty;
        defer placed_models_list.deinit(allocator);

        const total_rows = segments[0].height;
        const max_width = segments[0].width;

        for (segments[0].rows, 0..) |row, row_index| {
            if (!options.load_models) continue;

            const annotation = row.annotation orelse continue;
            const model_annotation = switch (annotation) {
                .model => |model| model,
                else => continue,
            };

            const archive_model_path = try resolveSegmentModelArchivePath(allocator, model_annotation.name);
            errdefer allocator.free(archive_model_path);

            const asset_index = if (model_asset_index_by_path.get(archive_model_path)) |existing_index| blk: {
                allocator.free(archive_model_path);
                break :blk existing_index;
            } else blk: {
                const model_entry = catalog.dat.entryByPath(archive_model_path) orelse {
                    allocator.free(archive_model_path);
                    continue;
                };

                const loaded_model = try x2.Uploaded.loadFromArchive(allocator, catalog, model_entry, true);
                try model_assets_list.append(allocator, .{
                    .path = archive_model_path,
                    .loaded = loaded_model,
                });
                const new_index = model_assets_list.items.len - 1;
                try model_asset_index_by_path.put(archive_model_path, new_index);
                break :blk new_index;
            };

            try placed_models_list.append(allocator, .{
                .asset_index = asset_index,
                .segment_index = 0,
                .row_index = row_index,
                .offset = model_annotation.offset,
            });
        }

        const runtime_build_flags = options.runtime_build_flags;
        const runtime_active_row_start = options.runtime_active_row_start;
        const runtime_active_row_end = options.runtime_active_row_end orelse total_rows;
        const course_end_threshold = options.course_end_threshold_override orelse fallbackCourseEndThreshold(total_rows);
        const runtime_build_config: RuntimeBuildConfig = .{
            .build_flags = runtime_build_flags,
            .build_seed = options.runtime_build_seed,
            .active_row_start = runtime_active_row_start,
            .active_row_end = runtime_active_row_end,
        };
        const runtime_tiles = try buildRuntimeTileGrid(
            allocator,
            segments,
            row_offsets,
            total_rows,
            max_width,
            runtime_build_config,
        );
        errdefer allocator.free(runtime_tiles);
        const runtime_row_flags = try buildRuntimeRowFlags(
            allocator,
            segments,
            row_offsets,
            total_rows,
        );
        errdefer allocator.free(runtime_row_flags);
        const runtime_row_ring_speeds = try buildRuntimeRowRingSpeeds(
            allocator,
            segments,
            row_offsets,
            total_rows,
        );
        errdefer allocator.free(runtime_row_ring_speeds);
        const runtime_ring_effect_kinds = try buildRuntimeRingEffectGrid(
            allocator,
            runtime_tiles,
            runtime_row_flags,
            total_rows,
            max_width,
            runtime_build_flags,
        );
        errdefer allocator.free(runtime_ring_effect_kinds);
        const runtime_warning_zone_grid = try buildRuntimeWarningZoneGrid(
            allocator,
            runtime_tiles,
            total_rows,
            max_width,
        );
        errdefer allocator.free(runtime_warning_zone_grid);
        const render_cache_warn_surface_grid = try buildRenderCacheWarnSurfaceGrid(
            allocator,
            runtime_tiles,
            total_rows,
            max_width,
        );
        errdefer allocator.free(render_cache_warn_surface_grid);
        const render_cache_surface_swap_grid = try buildRenderCacheSurfaceSwapGrid(
            allocator,
            runtime_tiles,
            render_cache_warn_surface_grid,
            total_rows,
            max_width,
        );
        errdefer allocator.free(render_cache_surface_swap_grid);
        const runtime_flag_b40_grid = try buildRuntimeFlagB40Grid(
            allocator,
            runtime_tiles,
            render_cache_warn_surface_grid,
            total_rows,
            max_width,
        );
        errdefer allocator.free(runtime_flag_b40_grid);
        const runtime_flag_b01_grid = try buildRuntimeFlagB01Grid(
            allocator,
            segments,
            row_offsets,
            total_rows,
            max_width,
        );
        errdefer allocator.free(runtime_flag_b01_grid);
        const runtime_flag_b80_grid = try buildRuntimeFlagB80Grid(
            allocator,
            segments,
            row_offsets,
            total_rows,
            max_width,
        );
        errdefer allocator.free(runtime_flag_b80_grid);
        const mirror_state_build = try buildAttachmentSourceRowMirrorStates(
            allocator,
            segments,
            row_offsets,
            total_rows,
            runtime_build_config,
        );
        defer allocator.free(mirror_state_build.states);
        var attachment_scaffold = try attachment_builders.Scaffold.collect(
            allocator,
            segments,
            row_offsets,
            runtime_tiles,
            total_rows,
            max_width,
            mirror_state_build.states,
        );
        errdefer attachment_scaffold.deinit();
        const runtime_edge_masks = try buildRuntimeEdgeMaskGrid(allocator, runtime_tiles, total_rows, max_width);
        errdefer allocator.free(runtime_edge_masks);
        const runtime_spawn_hints = try buildRuntimeSpawnHintGrid(
            allocator,
            runtime_tiles,
            runtime_warning_zone_grid,
            total_rows,
            max_width,
            runtime_build_flags,
        );
        errdefer allocator.free(runtime_spawn_hints);

        return .{
            .allocator = allocator,
            .segments = segments,
            .segment_logical_indices = segment_logical_indices,
            .row_offsets = row_offsets,
            .attachment_scaffold = attachment_scaffold,
            .model_assets = try model_assets_list.toOwnedSlice(allocator),
            .placed_models = try placed_models_list.toOwnedSlice(allocator),
            .runtime_build_flags = runtime_build_flags,
            .runtime_build_seed = options.runtime_build_seed,
            .runtime_build_final_random_state = mirror_state_build.final_random_state,
            .runtime_active_row_start = runtime_active_row_start,
            .runtime_active_row_end = runtime_active_row_end,
            .course_end_threshold = course_end_threshold,
            .garbage_scalar = options.garbage_scalar_override orelse 0.0,
            .salt_scalar = options.salt_scalar_override orelse 0.0,
            .parcel_target_count = countActiveParcelAnnotations(segments),
            .runtime_tiles = runtime_tiles,
            .runtime_row_flags = runtime_row_flags,
            .runtime_row_ring_speeds = runtime_row_ring_speeds,
            .runtime_ring_effect_kinds = runtime_ring_effect_kinds,
            .runtime_warning_zone_grid = runtime_warning_zone_grid,
            .render_cache = .{
                .warn_surface_grid = render_cache_warn_surface_grid,
                .surface_swap_grid = render_cache_surface_swap_grid,
                .flag_b40_grid = runtime_flag_b40_grid,
                .edge_masks = runtime_edge_masks,
            },
            .runtime_flag_b01_grid = runtime_flag_b01_grid,
            .runtime_flag_b80_grid = runtime_flag_b80_grid,
            .runtime_spawn_hints = runtime_spawn_hints,
            .total_rows = total_rows,
            .max_width = max_width,
        };
    }

    pub fn deinit(self: *LoadedLevelPreview) void {
        for (self.model_assets) |*asset| {
            asset.deinit(self.allocator);
        }
        self.attachment_scaffold.deinit();
        self.allocator.free(self.placed_models);
        self.allocator.free(self.model_assets);
        self.allocator.free(self.runtime_spawn_hints);
        self.allocator.free(self.runtime_ring_effect_kinds);
        self.allocator.free(self.runtime_warning_zone_grid);
        self.allocator.free(self.runtime_row_flags);
        self.allocator.free(self.runtime_row_ring_speeds);
        self.render_cache.deinit(self.allocator);
        self.allocator.free(self.runtime_flag_b01_grid);
        self.allocator.free(self.runtime_flag_b80_grid);
        self.allocator.free(self.runtime_tiles);
        for (self.segments) |*loaded_segment| {
            loaded_segment.deinit();
        }
        self.allocator.free(self.segment_logical_indices);
        self.allocator.free(self.row_offsets);
        self.allocator.free(self.segments);
    }

    pub fn activeParcelCount(self: *const LoadedLevelPreview) usize {
        return countActiveParcelAnnotations(self.segments);
    }

    pub fn trimParcelAnnotationsToTarget(
        self: *LoadedLevelPreview,
        random_state: *u32,
        target_count: usize,
    ) !usize {
        var parcel_rows: std.ArrayList(ParcelRowLocation) = .empty;
        defer parcel_rows.deinit(self.allocator);

        for (self.segments, 0..) |loaded_segment, segment_index| {
            for (loaded_segment.rows, 0..) |row, row_index| {
                const annotation = row.annotation orelse continue;
                if (annotation.tag() != .parcel) continue;
                try parcel_rows.append(self.allocator, .{
                    .segment_index = segment_index,
                    .row_index = row_index,
                });
            }
        }

        const keep_count = @min(target_count, parcel_rows.items.len);
        var remaining = parcel_rows.items.len;
        while (remaining > keep_count) {
            const remove_index = nextMathRandomScaledIndex(random_state, remaining);
            const last_index = remaining - 1;
            const remove_row = parcel_rows.items[remove_index];
            @constCast(self.segments[remove_row.segment_index].rows)[remove_row.row_index].annotation = null;
            parcel_rows.items[remove_index] = parcel_rows.items[last_index];
            remaining = last_index;
        }

        self.parcel_target_count = keep_count;
        return keep_count;
    }

    pub fn previewCamera(self: *const LoadedLevelPreview, time_seconds: f32, selected_segment_index: usize) rl.Camera3D {
        const bounds = self.segmentPreviewBounds(selected_segment_index);
        const target = bounds.center;
        const distance = @max(@as(f32, @floatFromInt(self.total_rows)) * 0.45, @max(bounds.radius * 2.8, 18.0));
        return .{
            .position = .{
                .x = target.x + std.math.cos(time_seconds * 0.18) * distance,
                .y = target.y + distance * 0.6,
                .z = target.z + std.math.sin(time_seconds * 0.18) * distance,
            },
            .target = target,
            .up = .{ .x = 0.0, .y = 1.0, .z = 0.0 },
            .fovy = 45.0,
            .projection = .perspective,
        };
    }

    pub fn draw(self: *const LoadedLevelPreview, selected_segment_index: usize) void {
        self.drawRawDebug(selected_segment_index);
    }

    pub fn drawRawDebug(self: *const LoadedLevelPreview, selected_segment_index: usize) void {
        const cell_size: f32 = 1.0;
        const width_offset = @as(f32, @floatFromInt(self.max_width)) * 0.5;

        for (self.segments, 0..) |loaded_segment, segment_index| {
            const is_selected = segment_index == selected_segment_index;
            const segment_start_z = @as(f32, @floatFromInt(self.row_offsets[segment_index])) * cell_size;

            drawSegmentBoundary(width_offset, segment_start_z, loaded_segment.height, is_selected);
            drawSegmentCells(self, segment_index, loaded_segment, width_offset, segment_start_z, is_selected, cell_size);
            drawSegmentGameplayMarkers(self, segment_index, loaded_segment, width_offset, segment_start_z, is_selected, cell_size);
            drawSegmentCenterline(self, segment_index, loaded_segment, width_offset, segment_start_z, cell_size, if (is_selected) .orange else .sky_blue);
            drawSegmentAnnotations(self, segment_index, loaded_segment, width_offset, segment_start_z, cell_size, is_selected);
        }

        self.drawPlacedModels(width_offset, cell_size);
    }

    pub fn drawDebugOverlay(self: *const LoadedLevelPreview, selected_segment_index: usize) void {
        const cell_size: f32 = 1.0;
        const width_offset = @as(f32, @floatFromInt(self.max_width)) * 0.5;

        for (self.segments, 0..) |loaded_segment, segment_index| {
            const is_selected = segment_index == selected_segment_index;
            const segment_start_z = @as(f32, @floatFromInt(self.row_offsets[segment_index])) * cell_size;

            drawSegmentBoundary(width_offset, segment_start_z, loaded_segment.height, is_selected);
            drawSegmentCells(self, segment_index, loaded_segment, width_offset, segment_start_z, is_selected, cell_size);
            drawSegmentGameplayMarkers(self, segment_index, loaded_segment, width_offset, segment_start_z, is_selected, cell_size);
            drawSegmentCenterline(self, segment_index, loaded_segment, width_offset, segment_start_z, cell_size, if (is_selected) .orange else .sky_blue);
            drawSegmentAnnotations(self, segment_index, loaded_segment, width_offset, segment_start_z, cell_size, is_selected);
        }
    }

    pub fn activeSegment(self: *const LoadedLevelPreview, selected_segment_index: usize) ?*const segment.Definition {
        if (selected_segment_index >= self.segments.len) return null;
        return &self.segments[selected_segment_index];
    }

    pub fn locateRow(self: *const LoadedLevelPreview, global_row: usize) ?RowLocation {
        if (global_row >= self.total_rows or self.segments.len == 0) return null;

        var segment_index = self.segments.len - 1;
        for (self.row_offsets, 0..) |row_offset, index| {
            const next_offset = if (index + 1 < self.row_offsets.len) self.row_offsets[index + 1] else self.total_rows;
            if (global_row >= row_offset and global_row < next_offset) {
                segment_index = index;
                break;
            }
        }

        const row_index = global_row - self.row_offsets[segment_index];
        const loaded_segment = self.segments[segment_index];
        if (row_index >= loaded_segment.rows.len) return null;

        return .{
            .global_row = global_row,
            .segment_index = segment_index,
            .row_index = row_index,
            .row = loaded_segment.rows[row_index],
        };
    }

    pub fn laneBoundsForRow(self: *const LoadedLevelPreview, row_location: RowLocation) LaneBounds {
        _ = self;
        return guidanceBounds(row_location.row) orelse blk: {
            if (row_location.row.cells.len == 0) {
                break :blk .{ .min = 0, .max = 0 };
            }
            break :blk .{ .min = 0, .max = row_location.row.cells.len - 1 };
        };
    }

    pub fn pathBoundsForRow(self: *const LoadedLevelPreview, row_location: RowLocation) ?LaneBounds {
        _ = self;
        return pathBounds(row_location.row.cells);
    }

    pub fn activePathAtRow(self: *const LoadedLevelPreview, global_row: usize) ?attachment_builders.AuthoredPathRow {
        return self.attachment_scaffold.activePathAtRow(global_row);
    }

    pub fn activeBuiltAttachmentAtRow(self: *const LoadedLevelPreview, global_row: usize) ?*const attachment_builders.BuiltAttachment {
        return self.attachment_scaffold.activeBuiltAttachmentAtRow(global_row);
    }

    pub fn installedBuiltAttachmentsAtRow(self: *const LoadedLevelPreview, global_row: usize) attachment_builders.InstalledBuiltAttachmentSlots {
        return self.attachment_scaffold.installedBuiltAttachmentsAtRow(global_row);
    }

    pub fn installedBuiltAttachmentAtRow(self: *const LoadedLevelPreview, global_row: usize) ?*const attachment_builders.BuiltAttachment {
        return self.attachment_scaffold.installedBuiltAttachmentAtRow(global_row);
    }

    pub fn builtAttachmentForSourceRow(self: *const LoadedLevelPreview, global_row: usize) ?*const attachment_builders.BuiltAttachment {
        for (self.attachment_scaffold.built_attachments) |*built| {
            if (built.row.global_row == global_row) return built;
        }
        return null;
    }

    pub fn activePathNameAtRow(self: *const LoadedLevelPreview, global_row: usize) ?[]const u8 {
        const installed = self.installedBuiltAttachmentsAtRow(global_row);
        if (installed.primary orelse installed.secondary) |built| {
            return built.row.raw_name;
        }
        const row = self.activePathAtRow(global_row) orelse return null;
        return row.raw_name;
    }

    pub fn attachmentPathCountForSegment(self: *const LoadedLevelPreview, segment_index: usize) usize {
        return self.attachment_scaffold.pathCountForSegment(segment_index);
    }

    pub fn firstAttachmentPathForSegment(self: *const LoadedLevelPreview, segment_index: usize) ?attachment_builders.AuthoredPathRow {
        return self.attachment_scaffold.firstPathForSegment(segment_index);
    }

    pub fn cellAt(self: *const LoadedLevelPreview, global_row: usize, lane_index: usize) ?u8 {
        const row_location = self.locateRow(global_row) orelse return null;
        const row = row_location.row;
        if (lane_index >= row.cells.len) return null;
        return row.cells[lane_index];
    }

    pub fn gameplayCellSampleAt(self: *const LoadedLevelPreview, global_row: usize, lane_index: usize) ?GameplayCellSample {
        const row_location = self.locateRow(global_row) orelse return null;
        const row = row_location.row;
        if (lane_index >= row.cells.len) return null;

        const cell = row.cells[lane_index];
        const kind = if (self.runtimeTileAt(global_row, lane_index)) |tile_type|
            runtimeGameplayCellKindForTile(tile_type, self.runtime_build_flags) orelse gameplayCellKind(cell) orelse return null
        else
            gameplayCellKind(cell) orelse return null;
        return .{
            .global_row = global_row,
            .lane_index = lane_index,
            .cell = cell,
            .kind = kind,
            .annotation = if (row.annotation) |annotation| annotation.tag() else null,
            .marked = row.marked,
        };
    }

    pub fn laneIndexAtWorldX(self: *const LoadedLevelPreview, world_x: f32) usize {
        if (self.max_width == 0) return 0;
        const width_offset = @as(f32, @floatFromInt(self.max_width)) * 0.5;
        const raw_index: isize = @intFromFloat(@floor((world_x + width_offset) - 0.5));
        return @intCast(std.math.clamp(raw_index, 0, @as(isize, @intCast(self.max_width - 1))));
    }

    pub fn rowIndexAtWorldZ(self: *const LoadedLevelPreview, world_z: f32) usize {
        if (self.total_rows == 0) return 0;
        const raw_index: isize = @intFromFloat(@floor(world_z));
        return @intCast(std.math.clamp(raw_index, 0, @as(isize, @intCast(self.total_rows - 1))));
    }

    pub fn gameplayCellSampleAtWorldPosition(self: *const LoadedLevelPreview, world_position: rl.Vector3) ?GameplayCellSample {
        if (self.total_rows == 0 or self.max_width == 0) return null;
        const global_row = self.rowIndexAtWorldZ(world_position.z);
        const lane_index = self.laneIndexAtWorldX(world_position.x);
        return self.gameplayCellSampleAt(global_row, lane_index);
    }

    pub fn runtimeTileAt(self: *const LoadedLevelPreview, global_row: usize, lane_index: usize) ?u8 {
        if (global_row >= self.total_rows or self.max_width == 0 or lane_index >= self.max_width) return null;
        return self.runtime_tiles[runtimeTileIndex(self.max_width, global_row, lane_index)];
    }

    pub fn runtimeRowFlagsAt(self: *const LoadedLevelPreview, global_row: usize) u32 {
        if (global_row >= self.total_rows) return 0;
        return self.runtime_row_flags[global_row];
    }

    pub fn runtimeRowRingSpeedAt(self: *const LoadedLevelPreview, global_row: usize) f32 {
        if (global_row >= self.total_rows) return 0.0;
        return self.runtime_row_ring_speeds[global_row];
    }

    pub fn nativeRingEffectKindAt(self: *const LoadedLevelPreview, global_row: usize, lane_index: usize) u8 {
        if (global_row >= self.total_rows or self.max_width == 0 or lane_index >= self.max_width) return 0;
        return self.runtime_ring_effect_kinds[runtimeTileIndex(self.max_width, global_row, lane_index)];
    }

    pub fn renderCacheWarnSurfaceAt(self: *const LoadedLevelPreview, global_row: usize, lane_index: usize) bool {
        return self.render_cache.warnSurfaceAt(self.total_rows, self.max_width, global_row, lane_index);
    }

    pub fn runtimeWarningZoneAt(self: *const LoadedLevelPreview, global_row: usize, lane_index: usize) bool {
        if (global_row >= self.total_rows or self.max_width == 0 or lane_index >= self.max_width) return false;
        return self.runtime_warning_zone_grid[runtimeTileIndex(self.max_width, global_row, lane_index)];
    }

    pub fn renderCacheSurfaceSwapAt(self: *const LoadedLevelPreview, global_row: usize, lane_index: usize) bool {
        return self.render_cache.surfaceSwapAt(self.total_rows, self.max_width, global_row, lane_index);
    }

    pub fn renderCacheHeadAt(self: *const LoadedLevelPreview, global_row: usize, lane_index: usize) bool {
        return self.render_cache.flagB40At(self.total_rows, self.max_width, global_row, lane_index);
    }

    pub fn runtimeFlagB40At(self: *const LoadedLevelPreview, global_row: usize, lane_index: usize) bool {
        return self.renderCacheHeadAt(global_row, lane_index);
    }

    pub fn runtimeFlagB01At(self: *const LoadedLevelPreview, global_row: usize, lane_index: usize) bool {
        if (global_row >= self.total_rows or self.max_width == 0 or lane_index >= self.max_width) return false;
        return self.runtime_flag_b01_grid[runtimeTileIndex(self.max_width, global_row, lane_index)];
    }

    pub fn runtimeFlagB80At(self: *const LoadedLevelPreview, global_row: usize, lane_index: usize) bool {
        if (global_row >= self.total_rows or self.max_width == 0 or lane_index >= self.max_width) return false;
        return self.runtime_flag_b80_grid[runtimeTileIndex(self.max_width, global_row, lane_index)];
    }

    pub fn runtimeEdgeMaskAt(self: *const LoadedLevelPreview, global_row: usize, lane_index: usize) ?u8 {
        return self.render_cache.edgeMaskAt(self.total_rows, self.max_width, global_row, lane_index);
    }

    pub fn runtimeSpawnHintMaskAt(self: *const LoadedLevelPreview, global_row: usize, lane_index: usize) ?u8 {
        if (global_row >= self.total_rows or self.max_width == 0 or lane_index >= self.max_width) return null;
        return self.runtime_spawn_hints[runtimeTileIndex(self.max_width, global_row, lane_index)];
    }

    pub fn hasGarbageSpawnHintAt(self: *const LoadedLevelPreview, global_row: usize, lane_index: usize) bool {
        const mask = self.runtimeSpawnHintMaskAt(global_row, lane_index) orelse return false;
        return (mask & runtime_spawn_hint_garbage_fallback) != 0;
    }

    pub fn hasSaltSpawnHintAt(self: *const LoadedLevelPreview, global_row: usize, lane_index: usize) bool {
        const mask = self.runtimeSpawnHintMaskAt(global_row, lane_index) orelse return false;
        return (mask & runtime_spawn_hint_salt_fallback) != 0;
    }

    pub fn garbageFallbackNeighborsAllowedAt(self: *const LoadedLevelPreview, global_row: usize, lane_index: usize) bool {
        if (global_row >= self.total_rows or self.max_width == 0 or lane_index >= self.max_width) return false;

        if (lane_index > 0) {
            const left_tile = self.runtimeTileAt(global_row, lane_index - 1) orelse return false;
            if (!runtimeGarbageFallbackNeighborAllowed(left_tile)) return false;
        }
        if (lane_index + 1 < self.max_width) {
            const right_tile = self.runtimeTileAt(global_row, lane_index + 1) orelse return false;
            if (!runtimeGarbageFallbackNeighborAllowed(right_tile)) return false;
        }
        return true;
    }

    pub fn fallbackHazardCandidateCounts(self: *const LoadedLevelPreview) FallbackHazardCandidateCounts {
        var counts: FallbackHazardCandidateCounts = .{};
        for (self.runtime_spawn_hints) |hint_mask| {
            if ((hint_mask & runtime_spawn_hint_garbage_fallback) != 0) {
                counts.garbage += 1;
            }
            if ((hint_mask & runtime_spawn_hint_salt_fallback) != 0) {
                counts.salt += 1;
            }
        }
        return counts;
    }

    pub fn worldPositionForLane(self: *const LoadedLevelPreview, lane_center: f32, row_position: f32, y: f32) rl.Vector3 {
        const width_offset = @as(f32, @floatFromInt(self.max_width)) * 0.5;
        return .{
            .x = (lane_center - width_offset) * 1.0,
            .y = y,
            .z = row_position + 0.5,
        };
    }

    pub fn sampleFloorHeightAtGridPosition(self: *const LoadedLevelPreview, global_row: usize, lane_index: usize, row_position: f32) ?f32 {
        const tile_type = self.runtimeTileAt(global_row, lane_index) orelse return null;
        return sampleFloorHeightForRuntimeTile(
            tile_type,
            row_position,
            specialFloorHeightForShippedRuntimeTile(tile_type),
        );
    }

    pub fn floorHeightAtCellCenter(self: *const LoadedLevelPreview, global_row: usize, lane_index: usize) ?f32 {
        return self.sampleFloorHeightAtGridPosition(
            global_row,
            lane_index,
            @as(f32, @floatFromInt(global_row)) + 0.5,
        );
    }

    const PreviewBounds = struct {
        center: rl.Vector3,
        radius: f32,
    };

    fn segmentPreviewBounds(self: *const LoadedLevelPreview, selected_segment_index: usize) PreviewBounds {
        const safe_index = @min(selected_segment_index, self.segments.len - 1);
        const loaded_segment = self.segments[safe_index];
        const width_offset = @as(f32, @floatFromInt(self.max_width)) * 0.5;
        const start_z = @as(f32, @floatFromInt(self.row_offsets[safe_index]));
        const end_z = start_z + @as(f32, @floatFromInt(loaded_segment.height));

        var min_x = -width_offset;
        var max_x = width_offset;
        var min_y: f32 = 0.0;
        var max_y: f32 = 0.0;
        var min_z = start_z;
        var max_z = end_z;

        for (self.attachment_scaffold.built_attachments) |built| {
            if (built.row.segment_index != safe_index) continue;
            const half_width = @as(f32, @floatFromInt(built.template.width_cells)) * 0.5;
            const base_row = @as(f32, @floatFromInt(built.row.global_row));
            for (built.template.samples) |sample| {
                const lateral_span = half_width * sample.lateral_scale;
                const center_x = sample.position.x + sample.center_x;
                const world_z = base_row + sample.position.z;
                min_x = @min(min_x, center_x - lateral_span);
                max_x = @max(max_x, center_x + lateral_span);
                min_y = @min(min_y, sample.position.y);
                max_y = @max(max_y, sample.position.y);
                min_z = @min(min_z, world_z);
                max_z = @max(max_z, world_z);
            }
        }

        const center = rl.Vector3{
            .x = (min_x + max_x) * 0.5,
            .y = (min_y + max_y) * 0.5,
            .z = (min_z + max_z) * 0.5,
        };
        const dx = max_x - center.x;
        const dy = max_y - center.y;
        const dz = max_z - center.z;
        return .{
            .center = center,
            .radius = @max(std.math.sqrt((dx * dx) + (dy * dy) + (dz * dz)), 1.0),
        };
    }

    fn drawPlacedModels(self: *const LoadedLevelPreview, width_offset: f32, cell_size: f32) void {
        for (self.placed_models) |instance| {
            if (instance.asset_index >= self.model_assets.len) continue;
            if (instance.segment_index >= self.segments.len) continue;

            const loaded_segment = self.segments[instance.segment_index];
            if (instance.row_index >= loaded_segment.rows.len) continue;

            const row = loaded_segment.rows[instance.row_index];
            const segment_start_z = @as(f32, @floatFromInt(self.row_offsets[instance.segment_index])) * cell_size;
            const global_row = self.row_offsets[instance.segment_index] + instance.row_index;
            const base = rowAnchorPosition(self, global_row, row, instance.row_index, width_offset, segment_start_z, cell_size, 0.02);
            const position = applyAnnotationOffset(base, instance.offset);
            const asset = &self.model_assets[instance.asset_index].loaded;

            const transform = rl.Matrix.translate(
                position.x - asset.bounds.center.x,
                position.y - asset.bounds.min.y,
                position.z - asset.bounds.center.z,
            );
            asset.drawEx(transform);
        }
    }

    pub fn drawPlacedModelsOnly(self: *const LoadedLevelPreview) void {
        self.drawPlacedModels(@as(f32, @floatFromInt(self.max_width)) * 0.5, 1.0);
    }
};

fn fallbackCourseEndThreshold(total_rows: usize) f32 {
    if (total_rows == 0) return 0.0;
    return @floatFromInt(total_rows - 1);
}

fn nativeCourseEndThresholdForLevel(
    level_definition: *const level.Definition,
    row_offsets: []const usize,
    total_rows: usize,
    random_length_scalar_override: ?f32,
) f32 {
    // PORT(verified): non-random `populate_runtime_track_cells_from_segments` seeds
    // `game + 0x58` from the start of the final `Last:` block (`total_rows - last_block_len`),
    // not from the last populated row. The mode-1 random branch keeps `game + 0x54` on the
    // authored `Length:` lane, scales it by `floor((scalar * 0.65 + 0.35) * Length)`, then
    // subtracts the final `Last:` block row count into `game + 0x58`.
    if (!level_definition.random and level_definition.last_segments.len != 0 and level_definition.last_segments.len <= row_offsets.len) {
        const last_block_start = row_offsets.len - level_definition.last_segments.len;
        return @floatFromInt(row_offsets[last_block_start]);
    }

    if (level_definition.random) {
        if (random_length_scalar_override) |random_length_scalar| {
            if (level_definition.last_segments.len != 0 and level_definition.last_segments.len <= row_offsets.len) {
                const last_block_start = row_offsets.len - level_definition.last_segments.len;
                const last_block_row_count = total_rows - row_offsets[last_block_start];
                const scaled_total_rows = @as(isize, @intFromFloat(@floor(
                    @as(f32, @floatFromInt(level_definition.length)) * ((random_length_scalar * 0.65) + 0.35),
                )));
                return @floatFromInt(scaled_total_rows - @as(isize, @intCast(last_block_row_count)));
            }
        }
    }

    return fallbackCourseEndThreshold(total_rows);
}

fn resolveSegmentModelArchivePath(allocator: std.mem.Allocator, model_name: []const u8) ![]const u8 {
    const stem = if (std.mem.lastIndexOfScalar(u8, model_name, '.')) |dot_index| model_name[0..dot_index] else model_name;
    var upper = try allocator.alloc(u8, stem.len);
    errdefer allocator.free(upper);
    for (stem, 0..) |ch, index| {
        upper[index] = std.ascii.toUpper(ch);
    }

    const archive_path = try std.fmt.allocPrint(allocator, "X/{s}.X2", .{upper});
    allocator.free(upper);
    return archive_path;
}

fn drawSegmentCells(
    preview: *const LoadedLevelPreview,
    segment_index: usize,
    loaded_segment: segment.Definition,
    width_offset: f32,
    segment_start_z: f32,
    is_selected: bool,
    cell_size: f32,
) void {
    for (loaded_segment.rows, 0..) |row, row_index| {
        const global_row = preview.row_offsets[segment_index] + row_index;
        for (row.cells, 0..) |cell, col_index| {
            const floor_height = preview.floorHeightAtCellCenter(global_row, col_index) orelse 0.0;
            const position = rl.Vector3{
                .x = (@as(f32, @floatFromInt(col_index)) - width_offset + 0.5) * cell_size,
                .y = if (cell == '@') 0.35 else floor_height - 0.05,
                .z = segment_start_z + @as(f32, @floatFromInt(row_index)) * cell_size + 0.5,
            };
            const size = rl.Vector3{
                .x = cell_size,
                .y = if (cell == '@') 0.7 else 0.1,
                .z = cell_size,
            };

            const color = tintForSelection(colorForCell(cell), is_selected);
            rl.drawCubeV(position, size, color);
            if (cell != '@') {
                drawRuntimeCellExposedEdges(
                    preview.runtimeEdgeMaskAt(global_row, col_index) orelse 0,
                    position,
                    size,
                    tintForSelection(.ray_white, is_selected),
                );
            }
            if (row.marked and cell != '@') {
                rl.drawCubeWiresV(position, size, .gold);
            }
            if (preview.runtimeWarningZoneAt(global_row, col_index) and cell != '@') {
                rl.drawCubeWiresV(position, size, .orange);
            }
        }
    }
}

fn drawSegmentCenterline(
    preview: *const LoadedLevelPreview,
    segment_index: usize,
    loaded_segment: segment.Definition,
    width_offset: f32,
    segment_start_z: f32,
    cell_size: f32,
    color: rl.Color,
) void {
    var previous: ?rl.Vector3 = null;

    for (loaded_segment.rows, 0..) |row, row_index| {
        const global_row = preview.row_offsets[segment_index] + row_index;
        const bounds = guidanceBounds(row) orelse {
            previous = null;
            continue;
        };

        const center_col = (@as(f32, @floatFromInt(bounds.min + bounds.max)) * 0.5) + 0.5;
        const floor_height = preview.floorHeightAtCellCenter(global_row, (bounds.min + bounds.max) / 2) orelse 0.0;
        const point = worldPositionForColumn(center_col, row_index, width_offset, segment_start_z, cell_size, floor_height + 0.35);

        rl.drawSphere(point, 0.08, color);
        if (previous) |prev| {
            rl.drawLine3D(prev, point, color);
        }
        previous = point;
    }
}

fn drawSegmentAnnotations(
    preview: *const LoadedLevelPreview,
    segment_index: usize,
    loaded_segment: segment.Definition,
    width_offset: f32,
    segment_start_z: f32,
    cell_size: f32,
    is_selected: bool,
) void {
    for (loaded_segment.rows, 0..) |row, row_index| {
        const global_row = preview.row_offsets[segment_index] + row_index;
        const annotation = row.annotation orelse continue;
        switch (annotation) {
            .path => drawPathMarkers(preview, global_row, row, row_index, width_offset, segment_start_z, cell_size, is_selected),
            .ring => drawRingMarkers(preview, global_row, row, row_index, width_offset, segment_start_z, cell_size, is_selected),
            .parcel => |parcel| drawParcelMarker(preview, global_row, row, row_index, width_offset, segment_start_z, cell_size, parcel, is_selected),
            .model => |model| drawModelMarker(preview, global_row, row, row_index, width_offset, segment_start_z, cell_size, model, is_selected),
            .jetpack_off => drawJetpackOffMarker(preview, global_row, row, row_index, width_offset, segment_start_z, cell_size, is_selected),
            .no_fall => drawNoFallMarker(preview, global_row, row, row_index, width_offset, segment_start_z, cell_size, is_selected),
        }
    }
}

fn drawSegmentGameplayMarkers(
    preview: *const LoadedLevelPreview,
    segment_index: usize,
    loaded_segment: segment.Definition,
    width_offset: f32,
    segment_start_z: f32,
    is_selected: bool,
    cell_size: f32,
) void {
    for (loaded_segment.rows, 0..) |row, row_index| {
        const global_row = preview.row_offsets[segment_index] + row_index;
        for (row.cells, 0..) |_, col_index| {
            const floor_height = preview.floorHeightAtCellCenter(global_row, col_index) orelse 0.0;
            if (preview.gameplayCellSampleAt(global_row, col_index)) |sample| {
                const kind = sample.kind;
                if (kind != .ring and kind != .attachment_probe and kind != .attachment_entry) {
                    const position = cellWorldPosition(col_index, row_index, width_offset, segment_start_z, cell_size, floor_height + gameplayCellY(kind));
                    const color = tintForSelection(gameplayCellColor(kind), is_selected);

                    switch (kind) {
                        .trampoline => rl.drawCubeV(position, .{ .x = 0.34, .y = 0.1, .z = 0.34 }, color),
                        .slug => rl.drawCubeV(position, .{ .x = 0.26, .y = 0.48, .z = 0.26 }, color),
                        .garbage => rl.drawSphere(position, 0.16, color),
                        .salt => {
                            rl.drawSphere(position, 0.14, color);
                            rl.drawLine3D(
                                .{ .x = position.x, .y = position.y - 0.1, .z = position.z },
                                .{ .x = position.x, .y = position.y + 0.14, .z = position.z },
                                color,
                            );
                        },
                        .health => rl.drawCubeV(position, .{ .x = 0.22, .y = 0.22, .z = 0.22 }, color),
                        .jetpack => rl.drawCubeV(position, .{ .x = 0.24, .y = 0.44, .z = 0.24 }, color),
                        .ring, .attachment_probe, .attachment_entry => unreachable,
                    }
                }
            }

            const spawn_hint_mask = preview.runtimeSpawnHintMaskAt(global_row, col_index) orelse 0;
            if ((spawn_hint_mask & runtime_spawn_hint_garbage_fallback) != 0) {
                const garbage_position = cellWorldPosition(
                    col_index,
                    row_index,
                    width_offset,
                    segment_start_z,
                    cell_size,
                    floor_height + 0.24,
                );
                const shifted = rl.Vector3{
                    .x = garbage_position.x - 0.12,
                    .y = garbage_position.y,
                    .z = garbage_position.z,
                };
                rl.drawCubeWiresV(shifted, .{ .x = 0.18, .y = 0.18, .z = 0.18 }, tintForSelection(.gray, is_selected));
            }

            if ((spawn_hint_mask & runtime_spawn_hint_salt_fallback) != 0) {
                const salt_position = cellWorldPosition(
                    col_index,
                    row_index,
                    width_offset,
                    segment_start_z,
                    cell_size,
                    floor_height + 0.28,
                );
                const shifted = rl.Vector3{
                    .x = salt_position.x + 0.12,
                    .y = salt_position.y,
                    .z = salt_position.z,
                };
                const color = tintForSelection(.sky_blue, is_selected);
                rl.drawCubeWiresV(shifted, .{ .x = 0.16, .y = 0.16, .z = 0.16 }, color);
                rl.drawLine3D(
                    .{ .x = shifted.x, .y = shifted.y - 0.1, .z = shifted.z },
                    .{ .x = shifted.x, .y = shifted.y + 0.12, .z = shifted.z },
                    color,
                );
            }
        }
    }
}

fn drawSegmentBoundary(width_offset: f32, segment_start_z: f32, height: usize, is_selected: bool) void {
    const left = rl.Vector3{ .x = -width_offset, .y = 0.02, .z = segment_start_z };
    const right = rl.Vector3{ .x = width_offset, .y = 0.02, .z = segment_start_z };
    rl.drawLine3D(left, right, if (is_selected) .orange else .dark_gray);

    const end_z = segment_start_z + @as(f32, @floatFromInt(height));
    rl.drawLine3D(
        .{ .x = -width_offset, .y = 0.02, .z = end_z },
        .{ .x = width_offset, .y = 0.02, .z = end_z },
        if (is_selected) .orange else .dark_gray,
    );
}

fn drawPathMarkers(
    preview: *const LoadedLevelPreview,
    global_row: usize,
    row: segment.Row,
    row_index: usize,
    width_offset: f32,
    segment_start_z: f32,
    cell_size: f32,
    is_selected: bool,
) void {
    var found = false;
    var first: ?rl.Vector3 = null;
    var last: ?rl.Vector3 = null;

    for (row.cells, 0..) |cell, col_index| {
        if (!isPathCell(cell)) continue;
        found = true;

        const floor_height = preview.floorHeightAtCellCenter(global_row, col_index) orelse 0.0;
        const position = cellWorldPosition(col_index, row_index, width_offset, segment_start_z, cell_size, floor_height + 0.62);
        const color = tintForSelection(if (cell == 'P') .sky_blue else .blue, is_selected);
        rl.drawSphere(position, if (cell == 'P') 0.17 else 0.13, color);
        if (first == null) first = position;
        last = position;
    }

    if (first) |start| {
        if (last) |finish| {
            if (start.x != finish.x or start.z != finish.z) {
                rl.drawLine3D(start, finish, tintForSelection(.gold, is_selected));
            }
        }
    }
}

fn drawRingMarkers(
    preview: *const LoadedLevelPreview,
    global_row: usize,
    row: segment.Row,
    row_index: usize,
    width_offset: f32,
    segment_start_z: f32,
    cell_size: f32,
    is_selected: bool,
) void {
    const annotation = row.annotation orelse return;
    const ring = switch (annotation) {
        .ring => |ring_kind| ring_kind,
        else => return,
    };
    const color = tintForSelection(colorForAnnotation(annotation), is_selected);

    for (row.cells, 0..) |cell, col_index| {
        if (!isRingCell(cell)) continue;
        const floor_height = preview.floorHeightAtCellCenter(global_row, col_index) orelse 0.0;
        const position = cellWorldPosition(col_index, row_index, width_offset, segment_start_z, cell_size, floor_height + 0.85);
        switch (ring) {
            .none => rl.drawCubeWiresV(position, .{ .x = 0.28, .y = 0.28, .z = 0.28 }, color),
            .normal => rl.drawSphere(position, 0.2, color),
            .powerup => rl.drawCubeV(position, .{ .x = 0.28, .y = 0.28, .z = 0.28 }, color),
            .explode => {
                rl.drawSphere(position, 0.22, color);
                rl.drawSphere(.{ .x = position.x, .y = position.y + 0.05, .z = position.z }, 0.08, .red);
            },
            .slow => rl.drawSphere(position, 0.18, color),
        }
    }
}

fn drawParcelMarker(
    preview: *const LoadedLevelPreview,
    global_row: usize,
    row: segment.Row,
    row_index: usize,
    width_offset: f32,
    segment_start_z: f32,
    cell_size: f32,
    parcel: segment.ParcelAnnotation,
    is_selected: bool,
) void {
    const base = rowAnchorPosition(preview, global_row, row, row_index, width_offset, segment_start_z, cell_size, 0.6);
    const position = applyAnnotationOffset(base, parcel.offset);
    const color = tintForSelection(if (parcel.id == 0) .gold else .green, is_selected);

    rl.drawLine3D(base, position, tintForSelection(.dark_green, is_selected));
    rl.drawCubeV(position, .{ .x = 0.32, .y = 0.32, .z = 0.32 }, color);
}

fn drawModelMarker(
    preview: *const LoadedLevelPreview,
    global_row: usize,
    row: segment.Row,
    row_index: usize,
    width_offset: f32,
    segment_start_z: f32,
    cell_size: f32,
    model_annotation: segment.ModelAnnotation,
    is_selected: bool,
) void {
    const base = rowAnchorPosition(preview, global_row, row, row_index, width_offset, segment_start_z, cell_size, 0.5);
    const position = applyAnnotationOffset(base, model_annotation.offset);
    const color = tintForSelection(.purple, is_selected);

    rl.drawLine3D(base, position, tintForSelection(.light_gray, is_selected));
    rl.drawCubeV(position, .{ .x = 0.36, .y = 0.72, .z = 0.36 }, color);
    rl.drawCubeWiresV(position, .{ .x = 0.36, .y = 0.72, .z = 0.36 }, .ray_white);
}

fn drawJetpackOffMarker(
    preview: *const LoadedLevelPreview,
    global_row: usize,
    row: segment.Row,
    row_index: usize,
    width_offset: f32,
    segment_start_z: f32,
    cell_size: f32,
    is_selected: bool,
) void {
    const bounds = guidanceBounds(row) orelse return;
    drawRowStrip(preview, global_row, bounds, row_index, width_offset, segment_start_z, cell_size, 0.22, tintForSelection(.red, is_selected));
}

fn drawNoFallMarker(
    preview: *const LoadedLevelPreview,
    global_row: usize,
    row: segment.Row,
    row_index: usize,
    width_offset: f32,
    segment_start_z: f32,
    cell_size: f32,
    is_selected: bool,
) void {
    const bounds = guidanceBounds(row) orelse return;
    const left_floor = preview.floorHeightAtCellCenter(global_row, bounds.min) orelse 0.0;
    const right_floor = preview.floorHeightAtCellCenter(global_row, bounds.max) orelse 0.0;
    const left = worldPositionForColumn(@as(f32, @floatFromInt(bounds.min)) + 0.5, row_index, width_offset, segment_start_z, cell_size, left_floor + 0.95);
    const right = worldPositionForColumn(@as(f32, @floatFromInt(bounds.max)) + 0.5, row_index, width_offset, segment_start_z, cell_size, right_floor + 0.95);
    const color = tintForSelection(.sky_blue, is_selected);
    rl.drawLine3D(left, right, color);
    rl.drawSphere(left, 0.08, color);
    rl.drawSphere(right, 0.08, color);
}

fn drawRowStrip(
    preview: *const LoadedLevelPreview,
    global_row: usize,
    bounds: LaneBounds,
    row_index: usize,
    width_offset: f32,
    segment_start_z: f32,
    cell_size: f32,
    y: f32,
    color: rl.Color,
) void {
    const center_col = (@as(f32, @floatFromInt(bounds.min + bounds.max)) * 0.5) + 0.5;
    const width = @as(f32, @floatFromInt(bounds.max - bounds.min + 1)) * cell_size;
    const floor_height = preview.floorHeightAtCellCenter(global_row, (bounds.min + bounds.max) / 2) orelse 0.0;
    const position = worldPositionForColumn(center_col, row_index, width_offset, segment_start_z, cell_size, floor_height + y);
    rl.drawCubeV(position, .{ .x = width, .y = 0.08, .z = 0.2 }, color);
}

fn rowAnchorPosition(
    preview: *const LoadedLevelPreview,
    global_row: usize,
    row: segment.Row,
    row_index: usize,
    width_offset: f32,
    segment_start_z: f32,
    cell_size: f32,
    y: f32,
) rl.Vector3 {
    const bounds = guidanceBounds(row) orelse blk: {
        const max_index = if (row.cells.len == 0) @as(usize, 0) else row.cells.len - 1;
        break :blk LaneBounds{ .min = 0, .max = max_index };
    };
    const center_col = (@as(f32, @floatFromInt(bounds.min + bounds.max)) * 0.5) + 0.5;
    const floor_height = preview.floorHeightAtCellCenter(global_row, (bounds.min + bounds.max) / 2) orelse 0.0;
    return worldPositionForColumn(center_col, row_index, width_offset, segment_start_z, cell_size, floor_height + y);
}

fn cellWorldPosition(
    col_index: usize,
    row_index: usize,
    width_offset: f32,
    segment_start_z: f32,
    cell_size: f32,
    y: f32,
) rl.Vector3 {
    return worldPositionForColumn(@as(f32, @floatFromInt(col_index)) + 0.5, row_index, width_offset, segment_start_z, cell_size, y);
}

fn worldPositionForColumn(
    column: f32,
    row_index: usize,
    width_offset: f32,
    segment_start_z: f32,
    cell_size: f32,
    y: f32,
) rl.Vector3 {
    return .{
        .x = (column - width_offset) * cell_size,
        .y = y,
        .z = segment_start_z + @as(f32, @floatFromInt(row_index)) * cell_size + 0.5,
    };
}

fn drawRuntimeCellExposedEdges(edge_mask: u8, position: rl.Vector3, size: rl.Vector3, color: rl.Color) void {
    if (edge_mask == 0) return;

    const half_x = size.x * 0.5;
    const half_z = size.z * 0.5;
    const top_y = position.y + (size.y * 0.5) + 0.01;

    const front_left = rl.Vector3{ .x = position.x - half_x, .y = top_y, .z = position.z - half_z };
    const front_right = rl.Vector3{ .x = position.x + half_x, .y = top_y, .z = position.z - half_z };
    const back_left = rl.Vector3{ .x = position.x - half_x, .y = top_y, .z = position.z + half_z };
    const back_right = rl.Vector3{ .x = position.x + half_x, .y = top_y, .z = position.z + half_z };

    if ((edge_mask & 0x01) != 0) {
        rl.drawLine3D(front_left, front_right, color);
    }
    if ((edge_mask & 0x02) != 0) {
        rl.drawLine3D(back_left, back_right, color);
    }
    if ((edge_mask & 0x08) != 0) {
        rl.drawLine3D(front_left, back_left, color);
    }
    if ((edge_mask & 0x04) != 0) {
        rl.drawLine3D(front_right, back_right, color);
    }
}

fn applyAnnotationOffset(base: rl.Vector3, offset: segment.Vec3) rl.Vector3 {
    return .{
        .x = base.x + offset.x,
        .y = base.y + offset.y,
        .z = base.z + offset.z,
    };
}

fn guidanceBounds(row: segment.Row) ?LaneBounds {
    return pathBounds(row.cells) orelse traversableBounds(row.cells);
}

const RuntimeTileTransition = struct {
    current: u8,
    previous_override: ?u8 = null,
};

const RuntimeBuildConfig = struct {
    build_flags: u32,
    build_seed: u32,
    active_row_start: usize,
    active_row_end: usize,
};

const MathRandom = struct {
    state: u32,

    fn init(seed: u32) MathRandom {
        return .{ .state = seed };
    }

    fn nextInt15(self: *MathRandom) u32 {
        self.state = (self.state *% 0x343fd) +% 0x269ec3;
        return (self.state >> 16) & 0x7fff;
    }
};

const RuntimeBuildState = struct {
    build_flags: u32,
    math_random: MathRandom,
    mirror_state: bool = false,
    mirror_counter: u32 = 0,

    fn init(build_flags: u32, build_seed: u32) RuntimeBuildState {
        return .{
            .build_flags = build_flags,
            .math_random = MathRandom.init(build_seed),
        };
    }

    fn applyMirrorDecision(self: *RuntimeBuildState, decision: bool) bool {
        const previous_state = self.mirror_state;
        if (decision != previous_state) {
            self.mirror_counter += 1;
        } else {
            self.mirror_counter = 0;
        }
        if (self.mirror_counter < 4) {
            self.mirror_state = decision;
            return decision;
        }
        self.mirror_counter = 0;
        self.mirror_state = !decision;
        return self.mirror_state;
    }

    fn switchTrackMirror(self: *RuntimeBuildState) bool {
        const decision = self.math_random.nextInt15() >= 0x4000;
        return self.applyMirrorDecision(decision);
    }
};

fn beginRuntimeBuildSegment(build_state: *RuntimeBuildState, loaded_segment: segment.Definition) void {
    if (loaded_segment.rows.len == 0) return;
    // Windows advances the mirror selector when the builder rolls onto the next installed
    // segment span. In the current sequential preview build, that boundary is the authored
    // segment start.
    _ = build_state.switchTrackMirror();
}

const AttachmentSourceRowMirrorStateBuild = struct {
    states: []bool,
    final_random_state: u32,
};

fn buildRuntimeTileGrid(
    allocator: std.mem.Allocator,
    segments: []const segment.Definition,
    row_offsets: []const usize,
    total_rows: usize,
    max_width: usize,
    config: RuntimeBuildConfig,
) ![]u8 {
    const runtime_tiles = try allocator.alloc(u8, total_rows * max_width);
    @memset(runtime_tiles, 0);
    var build_state = RuntimeBuildState.init(config.build_flags, config.build_seed);

    for (segments, 0..) |loaded_segment, segment_index| {
        beginRuntimeBuildSegment(&build_state, loaded_segment);
        const row_base = row_offsets[segment_index];
        for (loaded_segment.rows, 0..) |row, row_index| {
            const global_row = row_base + row_index;
            const outside_active_rows = global_row < config.active_row_start or global_row >= config.active_row_end;
            for (row.cells, 0..) |cell, lane_index| {
                const normalized_cell = normalizeSegmentGlyphForTrackFlags(
                    cell,
                    build_state.build_flags,
                    build_state.mirror_state,
                    outside_active_rows,
                );
                if (normalized_cell == '@') {
                    _ = build_state.switchTrackMirror();
                }
                const previous_tile = if (global_row > 0 and lane_index < max_width)
                    runtime_tiles[runtimeTileIndex(max_width, global_row - 1, lane_index)]
                else
                    null;
                const transition = runtimeTileTransitionForNormalizedGlyph(normalized_cell, previous_tile);
                const tile_type = if (transition) |value| value.current else 0;
                runtime_tiles[runtimeTileIndex(max_width, global_row, lane_index)] = tile_type;

                if (transition) |value| {
                    if (value.previous_override) |previous_override| {
                        if (global_row > 0) {
                            runtime_tiles[runtimeTileIndex(max_width, global_row - 1, lane_index)] = previous_override;
                        }
                    }
                }
            }
        }
    }

    return runtime_tiles;
}

fn buildAttachmentSourceRowMirrorStates(
    allocator: std.mem.Allocator,
    segments: []const segment.Definition,
    row_offsets: []const usize,
    total_rows: usize,
    config: RuntimeBuildConfig,
) !AttachmentSourceRowMirrorStateBuild {
    const mirror_states = try allocator.alloc(bool, total_rows);
    @memset(mirror_states, false);
    var build_state = RuntimeBuildState.init(config.build_flags, config.build_seed);

    for (segments, 0..) |loaded_segment, segment_index| {
        beginRuntimeBuildSegment(&build_state, loaded_segment);
        const row_base = row_offsets[segment_index];
        for (loaded_segment.rows, 0..) |row, row_index| {
            const global_row = row_base + row_index;
            const outside_active_rows = global_row < config.active_row_start or global_row >= config.active_row_end;
            var recorded = false;
            for (row.cells, 0..) |cell, lane_index| {
                const normalized_cell = normalizeSegmentGlyphForTrackFlags(
                    cell,
                    build_state.build_flags,
                    build_state.mirror_state,
                    outside_active_rows,
                );
                if (normalized_cell == '@') {
                    _ = build_state.switchTrackMirror();
                }
                if (lane_index == 0) {
                    mirror_states[global_row] = build_state.mirror_state;
                    recorded = true;
                }
            }
            if (!recorded) {
                mirror_states[global_row] = build_state.mirror_state;
            }
        }
    }

    return .{
        .states = mirror_states,
        .final_random_state = build_state.math_random.state,
    };
}

fn runtimeFlagB40BaseForTile(tile_type: u8) bool {
    return tile_type != 0x00 and tile_type != 0x23;
}

fn isRuntimeFlagB40FloorCondenseTile(tile_type: u8) bool {
    return isFloorCacheRuntimeTileFamily(tile_type);
}

fn isRuntimeFlagB40SlideCondenseTile(tile_type: u8) bool {
    return isSlideRuntimeTileFamily(tile_type);
}

fn runtimeEdgeMaskGetsCornerVariantBit(edge_mask: u8) bool {
    return switch (edge_mask & 0x0f) {
        0x05, 0x06, 0x09, 0x0a => true,
        else => false,
    };
}

fn runtimeTileGetsCornerVariantBit(
    runtime_tiles: []const u8,
    total_rows: usize,
    max_width: usize,
    global_row: usize,
    lane_index: usize,
) bool {
    const tile_type = runtime_tiles[runtimeTileIndex(max_width, global_row, lane_index)];
    const edge_mask = runtimeOpenEdgeMask(runtime_tiles, total_rows, max_width, global_row, lane_index, tile_type);
    return runtimeEdgeMaskGetsCornerVariantBit(edge_mask);
}

fn runtimeFlagB40RunLength(
    runtime_tiles: []const u8,
    warn_surface_grid: []const bool,
    total_rows: usize,
    max_width: usize,
    global_row: usize,
    lane_index: usize,
) usize {
    const start_index = runtimeTileIndex(max_width, global_row, lane_index);
    const start_tile = runtime_tiles[start_index];
    var run_length: usize = 1;

    if (start_tile == 0x0e) {
        while (lane_index + run_length < max_width) : (run_length += 1) {
            const next_tile = runtime_tiles[runtimeTileIndex(max_width, global_row, lane_index + run_length)];
            if (next_tile != 0x0e) break;
        }
        return run_length;
    }

    if (isRuntimeFlagB40FloorCondenseTile(start_tile)) {
        if (warn_surface_grid[start_index] or runtimeTileGetsCornerVariantBit(runtime_tiles, total_rows, max_width, global_row, lane_index)) {
            return 1;
        }
        while (lane_index + run_length < max_width) : (run_length += 1) {
            const next_index = runtimeTileIndex(max_width, global_row, lane_index + run_length);
            const next_tile = runtime_tiles[next_index];
            if (!isRuntimeFlagB40FloorCondenseTile(next_tile)) break;
            if (warn_surface_grid[next_index]) break;
            if (runtimeTileGetsCornerVariantBit(runtime_tiles, total_rows, max_width, global_row, lane_index + run_length)) break;
        }
        return run_length;
    }

    if (isRuntimeFlagB40SlideCondenseTile(start_tile)) {
        if (warn_surface_grid[start_index] or runtimeTileGetsCornerVariantBit(runtime_tiles, total_rows, max_width, global_row, lane_index)) {
            return 1;
        }
        while (lane_index + run_length < max_width) : (run_length += 1) {
            const next_index = runtimeTileIndex(max_width, global_row, lane_index + run_length);
            const next_tile = runtime_tiles[next_index];
            if (!isRuntimeFlagB40SlideCondenseTile(next_tile)) break;
            if (warn_surface_grid[next_index]) break;
            if (runtimeTileGetsCornerVariantBit(runtime_tiles, total_rows, max_width, global_row, lane_index + run_length)) break;
        }
        return run_length;
    }

    return run_length;
}

fn buildRuntimeFlagB40Grid(
    allocator: std.mem.Allocator,
    runtime_tiles: []const u8,
    warn_surface_grid: []const bool,
    total_rows: usize,
    max_width: usize,
) ![]bool {
    const flag_grid = try allocator.alloc(bool, total_rows * max_width);
    @memset(flag_grid, false);

    for (0..total_rows) |global_row| {
        var lane_index: usize = 0;
        while (lane_index < max_width) {
            const current_index = runtimeTileIndex(max_width, global_row, lane_index);
            const tile_type = runtime_tiles[current_index];
            flag_grid[current_index] = runtimeFlagB40BaseForTile(tile_type);
            if (!flag_grid[current_index]) {
                lane_index += 1;
                continue;
            }

            // Windows seeds `flags_b & 0x40` broadly and then clears it on horizontal
            // follower cells during `CondenseTrack`.
            const run_length = runtimeFlagB40RunLength(
                runtime_tiles,
                warn_surface_grid,
                total_rows,
                max_width,
                global_row,
                lane_index,
            );
            if (run_length > 1) {
                for (1..run_length) |offset| {
                    flag_grid[current_index + offset] = false;
                }
            }
            lane_index += run_length;
        }
    }

    return flag_grid;
}

fn runtimeRowFlagsForRow(row: segment.Row) u32 {
    var flags: u32 = 0;
    if (row.marked) {
        flags |= 0x04;
    }

    if (row.annotation) |annotation| {
        switch (annotation) {
            .path => flags |= 0x08,
            .ring => |ring_kind| {
                flags |= switch (ring_kind) {
                    .none => runtime_row_flag_ring_none,
                    .normal => runtime_row_flag_ring_normal,
                    .powerup => runtime_row_flag_ring_powerup,
                    .explode => runtime_row_flag_ring_explode,
                    .slow => runtime_row_flag_ring_slow,
                };
            },
            .parcel => flags |= 0x01,
            .model => flags |= 0x02,
            .jetpack_off => flags |= runtime_row_flag_jetpack_off,
            .no_fall => flags |= runtime_row_flag_no_fall,
        }
    }

    return flags;
}

fn buildRuntimeRowFlags(
    allocator: std.mem.Allocator,
    segments: []const segment.Definition,
    row_offsets: []const usize,
    total_rows: usize,
) ![]u32 {
    const row_flags = try allocator.alloc(u32, total_rows);
    @memset(row_flags, 0);

    for (segments, 0..) |loaded_segment, segment_index| {
        const row_base = row_offsets[segment_index];
        for (loaded_segment.rows, 0..) |row, row_index| {
            row_flags[row_base + row_index] = runtimeRowFlagsForRow(row);
        }
    }

    return row_flags;
}

fn buildRuntimeRowRingSpeeds(
    allocator: std.mem.Allocator,
    segments: []const segment.Definition,
    row_offsets: []const usize,
    total_rows: usize,
) ![]f32 {
    const ring_speeds = try allocator.alloc(f32, total_rows);
    @memset(ring_speeds, 0.0);

    for (segments, 0..) |loaded_segment, segment_index| {
        const row_base = row_offsets[segment_index];
        for (loaded_segment.rows, 0..) |row, row_index| {
            ring_speeds[row_base + row_index] = row.ring_speed orelse 0.0;
        }
    }

    return ring_speeds;
}

fn setRuntimeRingEffectKind(
    ring_effect_kinds: []u8,
    max_width: usize,
    total_rows: usize,
    global_row: usize,
    lane_index: usize,
    kind: u8,
) void {
    if (global_row >= total_rows or lane_index >= max_width or kind == 0) return;
    ring_effect_kinds[runtimeTileIndex(max_width, global_row, lane_index)] = kind;
}

fn buildRuntimeRingEffectGrid(
    allocator: std.mem.Allocator,
    runtime_tiles: []const u8,
    runtime_row_flags: []const u32,
    total_rows: usize,
    max_width: usize,
    build_flags: u32,
) ![]u8 {
    const ring_effect_kinds = try allocator.alloc(u8, total_rows * max_width);
    @memset(ring_effect_kinds, 0);
    const tutorial_default_rings = build_flags == tutorialRuntimeBuildFlags;

    for (0..total_rows) |global_row| {
        const row_flags = runtime_row_flags[global_row];
        for (0..max_width) |lane_index| {
            const tile_type = runtime_tiles[runtimeTileIndex(max_width, global_row, lane_index)];
            switch (tile_type) {
                0x23 => {
                    if ((row_flags & runtime_row_flag_ring_normal) != 0) {
                        setRuntimeRingEffectKind(ring_effect_kinds, max_width, total_rows, global_row, lane_index, 5);
                    } else if ((row_flags & runtime_row_flag_ring_powerup) != 0) {
                        setRuntimeRingEffectKind(ring_effect_kinds, max_width, total_rows, global_row, lane_index, 8);
                    } else if ((row_flags & runtime_row_flag_ring_explode) != 0) {
                        setRuntimeRingEffectKind(ring_effect_kinds, max_width, total_rows, global_row, lane_index, 6);
                    } else if ((row_flags & runtime_row_flag_ring_slow) != 0) {
                        setRuntimeRingEffectKind(ring_effect_kinds, max_width, total_rows, global_row, lane_index, 7);
                    }
                },
                0x02, 0x03, 0x04, 0x05, 0x06, 0x07 => {
                    const target_row = global_row + ramp_special_ring_forward_row_offset;
                    if ((row_flags & runtime_row_flag_ring_powerup) != 0) {
                        setRuntimeRingEffectKind(ring_effect_kinds, max_width, total_rows, target_row, lane_index, 8);
                    } else if ((row_flags & runtime_row_flag_ring_explode) != 0) {
                        setRuntimeRingEffectKind(ring_effect_kinds, max_width, total_rows, target_row, lane_index, 6);
                    } else if ((row_flags & runtime_row_flag_ring_slow) != 0) {
                        setRuntimeRingEffectKind(ring_effect_kinds, max_width, total_rows, target_row, lane_index, 7);
                    } else if (tutorial_default_rings and (row_flags & runtime_row_flag_ring_none) == 0 and (tile_type == 0x02 or tile_type == 0x03 or tile_type == 0x04)) {
                        setRuntimeRingEffectKind(ring_effect_kinds, max_width, total_rows, global_row + ramp_default_ring_forward_row_offset, lane_index, 4);
                    }
                },
                0x08, 0x09, 0x0a => {
                    if ((row_flags & runtime_row_flag_ring_explode) != 0) {
                        setRuntimeRingEffectKind(ring_effect_kinds, max_width, total_rows, global_row + ramp_explode_ring_forward_row_offset, lane_index, 2);
                    } else if (tutorial_default_rings and (row_flags & runtime_row_flag_ring_none) == 0) {
                        setRuntimeRingEffectKind(ring_effect_kinds, max_width, total_rows, global_row + ramp_explode_ring_forward_row_offset, lane_index, 2);
                    }
                },
                else => {},
            }
        }
    }

    return ring_effect_kinds;
}

fn seedsRuntimeWarningZone(tile_type: u8) bool {
    return switch (tile_type) {
        0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x17, 0x19, 0x21 => true,
        else => false,
    };
}

fn buildRuntimeWarningZoneGrid(
    allocator: std.mem.Allocator,
    runtime_tiles: []const u8,
    total_rows: usize,
    max_width: usize,
) ![]bool {
    const flag_grid = try allocator.alloc(bool, total_rows * max_width);
    @memset(flag_grid, false);

    if (total_rows <= 1 or max_width == 0) return flag_grid;

    // PORT(verified): `mark_track_warning_zones` marks a 6-row by 2-lane footprint
    // behind each recovered warning seed tile. The footprint includes the seed lane and
    // its left neighbor, and it never writes into the terminal runtime row.
    for (0..total_rows - 1) |global_row| {
        for (0..max_width) |lane_index| {
            const tile_type = runtime_tiles[runtimeTileIndex(max_width, global_row, lane_index)];
            if (!seedsRuntimeWarningZone(tile_type)) continue;

            const min_row = global_row + 1 -| 6;
            for (min_row..global_row + 1) |marked_row| {
                if (lane_index > 0) {
                    flag_grid[runtimeTileIndex(max_width, marked_row, lane_index - 1)] = true;
                }
                flag_grid[runtimeTileIndex(max_width, marked_row, lane_index)] = true;
            }
        }
    }

    return flag_grid;
}

fn renderCacheWarnSurfaceEligibleTile(tile_type: u8) bool {
    return isFloorCacheRuntimeTileFamily(tile_type) or isSlideRuntimeTileFamily(tile_type);
}

fn buildRenderCacheWarnSurfaceGrid(
    allocator: std.mem.Allocator,
    runtime_tiles: []const u8,
    total_rows: usize,
    max_width: usize,
) ![]bool {
    const flag_grid = try allocator.alloc(bool, total_rows * max_width);
    @memset(flag_grid, false);

    if (total_rows <= 1 or max_width == 0) return flag_grid;

    // PORT(partial): `promote_track_tiles_to_fringe_variants` swaps selected floor/slide
    // meshes into a warn-surface family when the runtime cell directly below is open.
    // Static asset-init recovery now confirms both replacement tables route into the shared
    // TRACKWARN asset family; the remaining gap is exact BOD-object eligibility, not whether
    // promoted floor vs slide cells use different texture families.
    for (0..total_rows - 1) |global_row| {
        for (0..max_width) |lane_index| {
            const current_index = runtimeTileIndex(max_width, global_row, lane_index);
            const below_index = runtimeTileIndex(max_width, global_row + 1, lane_index);
            const current_tile = runtime_tiles[current_index];
            const below_tile = runtime_tiles[below_index];
            flag_grid[current_index] =
                renderCacheWarnSurfaceEligibleTile(current_tile) and
                isOpenNeighborRuntimeTileFamily(below_tile);
        }
    }

    return flag_grid;
}

fn maybeMarkRuntimeSurfaceSwap(
    swap_grid: []bool,
    runtime_tiles: []const u8,
    warn_surface_grid: []const bool,
    max_width: usize,
    current_row: usize,
    lane_index: usize,
    neighbor_row: usize,
    special_floor_tile: ?u8,
) void {
    const current_index = runtimeTileIndex(max_width, current_row, lane_index);
    const neighbor_index = runtimeTileIndex(max_width, neighbor_row, lane_index);
    if (warn_surface_grid[current_index] or warn_surface_grid[neighbor_index]) return;

    const current_tile = runtime_tiles[current_index];
    const neighbor_tile = runtime_tiles[neighbor_index];

    if (isSlideRuntimeTileFamily(current_tile) and
        (isFloorCacheRuntimeTileFamily(neighbor_tile) or
            (special_floor_tile != null and neighbor_tile == special_floor_tile.?)))
    {
        swap_grid[current_index] = true;
        return;
    }

    if (isFloorCacheRuntimeTileFamily(current_tile) and isSlideRuntimeTileFamily(neighbor_tile)) {
        swap_grid[current_index] = true;
    }
}

fn buildRenderCacheSurfaceSwapGrid(
    allocator: std.mem.Allocator,
    runtime_tiles: []const u8,
    warn_surface_grid: []const bool,
    total_rows: usize,
    max_width: usize,
) ![]bool {
    const swap_grid = try allocator.alloc(bool, total_rows * max_width);
    @memset(swap_grid, false);

    if (max_width <= 3 or total_rows == 0) return swap_grid;

    // PORT(partial): `harmonize_center_lane_floor_slide_variants` only touches two
    // center-seam lanes. Native keys the swap from promoted warn-surface bits plus a
    // small pair of special neighbor tile ids; the port mirrors that recovered layout.
    if (max_width > 3 and total_rows > 1) {
        for (0..total_rows - 1) |global_row| {
            maybeMarkRuntimeSurfaceSwap(
                swap_grid,
                runtime_tiles,
                warn_surface_grid,
                max_width,
                global_row,
                3,
                global_row + 1,
                0x1e,
            );
        }
    }

    if (max_width > 5 and total_rows > 1) {
        for (1..total_rows) |global_row| {
            maybeMarkRuntimeSurfaceSwap(
                swap_grid,
                runtime_tiles,
                warn_surface_grid,
                max_width,
                global_row,
                5,
                global_row - 1,
                0x20,
            );
        }
    }

    return swap_grid;
}

fn buildRuntimeFlagB80Grid(
    allocator: std.mem.Allocator,
    segments: []const segment.Definition,
    row_offsets: []const usize,
    total_rows: usize,
    max_width: usize,
) ![]bool {
    const flag_grid = try allocator.alloc(bool, total_rows * max_width);
    @memset(flag_grid, false);

    for (segments, 0..) |loaded_segment, segment_index| {
        const row_base = row_offsets[segment_index];
        for (loaded_segment.rows, 0..) |row, row_index| {
            const annotation = row.annotation orelse continue;
            if (annotation.tag() != .jetpack_off) continue;

            const global_row = row_base + row_index;
            for (row.cells, 0..) |_, lane_index| {
                flag_grid[runtimeTileIndex(max_width, global_row, lane_index)] = true;
            }
        }
    }

    return flag_grid;
}

fn buildRuntimeFlagB01Grid(
    allocator: std.mem.Allocator,
    segments: []const segment.Definition,
    row_offsets: []const usize,
    total_rows: usize,
    max_width: usize,
) ![]bool {
    const flag_grid = try allocator.alloc(bool, total_rows * max_width);
    @memset(flag_grid, false);

    for (segments, 0..) |loaded_segment, segment_index| {
        const row_base = row_offsets[segment_index];
        for (loaded_segment.rows, 0..) |row, row_index| {
            const annotation = row.annotation orelse continue;
            if (annotation.tag() != .no_fall) continue;

            const global_row = row_base + row_index;
            for (row.cells, 0..) |_, lane_index| {
                flag_grid[runtimeTileIndex(max_width, global_row, lane_index)] = true;
            }
        }
    }

    return flag_grid;
}

const ParcelRowLocation = struct {
    segment_index: usize,
    row_index: usize,
};

fn countActiveParcelAnnotations(segments: []const segment.Definition) usize {
    var count: usize = 0;
    for (segments) |loaded_segment| {
        for (loaded_segment.rows) |row| {
            const annotation = row.annotation orelse continue;
            if (annotation.tag() == .parcel) {
                count += 1;
            }
        }
    }
    return count;
}

fn nextMathRandomScaledIndex(random_state: *u32, upper_bound: usize) usize {
    if (upper_bound <= 1) return 0;
    random_state.* = (random_state.* *% 0x343fd) +% 0x269ec3;
    const random_value = (random_state.* >> 16) & 0x7fff;
    const scaled = @as(f32, @floatFromInt(random_value)) *
        @as(f32, @floatFromInt(upper_bound)) * 0.0000305175781;
    return @min(@as(usize, @intFromFloat(scaled)), upper_bound - 1);
}

fn buildRuntimeEdgeMaskGrid(
    allocator: std.mem.Allocator,
    runtime_tiles: []const u8,
    total_rows: usize,
    max_width: usize,
) ![]u8 {
    const edge_masks = try allocator.alloc(u8, total_rows * max_width);
    @memset(edge_masks, 0);

    for (0..total_rows) |global_row| {
        for (0..max_width) |lane_index| {
            const tile_type = runtime_tiles[runtimeTileIndex(max_width, global_row, lane_index)];
            edge_masks[runtimeTileIndex(max_width, global_row, lane_index)] = runtimeOpenEdgeMask(
                runtime_tiles,
                total_rows,
                max_width,
                global_row,
                lane_index,
                tile_type,
            );
        }
    }

    return edge_masks;
}

fn buildRuntimeSpawnHintGrid(
    allocator: std.mem.Allocator,
    runtime_tiles: []const u8,
    runtime_warning_zone_grid: []const bool,
    total_rows: usize,
    max_width: usize,
    build_flags: u32,
) ![]u8 {
    const spawn_hints = try allocator.alloc(u8, total_rows * max_width);
    @memset(spawn_hints, 0);

    for (0..total_rows) |global_row| {
        for (0..max_width) |lane_index| {
            const index = runtimeTileIndex(max_width, global_row, lane_index);
            const tile_type = runtime_tiles[index];
            var mask = runtimeFallbackSpawnHintMask(tile_type, build_flags);
            if (runtime_warning_zone_grid[index]) {
                // PORT(verified): `mark_track_warning_zones` feeds live fallback-hazard
                // suppression in `update_subgame`. Generic garbage/salt spawns on
                // `0x01/0x15/0x0f` cells are blocked when the runtime cell carries the
                // warning footprint bits, while explicit authored hazard tiles still use
                // their own direct spawn lanes.
                mask = 0;
            }
            spawn_hints[index] = mask;
        }
    }

    return spawn_hints;
}

fn runtimeTileIndex(max_width: usize, global_row: usize, lane_index: usize) usize {
    return (global_row * max_width) + lane_index;
}

fn runtimeOpenEdgeMask(
    runtime_tiles: []const u8,
    total_rows: usize,
    max_width: usize,
    global_row: usize,
    lane_index: usize,
    tile_type: u8,
) u8 {
    if (tile_type == 0x00 or tile_type == 0x0e or tile_type == 0x1c or tile_type == 0x1d or tile_type == 0x1e or tile_type == 0x23) {
        return 0;
    }

    var mask: u8 = 0;
    if (lane_index == 0 or isRuntimeEdgeNeighborOpen(runtime_tiles, total_rows, max_width, global_row, lane_index - 1)) {
        mask |= 0x08;
    }
    if (lane_index + 1 >= max_width or isRuntimeEdgeNeighborOpen(runtime_tiles, total_rows, max_width, global_row, lane_index + 1)) {
        mask |= 0x04;
    }
    if (global_row == 0 or isRuntimeEdgeNeighborOpen(runtime_tiles, total_rows, max_width, global_row - 1, lane_index)) {
        mask |= 0x01;
    }
    if (global_row + 1 >= total_rows or isRuntimeEdgeNeighborOpen(runtime_tiles, total_rows, max_width, global_row + 1, lane_index)) {
        mask |= 0x02;
    }
    if (runtimeEdgeMaskGetsCornerVariantBit(mask)) {
        mask |= 0x80;
    }
    return mask;
}

fn isRuntimeEdgeNeighborOpen(
    runtime_tiles: []const u8,
    total_rows: usize,
    max_width: usize,
    global_row: usize,
    lane_index: usize,
) bool {
    if (global_row >= total_rows or lane_index >= max_width) return true;
    const tile_type = runtime_tiles[runtimeTileIndex(max_width, global_row, lane_index)];
    return isOpenNeighborRuntimeTileFamily(tile_type);
}

fn runtimeFallbackSpawnHintMask(tile_type: u8, build_flags: u32) u8 {
    var mask: u8 = 0;
    if ((build_flags & 0x2) != 0) {
        switch (tile_type) {
            0x01, 0x15 => mask |= runtime_spawn_hint_garbage_fallback,
            else => {},
        }
    }
    if ((build_flags & 0x10000) != 0) {
        switch (tile_type) {
            0x01, 0x0f => mask |= runtime_spawn_hint_salt_fallback,
            else => {},
        }
    }
    return mask;
}

fn runtimeGarbageFallbackNeighborAllowed(tile_type: u8) bool {
    return switch (tile_type) {
        0x01, 0x14, 0x15, 0x20 => true,
        else => false,
    };
}

fn normalizeSegmentGlyphForTrackFlags(cell: u8, build_flags: u32, mirror_state: bool, outside_active_rows: bool) u8 {
    return switch (cell) {
        ' ' => if ((build_flags & 0x400) == 0)
            ','
        else if ((build_flags & 0x1) == 0)
            '.'
        else
            cell,
        '$' => if ((build_flags & 0x800) == 0)
            if ((build_flags & 0x40) != 0) '_' else '.'
        else
            cell,
        '-' => if ((build_flags & 0x40) == 0) '.' else cell,
        '<', '>' => if ((build_flags & 0x200) == 0) '.' else cell,
        '=' => if ((build_flags & 0x100) != 0)
            cell
        else if ((build_flags & 0x1) == 0)
            '.'
        else if ((build_flags & 0x400) != 0)
            ' '
        else
            ',',
        '[' => if ((build_flags & 0x200) == 0)
            '.'
        else if ((build_flags & 0x20) == 0)
            '<'
        else if (mirror_state)
            '['
        else
            cell,
        ']' => if ((build_flags & 0x200) == 0)
            '.'
        else if ((build_flags & 0x20) == 0)
            '<'
        else if (mirror_state)
            '{'
        else
            cell,
        '_' => if ((build_flags & 0x40) != 0 or outside_active_rows) cell else '.',
        'o' => if ((build_flags & 0x4) == 0)
            if ((build_flags & 0x40) != 0) '_' else '.'
        else
            cell,
        '{' => if ((build_flags & 0x200) == 0)
            '.'
        else if ((build_flags & 0x20) == 0)
            '>'
        else if (mirror_state)
            '}'
        else
            cell,
        '|' => if ((build_flags & 0x100) != 0)
            cell
        else if ((build_flags & 0x1) == 0)
            ' '
        else if ((build_flags & 0x400) != 0)
            '='
        else
            ',',
        '}' => if ((build_flags & 0x200) == 0)
            '.'
        else if ((build_flags & 0x20) == 0)
            '>'
        else if (mirror_state)
            '['
        else
            cell,
        else => cell,
    };
}

fn runtimeTileTransitionForShippedGlyph(cell: u8, previous_tile: ?u8) ?RuntimeTileTransition {
    return runtimeTileTransitionForNormalizedGlyph(cell, previous_tile);
}

fn runtimeTileTransitionForNormalizedGlyph(cell: u8, previous_tile: ?u8) ?RuntimeTileTransition {
    return switch (cell) {
        ' ', '@' => .{ .current = 0x00 },
        ',' => .{ .current = 0x1c },
        '#' => .{ .current = 0x20 },
        '$' => .{ .current = 0x17 },
        '&' => .{ .current = 0x22 },
        '(' => .{ .current = 0x16 },
        '-' => .{ .current = 0x15 },
        '.' => .{ .current = 0x01 },
        '0', '1', '2', '3' => .{ .current = 0x0f },
        '<' => .{ .current = 0x06 },
        '=' => .{ .current = 0x0e },
        '>' => if (previous_tile == 0x03)
            .{ .current = 0x09 }
        else
            .{ .current = 0x03, .previous_override = if (previous_tile != null) 0x0c else null },
        'J' => .{ .current = 0x19 },
        'M' => .{ .current = 0x12 },
        'o' => .{ .current = 0x10 },
        'P' => .{ .current = 0x1e },
        'R' => .{ .current = 0x23 },
        '[' => .{ .current = 0x05 },
        '_' => .{ .current = 0x0f },
        'p' => .{ .current = 0x1d },
        's' => .{ .current = 0x21 },
        '{' => if (previous_tile == 0x03)
            .{ .current = 0x08 }
        else
            .{ .current = 0x02, .previous_override = if (previous_tile != null) 0x0b else null },
        '|' => .{ .current = 0x0e },
        '}' => if (previous_tile == 0x03)
            .{ .current = 0x0a }
        else
            .{ .current = 0x04, .previous_override = if (previous_tile != null) 0x0d else null },
        else => null,
    };
}

fn traversableBounds(cells: []const u8) ?LaneBounds {
    var min_index: ?usize = null;
    var max_index: usize = 0;
    for (cells, 0..) |cell, index| {
        if (!isTraversable(cell)) continue;
        if (min_index == null) min_index = index;
        max_index = index;
    }

    if (min_index == null) return null;
    return .{ .min = min_index.?, .max = max_index };
}

fn pathBounds(cells: []const u8) ?LaneBounds {
    var min_index: ?usize = null;
    var max_index: usize = 0;
    for (cells, 0..) |cell, index| {
        if (!isPathCell(cell)) continue;
        if (min_index == null) min_index = index;
        max_index = index;
    }

    if (min_index == null) return null;
    return .{ .min = min_index.?, .max = max_index };
}

fn isTraversable(cell: u8) bool {
    return cell != '@';
}

fn isPathCell(cell: u8) bool {
    return cell == 'P' or cell == 'p';
}

fn isRingCell(cell: u8) bool {
    return switch (cell) {
        '>', '<', '{', '}', ';', 'R' => true,
        else => false,
    };
}

pub fn gameplayCellKind(cell: u8) ?GameplayCellKind {
    return switch (cell) {
        'p' => .attachment_probe,
        'P' => .attachment_entry,
        '>', '<', '{', '}', ';', 'R' => .ring,
        '(' => .trampoline,
        'M' => .slug,
        's' => .garbage,
        '&' => .salt,
        '$' => .health,
        'J' => .jetpack,
        else => null,
    };
}

pub fn runtimeGameplayCellKindForTile(tile_type: u8, build_flags: u32) ?GameplayCellKind {
    return switch (tile_type) {
        0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x23 => .ring,
        0x12 => if ((build_flags & 0x80) != 0) .slug else null,
        0x16 => .trampoline,
        0x17 => .health,
        0x19 => .jetpack,
        0x1d => .attachment_probe,
        0x1e => .attachment_entry,
        0x21 => .garbage,
        0x22 => .salt,
        else => null,
    };
}

pub fn gameplayCellKindForRuntimeTile(tile_type: u8) ?GameplayCellKind {
    return runtimeGameplayCellKindForTile(tile_type, defaultRuntimeBuildFlags);
}

fn gameplayCellColor(kind: GameplayCellKind) rl.Color {
    return switch (kind) {
        .attachment_probe => .blue,
        .attachment_entry => .sky_blue,
        .ring => .yellow,
        .trampoline => .pink,
        .slug => .red,
        .garbage => .gray,
        .salt => .sky_blue,
        .health => .green,
        .jetpack => .orange,
    };
}

fn gameplayCellY(kind: GameplayCellKind) f32 {
    return switch (kind) {
        .attachment_probe, .attachment_entry, .ring => 0.62,
        .trampoline => 0.18,
        .slug => 0.62,
        .garbage => 0.56,
        .salt => 0.62,
        .health => 0.7,
        .jetpack => 0.82,
    };
}

fn colorForAnnotation(annotation: segment.Annotation) rl.Color {
    return switch (annotation) {
        .path => .gold,
        .ring => |ring| switch (ring) {
            .none => .gray,
            .normal => .yellow,
            .powerup => .green,
            .explode => .orange,
            .slow => .purple,
        },
        .parcel => .green,
        .model => .purple,
        .jetpack_off => .red,
        .no_fall => .sky_blue,
    };
}

fn colorForCell(cell: u8) rl.Color {
    return switch (cell) {
        '@' => .dark_blue,
        '_' => .gray,
        '.' => .light_gray,
        'P' => .sky_blue,
        '#' => .orange,
        's' => .white,
        '>' => .gold,
        '{', '}', ';' => .yellow,
        '[', 'M', 'R', 'J' => .red,
        '~' => .green,
        '$', '&', '(', ')', '-', '<', '=', '0', '1', '2', '3', '|', 'p' => .purple,
        ' ' => .dark_gray,
        else => .dark_purple,
    };
}

fn tintForSelection(base: rl.Color, is_selected: bool) rl.Color {
    if (!is_selected) return base;
    return .{
        .r = @intCast(@min(@as(u16, base.r) + 30, 255)),
        .g = @intCast(@min(@as(u16, base.g) + 20, 255)),
        .b = @intCast(@min(@as(u16, base.b) + 10, 255)),
        .a = base.a,
    };
}

test "load tutorial level preview" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const level_entry = catalog.level_entries[catalog.findLevelIndex("LEVELS/TUTORIAL.TXT").?];
    var level_definition = try level.loadFromArchive(std.testing.allocator, &catalog, level_entry);
    defer level_definition.deinit();

    var preview = try LoadedLevelPreview.load(std.testing.allocator, &catalog, &level_definition);
    defer preview.deinit();

    try std.testing.expectEqual(
        @as(usize, level_definition.first_segments.len + level_definition.segments.len + level_definition.last_segments.len),
        preview.segments.len,
    );
    try std.testing.expectEqualStrings("Start", preview.segments[0].name);
    try std.testing.expectEqual(@as(?usize, null), preview.segment_logical_indices[0]);
    try std.testing.expectEqual(@as(?usize, 0), preview.segment_logical_indices[level_definition.first_segments.len]);
    try std.testing.expect(preview.total_rows > 0);
    const first_row = preview.locateRow(0).?;
    try std.testing.expectEqual(@as(usize, 0), first_row.segment_index);
    try std.testing.expectEqual(@as(usize, 0), first_row.row_index);
    try std.testing.expect(preview.cellAt(0, 0) != null);
}

test "challenge preview counts live parcel rows instead of level metadata" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const level_entry = catalog.level_entries[catalog.findLevelIndex("LEVELS/CHALLENGE000.TXT").?];
    var level_definition = try level.loadFromArchive(std.testing.allocator, &catalog, level_entry);
    defer level_definition.deinit();

    try std.testing.expectEqual(@as(?usize, 0), level_definition.parcels);

    var preview = try LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &level_definition,
        .{ .load_models = false },
    );
    defer preview.deinit();

    try std.testing.expect(preview.parcel_target_count > 0);
    try std.testing.expectEqual(preview.parcel_target_count, preview.activeParcelCount());
}

test "challenge parcel trim reduces live parcel rows to the requested target" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const level_entry = catalog.level_entries[catalog.findLevelIndex("LEVELS/CHALLENGE000.TXT").?];
    var level_definition = try level.loadFromArchive(std.testing.allocator, &catalog, level_entry);
    defer level_definition.deinit();

    var preview = try LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &level_definition,
        .{ .load_models = false },
    );
    defer preview.deinit();

    const initial_count = preview.parcel_target_count;
    try std.testing.expect(initial_count > 5);

    var random_state = preview.runtime_build_final_random_state;
    const kept_count = try preview.trimParcelAnnotationsToTarget(&random_state, 5);
    try std.testing.expectEqual(@as(usize, 5), kept_count);
    try std.testing.expectEqual(@as(usize, 5), preview.parcel_target_count);
    try std.testing.expectEqual(@as(usize, 5), preview.activeParcelCount());
}

test "resolve segment x model path" {
    const resolved = try resolveSegmentModelArchivePath(std.testing.allocator, "signBang.x");
    defer std.testing.allocator.free(resolved);

    try std.testing.expectEqualStrings("X/SIGNBANG.X2", resolved);
}

test "gameplay cell kinds match recovered runtime glyph semantics" {
    try std.testing.expectEqual(GameplayCellKind.attachment_entry, gameplayCellKind('P').?);
    try std.testing.expectEqual(GameplayCellKind.attachment_probe, gameplayCellKind('p').?);
    try std.testing.expectEqual(GameplayCellKind.trampoline, gameplayCellKind('(').?);
    try std.testing.expectEqual(GameplayCellKind.health, gameplayCellKind('$').?);
    try std.testing.expectEqual(GameplayCellKind.jetpack, gameplayCellKind('J').?);
    try std.testing.expectEqual(GameplayCellKind.slug, gameplayCellKind('M').?);
    try std.testing.expectEqual(GameplayCellKind.garbage, gameplayCellKind('s').?);
    try std.testing.expectEqual(GameplayCellKind.salt, gameplayCellKind('&').?);
    try std.testing.expectEqual(@as(?GameplayCellKind, null), gameplayCellKind('0'));
    try std.testing.expectEqual(@as(?GameplayCellKind, null), gameplayCellKind('='));
    try std.testing.expectEqual(@as(?GameplayCellKind, null), gameplayCellKind('['));
}

test "confirmed runtime tile hints match recovered gameplay tiles" {
    try std.testing.expectEqual(@as(?u8, 0x01), confirmedRuntimeTileHint('.'));
    try std.testing.expectEqual(@as(?u8, 0x0f), confirmedRuntimeTileHint('_'));
    try std.testing.expectEqual(@as(?u8, 0x0e), confirmedRuntimeTileHint('|'));
    try std.testing.expectEqual(@as(?u8, 0x16), confirmedRuntimeTileHint('('));
    try std.testing.expectEqual(@as(?u8, 0x15), confirmedRuntimeTileHint('-'));
    try std.testing.expectEqual(@as(?u8, 0x1e), confirmedRuntimeTileHint('P'));
    try std.testing.expectEqual(@as(?u8, 0x1d), confirmedRuntimeTileHint('p'));
    try std.testing.expectEqual(@as(?u8, 0x17), confirmedRuntimeTileHint('$'));
    try std.testing.expectEqual(@as(?u8, 0x19), confirmedRuntimeTileHint('J'));
    try std.testing.expectEqual(@as(?u8, 0x12), confirmedRuntimeTileHint('M'));
    try std.testing.expectEqual(@as(?u8, 0x22), confirmedRuntimeTileHint('&'));
    try std.testing.expectEqual(@as(?u8, 0x23), confirmedRuntimeTileHint('R'));
    try std.testing.expectEqual(@as(?u8, 0x21), confirmedRuntimeTileHint('s'));
    try std.testing.expectEqual(@as(?u8, null), confirmedRuntimeTileHint('#'));
}

test "runtime tile transitions match recovered shipped glyph mapping" {
    try std.testing.expectEqualDeep(
        RuntimeTileTransition{ .current = 0x03, .previous_override = 0x0c },
        runtimeTileTransitionForShippedGlyph('>', 0x00).?,
    );
    try std.testing.expectEqualDeep(
        RuntimeTileTransition{ .current = 0x09 },
        runtimeTileTransitionForShippedGlyph('>', 0x03).?,
    );
    try std.testing.expectEqualDeep(
        RuntimeTileTransition{ .current = 0x02, .previous_override = 0x0b },
        runtimeTileTransitionForShippedGlyph('{', 0x00).?,
    );
    try std.testing.expectEqualDeep(
        RuntimeTileTransition{ .current = 0x08 },
        runtimeTileTransitionForShippedGlyph('{', 0x03).?,
    );
    try std.testing.expectEqualDeep(
        RuntimeTileTransition{ .current = 0x04, .previous_override = 0x0d },
        runtimeTileTransitionForShippedGlyph('}', 0x00).?,
    );
    try std.testing.expectEqualDeep(
        RuntimeTileTransition{ .current = 0x0a },
        runtimeTileTransitionForShippedGlyph('}', 0x03).?,
    );
    try std.testing.expectEqualDeep(
        RuntimeTileTransition{ .current = 0x20 },
        runtimeTileTransitionForShippedGlyph('#', null).?,
    );
    try std.testing.expectEqualDeep(
        RuntimeTileTransition{ .current = 0x16 },
        runtimeTileTransitionForShippedGlyph('(', null).?,
    );
    try std.testing.expectEqualDeep(
        RuntimeTileTransition{ .current = 0x05 },
        runtimeTileTransitionForShippedGlyph('[', null).?,
    );
    try std.testing.expectEqualDeep(
        RuntimeTileTransition{ .current = 0x1c },
        runtimeTileTransitionForNormalizedGlyph(',', null).?,
    );
    try std.testing.expectEqualDeep(
        RuntimeTileTransition{ .current = 0x10 },
        runtimeTileTransitionForNormalizedGlyph('o', null).?,
    );
}

test "runtime tile kinds map to recovered gameplay families" {
    try std.testing.expectEqual(GameplayCellKind.attachment_probe, gameplayCellKindForRuntimeTile(0x1d).?);
    try std.testing.expectEqual(GameplayCellKind.attachment_entry, gameplayCellKindForRuntimeTile(0x1e).?);
    try std.testing.expectEqual(GameplayCellKind.trampoline, gameplayCellKindForRuntimeTile(0x16).?);
    try std.testing.expectEqual(GameplayCellKind.health, gameplayCellKindForRuntimeTile(0x17).?);
    try std.testing.expectEqual(GameplayCellKind.jetpack, gameplayCellKindForRuntimeTile(0x19).?);
    try std.testing.expectEqual(GameplayCellKind.slug, gameplayCellKindForRuntimeTile(0x12).?);
    try std.testing.expectEqual(GameplayCellKind.garbage, gameplayCellKindForRuntimeTile(0x21).?);
    try std.testing.expectEqual(GameplayCellKind.salt, gameplayCellKindForRuntimeTile(0x22).?);
    try std.testing.expectEqual(GameplayCellKind.ring, gameplayCellKindForRuntimeTile(0x23).?);
}

test "runtime gameplay tile mapping respects build-flag gates" {
    try std.testing.expectEqual(@as(?GameplayCellKind, null), runtimeGameplayCellKindForTile(0x12, 0));
    try std.testing.expectEqual(GameplayCellKind.slug, runtimeGameplayCellKindForTile(0x12, 0x80).?);
    try std.testing.expectEqual(GameplayCellKind.health, runtimeGameplayCellKindForTile(0x17, 0).?);
}

test "runtime fallback spawn hint mask follows recovered tile families" {
    try std.testing.expectEqual(
        runtime_spawn_hint_garbage_fallback | runtime_spawn_hint_salt_fallback,
        runtimeFallbackSpawnHintMask(0x01, defaultRuntimeBuildFlags),
    );
    try std.testing.expectEqual(
        runtime_spawn_hint_garbage_fallback,
        runtimeFallbackSpawnHintMask(0x15, defaultRuntimeBuildFlags),
    );
    try std.testing.expectEqual(
        runtime_spawn_hint_salt_fallback,
        runtimeFallbackSpawnHintMask(0x0f, defaultRuntimeBuildFlags),
    );
    try std.testing.expectEqual(@as(u8, 0), runtimeFallbackSpawnHintMask(0x22, defaultRuntimeBuildFlags));
}

test "runtime spawn hint grid suppresses fallback hazards inside warning zones" {
    const runtime_tiles = [_]u8{
        0x01, 0x15, 0x0f, 0x22,
    };
    const runtime_warning_zone_grid = [_]bool{
        true, false, true, false,
    };

    const hints = try buildRuntimeSpawnHintGrid(
        std.testing.allocator,
        &runtime_tiles,
        &runtime_warning_zone_grid,
        1,
        runtime_tiles.len,
        defaultRuntimeBuildFlags,
    );
    defer std.testing.allocator.free(hints);

    try std.testing.expectEqual(@as(u8, 0), hints[0]);
    try std.testing.expectEqual(@as(u8, runtime_spawn_hint_garbage_fallback), hints[1]);
    try std.testing.expectEqual(@as(u8, 0), hints[2]);
    try std.testing.expectEqual(@as(u8, 0), hints[3]);
}

test "garbage fallback neighbor gate follows recovered horizontal tile set" {
    var preview: LoadedLevelPreview = undefined;
    preview.total_rows = 1;
    preview.max_width = 4;
    var allowed_tiles = [_]u8{ 0x01, 0x15, 0x20, 0x14 };
    preview.runtime_tiles = &allowed_tiles;

    try std.testing.expect(preview.garbageFallbackNeighborsAllowedAt(0, 1));
    try std.testing.expect(preview.garbageFallbackNeighborsAllowedAt(0, 2));

    var blocked_left_tiles = [_]u8{ 0x01, 0x0f, 0x20, 0x14 };
    preview.runtime_tiles = &blocked_left_tiles;
    try std.testing.expect(!preview.garbageFallbackNeighborsAllowedAt(0, 2));

    var blocked_right_tiles = [_]u8{ 0x01, 0x15, 0x23, 0x14 };
    preview.runtime_tiles = &blocked_right_tiles;
    try std.testing.expect(!preview.garbageFallbackNeighborsAllowedAt(0, 1));
}

test "normalize segment glyph for track flags matches recovered helper cases" {
    try std.testing.expectEqual(@as(u8, ' '), normalizeSegmentGlyphForTrackFlags(' ', defaultRuntimeBuildFlags, false, false));
    try std.testing.expectEqual(@as(u8, ','), normalizeSegmentGlyphForTrackFlags(' ', 0, false, false));
    try std.testing.expectEqual(@as(u8, ' '), normalizeSegmentGlyphForTrackFlags('=', 0x401, false, false));
    try std.testing.expectEqual(@as(u8, '_'), normalizeSegmentGlyphForTrackFlags('$', 0x40, false, false));
    try std.testing.expectEqual(@as(u8, '.'), normalizeSegmentGlyphForTrackFlags('o', 0, false, false));
    try std.testing.expectEqual(@as(u8, '{'), normalizeSegmentGlyphForTrackFlags(']', defaultRuntimeBuildFlags, true, false));
    try std.testing.expectEqual(@as(u8, '_'), normalizeSegmentGlyphForTrackFlags('_', 0, false, true));
    try std.testing.expectEqual(@as(u8, '.'), normalizeSegmentGlyphForTrackFlags('_', 0, false, false));
}

test "runtime flag b40 clears followers across recovered slide-strip runs" {
    const runtime_tiles = [_]u8{ 0x01, 0x15, 0x21, 0x22, 0x00 };
    const warn_surface = [_]bool{ false, false, false, false, false };
    const flags = try buildRuntimeFlagB40Grid(std.testing.allocator, &runtime_tiles, &warn_surface, 1, runtime_tiles.len);
    defer std.testing.allocator.free(flags);

    try std.testing.expect(flags[0]);
    try std.testing.expect(!flags[1]);
    try std.testing.expect(!flags[2]);
    try std.testing.expect(!flags[3]);
    try std.testing.expect(!flags[4]);
}

test "runtime flag b40 keeps separate heads across floor and slide strip families" {
    const runtime_tiles = [_]u8{ 0x0f, 0x14, 0x15, 0x00 };
    const warn_surface = [_]bool{ false, false, false, false };
    const flags = try buildRuntimeFlagB40Grid(std.testing.allocator, &runtime_tiles, &warn_surface, 1, runtime_tiles.len);
    defer std.testing.allocator.free(flags);

    try std.testing.expect(flags[0]);
    try std.testing.expect(flags[1]);
    try std.testing.expect(!flags[2]);
    try std.testing.expect(!flags[3]);
}

test "runtime flag b40 clears followers on recovered tile 0x0e strips" {
    const runtime_tiles = [_]u8{ 0x0e, 0x0e, 0x0e, 0x23 };
    const warn_surface = [_]bool{ false, false, false, false };
    const flags = try buildRuntimeFlagB40Grid(std.testing.allocator, &runtime_tiles, &warn_surface, 1, runtime_tiles.len);
    defer std.testing.allocator.free(flags);

    try std.testing.expect(flags[0]);
    try std.testing.expect(!flags[1]);
    try std.testing.expect(!flags[2]);
    try std.testing.expect(!flags[3]);
}

test "runtime flag b40 preserves non-condensed populated tiles" {
    const runtime_tiles = [_]u8{ 0x0f, 0x1d, 0x1e, 0x00 };
    const warn_surface = [_]bool{ false, false, false, false };
    const flags = try buildRuntimeFlagB40Grid(std.testing.allocator, &runtime_tiles, &warn_surface, 1, runtime_tiles.len);
    defer std.testing.allocator.free(flags);

    try std.testing.expect(flags[0]);
    try std.testing.expect(flags[1]);
    try std.testing.expect(flags[2]);
    try std.testing.expect(!flags[3]);
}

test "render cache warn surface grid promotes open-below floor and slide cells" {
    const runtime_tiles = [_]u8{
        0x0f, 0x01, 0x02, 0x00,
        0x00, 0x0e, 0x0f, 0x00,
    };
    const flags = try buildRenderCacheWarnSurfaceGrid(std.testing.allocator, &runtime_tiles, 2, 4);
    defer std.testing.allocator.free(flags);

    try std.testing.expect(flags[0]);
    try std.testing.expect(flags[1]);
    try std.testing.expect(!flags[2]);
    try std.testing.expect(!flags[3]);
    try std.testing.expect(!flags[4]);
    try std.testing.expect(!flags[5]);
}

test "runtime warning zone grid matches recovered backward footprint" {
    const runtime_tiles = [_]u8{
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x19, 0x00,
        0x00, 0x00, 0x00, 0x00,
    };
    const flags = try buildRuntimeWarningZoneGrid(std.testing.allocator, &runtime_tiles, 8, 4);
    defer std.testing.allocator.free(flags);

    for (0..6) |global_row| {
        try std.testing.expect(flags[runtimeTileIndex(4, global_row + 1, 1)]);
        try std.testing.expect(flags[runtimeTileIndex(4, global_row + 1, 2)]);
    }
    try std.testing.expect(!flags[runtimeTileIndex(4, 0, 1)]);
    try std.testing.expect(!flags[runtimeTileIndex(4, 7, 2)]);
}

test "runtime warning zone grid clamps the left edge and terminal row" {
    const runtime_tiles = [_]u8{
        0x00, 0x00, 0x00, 0x00,
        0x03, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
    };
    const flags = try buildRuntimeWarningZoneGrid(std.testing.allocator, &runtime_tiles, 3, 4);
    defer std.testing.allocator.free(flags);

    try std.testing.expect(flags[runtimeTileIndex(4, 0, 0)]);
    try std.testing.expect(flags[runtimeTileIndex(4, 1, 0)]);
    try std.testing.expect(!flags[runtimeTileIndex(4, 0, 1)]);
    try std.testing.expect(!flags[runtimeTileIndex(4, 2, 0)]);
}

test "render cache surface swap grid follows recovered center seam rules" {
    const runtime_tiles = [_]u8{
        0x0f, 0x0f, 0x0f, 0x01, 0x0f, 0x0f, 0x0f, 0x0f,
        0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x01, 0x0f, 0x0f,
    };
    const warn_surface = try buildRenderCacheWarnSurfaceGrid(std.testing.allocator, &runtime_tiles, 2, 8);
    defer std.testing.allocator.free(warn_surface);
    const swaps = try buildRenderCacheSurfaceSwapGrid(std.testing.allocator, &runtime_tiles, warn_surface, 2, 8);
    defer std.testing.allocator.free(swaps);

    try std.testing.expect(swaps[runtimeTileIndex(8, 0, 3)]);
    try std.testing.expect(swaps[runtimeTileIndex(8, 1, 5)]);
    try std.testing.expect(!swaps[runtimeTileIndex(8, 0, 2)]);
    try std.testing.expect(!swaps[runtimeTileIndex(8, 1, 4)]);
}

test "render cache surface swap grid preserves warn-promoted center seam cells" {
    const runtime_tiles = [_]u8{
        0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
        0x0f, 0x0f, 0x0f, 0x00, 0x0f, 0x01, 0x0f, 0x0f,
    };
    const warn_surface = try buildRenderCacheWarnSurfaceGrid(std.testing.allocator, &runtime_tiles, 2, 8);
    defer std.testing.allocator.free(warn_surface);
    const swaps = try buildRenderCacheSurfaceSwapGrid(std.testing.allocator, &runtime_tiles, warn_surface, 2, 8);
    defer std.testing.allocator.free(swaps);

    try std.testing.expect(warn_surface[runtimeTileIndex(8, 0, 3)]);
    try std.testing.expect(!swaps[runtimeTileIndex(8, 0, 3)]);
}

test "runtime flag b80 follows JetPack=Off annotations" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath("SEGMENTS/JETPACKOFF.TXT") orelse return error.EntryNotFound;
    var preview = try LoadedLevelPreview.loadStandaloneSegmentWithOptions(
        std.testing.allocator,
        &catalog,
        entry,
        .{ .load_models = false },
    );
    defer preview.deinit();

    for (0..preview.max_width) |lane_index| {
        try std.testing.expect(preview.runtimeFlagB80At(0, lane_index));
        try std.testing.expect(!preview.runtimeFlagB80At(1, lane_index));
    }
}

test "runtime flag b01 follows NoFall annotations" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath("SEGMENTS/TRAMPOLINE.TXT") orelse return error.EntryNotFound;
    var preview = try LoadedLevelPreview.loadStandaloneSegmentWithOptions(
        std.testing.allocator,
        &catalog,
        entry,
        .{ .load_models = false },
    );
    defer preview.deinit();

    var saw_no_fall = false;
    for (0..preview.total_rows) |global_row| {
        const row_location = preview.locateRow(global_row) orelse continue;
        const expects_flag = if (row_location.row.annotation) |annotation| annotation.tag() == .no_fall else false;
        for (0..preview.max_width) |lane_index| {
            try std.testing.expectEqual(expects_flag, preview.runtimeFlagB01At(global_row, lane_index));
        }
        saw_no_fall = saw_no_fall or expects_flag;
    }
    try std.testing.expect(saw_no_fall);
}

test "runtime row flags preserve recovered shipped ring bits" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const tutorial4_entry = catalog.dat.entryByPath("SEGMENTS/TUTORIAL 4.TXT") orelse return error.EntryNotFound;
    var tutorial4 = try LoadedLevelPreview.loadStandaloneSegmentWithOptions(
        std.testing.allocator,
        &catalog,
        tutorial4_entry,
        .{ .load_models = false },
    );
    defer tutorial4.deinit();

    try std.testing.expectEqual(runtime_row_flag_ring_powerup, tutorial4.runtimeRowFlagsAt(7) & runtime_row_flag_ring_powerup);
    try std.testing.expectEqual(@as(u32, 0), tutorial4.runtimeRowFlagsAt(13) & (runtime_row_flag_ring_powerup | runtime_row_flag_ring_explode | runtime_row_flag_ring_slow | runtime_row_flag_ring_normal | runtime_row_flag_ring_none));

    const tutorial7_entry = catalog.dat.entryByPath("SEGMENTS/TUTORIAL 7.TXT") orelse return error.EntryNotFound;
    var tutorial7 = try LoadedLevelPreview.loadStandaloneSegmentWithOptions(
        std.testing.allocator,
        &catalog,
        tutorial7_entry,
        .{ .load_models = false },
    );
    defer tutorial7.deinit();

    try std.testing.expectEqual(runtime_row_flag_ring_none, tutorial7.runtimeRowFlagsAt(21) & runtime_row_flag_ring_none);
    try std.testing.expectEqual(runtime_row_flag_ring_slow, tutorial7.runtimeRowFlagsAt(27) & runtime_row_flag_ring_slow);
}

test "runtime ring effect grid matches recovered tutorial offset and explicit-row cases" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const tutorial4_entry = catalog.dat.entryByPath("SEGMENTS/TUTORIAL 4.TXT") orelse return error.EntryNotFound;
    var tutorial4 = try LoadedLevelPreview.loadStandaloneSegmentWithOptions(
        std.testing.allocator,
        &catalog,
        tutorial4_entry,
        .{ .load_models = false },
    );
    defer tutorial4.deinit();

    try std.testing.expectEqual(@as(u8, 0), tutorial4.nativeRingEffectKindAt(7, 1));
    try std.testing.expectEqual(@as(u8, 8), tutorial4.nativeRingEffectKindAt(13, 1));

    const tutorial7_entry = catalog.dat.entryByPath("SEGMENTS/TUTORIAL 7.TXT") orelse return error.EntryNotFound;
    var tutorial7 = try LoadedLevelPreview.loadStandaloneSegmentWithOptions(
        std.testing.allocator,
        &catalog,
        tutorial7_entry,
        .{ .load_models = false },
    );
    defer tutorial7.deinit();

    try std.testing.expectEqual(@as(u8, 0), tutorial7.nativeRingEffectKindAt(21, 1));
    try std.testing.expectEqual(@as(u8, 7), tutorial7.nativeRingEffectKindAt(27, 4));

    const tutorial6_entry = catalog.dat.entryByPath("SEGMENTS/TUTORIAL 6.TXT") orelse return error.EntryNotFound;
    var tutorial6 = try LoadedLevelPreview.loadStandaloneSegmentWithOptions(
        std.testing.allocator,
        &catalog,
        tutorial6_entry,
        .{ .load_models = false },
    );
    defer tutorial6.deinit();

    try std.testing.expectEqual(@as(u8, 8), tutorial6.nativeRingEffectKindAt(51, 1));

    const tutorial11_entry = catalog.dat.entryByPath("SEGMENTS/TUTORIAL 11.TXT") orelse return error.EntryNotFound;
    var tutorial11 = try LoadedLevelPreview.loadStandaloneSegmentWithOptions(
        std.testing.allocator,
        &catalog,
        tutorial11_entry,
        .{ .load_models = false },
    );
    defer tutorial11.deinit();

    try std.testing.expectEqual(@as(u8, 6), tutorial11.nativeRingEffectKindAt(27, 4));
}

test "tutorial runtime ring effect grid publishes default ramp families without annotations" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const tutorial11_entry = catalog.dat.entryByPath("SEGMENTS/TUTORIAL 11.TXT") orelse return error.EntryNotFound;
    var tutorial11 = try LoadedLevelPreview.loadStandaloneSegmentWithOptions(
        std.testing.allocator,
        &catalog,
        tutorial11_entry,
        .{
            .load_models = false,
            .runtime_build_flags = tutorialRuntimeBuildFlags,
        },
    );
    defer tutorial11.deinit();

    try std.testing.expectEqual(@as(u8, 0), tutorial11.nativeRingEffectKindAt(22, 1));
    try std.testing.expectEqual(@as(u8, 2), tutorial11.nativeRingEffectKindAt(39, 1));

    const tutorial7_entry = catalog.dat.entryByPath("SEGMENTS/TUTORIAL 7.TXT") orelse return error.EntryNotFound;
    var tutorial7 = try LoadedLevelPreview.loadStandaloneSegmentWithOptions(
        std.testing.allocator,
        &catalog,
        tutorial7_entry,
        .{
            .load_models = false,
            .runtime_build_flags = tutorialRuntimeBuildFlags,
        },
    );
    defer tutorial7.deinit();

    try std.testing.expectEqual(@as(u8, 0), tutorial7.nativeRingEffectKindAt(21, 1));
}

test "runtime build mirror latch matches recovered threshold logic" {
    var state = RuntimeBuildState.init(defaultRuntimeBuildFlags, 0);
    try std.testing.expect(state.applyMirrorDecision(true));
    try std.testing.expect(!state.applyMirrorDecision(false));
    try std.testing.expect(state.applyMirrorDecision(true));
    try std.testing.expect(state.applyMirrorDecision(false));
    try std.testing.expect(!state.applyMirrorDecision(false));
}

test "level preview builds derived runtime tiles for shipped glyphs across the corpus" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    var saw_health = false;
    var saw_jetpack = false;
    var saw_slug = false;
    var saw_trampoline = false;
    var saw_garbage = false;
    var saw_salt = false;

    for (catalog.level_entries) |level_entry| {
        var level_definition = try level.loadFromArchive(std.testing.allocator, &catalog, level_entry);
        defer level_definition.deinit();

        var preview = try LoadedLevelPreview.loadWithOptions(std.testing.allocator, &catalog, &level_definition, .{ .load_models = false });
        defer preview.deinit();

        for (0..preview.total_rows) |row_index| {
            const row_location = preview.locateRow(row_index) orelse continue;
            for (row_location.row.cells, 0..) |cell, lane_index| {
                const tile_type = preview.runtimeTileAt(row_index, lane_index) orelse continue;
                switch (cell) {
                    '$' => {
                        saw_health = true;
                        try std.testing.expectEqual(@as(u8, 0x17), tile_type);
                    },
                    'J' => {
                        saw_jetpack = true;
                        try std.testing.expectEqual(@as(u8, 0x19), tile_type);
                    },
                    'M' => {
                        saw_slug = true;
                        try std.testing.expectEqual(@as(u8, 0x12), tile_type);
                    },
                    '(' => {
                        saw_trampoline = true;
                        try std.testing.expectEqual(@as(u8, 0x16), tile_type);
                        try std.testing.expectEqual(@as(?f32, -3.0), preview.floorHeightAtCellCenter(row_index, lane_index));
                    },
                    's' => {
                        saw_garbage = true;
                        try std.testing.expectEqual(@as(u8, 0x21), tile_type);
                    },
                    '&' => {
                        saw_salt = true;
                        try std.testing.expectEqual(@as(u8, 0x22), tile_type);
                    },
                    else => {},
                }
            }
        }
    }

    try std.testing.expect(saw_health);
    try std.testing.expect(saw_jetpack);
    try std.testing.expect(saw_slug);
    try std.testing.expect(saw_trampoline);
    try std.testing.expect(saw_garbage);
    try std.testing.expect(saw_salt);
}

test "level preview applies runtime hazard scalar overrides" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath("LEVELS/ARCADE000.TXT") orelse return error.EntryNotFound;
    var level_definition = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer level_definition.deinit();

    var preview = try LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &level_definition,
        .{
            .load_models = false,
            .garbage_scalar_override = 0.32,
            .salt_scalar_override = 0.45,
        },
    );
    defer preview.deinit();

    try std.testing.expectApproxEqAbs(@as(f32, 0.32), preview.garbage_scalar, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.45), preview.salt_scalar, 0.0001);
}

test "level preview seeds course-end threshold from the native last block on non-random levels" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath("LEVELS/ARCADE000.TXT") orelse return error.EntryNotFound;
    var level_definition = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer level_definition.deinit();

    var preview = try LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &level_definition,
        .{ .load_models = false },
    );
    defer preview.deinit();

    const last_block_start_index = preview.segments.len - level_definition.last_segments.len;
    const expected_threshold: f32 = @floatFromInt(preview.row_offsets[last_block_start_index]);
    try std.testing.expectApproxEqAbs(expected_threshold, preview.course_end_threshold, 0.0001);
}

test "level preview seeds runtime row window from the native fallback" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath("LEVELS/ARCADE000.TXT") orelse return error.EntryNotFound;
    var level_definition = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer level_definition.deinit();

    var preview = try LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &level_definition,
        .{ .load_models = false },
    );
    defer preview.deinit();

    try std.testing.expectEqual(defaultRuntimeActiveRowStart, preview.runtime_active_row_start);
    try std.testing.expectEqual(preview.total_rows, preview.runtime_active_row_end);
}

test "random level preview keeps course-end threshold fallback without a native scalar override" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath("LEVELS/CHALLENGE000.TXT") orelse return error.EntryNotFound;
    var level_definition = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer level_definition.deinit();

    try std.testing.expect(level_definition.random);

    var preview = try LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &level_definition,
        .{ .load_models = false },
    );
    defer preview.deinit();

    try std.testing.expectApproxEqAbs(@as(f32, @floatFromInt(preview.total_rows - 1)), preview.course_end_threshold, 0.0001);
}

test "random level preview seeds course-end threshold from the native Length scalar when provided" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath("LEVELS/CHALLENGE000.TXT") orelse return error.EntryNotFound;
    var level_definition = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer level_definition.deinit();

    try std.testing.expect(level_definition.random);

    const random_length_scalar: f32 = 0.4;
    var preview = try LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &level_definition,
        .{
            .load_models = false,
            .random_length_scalar_override = random_length_scalar,
        },
    );
    defer preview.deinit();

    const last_block_start_index = preview.segments.len - level_definition.last_segments.len;
    const last_block_row_count = preview.total_rows - preview.row_offsets[last_block_start_index];
    const expected_total_rows = @as(isize, @intFromFloat(@floor(
        @as(f32, @floatFromInt(level_definition.length)) * ((random_length_scalar * 0.65) + 0.35),
    )));
    const expected_threshold = @as(f32, @floatFromInt(expected_total_rows - @as(isize, @intCast(last_block_row_count))));
    try std.testing.expectApproxEqAbs(expected_threshold, preview.course_end_threshold, 0.0001);
}

test "level preview applies explicit runtime row window overrides" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath("LEVELS/ARCADE000.TXT") orelse return error.EntryNotFound;
    var level_definition = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer level_definition.deinit();

    var preview = try LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &level_definition,
        .{
            .load_models = false,
            .runtime_active_row_start = 12,
            .runtime_active_row_end = 345,
        },
    );
    defer preview.deinit();

    try std.testing.expectEqual(@as(usize, 12), preview.runtime_active_row_start);
    try std.testing.expectEqual(@as(usize, 345), preview.runtime_active_row_end);
}

test "level preview applies explicit course-end threshold overrides" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath("LEVELS/ARCADE000.TXT") orelse return error.EntryNotFound;
    var level_definition = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer level_definition.deinit();

    var preview = try LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &level_definition,
        .{
            .load_models = false,
            .course_end_threshold_override = 123.5,
        },
    );
    defer preview.deinit();

    try std.testing.expectApproxEqAbs(@as(f32, 123.5), preview.course_end_threshold, 0.0001);
}

test "runtime tile family helpers match recovered cache predicates" {
    try std.testing.expect(isFloorCacheRuntimeTileFamily(0x17));
    try std.testing.expect(isFloorCacheRuntimeTileFamily(0x10));
    try std.testing.expect(!isFloorCacheRuntimeTileFamily(0x22));

    try std.testing.expect(isRampRuntimeTileFamily(0x02));
    try std.testing.expect(isRampRuntimeTileFamily(0x0a));
    try std.testing.expect(!isRampRuntimeTileFamily(0x17));

    try std.testing.expect(isSlideRuntimeTileFamily(0x22));
    try std.testing.expect(isSlideRuntimeTileFamily(0x01));
    try std.testing.expect(!isSlideRuntimeTileFamily(0x10));

    try std.testing.expect(isOpenNeighborRuntimeTileFamily(0x1d));
    try std.testing.expect(isOpenNeighborRuntimeTileFamily(0x23));
    try std.testing.expect(!isOpenNeighborRuntimeTileFamily(0x1e));
}

test "runtime open edge mask follows open-neighbor family boundaries" {
    const tiles = [_]u8{
        0x00, 0x00, 0x00,
        0x00, 0x01, 0x00,
        0x00, 0x00, 0x00,
    };
    try std.testing.expectEqual(@as(u8, 0x0f), runtimeOpenEdgeMask(&tiles, 3, 3, 1, 1, 0x01));

    const closed_neighbors = [_]u8{
        0x01, 0x01, 0x01,
        0x01, 0x01, 0x01,
        0x01, 0x01, 0x01,
    };
    try std.testing.expectEqual(@as(u8, 0x00), runtimeOpenEdgeMask(&closed_neighbors, 3, 3, 1, 1, 0x01));

    try std.testing.expectEqual(@as(u8, 0x00), runtimeOpenEdgeMask(&tiles, 3, 3, 1, 1, 0x1e));
}

test "runtime open edge mask carries the native corner bit on corner masks" {
    const tiles = [_]u8{
        0x01, 0x00, 0x01,
        0x00, 0x01, 0x01,
        0x01, 0x01, 0x01,
    };
    try std.testing.expectEqual(@as(u8, 0x89), runtimeOpenEdgeMask(&tiles, 3, 3, 1, 1, 0x01));
}

test "runtime flag b40 grid condenses recovered floor-family runs" {
    const tiles = [_]u8{ 0x0f, 0x10, 0x13 };
    const warn_surface = [_]bool{ false, false, false };
    const flag_grid = try buildRuntimeFlagB40Grid(std.testing.allocator, &tiles, &warn_surface, 1, 3);
    defer std.testing.allocator.free(flag_grid);

    try std.testing.expect(flag_grid[0]);
    try std.testing.expect(!flag_grid[1]);
    try std.testing.expect(!flag_grid[2]);
}

test "runtime flag b40 grid keeps warn-promoted slide cells as separate heads" {
    const tiles = [_]u8{ 0x01, 0x15 };
    const warn_surface = [_]bool{ true, true };
    const flag_grid = try buildRuntimeFlagB40Grid(std.testing.allocator, &tiles, &warn_surface, 1, 2);
    defer std.testing.allocator.free(flag_grid);

    try std.testing.expect(flag_grid[0]);
    try std.testing.expect(flag_grid[1]);
}

test "runtime flag b40 grid keeps corner-marked slide cells as separate heads" {
    const tiles = [_]u8{
        0x01, 0x00, 0x01, 0x01,
        0x00, 0x01, 0x01, 0x01,
        0x01, 0x01, 0x01, 0x01,
    };
    const warn_surface = [_]bool{
        false, false, false, false,
        false, false, false, false,
        false, false, false, false,
    };
    const flag_grid = try buildRuntimeFlagB40Grid(std.testing.allocator, &tiles, &warn_surface, 3, 4);
    defer std.testing.allocator.free(flag_grid);

    try std.testing.expect(flag_grid[5]);
    try std.testing.expect(flag_grid[6]);
    try std.testing.expect(!flag_grid[7]);
}

test "runtime floor sampler matches recovered tile formulas" {
    try std.testing.expectEqual(@as(?f32, 0.0), sampleFloorHeightForRuntimeTile(0x01, 12.25, null));
    try std.testing.expectApproxEqAbs(@as(f32, 0.1), sampleFloorHeightForRuntimeTile(0x02, 12.25, null).?, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.6), sampleFloorHeightForRuntimeTile(0x08, 12.25, null).?, 0.0001);
    try std.testing.expectEqual(@as(?f32, 1.75), sampleFloorHeightForRuntimeTile(0x16, 12.25, 1.75));
    try std.testing.expectEqual(@as(?f32, null), sampleFloorHeightForRuntimeTile(0x1e, 12.25, null));
}

test "special floor heights match recovered shipped builder defaults" {
    try std.testing.expectEqual(@as(?f32, -3.0), specialFloorHeightForShippedRuntimeTile(0x16));
    try std.testing.expectEqual(@as(?f32, null), specialFloorHeightForShippedRuntimeTile(0x1e));
}

test "world quantization matches recovered track grid sampling" {
    var catalog = try assets.Catalog.init(std.testing.allocator, "artifacts/bin/SnailMail.dat");
    defer catalog.deinit();

    const level_entry = catalog.level_entries[catalog.findLevelIndex("LEVELS/TUTORIAL.TXT").?];
    var level_definition = try level.loadFromArchive(std.testing.allocator, &catalog, level_entry);
    defer level_definition.deinit();

    var preview = try LoadedLevelPreview.load(std.testing.allocator, &catalog, &level_definition);
    defer preview.deinit();

    try std.testing.expectEqual(@as(usize, 0), preview.laneIndexAtWorldX(-20.0));
    try std.testing.expectEqual(@as(usize, 9), preview.laneIndexAtWorldX(20.0));
    try std.testing.expectEqual(@as(usize, 0), preview.laneIndexAtWorldX(-3.99));
    try std.testing.expectEqual(@as(usize, 8), preview.laneIndexAtWorldX(3.99));
    try std.testing.expectEqual(@as(usize, 1), preview.laneIndexAtWorldX(preview.worldPositionForLane(1.5, 0.0, 0.0).x));
    try std.testing.expectEqual(@as(usize, 8), preview.laneIndexAtWorldX(preview.worldPositionForLane(8.5, 0.0, 0.0).x));
    try std.testing.expectEqual(@as(usize, 0), preview.rowIndexAtWorldZ(-5.0));
    try std.testing.expectEqual(preview.total_rows - 1, preview.rowIndexAtWorldZ(10_000.0));
}
