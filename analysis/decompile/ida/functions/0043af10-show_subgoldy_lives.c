/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: show_subgoldy_lives @ 0x43af10 */
/* selector: show_subgoldy_lives */

// Refreshes the nine-slot Goldy life display by showing the first `current_lives` widgets and hiding the rest. Windows `update_subgoldy` only calls it for gameplay mode 0, matching the mode-gated `cRSubGoldy::ShowLives()` helper in the Android and iOS ports.
void __thiscall sub_43AF10(_DWORD *this)
{
  int v2; // edi
  int i; // esi

  v2 = 0;
  for ( i = 3521432; i < 3521468; i += 4 )
  {
    if ( v2 >= *(this + 4304) )
      hide_border_init(*(_DWORD **)(*(this + 258) + i));
    else
      unhide_border_init(*(_DWORD **)(*(this + 258) + i));
    ++v2;
  }
}

