// border_input_text_init @ 0x403410 (thiscall, ret 0xc)

#include "frontend_widget.h"
#include "input_ok_state.h"

void __cdecl rstrcpy_checked_ascii(char* destination, char* source);

FrontendWidget* FrontendWidget::border_input_text_init(int arg2, char* text, int flags)
{
    char* self = (char*)this;

    *(int*)(self + 0x70c) = flags;
    rstrcpy_checked_ascii(self + 0x6cc, text);

    *(int*)(self + 0x6fc) = 0;
    *(int*)(self + 0x710) = 0;

    char* cursor = text_buffer;
    char ch = *cursor;
    if (ch != 0) {
        do {
            ++cursor;
            ++*(int*)(self + 0x710);
            ++*(int*)(self + 0x6fc);
            ch = *cursor;
        } while (ch != 0);
    }

    text_buffer[*(int*)(self + 0x6fc)] = '|';
    text_buffer[*(int*)(self + 0x6fc) + 1] = 0;
    *(int*)(self + 0x704) = 0;
    *(int*)(self + 0x700) = 1;
    *(int*)(self + 0x714) = arg2;
    *(int*)(self + 0x708) = 0x3daaaaab;

    FrontendWidget* result = (FrontendWidget*)layout_frontend_widget();
    if ((flags & 0xc) != 0)
        return ((InputOkState*)(self + 0x2a8))->initialize_input_ok();
    return result;
}
