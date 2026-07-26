/*
 * mangled: _Z16RShellSwapTgaRGBP10cTgaHeader
 * demangled: RShellSwapTgaRGB(cTgaHeader*)
 * address: 0002a304
 * size: 76
 */

/* RShellSwapTgaRGB(cTgaHeader*) */

void RShellSwapTgaRGB(cTgaHeader *param_1)

{
  cTgaHeader cVar1;
  int iVar2;
  cTgaHeader *pcVar3;

  if ((uint)*(ushort *)(param_1 + 0xc) * (uint)*(ushort *)(param_1 + 0xe) == 0) {
    return;
  }
  pcVar3 = param_1 + 0x12;
  iVar2 = 0;
  do {
    iVar2 = iVar2 + 1;
    cVar1 = pcVar3[2];
    pcVar3[2] = *pcVar3;
    *pcVar3 = cVar1;
    pcVar3 = pcVar3 + 3;
  } while ((uint)*(ushort *)(param_1 + 0xc) * (uint)*(ushort *)(param_1 + 0xe) - iVar2 != 0 &&
           iVar2 <= (int)((uint)*(ushort *)(param_1 + 0xc) * (uint)*(ushort *)(param_1 + 0xe)));
  return;
}
