#ifndef CHEAT_STATE_H
#define CHEAT_STATE_H

class CheatState {
public:
    int initialize_cheat();
    char update_cheat();
    char match_cheat_text(const char* text);

    int flags; // +0x00
    int unused_04; // +0x04
    int recent_text_0; // +0x08
    int recent_text_4; // +0x0c
};

typedef char CheatState_must_be_0x10[
    (sizeof(CheatState) == 0x10) ? 1 : -1];

extern CheatState g_cheat_state; // data_4b2f40

char read_pressed_text_input_key_code(); // @ 0x432440

#endif
