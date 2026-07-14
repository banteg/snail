// initialize_damage_gauge @ 0x440fa0 (thiscall, ret)

#include "damage_guage.h"

void DamageGuage::initialize_damage_gauge()
{
    pulse_step = 0.020833334f;
    fill = 0.0f;
    display_fill = 0.0f;
    skin_hold_ticks = 0;
    state = DAMAGE_GUAGE_STATE_MONITORING;
    warning_transition_progress = 0.0f;
    unresolved_byte_0c = 0;
    pulse_progress = 0.0f;
    hit_flash_progress = 0.0f;
    hit_flash_step = 0.0333333351f;
}
