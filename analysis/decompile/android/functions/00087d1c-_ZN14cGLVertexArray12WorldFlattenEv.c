/*
 * mangled: _ZN14cGLVertexArray12WorldFlattenEv
 * demangled: cGLVertexArray::WorldFlatten()
 * address: 00087d1c
 * size: 128
 */

/* cGLVertexArray::WorldFlatten() */

void cGLVertexArray::WorldFlatten(void)

{
  float fVar1;
  int in_r0;
  float extraout_r0;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint in_fpscr;
  float in_s0;

  fVar1 = DAT_00087da4;
  iVar5 = *(int *)(in_r0 + 0x3c);
  if (0 < iVar5) {
    iVar3 = 0;
    iVar6 = *(int *)(in_r0 + 8);
    iVar4 = 0;
    do {
      iVar2 = iVar6 + iVar3;
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + 10;
      VectorSignedToFloat((int)*(short *)(iVar2 + 4),(byte)(in_fpscr >> 0x16) & 3);
      in_s0 = floorf(in_s0);
      *(undefined2 *)(iVar2 + 2) = 0;
      *(short *)(iVar2 + 4) = (short)(int)(extraout_r0 * fVar1);
    } while (iVar4 != iVar5);
  }
  return;
}
