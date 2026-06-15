// set_border_justify_centre @ 0x404730 (thiscall, ret 0x4)

class BorderRuntime {
public:
    int set_border_justify_centre(int justify_centre_);

    char unknown_00000[0x435b0];
    int justify_centre; // +0x435b0
};

int BorderRuntime::set_border_justify_centre(int justify_centre_)
{
    justify_centre = justify_centre_;
    return justify_centre_;
}
