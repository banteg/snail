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

#endif
