/*
 * mangled: _ZN9cRObjects10ReSetFlagsEi
 * demangled: cRObjects::ReSetFlags(int)
 * address: 0002cc3c
 * size: 68
 */

/* cRObjects::ReSetFlags(int) */

void __thiscall cRObjects::ReSetFlags(cRObjects *this,int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;

  iVar4 = *(int *)(this + 4);
  if (0 < iVar4) {
    iVar3 = 0;
    iVar1 = *(int *)(this + 8);
    iVar2 = 0;
    do {
      iVar2 = iVar2 + 1;
      *(uint *)(iVar1 + iVar3) = *(uint *)(iVar1 + iVar3) & ~param_1;
      iVar3 = iVar3 + 0x110;
    } while (iVar2 != iVar4);
  }
  return;
}
