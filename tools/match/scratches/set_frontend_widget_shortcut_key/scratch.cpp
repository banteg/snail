// set_frontend_widget_shortcut_key @ 0x402790 (thiscall, ret 0x4)

class FrontendWidget {
public:
    int set_frontend_widget_shortcut_key(int shortcut_key_code_);

    char unknown_000[0x194];
    int shortcut_key_code;       // +0x194
    char unknown_198[0x1a0 - 0x198];
    unsigned int widget_flags;   // +0x1a0
};

int FrontendWidget::set_frontend_widget_shortcut_key(int shortcut_key_code_)
{
    shortcut_key_code = shortcut_key_code_;
    int result = widget_flags | 0x80000;
    widget_flags = result;
    return result;
}
