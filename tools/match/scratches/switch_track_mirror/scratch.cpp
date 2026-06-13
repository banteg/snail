// switch_track_mirror @ 0x435e60 (thiscall, ret)
// Anti-streak mirror coin: flips at random but never repeats the same
// side more than 4 times in a row.

float random_float_below(float maximum, const char* tag); // @ 0x44dc90, cdecl

class TrackMirrorState {
public:
    bool switch_track_mirror();

    char unknown_00[2];
    bool last_coin; // +0x02
    char pad_03;
    int streak;     // +0x04
};

bool TrackMirrorState::switch_track_mirror()
{
    bool coin = random_float_below(1.0f, "Mirror") > 0.5f;
    if (coin == last_coin)
        ++streak;
    else
        streak = 0;
    if (streak < 4) {
        last_coin = coin;
        return coin;
    }
    streak = 0;
    coin = !coin;
    last_coin = coin;
    return coin;
}
