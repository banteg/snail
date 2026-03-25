/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: border_sprite_extend @ 0x404540 */
/* selector: border_sprite_extend */

int __thiscall sub_404540(int this, int a2, int a3, int a4, char a5)
{
  *(_DWORD *)(this + 96) = a2;
  *(_DWORD *)(this + 100) = a4;
  *(_DWORD *)(this + 104) = a3;
  *(_BYTE *)(this + 92) = 1;
  *(_BYTE *)(this + 93) = a5;
  *(_DWORD *)(this + 540) = 0;
  *(_DWORD *)(this + 532) = 0;
  *(_DWORD *)(this + 536) = 0;
  return 0;
}

