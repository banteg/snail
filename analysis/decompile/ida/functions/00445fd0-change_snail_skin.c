/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: change_snail_skin @ 0x445fd0 */
/* selector: change_snail_skin */

void __thiscall sub_445FD0(float *this, int a2, float a3)
{
  *((_DWORD *)this + 5) = 1;
  *(this + 6) = 0.0;
  if ( a3 == 0.0 )
  {
    *(this + 7) = 0.0;
    *(_DWORD *)this = a2;
  }
  else
  {
    *(_DWORD *)this = a2;
    *(this + 7) = 1.0 / (a3 * 60.0);
  }
}

