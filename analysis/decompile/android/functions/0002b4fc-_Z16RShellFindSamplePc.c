/*
 * mangled: _Z16RShellFindSamplePc
 * demangled: RShellFindSample(char*)
 * address: 0002b4fc
 * size: 128
 */

/* RShellFindSample(char*) */

int RShellFindSample(char *param_1)

{
  int iVar1;
  int iVar2;

  if (0 < RShellSoundCount) {
    iVar2 = 0;
    do {
      iVar1 = Rstrfind(param_1,RShellSoundName + iVar2 * 0x80);
      if (iVar1 != 0) {
        return iVar2;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < RShellSoundCount);
  }
  RShellError("Cannot Find Sample %s",param_1);
  return 0;
}
