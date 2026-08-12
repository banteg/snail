#ifndef CHEAT_STATE_H
#define CHEAT_STATE_H

enum CheatStateFlag {
    CHEAT_STATE_FLAG_NEWTON = 0x01,
    CHEAT_STATE_FLAG_AUTUMN = 0x02,
    CHEAT_STATE_FLAG_SHEEP = 0x04,
};

class cRCheat {
public:
    void Init();
    void AI();
    bool MatchText(char* text);

    int flags; // +0x00
    int unused_04; // +0x04
    union {
        struct {
            int recent_text_0; // +0x08, constructor-width zeroing view
            int recent_text_4; // +0x0c
        };
        char recent_text[8]; // +0x08, rolling uppercase input buffer
    };
};

typedef cRCheat CheatState;
typedef char CheatState_must_be_0x10[
    (sizeof(cRCheat) == 0x10) ? 1 : -1];

extern cRCheat g_cheat_state; // data_4b2f40

char read_pressed_text_input_key_code(); // @ 0x432440

#endif
