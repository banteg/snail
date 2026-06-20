// initialize_frontend_widget @ 0x401d30 (thiscall, ret 0x20)

#include "border_manager.h"
#include "frontend_widget.h"

extern char* g_game_base; // data_4df904
extern char g_blank_text[]; // data_4dfb08

int report_errorf(char* format, ...);
void __cdecl rstrcpy_checked_ascii(char* destination, char* source);

static void copy_color(Color4f* out, Color4f* in)
{
    *out = *in;
}

int FrontendWidget::initialize_frontend_widget(
    int flags,
    char* text,
    int widget_type,
    float x,
    float y,
    Color4f* color,
    int alignment,
    float anchor_x)
{
    char* self = (char*)this;
    FrontendWidget* head = (FrontendWidget*)(g_game_base + 0xb4c);
    Color4f tmp;

    *(int*)(self + 0x10) = widget_type;
    *(int*)(self + 0x48) = 5;
    *(unsigned char*)(self + 0x5c) = 0;
    *(int*)(self + 0x178) = 0;
    *(float*)(self + 0x22c) = 0.0f;
    *(float*)(self + 0x230) = 20.0f;
    *(unsigned char*)(self + 0x234) = 0;

    if ((list_flags & 0x200) != 0) {
        report_errorf("List ADDafter");
    } else {
        list_prev = head;
        list_next = head->list_next;
        head->list_next = this;
        if (list_next != 0)
            list_next->list_prev = this;
        list_flags |= 0x200;
    }

    *(int*)(self + 0x290) = 0;
    *(FrontendWidget**)(self + 0x298) = this;
    *(FrontendWidget**)(self + 0x2a4) = 0;
    *(FrontendWidget**)(self + 0x2c4) = this;
    *(int*)(self + 0x1a0) = flags | 0x40001;

    ((Color4f*)(self + 0x1dc))->set_color_white();
    ((Color4f*)(self + 0x1ec))->set_color_white();

    switch (widget_type) {
    case 20:
        *(float*)(self + 0x18) = 0.0f;
        *(float*)(self + 0x1c) = 1.3f;
        *(float*)(self + 0x214) = 9.0f;
        *(float*)(self + 0x218) = 13.0f;
        *(float*)(self + 0x26c) = 26.0f;
        copy_color((Color4f*)(self + 0x1ec), tmp.set_color_rgba(1.0f, 0.52156866f, 0.0f, 0.69999999f));
        copy_color((Color4f*)(self + 0x1fc), tmp.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f));
        copy_color((Color4f*)(self + 0x1ac), tmp.set_color_rgba(0.32941177f, 0.22352941f, 0.50196081f, 0.69999999f));
        copy_color((Color4f*)(self + 0x1bc), tmp.set_color_rgba(0.60784316f, 0.30980393f, 0.69411767f, 1.0f));
        break;
    case 21:
        *(float*)(self + 0x18) = 0.0f;
        *(float*)(self + 0x1c) = 1.0f;
        *(float*)(self + 0x214) = 9.0f;
        *(float*)(self + 0x218) = 13.0f;
        *(float*)(self + 0x26c) = 26.0f;
        copy_color((Color4f*)(self + 0x1ec), tmp.set_color_rgba(1.0f, 0.52156866f, 0.0f, 0.69999999f));
        copy_color((Color4f*)(self + 0x1fc), tmp.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f));
        copy_color((Color4f*)(self + 0x1ac), tmp.set_color_rgba(0.32941177f, 0.22352941f, 0.50196081f, 0.69999999f));
        copy_color((Color4f*)(self + 0x1bc), tmp.set_color_rgba(0.60784316f, 0.30980393f, 0.69411767f, 1.0f));
        break;
    case 22:
        *(float*)(self + 0x230) = 20.0f;
        *(float*)(self + 0x18) = 0.0f;
        *(float*)(self + 0x1c) = 0.64999998f;
        *(float*)(self + 0x214) = 1.0f;
        *(float*)(self + 0x218) = 3.0f;
        *(float*)(self + 0x26c) = 2.0f;
        *(unsigned char*)(self + 0x234) = 1;
        copy_color((Color4f*)(self + 0x1ec), tmp.set_color_rgba(1.0f, 0.52156866f, 0.0f, 0.69999999f));
        copy_color((Color4f*)(self + 0x1fc), tmp.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f));
        copy_color((Color4f*)(self + 0x1ac), tmp.set_color_rgba(0.32941177f, 0.22352941f, 0.50196081f, 0.69999999f));
        copy_color((Color4f*)(self + 0x1bc), tmp.set_color_rgba(0.60784316f, 0.30980393f, 0.69411767f, 1.0f));
        break;
    case 23:
        *(float*)(self + 0x18) = 0.0f;
        *(float*)(self + 0x1c) = 1.14f;
        *(float*)(self + 0x214) = 6.0f;
        *(float*)(self + 0x218) = 7.0f;
        *(float*)(self + 0x26c) = 2.0f;
        *(float*)(self + 0x230) = 20.0f;
        copy_color((Color4f*)(self + 0x1ec), tmp.set_color_rgba(1.0f, 0.52156866f, 0.0f, 0.69999999f));
        copy_color((Color4f*)(self + 0x1fc), tmp.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f));
        copy_color((Color4f*)(self + 0x1ac), tmp.set_color_rgba(0.32941177f, 0.22352941f, 0.50196081f, 0.69999999f));
        copy_color((Color4f*)(self + 0x1bc), tmp.set_color_rgba(0.60784316f, 0.30980393f, 0.69411767f, 1.0f));
        break;
    default:
        report_errorf("Unknown Border Style Requested");
        break;
    }

    *(float*)(self + 0x17c) = 0.5f;
    *(float*)(self + 0x180) = 0.5f;
    *(int*)(self + 0x38) = 1;
    unhide_border_init();
    rstrcpy_checked_ascii(self + 0x2cc, text);
    *(float*)(self + 0x6f8) = y;
    *(float*)(self + 0x6f4) = x;
    *(float*)(self + 0x20c) = 1.0f;

    if ((*(unsigned char*)(self + 0x1a0) & 2) != 0)
        highlight_border();
    else
        unhighlight_border();

    *(float*)(self + 0x210) = *(float*)(self + 0x20c);
    *(float*)(self + 0x21c) = *(float*)(self + 0x214);
    *(float*)(self + 0x220) = *(float*)(self + 0x214);
    *(float*)(self + 0x224) = 0.0f;
    *(float*)(self + 0x228) = 0.0f;
    *(int*)(self + 0x25c) = alignment;
    *(float*)(self + 0x260) = anchor_x;
    *(int*)(self + 0x264) = 1;
    *(float*)(self + 0x260) = anchor_x + *(float*)(g_game_base + 0x440fc);

    if ((*(unsigned int*)(self + 0x1a0) & 0x100000) != 0) {
        Color4f white;
        float slider_y = y + 40.0f;
        FrontendWidget* more = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
        *(FrontendWidget**)(self + 0x184) = more;
        more->initialize_frontend_sprite_button(
            (*(unsigned int*)(self + 0x1a0) & 0x800000) | 0x20400814,
            42,
            *(float*)(g_game_base + 0x440fc) + 458.0f,
            slider_y,
            white.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            0.0f,
            4);
        more->border_sprite_extend(44, 43, 45, 1);

        FrontendWidget* less = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
        *(FrontendWidget**)(self + 0x188) = less;
        less->initialize_frontend_sprite_button(
            (*(unsigned int*)(self + 0x1a0) & 0x800000) | 0x20400814,
            38,
            *(float*)(g_game_base + 0x440fc) + 118.0f,
            slider_y,
            white.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            0.0f,
            4);
        less->border_sprite_extend(40, 39, 41, 0);

        FrontendWidget* value = ((BorderManager*)(g_game_base + 0xb4c))->allocate_border();
        *(FrontendWidget**)(self + 0x18c) = value;
        value->initialize_frontend_widget(
            0x400000,
            (char*)"00%",
            21,
            0.0f,
            *(float*)(self + 0x6f8) + 40.0f,
            white.set_color_rgba(1.0f, 1.0f, 1.0f, 1.0f),
            2,
            0.0f);
    }

    return layout_frontend_widget();
}
