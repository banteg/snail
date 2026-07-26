/*
 * mangled: _ZN13cRShellMemory4SizeEi
 * demangled: cRShellMemory::Size(int)
 * address: 0002b624
 * size: 128
 */

/* cRShellMemory::Size(int) */

undefined4 __thiscall cRShellMemory::Size(cRShellMemory *this,int param_1)

{
  cRShellMemory *pcVar1;
  int iVar2;
  cRShellMemory *pcVar3;
  bool bVar4;

  iVar2 = *(int *)this + -1;
  if (-1 < iVar2) {
    if (*(int *)(this + iVar2 * 0xc + 0x10) != param_1) {
      pcVar3 = this + *(int *)this * 0xc + 0xc;
      do {
        bVar4 = iVar2 == 0;
        iVar2 = iVar2 + -1;
        if (bVar4) goto LAB_0002b67c;
        pcVar1 = pcVar3 + -0x14;
        pcVar3 = pcVar3 + -0xc;
      } while (*(int *)pcVar1 != param_1);
    }
    return *(undefined4 *)(this + iVar2 * 0xc + 0x14);
  }
LAB_0002b67c:
  RShellError("Cannot find Memory Size");
  return 0;
}
