// start_warning @ 0x446f30 (thiscall, tailcall)

#include "warning.h"

void cRWarning::Start()
{
    phase = 1.0f;
    state = WARNING_STATE_FADING;
    border->UnHideInit();
}
