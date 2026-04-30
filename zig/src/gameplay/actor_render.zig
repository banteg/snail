const std = @import("std");
const rl = @import("raylib");

const attachment_builders = @import("../attachment_builders.zig");
const game_font = @import("../game_font.zig");
const gameplay = @import("../gameplay.zig");
const gameplay_attachment = @import("attachment.zig");
const gameplay_assets = @import("assets.zig");
const gameplay_barrier_render = @import("barrier_render.zig");
const gameplay_billboard = @import("billboard.zig");
const gameplay_effects = @import("effects.zig");
const gameplay_model_render = @import("model_render.zig");
const gameplay_presentation = @import("presentation.zig");
const gameplay_projectile_render = @import("projectile_render.zig");
const gameplay_render_policy = @import("render_policy.zig");
const gameplay_resources = @import("resources.zig");
const gameplay_runtime_entities = @import("runtime_entities.zig");
const segment = @import("../segment.zig");
const track = @import("../track.zig");

const start_banner_visible_rows: f32 = 40.0;
const banner_bob_amplitude: f32 = 0.26;
const banner_bob_cycle_seconds: f32 = 144.0 / 60.0;
const tau: f32 = 6.2831855;
const native_runtime_ring_particle_count: usize = 10;
const native_runtime_ring_particle_radius: f32 = 1.2;
const native_runtime_ring_particle_size: f32 = 0.72;
const native_runtime_ring_particle_alpha: u8 = 204;
const native_runtime_ring_particle_phase_step: f32 = tau / @as(f32, @floatFromInt(native_runtime_ring_particle_count));
const native_time_trial_ghost_sprite_world_size: f32 = 1.0;
const native_time_trial_ghost_y: f32 = 1.0;

const RuntimeRingParticleSpriteFamily = enum {
    ring,
    explode,
    slow,
};

pub const Context = struct {
    resources: *const gameplay_resources.State,
    ui_font: *const game_font.Loaded,
    effects: *const gameplay_effects.Controller,
    weapon_visual_state: *const gameplay_presentation.WeaponVisualState,
    jetpack_visual_state: *const gameplay_presentation.JetpackVisualState,
    billboard_shader: ?rl.Shader,
    render_time_seconds: f64,
    click_start_active: bool,
    tutorial_click_start_cutscene_active: bool,
    is_tutorial_level: bool,
};

pub fn context(state: anytype) Context {
    return .{
        .resources = &state.gameplay_resources,
        .ui_font = &state.ui_font,
        .effects = &state.gameplay_effects,
        .weapon_visual_state = &state.gameplay_weapon_visual_state,
        .jetpack_visual_state = &state.gameplay_jetpack_visual_state,
        .billboard_shader = state.gameplay_billboard_shader,
        .render_time_seconds = state.render_time_seconds,
        .click_start_active = state.gameplay_click_start_active,
        .tutorial_click_start_cutscene_active = if (state.gameplay_click_start_active) blk: {
            const runner = state.level_runner orelse break :blk false;
            break :blk runner.introCutsceneBlocksGameplay();
        } else false,
        .is_tutorial_level = if (state.current_level) |loaded_level|
            std.mem.eql(u8, loaded_level.source_path, "LEVELS/TUTORIAL.TXT")
        else
            false,
    };
}

pub fn drawRuntimeActors(
    render: Context,
    loaded_track_preview: *const track.LoadedLevelPreview,
    runner: gameplay.Runner,
    camera: rl.Camera3D,
) void {
    if (loaded_track_preview.max_width == 0 or loaded_track_preview.total_rows == 0) return;

    const current_row = loaded_track_preview.rowIndexAtWorldZ(runner.row_position);
    const start_row = current_row -| 1;
    const end_row = @min(loaded_track_preview.total_rows, current_row + 72);

    var global_row = end_row;
    while (global_row > start_row) {
        global_row -= 1;
        if (!gameplay_render_policy.actorRowVisible(runner, global_row)) continue;
        const row_location = loaded_track_preview.locateRow(global_row) orelse continue;
        for (0..row_location.row.cells.len) |lane_index| {
            if (loaded_track_preview.gameplayCellSampleAt(global_row, lane_index)) |sample| {
                switch (sample.kind) {
                    .slug => drawGameplaySlugActor(render, loaded_track_preview, runner, camera, global_row, lane_index),
                    .ring => {
                        if (gameplay_render_policy.staticRingVisible(loaded_track_preview, row_location, loaded_track_preview.runtimeTileAt(global_row, lane_index))) {
                            drawGameplayStaticRingActor(render, loaded_track_preview, camera, row_location, lane_index);
                        }
                    },
                    .health, .jetpack, .attachment_probe, .attachment_entry, .trampoline, .garbage, .salt => {},
                }
            }
            if (wall2PillarActorVisible(loaded_track_preview, global_row, lane_index)) {
                drawGameplayWall2PillarActor(render, loaded_track_preview, global_row, lane_index);
            }
        }
    }

    for (runner.activeTrackParcels()) |parcel| {
        if (!parcel.active()) continue;
        if (!gameplay_render_policy.actorRowVisible(runner, parcel.row)) continue;
        drawGameplayTrackParcelActor(render, camera, parcel);
    }

    for (runner.activeRuntimeHazards()) |hazard| {
        if (!gameplay_render_policy.hazardVisible(runner, hazard)) continue;
        switch (hazard.kind) {
            .garbage => {
                drawGameplayGarbageActor(render, loaded_track_preview, camera, hazard);
            },
        }
    }

    // PORT(verified): dedicated `cRSalt`-shaped pool render. Each active
    // slot owns its own world position + yaw and is drawn with the shared
    // `drawGameplaySaltSlotActor` helper that reads the same salt mesh path
    // as the legacy branch.
    for (runner.activeRuntimeSalts()) |slot| {
        if (!gameplay_render_policy.saltSlotVisible(runner, slot)) continue;
        drawGameplaySaltSlotActor(render, camera, slot);
    }

    for (runner.activeRuntimeSubLazers()) |slot| {
        if (!gameplay_render_policy.subLazerVisible(runner, slot)) continue;
        drawGameplaySubLazerSlotActor(render, camera, slot);
    }

    for (runner.activeRuntimePickups()) |pickup| {
        if (!gameplay_render_policy.pickupVisible(runner, pickup)) continue;
        switch (pickup.kind) {
            .health => drawGameplayHealthPickupActor(render, camera, pickup),
            .jetpack => drawGameplayJetpackPickupActor(render, camera, pickup),
        }
    }

    for (runner.activeRuntimeRingEffects()) |effect| {
        if (!gameplay_render_policy.ringEffectVisible(runner, effect)) continue;
        drawGameplayRuntimeRingEffectActor(render, camera, effect);
    }

    drawTimeTrialGhost(render, runner, camera);

    for (runner.activeProjectiles()) |projectile| {
        drawGameplayProjectileActor(render, camera, projectile);
    }

    drawGameplayEffects(render, camera);
}

