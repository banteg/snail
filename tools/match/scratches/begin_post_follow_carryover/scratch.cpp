// begin_post_follow_carryover @ 0x43af60 (thiscall, ret)
#include "player.h"
#include "track_attachment_types.h"

void Player::begin_post_follow_carryover()
{
    if (follow_state.active) {
        post_follow_heading_carryover = follow_state.template_record->installed_heading_bits;
        post_follow_exit_roll = follow_state.orientation_b;
    } else {
        post_follow_heading_carryover = 0;
        post_follow_exit_roll = 0;
    }
    follow_state.active = 0;
    attachment_exit_pending = 1;
    attachment_exit_anchor_z = transform.position.z;
    attachment_exit_progress = 0;
    attachment_exit_gate_a = 0;
    attachment_exit_gate_b = 0;
}
