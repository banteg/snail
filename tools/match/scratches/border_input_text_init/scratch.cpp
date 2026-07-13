// border_input_text_init @ 0x403410 (thiscall, ret 0xc)

#include "frontend_widget.h"
#include "input_ok_state.h"

void __cdecl rstrcpy_checked_ascii(char* destination, char* source);

FrontendWidget* FrontendWidget::border_input_text_init(int arg2, char* text, int flags)
{
    input_flags = flags;
    rstrcpy_checked_ascii(text_buffer + 0x400, text);

    input_cursor = 0;
    input_length = 0;

    char* cursor = text_buffer;
    char ch = *cursor;
    if (ch != 0) {
        do {
            ++cursor;
            ++input_length;
            ++input_cursor;
            ch = *cursor;
        } while (ch != 0);
    }

    text_buffer[input_cursor] = '|';
    text_buffer[input_cursor + 1] = 0;
    input_cursor_blink_progress = 0.0f;
    input_cursor_visible = 1;
    input_capacity = arg2;
    *(int*)&input_cursor_blink_step = 0x3daaaaab;

    FrontendWidget* result = (FrontendWidget*)layout_frontend_widget();
    if ((flags & 0xc) != 0)
        return ((InputOkState*)((char*)this + 0x2a8))->initialize_input_ok();
    return result;
}
