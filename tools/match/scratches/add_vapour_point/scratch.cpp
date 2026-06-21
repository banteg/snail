// add_vapour_point @ 0x442560 (thiscall, ret 0x4)

#include "vapour_trail.h"

extern "C" void* memcpy(void* destination, const void* source, unsigned int count);

void VapourTrail::add_vapour_point(const TransformMatrix* point)
{
    int* result = (int*)this;
    if (result[32] < result[33]) {
        int point_index = result[32];
        memcpy((void*)(result[36] + (point_index << 6)), point, 0x40);
        ++result[32];
        return;
    }

    int point_limit = result[33];
    int shift_index = 0;
    int shift_slot = 0;
    if (point_limit - 1 > 0) {
        do {
            TransformMatrix* point_base = (TransformMatrix*)result[36];
            ++shift_index;
            memcpy(&point_base[shift_slot], &point_base[shift_slot + 1], 0x40);
            ++shift_slot;
        } while (shift_index < result[33] - 1);
    }

    TransformMatrix* points = this->points;
    int count = this->point_count;
    memcpy(&points[count - 1], point, 0x40);
}
