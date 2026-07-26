/*
 * mangled: _ZN14cGLVertexArray12WorldFlattenEv
 * demangled: cGLVertexArray::WorldFlatten()
 * address: 0006d1d8
 * size: 180
 */

/* cGLVertexArray::WorldFlatten() */

void __thiscall cGLVertexArray::WorldFlatten(cGLVertexArray *this)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint in_fpscr;
  float fVar4;

  if (*(int *)(this + 0x3c) < 1) {
    return;
  }
  iVar3 = 0;
  iVar2 = 0;
  do {
    iVar3 = iVar3 + 1;
    _printf("Z0=%i ",(int)*(short *)(*(int *)(this + 8) + iVar2 + 4));
    fVar4 = (float)VectorSignedToFloat((int)*(short *)(iVar2 + *(int *)(this + 8) + 4),
                                       (byte)(in_fpscr >> 0x16) & 3);
    fVar4 = (float)VectorSignedToFloat((int)(fVar4 * 0.0078125 * 10.0),(byte)(in_fpscr >> 0x16) & 3)
    ;
    *(short *)(iVar2 + *(int *)(this + 8) + 4) = (short)(int)((fVar4 / 10.0) * 128.0);
    _printf("Z1=%i \n",(int)*(short *)(*(int *)(this + 8) + iVar2 + 4));
    iVar1 = *(int *)(this + 8) + iVar2;
    iVar2 = iVar2 + 10;
    *(undefined2 *)(iVar1 + 2) = 0;
  } while (iVar3 < *(int *)(this + 0x3c));
  return;
}
