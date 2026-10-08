// Lockstep replay: runs a session the original recorded
// (tools/frida/snailmail-lockstep.js), converted to a compact tape by
// `snail port lockstep`. The headless program (--tape) writes the port's state
// after every tick for that command to compare with the original's; the
// browser build steps it with a presenter attached (snail_tape_open), so a
// host can render any recorded frame and compare it with the capture.
//
// For every recorded cRGame::AI call, the tape holds the input state the
// original's main loop left behind after polling (keyboard, controller slots,
// mouse, buttons, wheel, g_render_queue_active), so the port writes that state
// back instead of polling, then runs FontAI and AI as the loop did. Frames
// render on the recorded cadence. The tape also lists which snapshot fields to
// write (offsets into the game root), so this file needs no field table.
//
// Tape (little-endian): "SNTP", version, warmup, renders before the first
// tick, field count, (offset, kind) per field, tick count, then per tick the
// fixed record below. Output: "SNTO", the RNG state after the warmup, field
// count, then per tick the field values, the RNG state and AI's result.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "direct_input_view.h"
#include "font_system.h"
#include "game_root.h"
#include "game_session.h"
#include "input_controller_state.h"
#include "lockstep_tape.h"
#include "main_loop_state.h"
#include "mouse_input_state.h"
#include "rmath_tables.h"

unsigned int msvc_rand_seed();  // shell/runtime.cpp

namespace {

const unsigned int kTapeVersion = 1;

struct TickRecord {
    unsigned char render_queue_active;
    unsigned char padding[3];
    unsigned char keys[32];           // bitmap of held DirectInput scan codes, this poll
    unsigned char previous_keys[32];  // and the previous poll
    unsigned char slot0[sizeof(InputControllerSlot)];
    unsigned char slot1[sizeof(InputControllerSlot)];
    float mouse_x, mouse_y;
    unsigned char left_state, left_latch, right_state, right_latch;
    int wheel;
    unsigned int renders_after;
};
static_assert(sizeof(TickRecord) == 152, "tape record layout (src/snail/port_tape.py)");

struct Field {
    unsigned int offset;
    unsigned int kind;  // values are copied as raw 32-bit words either way
};

unsigned char* read_file(const char* path, long* size)
{
    FILE* file = fopen(path, "rb");
    if (!file)
        return nullptr;
    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    fseek(file, 0, SEEK_SET);
    unsigned char* bytes = (unsigned char*)malloc(*size);
    *size = (long)fread(bytes, 1, *size, file);
    fclose(file);
    return bytes;
}

unsigned int word(const unsigned char*& cursor)
{
    unsigned int value;
    memcpy(&value, cursor, 4);
    cursor += 4;
    return value;
}

void put(FILE* out, unsigned int value)
{
    fwrite(&value, 4, 1, out);
}

void apply(const TickRecord& tick)
{
    for (int code = 0; code < DIRECT_INPUT_KEY_COUNT; ++code) {
        g_keyboard_current_state[code] = (tick.keys[code >> 3] >> (code & 7)) & 1 ? 0x80 : 0;
        g_keyboard_previous_state[code] = (tick.previous_keys[code >> 3] >> (code & 7)) & 1 ? 0x80 : 0;
    }
    memcpy(&g_input_controller_slot0, tick.slot0, sizeof(tick.slot0));
    memcpy(&g_input_controller_slot1, tick.slot1, sizeof(tick.slot1));
    g_mouse_live_x[0] = tick.mouse_x;
    g_mouse_live_y[0] = tick.mouse_y;
    g_left_mouse_button_state[0] = tick.left_state;
    g_left_mouse_button_latch[0] = tick.left_latch;
    g_right_mouse_button_state[0] = tick.right_state;
    g_right_mouse_button_latch[0] = tick.right_latch;
    g_mouse_wheel_delta[0] = tick.wheel;
    g_render_queue_active = tick.render_queue_active;
}

struct Tape {
    unsigned char* bytes = nullptr;
    const unsigned char* ticks = nullptr;
    unsigned int tick_count = 0;
    unsigned int next = 0;
    Field* fields = nullptr;
    unsigned int field_count = 0;
};

Tape g_tape;

}  // namespace

bool tape_open(const char* tape_path)
{
    long size;
    unsigned char* tape = read_file(tape_path, &size);
    if (!tape || size < 24 || memcmp(tape, "SNTP", 4) != 0) {
        fprintf(stderr, "snail: %s is not a lockstep tape\n", tape_path);
        return false;
    }
    const unsigned char* cursor = tape + 4;
    if (word(cursor) != kTapeVersion) {
        fprintf(stderr, "snail: %s has another tape version; rerun snail port lockstep\n", tape_path);
        return false;
    }
    int warmup = (int)word(cursor);
    unsigned int renders_before = word(cursor);
    g_tape.field_count = word(cursor);
    g_tape.fields = (Field*)malloc(g_tape.field_count * sizeof(Field));
    for (unsigned int i = 0; i < g_tape.field_count; ++i) {
        g_tape.fields[i].offset = word(cursor);
        g_tape.fields[i].kind = word(cursor);
    }
    g_tape.tick_count = word(cursor);
    if (cursor + (size_t)g_tape.tick_count * sizeof(TickRecord) > tape + size) {
        fprintf(stderr, "snail: %s is truncated\n", tape_path);
        return false;
    }
    g_tape.bytes = tape;
    g_tape.ticks = cursor;
    g_tape.next = 0;
    if (!start_game(warmup))
        return false;
    for (unsigned int i = 0; i < renders_before; ++i)
        render_frame();
    return true;
}

int tape_step(FILE* states)
{
    if (g_tape.next == g_tape.tick_count)
        return -1;
    TickRecord tick;
    memcpy(&tick, g_tape.ticks + (size_t)g_tape.next++ * sizeof(TickRecord), sizeof(tick));
    apply(tick);
    FontAI();
    int result = g_game->AI();
    if (states) {
        const unsigned char* game = (const unsigned char*)g_game;
        for (unsigned int i = 0; i < g_tape.field_count; ++i) {
            unsigned int value;
            memcpy(&value, game + g_tape.fields[i].offset, 4);
            put(states, value);
        }
        put(states, msvc_rand_seed());
        put(states, (unsigned int)g_math_random_index);
        put(states, (unsigned int)result);
    }
    for (unsigned int i = 0; i < tick.renders_after; ++i)
        render_frame();
    return (int)tick.renders_after;
}

int run_tape(const char* tape_path, const char* out_path)
{
    FILE* out = fopen(out_path, "wb");
    if (!out) {
        fprintf(stderr, "snail: cannot write %s\n", out_path);
        return 2;
    }
    if (!tape_open(tape_path))
        return 2;
    StartupRng rng = startup_rng();
    fwrite("SNTO", 1, 4, out);
    put(out, rng.crt_rand_seed);
    put(out, (unsigned int)rng.math_random_index);
    put(out, g_tape.field_count);
    while (tape_step(out) >= 0) {
    }
    fclose(out);
    end_game();
    fprintf(stderr, "snail: replayed %u ticks\n", g_tape.tick_count);
    return 0;
}
