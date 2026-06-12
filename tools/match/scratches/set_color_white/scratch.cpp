// set_color_white @ 0x44dc50 (thiscall, ret)

class Color4f {
public:
    float set_color_grayscale(float intensity);
    float set_color_white();
};

float Color4f::set_color_white()
{
    return set_color_grayscale(1.0f);
}
