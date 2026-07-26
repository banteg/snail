/*
 * mangled: _ZN10cRSubHover2OnEv
 * demangled: cRSubHover::On()
 * address: 00070bf0
 * size: 100
 */

/* cRSubHover::On() */

void __thiscall cRSubHover::On(cRSubHover *this)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int *piVar4;

  iVar3 = DAT_00070c58 + 0x70c08;
  if (*(int *)(this + 0xc) != 0) {
    return;
  }
  *(undefined4 *)(this + 0xc) = 1;
  iVar2 = DAT_00070c5c;
  uVar1 = DAT_00070c54;
  *(undefined4 *)(this + 0x14) = DAT_00070c54;
  piVar4 = *(int **)(iVar3 + iVar2);
  *(undefined4 *)this = uVar1;
  *(undefined4 *)(this + 0x1c) = uVar1;
  *(undefined4 *)(this + 0x18) = uVar1;
  cRSnail::SetJetPack((cRSnail *)(*piVar4 + 0x83b64),1);
  JetInit(this);
  return;
}
