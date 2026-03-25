/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_subgoldy_fall_state @ 0x43af60 */
/* selector: initialize_subgoldy_fall_state */

// Seeds Goldy's post-follow fall state. If the active follow byte is still set, it copies the current attachment payload and cached carryover scalar into the post-follow slots at `+0x430` and `+0x42c`, clears `+0x384`, sets `+0x41d`, latches player z into `attachment_exit_anchor_z` at `+0x424`, and zeroes the exit-progress and gate bytes. Windows `cdb` confirmed this helper can also run after the active follow byte has already been cleared, so it is one real exit lane but not the only attachment-retirement path.
int __thiscall sub_43AF60(int this)
{
  int result; // eax
  int v2; // edx

  result = 0;
  if ( *(_BYTE *)(this + 900) )
  {
    *(_DWORD *)(this + 1072) = *(_DWORD *)(*(_DWORD *)(this + 904) + 152);
    *(_DWORD *)(this + 1068) = *(_DWORD *)(this + 928);
  }
  else
  {
    *(_DWORD *)(this + 1072) = 0;
    *(_DWORD *)(this + 1068) = 0;
  }
  v2 = *(_DWORD *)(this + 112);
  *(_BYTE *)(this + 900) = 0;
  *(_BYTE *)(this + 1053) = 1;
  *(_DWORD *)(this + 1060) = v2;
  *(_DWORD *)(this + 1076) = 0;
  *(_BYTE *)(this + 1100) = 0;
  *(_BYTE *)(this + 1101) = 0;
  return result;
}

