/*
 * mangled: _ZN13cRShellMemory4FreeEi
 * demangled: cRShellMemory::Free(int)
 * address: 00029b54
 * size: 164
 */

/* cRShellMemory::Free(int) */

void __thiscall cRShellMemory::Free(cRShellMemory *this,int param_1)

{
  bool bVar1;
  cRShellMemory *pcVar2;
  int iVar3;
  cRShellMemory *pcVar4;
  int iVar5;

  iVar5 = *(int *)this;
  if ((iVar5 < 1) || (*(int *)(this + 0x10) == param_1)) {
    iVar3 = 0;
  }
  else {
    iVar3 = 1;
    pcVar4 = this;
    if (1 < iVar5) {
      do {
        pcVar2 = pcVar4 + 0x1c;
        pcVar4 = pcVar4 + 0xc;
        if (*(int *)pcVar2 == param_1) break;
        iVar3 = iVar3 + 1;
      } while (iVar3 < iVar5);
    }
  }
  iVar5 = iVar5 + -1;
  if (iVar3 < iVar5) {
    pcVar4 = this + (iVar3 + 1) * 0xc + 0x14;
    iVar3 = iVar3 + 1;
    do {
      pcVar4[-0x14] = pcVar4[-8];
      *(undefined4 *)(pcVar4 + -0xc) = *(undefined4 *)pcVar4;
      *(undefined4 *)(pcVar4 + -0x10) = *(undefined4 *)(pcVar4 + -4);
      pcVar4 = pcVar4 + 0xc;
      bVar1 = iVar3 < iVar5;
      iVar3 = iVar3 + 1;
    } while (bVar1);
  }
  *(int *)this = iVar5;
  return;
}
