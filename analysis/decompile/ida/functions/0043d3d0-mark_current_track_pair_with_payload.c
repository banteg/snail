/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: mark_current_track_pair_with_payload @ 0x43d3d0 */
/* selector: mark_current_track_pair_with_payload */

// Sets flag 0x40 on the two ghost sprites at +0x98/+0x9c and writes the supplied scalar payload bits into Sprite::position.z (+0x50).
int __thiscall sub_43D3D0(_DWORD *this, int payload_bits)
{
  int result; // eax

  *(_DWORD *)(*(this + 38) + 4) |= 0x40u;
  *(_DWORD *)(*(this + 39) + 4) |= 0x40u;
  *(_DWORD *)(*(this + 38) + 80) = payload_bits;
  result = *(this + 39);
  *(_DWORD *)(result + 80) = payload_bits;
  return result;
}
