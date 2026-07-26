/*
 * mangled: _ZN8cRObject15RequestVerticesEi
 * demangled: cRObject::RequestVertices(int)
 * address: 00012710
 * size: 124
 */

/* cRObject::RequestVertices(int) */

void __thiscall cRObject::RequestVertices(cRObject *this,int param_1)

{
  undefined4 uVar1;
  int iVar2;

  if (param_1 < 0x10001) {
    iVar2 = *(int *)(this + 0xa0);
  }
  else {
    RShellError("Too many Vertices");
    iVar2 = *(int *)(this + 0xa0);
  }
  if (iVar2 < 1) {
    if (iVar2 != 0) {
      return;
    }
  }
  else {
    if (param_1 <= iVar2) {
      return;
    }
    RShellError("Reallocation of Vertices impending\n");
    RShellMemoryFree(*(void **)(this + 0xa4));
    *(undefined4 *)(this + 0xa0) = 0;
  }
  *(int *)(this + 0xa0) = param_1;
  uVar1 = RShellMemoryMalloc(param_1 * 0xc,"Object Vertex List");
  *(undefined4 *)(this + 0xa4) = uVar1;
  return;
}
