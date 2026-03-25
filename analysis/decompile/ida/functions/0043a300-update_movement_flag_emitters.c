/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_movement_flag_emitters @ 0x43a300 */
/* selector: update_movement_flag_emitters */

// Iterates the 12 Golb emitter slots at player+0x450 and seeds one, two, or three live shot actors based on the current movement_flags family.
int __thiscall sub_43A300(char *this, int a2)
{
  int result; // eax
  int v4; // ebx
  int v5; // esi
  char *v6; // edi

  result = *(_DWORD *)(a2 + 824);
  if ( (result & 0x69) != 0 )
  {
    v4 = 1;
  }
  else if ( (result & 0x12) != 0 )
  {
    v4 = 2;
  }
  else
  {
    if ( (result & 4) == 0 )
      return result;
    v4 = 3;
  }
  v5 = 0;
  v6 = this + 1104;
  do
  {
    result = *((_DWORD *)v6 + 145);
    if ( !result )
    {
      result = create_golb(v6, (int)this, v4--, v5);
      if ( !v4 )
        break;
    }
    ++v5;
    v6 += 744;
  }
  while ( v5 < 12 );
  return result;
}

