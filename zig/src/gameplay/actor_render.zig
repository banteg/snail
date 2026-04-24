const std = @import("std");
const rl = @import("raylib");

const game_font = @import("../game_font.zig");
const gameplay = @import("../gameplay.zig");
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
            const sample = loaded_track_preview.gameplayCellSampleAt(global_row, lane_index) orelse continue;
            switch (sample.kind) {
                .slug => drawGameplaySlugActor(render, loaded_track_preview, runner, camera, global_row, lane_index),
                .ring => {
                    if (gameplay_render_policy.staticRingVisible(loaded_track_preview, row_location, loaded_track_preview.runtimeTileAt(global_row, lane_index))) {
                        drawGameplayStaticRingActor(render, loaded_track_preview, camera, row_location, lane_index);
                    }
                },
                .health, .jetpack, .attachment_probe, .attachment_entry, .trampoline, .garbage, .salt => {},
            }
            if (row_location.row.cells[lane_index] == '=') {
                drawGameplayTurretActor(render, loaded_track_preview, runner, global_row, lane_index);
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

    for (runner.activeProjectiles()) |projectile| {
        drawGameplayProjectileActor(render, projectile);
    }

    drawGameplayEffects(render, camera);
}

fn drawGameplaySlugActor(
    render: Context,
    preview: *const track.LoadedLevelPreview,
    runner: gameplay.Runner,
    camera: rl.Camera3D,
    global_row: usize,
    lane_index: usize,
) void {
    if (runner.isSlugDefeated(global_row, lane_index)) return;

    // Native slug hazards spawn a world sprite with size lanes +0x60/+0x64 both seeded to 2.0,
    // and `draw_sprite_quad` treats that blended value as the quad half-extent.
    const slug_sprite_half_extent: f32 = 2.0;
    const slug_sprite_world_size: f32 = slug_sprite_half_extent * 2.0;
    const slug_sprite_y_offset: f32 = 1.7;
    // Native `spawn_slug_hazard` allocates the live sprite with texture ref 118 (`SLUG000`), and
    // `update_slug_hazard_ai` only switches to 119/120 during non-default state-machine branches.
    // So authored live slugs should not free-run a local blink in the port.
    const loaded_texture = render.resources.sprites.slug_frames[0] orelse return;
    const position = gameplayLaneWorldPosition(preview, global_row, lane_index, slug_sprite_y_offset);
    gameplay_billboard.drawTextureRect(
        loaded_texture.texture,
        .{ .x = 0.0, .y = 0.0, .width = @floatFromInt(loaded_texture.texture.width), .height = @floatFromInt(loaded_texture.texture.height) },
        position,
        slug_sprite_world_size,
        slug_sprite_world_size,
        camera,
        render.billboard_shader,
        .white,
    );
}

