// update_sub_lazer_projectile @ 0x4417d0 (thiscall, ret)
// State 2 inlines the live-list removal; state 1 integrates, bounds-checks,
// and runs the two attachment containment probes before deactivating.

#include "vector3.h"
#include "sub_lazer_types.h"

struct RuntimeTrackCellRef;

struct GridCell {
    char unknown_00[0x3c];
    unsigned char tile; // +0x3c
};

struct AttachmentBody {
    bool is_point_inside_track_attachment(
        Vector3 probe, Vector3 scaled_velocity, RuntimeTrackCellRef* owner);
};

struct AttachmentTemplateRecord {
    char unknown_00[0x38];
    AttachmentBody* body; // +0x38
};

struct RuntimeTrackCell {
    unsigned char flags; // +0x00, 0x40 primary attachment, 0x80 secondary
    char unknown_01[0xa4 - 0x01];
    AttachmentTemplateRecord* primary_attachment;   // +0xa4
    AttachmentTemplateRecord* secondary_attachment; // +0xa8
};

struct TrackRuntime {
    GridCell* get_track_grid_cell_at_world_position(Vector3* position);
    RuntimeTrackCell* get_track_runtime_cell_at_world_z(Vector3* position);
};

class Game {
public:
    char unknown_00[0x9];
    unsigned char subgame_pause_gate; // +0x09
    char unknown_0a[0x5a8 - 0x0a];
    SubLazerListAnchor sub_lazer_free_anchor; // +0x5a8
    char unknown_5b4[0x74618 - 0x5b4];
    TrackRuntime track_runtime; // +0x74618
    char unknown_74619[0x3be0e4 - 0x74619];
    float sub_lazer_kill_plane_z; // +0x3be0e4
};

extern Game* volatile g_game; // data_4df904
extern char g_debug_report_arg[];
int debug_report_stub(void* arg); // @ 0x449c00, stripped to xor eax/ret in release
int report_errorf(char* format, ...);

void SubLazerSlot::update_sub_lazer_projectile()
{
    if (owner_game->subgame_pause_gate)
        return;
    switch (state) {
    case 2: {
        SubLazerListAnchor* anchor = &g_game->sub_lazer_free_anchor;
        int flags = list_flags;
        BodNode* next;
        BodNode* prev;
        if ((flags & 0x200) == 0) {
            report_errorf("List remove");
            state = 0;
            return;
        }
        if ((flags & 0x40) != 0) {
            report_errorf("List remove NEXTBOD");
            state = 0;
            return;
        }
        next = list_next;
        if (next)
            next->list_prev = list_prev;
        prev = list_prev;
        if (prev)
            prev->list_next = list_next;
        else
            anchor->first = list_next;
        list_next = anchor->free_top;
        anchor->free_top = this;
        int updated = list_flags;
        state = 0;
        updated &= ~0x200;
        list_flags = updated;
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
        position.x = velocity.x + position.x;
        position.y = velocity.y + position.y;
        position.z = velocity.z + position.z;
        if (position.y >= 0.0f && position.z >= owner_game->sub_lazer_kill_plane_z) {
            GridCell* grid = g_game->track_runtime.get_track_grid_cell_at_world_position(&position);
            RuntimeTrackCell* cell = g_game->track_runtime.get_track_runtime_cell_at_world_z(&position);
            if (grid->tile != 14 || position.y >= 0.0f) {
                if ((cell->flags & 0x40) == 0
                    || !cell->primary_attachment->body->is_point_inside_track_attachment(
                        Vector3(velocity.x + position.x, velocity.y + position.y, velocity.z + position.z),
                        Vector3(velocity.x * 1.05f, velocity.y * 1.05f, velocity.z * 1.05f),
                        (RuntimeTrackCellRef*)cell->primary_attachment)) {
                    if ((cell->flags & 0x80) == 0)
                        return;
                    if (!cell->secondary_attachment->body->is_point_inside_track_attachment(
                            Vector3(velocity.x + position.x, velocity.y + position.y, velocity.z + position.z),
                            Vector3(velocity.x * 1.05f, velocity.y * 1.05f, velocity.z * 1.05f),
                            (RuntimeTrackCellRef*)cell->secondary_attachment))
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
