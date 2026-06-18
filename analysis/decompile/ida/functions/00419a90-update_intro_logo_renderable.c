/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_intro_logo_renderable @ 0x419a90 */
/* selector: update_intro_logo_renderable */

// Advances one intro/credits or logo renderable by applying its velocity to the shared BOD position, fades alpha as it passes the z-window, marks the backing object dirty, and toggles the visible bit. The old `update_logo_row` name was too narrow: `initialize_intro_screen` uses the same 0x90-byte bank for intro text and image renderables, while `open_logo` uses the 32-slot logo bank.
char __thiscall update_intro_logo_renderable(int this)
{
  int v1; // eax

  *(float *)(this + 104) = *(float *)(this + 128) + *(float *)(this + 104);
  *(float *)(this + 108) = *(float *)(this + 132) + *(float *)(this + 108);
  *(float *)(this + 112) = *(float *)(this + 136) + *(float *)(this + 112);
  if ( *(float *)(this + 112) <= 8.0 )
    *(_DWORD *)(this + 52) = 1065336439;
  else
    *(float *)(this + 52) = (1.0 - (*(float *)(this + 112) - 8.0) * 0.125) * 0.99900001;
  *(_DWORD *)(*(_DWORD *)(this + 36) + 16) |= 0x10u;
  if ( *(float *)(this + 112) > 16.0 || *(float *)(this + 112) < -4.0 )
  {
    v1 = *(_DWORD *)(this + 4);
    LOBYTE(v1) = v1 & 0xDF;
    *(_DWORD *)(this + 4) = v1;
  }
  else
  {
    v1 = *(_DWORD *)(this + 4);
    LOBYTE(v1) = v1 | 0x20;
    *(_DWORD *)(this + 4) = v1;
  }
  return v1;
}

