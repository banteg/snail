/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_sprite_manager @ 0x44e160 */
/* selector: initialize_sprite_manager */

void __thiscall initialize_sprite_manager(_DWORD *manager)
{
  int index; // edi
  _DWORD *sprite_words; // ebp

  *(_BYTE *)manager = 0;
  *(manager + 135001) = 0;
  *(manager + 135002) = 0;
  *(manager + 135003) = 0;
  *(manager + 135004) = 0;
  index = 0;
  *(manager + 135005) = 0;
  *(manager + 135006) = manager + 1;
  do
  {
    sprite_words = manager + 45 * index;
    initialize_sprite(sprite_words + 1);
    if ( index )
    {
      if ( index == 2999 )
      {
        *(manager + 134960) = manager + 134911;
        *(manager + 134959) = 0;
      }
      else
      {
        sprite_words[5] = sprite_words - 44;
        sprite_words[4] = sprite_words + 46;
      }
    }
    else
    {
      *(manager + 5) = 0;
      *(manager + 4) = manager + 46;
    }
    ++index;
  }
  while ( index < 3000 );
}
