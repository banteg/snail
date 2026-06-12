// initialize_sub_lazer_pool @ 0x441650 (thiscall, ret)

class SubLazerPool {
public:
    int* initialize_sub_lazer_pool();

    char unknown_00[0x80];
};

int* SubLazerPool::initialize_sub_lazer_pool()
{
    int* state = (int*)((char*)this + 0x80);
    int count = 20;
    do {
        *state = 0;
        state += 44;
        --count;
    } while (count);
    return state;
}
