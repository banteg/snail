// cREnemyManager::Find @ 0x415e30 (thiscall, ret 0x4)
#include "contact_target.h"

ContactTargetEntry* cREnemyManager::Find(tVector& position)
{
    ContactTargetEntry* found = 0;
    float best = 1000000000.0f;

    int i = 0;
    if (count > 0) {
        const float* cursor = &entries[0].position.z;
        do {
            Vector3 delta;
            delta.x = cursor[-2] - position.x;
            delta.y = cursor[-1] - position.y;
            delta.z = cursor[0] - position.z;
            Vector3 probe = delta;
            if (delta.z > 0.0f && delta.z < 30.0f) {
                float m = probe.Magnitude();
                if (m < best) {
                    best = m;
                    found = (ContactTargetEntry*)(cursor - 3);
                }
            }
            ++i;
            cursor += sizeof(ContactTargetEntry) / sizeof(float);
        } while (i < count);
    }
    return found;
}
