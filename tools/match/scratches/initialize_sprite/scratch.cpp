// initialize_sprite @ 0x44de90 (thiscall, ret)

class Color4f {
public:
    void set_color_white();

    float r;
    float g;
    float b;
    float a;
};

class Sprite {
public:
    void initialize_sprite();

    int sprite_id; // +0x00
    int flags; // +0x04
    int owner; // +0x08
    Sprite* next; // +0x0c
    Sprite* prev; // +0x10
    int field_14;
    int field_18;
    int texture_ref; // +0x1c
    int field_20;
    int field_24;
    int field_28;
    Color4f color; // +0x2c
    int field_3c;
    int field_40;
    int field_44;
    int field_48;
    int field_4c;
    int field_50;
    int field_54;
    int field_58;
    int field_5c;
    int field_60;
    int field_64;
    int field_68;
    int field_6c;
    int field_70;
    int field_74;
    int field_78;
    int field_7c;
    int field_80;
    int field_84;
    int field_88;
    int field_8c;
    int field_90;
    int field_94;
    int field_98;
    int field_9c;
    int field_a0;
    int field_a4;
    int field_a8;
    int field_ac;
    int field_b0;
};

void Sprite::initialize_sprite()
{
    flags = 0x49;
    color.set_color_white();

    int zero = 0;
    field_78 = 0xbc54fdf4;
    field_28 = zero;
    field_68 = zero;
    field_70 = zero;
    field_74 = zero;
    field_7c = zero;
    field_80 = zero;
    field_84 = zero;
    field_88 = 0x3f800000;
    field_8c = zero;
    field_90 = zero;
    field_94 = 0xc3fa0000;
    field_20 = zero;
    field_24 = zero;
    field_5c = zero;
    field_58 = zero;
    field_54 = zero;
    field_98 = zero;
    sprite_id = -1;
    field_9c = zero;
    field_a0 = zero;
    field_a4 = zero;
    field_ac = zero;
    field_b0 = zero;
    field_a8 = 1;
}
