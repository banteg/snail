// update_track_health_pickup @ 0x43ecc0 (thiscall, ret)

#include "sprite.h"

extern char* g_game_base; // data_4df904

int report_errorf(char* format, ...);
float sine(float radians);

struct TrackRuntimeCell {
    char unknown_00[9];
    unsigned char hidden;
};

struct Player {
    char unknown_00[0x2980];
    float interaction_max_z;
};

struct ListHead {
    int unknown_00;
    void* tail;
    void* next;
};

class TrackHealthPickup {
public:
    void update_track_health_pickup();

    int unknown_00;
    unsigned int list_flags;
    TrackHealthPickup* list_prev;
    TrackHealthPickup* list_next;
    char unknown_10[0x14 - 0x10];
    float world_y;
    float world_z;
    char unknown_1c[0x38 - 0x1c];
    int state;
    Player* owner;
    char unknown_40[0x44 - 0x40];
    TrackRuntimeCell* source_cell;
    char unknown_48[0x64 - 0x48];
    Sprite* sprite;
    char unknown_68[0x6c - 0x68];
    float bob_phase;
    float bob_phase_step;
};

void TrackHealthPickup::update_track_health_pickup()
{
    int zero = 0;
    unsigned int flags;
    ListHead* head;
    TrackHealthPickup* next;
    TrackHealthPickup* prev;

    if (source_cell->hidden != zero) {
        return;
    }

    int current_state = state - zero;
    switch (current_state) {
    case 0:
        break;
    case 1:
        goto state_one;
    case 2:
        goto state_two;
    default:
        goto update_bob;
    }
    return;

state_two:
    flags = list_flags;
    state = zero;
    head = (ListHead*)(g_game_base + 0x5a8);
    if ((flags & 0x200) == 0) {
        report_errorf("List remove");
        sprite->kill_sprite();
        return;
    }
    if ((flags & 0x40) != 0) {
        report_errorf("List remove NEXTBOD");
        sprite->kill_sprite();
        return;
    }

    next = list_next;
    if (next != (TrackHealthPickup*)zero) {
        next->list_prev = list_prev;
    }

    prev = list_prev;
    if (prev != (TrackHealthPickup*)zero) {
        prev->list_next = list_next;
    } else {
        head->tail = list_next;
    }

    list_next = (TrackHealthPickup*)head->next;
    head->next = this;
    list_flags &= ~0x200;
    sprite->kill_sprite();
    return;

state_one:
    if (world_z >= owner->interaction_max_z) {
        goto update_bob;
    }

    flags = list_flags;
    state = zero;
    head = (ListHead*)(g_game_base + 0x5a8);
    if ((flags & 0x200) == 0) {
        report_errorf("List remove");
        sprite->kill_sprite();
        return;
    }
    if ((flags & 0x40) != 0) {
        report_errorf("List remove NEXTBOD");
        sprite->kill_sprite();
        return;
    }

    next = list_next;
    if (next != (TrackHealthPickup*)zero) {
        next->list_prev = list_prev;
    }

    prev = list_prev;
    if (prev != (TrackHealthPickup*)zero) {
        prev->list_next = list_next;
    } else {
        head->tail = list_next;
    }

    list_next = (TrackHealthPickup*)head->next;
    head->next = this;
    list_flags &= ~0x200;
    sprite->kill_sprite();
    return;

update_bob:
    float advanced = bob_phase_step + bob_phase;
    bob_phase = advanced;
    if (advanced > 1.0f)
        bob_phase = advanced - 1.0f;
    sprite->position.y = (sine(bob_phase * 6.2831855f) + 1.0f) * 0.30000001f + world_y;
}
