// Live input for the shell: keys, pointer and mouse buttons as the platform
// layer reports them, read by the recovered polling code. Keys reach
// update_keyboard_input through a DirectInput device; buttons arrive as
// game_window_proc set them for WM_*BUTTONDOWN/UP and WM_MOUSEWHEEL; the
// mouse is a 640x480 client area at the screen origin. The joystick reports
// nothing. Scripts (input_script.cpp) and the browser (web_main.cpp) drive it.

#include <string.h>
#include <algorithm>
#include <vector>

#include "direct_input_view.h"
#include "game_root.h"
#include "input_controller_state.h"
#include "input_polling.h"
#include "input_state.h"
#include "mouse_input_state.h"
#include "profile.h"
#include "win32_window_state.h"

namespace {

unsigned char g_keys[DIRECT_INPUT_KEY_COUNT];
int g_mouse_x = 320, g_mouse_y = 240;

// Each change alternates between up and down. Deliver one per fixed tick so
// even two complete clicks between polls produce two distinct press edges.
struct ButtonChanges {
    std::vector<unsigned> held_sources;
    unsigned count = 0;
    bool sampled_down = false;
    bool completed = false;

    bool change(unsigned source, bool down, bool cancelled)
    {
        bool was_held = !held_sources.empty();
        auto found = std::find(held_sources.begin(), held_sources.end(), source);
        if (down && found == held_sources.end()) {
            if (!was_held)
                completed = false;
            held_sources.push_back(source);
        } else if (!down && found != held_sources.end()) {
            completed |= !cancelled;
            held_sources.erase(found);
        }
        bool held = !held_sources.empty();
        if (held != was_held) {
            if (cancelled && !completed && count)
                --count;  // every contributing source cancelled before the press was sampled
            else
                ++count;
        }
        return held;
    }

    bool poll()
    {
        if (count) {
            --count;
            sampled_down = !sampled_down;
        }
        return sampled_down;
    }

    void reset()
    {
        held_sources.clear();
        // If the game already observed a hold, it still needs to observe the
        // release before a new press delivered immediately after focus returns.
        count = sampled_down ? 1 : 0;
        completed = false;
    }
};

ButtonChanges g_button_changes[2];

struct LiveKeyboard : DirectInputDevice {
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

LiveKeyboard g_keyboard;

}  // namespace

void install_input_devices()
{
    g_keyboard_device = &g_keyboard;
    input_reset_buttons_and_keys();
}

void input_set_key(int scan_code, bool down)
{
    if (scan_code >= 0 && scan_code < DIRECT_INPUT_KEY_COUNT)
        g_keys[scan_code] = down ? 0x80 : 0;
}

void input_set_pointer(int x, int y)
{
    g_mouse_x = x;
    g_mouse_y = y;
}

void input_set_button(int button, bool down, unsigned source, bool cancelled)
{
    if (button != INPUT_MOUSE_LEFT && button != INPUT_MOUSE_RIGHT)
        return;
    unsigned char* latch = button == INPUT_MOUSE_LEFT ? g_left_mouse_button_latch : g_right_mouse_button_latch;
    unsigned char* state = button == INPUT_MOUSE_LEFT ? g_left_mouse_button_state : g_right_mouse_button_state;
    if (g_port_ultimate)
        down = g_button_changes[button].change(source, down, cancelled);
    latch[0] = state[0] = down;
}

void input_add_wheel(int direction)
{
    g_mouse_wheel_delta[0] = direction > 0 ? 1 : -1;
}

void input_reset_buttons_and_keys()
{
    memset(g_keys, 0, sizeof(g_keys));
    g_left_mouse_button_latch[0] = g_left_mouse_button_state[0] = 0;
    g_right_mouse_button_latch[0] = g_right_mouse_button_state[0] = 0;
    g_button_changes[INPUT_MOUSE_LEFT].reset();
    g_button_changes[INPUT_MOUSE_RIGHT].reset();
    g_mouse_wheel_delta[0] = 0;
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
    bool left = read_left_mouse_button_state(0);
    bool right = read_right_mouse_button_state(0);
    if (g_port_ultimate) {
        left = g_button_changes[INPUT_MOUSE_LEFT].poll();
        right = g_button_changes[INPUT_MOUSE_RIGHT].poll();
    }
    update_input_controller_pointer_region(0, 0, 0, 640, 480, g_mouse_x, g_mouse_y, consume_mouse_wheel_delta(0),
        left, right, 0, g_game->players[0].mouse_cursor.IsActive(), g_fullscreen_active);
    return 0;
}
