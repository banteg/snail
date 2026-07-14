// append_subgame_contact_target @ 0x415ef0 (thiscall, ret 0x10)
// Appends one `{kind, position, radius, object}` entry to the per-frame
// subgame contact registry unless the target suppresses contact registration.

#include "contact_target.h"

void EnemyManager::append_subgame_contact_target(
    const Vector3* position,
    float radius,
    int kind,
    ContactTargetObject* object
)
{
    if ((object->list_flags & BOD_FLAG_SUPPRESS_CONTACT) != 0)
        return;

    entries[count].kind = kind;
    entries[count].position = *position;
    entries[count].radius = radius;
    entries[count].object = object;
    ++count;
}
