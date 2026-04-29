const rl = @import("raylib");

const gameplay = @import("../gameplay.zig");
const object = @import("../object.zig");
const track = @import("../track.zig");

pub fn draw(
    maybe_loaded_object: ?*const object.LoadedObject,
    loaded_track_preview: *const track.LoadedLevelPreview,
    runner: gameplay.Runner,
    is_tutorial_level: bool,
) void {
    const loaded_object = maybe_loaded_object orelse return;
    // Native barrier visibility follows `Game.level_mode == FrontendLevelMode.tutorial`
    // (= 7): `initialize_tutorial` (0x448da0) sets `runtime_flags |= 0x600000` and
    // `set_subgame_features` (0x435df0) maps the tutorial mode to 0xe4cfff;
    // `initialize_tutorial` then clears the low garbage-fallback bit but keeps
    // the barrier bits. NoFall segments additionally expose the barrier in
    // non-tutorial modes via the per-row annotation.
    const tutorial_active = runner.session_mode == .tutorial or is_tutorial_level;
    const barrier_active = tutorial_active or runner.current_annotation == .no_fall;
    if (!barrier_active) return;

    const runner_position = runner.worldPosition(loaded_track_preview, 0.4);
    // `update_barrier_ai` 0x440f80 updates only the object-space Y/Z slots:
    // `y = 0.4`, `z = owner->+0x70` (player z). The barrier mesh is authored in
    // world orientation, so the draw should follow the owner without inventing
    // an extra upright rotation.
    const world_transform = rl.Matrix.translate(0.0, 0.4, runner_position.z);
    // What we know from the native decompile:
    //
    //   - The mesh is two thin horizontal quads at x=-4.5/4.5, y=-0.3/0.3, z=-18..+40
    //     (see OBJECTS/BARRIER/_OBJECT.TXT; the Wii and Android ports ship the
    //     same vertices).
    //   - BARRIER.TGA is a 4x4 vertical gradient (dark blue -> bright blue ->
    //     dark blue) with alpha=255 everywhere.
    //   - Windows barrier setup stores object tint `(1, 1, 1, 0.8)` and blend
    //     preset `7` in `initialize_game_assets_and_world` (0x40acf0).
    //   - Windows texture load `sub_412a70` tags 32-bit TGA textures with
    //     `TextureRef.flags |= 0x10000`; `render_object` (0x4126c0) only enters
    //     `set_blend_mode(...)` when object alpha != 1 and that flag is set.
    //     BARRIER.TGA is 32-bit, so the barrier definitely takes the blended
    //     grouped-object path.
    //   - Windows `set_blend_mode(7)` resolves to additive blending
    //     (`SRC=ONE`, `DEST=ONE`).
    //   - Android barrier setup stores the same tint `(1, 1, 1, 0.8)` and
    //     assigns blend preset `3`; `G0SetBlend(3)` is also additive and
    //     explicitly disables depth writes for the draw.
    //   - Native grouped-object draws keep back-face culling enabled unless the
    //     object sets the `0x100000` opt-out flag. Barrier init does not set it.
    //
    // Port choice:
    // Use the recovered additive path and disable depth writes for the draw so
    // the translucent barrier does not stamp the later scene. This matches the
    // Android renderer directly, and it is the only way the Windows additive
    // barrier can behave without the Z corruption we saw in the port.
    //
    // We still disable back-face culling in the port. The authored barrier
    // quads point outward from the track center (`+X` on the right strip,
    // `-X` on the left strip), so our raylib/OpenGL mesh winding hides the
    // interior faces when culling is left on.
    rl.beginBlendMode(.additive);
    defer rl.endBlendMode();
    rl.gl.rlDisableDepthMask();
    defer rl.gl.rlEnableDepthMask();
    rl.gl.rlDisableBackfaceCulling();
    defer rl.gl.rlEnableBackfaceCulling();
    const barrier_tint = rl.Color{ .r = 255, .g = 255, .b = 255, .a = 204 };
    loaded_object.drawTintedEx(world_transform, barrier_tint);
}
