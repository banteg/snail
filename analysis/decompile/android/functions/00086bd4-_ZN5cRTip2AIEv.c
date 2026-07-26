/*
 * mangled: _ZN5cRTip2AIEv
 * demangled: cRTip::AI()
 * address: 00086bd4
 * size: 296
 */

/* cRTip::AI() */

void __thiscall cRTip::AI(cRTip *this)

{
  float fVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  float fVar6;

  iVar2 = DAT_00086d04;
  iVar4 = DAT_00086d00 + 0x86bec;
  piVar5 = *(int **)(iVar4 + DAT_00086d04);
  if (*(char *)(*piVar5 + 0x718b9) != '\0') {
    cRBorder::HideInit(*(cRBorder **)(this + 0xc));
    return;
  }
  cRBorder::UnHideInit(*(cRBorder **)(this + 0xc));
  fVar1 = DAT_00086cfc;
  iVar3 = *(int *)(this + 0x10);
  if ((iVar3 != 0) && ((*(uint *)(iVar3 + 0x194) & 0x20) != 0)) {
    *(uint *)(iVar3 + 0x194) = *(uint *)(iVar3 + 0x194) & 0xffffffdf;
    *(undefined4 *)(*piVar5 + 0x15c) = *(undefined4 *)(this + 4);
    UnInit(this);
    cRBorderManager::UnHideBorders((cRBorderManager *)(*piVar5 + 0xd14));
    *(undefined4 *)this = 0;
    return;
  }
  iVar3 = *(int *)(this + 0x14);
  if ((iVar3 != 0) && ((*(uint *)(iVar3 + 0x194) & 0x20) != 0)) {
    piVar5 = *(int **)(iVar4 + iVar2);
    *(uint *)(iVar3 + 0x194) = *(uint *)(iVar3 + 0x194) & 0xffffffdf;
    *(undefined4 *)(*piVar5 + 0x15c) = *(undefined4 *)(this + 4);
    UnInit(this);
    cRBorderManager::UnHideBorders((cRBorderManager *)(*piVar5 + 0xd14));
    *(undefined4 *)this = 0;
    return;
  }
  if ((**(uint **)(this + 8) & 2) == 0) {
    return;
  }
  fVar6 = *(float *)(this + 0x18);
  *(float *)(this + 0x18) = fVar6 + *(float *)(this + 0x1c);
  if (fVar6 + *(float *)(this + 0x1c) <= fVar1) {
    return;
  }
  UnInit(this);
  *(undefined4 *)this = 0;
  return;
}
