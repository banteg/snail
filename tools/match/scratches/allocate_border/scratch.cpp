// allocate_border @ 0x4032a0 (thiscall, ret)

extern char* g_game_base; // data_4df904

int report_errorf(char* format, ...);

class BorderRecord {
public:
    char unknown_000[0x19c];
    int created_time; // +0x19c
    int flags;        // +0x1a0
    char unknown_1a4[0x724 - 0x1a4];
};

class BorderManager {
public:
    BorderRecord* allocate_border();

    char unknown_000[0x684];
    BorderRecord borders[150]; // +0x684
};

BorderRecord* BorderManager::allocate_border()
{
    for (int i = 0; i < 150; ++i) {
        if (borders[i].flags == 0) {
            borders[i].created_time = *(int*)(g_game_base + 0x51c);
            return &borders[i];
        }
    }

    report_errorf("Run out of Borders - Increase RGAME_BORDER_NUMBER");
    return 0;
}
