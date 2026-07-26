/*
 * mangled: _ZN11cRSnailSkin4InitEv
 * demangled: cRSnailSkin::Init()
 * address: 0006d290
 * size: 52
 */

/* cRSnailSkin::Init() */

void __thiscall cRSnailSkin::Init(cRSnailSkin *this)

{
  int iVar1;
  int iVar2;
  int *piVar3;

  iVar1 = DAT_0006d2c8;
  iVar2 = DAT_0006d2c4 + 0x6d2a8;
  *(undefined4 *)(this + 0x14) = 0;
  piVar3 = *(int **)(iVar2 + iVar1);
  *(undefined4 *)this = 0;
  *(int *)(this + 0x10) = *piVar3 + 0x83b64;
  return;
}
