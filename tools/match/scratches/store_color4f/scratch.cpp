// store_color4f @ 0x44dbb0 (thiscall, ret 0x10)

class Color4f {
public:
    int store_color4f(int r_, int g_, int b_, int a_);

    int r; // +0x00
    int g; // +0x04
    int b; // +0x08
    int a; // +0x0c
};

int Color4f::store_color4f(int r_, int g_, int b_, int a_)
{
    r = r_;
    g = g_;
    b = b_;
    a = a_;
    return b_;
}
