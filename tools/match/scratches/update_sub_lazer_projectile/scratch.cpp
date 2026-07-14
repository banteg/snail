// update_sub_lazer_projectile @ 0x4417d0 (thiscall, ret)
// Recycle-pending inlines the live-list removal; active integrates,
// bounds-checks, and runs the two attachment containment probes before Kill.

#include "game_root.h"
#include "vector3.h"
#include "sub_lazer_types.h"
#include "subgame_runtime.h"
#include "track_attachment_types.h"

extern GameRoot* g_game; // data_4df904
extern char g_lazer_path2_kill_format[]; // data_4a4f40
extern char g_lazer_path_kill_format[]; // data_4a4f54
int debug_report_stub(void* arg); // @ 0x449c00, stripped to xor eax/ret in release
int report_errorf(char* format, ...);

void SubLazer::update_sub_lazer_projectile()
{
    if (owner_game->subgame_pause_gate)
        return;
    switch (state) {
    case SUB_LAZER_STATE_RECYCLE_PENDING: {
        g_game->active_bod_list.remove_bod(this);
        state = SUB_LAZER_STATE_INACTIVE;
        return;
    }
    case SUB_LAZER_STATE_ACTIVE: {
        float* progress = &sprite_bob_phase;
        float* progress_step = &sprite_bob_phase_step;
        *progress = *progress_step + *progress;
        if (*progress > 1.0f) {
            state = SUB_LAZER_STATE_RECYCLE_PENDING;
            return;
        }
        Vector3* live_position = &transform.position;
        *live_position += velocity;
        if (transform.position.y >= 0.0f
            && transform.position.z >= owner_game->player.interaction_max_z) {
            TrackRowCell* grid =
                g_game->subgame.get_track_grid_cell_at_world_position(live_position);
            SubRow* cell =
                g_game->subgame.get_track_runtime_cell_at_world_z(live_position);
            if (grid->tile_id != 14 || transform.position.y >= 7.0f) {
                if ((cell->flags & 0x40) != 0
                    && cell->primary_attachment_cell->attachment_template_record->is_point_inside_track_attachment(
                        Vector3(velocity.x + live_position->x, velocity.y + live_position->y, velocity.z + live_position->z),
                        velocity * 1.05f,
                        cell->primary_attachment_cell)) {
                    debug_report_stub(g_lazer_path_kill_format);
                    deactivate_sub_lazer_projectile();
                    return;
                }
                if ((cell->flags & 0x80) != 0
                    && cell->secondary_attachment_cell->attachment_template_record->is_point_inside_track_attachment(
                        Vector3(velocity.x + live_position->x, velocity.y + live_position->y, velocity.z + live_position->z),
                        velocity * 1.05f,
                        cell->secondary_attachment_cell)) {
                    debug_report_stub(g_lazer_path2_kill_format);
                    deactivate_sub_lazer_projectile();
                    return;
                }
                return;
            }
        }
        deactivate_sub_lazer_projectile();
        return;
    }
    }
}
