/*
 * mangled: _Z21RShellScrambleFileDatPvi
 * demangled: RShellScrambleFileDat(void*, int)
 * address: 00029a3c
 * size: 72
 */

/* RShellScrambleFileDat(void*, int) */

void RShellScrambleFileDat(void *param_1,int param_2)

{
  byte bVar1;
  int iVar2;

  if (0 < param_2) {
    iVar2 = 0;
    bVar1 = 0;
    do {
      *(byte *)((int)param_1 + iVar2) =
           bVar1 ^ *(byte *)((int)param_1 + iVar2) ^ (char)iVar2 * (char)iVar2;
      iVar2 = iVar2 + 1;
      bVar1 = bVar1 + 3;
    } while (iVar2 != param_2);
  }
  return;
}
