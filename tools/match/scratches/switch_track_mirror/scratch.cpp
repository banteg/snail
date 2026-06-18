// switch_track_mirror @ 0x435e60 (thiscall, ret)
// Anti-streak track mirror toggle: randomizes the row mirror flag, but never
// repeats the same state more than 4 times in a row.

float random_float_below(float maximum, const char* tag); // @ 0x44dc90, cdecl

class Game {
public:
    bool switch_track_mirror();

    char unknown_00[2];
    bool track_mirror_enabled; // +0x02
    char pad_03;
    int track_mirror_repeat_count; // +0x04
};

bool Game::switch_track_mirror()
{
    bool mirror_enabled = random_float_below(1.0f, "Mirror") > 0.5f;
    if (mirror_enabled == track_mirror_enabled)
        ++track_mirror_repeat_count;
    else
        track_mirror_repeat_count = 0;
    if (track_mirror_repeat_count < 4) {
        track_mirror_enabled = mirror_enabled;
        return mirror_enabled;
    }
    track_mirror_repeat_count = 0;
    mirror_enabled = !mirror_enabled;
    track_mirror_enabled = mirror_enabled;
    return mirror_enabled;
}
