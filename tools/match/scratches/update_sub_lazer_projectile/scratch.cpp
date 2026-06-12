// update_sub_lazer_projectile @ 0x43efb0 (thiscall, ret)

extern char* g_game_base; // data_4df904

int report_errorf(char* format, ...);
double sine(float angle);

class Sprite {
public:
    void kill_sprite();

    char unknown_00[0x4c];
    float local_y;
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

class SubLazerSlot {
public:
    void update_sub_lazer_projectile();

    int unknown_00;
    unsigned int list_flags;
    SubLazerSlot* list_prev;
    SubLazerSlot* list_next;
    char unknown_10[0x14 - 0x10];
    float sprite_bob_base_y;
    float world_z;
    char unknown_1c[0x38 - 0x1c];
    int state;
    Player* owner;
    char unknown_40[0x44 - 0x40];
    TrackRuntimeCell* source_cell;
    char unknown_48[0x64 - 0x48];
    Sprite* sprite;
    char unknown_68[0x6c - 0x68];
    float sprite_bob_phase;
    float sprite_bob_phase_step;
};

void SubLazerSlot::update_sub_lazer_projectile()
{
    int zero = 0;
    unsigned int flags;
    ListHead* head;
    SubLazerSlot* next;
    SubLazerSlot* prev;

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
    if (next != (SubLazerSlot*)zero) {
        next->list_prev = list_prev;
    }

    prev = list_prev;
    if (prev != (SubLazerSlot*)zero) {
        prev->list_next = list_next;
    } else {
        head->tail = list_next;
    }

    list_next = (SubLazerSlot*)head->next;
    head->next = this;
    list_flags &= ~0x200;
    sprite->kill_sprite();
    return;

state_one:
    if (!(world_z < owner->interaction_max_z)) {
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
    if (next != (SubLazerSlot*)zero) {
        next->list_prev = list_prev;
    }

    prev = list_prev;
    if (prev != (SubLazerSlot*)zero) {
        prev->list_next = list_next;
    } else {
        head->tail = list_next;
    }

    list_next = (SubLazerSlot*)head->next;
    head->next = this;
    list_flags &= ~0x200;
    sprite->kill_sprite();
    return;

update_bob:
    float phase = sprite_bob_phase + sprite_bob_phase_step;
    sprite_bob_phase = phase;
    if (phase > 1.0f) {
        sprite_bob_phase = phase - 1.0f;
    }
    sprite->local_y = (float)sine(sprite_bob_phase * 6.2831855f) * 0.30000001f + sprite_bob_base_y;
}
