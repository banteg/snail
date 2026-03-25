/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_sprite_manager @ 0x44e160 */
/* selector: initialize_sprite_manager */

int __thiscall sub_44E160(_DWORD *this)
{
  int v2; // edi
  _DWORD *v3; // ebp
  int result; // eax

  *(_BYTE *)this = 0;
  *(this + 135001) = 0;
  *(this + 135002) = 0;
  *(this + 135003) = 0;
  *(this + 135004) = 0;
  v2 = 0;
  *(this + 135005) = 0;
  *(this + 135006) = this + 1;
  do
  {
    v3 = this + 45 * v2;
    result = initialize_sprite(v3 + 1);
    if ( v2 )
    {
      if ( v2 == 2999 )
      {
        *(this + 134960) = this + 134911;
        *(this + 134959) = 0;
      }
      else
      {
        result = (int)(v3 + 46);
        v3[5] = v3 - 44;
        v3[4] = v3 + 46;
      }
    }
    else
    {
      result = (int)(this + 46);
      *(this + 5) = 0;
      *(this + 4) = this + 46;
    }
    ++v2;
  }
  while ( v2 < 3000 );
  return result;
}

