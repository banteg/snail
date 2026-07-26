/*
 * mangled: _ZN15cRBorderManager9GetBorderEv
 * demangled: cRBorderManager::GetBorder()
 * address: 000388a0
 * size: 132
 */

/* cRBorderManager::GetBorder() */

cRBorderManager * __thiscall cRBorderManager::GetBorder(cRBorderManager *this)

{
  int iVar1;
  cRBorderManager *pcVar2;

  pcVar2 = this + 0x80c;
  iVar1 = 0;
  do {
    if (*(int *)pcVar2 == 0) {
      *(undefined4 *)(this + iVar1 * 0x71c + 0x808) =
           *(undefined4 *)(*(int *)PTR__Game_001b60b8 + 0x2d8);
      return this + iVar1 * 0x71c + 0x678;
    }
    iVar1 = iVar1 + 1;
    pcVar2 = pcVar2 + 0x71c;
  } while (iVar1 != 0x96);
  RShellError("Run out of Borders - Increase RGAME_BORDER_NUMBER");
  return (cRBorderManager *)0x0;
}
