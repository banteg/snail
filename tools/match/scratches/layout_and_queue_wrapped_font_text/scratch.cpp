// FontType @ 0x44abe0 (cdecl)

#include "font_system.h"

void FontType(
    char* text,
    int font_id,
    float text_scale,
    float x,
    float y,
    float* out_x,
    float* out_y,
    float* out_width,
    float* out_height,
    float text_wave_amplitude,
    char shadow_enabled,
    int horizontal_align,
    float anchor_x,
    int flags,
    tColour* color_arg,
    char measure_only,
    char pulse_alpha)
{
    tColour color;
    color.noop_this_constructor();
    color = *color_arg;

    float max_right = x;
    float cursor_y = y;
    char* source = text;
    char line[0x400];

    char ch;
    char* out = line;
    do {
        ch = *source;
        if (ch == '>' || ch == 0) {
            *out = 0;

            if (out != line) {
                float width = FontGetStringX(line, font_id, text_scale);
                float right = width + x;
                if (right > max_right)
                    max_right = right;

                if (measure_only == 0) {
                    if (pulse_alpha != 0)
                        color.a = Sin(cursor_y * 0.00654498488f);
                    FontPrint(
                        line,
                        font_id,
                        text_scale,
                        x,
                        cursor_y,
                        horizontal_align,
                        anchor_x,
                        flags,
                        &color,
                        text_wave_amplitude,
                        shadow_enabled);
                }
            }

            float line_height = g_font_sheets[font_id].height_scale;
            line_height *= g_font_sheets[font_id].spacing_scale;
            line_height *= g_font_sheets[font_id].line_marker_y;
            cursor_y = line_height * text_scale + cursor_y;
            out = line;
        } else {
            *out = ch;
            ++out;
        }
        ++source;
    } while (ch != 0);

    *out_x = x;
    *out_y = y;
    *out_width = max_right - x;
    *out_height = cursor_y - y;

    if (horizontal_align == 1) {
        *out_x = anchor_x + 320.0f;
        return;
    }
    if (horizontal_align == 3) {
        *out_x = anchor_x + 320.0f - *out_width;
        return;
    }
    if (horizontal_align == 2) {
        *out_x = anchor_x + 320.0f - *out_width * 0.5f;
        return;
    }
}
