/*
 * mangled: _ZN6cRHelp2AIEv
 * demangled: cRHelp::AI()
 * address: 00064b6c
 * size: 180
 */

/* cRHelp::AI() */

void __thiscall cRHelp::AI(cRHelp *this)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;

  iVar2 = DAT_00064c24;
  iVar3 = DAT_00064c20 + 0x64b84;
  piVar4 = *(int **)(iVar3 + DAT_00064c24);
  iVar1 = *piVar4;
  if (((*(uint *)(*(int *)(iVar1 + 0x224) + 0x30) & 0x4000) == 0) || (*(int *)(iVar1 + 0x24) != 0))
  {
    if (this[4] == (cRHelp)0x0) {
      return;
    }
    iVar1 = *(int *)(iVar1 + 0x24);
  }
  else {
    if (this[4] != (cRHelp)0x0) {
      return;
    }
    cRSound::Play(*(int *)(iVar3 + DAT_00064c28));
    cRFade::Start((cRFade *)(*piVar4 + 0x24),(_func_void *)0x0);
    iVar1 = *piVar4;
    this[4] = (cRHelp)0x1;
    iVar1 = *(int *)(iVar1 + 0x24);
  }
  if (iVar1 != 4) {
    return;
  }
  UnInit();
  iVar2 = **(int **)(iVar3 + iVar2);
  *(undefined1 *)(iVar2 + 0x2c0) = 1;
  *(undefined4 *)(iVar2 + 0x15c) = 2;
  return;
}
