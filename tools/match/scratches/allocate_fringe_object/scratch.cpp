// allocate_fringe_object @ 0x4470a0 (thiscall, ret)

int report_errorf(char* format, ...);

struct FringeObject {
    char unknown_00[0x38];
};

class FringeManager {
public:
    FringeObject* allocate_fringe_object();

    FringeObject objects[7000];
    int count; // +0x5fb40
};

FringeObject* FringeManager::allocate_fringe_object()
{
    if (count == 7000) {
        report_errorf("Too many Fringes increase RFRINGEMANAGER_NUMBER");
        return 0;
    }

    return &objects[count++];
}
