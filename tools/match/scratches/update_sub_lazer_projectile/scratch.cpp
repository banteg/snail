// update_sub_lazer_projectile @ 0x4417d0 (thiscall, ret)
// State 2 inlines the live-list removal; state 1 integrates, bounds-checks,
// and runs the two attachment containment probes before deactivating.

#include "vector3.h"
#include "sub_lazer_types.h"
#include "subgame_runtime.h"
#include "track_attachment_types.h"

extern char* g_game_base; // data_4df904
extern char g_debug_report_arg[];
int debug_report_stub(void* arg); // @ 0x449c00, stripped to xor eax/ret in release
int report_errorf(char* format, ...);

void SubLazer::update_sub_lazer_projectile()
{
    if (owner_game->subgame_pause_gate)
        return;
    switch (state) {
    case 2: {
        ((BodList*)(g_game_base + 0x5a8))->remove_bod(this);
        state = 0;
        return;
    }
    case 1: {
        float* progress = &sprite_bob_phase;
        float* progress_step = &sprite_bob_phase_step;
        *progress = *progress_step + *progress;
        if (*progress > 1.0f) {
            state = 2;
            return;
        }
        Vector3* live_position = &position;
        live_position->x = velocity.x + live_position->x;
        live_position->y = velocity.y + live_position->y;
        float* live_z = &live_position->z;
        *live_z = velocity.z + *live_z;
        if (position.y >= 0.0f && position.z >= owner_game->player.interaction_max_z) {
            TrackRowCell* grid =
                ((SubgameRuntime*)(g_game_base + 0x74618))->get_track_grid_cell_at_world_position(live_position);
            SubRow* cell =
                ((SubgameRuntime*)(g_game_base + 0x74618))->get_track_runtime_cell_at_world_z(live_position);
            if (grid->tile_id != 14 || position.y >= 7.0f) {
                if ((cell->flags & 0x40) == 0
                    || !cell->primary_attachment_cell->attachment_template_record->is_point_inside_track_attachment(
                        Vector3(velocity.x + live_position->x, velocity.y + live_position->y, velocity.z + live_position->z),
                        velocity * 1.05f,
                        cell->primary_attachment_cell)) {
                    if ((cell->flags & 0x80) == 0)
                        return;
                    if (!cell->secondary_attachment_cell->attachment_template_record->is_point_inside_track_attachment(
                            Vector3(velocity.x + live_position->x, velocity.y + live_position->y, velocity.z + live_position->z),
                            velocity * 1.05f,
                            cell->secondary_attachment_cell))
                        return;
                }
                debug_report_stub(g_debug_report_arg);
                deactivate_sub_lazer_projectile();
                return;
            }
        }
        deactivate_sub_lazer_projectile();
        return;
    }
    }
}
