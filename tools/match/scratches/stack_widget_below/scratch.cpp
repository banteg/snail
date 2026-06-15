// stack_widget_below @ 0x4027b0 (thiscall, ret 0x4)

class FrontendWidget {
public:
    FrontendWidget* stack_widget_below(FrontendWidget* previous_widget);
    FrontendWidget* layout_frontend_widget();

    char unknown_000[0x24c];
    float layout_height; // +0x24c
    char unknown_250[0x26c - 0x250];
    float stack_gap; // +0x26c
    char unknown_270[0x6f4 - 0x270];
    float layout_anchor_x; // +0x6f4
    float layout_anchor_y; // +0x6f8
};

FrontendWidget* FrontendWidget::stack_widget_below(FrontendWidget* previous_widget)
{
    layout_anchor_x = previous_widget->layout_anchor_x;
    layout_anchor_y = previous_widget->layout_anchor_y + stack_gap + previous_widget->layout_height;
    return layout_frontend_widget();
}