fn wall2PillarActorVisible(preview: *const track.LoadedLevelPreview, global_row: usize, lane_index: usize) bool {
    if ((preview.runtimeTileAt(global_row, lane_index) orelse 0) != 0x0e) return false;
    // PORT(verified): native `merge_track_tile_runs` keeps the merged Wall2
    // BOD object on the first `0x0e` cell only, stores the run width in that
    // owner's `TrackRowCell.render_flags >> 8`, and clears the object-owner
    // bits on the follower cells. The preview's B40 grid mirrors that owner
    // head bit for render consumers.
    return preview.runtimeFlagB40At(global_row, lane_index);
}

fn drawTimeTrialGhost(render: Context, runner: gameplay.Runner, camera: rl.Camera3D) void {
    if (!runner.time_trial_ghost_active) return;
    const loaded_texture = render.resources.sprites.ghost.?;
    inline for (.{ -4.0, 4.0 }) |world_x| {
        gameplay_billboard.drawTexture(
            loaded_texture.texture,
            .{
                .x = world_x,
                .y = native_time_trial_ghost_y,
                .z = runner.time_trial_ghost_z,
            },
            native_time_trial_ghost_sprite_world_size,
            native_time_trial_ghost_sprite_world_size,
            camera,
            render.billboard_shader,
            .white,
        );
    }
}

pub fn drawPostOfficeStopBanners(
    render: Context,
    loaded_track_preview: *const track.LoadedLevelPreview,
    runner: gameplay.Runner,
) void {
    if (runner.row_position >= start_banner_visible_rows) return;
    const model = render.resources.post_office_stop_model orelse return;

    const phase = @as(f32, @floatCast(render.render_time_seconds)) * (tau / banner_bob_cycle_seconds);
    const y = std.math.sin(phase) * banner_bob_amplitude;
    // PORT(verified): native creates two cRBanner slots from postofficestop.x.
    // Mode 0 is visible while player z < 40. Build-level setup zeros x/y, writes
    // z from game+0x50 (`track_row_start`), then update_banner only applies this
    // sine bob to y. The cRBod render path passes these fields straight through
    // as the object matrix translation; it does not use annotation-style
    // center/ground correction against the mesh bounds.
    model.drawEx(startBannerNativeTransform(loaded_track_preview, y));
}

fn startBannerNativeTransform(loaded_track_preview: *const track.LoadedLevelPreview, bob_y: f32) rl.Matrix {
    return startBannerNativeTransformForRow(loaded_track_preview.runtime_active_row_start, bob_y);
}

fn startBannerNativeTransformForRow(runtime_active_row_start: usize, bob_y: f32) rl.Matrix {
    return rl.Matrix.translate(0.0, bob_y, @floatFromInt(runtime_active_row_start));
}

test "post office stop banner uses native bod origin transform" {
    const transform = startBannerNativeTransformForRow(track.defaultRuntimeActiveRowStart, 0.25);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), transform.m12, 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.25), transform.m13, 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, @floatFromInt(track.defaultRuntimeActiveRowStart)), transform.m14, 0.001);
}

fn drawGameplaySlugActor(
    render: Context,
    preview: *const track.LoadedLevelPreview,
    runner: gameplay.Runner,
    camera: rl.Camera3D,
    global_row: usize,
    lane_index: usize,
) void {
    const visual = runner.slugVisualState(global_row, lane_index);
    if (!visual.visible) return;

    // Native slug hazards spawn a world sprite with size lanes +0x60/+0x64 both seeded to 2.0,
    // and `draw_sprite_quad` treats that blended value as the quad half-extent.
    const slug_sprite_half_extent: f32 = 2.0;
    const slug_sprite_world_size: f32 = slug_sprite_half_extent * 2.0;
    const slug_sprite_y_offset: f32 = 1.7;
    // Native `spawn_slug_hazard` allocates the live sprite with texture ref 118 (`SLUG000`).
    // Projectile hits drive the recovered state-machine branches that switch to 119/120.
    const loaded_texture = if (visual.use_mask)
        render.resources.sprites.slug_mask orelse render.resources.sprites.slug_frames[@min(visual.frame_index, render.resources.sprites.slug_frames.len - 1)].?
    else
        render.resources.sprites.slug_frames[@min(visual.frame_index, render.resources.sprites.slug_frames.len - 1)].?;
    const frame = slugSpriteFrame(preview, global_row, lane_index, slug_sprite_y_offset);
    gameplay_billboard.drawTextureRectBasis(
        loaded_texture.texture,
        .{ .x = 0.0, .y = 0.0, .width = @floatFromInt(loaded_texture.texture.width), .height = @floatFromInt(loaded_texture.texture.height) },
        frame.position,
        slug_sprite_world_size,
        slug_sprite_world_size,
        frame.right,
        frame.up,
        render.billboard_shader,
        visual.tint,
    );
    _ = camera;
}

