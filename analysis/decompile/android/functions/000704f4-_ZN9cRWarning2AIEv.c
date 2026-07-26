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
  float fVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  float fVar6;

  iVar4 = DAT_00070620 + 0x7050c;
  if (*(char *)(**(int **)(iVar4 + DAT_00070624) + 0x718b9) != '\0') {
    return;
  }
  iVar3 = *(int *)this;
  if (iVar3 == 1) {
    *(undefined4 *)(*(int *)(this + 0x14) + 0x1fc) = DAT_00070614;
    fVar6 = DAT_0007060c;
    fVar5 = *(float *)(this + 4);
    *(float *)(this + 4) = fVar5 + *(float *)(this + 8);
    if (fVar6 < fVar5 + *(float *)(this + 8)) {
      *(float *)(this + 4) = DAT_00070610;
      *(undefined4 *)this = 2;
    }
  }
  else if (iVar3 == 2) {
    fVar6 = *(float *)(this + 4);
    if (fVar6 < DAT_00070618) {
      iVar3 = *(int *)(this + 0x14);
      fVar5 = fVar6;
      fVar2 = DAT_0007060c + fVar6 * DAT_0007061c;
    }
    else {
      iVar3 = *(int *)(this + 0x14);
      fVar5 = DAT_00070610;
      fVar2 = DAT_00070618;
    }
    if (fVar6 < DAT_00070618) {
      *(float *)(iVar3 + 0x1fc) = fVar2;
    }
    else {
      *(float *)(iVar3 + 0x1fc) = fVar5;
    }
    fVar6 = DAT_0007060c;
    fVar5 = *(float *)(this + 4);
    *(float *)(this + 4) = fVar5 + *(float *)(this + 8);
    if (fVar6 < fVar5 + *(float *)(this + 8)) {
      *(float *)(this + 4) = DAT_00070610;
      *(undefined4 *)this = 1;
    }
  }
  else if (iVar3 == 0) {
    return;
  }
  bVar1 = *(float *)(this + 0xc) + *(float *)(this + 0x10) < DAT_0007060c;
  *(float *)(this + 0xc) = *(float *)(this + 0xc) + *(float *)(this + 0x10);
  iVar3 = DAT_00070628;
  if (bVar1) {
    return;
  }
  *(float *)(this + 0xc) = DAT_00070610;
  cRSound::Play(*(int *)(iVar4 + iVar3));
  return;
}
