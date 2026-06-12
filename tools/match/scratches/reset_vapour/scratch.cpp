// reset_vapour @ 0x442540 (thiscall, ret 0x4)

class VapourTrail {
public:
    int reset_vapour(int mode);

    char unknown_00[0x04];
    int flags;                // +0x04
    char unknown_08[0x80 - 0x08];
    int point_count;           // +0x80
    char unknown_84[0x8c - 0x84];
    int mode;                 // +0x8c
};

int VapourTrail::reset_vapour(int new_mode)
{
    point_count = 0;
    mode = new_mode;
    int result = flags;
    result &= ~0x20;
    flags = result;
    return result;
}
