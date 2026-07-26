/*
 * mangled: _ZN13cRShellMemory6MallocEPcii
 * demangled: cRShellMemory::Malloc(char*, int, int)
 * address: 0002b5b4
 * size: 104
 */

/* cRShellMemory::Malloc(char*, int, int) */

void __thiscall cRShellMemory::Malloc(cRShellMemory *this,char *param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;

  iVar1 = DAT_0002b61c + 0x2b5cc;
  *(int *)(this + *(int *)this * 0xc + 0x14) = param_3;
  *(int *)(this + *(int *)this * 0xc + 0x10) = param_2;
  iVar2 = *(int *)this + 1;
  *(int *)this = iVar2;
  if (*(int *)(this + 4) < iVar2) {
    *(int *)(this + 4) = iVar2;
  }
  if (iVar2 < 15000) {
    return;
  }
  RShellError((char *)(iVar1 + DAT_0002b620));
  uRam00000000 = 0;
  return;
}
