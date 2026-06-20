// initialize_frontend_sprite_button @ 0x401a70 (thiscall, ret 0x1c)

#include "sprite.h"

extern char* g_game_base; // data_4df904
int report_errorf(char* format, ...);

class FrontendWidget {
public:
    void initialize_frontend_sprite_button(int flags, int sprite, float x, float y,
        Color4f* color, float anchor_x, int layer);
    int unhide_border_init();
    int layout_frontend_widget();

    unsigned int list_kind; // +0x00
    unsigned int list_flags; // +0x04
    FrontendWidget* list_prev; // +0x08
    FrontendWidget* list_next; // +0x0c
};

void FrontendWidget::initialize_frontend_sprite_button(
    int flags,
    int sprite,
    float x,
    float y,
    Color4f* color,
    float anchor_x,
    int layer)
{
    char* self = (char*)this;
    FrontendWidget* head = (FrontendWidget*)(g_game_base + 0xb4c);

    if ((list_flags & 0x200) != 0) {
        report_errorf("List ADDafter");
    } else {
        list_prev = head;
        list_next = head->list_next;
        head->list_next = this;
        FrontendWidget* next = list_next;
        if (next != 0)
            next->list_prev = this;
        list_flags |= 0x200;
    }

    *(int*)(self + 0x48) = 5;
    *(unsigned char*)(self + 0x5c) = 0;
    *(int*)(self + 0x290) = 0;
    *(FrontendWidget**)(self + 0x298) = this;
    *(FrontendWidget**)(self + 0x2a4) = 0;
    *(FrontendWidget**)(self + 0x2c4) = this;
    *(int*)(self + 0x22c) = 0;
    *(int*)(self + 0x230) = 0x41a00000;
    *(unsigned char*)(self + 0x234) = 0;
    *(int*)(self + 0x178) = 0x40800000;
    *(int*)(self + 0x6ec) = 0;
    *(int*)(self + 0x6f0) = 0x3f800000;
    *(int*)(self + 0x214) = 0x41200000;
    *(int*)(self + 0x218) = 0x41700000;
    *(int*)(self + 0x26c) = 0x41a00000;
    *(int*)(self + 0x258) = 0;
    *(int*)(self + 0x38) = 1;
    unhide_border_init();

    int widget_flags = flags | 0x40801;
    *(float*)(self + 0x6f8) = y;
    *(int*)(self + 0x1a0) = widget_flags;
    *(int*)(self + 0x1a4) = widget_flags;
    *(unsigned char*)(self + 0x2cc) = 0;
    *(float*)(self + 0x6f4) = x;

    *(Color4f*)(self + 0x1bc) = *color;
    *(Color4f*)(self + 0x1cc) = *color;

    Color4f white;
    *(Color4f*)(self + 0x1ec) = *white.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f);
    *(Color4f*)(self + 0x1fc) = *white.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f);

    if ((*(unsigned char*)(self + 0x1a0) & 2) != 0) {
        *(int*)(self + 0x20c) = 0x3f800000;
        *(int*)(self + 0x21c) = *(int*)(self + 0x218);
    } else {
        *(int*)(self + 0x20c) = 0;
        *(int*)(self + 0x21c) = *(int*)(self + 0x214);
    }

    *(int*)(self + 0x210) = *(int*)(self + 0x20c);
    *(int*)(self + 0x220) = *(int*)(self + 0x21c);
    *(int*)(self + 0x224) = 0;
    *(int*)(self + 0x228) = 0;
    *(int*)(self + 0x25c) = 0;
    *(float*)(self + 0x260) = anchor_x;
    *(float*)(self + 0x238) = x;
    *(float*)(self + 0x23c) = y;
    *(float*)(self + 0x260) = anchor_x + *(float*)(g_game_base + 0x440fc);

    TextureRef* texture = g_sprite_texture_table[sprite];
    *(float*)(self + 0x248) = (float)*(int*)((char*)texture + 4);
    *(int*)(self + 0x250) = *(int*)(self + 0x248);
    *(int*)(self + 0x270) = sprite;
    *(float*)(self + 0x24c) = (float)*(int*)((char*)texture + 8);
    *(int*)(self + 0x254) = *(int*)(self + 0x24c);
    *(float*)(self + 0x6f4) = x;
    *(float*)(self + 0x6f8) = y;
    *(int*)(self + 0x274) = layer;
    *(int*)(self + 0x264) = 0;
    *(int*)(self + 0x268) = 0;
    layout_frontend_widget();
}
