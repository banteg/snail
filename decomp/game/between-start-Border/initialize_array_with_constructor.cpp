// initialize_array_with_constructor @ 0x401000 (stdcall, ret 0x10)

#include "runtime_slot.h"

void __stdcall initialize_array_with_constructor(RuntimeSlot* base, int stride, int count, RuntimeSlotConstructor constructor)
{
    if (--count < 0)
        return;

    int loops = count + 1;
    RuntimeSlot* slot = base;
    do {
        (slot->*constructor)();
        slot = (RuntimeSlot*)((char*)slot + stride);
    } while (--loops != 0);
}
