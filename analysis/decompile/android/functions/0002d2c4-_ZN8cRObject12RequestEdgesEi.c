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

  if (*(int *)(this + 0xe4) != 0) {
    return;
  }
  *(int *)(this + 0xe4) = param_1;
  uVar1 = RShellMemoryMalloc(param_1 * 10,"Object Edges");
  *(undefined4 *)(this + 0xe8) = uVar1;
  uVar1 = RShellMemoryMalloc(param_1 * 4,"Object Edge Index Array");
  *(undefined4 *)(this + 0xe0) = uVar1;
  return;
}
