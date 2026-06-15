// search_path_for_golb @ 0x415e30 (thiscall, ret 0x4)
#include "golb.h"

GolbPathSample* GolbPathBank::search_path_for_golb(const Vector3* position)
{
    GolbPathSample* found = 0;
    float best = 1000000000.0f;

    int i = 0;
    if (count > 0) {
        const float* cursor = &samples[0].z;
        do {
            Vector3 delta;
            delta.x = cursor[-2] - position->x;
            delta.y = cursor[-1] - position->y;
            delta.z = cursor[0] - position->z;
            Vector3 probe = delta;
            if (delta.z > 0.0f && delta.z < 30.0f) {
                float m = probe.vector_magnitude();
                if (m < best) {
                    best = m;
                    found = (GolbPathSample*)(cursor - 3);
                }
            }
            ++i;
            cursor += 6;
        } while (i < count);
    }
    return found;
}
