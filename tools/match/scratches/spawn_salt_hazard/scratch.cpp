// spawn_salt_hazard @ 0x441560 (thiscall, ret 0x4)
#include "salt_hazard_types.h"
#include "subgame_runtime.h"
#include "transform_matrix.h"

extern char* g_game; // data_4df904
int next_math_random_value();
int report_errorf(char* format, ...);

int SaltHazardPool::spawn_salt_hazard(const Vector3* position)
{
    int index = 0;
    int* state = &slots[0].state;
    while (1) {
        if (!*state)
            break;
        ++index;
        state += 38;
        if (index >= 40)
            return index;
    }

    SaltHazardSlot* slot = &slots[index];
    slot->state = 1;
    slot->velocity.x = 0.0f;
    slot->velocity.y = ((SubgameRuntime*)(g_game + 0x74618))->subgame_rate * 0.033333335f;
    TransformMatrix* live_matrix = (TransformMatrix*)((char*)slot + 0x38);
    Vector3* spawn_position = &slot->position;
    *spawn_position = *position;
    live_matrix->set_matrix_rotation_identity();
    live_matrix->rotate_matrix_world_y(
        ((float)next_math_random_value() - 16384.0f) * 0.0001917476f);
    slot->collision_armed() = 1;
    int* list_flags = &slot->list_flags;
    SaltHazardSlot* head = (SaltHazardSlot*)(g_game + 0x3ca224);
    if ((*list_flags & 0x200) != 0)
        return report_errorf("List ADDafter");
    slot->list_prev = head;
    slot->list_next = head->list_next;
    head->list_next = slot;
    if (slot->list_next)
        slot->list_next->list_prev = slot;
    return *list_flags |= 0x200;
}
