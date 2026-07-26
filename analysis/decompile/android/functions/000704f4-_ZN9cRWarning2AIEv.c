/*
 * mangled: _ZN9cRWarning2AIEv
 * demangled: cRWarning::AI()
 * address: 000704f4
 * size: 280
 */

/* cRWarning::AI() */

void __thiscall cRWarning::AI(cRWarning *this)

{
  bool bVar1;
  int iVar2;
  float fVar3;
  float fVar4;

  if (*(char *)(Game + 0x718b9) != '\0') {
    return;
  }
  iVar2 = *(int *)this;
  if (iVar2 == 1) {
    *(undefined4 *)(*(int *)(this + 0x14) + 0x1fc) = 0x3f7fbe77;
    fVar3 = *(float *)(this + 4);
    *(float *)(this + 4) = fVar3 + *(float *)(this + 8);
    if (1.0 < fVar3 + *(float *)(this + 8)) {
      *(undefined4 *)(this + 4) = 0;
      *(undefined4 *)this = 2;
    }
  }
  else if (iVar2 == 2) {
    fVar3 = *(float *)(this + 4);
    fVar4 = 0.5;
    bVar1 = fVar3 < 0.5;
    if (bVar1) {
      fVar4 = fVar3 * -2.0 + 1.0;
      iVar2 = *(int *)(this + 0x14);
    }
    else {
      fVar3 = 0.0;
      iVar2 = *(int *)(this + 0x14);
    }
    if (bVar1) {
      *(float *)(iVar2 + 0x1fc) = fVar4;
    }
    else {
      *(float *)(iVar2 + 0x1fc) = fVar3;
    }
    fVar3 = *(float *)(this + 4);
    *(float *)(this + 4) = fVar3 + *(float *)(this + 8);
    if (1.0 < fVar3 + *(float *)(this + 8)) {
      *(undefined4 *)(this + 4) = 0;
      *(undefined4 *)this = 1;
    }
  }
  else if (iVar2 == 0) {
    return;
  }
  fVar3 = *(float *)(this + 0xc);
  *(float *)(this + 0xc) = fVar3 + *(float *)(this + 0x10);
  if (fVar3 + *(float *)(this + 0x10) < 1.0) {
    return;
  }
  *(undefined4 *)(this + 0xc) = 0;
  cRSound::Play((int)&gRSound);
  return;
}
