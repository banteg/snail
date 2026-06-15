// spawn_salt_hazard @ 0x441560 (thiscall, ret 0x4)
#include "salt_hazard_types.h"
#include "transform_matrix.h"

struct Game {
    char unknown_00[0x74650];
    float salt_speed_base;      // +0x74650
    char unknown_74654[0x3ca224 - 0x74654];
    SaltHazardSlot salt_list_head; // +0x3ca224, node-shaped anchor
};

extern Game* volatile g_game; // data_4df904
int next_math_random_value();
int report_errorf(char* format, ...);

int SaltHazardPool::spawn_salt_hazard(const Vector3* position)
{
    int index = 0;
    int* state = &slots[0].state;
    do {
        if (!*state)
            goto found;
        ++index;
        state += 38;
    } while (index < 40);
    return index;

found:
    SaltHazardSlot* slot = &slots[index];
    slot->state = 1;
    slot->velocity.x = 0.0f;
    slot->velocity.y = g_game->salt_speed_base * 0.033333335f;
    TransformMatrix* live_matrix = (TransformMatrix*)((char*)slot + 0x38);
    Vector3* spawn_position = &slot->position;
    *spawn_position = *position;
    live_matrix->set_matrix_rotation_identity();
    float angle = ((float)next_math_random_value() - 16384.0f) * 0.0001917476f;
    live_matrix->rotate_matrix_world_y(angle);
    *(unsigned char*)&slot->velocity.z = 1;
    SaltHazardSlot* head = &g_game->salt_list_head;
    if ((slot->list_flags & 0x200) != 0)
        return report_errorf("List ADDafter");
    slot->list_prev = head;
    slot->list_next = head->list_next;
    head->list_next = slot;
    if (slot->list_next)
        slot->list_next->list_prev = slot;
    return slot->list_flags |= 0x200;
}
