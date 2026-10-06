// Headless input from a script. Keys reach the recovered update_keyboard_input
// through a DirectInput device; the mouse is a 640x480 window at the origin,
// whose buttons arrive as the window procedure would set them. The joystick
// reports nothing. Stage 4 feeds SDL3 events into the same paths.
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
#include "game_root.h"
#include "input_controller_state.h"
#include "input_polling.h"
#include "mouse_input_state.h"
#include "win32_window_state.h"
#include "input_script.h"

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
unsigned char g_keys[DIRECT_INPUT_KEY_COUNT];
bool g_left_held = false, g_right_held = false;
int g_mouse_x = 320, g_mouse_y = 240;

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

struct ScriptedKeyboard : DirectInputDevice {
    int __stdcall QueryInterface(void*, void**) override { return -1; }
    int __stdcall AddRef() override { return 1; }
    int __stdcall Release() override { return 0; }
    int __stdcall GetCapabilities(void*) override { return 0; }
    int __stdcall EnumObjects(DirectInputEnumObjectsCallback, void*, unsigned int) override { return 0; }
    int __stdcall GetProperty(void*, void*) override { return 0; }
    int __stdcall SetProperty(void*, DIPROPHEADER*) override { return 0; }
    int __stdcall Acquire() override { return 0; }
    int __stdcall Unacquire() override { return 0; }
    int __stdcall GetDeviceState(unsigned int size, void* data) override
    {
        memcpy(data, g_keys, size < sizeof(g_keys) ? size : sizeof(g_keys));
        return 0;
    }
    int __stdcall GetDeviceData(unsigned int, void*, unsigned int*, unsigned int) override { return 0; }
    int __stdcall SetDataFormat(const DIDATAFORMAT*) override { return 0; }
    int __stdcall SetEventNotification(void*) override { return 0; }
    int __stdcall SetCooperativeLevel(int, unsigned int) override { return 0; }
    int __stdcall GetObjectInfo(void*, unsigned int, unsigned int) override { return 0; }
    int __stdcall GetDeviceInfo(void*) override { return 0; }
    int __stdcall RunControlPanel(int, unsigned int) override { return 0; }
    int __stdcall Initialize(void*, unsigned int, void*) override { return 0; }
    int __stdcall CreateEffect(void*, void*, void**, void*) override { return 0; }
    int __stdcall EnumEffects(void*, void*, unsigned int) override { return 0; }
    int __stdcall GetEffectInfo(void*, void*) override { return 0; }
    int __stdcall GetForceFeedbackState(unsigned int*) override { return 0; }
    int __stdcall SendForceFeedbackCommand(unsigned int) override { return 0; }
    int __stdcall EnumCreatedEffectObjects(void*, void*, unsigned int) override { return 0; }
    int __stdcall Escape(void*) override { return 0; }
    int __stdcall Poll() override { return 0; }
};

ScriptedKeyboard g_scripted_keyboard;

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

void install_scripted_keyboard()
{
    g_keyboard_device = &g_scripted_keyboard;
}

void set_scripted_input(int tick)
{
    memset(g_keys, 0, sizeof(g_keys));
    bool left = false, right = false;
    for (int i = 0; i < g_press_count; ++i) {
        const Press& press = g_presses[i];
        if (press.code < 0) {
            if (press.tick == tick) {
                g_mouse_x = press.duration;
                g_mouse_y = press.y;
            }
        } else if (press.tick <= tick && tick < press.tick + press.duration) {
            if (press.code == kLeftButton)
                left = true;
            else if (press.code == kRightButton)
                right = true;
            else
                g_keys[press.code] = 0x80;
        }
    }
    // WM_LBUTTONDOWN/UP and WM_RBUTTONDOWN/UP in game_window_proc.
    if (left != g_left_held)
        g_left_mouse_button_latch[0] = g_left_mouse_button_state[0] = left;
    if (right != g_right_held)
        g_right_mouse_button_latch[0] = g_right_mouse_button_state[0] = right;
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

int update_joystick_input(HWND) { return 0; }
int consume_mouse_wheel_delta(int slot);       // @ 0x4077f0
unsigned char read_left_mouse_button_state(int slot);   // @ 0x407810
unsigned char read_right_mouse_button_state(int slot);  // @ 0x407830

// update_mouse (0x44bc50) for a 640x480 client area at the screen origin with
// no clip insets: both of its branches reduce to this call.
int update_mouse(HWND)
{
    g_mouse_live_x[0] = (float)g_mouse_x;
    g_mouse_live_y[0] = (float)g_mouse_y;
    update_input_controller_pointer_region(0, 0, 0, 640, 480, g_mouse_x, g_mouse_y, consume_mouse_wheel_delta(0),
        read_left_mouse_button_state(0), read_right_mouse_button_state(0), 0,
        g_game->players[0].mouse_cursor.IsActive(), g_fullscreen_active);
    return 0;
}
int read_repeating_text_input_key_code() { return 0; }
