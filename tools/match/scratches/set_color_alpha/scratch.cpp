// set_color_alpha @ 0x44db80 (thiscall, ret 0x4)

class Color4f {
public:
    int set_color_alpha(int alpha_bits);

    float r; // +0x00
    float g; // +0x04
    float b; // +0x08
    int a;   // +0x0c
};

int Color4f::set_color_alpha(int alpha_bits)
{
    a = alpha_bits;
    return alpha_bits;
}
