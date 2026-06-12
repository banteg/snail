// set_color_black @ 0x44dc60 (thiscall, ret)

class Color4f {
public:
    float set_color_grayscale(float intensity);
    float set_color_black();
};

float Color4f::set_color_black()
{
    return set_color_grayscale(0.0f);
}
