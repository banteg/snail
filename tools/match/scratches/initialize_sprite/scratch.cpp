// initialize_sprite @ 0x44de90 (thiscall, ret)

class Color4f {
public:
    void set_color_white();
};

class Sprite {
public:
    void initialize_sprite();
};

void Sprite::initialize_sprite()
{
    *(int*)((char*)this + 0x04) = 0x49;
    ((Color4f*)((char*)this + 0x2c))->set_color_white();

    int zero = 0;
    *(int*)((char*)this + 0x78) = 0xbc54fdf4;
    *(int*)((char*)this + 0x28) = zero;
    *(int*)((char*)this + 0x68) = zero;
    *(int*)((char*)this + 0x70) = zero;
    *(int*)((char*)this + 0x74) = zero;
    *(int*)((char*)this + 0x7c) = zero;
    *(int*)((char*)this + 0x80) = zero;
    *(int*)((char*)this + 0x84) = zero;
    *(int*)((char*)this + 0x88) = 0x3f800000;
    *(int*)((char*)this + 0x8c) = zero;
    *(int*)((char*)this + 0x90) = zero;
    *(int*)((char*)this + 0x94) = 0xc3fa0000;
    *(int*)((char*)this + 0x20) = zero;
    *(int*)((char*)this + 0x24) = zero;
    *(int*)((char*)this + 0x5c) = zero;
    *(int*)((char*)this + 0x58) = zero;
    *(int*)((char*)this + 0x54) = zero;
    *(int*)((char*)this + 0x98) = zero;
    *(int*)((char*)this + 0x00) = -1;
    *(int*)((char*)this + 0x9c) = zero;
    *(int*)((char*)this + 0xa0) = zero;
    *(int*)((char*)this + 0xa4) = zero;
    *(int*)((char*)this + 0xac) = zero;
    *(int*)((char*)this + 0xb0) = zero;
    *(int*)((char*)this + 0xa8) = 1;
}
