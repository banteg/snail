// start_warning @ 0x446f30 (thiscall, tailcall)

#include "warning.h"

void Warning::start_warning()
{
    phase = 1.0f;
    state = 2;
    border->unhide_border_init();
}
