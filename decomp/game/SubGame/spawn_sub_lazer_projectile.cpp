// spawn_sub_lazer_projectile @ 0x441670 (thiscall, ret 0x8)
// Authored owner: cRSubLazer::Shoot().
#include "sub_lazer_types.h"
#include "subgame_runtime.h"
#include "transform_matrix.h"

int report_errorf(char* format, ...);

void cRSubLazer::Shoot(const Vector3* origin, const Vector3* direction)
{
    state = SUB_LAZER_STATE_ACTIVE;
    TransformMatrix* live_matrix = &transform;
    live_matrix->Identity();
    Vector3* position = &transform.position;
    *position = *origin;
    velocity = *direction;
    // Compatibility field spelling: this pair is consumed as a normalized
    // flight lifetime, not as a borrowed cRSprite.
    flight_lifetime_progress = 0.0f;
    flight_lifetime_step = owner_game->subgame_rate * 0.0055555557f;

    BodNode* head = &owner_game->barrier_sub_lazer_list_head;
    if ((list_flags & BOD_FLAG_LINKED) != 0) {
        report_errorf("List ADDafter");
    } else {
        list_prev = head;
        list_next = head->list_next;
        head->list_next = this;
        if (list_next != 0) {
            list_next->list_prev = this;
        }
        list_flags |= BOD_FLAG_LINKED;
    }

    live_matrix->SetZDir(velocity);
}
