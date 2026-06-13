// update_sub_lazer_projectile @ 0x43efb0 (thiscall, ret)
// State 2 -> list remove + kill_sprite; state 1 -> cull behind the owner
// kill plane or advance the wrapped sine bob on the nested sprite. The
// projectile BODY motion lives with the renderable-body owner; this
// update never integrates position. Update-state (+0x38) is distinct
// from the pool free flag (+0x80) used by the shoot scan.

struct SubLazerSlot;

struct FreeAnchor {
    char unknown_00[4];
    SubLazerSlot* first;    // +0x04
    SubLazerSlot* free_top; // +0x08
};

struct Game {
    char unknown_00[0x9];
    unsigned char paused; // +0x09
    char unknown_0a[0x5a8 - 0x0a];
    FreeAnchor free_anchor; // +0x5a8 (shared with the salt pool)
};

struct OwnerRecord {
    char unknown_00[0x2980];
    float kill_plane_z; // +0x2980
};

struct Sprite {
    char unknown_00[0x4c];
    float local_y; // +0x4c
};

extern Game* volatile g_game; // data_4df904
int report_errorf(char* format, ...);
void kill_sprite(Sprite* sprite);
float sine(float radians);

struct SubLazerSlot {
    void update_sub_lazer_projectile();

    int unknown_00;
    unsigned int list_flags;  // +0x04
    SubLazerSlot* list_prev;  // +0x08
    SubLazerSlot* list_next;  // +0x0c
    char unknown_10[0x14 - 0x10];
    float bob_base_y;         // +0x14
    float position_z;         // +0x18
    char unknown_1c[0x38 - 0x1c];
    int state;                // +0x38: 1 live, 2 remove
    OwnerRecord* owner;       // +0x3c
    char unknown_40[0x44 - 0x40];
    Game* owner_game;         // +0x44
    char unknown_48[0x64 - 0x48];
    Sprite* sprite;           // +0x64
    char unknown_68[0x6c - 0x68];
    float bob_phase;          // +0x6c
    float bob_phase_step;     // +0x70
};

void SubLazerSlot::update_sub_lazer_projectile()
{
    if (owner_game->paused)
        return;
    int current = state;
    if (!current)
        return;
    if (current - 1) {
        if (current - 1 == 1) {
            int flags = list_flags;
            state = 0;
            FreeAnchor* anchor = &g_game->free_anchor;
            if ((flags & 0x200) == 0) {
                report_errorf("List remove");
                kill_sprite(sprite);
                return;
            }
            if ((flags & 0x40) != 0) {
                report_errorf("List remove NEXTBOD");
                kill_sprite(sprite);
                return;
            }
            if (list_next)
                list_next->list_prev = list_prev;
            if (list_prev) {
                list_prev->list_next = list_next;
            } else {
                anchor->first = list_next;
            }
            list_next = anchor->free_top;
            anchor->free_top = this;
            int updated = list_flags;
            Sprite* handle = sprite;
            updated &= ~0x200;
            list_flags = updated;
            kill_sprite(handle);
            return;
        }
    } else if (position_z < owner->kill_plane_z) {
        int flags = list_flags;
        state = 0;
        FreeAnchor* anchor = &g_game->free_anchor;
        if ((flags & 0x200) == 0) {
            report_errorf("List remove");
            kill_sprite(sprite);
            return;
        }
        if ((flags & 0x40) != 0) {
            report_errorf("List remove NEXTBOD");
            kill_sprite(sprite);
            return;
        }
        if (list_next)
            list_next->list_prev = list_prev;
        if (list_prev) {
            list_prev->list_next = list_next;
        } else {
            anchor->first = list_next;
        }
        list_next = anchor->free_top;
        anchor->free_top = this;
        int updated = list_flags;
        Sprite* handle = sprite;
        updated &= ~0x200;
        list_flags = updated;
        kill_sprite(handle);
        return;
    }
    float advanced = bob_phase_step + bob_phase;
    bob_phase = advanced;
    if (advanced >= 1.0f)
        bob_phase = advanced - 1.0f;
    sprite->local_y = sine(bob_phase * 6.2831855f) * 0.30000001f + bob_base_y;
}
