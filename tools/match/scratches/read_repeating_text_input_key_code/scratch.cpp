// read_repeating_text_input_key_code @ 0x4327e0 (cdecl)

#include "rstring.h"
#include "text_input_repeat_state.h"

unsigned char is_key_down(int key_code); // @ 0x44bb40

char read_repeating_text_input_key_code()
{
    char result = 0;

    if (is_key_down(0x1e)) {
        result = 'a';
    }
    if (is_key_down(0x30)) {
        result = 'b';
    }
    if (is_key_down(0x2e)) {
        result = 'c';
    }
    if (is_key_down(0x20)) {
        result = 'd';
    }
    if (is_key_down(0x12)) {
        result = 'e';
    }
    if (is_key_down(0x21)) {
        result = 'f';
    }
    if (is_key_down(0x22)) {
        result = 'g';
    }
    if (is_key_down(0x23)) {
        result = 'h';
    }
    if (is_key_down(0x17)) {
        result = 'i';
    }
    if (is_key_down(0x24)) {
        result = 'j';
    }
    if (is_key_down(0x25)) {
        result = 'k';
    }
    if (is_key_down(0x26)) {
        result = 'l';
    }
    if (is_key_down(0x32)) {
        result = 'm';
    }
    if (is_key_down(0x31)) {
        result = 'n';
    }
    if (is_key_down(0x18)) {
        result = 'o';
    }
    if (is_key_down(0x19)) {
        result = 'p';
    }
    if (is_key_down(0x10)) {
        result = 'q';
    }
    if (is_key_down(0x13)) {
        result = 'r';
    }
    if (is_key_down(0x1f)) {
        result = 's';
    }
    if (is_key_down(0x14)) {
        result = 't';
    }
    if (is_key_down(0x16)) {
        result = 'u';
    }
    if (is_key_down(0x2f)) {
        result = 'v';
    }
    if (is_key_down(0x11)) {
        result = 'w';
    }
    if (is_key_down(0x2d)) {
        result = 'x';
    }
    if (is_key_down(0x15)) {
        result = 'y';
    }
    if (is_key_down(0x2c)) {
        result = 'z';
    } else if (result == 0) {
        goto after_letters;
    }

    if (is_key_down(0x2a) || is_key_down(0x36)) {
        result -= 0x20;
    }

after_letters:
    if (is_key_down(0x39)) {
        result = ' ';
    }
    if (is_key_down(0x0b)) {
        result = '0';
    }
    if (is_key_down(0x02)) {
        result = '1';
    }
    if (is_key_down(0x03)) {
        result = '2';
    }
    if (is_key_down(0x04)) {
        result = '3';
    }
    if (is_key_down(0x05)) {
        result = '4';
    }
    if (is_key_down(0x06)) {
        result = '5';
    }
    if (is_key_down(0x07)) {
        result = '6';
    }
    if (is_key_down(0x08)) {
        result = '7';
    }
    if (is_key_down(0x09)) {
        result = '8';
    }
    if (is_key_down(0x0a)) {
        result = '9';
    }
    if (is_key_down(0x34)) {
        result = '.';
    }
    if (is_key_down(0x33)) {
        result = ',';
    }
    if (is_key_down(0x28)) {
        result = '\'';
    }
    if (is_key_down(0x2b)) {
        result = '\\';
    }
    if (is_key_down(0x0e)) {
        result = 1;
    }
    if (is_key_down(0xd3)) {
        result = 2;
    }
    if (is_key_down(0xcb)) {
        result = 3;
    }
    if (is_key_down(0xcd)) {
        result = 4;
    }
    if (is_key_down(0xc8)) {
        result = 7;
    }
    if (is_key_down(0xd0)) {
        result = 8;
    }
    if (is_key_down(0xcf)) {
        result = 9;
    }
    if (is_key_down(0xc7)) {
        result = 10;
    }
    if (is_key_down(0x01)) {
        result = 11;
    }
    if (is_key_down(0x3b)) {
        result = 12;
    }
    if (is_key_down(0x1c)) {
        result = is_key_down(0x1d) ? 6 : 5;
    } else if (result == 0) {
        g_text_input_repeat_accumulator = 0.0f;
        g_text_input_last_repeat_code = 0;
        return 0;
    }

    if (g_text_input_repeat_accumulator == 0.0f) {
        g_text_input_last_repeat_code = result;
        g_text_input_repeat_step = 0.033333335f;
        g_text_input_repeat_accumulator = 0.033333335f;
        return result;
    }

    if (RstrASC(g_text_input_last_repeat_code)
        == RstrASC(result)) {
        float accumulator = g_text_input_repeat_step + g_text_input_repeat_accumulator;
        g_text_input_repeat_accumulator = accumulator;
        if (accumulator > 1.0f) {
            g_text_input_repeat_step = 0.111111104f;
            g_text_input_repeat_accumulator = 0.111111104f;
            return result;
        }

        return 0;
    }

    g_text_input_last_repeat_code = result;
    g_text_input_repeat_step = 0.011111111f;
    g_text_input_repeat_accumulator = 0.011111111f;
    return result;
}
