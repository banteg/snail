// is_mouse_captured @ 0x44c3b0 (thiscall, ret)

class MouseCursorState {
public:
    unsigned char is_mouse_captured();

    unsigned char captured; // +0x00
};

unsigned char MouseCursorState::is_mouse_captured()
{
    return captured;
}
