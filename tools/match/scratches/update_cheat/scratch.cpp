// update_cheat @ 0x404750 (thiscall, ret)

#include "cheat_state.h"

void CheatState::update_cheat()
{
    char key = read_pressed_text_input_key_code();
    if (key >= 'a' && key <= 'z') {
        key -= 0x20;
    }

    if (key >= 'A' && key <= 'Z') {
        int index = 7;
        do {
            recent_text[index] = recent_text[index - 1];
            --index;
        } while (index > 0);

        recent_text[0] = key;

        if (match_cheat_text("NEWTON") != 0) {
            flags |= CHEAT_STATE_FLAG_NEWTON;
        }
        if (match_cheat_text("AUTUMN") != 0) {
            flags |= CHEAT_STATE_FLAG_AUTUMN;
        }
        key = match_cheat_text("SHEEP");
        if (key != 0) {
            int value = flags;
            value |= CHEAT_STATE_FLAG_SHEEP;
            flags = value;
            key = (char)value;
        }
    }
}
