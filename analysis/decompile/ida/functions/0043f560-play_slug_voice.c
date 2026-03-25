/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_slug_voice @ 0x43f560 */
/* selector: play_slug_voice */

void __thiscall sub_43F560(int this, int a2)
{
  if ( !*(_BYTE *)(this + 216) && !*((_BYTE *)MEMORY[0x4DF904] + 3998100) )
  {
    *((_DWORD *)MEMORY[0x4DF904] + 999526) = *((_DWORD *)MEMORY[0x4DF904] + 999527);
    *((_BYTE *)MEMORY[0x4DF904] + 3998100) = 1;
    *(_BYTE *)(this + 216) = 1;
    *(_DWORD *)(this + 220) = 0;
    play_voice_backend(a2, 1.0, -1.0, 0.0);
  }
}

