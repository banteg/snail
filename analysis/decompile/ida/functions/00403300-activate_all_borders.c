/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: activate_all_borders @ 0x403300 */
/* selector: activate_all_borders */

void __thiscall activate_all_borders(BorderManager *manager)
{
  int32_t *p_flags; // eax
  int v2; // edx
  int v3; // ecx
  int32_t v4; // ecx

  p_flags = &manager->borders[0].flags;
  v2 = 150;
  do
  {
    v3 = *p_flags;
    if ( *p_flags >= 0 )
    {
      BYTE1(v3) &= ~0x80u;
      *p_flags = v3;
    }
    v4 = *p_flags;
    p_flags += 457;
    --v2;
    *(p_flags - 457) = v4 & 0x7FFFFFFF;
    *(p_flags - 426) = *(p_flags - 428);
    *(p_flags - 425) = *(p_flags - 428);
    *(p_flags - 430) = 0;
  }
  while ( v2 );
}
