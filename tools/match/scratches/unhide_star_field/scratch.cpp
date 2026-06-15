// unhide_star_field @ 0x4346b0 (thiscall, ret int)

class Sprite {
public:
    void* vtable; // +0x00
    int flags;    // +0x04
};

class StarFieldEntry {
public:
    char pad_00[0x1c];
    Sprite* sprite; // +0x1c
    char pad_20[0x0c];
};

class StarField {
public:
    int unhide_star_field();

    char pad_00[0x38];
    int active;               // +0x38
    StarFieldEntry* entries;  // +0x3c
    int count;                // +0x40
};

int StarField::unhide_star_field()
{
    int result = active;
    if (result != 0) {
        result = count;
        for (int i = 0; i < result; ++i) {
            entries[i].sprite->flags |= 0x40;
            result = count;
        }
    }
    return result;
}
