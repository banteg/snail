/*
 * mangled: _Z18RShellScrambleFilePvi
 * demangled: RShellScrambleFile(void*, int)
 * address: 0002a2d8
 * size: 40
 */

/* RShellScrambleFile(void*, int) */

void RShellScrambleFile(void *param_1,int param_2)

{
  int iVar1;

  if (param_2 < 1) {
    return;
  }
  iVar1 = 0;
  do {
    *(byte *)((int)param_1 + iVar1) = *(byte *)((int)param_1 + iVar1) ^ (byte)iVar1;
    iVar1 = iVar1 + 1;
  } while (iVar1 != param_2);
  return;
}
