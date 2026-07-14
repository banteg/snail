// SubgameRuntime::calc_slider_to_rate @ 0x437e80

#include "subgame_runtime.h"

float SubgameRuntime::calc_slider_to_rate(float slider)
{
    if (slider == 1.0f) {
        return 1.1f;
    }
    return slider * 0.90000004f + 0.2f;
}
