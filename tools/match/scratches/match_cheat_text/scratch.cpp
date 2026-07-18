// match_cheat_text @ 0x4047d0 (thiscall, ret)

#include "cheat_state.h"

#include <string.h>

int report_errorf(char* format, ...);

bool CheatState::match_cheat_text(char* text)
{
    unsigned int text_size = strlen(text) + 1;
    int length = text_size - 1;
    if (length >= 8) {
        report_errorf("Cheat text too long");
        return 0;
    }

    int index = 0;
    if (0 < length) {
        char* cursor = recent_text + length - 1;
        for (; index < length;) {
            char expected = text[index];
            char actual = *cursor;
            if (expected != actual) {
                return 0;
            }
            ++index;
            --cursor;
        }
    }

    return 1;
}
