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

  *(int *)(this + *(int *)this * 0xc + 0x14) = param_3;
  *(int *)(this + *(int *)this * 0xc + 0x10) = param_2;
  iVar1 = *(int *)this + 1;
  *(int *)this = iVar1;
  if (*(int *)(this + 4) < iVar1) {
    *(int *)(this + 4) = iVar1;
  }
  if (iVar1 < 15000) {
    return;
  }
  RShellError("Memory Stack Full");
  uRam00000000 = 0;
  return;
}
