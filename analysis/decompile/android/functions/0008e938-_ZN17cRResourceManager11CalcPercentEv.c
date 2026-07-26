/*
 * mangled: _ZN17cRResourceManager11CalcPercentEv
 * demangled: cRResourceManager::CalcPercent()
 * address: 0008e938
 * size: 104
 */

/* cRResourceManager::CalcPercent() */

float __thiscall cRResourceManager::CalcPercent(cRResourceManager *this)

{
  cRResourceManager *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint in_fpscr;
  float fVar5;
  float fVar6;

  iVar2 = *(int *)(this + 4);
  if (iVar2 == 0) {
    return DAT_0008e9a0;
  }
  if (iVar2 < 1) {
    iVar4 = 0;
  }
  else {
    iVar3 = 0;
    iVar4 = 0;
    do {
      pcVar1 = this + 8;
      iVar3 = iVar3 + 1;
      this = this + 0x8c;
      if (*(int *)pcVar1 == 2) {
        iVar4 = iVar4 + 1;
      }
    } while (iVar3 != iVar2);
  }
  fVar5 = (float)VectorSignedToFloat(iVar4,(byte)(in_fpscr >> 0x16) & 3);
  fVar6 = (float)VectorSignedToFloat(iVar2,(byte)(in_fpscr >> 0x16) & 3);
  return (fVar5 * DAT_0008e9a0) / fVar6;
}
