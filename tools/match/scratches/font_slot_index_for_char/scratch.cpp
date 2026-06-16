// font_slot_index_for_char @ 0x449d20 (cdecl)

int font_slot_index_for_char(char value)
{
    if (value >= 'A' && value <= 'Z')
        return value - 0x26;
    if (value >= 'a' && value <= 'z')
        return value - 0x60;
    if (value >= '0' && value <= '9')
        return value + 6;
    if (value == ' ')
        return 0x35;
    if ((int)value == '""')
        return 0x40;

    if (value == ':') return 0x42;
    if (value == '(') return 0x43;
    if (value == ')') return 0x44;
    if (value == '!') return 0x45;
    if (value == '@') return 0x46;
    if (value == '#') return 0x47;
    if (value == '$') return 0x48;
    if (value == '%') return 0x49;
    if (value == '?') return 0x4a;
    if (value == '&') return 0x4b;
    if (value == '*') return 0x4c;
    if (value == '+') return 0x4d;
    if (value == '-') return 0x4f;
    if (value == '/') return 0x50;
    if (value == '\\') return 0x51;
    if (value == ',') return 0x52;
    if (value == '.') return 0x53;
    if (value == '\'') return 0x54;
    if (value == '|') return 0x55;
    if (value == '{') return 0x56;
    if (value == '}') return 0x57;
    if (value == '[') return 0x58;
    if (value == ']') return 0x59;
    if (value == '~') return 0x5a;
    if (value == ';') return 0x5b;
    if (value == '_') return 0x5c;
    if (value == '^') return 0x5d;

    return value == '=' ? 0x5e : 0x35;
}
