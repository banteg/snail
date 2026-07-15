/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: allocate_border @ 0x4032a0 */
/* selector: allocate_border */

FrontendWidget *__thiscall allocate_border(BorderManager *manager)
{
  int v1; // eax
  int32_t *i; // edx
  FrontendWidget *result; // eax

  v1 = 0;
  for ( i = &manager->borders[0].flags; *i; i += 457 )
  {
    if ( ++v1 >= 150 )
    {
      report_errorf(aRunOutOfBorder);
      return nullptr;
    }
  }
  result = (FrontendWidget *)&manager->borders[v1];
  *(_DWORD *)&result->_pad_198[4] = g_game_base->frame_counter;
  return result;
}
