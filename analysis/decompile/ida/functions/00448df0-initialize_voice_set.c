/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_voice_set @ 0x448df0 */
/* selector: initialize_voice_set */

int __thiscall sub_448DF0(int *this, int a2)
{
  _BYTE *v3; // eax
  _BYTE *v4; // eax
  int v5; // ecx
  int v6; // eax
  int v8; // [esp-10h] [ebp-14h]

  *this = a2;
  *(this + 1) = 0;
  v3 = allocate_tracked_memory(4 * a2, (int)aPlaylist);
  v8 = 4 * *this;
  *(this + 2) = (int)v3;
  v4 = allocate_tracked_memory(v8, (int)aVoicebite);
  v5 = *this;
  *(this + 3) = (int)v4;
  v6 = 0;
  *(this + 4) = 0;
  *(this + 5) = 998803593;
  if ( v5 > 0 )
  {
    do
    {
      *(_DWORD *)(*(this + 2) + 4 * v6) = v6;
      ++v6;
    }
    while ( v6 < *this );
  }
  return shuffle_voice_set(this);
}

