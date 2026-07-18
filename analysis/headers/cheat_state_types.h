#ifndef CHEAT_STATE_TYPES_H
#define CHEAT_STATE_TYPES_H

/*
 * Exact Windows cRCheat owner. Android preserves the cRCheat::Init(),
 * cRCheat::AI(), cRCheat::MatchText(char*), and gCheat symbols and bounds the
 * global as four dwords. Windows uses the same 0x10-byte owner at 0x4b2f40;
 * the independently named animation-directory global starts at 0x4b2f50.
 */

typedef unsigned int uint32_t;

typedef enum CheatStateFlag {
    CHEAT_STATE_FLAG_NEWTON = 0x01,
    CHEAT_STATE_FLAG_AUTUMN = 0x02,
    CHEAT_STATE_FLAG_SHEEP = 0x04,
} CheatStateFlag;

typedef union CheatTextBuffer {
    char bytes[8];
    uint32_t words[2];
} CheatTextBuffer;

typedef struct CheatState {
    uint32_t flags;
    uint32_t unused_04;
    CheatTextBuffer recent_text;
} CheatState;

extern CheatState g_cheat_state;

#endif
