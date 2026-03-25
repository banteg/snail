/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_subgoldy_resurrect @ 0x441fd0 */
/* selector: update_subgoldy_resurrect */

// Advances Goldy's resurrect or death-resolution state machine after `initialize_subgoldy_death`: starts the fade, decrements the visible life stock on the respawn branch, and only falls through to `complete_subgame` when the final-loss path wins. Cross-port Android and iOS symbols match this helper to `cRSubGoldy::RessurectAI()`.
void __thiscall sub_441FD0(int this)
{
  double v2; // st7
  int v3; // eax

  *(_DWORD *)(this + 1048) = 0;
  if ( !*((_DWORD *)MEMORY[0x4DF904] + 9) )
  {
    v2 = *(float *)(this + 144) + *(float *)(this + 140);
    *(float *)(this + 140) = v2;
    if ( v2 > 1.0 && !*((_DWORD *)MEMORY[0x4DF904] + 9) )
      begin_frontend_fade_out((_DWORD *)MEMORY[0x4DF904] + 9, 0);
  }
  if ( *(float *)(this + 140) > 1.0 && *((_DWORD *)MEMORY[0x4DF904] + 9) == 4 )
  {
    v3 = *(_DWORD *)(this + 1032);
    if ( *(_DWORD *)(this + 128) )
    {
      *(_DWORD *)(v3 + 19337160) = 2;
      complete_subgame(*(_DWORD *)(this + 1032), 1);
      if ( *(_BYTE *)(*(_DWORD *)(this + 1032) + 16721361) )
      {
        *((_DWORD *)MEMORY[0x4DF904] + 111) = *((_DWORD *)MEMORY[0x4DF904] + 110);
        *((_DWORD *)MEMORY[0x4DF904] + 110) = 26;
      }
      else
      {
        *((_DWORD *)MEMORY[0x4DF904] + 111) = *((_DWORD *)MEMORY[0x4DF904] + 110);
        if ( *(_DWORD *)(*(_DWORD *)(this + 1032) + 64) || *((_BYTE *)MEMORY[0x4DF904] + 781) )
        {
          *((_DWORD *)MEMORY[0x4DF904] + 110) = 27;
        }
        else
        {
          *((_DWORD *)MEMORY[0x4DF904] + 110) = 26;
          *((_DWORD *)MEMORY[0x4DF904] + 111) = 2;
        }
      }
    }
    else
    {
      if ( !*(_DWORD *)(v3 + 64) )
        --*(_DWORD *)(this + 17216);
      *((_DWORD *)MEMORY[0x4DF904] + 111) = *((_DWORD *)MEMORY[0x4DF904] + 110);
      *((_DWORD *)MEMORY[0x4DF904] + 110) = 28;
    }
  }
}

