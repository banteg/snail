// initialize_vapour @ 0x442500 (thiscall, ret 0x8)

void* allocate_tracked_memory(int size, char* name);

struct VapourOwner {
    char unknown_00[0x54];
    int max_points;            // +0x54
};

class VapourTrail {
public:
    int initialize_vapour(int unused, int point_stride);
    int reset_vapour(int mode);

    char unknown_00[0x24];
    VapourOwner* owner;        // +0x24
    char unknown_28[0x84 - 0x28];
    int capacity;              // +0x84
    int point_stride;          // +0x88
    char unknown_8c[0x90 - 0x8c];
    void* points;              // +0x90
};

int VapourTrail::initialize_vapour(int, int new_point_stride)
{
    VapourOwner* owner_ptr = owner;
    point_stride = new_point_stride;
    int point_capacity = owner_ptr->max_points + 1;
    capacity = point_capacity;
    points = allocate_tracked_memory(point_capacity << 6, "Vapour Trail");
    return reset_vapour(0);
}
