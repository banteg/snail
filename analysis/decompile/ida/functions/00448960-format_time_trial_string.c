/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: format_time_trial_string @ 0x448960 */
/* selector: format_time_trial_string */

char *__stdcall sub_448960(int a1)
{
  if ( *(float *)a1 == 0.0 )
  {
    sprintf(MEMORY[0x751478], asc_4AC5BC);
  }
  else
  {
    sprintf(MEMORY[0x751478], "%1i:%02i:%03i", *(_DWORD *)(a1 + 4), *(_DWORD *)(a1 + 8), *(_DWORD *)(a1 + 16));
    sprintf(MEMORY[0x751478], "%1i:%02i:%02i", *(_DWORD *)(a1 + 4), *(_DWORD *)(a1 + 8), *(_DWORD *)(a1 + 12));
  }
  return MEMORY[0x751478];
}