const SlugSpriteFrame = struct {
    position: rl.Vector3,
    right: rl.Vector3,
    up: rl.Vector3,
};

fn slugSpriteFrame(preview: *const track.LoadedLevelPreview, global_row: usize, lane_index: usize, y_offset: f32) SlugSpriteFrame {
    const floor_height = preview.floorHeightAtCellCenter(global_row, lane_index) orelse 0.0;
    const lane_center = @as(f32, @floatFromInt(lane_index)) + 0.5;
    const flat_surface = preview.worldPositionForLane(lane_center, @as(f32, @floatFromInt(global_row)), floor_height);
    if (preview.activeBuiltAttachmentAtRow(global_row)) |built| {
        return slugSpriteFrameForAttachment(built, global_row, flat_surface, y_offset);
    }

    return .{
        .position = .{
            .x = flat_surface.x,
            .y = flat_surface.y + y_offset,
            .z = flat_surface.z,
        },
        .right = .{ .x = 1.0, .y = 0.0, .z = 0.0 },
        .up = .{ .x = 0.0, .y = 1.0, .z = 0.0 },
    };
}

fn slugSpriteFrameForAttachment(
    built: *const attachment_builders.BuiltAttachment,
    global_row: usize,
    flat_surface: rl.Vector3,
    y_offset: f32,
) SlugSpriteFrame {
    const progress: f32 = @floatFromInt(global_row -| built.row.global_row);
    const pose = attachment_builders.worldPoseForTemplate(&built.template, progress, built.row.global_row, 0.0, 0.0);
    const local_surface = gameplay_attachment.localPosition(pose, .{
        .x = flat_surface.x,
        .y = flat_surface.y,
        .z = flat_surface.z,
    });
    const projected_position = gameplay_attachment.worldPositionFromLocal(pose, .{
        .x = local_surface.x,
        .y = y_offset,
        .z = local_surface.z,
    });
    return .{
        .position = vec3ToRl(projected_position),
        .right = vec3ToRl(pose.basis_right),
        .up = vec3ToRl(pose.basis_up),
    };
}

fn vec3ToRl(v: attachment_builders.Vec3) rl.Vector3 {
    return .{ .x = v.x, .y = v.y, .z = v.z };
}

test "slug sprite frame uses active attachment basis" {
    var samples = [_]attachment_builders.TemplateSample{.{
        .basis_right = .{ .x = 0.0, .y = 1.0, .z = 0.0 },
        .basis_up = .{ .x = -1.0, .y = 0.0, .z = 0.0 },
        .basis_forward = .{ .x = 0.0, .y = 0.0, .z = 1.0 },
        .position = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
        .center_x = 0.0,
        .lateral_scale = 1.0,
    }};
    const built = attachment_builders.BuiltAttachment{
        .row = .{
            .global_row = 10,
            .segment_index = 0,
            .row_index = 10,
            .raw_name = "TEST",
            .public_path = null,
        },
        .template = .{
            .spec = .{
                .public_path = .start,
                .family = .start,
                .status = .partial,
            },
            .sample_count = samples.len,
            .samples = samples[0..],
        },
    };

    const frame = slugSpriteFrameForAttachment(&built, 10, .{ .x = 2.0, .y = 3.0, .z = 10.5 }, 1.7);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), frame.right.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), frame.right.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), frame.right.z, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, -1.0), frame.up.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), frame.up.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.0), frame.up.z, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, -1.7), frame.position.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 3.0), frame.position.y, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 10.5), frame.position.z, 0.0001);
}

fn drawGameplayGarbageActor(
    render: Context,
    preview: *const track.LoadedLevelPreview,
    camera: rl.Camera3D,
    hazard: gameplay_runtime_entities.Hazard,
) void {
    _ = preview;
    if (hazard.state == .inactive) return;
    const variant_index = @min(
        @as(usize, hazard.sprite_variant_index),
        gameplay_assets.gameplay_garbage_sprite_paths.len - 1,
    );
    const loaded_texture = render.resources.sprites.garbage_variants[variant_index].?;
    gameplay_billboard.drawTextureRectRolledAlphaCutoff(
        loaded_texture.texture,
        .{ .x = 0.0, .y = 0.0, .width = @floatFromInt(loaded_texture.texture.width), .height = @floatFromInt(loaded_texture.texture.height) },
        hazard.world_position,
        hazard.presentation_scale,
        hazard.presentation_scale,
        camera,
        render.billboard_shader,
        hazard.presentation_phase,
        .white,
        gameplay_billboard.hard_alpha_cutoff,
    );
}

