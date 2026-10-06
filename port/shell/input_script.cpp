// Headless input from a script, applied to the live input state
// (input_state.cpp) once per fixed tick.
//
// Script lines, `#` starting a comment:
//   <tick> <key> [<ticks held>]    DirectInput scan code (0x1c) or a kKeyNames name
//   <tick> click|rclick [<ticks held>]
//   <tick> mouse <x> <y>           pointer position from this tick on
// Keys and buttons are held for one tick unless a duration is given.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "direct_input_view.h"
#include "input_script.h"
#include "input_state.h"

namespace {

struct KeyName {
    const char* name;
    unsigned char code;
};

const KeyName kKeyNames[] = {
    {"escape", 0x01}, {"return", 0x1c}, {"enter", 0x1c}, {"lcontrol", 0x1d}, {"lshift", 0x2a},
    {"space", 0x39}, {"lalt", 0x38}, {"f2", 0x3c}, {"up", 0xc8}, {"down", 0xd0}, {"left", 0xcb},
    {"right", 0xcd}, {"a", 0x1e}, {"s", 0x1f}, {"w", 0x11}, {"e", 0x12}, {"x", 0x2d}, {"z", 0x2c},
    {"c", 0x2e}, {"y", 0x15}, {"n", 0x31},
};

// Button codes past the keyboard's scan codes.
const int kLeftButton = DIRECT_INPUT_KEY_COUNT;
const int kRightButton = DIRECT_INPUT_KEY_COUNT + 1;

struct Press {
    int tick;
    int code;      // scan code, kLeftButton or kRightButton; -1 for a move
    int duration;  // ticks held; for a move, x
    int y;
};

Press* g_presses = 0;
int g_press_count = 0;
bool g_left_held = false, g_right_held = false;

int parse_key(const char* text)
{
    if (strncmp(text, "0x", 2) == 0)
        return (int)strtol(text, 0, 16);
    if (strcasecmp(text, "click") == 0)
        return kLeftButton;
    if (strcasecmp(text, "rclick") == 0)
        return kRightButton;
    for (const KeyName& key : kKeyNames)
        if (strcasecmp(key.name, text) == 0)
            return key.code;
    return -1;
}



}  // namespace

bool load_input_script(const char* path)
{
    FILE* file = fopen(path, "r");
    if (!file)
        return false;
    char line[256];
    int capacity = 0;
    int number = 0;
    while (fgets(line, sizeof(line), file)) {
        ++number;
        if (char* comment = strchr(line, '#'))
            *comment = 0;
        char key[64];
        Press press = {0, 0, 1, 0};
        int fields = sscanf(line, "%d %63s %d %d", &press.tick, key, &press.duration, &press.y);
        if (fields <= 0)
            continue;
        bool move = fields == 4 && strcasecmp(key, "mouse") == 0;
        press.code = move ? -1 : fields >= 2 ? parse_key(key) : -2;
        if (press.code == -2 || (!move && (fields > 3 || press.duration < 1))) {
            fprintf(stderr, "%s:%d: expected `<tick> <key|click|rclick> [<ticks held>]` or `<tick> mouse <x> <y>`\n",
                path, number);
            fclose(file);
            return false;
        }
        if (g_press_count == capacity) {
            capacity = capacity ? capacity * 2 : 64;
            g_presses = (Press*)realloc(g_presses, capacity * sizeof(Press));
        }
        g_presses[g_press_count++] = press;
    }
    fclose(file);
    return true;
}

void set_scripted_input(int tick)
{
    unsigned char keys[DIRECT_INPUT_KEY_COUNT] = {0};
    bool left = false, right = false;
    for (int i = 0; i < g_press_count; ++i) {
        const Press& press = g_presses[i];
        if (press.code < 0) {
            if (press.tick == tick)
                input_set_pointer(press.duration, press.y);
        } else if (press.tick <= tick && tick < press.tick + press.duration) {
            if (press.code == kLeftButton)
                left = true;
            else if (press.code == kRightButton)
                right = true;
            else
                keys[press.code] = 1;
        }
    }
    for (int code = 0; code < DIRECT_INPUT_KEY_COUNT; ++code)
        input_set_key(code, keys[code] != 0);
    if (left != g_left_held)
        input_set_button(INPUT_MOUSE_LEFT, left);
    if (right != g_right_held)
        input_set_button(INPUT_MOUSE_RIGHT, right);
    g_left_held = left;
    g_right_held = right;
}

int last_scripted_tick()
{
    int last = -1;
    for (int i = 0; i < g_press_count; ++i) {
        int end = g_presses[i].tick + (g_presses[i].code < 0 ? 1 : g_presses[i].duration);
        if (end > last)
            last = end;
    }
    return last;
}

