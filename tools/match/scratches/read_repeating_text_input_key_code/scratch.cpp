// read_repeating_text_input_key_code @ 0x4327e0 (cdecl)

extern float g_text_input_repeat_step;              // data_50339c
extern float g_text_input_repeat_accumulator;       // data_5108b8
extern unsigned char g_text_input_last_repeat_code; // data_53c7f5

unsigned char is_key_down(int key_code); // @ 0x44bb40
char ascii_upper_if_lowercase(char value); // @ 0x44e5a0

char read_repeating_text_input_key_code()
{
    char result = 0;
    char repeat_code = 0;

    if (is_key_down(0x1e)) {
        result = 'a';
        repeat_code = result;
    }
    if (is_key_down(0x30)) {
        result = 'b';
        repeat_code = result;
    }
    if (is_key_down(0x2e)) {
        result = 'c';
        repeat_code = result;
    }
    if (is_key_down(0x20)) {
        result = 'd';
        repeat_code = result;
    }
    if (is_key_down(0x12)) {
        result = 'e';
        repeat_code = result;
    }
    if (is_key_down(0x21)) {
        result = 'f';
        repeat_code = result;
    }
    if (is_key_down(0x22)) {
        result = 'g';
        repeat_code = result;
    }
    if (is_key_down(0x23)) {
        result = 'h';
        repeat_code = result;
    }
    if (is_key_down(0x17)) {
        result = 'i';
        repeat_code = result;
    }
    if (is_key_down(0x24)) {
        result = 'j';
        repeat_code = result;
    }
    if (is_key_down(0x25)) {
        result = 'k';
        repeat_code = result;
    }
    if (is_key_down(0x26)) {
        result = 'l';
        repeat_code = result;
    }
    if (is_key_down(0x32)) {
        result = 'm';
        repeat_code = result;
    }
    if (is_key_down(0x31)) {
        result = 'n';
        repeat_code = result;
    }
    if (is_key_down(0x18)) {
        result = 'o';
        repeat_code = result;
    }
    if (is_key_down(0x19)) {
        result = 'p';
        repeat_code = result;
    }
    if (is_key_down(0x10)) {
        result = 'q';
        repeat_code = result;
    }
    if (is_key_down(0x13)) {
        result = 'r';
        repeat_code = result;
    }
    if (is_key_down(0x1f)) {
        result = 's';
        repeat_code = result;
    }
    if (is_key_down(0x14)) {
        result = 't';
        repeat_code = result;
    }
    if (is_key_down(0x16)) {
        result = 'u';
        repeat_code = result;
    }
    if (is_key_down(0x2f)) {
        result = 'v';
        repeat_code = result;
    }
    if (is_key_down(0x11)) {
        result = 'w';
        repeat_code = result;
    }
    if (is_key_down(0x2d)) {
        result = 'x';
        repeat_code = result;
    }
    if (is_key_down(0x15)) {
        result = 'y';
        repeat_code = result;
    }
    if (is_key_down(0x2c)) {
        result = 'z';
        repeat_code = result;
    } else if (result == 0) {
        goto after_letters;
    }

    if (is_key_down(0x2a) || is_key_down(0x36)) {
        result -= 0x20;
        repeat_code = result;
    }

after_letters:
    if (is_key_down(0x39)) {
        result = ' ';
        repeat_code = result;
    }
    if (is_key_down(0x0b)) {
        result = '0';
        repeat_code = result;
    }
    if (is_key_down(0x02)) {
        result = '1';
        repeat_code = result;
    }
    if (is_key_down(0x03)) {
        result = '2';
        repeat_code = result;
    }
    if (is_key_down(0x04)) {
        result = '3';
        repeat_code = result;
    }
    if (is_key_down(0x05)) {
        result = '4';
        repeat_code = result;
    }
    if (is_key_down(0x06)) {
        result = '5';
        repeat_code = result;
    }
    if (is_key_down(0x07)) {
        result = '6';
        repeat_code = result;
    }
    if (is_key_down(0x08)) {
        result = '7';
        repeat_code = result;
    }
    if (is_key_down(0x09)) {
        result = '8';
        repeat_code = result;
    }
    if (is_key_down(0x0a)) {
        result = '9';
        repeat_code = result;
    }
    if (is_key_down(0x34)) {
        result = '.';
        repeat_code = result;
    }
    if (is_key_down(0x33)) {
        result = ',';
        repeat_code = result;
    }
    if (is_key_down(0x28)) {
        result = '\'';
        repeat_code = result;
    }
    if (is_key_down(0x2b)) {
        result = '\\';
        repeat_code = result;
    }
    if (is_key_down(0x0e)) {
        result = 1;
        repeat_code = result;
    }
    if (is_key_down(0xd3)) {
        result = 2;
        repeat_code = result;
    }
    if (is_key_down(0xcb)) {
        result = 3;
        repeat_code = result;
    }
    if (is_key_down(0xcd)) {
        result = 4;
        repeat_code = result;
    }
    if (is_key_down(0xc8)) {
        result = 7;
        repeat_code = result;
    }
    if (is_key_down(0xd0)) {
        result = 8;
        repeat_code = result;
    }
    if (is_key_down(0xcf)) {
        result = 9;
        repeat_code = result;
    }
    if (is_key_down(0xc7)) {
        result = 10;
        repeat_code = result;
    }
    if (is_key_down(0x01)) {
        result = 11;
        repeat_code = result;
    }
    if (is_key_down(0x3b)) {
        result = 12;
        repeat_code = result;
    }
    if (is_key_down(0x1c)) {
        int enter_code = is_key_down(0x1d) != 0;
        enter_code += 5;
        result = (char)enter_code;
        repeat_code = result;
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

    if (ascii_upper_if_lowercase(g_text_input_last_repeat_code)
        == ascii_upper_if_lowercase(repeat_code)) {
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
