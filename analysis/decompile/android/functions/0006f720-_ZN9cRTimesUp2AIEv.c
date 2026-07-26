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
  int iVar2;
  float fVar3;

  fVar1 = DAT_0006f794;
  iVar2 = DAT_0006f798 + 0x6f73c;
  if (*(int *)this == 1) {
    fVar3 = *(float *)(this + 8);
    *(float *)(this + 8) = fVar3 + *(float *)(this + 0xc);
    if (fVar1 < fVar3 + *(float *)(this + 0xc)) {
      *(undefined4 *)this = 2;
    }
    return;
  }
  if (*(int *)this == 2) {
    UnInit(this);
    cRSubGoldy::Kill((cRSubGoldy *)(**(int **)(iVar2 + DAT_0006f79c) + 0x81364));
    *(undefined4 *)this = 0;
    return;
  }
  return;
}
