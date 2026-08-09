// spawn_salt_hazard @ 0x441560 (thiscall, ret 0x4)
#include "game_root.h"
#include "salt_hazard_types.h"
#include "transform_matrix.h"

int next_math_random_value();
int report_errorf(char* format, ...);

void cRSaltManager::Add(tVector& position)
{
    enum {
        SALT_SLOT_CAPACITY = sizeof(slots) / sizeof(slots[0]),
    };
    int index = 0;
    cRSalt* scan = slots;
    while (index < SALT_SLOT_CAPACITY
        && scan->state != SALT_STATE_INACTIVE) {
        ++index;
        ++scan;
        if (index >= SALT_SLOT_CAPACITY)
            return;
    }

    cRSalt* slot = &slots[index];
    slot->state = SALT_STATE_ACTIVE;
    slot->fade_alpha = 0.0f;
    // This mobile-preserved +0x90 seed is write-only in the recovered runtime;
    // keep the compatibility field spelling without inventing a consumer.
    slot->spawn_velocity_y = g_game->subgame.subgame_rate * 0.033333335f;
    TransformMatrix* live_matrix = &slot->transform;
    Vector3* spawn_position = &slot->transform.position;
    *spawn_position = position;
    live_matrix->RotIdentity();
    live_matrix->RotLocalY(
        ((float)next_math_random_value() - 16384.0f)
        * 0.0000610351562f * 3.1415927f);
    slot->collision_armed = 1;
    int* list_flags = &slot->list_flags;
    BodNode* head = &g_game->subgame.salt_hazard_list_head;
    if ((*list_flags & BOD_FLAG_LINKED) != 0) {
        report_errorf("List ADDafter");
        return;
    }
    slot->list_prev = head;
    slot->list_next = head->list_next;
    head->list_next = slot;
    if (slot->list_next)
        slot->list_next->list_prev = slot;
    *list_flags |= BOD_FLAG_LINKED;
}
