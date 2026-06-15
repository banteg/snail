// activate_all_borders @ 0x403300 (thiscall, ret)

class BorderRecord {
public:
    char unknown_000[0x1a0];
    int flags; // +0x1a0
    char unknown_1a4[0x20c - 0x1a4];
    float hover_blend_target; // +0x20c
    float hover_blend_current; // +0x210
    float idle_padding; // +0x214
    float hot_padding; // +0x218
    float target_padding; // +0x21c
    float active_padding; // +0x220
    char unknown_224[0x724 - 0x224];
};

class BorderManager {
public:
    void activate_all_borders();

    char unknown_000[0x684];
    BorderRecord borders[150]; // +0x684
};

void BorderManager::activate_all_borders()
{
    for (int i = 0; i < 150; ++i) {
        int flags = borders[i].flags;
        if ((flags & 0x80000000) == 0) {
            flags &= 0xffff7fff;
            borders[i].flags = flags;
        }
        borders[i].flags &= 0x7fffffff;
        borders[i].target_padding = borders[i].idle_padding;
        borders[i].active_padding = borders[i].idle_padding;
        borders[i].hover_blend_target = 0.0f;
    }
}