fn drawGameplaySaltSlotActor(
    render: Context,
    camera: rl.Camera3D,
    slot: gameplay_runtime_entities.SaltSlot,
) void {
    if (slot.state != .active) return;
    drawGameplaySaltVisual(render, camera, slot.world_position, slot.yaw_radians);
}

fn drawGameplaySaltVisual(
    render: Context,
    camera: rl.Camera3D,
    world_position: rl.Vector3,
    yaw_radians: f32,
) void {
    const presentation_alpha: u8 = 232;
    if (render.resources.salt_model) |*model| {
        const yaw_sin = std.math.sin(yaw_radians);
        const yaw_cos = std.math.cos(yaw_radians);
        const right: rl.Vector3 = .{ .x = yaw_cos, .y = 0.0, .z = -yaw_sin };
        const up: rl.Vector3 = .{ .x = 0.0, .y = 1.0, .z = 0.0 };
        const forward: rl.Vector3 = .{ .x = yaw_sin, .y = 0.0, .z = yaw_cos };
        const transform = gameplay_model_render.transformFromBasis(world_position, right, up, forward);
        const tint: rl.Color = .{ .r = 255, .g = 255, .b = 255, .a = presentation_alpha };
        if (render.billboard_shader) |alpha_cutout_shader| {
            model.drawTintedAlphaCutoutEx(transform, tint, alpha_cutout_shader);
        } else {
            model.drawTintedEx(transform, tint);
        }
        return;
    }

    const icon = render.ui_font.slots[game_font.IconGlyph.salt.slotIndex()];
    gameplay_billboard.drawTextureRect(
        render.ui_font.texture,
        .{
            .x = icon.source_x,
            .y = icon.source_y,
            .width = icon.source_width,
            .height = icon.source_height,
        },
        world_position,
        0.58,
        0.72,
        camera,
        render.billboard_shader,
        .{ .r = 144, .g = 198, .b = 255, .a = presentation_alpha },
    );
}

fn drawGameplayWall2PillarActor(
    render: Context,
    preview: *const track.LoadedLevelPreview,
    global_row: usize,
    lane_index: usize,
) void {
    const model_info = wall2PillarModelInfo(preview, global_row, lane_index) orelse return;
    const model = render.resources.wall2_pillar_models[model_info.model_index] orelse return;
    const floor_height = preview.floorHeightAtCellCenter(global_row, lane_index) orelse 0.0;
    const position = preview.worldPositionForLane(
        @as(f32, @floatFromInt(lane_index)) + @as(f32, @floatFromInt(model_info.run_length)) * 0.5,
        @as(f32, @floatFromInt(global_row)),
        floor_height,
    );
    const transform = rl.Matrix.translate(
        position.x - model.bounds.center.x,
        position.y - model.bounds.min.y,
        position.z - model.bounds.center.z,
    );
    model.drawEx(transform);
}

const Wall2PillarModelInfo = struct {
    model_index: usize,
    run_length: usize,
};

fn wall2PillarModelInfo(preview: *const track.LoadedLevelPreview, global_row: usize, lane_index: usize) ?Wall2PillarModelInfo {
    if (!wall2PillarActorVisible(preview, global_row, lane_index)) return null;

    var run_length: usize = 1;
    while (lane_index + run_length < preview.max_width) : (run_length += 1) {
        if ((preview.runtimeTileAt(global_row, lane_index + run_length) orelse 0) != 0x0e) break;
    }
    run_length = @min(run_length, gameplay_assets.gameplay_wall2_pillar_model_paths.len);
    return .{
        .model_index = run_length - 1,
        .run_length = run_length,
    };
}

fn drawGameplayHealthPickupActor(
    render: Context,
    camera: rl.Camera3D,
    pickup: gameplay_runtime_entities.Pickup,
) void {
    const loaded_texture = render.resources.sprites.health.?;
    gameplay_billboard.drawTexture(loaded_texture.texture, pickup.presentation_position, 0.52, 0.52, camera, render.billboard_shader, .white);
}

fn drawGameplayJetpackPickupActor(
    render: Context,
    camera: rl.Camera3D,
    pickup: gameplay_runtime_entities.Pickup,
) void {
    const frame_index: usize = @intFromFloat(@mod(@floor(render.render_time_seconds * 8.0), @as(f64, @floatFromInt(gameplay_assets.gameplay_jetpack_sprite_paths.len))));
    const loaded_texture = render.resources.sprites.jetpack_frames[frame_index].?;
    gameplay_billboard.drawTexture(loaded_texture.texture, pickup.presentation_position, 0.64, 0.88, camera, render.billboard_shader, .white);
}

fn drawGameplayStaticRingActor(
    render: Context,
    preview: *const track.LoadedLevelPreview,
    camera: rl.Camera3D,
    row_location: track.RowLocation,
    lane_index: usize,
) void {
    const ring_kind = if (row_location.row.annotation) |annotation|
        switch (annotation) {
            .ring => |kind| kind,
            else => segment.RingKind.normal,
        }
    else
        segment.RingKind.normal;
    const position = gameplayLaneWorldPosition(preview, row_location.global_row, lane_index, 0.72);
    drawGameplayRingSprite(render, camera, position, 1.0, ring_kind);
}

