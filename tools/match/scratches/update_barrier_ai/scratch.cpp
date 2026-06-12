// update_barrier_ai @ 0x440f80 (thiscall, ret)

class BarrierActor {
public:
    void* update_barrier_ai();

    char unknown_00[0x14];
    float y;                  // +0x14
    float z;                  // +0x18
    char unknown_1c[0x38 - 0x1c];
    char* owner;              // +0x38
};

void* BarrierActor::update_barrier_ai()
{
    char* owner_object = owner;
    int owner_z_bits = *(int*)(owner_object + 0x70);
    y = 0.4f;
    *(int*)&z = owner_z_bits;
    return owner_object;
}
