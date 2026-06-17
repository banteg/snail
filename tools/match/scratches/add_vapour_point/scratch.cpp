// add_vapour_point @ 0x442560 (thiscall, ret 0x4)

#include "vapour_trail.h"

extern "C" void* memcpy(void* destination, const void* source, unsigned int count);

void VapourTrail::add_vapour_point(const TransformMatrix* point)
{
    int* result = (int*)this;
    int point_index = result[32];
    int point_limit = result[33];
    if (point_index < point_limit) {
        memcpy((void*)(result[36] + (point_index << 6)), point, 0x40);
        ++result[32];
        return;
    }

    int shift_index = 0;
    if (point_limit - 1 > 0) {
        int shift_offset = 0;
        do {
            int point_base = result[36];
            ++shift_index;
            const void* source = (const void*)(shift_offset + point_base + 0x40);
            void* destination = (void*)(shift_offset + point_base);
            shift_offset += 0x40;
            memcpy(destination, source, 0x40);
        } while (shift_index < result[33] - 1);
    }

    int count = result[32];
    result = (int*)result[36];
    memcpy(&result[16 * count - 16], point, 0x40);
}