fn drawGameplayGarbageActor(
    render: Context,
    preview: *const track.LoadedLevelPreview,
    camera: rl.Camera3D,
    hazard: gameplay_runtime_entities.Hazard,
) void {
    _ = preview;
    if (hazard.state == .inactive) return;
    const variant_index = @as(usize, @intCast((hazard.row + hazard.lane * 3) % gameplay_assets.gameplay_garbage_sprite_paths.len));
    const loaded_texture = render.resources.sprites.garbage_variants[variant_index] orelse return;
    gameplay_billboard.drawTextureRectRolled(
        loaded_texture.texture,
        .{ .x = 0.0, .y = 0.0, .width = @floatFromInt(loaded_texture.texture.width), .height = @floatFromInt(loaded_texture.texture.height) },
        hazard.world_position,
        hazard.presentation_scale,
        hazard.presentation_scale,
        camera,
        render.billboard_shader,
        hazard.presentation_phase + (@as(f32, @floatCast(render.render_time_seconds)) * 1.75),
        .{ .r = 255, .g = 255, .b = 255, .a = if (hazard.state == .active) 232 else 255 },
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
        const world_transform = gameplay_model_render.transformFromBasis(world_position, right, up, forward);
        const local_offset = rl.Matrix.translate(
            -model.bounds.center.x,
            -model.bounds.center.y,
            -model.bounds.center.z,
        );
        const scale_value = 0.46;
        const scale = rl.Matrix.scale(scale_value, scale_value, scale_value);
        model.drawTintedEx(
            world_transform.multiply(local_offset).multiply(scale),
            .{ .r = 255, .g = 255, .b = 255, .a = presentation_alpha },
        );
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

fn drawGameplayTurretActor(
    render: Context,
    preview: *const track.LoadedLevelPreview,
    runner: gameplay.Runner,
    global_row: usize,
    lane_index: usize,
) void {
    const flash_ticks = runner.turretFlashTicksAt(global_row, lane_index);
    const model = blk: {
        if (flash_ticks > 0) {
            if (render.resources.blaster_top_models.fire) |*fire_model| break :blk fire_model.*;
        }
        break :blk render.resources.turret_model orelse return;
    };
    const floor_height = preview.floorHeightAtCellCenter(global_row, lane_index) orelse 0.0;
    const position = preview.worldPositionForLane(
        @as(f32, @floatFromInt(lane_index)) + 0.5,
        @as(f32, @floatFromInt(global_row)),
        floor_height + 0.18,
    );
    gameplay_model_render.drawUploadedModel(
        model,
        position,
        .{ .x = 1.0, .y = 0.0, .z = 0.0 },
        .{ .x = 0.0, .y = 1.0, .z = 0.0 },
        .{ .x = 0.0, .y = 0.0, .z = 1.0 },
        .{ .x = 0.34, .y = 0.34, .z = 0.34 },
        null,
    );
}

fn drawGameplayHealthPickupActor(
    render: Context,
    camera: rl.Camera3D,
    pickup: gameplay_runtime_entities.Pickup,
) void {
    const loaded_texture = render.resources.sprites.health orelse return;
    gameplay_billboard.drawTexture(loaded_texture.texture, pickup.presentation_position, 0.52, 0.52, camera, render.billboard_shader, .white);
}

fn drawGameplayJetpackPickupActor(
    render: Context,
    camera: rl.Camera3D,
    pickup: gameplay_runtime_entities.Pickup,
) void {
    const frame_index: usize = @intFromFloat(@mod(@floor(render.render_time_seconds * 8.0), @as(f64, @floatFromInt(gameplay_assets.gameplay_jetpack_sprite_paths.len))));
    const loaded_texture = render.resources.sprites.jetpack_frames[frame_index] orelse return;
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
    switch (ring_kind) {
        .none => {},
        .normal => if (render.resources.sprites.ring) |loaded_texture| {
            gameplay_billboard.drawTexture(loaded_texture.texture, position, 0.46, 0.46, camera, render.billboard_shader, .{ .r = 255, .g = 246, .b = 180, .a = 232 });
        },
        .powerup => if (render.resources.sprites.powerup) |loaded_texture| {
            gameplay_billboard.drawTexture(loaded_texture.texture, position, 0.64, 0.64, camera, render.billboard_shader, .white);
        },
        .explode => if (render.resources.sprites.ring_big) |loaded_texture| {
            gameplay_billboard.drawTexture(loaded_texture.texture, position, 0.72, 0.72, camera, render.billboard_shader, .{ .r = 255, .g = 220, .b = 120, .a = 232 });
        },
        .slow => if (render.resources.sprites.slow_ring) |loaded_texture| {
            gameplay_billboard.drawTexture(loaded_texture.texture, position, 0.5, 0.5, camera, render.billboard_shader, .white);
        },
    }
}

fn drawGameplayRuntimeRingEffectActor(
    render: Context,
    camera: rl.Camera3D,
    effect: gameplay_runtime_entities.RingEffect,
) void {
    const ring_kind = gameplay.nativeRuntimeRingKindLabel(effect.kind) orelse return;
    const position = effect.presentation_position;
    const scale = effect.presentation_scale;
    switch (ring_kind) {
        .none => {},
        .normal => if (render.resources.sprites.ring) |loaded_texture| {
            gameplay_billboard.drawTexture(loaded_texture.texture, position, 0.46 * scale, 0.46 * scale, camera, render.billboard_shader, .{ .r = 255, .g = 246, .b = 180, .a = 232 });
        },
        .powerup => if (render.resources.sprites.powerup) |loaded_texture| {
            gameplay_billboard.drawTexture(loaded_texture.texture, position, 0.64 * scale, 0.64 * scale, camera, render.billboard_shader, .white);
        },
        .explode => if (render.resources.sprites.ring_big) |loaded_texture| {
            gameplay_billboard.drawTexture(loaded_texture.texture, position, 0.72 * scale, 0.72 * scale, camera, render.billboard_shader, .{ .r = 255, .g = 220, .b = 120, .a = 232 });
        },
        .slow => if (render.resources.sprites.slow_ring) |loaded_texture| {
            gameplay_billboard.drawTexture(loaded_texture.texture, position, 0.5 * scale, 0.5 * scale, camera, render.billboard_shader, .white);
        },
    }
}

fn drawGameplayTrackParcelActor(
    render: Context,
    camera: rl.Camera3D,
    parcel: gameplay_runtime_entities.TrackParcel,
) void {
    const loaded_texture = render.resources.sprites.parcel orelse return;
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

fn drawGameplayProjectileActor(render: Context, projectile: gameplay.Projectile) void {
    const lazer_object = if (render.resources.lazer_object) |*loaded_object|
        loaded_object
    else
        null;
    const vapour_lazer_object = if (render.resources.vapour_lazer_object) |*loaded_object|
        loaded_object
    else
        null;
    const rocket_model = if (render.resources.rocket_model) |*model|
        model
    else
        null;
    gameplay_projectile_render.draw(.{
        .lazer_object = lazer_object,
        .vapour_lazer_object = vapour_lazer_object,
        .rocket_model = rocket_model,
    }, projectile);
}

fn drawGameplayEffects(render: Context, camera: rl.Camera3D) void {
    for (0..render.effects.count) |index| {
        const effect = render.effects.items[index];
        if (!effect.active or effect.ticks_remaining == 0) continue;
        const loaded_texture = switch (effect.kind) {
            .explode_big => render.resources.sprites.explode_big,
            .explode_small => render.resources.sprites.explode_small,
            .slug_goo => render.resources.sprites.slug_goo,
            .smoke => render.resources.sprites.smoke,
        } orelse continue;
        gameplay_billboard.drawTexture(
            loaded_texture.texture,
            effect.position,
            effect.width,
            effect.height,
            camera,
            render.billboard_shader,
            effect.tint,
        );
    }
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

    if (runner.presentation.invincible_ticks > 0) {
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
