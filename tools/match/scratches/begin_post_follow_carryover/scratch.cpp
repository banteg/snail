// begin_post_follow_carryover @ 0x43af60 (thiscall, ret)
#include "player.h"

void Player::begin_post_follow_carryover()
{
    if (follow_active) {
        post_follow_heading_carryover = attachment_record->installed_heading;
        post_follow_orientation_carryover = follow_orientation_b;
    } else {
        post_follow_heading_carryover = 0;
        post_follow_orientation_carryover = 0;
    }
    follow_active = 0;
    attachment_exit_pending = 1;
    attachment_exit_anchor_z = position.z;
    attachment_exit_progress = 0;
    attachment_exit_gate_a = 0;
    attachment_exit_gate_b = 0;
}