fn drawGameplayRingSprite(
    render: Context,
    camera: rl.Camera3D,
    position: rl.Vector3,
    scale: f32,
    ring_kind: segment.RingKind,
) void {
    switch (ring_kind) {
        .none => {},
        .normal => gameplay_billboard.drawTexture(render.resources.sprites.ring.?.texture, position, 0.46 * scale, 0.46 * scale, camera, render.billboard_shader, .{ .r = 255, .g = 246, .b = 180, .a = 232 }),
        .powerup => gameplay_billboard.drawTexture(render.resources.sprites.ring_big.?.texture, position, 0.72 * scale, 0.72 * scale, camera, render.billboard_shader, .white),
        .explode => gameplay_billboard.drawTexture(render.resources.sprites.explode_big.?.texture, position, 0.72 * scale, 0.72 * scale, camera, render.billboard_shader, .white),
        .slow => gameplay_billboard.drawTexture(render.resources.sprites.slow_ring_big.?.texture, position, 0.72 * scale, 0.72 * scale, camera, render.billboard_shader, .white),
    }
}

fn drawGameplayRuntimeRingEffectActor(
    render: Context,
    camera: rl.Camera3D,
    effect: gameplay_runtime_entities.RingEffect,
) void {
    const ring_kind = gameplay.nativeRuntimeRingKindLabel(effect.kind) orelse return;
    drawGameplayRingSprite(render, camera, effect.presentation_position, effect.presentation_scale, ring_kind);

    if (runtimeRingParticleSpriteFamily(effect.kind)) |family| {
        drawRuntimeRingParticleHalo(render, camera, effect, family);
    }
}

fn drawRuntimeRingParticleHalo(
    render: Context,
    camera: rl.Camera3D,
    effect: gameplay_runtime_entities.RingEffect,
    family: RuntimeRingParticleSpriteFamily,
) void {
    const texture = runtimeRingParticleTexture(render, family);
    const sprite_size = native_runtime_ring_particle_size * effect.presentation_scale;
    const radius = native_runtime_ring_particle_radius * effect.presentation_scale;
    for (0..native_runtime_ring_particle_count) |child_index| {
        gameplay_billboard.drawTexture(
            texture,
            runtimeRingParticlePosition(effect.presentation_position, effect.active_phase, child_index, radius),
            sprite_size,
            sprite_size,
            camera,
            render.billboard_shader,
            .{ .r = 255, .g = 255, .b = 255, .a = native_runtime_ring_particle_alpha },
        );
    }
}

fn runtimeRingParticleSpriteFamily(effect_kind: u8) ?RuntimeRingParticleSpriteFamily {
    return switch (effect_kind) {
        4, 5, 8 => .ring,
        2, 6 => .explode,
        3, 7 => .slow,
        else => null,
    };
}

fn runtimeRingParticleTexture(render: Context, family: RuntimeRingParticleSpriteFamily) rl.Texture2D {
    switch (family) {
        .ring => return render.resources.sprites.ring.?.texture,
        .explode => return render.resources.sprites.explode_small.?.texture,
        .slow => return render.resources.sprites.slow_ring.?.texture,
    }
}

fn runtimeRingParticlePosition(base: rl.Vector3, phase: f32, child_index: usize, radius: f32) rl.Vector3 {
    const child_phase = phase + @as(f32, @floatFromInt(child_index)) * native_runtime_ring_particle_phase_step;
    return .{
        .x = base.x + std.math.sin(child_phase) * radius,
        .y = base.y + std.math.cos(child_phase) * radius,
        .z = base.z,
    };
}

fn drawGameplayTrackParcelActor(
    render: Context,
    camera: rl.Camera3D,
    parcel: gameplay_runtime_entities.TrackParcel,
) void {
    const loaded_texture = render.resources.sprites.parcel.?;
    const position = parcel.presentationPosition();
    const scale = parcel.presentationScale();
    gameplay_billboard.drawTexture(
        loaded_texture.texture,
        position,
        0.56 * scale,
        0.56 * scale,
        camera,
        render.billboard_shader,
        if (parcel.parcel_id == 0)
            .white
        else
            .{ .r = 196, .g = 255, .b = 196, .a = 232 },
    );
}

fn gameplayLaneWorldPosition(preview: *const track.LoadedLevelPreview, global_row: usize, lane_index: usize, y_offset: f32) rl.Vector3 {
    const floor_height = preview.floorHeightAtCellCenter(global_row, lane_index) orelse 0.0;
    return preview.worldPositionForLane(@as(f32, @floatFromInt(lane_index)) + 0.5, @as(f32, @floatFromInt(global_row)), floor_height + y_offset);
}

pub fn drawBarrier(render: Context, loaded_track_preview: *const track.LoadedLevelPreview, runner: gameplay.Runner) void {
    const loaded_object = if (render.resources.barrier_object) |*loaded_object|
        loaded_object
    else
        null;
    gameplay_barrier_render.draw(
        loaded_object,
        loaded_track_preview,
        runner,
        render.is_tutorial_level,
    );
}

fn drawGameplayProjectileActor(render: Context, camera: rl.Camera3D, projectile: gameplay.Projectile) void {
    if (projectile.kind == .turbo) {
        drawGameplayBlasterProjectileActor(render, camera, projectile);
        return;
    }

    gameplay_projectile_render.draw(.{
        .lazer_object = &render.resources.lazer_object.?,
        .vapour_lazer_object = &render.resources.vapour_lazer_object.?,
        .rocket_model = &render.resources.rocket_model.?,
    }, projectile);
}

