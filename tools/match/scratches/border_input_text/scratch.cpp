// border_input_text @ 0x4035b0 (thiscall)

#include "border_manager.h"
#include "frontend_widget.h"
#include "input_ok_state.h"

extern char* g_game_base; // data_4df904

char read_repeating_text_input_key_code();

static void remove_char_at(char* text)
{
    while (*text != 0) {
        *text = text[1];
        ++text;
    }
}

static void insert_char_at(char* text, char ch)
{
    char carry = ch;
    while (*text != 0) {
        char next = *text;
        *text = carry;
        carry = next;
        ++text;
    }
    *text = carry;
    text[1] = 0;
}

static int previous_separator(char* text, int cursor, int* column)
{
    int pos = cursor;
    int count = -1;
    while (pos > 0) {
        if (text[pos] == '>')
            break;
        --pos;
        ++count;
    }
    if (text[pos] == '>')
        --pos;
    if (column != 0)
        *column = count;
    return pos;
}

static int next_separator(char* text, int cursor, int* column)
{
    int pos = cursor;
    int count = 0;
    while (pos > 0) {
        if (text[pos] == '>')
            break;
        --pos;
        ++count;
    }
    if (text[pos] == '>') {
        ++pos;
        --count;
    }
    int scan = pos;
    while (text[scan] != 0 && text[scan] != '>')
        ++scan;
    if (column != 0)
        *column = count;
    return scan;
}

void FrontendWidget::border_input_text()
{
    char* self = (char*)this;
    char* text = self + 0x2cc;
    char key = read_repeating_text_input_key_code();

    if ((*(int*)(self + 0x70c) & 0x0c) != 0) {
        ((InputOkState*)(self + 0x2a8))->update_input_ok();
        if ((*(unsigned char*)(*(int*)(self + 0x2c8) + 0x1a0) & 0x20) != 0)
            key = 5;
    }

    if (key != 5 && ((*(unsigned int*)(self + 0x1a0) & 0x08000000) == 0)) {
        int cursor = *(int*)(self + 0x6fc);
        switch (key) {
        case 6:
            if ((*(int*)(self + 0x70c) & 1) == 0) {
                if ((*(int*)(self + 0x70c) & 2) == 0) {
                    insert_char_at(text + cursor, '>');
                    *(int*)(self + 0x6fc) = cursor + 1;
                    ++*(int*)(self + 0x710);
                }
            }
            break;
        case 3:
            if (cursor > 0) {
                char old = text[cursor];
                text[cursor] = text[cursor - 1];
                text[cursor - 1] = old;
                --*(int*)(self + 0x6fc);
            }
            break;
        case 4:
            if (cursor < *(int*)(self + 0x710)) {
                char old = text[cursor];
                text[cursor] = text[cursor + 1];
                text[cursor + 1] = old;
                ++*(int*)(self + 0x6fc);
            }
            break;
        case 7: {
            int column;
            int pos = previous_separator(text, cursor, &column);
            if (pos != 0) {
                int next_column;
                int line_start = previous_separator(text, pos, &next_column);
                if (text[line_start] == '>')
                    ++line_start;
                if (column > next_column)
                    column = next_column;
                remove_char_at(text + cursor);
                *(int*)(self + 0x6fc) = line_start + column;
                insert_char_at(text + *(int*)(self + 0x6fc), text[*(int*)(self + 0x6fc)]);
            }
            break;
        }
        case 8: {
            int column;
            int sep = next_separator(text, cursor, &column);
            if (text[sep] == '>') {
                int next_len = 0;
                while (text[sep + 1 + next_len] != 0 && text[sep + 1 + next_len] != '>')
                    ++next_len;
                if (column > next_len)
                    column = next_len;
                remove_char_at(text + cursor);
                *(int*)(self + 0x6fc) = sep + column;
                insert_char_at(text + *(int*)(self + 0x6fc), text[*(int*)(self + 0x6fc)]);
            }
            break;
        }
        case 9: {
            int sep = cursor;
            while (text[sep] != 0 && text[sep] != '>')
                ++sep;
            remove_char_at(text + cursor);
            *(int*)(self + 0x6fc) = sep - 1;
            insert_char_at(text + *(int*)(self + 0x6fc), text[*(int*)(self + 0x6fc)]);
            break;
        }
        case 10: {
            int pos = cursor;
            while (pos > 0 && text[pos] != '>')
                --pos;
            if (text[pos] == '>')
                ++pos;
            remove_char_at(text + cursor);
            *(int*)(self + 0x6fc) = pos;
            insert_char_at(text + pos, text[pos]);
            break;
        }
        case 1:
            if (cursor > 0) {
                --*(int*)(self + 0x6fc);
                remove_char_at(text + *(int*)(self + 0x6fc));
                --*(int*)(self + 0x710);
            }
            break;
        case 2:
            if (cursor < *(int*)(self + 0x710)) {
                remove_char_at(text + cursor);
                --*(int*)(self + 0x710);
            }
            break;
        case 0:
            break;
        default:
            if (*(int*)(self + 0x710) < *(int*)(self + 0x714)
                && !(key == ' ' && (*(int*)(self + 0x70c) & 1) != 0)
                && (!((*(int*)(self + 0x70c) & 2) != 0) || (key != ',' && key != '.'))) {
                insert_char_at(text + cursor, key);
                *(int*)(self + 0x6fc) = cursor + 1;
                ++*(int*)(self + 0x710);
            }
            break;
        }

        if ((*(int*)(self + 0x70c) & 2) != 0) {
            int i = 0;
            while (text[i] != 0) {
                if (text[i] != ' ' && i != *(int*)(self + 0x6fc))
                    break;
                if (i != *(int*)(self + 0x6fc)) {
                    remove_char_at(text + i);
                    if (i <= *(int*)(self + 0x6fc))
                        --*(int*)(self + 0x6fc);
                    --*(int*)(self + 0x710);
                }
                ++i;
            }
        }

        *(float*)(self + 0x704) += *(float*)(self + 0x708);
        if (*(float*)(self + 0x704) > 1.0f) {
            *(int*)(self + 0x704) = 0;
            *(int*)(self + 0x700) = (*(int*)(self + 0x700) == 0);
        }

        if (*(int*)(self + 0x700) == 1)
            text[*(int*)(self + 0x6fc)] = '|';
        else
            text[*(int*)(self + 0x6fc)] = ' ';
        layout_frontend_widget();
        return;
    }

    remove_char_at(text + *(int*)(self + 0x6fc));
    unsigned int flags = *(unsigned int*)(self + 0x1a0);
    flags &= 0xffffdfff;
    *(unsigned int*)(self + 0x1a0) = flags;
    --*(int*)(self + 0x710);
    flags |= 0x4000;
    *(unsigned int*)(self + 0x1a0) = flags;
    layout_frontend_widget();
    if ((*(int*)(self + 0x70c) & 0x0c) != 0)
        ((BorderManager*)(g_game_base + 0xb4c))
            ->kill_border((FrontendWidget*)*(void**)(self + 0x2c8));
}
