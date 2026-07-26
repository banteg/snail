/*
 * mangled: _ZN9cRSubGame7TestLocEP8cRSubLocii
 * demangled: cRSubGame::TestLoc(cRSubLoc*, int, int)
 * address: 0006d464
 * size: 164
 */

/* cRSubGame::TestLoc(cRSubLoc*, int, int) */

bool __thiscall cRSubGame::TestLoc(cRSubGame *this,cRSubLoc *param_1,int param_2,int param_3)

{
  cRSubGame cVar1;
  int iVar2;
  uint uVar3;

  iVar2 = cRSubLoc::Yi(param_1);
  uVar3 = param_2 + ((byte)param_1[0x34] & 7);
  if (((uVar3 < 8) && (iVar2 = iVar2 + param_3, -1 < iVar2)) && (iVar2 < *(int *)(this + 0x74))) {
    iVar2 = iVar2 * 0x240 + uVar3 * 0x48;
    cVar1 = this[iVar2 + 0x13b0c];
    iVar2 = cRSubLoc::IsEmpty((cRSubLoc *)(this + iVar2 + 0x13adc));
    if ((iVar2 == 0) && (cVar1 != (cRSubGame)0x23 && cVar1 != (cRSubGame)0x0)) {
      return cVar1 != (cRSubGame)0x16 && cVar1 != (cRSubGame)0x1c;
    }
  }
  return false;
}
