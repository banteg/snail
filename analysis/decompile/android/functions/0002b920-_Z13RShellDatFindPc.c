/*
 * mangled: _Z13RShellDatFindPc
 * demangled: RShellDatFind(char*)
 * address: 0002b920
 * size: 84
 */

/* RShellDatFind(char*) */

int RShellDatFind(char *param_1)

{
  int iVar1;

  if ((gDat != 0) && (iVar1 = cRHash::Search((cRHash *)gDatHash,param_1), iVar1 != -1)) {
    return gDat + iVar1 * 0x18 + 4;
  }
  return 0;
}
