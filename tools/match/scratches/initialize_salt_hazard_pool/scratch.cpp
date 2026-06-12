// initialize_salt_hazard_pool @ 0x441540 (thiscall, ret)

class SaltHazardPool {
public:
    int* initialize_salt_hazard_pool();

    char unknown_00[0x80];
};

int* SaltHazardPool::initialize_salt_hazard_pool()
{
    int* state = (int*)((char*)this + 0x80);
    int count = 40;
    do {
        *state = 0;
        state += 38;
        --count;
    } while (count);
    return state;
}
