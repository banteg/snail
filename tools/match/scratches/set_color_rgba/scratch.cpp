// set_color_rgba @ 0x44db60 (thiscall, ret 0x10)

class Color4f {
public:
    Color4f* set_color_rgba(float r_, float g_, float b_, float a_);

    float r; // +0x00
    float g; // +0x04
    float b; // +0x08
    float a; // +0x0c
};

Color4f* Color4f::set_color_rgba(float r_, float g_, float b_, float a_)
{
    r = r_;
    g = g_;
    b = b_;
    a = a_;
    return this;
}
