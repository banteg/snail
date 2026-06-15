// border_sprite_extend @ 0x404540 (thiscall, ret 0x10)

class FrontendBorderSprite {
public:
    int border_sprite_extend(int sprite_a, int sprite_c, int sprite_b, char flag);

    char pad_000[0x5c];
    char extended;     // +0x5c
    char flag;         // +0x5d
    char pad_05e[2];
    int sprite_a;      // +0x60
    int sprite_b;      // +0x64
    int sprite_c;      // +0x68
    char pad_06c[0x214 - 0x06c];
    int frame_a;       // +0x214
    int frame_b;       // +0x218
    int frame_c;       // +0x21c
};

int FrontendBorderSprite::border_sprite_extend(int sprite_a_, int sprite_c_, int sprite_b_, char flag_)
{
    sprite_a = sprite_a_;
    sprite_b = sprite_b_;
    sprite_c = sprite_c_;
    extended = 1;
    flag = flag_;
    frame_c = 0;
    frame_a = 0;
    frame_b = 0;
    return 0;
}
