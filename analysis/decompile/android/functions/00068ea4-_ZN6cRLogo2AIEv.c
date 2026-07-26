/*
 * mangled: _ZN6cRLogo2AIEv
 * demangled: cRLogo::AI()
 * address: 00068ea4
 * size: 292
 */

/* cRLogo::AI() */

void __thiscall cRLogo::AI(cRLogo *this)

{
  float fVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  float fVar7;

  iVar2 = DAT_00068fd8;
  iVar5 = DAT_00068fd4 + 0x68ebc;
  piVar6 = *(int **)(iVar5 + DAT_00068fd8);
  iVar3 = *piVar6;
  iVar4 = *(int *)(iVar3 + 0x24);
  if (iVar4 == 0) {
    if ((*(uint *)(*(int *)(iVar3 + 0x224) + 0x30) & 0x4000) == 0) {
      iVar3 = RShellInkey();
      if (iVar3 != 0xb) {
        iVar4 = *(int *)(*piVar6 + 0x24);
        goto LAB_00068efc;
      }
      iVar3 = *piVar6;
    }
    cRFade::Start((cRFade *)(iVar3 + 0x24),(_func_void *)0x0);
    piVar6 = *(int **)(iVar5 + iVar2);
    *this = (cRLogo)0x1;
    iVar4 = *(int *)(*piVar6 + 0x24);
  }
LAB_00068efc:
  if ((iVar4 == 4) && (*this != (cRLogo)0x0)) {
    UnInit(this);
  }
  fVar1 = DAT_00068fd0;
  fVar7 = DAT_00068fc8;
  if (*(int *)(this + 0xc) == 0) {
    *(float *)(this + 4) = DAT_00068fc8;
    *(undefined4 *)(this + 0xc) = 1;
    if (*(float *)(this + 0x14) != 0.0) {
      fVar7 = DAT_00068fd0 / (*(float *)(this + 0x14) * DAT_00068fcc);
    }
    *(float *)(this + 8) = fVar7;
    return;
  }
  if (*(int *)(this + 0xc) != 1) {
    return;
  }
  fVar7 = *(float *)(this + 4);
  *(float *)(this + 4) = fVar7 + *(float *)(this + 8);
  if (fVar1 < fVar7 + *(float *)(this + 8)) {
    cRFade::Start((cRFade *)(**(int **)(iVar5 + iVar2) + 0x24),(_func_void *)0x0);
    *this = (cRLogo)0x1;
    *(int *)(this + 0xc) = *(int *)(this + 0xc) + 1;
    return;
  }
  return;
}
