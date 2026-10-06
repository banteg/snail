#ifndef SNAIL_PORT_INPUT_SCRIPT_H
#define SNAIL_PORT_INPUT_SCRIPT_H

// Scripted input for the headless port (shell/input_script.cpp).
bool load_input_script(const char* path);
void install_scripted_keyboard();
void set_scripted_input(int tick);  // keys, buttons and pointer for this fixed tick
int last_scripted_tick();           // first tick after the last event ends, or -1

#endif
