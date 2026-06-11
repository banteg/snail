// begin_post_follow_carryover @ 0x43af60 (thiscall, ret)
#include "player.h"

void Player::begin_post_follow_carryover()
{
    if (follow_active) {
        post_follow_value_a = attachment_record->installed_heading;
        post_follow_value_b = follow_orientation_b;
    } else {
        post_follow_value_a = 0;
        post_follow_value_b = 0;
    }
    follow_active = 0;
    attachment_exit_pending = 1;
    attachment_exit_anchor_z = position_z;
    attachment_exit_progress = 0;
    attachment_exit_gate_a = 0;
    attachment_exit_gate_b = 0;
}
