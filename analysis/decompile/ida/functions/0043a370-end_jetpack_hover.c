/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: end_jetpack_hover @ 0x43a370 */
/* selector: end_jetpack_hover */

void __thiscall end_jetpack_hover(float *gauge)
{
  if ( *((_DWORD *)gauge + 3) == 1 && *gauge < 0.94 )
    *gauge = 0.94;
}
