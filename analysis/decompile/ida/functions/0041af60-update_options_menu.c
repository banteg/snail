/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_options_menu @ 0x41af60 */
/* selector: update_options_menu */

// Runs the Options-screen state machine, including fullscreen toggles, slider updates, audio-volume refresh, save, and return to the owning front-end state. Cross-port Android and iOS symbols match this helper to `cROptions::AI()`.
void __usercall sub_41AF60(int a1@<ecx>, int a2@<edi>)
{
  int v3; // ecx
  int v4; // eax
  int v5; // ecx
  int v6; // eax
  int v7; // ecx
  int v8; // eax

  unk_4DF91C = *(float *)(*(_DWORD *)(a1 + 28) + 380);
  unk_4DF918 = *(float *)(*(_DWORD *)(a1 + 24) + 380);
  if ( byte_4DF920 )
    sub_44E5B0((char *)(*(_DWORD *)(a1 + 20) + 716), aFullScreenOn);
  else
    sub_44E5B0((char *)(*(_DWORD *)(a1 + 20) + 716), aFullScreenOff);
  v3 = *(_DWORD *)(a1 + 20);
  v4 = *(_DWORD *)(v3 + 416);
  if ( (v4 & 0x20) != 0 )
  {
    LOBYTE(v4) = v4 & 0xDF;
    *(_DWORD *)(v3 + 416) = v4;
    if ( byte_4DF920 )
    {
      set_fullscreen_mode(a2, 0);
      byte_4DF920 = 0;
    }
    else
    {
      set_fullscreen_mode(a2, 1);
      byte_4DF920 = 1;
    }
  }
  v5 = *(_DWORD *)(a1 + 24);
  v6 = *(_DWORD *)(v5 + 416);
  if ( (v6 & 0x20) != 0 )
  {
    LOBYTE(v6) = v6 & 0xDF;
    *(_DWORD *)(v5 + 416) = v6;
  }
  v7 = *(_DWORD *)(a1 + 16);
  v8 = *(_DWORD *)(v7 + 416);
  if ( (v8 & 0x20) != 0 )
  {
    LOBYTE(v8) = v8 & 0xDF;
    *(_DWORD *)(v7 + 416) = v8;
    destroy_options_menu((_DWORD **)a1);
    *((_BYTE *)MEMORY[0x4DF904] + 1384) = 0;
    *((_DWORD *)MEMORY[0x4DF904] + 110) = *(_DWORD *)a1;
  }
  apply_audio_config_volumes();
  if ( *(float *)(a1 + 32) != unk_4DF918 )
  {
    play_sound_effect(8);
    *(float *)(a1 + 32) = unk_4DF918;
  }
}