fn drawGameplayBlasterProjectileActor(render: Context, camera: rl.Camera3D, projectile: gameplay.Projectile) void {
    drawGameplayBlasterProjectileTrail(render, camera, projectile);
    const texture = render.resources.sprites.blaster_projectile.?.texture;
    const position: rl.Vector3 = .{
        .x = projectile.world_x,
        .y = projectile.world_y,
        .z = projectile.world_z,
    };
    const roll = @as(f32, @floatCast(render.render_time_seconds)) * 4.0 + projectile.world_z * 0.19 + projectile.world_x;
    gameplay_billboard.drawTextureRectRolled(
        texture,
        .{ .x = 0.0, .y = 0.0, .width = @floatFromInt(texture.width), .height = @floatFromInt(texture.height) },
        position,
        0.49,
        0.49,
        camera,
        render.billboard_shader,
        roll,
        .white,
    );
}

fn drawGameplayBlasterProjectileTrail(render: Context, camera: rl.Camera3D, projectile: gameplay.Projectile) void {
    const texture = render.resources.sprites.blaster_trail.?.texture;
    const source: rl.Rectangle = .{ .x = 0.0, .y = 0.0, .width = @floatFromInt(texture.width), .height = @floatFromInt(texture.height) };
    const offsets = [_]f32{ 0.0, 0.3, 0.6 };
    const tints = [_]rl.Color{
        .{ .r = 255, .g = 255, .b = 255, .a = 220 },
        .{ .r = 255, .g = 255, .b = 255, .a = 170 },
        .{ .r = 255, .g = 255, .b = 255, .a = 120 },
    };
    for (offsets, tints) |offset, tint| {
        gameplay_billboard.drawTextureRectRolled(
            texture,
            source,
            blasterTrailPosition(projectile, offset),
            0.2,
            0.2,
            camera,
            render.billboard_shader,
            projectile.world_z * 0.31 + offset * 2.4,
            tint,
        );
    }
}

fn blasterTrailPosition(projectile: gameplay.Projectile, movement_delta_factor: f32) rl.Vector3 {
    const current: rl.Vector3 = .{
        .x = projectile.world_x,
        .y = projectile.world_y,
        .z = projectile.world_z,
    };
    if (projectile.trail_count < 2) {
        return .{
            .x = current.x - projectile.dir_x * movement_delta_factor,
            .y = current.y - projectile.dir_y * movement_delta_factor,
            .z = current.z - projectile.dir_z * movement_delta_factor,
        };
    }

    const previous = projectile.trail_points[projectile.trail_count - 2];
    const delta: rl.Vector3 = .{
        .x = current.x - previous.x,
        .y = current.y - previous.y,
        .z = current.z - previous.z,
    };
    return .{
        .x = current.x - delta.x * movement_delta_factor,
        .y = current.y - delta.y * movement_delta_factor,
        .z = current.z - delta.z * movement_delta_factor,
    };
}

fn drawGameplaySubLazerSlotActor(render: Context, camera: rl.Camera3D, slot: gameplay_runtime_entities.SubLazerSlot) void {
    // Native `cRSubLazerManager` slots render through the same LAZER/VAPOURLAZER
    // asset family as projectile shots; the Wall2 tile is only the emitter.
    drawGameplayProjectileActor(render, camera, .{
        .active = true,
        .kind = .sub_lazer,
        .world_x = slot.world_position.x,
        .world_y = slot.visual_y,
        .world_z = slot.world_position.z,
        .dir_x = slot.velocity.x,
        .dir_y = slot.velocity.y,
        .dir_z = slot.velocity.z,
    });
}

fn drawGameplayEffects(render: Context, camera: rl.Camera3D) void {
    const smoke_texture = render.resources.sprites.smoke.?;
    for (render.effects.jet_particles) |particle| {
        if (!particle.active or particle.width <= 0.0 or particle.height <= 0.0) continue;
        gameplay_billboard.drawTextureBlended(
            smoke_texture.texture,
            particle.position,
            particle.width,
            particle.height,
            camera,
            render.billboard_shader,
            particle.tint,
            .additive,
        );
    }

    const nuke_texture = render.resources.sprites.explode_big.?;
    for (render.effects.nuke_particles) |particle| {
        if (!particle.active or particle.width <= 0.0 or particle.height <= 0.0) continue;
        gameplay_billboard.drawTexture(
            nuke_texture.texture,
            particle.position,
            particle.width,
            particle.height,
            camera,
            render.billboard_shader,
            particle.tint,
        );
    }

    for (0..render.effects.count) |index| {
        const effect = render.effects.items[index];
        if (!effect.active or effect.ticks_remaining == 0) continue;
        const loaded_texture = switch (effect.kind) {
            .explode_big => render.resources.sprites.explode_big.?,
            .explode_small => render.resources.sprites.explode_small.?,
            .slug_goo => render.resources.sprites.slug_goo.?,
            .smoke => render.resources.sprites.smoke.?,
        };
        gameplay_billboard.drawTextureBlended(
            loaded_texture.texture,
            effect.position,
            effect.width,
            effect.height,
            camera,
            render.billboard_shader,
            effect.tint,
            effectBlendMode(effect.kind),
        );
    }
}

fn effectBlendMode(kind: gameplay_effects.Kind) gameplay_billboard.BlendMode {
    return switch (kind) {
        .smoke => .additive,
        else => .alpha,
    };
}

test "smoke effects use native additive sprite blend lane" {
    try std.testing.expectEqual(gameplay_billboard.BlendMode.additive, effectBlendMode(.smoke));
    try std.testing.expectEqual(gameplay_billboard.BlendMode.alpha, effectBlendMode(.explode_big));
    try std.testing.expectEqual(gameplay_billboard.BlendMode.alpha, effectBlendMode(.explode_small));
    try std.testing.expectEqual(gameplay_billboard.BlendMode.alpha, effectBlendMode(.slug_goo));
}

