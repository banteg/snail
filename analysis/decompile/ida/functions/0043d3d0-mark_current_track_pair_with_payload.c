/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: mark_current_track_pair_with_payload @ 0x43d3d0 */
/* selector: mark_current_track_pair_with_payload */

// Sets flag 0x40 on the two ghost sprites at +0x98/+0x9c and writes the supplied scalar payload bits into Sprite::position.z (+0x50).
Sprite *__thiscall mark_current_track_pair_with_payload(Player *player, float payload)
{
  Sprite *result; // eax
  int payload_bits; // edx

  payload_bits = *(_DWORD *)&payload;
  player->ghost_sprite_a->flags |= 0x40u;
  player->ghost_sprite_b->flags |= 0x40u;
  *(_DWORD *)&player->ghost_sprite_a->position.z = payload_bits;
  result = player->ghost_sprite_b;
  *(_DWORD *)&result->position.z = payload_bits;
  return result;
}
