// update_cheat @ 0x404750 (thiscall, ret)

#include "cheat_state.h"

char CheatState::update_cheat()
{
    char key = read_pressed_text_input_key_code();
    if (key >= 'a' && key <= 'z') {
        key -= 0x20;
    }

    if (key >= 'A' && key <= 'Z') {
        int index = 7;
        do {
            ((char*)this)[index + 8] = ((char*)this)[index + 7];
            --index;
        } while (index > 0);

        ((char*)this)[8] = key;

        if (match_cheat_text("NEWTON") != 0) {
            flags |= 1;
        }
        if (match_cheat_text("AUTUMN") != 0) {
            flags |= 2;
        }
        key = match_cheat_text("SHEEP");
        if (key != 0) {
            int value = flags;
            value |= 4;
            flags = value;
            key = (char)value;
        }
    }

    return key;
}
