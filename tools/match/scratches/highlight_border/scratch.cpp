// highlight_border @ 0x402800 (thiscall, ret)

class FrontendWidget {
public:
    int highlight_border();

    char unknown_000[0x20c];
    float hover_blend_target; // +0x20c
    float hover_blend_current; // +0x210
    float idle_padding; // +0x214
    float hot_padding; // +0x218
    float target_padding; // +0x21c
};

int FrontendWidget::highlight_border()
{
    int result = *(int*)&hot_padding;
    hover_blend_target = 1.0f;
    *(int*)&target_padding = result;
    return result;
}
