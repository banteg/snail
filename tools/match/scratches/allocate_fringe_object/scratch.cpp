#include "fringe_object.h"

// allocate_fringe_object @ 0x4470a0 (thiscall, ret)

int report_errorf(char* format, ...);

Fringe* FringeManager::allocate_fringe_object()
{
    if (count == 7000) {
        report_errorf("Too many Fringes increase RFRINGEMANAGER_NUMBER");
        return 0;
    }

    return &objects[count++];
}
