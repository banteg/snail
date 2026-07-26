/*
 * mangled: _ZN8cRObject12RequestEdgesEi
 * demangled: cRObject::RequestEdges(int)
 * address: 0002d2c4
 * size: 84
 */

/* cRObject::RequestEdges(int) */

void __thiscall cRObject::RequestEdges(cRObject *this,int param_1)

{
  undefined4 uVar1;
  char *pcVar2;
  int iVar3;

  iVar3 = DAT_0002d318 + 0x2d2e0;
  if (*(int *)(this + 0xe4) != 0) {
    return;
  }
  *(int *)(this + 0xe4) = param_1;
  uVar1 = RShellMemoryMalloc(param_1 * 10,(char *)(iVar3 + DAT_0002d31c));
  pcVar2 = (char *)(iVar3 + DAT_0002d320);
  *(undefined4 *)(this + 0xe8) = uVar1;
  uVar1 = RShellMemoryMalloc(param_1 * 4,pcVar2);
  *(undefined4 *)(this + 0xe0) = uVar1;
  return;
}
