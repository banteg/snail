// set_color_white @ 0x44dc50 (thiscall, ret)

class Color4f {
public:
    void set_color_grayscale(float intensity);
    void set_color_white();
};

void Color4f::set_color_white()
{
    set_color_grayscale(1.0f);
}
