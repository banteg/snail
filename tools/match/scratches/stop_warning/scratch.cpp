// stop_warning @ 0x446f50 (thiscall, tailcall)

#include "warning.h"

void Warning::stop_warning()
{
    state = 0;
    border->hide_border_init();
}
