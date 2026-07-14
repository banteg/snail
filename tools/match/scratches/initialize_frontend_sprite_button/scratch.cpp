// initialize_frontend_sprite_button @ 0x401a70 (thiscall, ret 0x1c)

#include "border_manager.h"
#include "frontend_widget.h"
#include "game_root.h"

extern GameRoot* g_game; // data_4df904
int report_errorf(char* format, ...);

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
    FrontendWidget* head = (FrontendWidget*)&g_game->border_manager;

    if ((list_flags & 0x200) != 0) {
        report_errorf("List ADDafter");
    } else {
        list_prev = head;
        list_next = head->list_next;
        head->list_next = this;
        BodNode* next = list_next;
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
    Color4f* idle_fill = (Color4f*)(self + 0x1bc);
    *(int*)(self + 0x6f0) = 0x3f800000;
    *(int*)(self + 0x214) = 0x41200000;
    *(int*)(self + 0x218) = 0x41700000;
    *(int*)(self + 0x26c) = 0x41a00000;
    *(int*)(self + 0x258) = 0;
    *(int*)(self + 0x38) = 1;
    unhide_border_init();

    int widget_flags = flags | 0x40801;
    *(int*)(self + 0x1a0) = widget_flags;
    *(int*)(self + 0x1a4) = widget_flags;
    *(unsigned char*)(self + 0x2cc) = 0;
    *(float*)(self + 0x6f4) = x;
    *(float*)(self + 0x6f8) = y;

    *idle_fill = *color;
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
    float adjusted_anchor_x =
        anchor_x + g_game->border_manager.justify_centre;
    *(float*)(self + 0x238) = x;
    *(float*)(self + 0x23c) = y;
    *(float*)(self + 0x260) = adjusted_anchor_x;

    layout_width = (float)g_sprite_texture_table[sprite]->loaded_width;
    layout_height = (float)g_sprite_texture_table[sprite]->loaded_height;
    texture_hit_width = layout_width;
    texture_hit_height = layout_height;
    layout_anchor_x = x;
    *(int*)(self + 0x270) = sprite;
    layout_anchor_y = y;
    *(int*)(self + 0x274) = layer;
    teardown_progress = 0.0f;
    teardown_progress_step = 0.0f;
    layout_frontend_widget();
}
