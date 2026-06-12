// update_salt_hazard @ 0x4417d0 (thiscall, ret)
// State 2 inlines the live-list removal; state 1 integrates, bounds-checks,
// and runs the two attachment containment probes before deactivating.
// NOTE: progress/step at +0x98/+0x9c reach past the 0x98 pool stride into
// the next slot's header dwords, and spawn never initializes them — native
// layout bug, preserved as-is.

struct Vector3 {
    float x;
    float y;
    float z;

    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
};

struct SaltHazardSlot;
struct RuntimeTrackCellRef;

struct SaltListAnchor {
    char unknown_00[4];
    SaltHazardSlot* first;    // +0x04
    SaltHazardSlot* free_top; // +0x08
};

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

struct Game {
    char unknown_00[0x9];
    unsigned char paused; // +0x09
    char unknown_0a[0x5a8 - 0x0a];
    SaltListAnchor salt_free_anchor; // +0x5a8
    char unknown_5b8[0x74618 - 0x5b8];
    TrackRuntime track_runtime; // +0x74618
    char unknown_74619[0x3be0e4 - 0x74619];
    float salt_kill_plane_z; // +0x3be0e4
};

extern Game* volatile g_game; // data_4df904
extern char g_debug_report_arg[];
int debug_report_stub(void* arg); // @ 0x449c00, stripped to xor eax/ret in release
int report_errorf(char* format, ...);

struct SaltHazardSlot {
    void update_salt_hazard();
    void deactivate_salt_hazard(); // @ 0x441740

    int unknown_00;
    unsigned int list_flags;   // +0x04
    SaltHazardSlot* list_prev; // +0x08
    SaltHazardSlot* list_next; // +0x0c
    char unknown_10[0x68 - 0x10];
    Vector3 position;          // +0x68, live-matrix position row
    char unknown_74[0x80 - 0x74];
    int state;                 // +0x80
    char unknown_84[0x88 - 0x84];
    Game* owner_game;          // +0x88
    Vector3 velocity;          // +0x8c (z low byte poked by spawn)
    float progress;            // +0x98, overlaps next slot
    float progress_step;       // +0x9c, overlaps next slot
};

void SaltHazardSlot::update_salt_hazard()
{
    if (owner_game->paused)
        return;
    switch (state) {
    case 2: {
        SaltListAnchor* anchor = &g_game->salt_free_anchor;
        int flags = list_flags;
        if ((flags & 0x200) == 0) {
            report_errorf("List REMOVE");
            state = 0;
            return;
        }
        if ((flags & 0x40) != 0) {
            report_errorf("List REMOVEnext");
            state = 0;
            return;
        }
        if (list_next)
            list_next->list_prev = list_prev;
        if (list_prev)
            list_prev->list_next = list_next;
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
        progress = progress_step + progress;
        if (progress > 1.0f) {
            state = 2;
            return;
        }
        position.x = velocity.x + position.x;
        position.y = velocity.y + position.y;
        position.z = velocity.z + position.z;
        if (position.y >= 0.0f && position.z >= owner_game->salt_kill_plane_z) {
            GridCell* grid = g_game->track_runtime.get_track_grid_cell_at_world_position(&position);
            RuntimeTrackCell* cell = g_game->track_runtime.get_track_runtime_cell_at_world_z(&position);
            if (grid->tile != 14 || position.y >= 7.0f) {
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
                deactivate_salt_hazard();
                return;
            }
        }
        deactivate_salt_hazard();
        return;
    }
    }
}
