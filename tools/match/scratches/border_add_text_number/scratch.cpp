// border_add_text_number @ 0x401030 (thiscall, ret 0x4)

#include "frontend_widget.h"

void FrontendWidget::border_add_text_number(int value)
{
    char* out = text_buffer;
    while (*out != 0)
        ++out;

    if (value == 0) {
        *out = '0';
        ++out;
        *out = (char)value;
        return;
    }

    char started;
    int divisor = 10000000;
    started = 0;
    do {
        if (started != 0 && (divisor == 100 || divisor == 100000)) {
            *out = ',';
            ++out;
        }

        if (value >= divisor || started != 0) {
            int digit;
            if (divisor == 1) {
                *out = (char)value + '0';
                ++out;
            } else {
                digit = value / divisor;
                if (digit == 0) {
                    if (started != 0) {
                        *out = '0';
                        ++out;
                    }
                } else {
                    started = 1;
                    *out = (char)digit + '0';
                    ++out;
                }
            }
        }

        value %= divisor;
        divisor /= 10;
    } while (divisor != 0);

    *out = 0;
}
