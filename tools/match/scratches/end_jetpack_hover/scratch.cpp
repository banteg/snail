// end_jetpack_hover @ 0x43a370 (thiscall, ret)

#include "jetpack_gauge.h"

void JetpackGaugeController::end_jetpack_hover()
{
    if (state == 1 && progress < 0.94f) {
        progress = 0.94f;
    }
}