pub fn drawTurbo(
    render: Context,
    loaded_track_preview: *const track.LoadedLevelPreview,
    runner: gameplay.Runner,
    camera: rl.Camera3D,
) void {
    const model = gameplay_resources.activeTurbo(render.resources) orelse return;
    const click_start_active = render.click_start_active;
    const pose = if (click_start_active and render.tutorial_click_start_cutscene_active)
        gameplay_model_render.tutorialClickStartTurboPose(model, loaded_track_preview, runner)
    else
        gameplay_model_render.turboPose(model, loaded_track_preview, runner);
    model.drawEx(pose.transform);
    model.drawToonOutlineEx(pose.transform, camera, .black);

    if (click_start_active) return;
    drawGameplayTurboAttachments(render, pose.transform, pose.position, pose.right, pose.up, pose.forward, runner, camera);
}

fn drawGameplayTurboAttachments(
    render: Context,
    turbo_transform: rl.Matrix,
    position: rl.Vector3,
    right: rl.Vector3,
    up: rl.Vector3,
    forward: rl.Vector3,
    runner: gameplay.Runner,
    camera: rl.Camera3D,
) void {
    const channel_states = gameplay.nativeWeaponChannelStates(runner.presentation.movement_flags);

    // Weapon X2s are already authored in Turbo-local coordinates; reuse the same pose
    // transform instead of re-centering them like standalone pickup models.
    const top_active = channel_states.center == 1 or
        render.weapon_visual_state.top_draw_ticks > 0 or
        render.weapon_visual_state.top_hide_ticks > 0;
    if (top_active) {
        if (render.resources.blaster_top_models.currentModel(
            render.weapon_visual_state.top_draw_ticks,
            render.weapon_visual_state.top_fire_ticks,
            render.weapon_visual_state.top_hide_ticks,
        )) |model| {
            gameplay_model_render.drawUploadedModelWithToonOutlineEx(
                model,
                turbo_transform,
                camera,
            );
        }
    }

    const left_active = channel_states.left != 0 or
        render.weapon_visual_state.left_draw_ticks > 0 or
        render.weapon_visual_state.left_hide_ticks > 0;
    if (left_active) {
        const left_selected_state = render.weapon_visual_state.sideSelectedState(channel_states.left, true);
        const left_model = switch (left_selected_state) {
            1 => render.resources.blaster_left_models.currentModel(
                render.weapon_visual_state.left_draw_ticks,
                0,
                render.weapon_visual_state.left_hide_ticks,
            ),
            2 => render.resources.laser_left_models.currentModel(
                render.weapon_visual_state.left_draw_ticks,
                0,
                render.weapon_visual_state.left_hide_ticks,
            ),
            else => null,
        };
        if (left_model) |model| {
            gameplay_model_render.drawUploadedModelWithToonOutlineEx(
                model,
                turbo_transform,
                camera,
            );
        }
    }

    const right_active = channel_states.right != 0 or
        render.weapon_visual_state.right_draw_ticks > 0 or
        render.weapon_visual_state.right_hide_ticks > 0;
    if (right_active) {
        const right_selected_state = render.weapon_visual_state.sideSelectedState(channel_states.right, false);
        const right_model = switch (right_selected_state) {
            1 => render.resources.blaster_right_models.currentModel(
                render.weapon_visual_state.right_draw_ticks,
                0,
                render.weapon_visual_state.right_hide_ticks,
            ),
            2 => render.resources.laser_right_models.currentModel(
                render.weapon_visual_state.right_draw_ticks,
                0,
                render.weapon_visual_state.right_hide_ticks,
            ),
            else => null,
        };
        if (right_model) |model| {
            gameplay_model_render.drawUploadedModelWithToonOutlineEx(
                model,
                turbo_transform,
                camera,
            );
        }
    }

    const rocket_active = channel_states.center == 3 or
        render.weapon_visual_state.rocket_draw_ticks > 0 or
        render.weapon_visual_state.rocket_hide_ticks > 0;
    if (rocket_active) {
        if (render.resources.rocket_launcher_models.currentModel(
            render.weapon_visual_state.rocket_draw_ticks,
            0,
            render.weapon_visual_state.rocket_hide_ticks,
        )) |model| {
            gameplay_model_render.drawUploadedModelWithToonOutlineEx(
                model,
                turbo_transform,
                camera,
            );
        }
    }

    const jetpack_visual_active = gameplay_presentation.nativeJetpackVisualPresentationActive(runner.jetpack.thrust_visual_active);
    const jetpack_visible = jetpack_visual_active or
        render.jetpack_visual_state.draw_ticks > 0 or
        render.jetpack_visual_state.hide_ticks > 0;
    if (jetpack_visible) {
        if (render.resources.jetpack_thrust_models.currentModel(
            render.jetpack_visual_state.draw_ticks,
            jetpack_visual_active,
            render.jetpack_visual_state.hide_ticks,
            render.render_time_seconds,
        )) |model| {
            gameplay_model_render.drawUploadedModelWithToonOutline(
                model,
                gameplay_model_render.offsetPosition(position, right, up, forward, 0.0, 0.10, -0.18),
                right,
                up,
                forward,
                .{ .x = 0.24, .y = 0.24, .z = 0.24 },
                camera,
            );
        }
    }

    if (gameplay.movementFlagsInvincible(runner.presentation.movement_flags)) {
        if (render.resources.invincible_models.currentModel(render.render_time_seconds)) |model| {
            gameplay_model_render.drawUploadedModel(
                model.*,
                gameplay_model_render.offsetPosition(position, right, up, forward, 0.0, 0.02, 0.0),
                right,
                up,
                forward,
                .{ .x = 1.05, .y = 1.05, .z = 1.05 },
                .{ .r = 220, .g = 240, .b = 255, .a = 180 },
            );
        }
    }
}

