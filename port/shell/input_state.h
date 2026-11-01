#ifndef SNAIL_PORT_INPUT_STATE_H
#define SNAIL_PORT_INPUT_STATE_H

// Live input state read by the recovered polling code (shell/input_state.cpp).
enum InputMouseButton {
    INPUT_MOUSE_LEFT = 0,
    INPUT_MOUSE_RIGHT = 1,
};

void install_input_devices();
void input_reset_buttons_and_keys();
void input_set_key(int scan_code, bool down);  // DirectInput scan code (DIK_*)
void input_set_pointer(int x, int y);          // 640x480 client coordinates
// A cancelled pointer retracts a press that has not yet reached a tick.
void input_set_button(int button, bool down, unsigned source = 0, bool cancelled = false);
void input_add_wheel(int direction);           // +1 away from the user, -1 towards

#endif
