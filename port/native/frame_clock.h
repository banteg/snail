#ifndef SNAIL_NATIVE_FRAME_CLOCK_H
#define SNAIL_NATIVE_FRAME_CLOCK_H

#include <stdint.h>

struct FrameClock {
    uint64_t last;

    float elapsed_seconds(uint64_t now)
    {
        // Keep SDL's nanosecond clock at full precision until after subtraction.
        uint64_t elapsed = now - last;
        last = now;
        return elapsed >= 1000000000 ? 1.0f : (float)elapsed / 1e9f;
    }
};

#endif
