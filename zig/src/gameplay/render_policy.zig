const gameplay = @import("../gameplay.zig");
const track = @import("../track.zig");
const runtime_entities = @import("runtime_entities.zig");

pub fn actorRowVisible(runner: gameplay.Runner, global_row: usize) bool {
    return @as(f32, @floatFromInt(global_row)) + 0.25 >= runner.row_position;
}

pub fn hazardVisible(runner: gameplay.Runner, hazard: runtime_entities.Hazard) bool {
    const trailing_rows: f32 = switch (hazard.kind) {
        .garbage => switch (hazard.state) {
            .active => @as(f32, 0.25),
            else => @as(f32, 8.0),
        },
    };
    return hazard.world_position.z + trailing_rows >= runner.row_position and
        hazard.world_position.z <= runner.row_position + 72.0;
}

pub fn pickupVisible(runner: gameplay.Runner, pickup: runtime_entities.Pickup) bool {
    return pickup.world_position.z + 0.25 >= runner.row_position and
        pickup.world_position.z <= runner.row_position + 72.0;
}

pub fn ringEffectVisible(runner: gameplay.Runner, effect: runtime_entities.RingEffect) bool {
    return effect.world_position.z + 0.25 >= runner.row_position and
        effect.world_position.z <= runner.row_position + 72.0;
}

pub fn saltSlotVisible(runner: gameplay.Runner, slot: runtime_entities.SaltSlot) bool {
    // Match the legacy salt trailing-rows window so visible behavior is
    // unchanged when rendering migrates from the shared pool to the
    // dedicated salt pool.
    const trailing_rows: f32 = 48.0;
    return slot.world_position.z + trailing_rows >= runner.row_position and
        slot.world_position.z <= runner.row_position + 72.0;
}

pub fn subLazerVisible(runner: gameplay.Runner, slot: runtime_entities.SubLazerSlot) bool {
    return slot.state == .active and
        slot.world_position.z + 8.0 >= runner.row_position and
        slot.world_position.z <= runner.row_position + 72.0;
}

pub fn staticRingVisible(
    preview: *const track.LoadedLevelPreview,
    row_location: track.RowLocation,
    runtime_tile_hint: ?u8,
) bool {
    return !gameplay.runtimeHandledRingAnnotation(runtime_tile_hint, preview.runtimeRowFlagsAt(row_location.global_row));
}
