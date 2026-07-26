/*
 * mangled: _ZN14cGLVertexArray12WorldFlattenEv
 * demangled: cGLVertexArray::WorldFlatten()
 * address: 00087d1c
 * size: 128
 */

/* cGLVertexArray::WorldFlatten() */

void cGLVertexArray::WorldFlatten(void)

{
  int in_r0;
  float extraout_r0;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint in_fpscr;
  float in_s0;

  iVar4 = *(int *)(in_r0 + 0x3c);
  if (0 < iVar4) {
    iVar2 = 0;
    iVar5 = *(int *)(in_r0 + 8);
    iVar3 = 0;
    do {
      iVar1 = iVar5 + iVar2;
      iVar3 = iVar3 + 1;
      iVar2 = iVar2 + 10;
      VectorSignedToFloat((int)*(short *)(iVar1 + 4),(byte)(in_fpscr >> 0x16) & 3);
      in_s0 = floorf(in_s0);
      *(undefined2 *)(iVar1 + 2) = 0;
      *(short *)(iVar1 + 4) = (short)(int)(extraout_r0 * 128.0);
    } while (iVar3 != iVar4);
  }
  return;
}
