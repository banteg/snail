// border_input_text @ 0x4035b0 (thiscall)

#include "border_manager.h"
#include "frontend_widget.h"
#include "game_root.h"
#include "input_ok_state.h"


char read_repeating_text_input_key_code();

void FrontendWidget::border_input_text()
{
    char key = read_repeating_text_input_key_code();

    if ((input_flags & 0x0c) != 0) {
        input_ok_state()->update_input_ok();
        if ((input_ok_state()->ok_widget->widget_flags
                & FRONTEND_WIDGET_FLAG_PRIMARY_ACTION_TRIGGERED)
            != 0)
            goto finish_input;
    }

    if (key == 5
        || (widget_flags & FRONTEND_WIDGET_FLAG_TEXT_INPUT_SUBMIT_REQUESTED) != 0)
        goto finish_input;

    if (key == 6 && (input_flags & 1) == 0) {
        if ((input_flags & 2) == 0) {
            text_buffer[input_cursor] = '>';
            ++input_cursor;

            char carry = ' ';
            char next = text_buffer[input_cursor];
            char* slot = &text_buffer[input_cursor];
            while (next != 0) {
                *slot = carry;
                ++slot;
                carry = next;
                next = *slot;
            }
            *slot = carry;
            slot[1] = 0;
            ++input_length;
        }
    } else if (key == 3) {
        int cursor = input_cursor;
        if (cursor > 0) {
            char old = text_buffer[cursor];
            char previous = text_buffer[cursor - 1];
            text_buffer[cursor] = previous;
            text_buffer[cursor - 1] = old;
            int updated_cursor = input_cursor - 1;
            input_cursor = updated_cursor;
        }
    } else if (key == 4) {
        int cursor = input_cursor;
        if (cursor < input_length) {
            char old = text_buffer[cursor];
            char next = text_buffer[cursor + 1];
            text_buffer[cursor] = next;
            text_buffer[cursor + 1] = old;
            int updated_cursor = input_cursor + 1;
            input_cursor = updated_cursor;
        }
    } else if (key == 7) {
        int pos = input_cursor;
        int column = -1;
        while (pos > 0) {
            if (text_buffer[pos] == '>')
                break;
            ++column;
            --pos;
        }
        if (text_buffer[pos] == '>')
            --pos;

        if (pos != 0) {
            int next_column = 0;
            while (pos > 0) {
                if (text_buffer[pos] == '>')
                    break;
                ++next_column;
                --pos;
            }
            if (text_buffer[pos] == '>')
                ++pos;
            if (column > next_column)
                column = next_column;

            char* remove = &text_buffer[input_cursor];
            while (*remove != 0) {
                *remove = remove[1];
                ++remove;
            }

            input_cursor = pos + column;
            char* insert = &text_buffer[input_cursor];
            char carry = *insert;
            do {
                char next = insert[1];
                insert[1] = carry;
                ++insert;
                carry = next;
            } while (*insert != 0);
        }
    } else if (key == 8) {
        int pos = input_cursor;
        int column = 0;
        while (pos > 0) {
            if (text_buffer[pos] == '>')
                break;
            ++column;
            --pos;
        }
        if (text_buffer[pos] == '>') {
            ++pos;
            --column;
        }

        int separator = pos;
        while (text_buffer[separator] != 0 && text_buffer[separator] != '>')
            ++separator;
        if (text_buffer[separator] == '>') {
            ++separator;
            int next_length = 0;
            while (text_buffer[separator + next_length] != 0
                && text_buffer[separator + next_length] != '>') {
                ++next_length;
            }
            if (column > next_length)
                column = next_length;

            char* remove = &text_buffer[input_cursor];
            while (*remove != 0) {
                *remove = remove[1];
                ++remove;
            }

            input_cursor = separator + column - 1;
            char* insert = &text_buffer[input_cursor];
            char carry = *insert;
            do {
                char next = insert[1];
                insert[1] = carry;
                ++insert;
                carry = next;
            } while (*insert != 0);
        }
    } else if (key == 9) {
        int separator = input_cursor;
        while (text_buffer[separator] != 0 && text_buffer[separator] != '>')
            ++separator;

        char* remove = &text_buffer[input_cursor];
        while (*remove != 0) {
            *remove = remove[1];
            ++remove;
        }

        input_cursor = separator - 1;
        char* insert = &text_buffer[input_cursor];
        char carry = *insert;
        do {
            char next = insert[1];
            insert[1] = carry;
            ++insert;
            carry = next;
        } while (*insert != 0);
    } else if (key == 10) {
        int pos = input_cursor;
        while (pos > 0 && text_buffer[pos] != '>')
            --pos;
        if (text_buffer[pos] == '>')
            ++pos;

        char* remove = &text_buffer[input_cursor];
        while (*remove != 0) {
            *remove = remove[1];
            ++remove;
        }

        input_cursor = pos;
        char* insert = &text_buffer[pos];
        char carry = *insert;
        do {
            char next = insert[1];
            insert[1] = carry;
            ++insert;
            carry = next;
        } while (*insert != 0);
    } else if (key == 1) {
        int cursor = input_cursor;
        if (cursor > 0) {
            --cursor;
            input_cursor = cursor;
            char* remove = &text_buffer[cursor];
            while (*remove != 0) {
                *remove = remove[1];
                ++remove;
            }
            --input_length;
        }
    } else if (key == 2) {
        int cursor = input_cursor;
        if (cursor < input_length) {
            char* remove = &text_buffer[cursor];
            while (*remove != 0) {
                *remove = remove[1];
                ++remove;
            }
            --input_length;
        }
    } else if (key != 0) {
        if (input_length < input_capacity
            && (key != ' ' || (input_flags & 1) == 0)
            && ((input_flags & 2) == 0 || (key != ',' && key != '.'))) {
            text_buffer[input_cursor] = key;
            ++input_cursor;

            char carry = ' ';
            char next = text_buffer[input_cursor];
            char* slot = &text_buffer[input_cursor];
            while (next != 0) {
                *slot = carry;
                ++slot;
                carry = next;
                next = *slot;
            }
            *slot = carry;
            slot[1] = 0;
            ++input_length;
        }
    }

    if ((input_flags & 2) != 0) {
        int index = 0;
        char ch = text_buffer[0];
        while (ch != 0) {
            if (text_buffer[index] != ' ' && index != input_cursor)
                break;
            if (index != input_cursor) {
                char* remove = &text_buffer[index];
                while (*remove != 0) {
                    *remove = remove[1];
                    ++remove;
                }
                if (index <= input_cursor)
                    --input_cursor;
                --input_length;
            }
            ++index;
            ch = text_buffer[index];
        }
    }

    input_cursor_blink_progress += input_cursor_blink_step;
    if (input_cursor_blink_progress > 1.0f) {
        input_cursor_blink_progress = 0.0f;
        input_cursor_visible = input_cursor_visible == 0;
    }

    if (input_cursor_visible == 1)
        text_buffer[input_cursor] = '|';
    else
        text_buffer[input_cursor] = ' ';
    layout_frontend_widget();
    return;

finish_input:
    char* remove = &text_buffer[input_cursor];
    while (*remove != 0) {
        *remove = remove[1];
        ++remove;
    }
    unsigned int cleared_flags =
        widget_flags & ~FRONTEND_WIDGET_FLAG_TEXT_INPUT_ACTIVE;
    unsigned int closing_flags =
        cleared_flags | FRONTEND_WIDGET_FLAG_TEXT_INPUT_COMPLETE;
    int remaining_length = input_length - 1;
    widget_flags = cleared_flags;
    input_length = remaining_length;
    widget_flags = closing_flags;
    layout_frontend_widget();
    if ((input_flags & 0x0c) != 0)
        g_game->border_manager
            .kill_border(input_ok_state()->ok_widget);
}