test "runtime powerup rings use the native particle-ring sprite family" {
    try std.testing.expectEqual(RuntimeRingParticleSpriteFamily.ring, runtimeRingParticleSpriteFamily(8).?);
    try std.testing.expectEqual(RuntimeRingParticleSpriteFamily.ring, runtimeRingParticleSpriteFamily(5).?);
    try std.testing.expectEqual(RuntimeRingParticleSpriteFamily.explode, runtimeRingParticleSpriteFamily(6).?);
    try std.testing.expectEqual(RuntimeRingParticleSpriteFamily.slow, runtimeRingParticleSpriteFamily(7).?);
}

test "native runtime ring halo positions ten sprites around the parent" {
    const base = rl.Vector3{ .x = 2.0, .y = 3.0, .z = 4.0 };
    const first = runtimeRingParticlePosition(base, 0.0, 0, native_runtime_ring_particle_radius);
    try std.testing.expectApproxEqAbs(base.x, first.x, 0.0001);
    try std.testing.expectApproxEqAbs(base.y + native_runtime_ring_particle_radius, first.y, 0.0001);
    try std.testing.expectApproxEqAbs(base.z, first.z, 0.0001);

    const opposite = runtimeRingParticlePosition(base, 0.0, 5, native_runtime_ring_particle_radius);
    try std.testing.expectApproxEqAbs(base.x, opposite.x, 0.0001);
    try std.testing.expectApproxEqAbs(base.y - native_runtime_ring_particle_radius, opposite.y, 0.0001);
    try std.testing.expectApproxEqAbs(base.z, opposite.z, 0.0001);
}

test "native blaster trail points use recovered movement-delta offsets" {
    const projectile = gameplay.Projectile{
        .world_x = 12.0,
        .world_y = 1.0,
        .world_z = 24.0,
        .trail_points = .{
            .{ .x = 10.0, .y = 1.0, .z = 20.0 },
            .{},
            .{},
            .{},
        },
        .trail_count = 2,
    };

    const current = blasterTrailPosition(projectile, 0.0);
    try std.testing.expectApproxEqAbs(@as(f32, 12.0), current.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 24.0), current.z, 0.0001);

    const mid = blasterTrailPosition(projectile, 0.3);
    try std.testing.expectApproxEqAbs(@as(f32, 11.4), mid.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 22.8), mid.z, 0.0001);

    const tail = blasterTrailPosition(projectile, 0.6);
    try std.testing.expectApproxEqAbs(@as(f32, 10.8), tail.x, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 21.6), tail.z, 0.0001);
}

test "Wall2 render only draws the native merged object owner" {
    var runtime_tiles = [_]u8{ 0x0e, 0x0e, 0x0e, 0x23 };
    var warn_surface = [_]bool{ false, false, false, false };
    var surface_swap = [_]bool{ false, false, false, false };
    var flag_b40 = [_]bool{ true, false, false, false };
    var edge_masks = [_]u8{ 0, 0, 0, 0 };
    var preview: track.LoadedLevelPreview = undefined;
    preview.total_rows = 1;
    preview.max_width = runtime_tiles.len;
    preview.runtime_tiles = &runtime_tiles;
    preview.render_cache = .{
        .warn_surface_grid = &warn_surface,
        .surface_swap_grid = &surface_swap,
        .flag_b40_grid = &flag_b40,
        .edge_masks = &edge_masks,
    };

    try std.testing.expect(wall2PillarActorVisible(&preview, 0, 0));
    try std.testing.expect(!wall2PillarActorVisible(&preview, 0, 1));
    try std.testing.expect(!wall2PillarActorVisible(&preview, 0, 2));
    try std.testing.expect(!wall2PillarActorVisible(&preview, 0, 3));
    try std.testing.expectEqual(@as(?track.GameplayCellKind, null), track.gameplayCellKindForRuntimeTile(0x0e));
}

test "Wall2 render selects native pillar model by merged strip width" {
    var runtime_tiles = [_]u8{ 0x0e, 0x0e, 0x0e, 0x23 };
    var warn_surface = [_]bool{ false, false, false, false };
    var surface_swap = [_]bool{ false, false, false, false };
    var flag_b40 = [_]bool{ true, false, false, false };
    var edge_masks = [_]u8{ 0, 0, 0, 0 };
    var preview: track.LoadedLevelPreview = undefined;
    preview.total_rows = 1;
    preview.max_width = runtime_tiles.len;
    preview.runtime_tiles = &runtime_tiles;
    preview.render_cache = .{
        .warn_surface_grid = &warn_surface,
        .surface_swap_grid = &surface_swap,
        .flag_b40_grid = &flag_b40,
        .edge_masks = &edge_masks,
    };

    try std.testing.expectEqual(Wall2PillarModelInfo{ .model_index = 2, .run_length = 3 }, wall2PillarModelInfo(&preview, 0, 0).?);
    try std.testing.expectEqual(@as(?Wall2PillarModelInfo, null), wall2PillarModelInfo(&preview, 0, 1));
}
