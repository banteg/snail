const rl = @import("raylib");

const subgame_camera = @import("../app/subgame_camera.zig");
const actor_render = @import("actor_render.zig");
const gameplay_billboard = @import("billboard.zig");

pub fn draw(state: anytype) void {
    const loaded_track_preview = state.current_track_preview orelse return;
    const runner = state.level_runner;
    const selected_segment_index = if (runner) |live_runner|
        if (loaded_track_preview.locateRow(live_runner.current_global_row)) |row_location|
            row_location.segment_index
        else
            0
    else if (loaded_track_preview.segments.len != 0 and state.level_segment_index < loaded_track_preview.segments.len)
        state.level_segment_index
    else
        0;
    const camera = if (runner != null)
        subgame_camera.levelCamera(&state.subgame_camera, &loaded_track_preview, state.subgame_camera.fov_degrees)
    else
        loaded_track_preview.previewCamera(@floatCast(state.render_time_seconds), selected_segment_index);
    camera.begin();
    defer rl.endMode3D();

    // PORT(partial): native `render_camera` enables linear range fog for the
    // gameplay world pass; menus and previews render with it disabled.
    const fog = gameplay_billboard.FogState{
        .enabled = runner != null,
        .color = if (state.current_game_background) |loaded_background| loaded_background.fogColor() else .white,
        .camera_position = camera.position,
    };
    if (state.gameplay_billboard_shader) |shader| gameplay_billboard.configureFog(shader, fog);
    if (state.gameplay_model_shader) |shader| gameplay_billboard.configureFog(shader, fog);

    if (state.current_game_track_scene) |*scene| {
        scene.drawGameplay(&loaded_track_preview, state.gameplay_billboard_shader, state.gameplay_model_shader);
    } else {
        loaded_track_preview.draw(selected_segment_index);
    }
    const live_runner = runner orelse return;
    const actor_render_context = actor_render.context(state);
    actor_render.drawPostOfficeStopBanners(actor_render_context, &loaded_track_preview, live_runner);
    if (state.gameplay_click_start_active) {
        actor_render.drawTurbo(actor_render_context, &loaded_track_preview, live_runner, camera);
        return;
    }
    actor_render.drawRuntimeActors(actor_render_context, &loaded_track_preview, live_runner, camera);
    actor_render.drawBarrier(actor_render_context, &loaded_track_preview, live_runner);
    actor_render.drawTurbo(actor_render_context, &loaded_track_preview, live_runner, camera);
}
