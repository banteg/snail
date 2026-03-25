/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: register_sprite_texture @ 0x44e0f0 */
/* selector: register_sprite_texture */

int __stdcall sub_44E0F0(_BYTE *a1, int a2, int a3)
{
  _BYTE *v3; // eax
  char v4; // cl
  _DWORD *v5; // eax
  int result; // eax

  v3 = a1;
  if ( *a1 != 46 )
  {
    do
      v4 = *++v3;
    while ( v4 != 46 );
  }
  if ( a2 >= 1000 )
    report_errorf("Too many Sprite References - Increase RSPRITE_REFERENCE_MAX(%i) in RSprite.h", 1000);
  v5 = (_DWORD *)get_or_create_texture_ref(&dword_4B7790, a1, 0, a3);
  LODWORD(unk_78FF90[a2]) = v5;
  *v5 |= a3;
  result = LODWORD(unk_78FF90[a2]);
  *(_DWORD *)(result + 144) = 0;
  return result;
}

