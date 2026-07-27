// switch_track_mirror @ 0x435e60 (thiscall, ret)
// Anti-streak track mirror toggle: randomizes the row mirror flag, but never
// repeats the same state more than 4 times in a row.

#include "subgame_runtime.h"
#include "rmath_random.h"


void SubgameRuntime::switch_track_mirror()
{
    bool mirror_enabled = random_float_below(1.0f, "Mirror") > 0.5f;
    if (mirror_enabled == track_mirror_enabled)
        ++track_mirror_repeat_count;
    else
        track_mirror_repeat_count = 0;
    if (track_mirror_repeat_count < 4) {
        track_mirror_enabled = mirror_enabled;
        return;
    }
    track_mirror_repeat_count = 0;
    mirror_enabled = !mirror_enabled;
    track_mirror_enabled = mirror_enabled;
}
