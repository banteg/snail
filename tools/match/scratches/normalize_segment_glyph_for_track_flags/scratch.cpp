// normalize_segment_glyph_for_track_flags @ 0x437270 (thiscall, ret 0xc)

#include "subgame_runtime.h"

char SubgameRuntime::normalize_segment_glyph_for_track_flags(char glyph, int row, char edge_row)
{
    if (row > completion_row_start)
        return glyph;

    switch (glyph) {
    case ' ': {
        unsigned int flags = runtime_flags;
        if ((flags & SUBGAME_RUNTIME_FLAG_ALLOW_FALLING) == 0)
            return ',';
        if ((flags & SUBGAME_RUNTIME_FLAG_PRESERVE_SPACE_GLYPH) == 0)
            return '.';
        return glyph;
    }

    case '<':
    case '>':
        if ((runtime_flags & SUBGAME_RUNTIME_FLAG_PRESERVE_RAMP_GLYPHS) == 0)
            return '.';
        return glyph;

    case '}': {
        unsigned int flags = runtime_flags;
        if ((flags & SUBGAME_RUNTIME_FLAG_PRESERVE_RAMP_GLYPHS) == 0)
            return '.';
        if ((flags & SUBGAME_RUNTIME_FLAG_PRESERVE_BRACE_ORIENTATION) == 0)
            return '>';
        if (track_mirror_enabled != 0)
            return '{';
        return glyph;
    }

    case '{': {
        unsigned int flags = runtime_flags;
        if ((flags & SUBGAME_RUNTIME_FLAG_PRESERVE_RAMP_GLYPHS) == 0)
            return '.';
        if ((flags & SUBGAME_RUNTIME_FLAG_PRESERVE_BRACE_ORIENTATION) == 0)
            return '>';
        if (track_mirror_enabled != 0)
            return '}';
        return glyph;
    }

    case ']': {
        unsigned int flags = runtime_flags;
        if ((flags & SUBGAME_RUNTIME_FLAG_PRESERVE_RAMP_GLYPHS) == 0)
            return '.';
        if ((flags & SUBGAME_RUNTIME_FLAG_PRESERVE_BRACE_ORIENTATION) == 0)
            return '<';
        if (track_mirror_enabled != 0)
            return '{';
        return glyph;
    }

    case '[': {
        unsigned int flags = runtime_flags;
        if ((flags & SUBGAME_RUNTIME_FLAG_PRESERVE_RAMP_GLYPHS) == 0)
            return '.';
        if ((flags & SUBGAME_RUNTIME_FLAG_PRESERVE_BRACE_ORIENTATION) == 0)
            return '<';
        if (track_mirror_enabled != 0)
            return '[';
        return glyph;
    }

    case '_':
        if ((runtime_flags & SUBGAME_RUNTIME_FLAG_PRESERVE_UNDERSCORE_GLYPH) == 0
            && edge_row == 0)
            return '.';
        return glyph;

    case '=': {
        unsigned int flags = runtime_flags;
        if ((flags & SUBGAME_RUNTIME_FLAG_PRESERVE_EQUALS_BAR_GLYPHS) == 0) {
            if ((flags & SUBGAME_RUNTIME_FLAG_PRESERVE_SPACE_GLYPH) == 0)
                return '.';
            return (flags & SUBGAME_RUNTIME_FLAG_ALLOW_FALLING) != 0 ? ' ' : ',';
        }
        return glyph;
    }

    case '|': {
        unsigned int flags = runtime_flags;
        if ((flags & SUBGAME_RUNTIME_FLAG_PRESERVE_EQUALS_BAR_GLYPHS) == 0) {
            if ((flags & SUBGAME_RUNTIME_FLAG_PRESERVE_SPACE_GLYPH) == 0)
                return ' ';
            return (flags & SUBGAME_RUNTIME_FLAG_ALLOW_FALLING) != 0 ? '=' : ',';
        }
        return glyph;
    }

    case 'o': {
        unsigned int flags = runtime_flags;
        if ((flags & SUBGAME_RUNTIME_FLAG_PRESERVE_O_GLYPH) == 0)
            return (flags & SUBGAME_RUNTIME_FLAG_PRESERVE_UNDERSCORE_GLYPH) != 0
                ? '_'
                : '.';
        return glyph;
    }

    case '-':
        if ((runtime_flags & SUBGAME_RUNTIME_FLAG_PRESERVE_DASH_GLYPH) == 0)
            return '.';
        return glyph;

    case '$': {
        unsigned int flags = runtime_flags;
        if ((flags & SUBGAME_RUNTIME_FLAG_HEALTH_PICKUPS) == 0)
            return (flags & SUBGAME_RUNTIME_FLAG_PRESERVE_UNDERSCORE_GLYPH) != 0
                ? '_'
                : '.';
        return glyph;
    }
    }

    return glyph;
}
