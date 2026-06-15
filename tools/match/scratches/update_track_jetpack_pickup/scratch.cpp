// update_track_jetpack_pickup @ 0x43ee50 (thiscall, ret)

#include "player.h"
#include "sprite.h"
#include "track_runtime.h"
#include "bod_list.h"

extern char* g_game_base; // data_4df904

int report_errorf(char* format, ...);

class TrackJetpackPickup {
public:
    void update_track_jetpack_pickup();

    int unknown_00;
    unsigned int list_flags;
    TrackJetpackPickup* list_prev;
    TrackJetpackPickup* list_next;
    char unknown_10[0x70 - 0x10];
    float world_z;
    char unknown_74[0x80 - 0x74];
    int state;
    Player* owner;
    char unknown_88[0x8c - 0x88];
    TrackRuntimeCell* source_cell;
    char unknown_90[0xac - 0x90];
    Sprite* sprite;
};

void TrackJetpackPickup::update_track_jetpack_pickup()
{
    int zero = 0;
    unsigned int flags;
    BodList* head;
    TrackJetpackPickup* next;
    TrackJetpackPickup* prev;

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
        return;
    }
    return;

state_two:
    flags = list_flags;
    state = zero;
    head = (BodList*)(g_game_base + 0x5a8);
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
    if (next != (TrackJetpackPickup*)zero) {
        next->list_prev = list_prev;
    }

    prev = list_prev;
    if (prev != (TrackJetpackPickup*)zero) {
        prev->list_next = list_next;
    } else {
        head->first = (BodNode*)list_next;
    }

    list_next = (TrackJetpackPickup*)head->free_top;
    head->free_top = (BodNode*)this;
    list_flags &= ~0x200;
    sprite->kill_sprite();
    return;

state_one:
    if (world_z >= owner->interaction_max_z) {
        return;
    }

    flags = list_flags;
    state = zero;
    head = (BodList*)(g_game_base + 0x5a8);
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
    if (next != (TrackJetpackPickup*)zero) {
        next->list_prev = list_prev;
    }

    prev = list_prev;
    if (prev != (TrackJetpackPickup*)zero) {
        prev->list_next = list_next;
    } else {
        head->first = (BodNode*)list_next;
    }

    list_next = (TrackJetpackPickup*)head->free_top;
    head->free_top = (BodNode*)this;
    list_flags &= ~0x200;
    sprite->kill_sprite();
}
