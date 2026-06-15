// kill_all_borders @ 0x4033c0 (thiscall, ret)

class BorderRecord {
public:
    char unknown_000[0x1a0];
    int flags; // +0x1a0
    char unknown_1a4[0x724 - 0x1a4];
};

class BorderManager {
public:
    int kill_all_borders();

    char unknown_000[0x684];
    BorderRecord borders[150]; // +0x684
};

int BorderManager::kill_all_borders()
{
    int result = 0;
    for (int i = 0; i < 150; ++i) {
        result = borders[i].flags;
        if (result != 0 && (result & 0x10000400) == 0) {
            result = (result & 0xffffff01) | 0x200;
            borders[i].flags = result;
        }
    }
    return result;
}
