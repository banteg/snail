// calc_slider_to_rate @ 0x437e80 (stdcall, ret 0x4)

float __stdcall calc_slider_to_rate(float slider)
{
    if (slider == 1.0f) {
        return 1.1f;
    }
    return slider * 0.90000004f + 0.2f;
}
