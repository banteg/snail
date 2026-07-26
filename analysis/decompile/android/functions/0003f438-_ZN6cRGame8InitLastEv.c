/*
 * mangled: _ZN6cRGame8InitLastEv
 * demangled: cRGame::InitLast()
 * address: 0003f438
 * size: 164
 */

/* cRGame::InitLast() */

void __thiscall cRGame::InitLast(cRGame *this)

{
  int iVar1;
  int iVar2;
  int *piVar3;

  iVar2 = DAT_0003f4dc;
  OFInit();
  iVar2 = iVar2 + 0x3f454;
  if (**(int **)(iVar2 + DAT_0003f4e0) == -1) {
    OFONewUser((char *)(*(int *)(iVar2 + DAT_0003f4f0) + 0xf0));
  }
  wprintf((char *)(iVar2 + DAT_0003f4e4));
  cKeyPad::Open((cKeyPad *)(this + 0xbf0));
  cRBackdrop::Init((cRBackdrop *)(this + 0x4d2e0),1);
  piVar3 = *(int **)(iVar2 + DAT_0003f4e8);
  iVar1 = *piVar3;
  **(undefined1 **)(iVar2 + DAT_0003f4ec) = 1;
  cROptions::Apply((bool)((char)iVar1 + -0x80));
  *(undefined4 *)(*piVar3 + 0x718b4) = 0;
  return;
}
