/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_input_ok @ 0x4034d0 */
/* selector: update_input_ok */

int __thiscall sub_4034D0(float **this)
{
  int result; // eax
  int v2; // edx
  float *v3; // edx
  double v4; // st7

  result = (int)*(this + 7);
  v2 = *(_DWORD *)(result + 1804);
  if ( (v2 & 4) != 0 )
  {
    v3 = *(this + 8);
    v4 = v3[134] + *(float *)(result + 584) + *(float *)(result + 568) + *(float *)(result + 536);
  }
  else
  {
    if ( (v2 & 8) == 0 )
      return result;
    v3 = *(this + 8);
    v4 = *(float *)(result + 568) - v3[146] - *(float *)(result + 536) - (v3[134] + v3[134]);
  }
  v3[142] = v4;
  (*(this + 8))[143] = (*(this + 7))[143];
  (*(this + 8))[445] = (*(this + 8))[142];
  result = (int)*(this + 7);
  (*(this + 8))[446] = *(float *)(result + 1784);
  return result;
}

