# set_color_rgb @ 0x44dbd0

Three-channel `tColour` setter used by `firework_shoot`. It stores red, green,
and blue in order and deliberately leaves the existing alpha value unchanged.
Android retains the authored overload as `tColour::Set(float, float, float)`;
the exact Windows scratch keeps its stable descriptive helper name.
