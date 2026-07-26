/*
 * mangled: _ZN9cRTimesUp2AIEv
 * demangled: cRTimesUp::AI()
 * address: 0006f720
 * size: 116
 */

/* cRTimesUp::AI() */

void __thiscall cRTimesUp::AI(cRTimesUp *this)

{
  float fVar1;

  if (*(int *)this == 1) {
    fVar1 = *(float *)(this + 8);
    *(float *)(this + 8) = fVar1 + *(float *)(this + 0xc);
    if (1.0 < fVar1 + *(float *)(this + 0xc)) {
      *(undefined4 *)this = 2;
    }
    return;
  }
  if (*(int *)this == 2) {
    UnInit(this);
    cRSubGoldy::Kill((cRSubGoldy *)(Game + 0x81364));
    *(undefined4 *)this = 0;
    return;
  }
  return;
}
