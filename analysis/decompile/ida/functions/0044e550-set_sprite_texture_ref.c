/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_sprite_texture_ref @ 0x44e550 */
/* selector: set_sprite_texture_ref */

int __thiscall sub_44E550(_DWORD *this, int a2, int a3)
{
  int result; // eax

  result = LODWORD(unk_78FF90[a2]) + 164 * a3;
  *(this + 7) = result;
  return result;
}

