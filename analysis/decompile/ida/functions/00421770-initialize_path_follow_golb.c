/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_path_follow_golb @ 0x421770 */
/* selector: initialize_path_follow_golb */

int __thiscall sub_421770(float *this, int a2, int a3, int a4)
{
  int v4; // edx
  double v5; // st7

  *(_BYTE *)this = 1;
  v4 = *(_DWORD *)(a2 + 56);
  *((_DWORD *)this + 2) = a2;
  *((_DWORD *)this + 1) = v4;
  *(this + 3) = 0.0;
  v5 = *(float *)(a3 + 8) - *(float *)(a2 + 24);
  *((_DWORD *)this + 9) = a4;
  *(this + 4) = v5;
  *(this + 5) = *(float *)(a3 + 4) - 0.49000001;
  return a4;
}

