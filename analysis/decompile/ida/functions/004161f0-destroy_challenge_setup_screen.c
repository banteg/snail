/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_challenge_setup_screen @ 0x4161f0 */
/* selector: destroy_challenge_setup_screen */

// Tears down the mode-1 front-end setup screen widgets, including the optional replay control and the difficulty or speed selectors.
void __thiscall sub_4161F0(_DWORD **this)
{
  int v2; // eax
  int v3; // eax

  v2 = (*this)[16];
  if ( v2 )
  {
    v3 = v2 - 1;
    if ( v3 )
    {
      if ( v3 == 3 )
      {
        kill_border(*(this + 1));
        kill_border(*(this + 2));
        kill_border(*(this + 3));
        kill_border(*(this + 4));
        kill_border(*(this + 6));
        kill_border(*(this + 9));
      }
    }
    else
    {
      kill_border(*(this + 4));
      kill_border(*(this + 6));
      kill_border(*(this + 7));
      kill_border(*(this + 8));
      kill_border(*(this + 9));
    }
  }
  else
  {
    kill_border(*(this + 1));
    kill_border(*(this + 2));
    kill_border(*(this + 3));
    kill_border(*(this + 4));
    kill_border(*(this + 6));
  }
}

