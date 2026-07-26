/*
 * mangled: _ZN15cRBorderManager9GetBorderEv
 * demangled: cRBorderManager::GetBorder()
 * address: 0005d11c
 * size: 128
 */

/* cRBorderManager::GetBorder() */

cRBorderManager * __thiscall cRBorderManager::GetBorder(cRBorderManager *this)

{
  int iVar1;
  int iVar2;
  cRBorderManager *pcVar3;

  iVar2 = 0;
  pcVar3 = this + 0x80c;
  do {
    iVar1 = *(int *)pcVar3;
    pcVar3 = pcVar3 + 0x71c;
    if (iVar1 == 0) {
      *(undefined4 *)(this + iVar2 * 0x71c + 0x808) =
           *(undefined4 *)(**(int **)(DAT_0005d19c + 0x5d138 + DAT_0005d1a0) + 0x2d8);
      return this + iVar2 * 0x71c + 0x678;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 != 0x96);
  RShellError((char *)(DAT_0005d19c + 0x5d138 + DAT_0005d1a4));
  return (cRBorderManager *)0x0;
}
