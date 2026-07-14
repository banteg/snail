// Attachment-follow runtime structures, partial.
// Offsets per analysis/decompile/*/00420c40-*.c, 0042c770-*.c, 00420cb0-*.c.
// UNIFIED (2026-06-12): the "FollowState global at game+0x430100" is the
// Player's embedded 0x40-byte follow sub-struct at player+0x384 (player block
// at game+0x42fd7c; 0x42fd7c + 0x384 = 0x430100). Accesses that used to be
// spelled as FollowState +0x8c/+0x90/+0x94/+0x99 are adjacent Player fields:
// velocity.x/y/z (+0x410/+0x414/+0x418), attachment_exit_pending (+0x41d).
#ifndef TRACK_ATTACHMENT_H
#define TRACK_ATTACHMENT_H

#include "track_attachment_types.h"

// data_4df904 is the relocatable game-allocation base; structures below live at
// fixed VA offsets added to it. Scratches use an ordinary singleton pointer;
// repeated native reloads remain visible scheduling debt rather than being
// reproduced with a volatile compiler barrier.
// Field-first view of SubgameRuntime::runtime_rows[0].installed_heading_delta;
// successive fields are one 0xf4-byte SubRow apart.
extern char g_runtime_row_installed_heading_fields[]; // 0x64118c
extern char g_follow_state_block[]; // 0x430100 = g_player_block + 0x384, size 0x40
extern char g_player_block[];       // 0x42fd7c
extern char g_player_position_offset[]; // 0x42fde4 = g_player_block + 0x68
extern char g_player_velocity_offset[]; // 0x43018c = g_player_block + 0x410
extern char g_player_attachment_exit_pending_offset[]; // 0x430199 = g_player_block + 0x41d
extern char g_player_squidge_offset[]; // 0x4340c0 = g_player_block + 0x4344

#endif
