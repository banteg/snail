// append_subgame_contact_target @ 0x415ef0 (thiscall, ret 0x10)
// Appends one `{kind, position, radius, object}` entry to the per-frame
// subgame contact registry unless the target object is hidden by flag 0x1000.

#include "contact_target.h"

void ContactTargetRegistry::append_subgame_contact_target(
    const Vector3* position,
    float radius,
    int kind,
    ContactTargetObject* object
)
{
    if ((object->list_flags & 0x1000) != 0)
        return;

    entries[count].kind = kind;
    entries[count].position = *position;
    entries[count].radius = radius;
    entries[count].object = object;
    ++count;
}
