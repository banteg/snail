// update_track_jetpack_pickup @ 0x43ee50 (thiscall, ret)

extern char* g_game_base; // data_4df904

int report_errorf(char* format, ...);

class Sprite {
public:
    void kill_sprite();
};

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
    ListHead* head;
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
    if (next != (TrackJetpackPickup*)zero) {
        next->list_prev = list_prev;
    }

    prev = list_prev;
    if (prev != (TrackJetpackPickup*)zero) {
        prev->list_next = list_next;
    } else {
        head->tail = list_next;
    }

    list_next = (TrackJetpackPickup*)head->next;
    head->next = this;
    list_flags &= ~0x200;
    sprite->kill_sprite();
    return;

state_one:
    if (world_z >= owner->interaction_max_z) {
        return;
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
    if (next != (TrackJetpackPickup*)zero) {
        next->list_prev = list_prev;
    }

    prev = list_prev;
    if (prev != (TrackJetpackPickup*)zero) {
        prev->list_next = list_next;
    } else {
        head->tail = list_next;
    }

    list_next = (TrackJetpackPickup*)head->next;
    head->next = this;
    list_flags &= ~0x200;
    sprite->kill_sprite();
}
