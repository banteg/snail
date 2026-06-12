// set_color_grayscale @ 0x44db90 (thiscall, ret 0x4)

class Color4f {
public:
    void set_color_grayscale(float intensity);

    float r; // +0x00
    float g; // +0x04
    float b; // +0x08
    float a; // +0x0c
};

void Color4f::set_color_grayscale(float intensity)
{
    a = 1.0f;
    r = intensity;
    g = intensity;
    b = intensity;
}
