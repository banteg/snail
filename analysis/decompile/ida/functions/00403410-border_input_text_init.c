/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: border_input_text_init @ 0x403410 */
/* selector: border_input_text_init */

float *__thiscall border_input_text_init(int this, int a2, char *ArgList, int a4)
{
  _BYTE *v5; // eax
  float *result; // eax

  *(_DWORD *)(this + 1804) = a4;
  rstrcpy_checked_ascii((char *)(this + 1740), ArgList);
  v5 = (_BYTE *)(this + 716);
  *(_DWORD *)(this + 1788) = 0;
  for ( *(_DWORD *)(this + 1808) = 0; *v5; ++*(_DWORD *)(this + 1788) )
  {
    ++v5;
    ++*(_DWORD *)(this + 1808);
  }
  *(_BYTE *)(*(_DWORD *)(this + 1788) + this + 716) = 124;
  *(_BYTE *)(*(_DWORD *)(this + 1788) + this + 717) = 0;
  *(_DWORD *)(this + 1796) = 0;
  *(_DWORD *)(this + 1792) = 1;
  *(_DWORD *)(this + 1812) = a2;
  *(_DWORD *)(this + 1800) = 1034594987;
  result = (float *)layout_frontend_widget((FrontendWidget *)this);
  if ( (a4 & 0xC) != 0 )
    return (float *)initialize_input_ok(this + 680);
  return result;
}

