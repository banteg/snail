// normalize_segment_glyph_for_track_flags @ 0x437270 (thiscall, ret 0xc)

class Game {
public:
    char normalize_segment_glyph_for_track_flags(char glyph, int row, char edge_row);

    char unknown_00[0x02];
    unsigned char track_mirror_enabled; // +0x02
    char unknown_03[0x4c - 0x03];
    unsigned int runtime_flags; // +0x4c
    char unknown_50[0x58 - 0x50];
    int completion_row_start; // +0x58
};

char Game::normalize_segment_glyph_for_track_flags(char glyph, int row, char edge_row)
{
    if (row > completion_row_start)
        return glyph;

    switch (glyph) {
    case ' ': {
        unsigned int flags = runtime_flags;
        if ((flags & 0x400) == 0)
            return ',';
        if ((flags & 1) == 0)
            return '.';
        return glyph;
    }

    case '<':
    case '>':
        if ((runtime_flags & 0x200) == 0)
            return '.';
        return glyph;

    case '}': {
        unsigned int flags = runtime_flags;
        if ((flags & 0x200) == 0)
            return '.';
        if ((flags & 0x20) == 0)
            return '>';
        if (track_mirror_enabled != 0)
            return '{';
        return glyph;
    }

    case '{': {
        unsigned int flags = runtime_flags;
        if ((flags & 0x200) == 0)
            return '.';
        if ((flags & 0x20) == 0)
            return '>';
        if (track_mirror_enabled != 0)
            return '}';
        return glyph;
    }

    case ']': {
        unsigned int flags = runtime_flags;
        if ((flags & 0x200) == 0)
            return '.';
        if ((flags & 0x20) == 0)
            return '<';
        if (track_mirror_enabled != 0)
            return '{';
        return glyph;
    }

    case '[': {
        unsigned int flags = runtime_flags;
        if ((flags & 0x200) == 0)
            return '.';
        if ((flags & 0x20) == 0)
            return '<';
        if (track_mirror_enabled != 0)
            return '[';
        return glyph;
    }

    case '_':
        if ((runtime_flags & 0x40) == 0 && edge_row == 0)
            return '.';
        return glyph;

    case '=': {
        unsigned int flags = runtime_flags;
        if ((flags & 0x100) == 0) {
            if ((flags & 1) == 0)
                return '.';
            return (flags & 0x400) != 0 ? ' ' : ',';
        }
        return glyph;
    }

    case '|': {
        unsigned int flags = runtime_flags;
        if ((flags & 0x100) == 0) {
            if ((flags & 1) == 0)
                return ' ';
            return (flags & 0x400) != 0 ? '=' : ',';
        }
        return glyph;
    }

    case 'o': {
        unsigned int flags = runtime_flags;
        if ((flags & 4) == 0)
            return (flags & 0x40) != 0 ? '_' : '.';
        return glyph;
    }

    case '-':
        if ((runtime_flags & 0x4000) == 0)
            return '.';
        return glyph;

    case '$': {
        unsigned int flags = runtime_flags;
        if ((flags & 0x800) == 0)
            return (flags & 0x40) != 0 ? '_' : '.';
        return glyph;
    }
    }

    return glyph;
}
