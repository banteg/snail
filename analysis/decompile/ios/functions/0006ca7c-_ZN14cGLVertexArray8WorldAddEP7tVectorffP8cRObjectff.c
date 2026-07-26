/*
 * mangled: _ZN14cGLVertexArray8WorldAddEP7tVectorffP8cRObjectff
 * demangled: cGLVertexArray::WorldAdd(tVector*, float, float, cRObject*, float, float)
 * address: 0006ca7c
 * size: 1760
 */

/* cGLVertexArray::WorldAdd(tVector*, float, float, cRObject*, float, float) */

void __thiscall
cGLVertexArray::WorldAdd
          (cGLVertexArray *this,tVector *param_1,float param_2,float param_3,cRObject *param_4,
          float param_5,float param_6)

{
  undefined2 uVar1;
  int iVar2;
  float *pfVar3;
  int iVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;

  fVar9 = param_5 * 0.25;
  fVar10 = 0.0;
  fVar6 = 128.0;
  pfVar3 = (float *)((uint)*(ushort *)(*(int *)(param_4 + 200) + 2) * 0xc + *(int *)(param_4 + 0xa4)
                    );
  fVar7 = *(float *)(param_1 + 4) + pfVar3[1] + fVar9;
  fVar8 = (*(float *)(param_1 + 8) + pfVar3[2] + param_5) - param_6;
  iVar2 = ___modsi3(*(undefined4 *)(this + 0x40),*(undefined4 *)(this + 0x3c));
  *(short *)(iVar2 * 10 + *(int *)(this + 8)) =
       (short)(int)((*(float *)param_1 + *pfVar3 + fVar10) * fVar6);
  iVar2 = ___modsi3(*(undefined4 *)(this + 0x40),*(undefined4 *)(this + 0x3c));
  *(short *)(iVar2 * 10 + *(int *)(this + 8) + 2) = (short)(int)(fVar7 * fVar6);
  iVar2 = ___modsi3(*(undefined4 *)(this + 0x40),*(undefined4 *)(this + 0x3c));
  *(short *)(iVar2 * 10 + *(int *)(this + 8) + 4) = (short)(int)(fVar8 * fVar6);
  iVar2 = ___modsi3(*(undefined4 *)(this + 0x40),*(undefined4 *)(this + 0x3c));
  *(short *)(iVar2 * 10 + *(int *)(this + 8) + 6) =
       (short)(int)((param_2 + *(float *)(*(int *)(param_4 + 200) + 0x10)) * fVar6);
  iVar2 = ___modsi3(*(undefined4 *)(this + 0x40),*(undefined4 *)(this + 0x3c));
  *(short *)(iVar2 * 10 + *(int *)(this + 8) + 8) =
       (short)(int)((param_3 + *(float *)(*(int *)(param_4 + 200) + 0x14)) * fVar6);
  pfVar3 = (float *)((uint)*(ushort *)(*(int *)(param_4 + 200) + 4) * 0xc + *(int *)(param_4 + 0xa4)
                    );
  fVar9 = fVar9 + *(float *)(param_1 + 4) + pfVar3[1];
  fVar7 = (param_5 + *(float *)(param_1 + 8) + pfVar3[2]) - param_6;
  iVar2 = ___modsi3(*(int *)(this + 0x40) + 1,*(undefined4 *)(this + 0x3c));
  *(short *)(iVar2 * 10 + *(int *)(this + 8)) =
       (short)(int)((*(float *)param_1 + *pfVar3 + fVar10) * fVar6);
  iVar2 = ___modsi3(*(int *)(this + 0x40) + 1,*(undefined4 *)(this + 0x3c));
  *(short *)(iVar2 * 10 + *(int *)(this + 8) + 2) = (short)(int)(fVar9 * fVar6);
  iVar2 = ___modsi3(*(int *)(this + 0x40) + 1,*(undefined4 *)(this + 0x3c));
  *(short *)(iVar2 * 10 + *(int *)(this + 8) + 4) = (short)(int)(fVar7 * fVar6);
  iVar2 = ___modsi3(*(int *)(this + 0x40) + 1,*(undefined4 *)(this + 0x3c));
  *(short *)(iVar2 * 10 + *(int *)(this + 8) + 6) =
       (short)(int)((param_2 + *(float *)(*(int *)(param_4 + 200) + 0x18)) * fVar6);
  iVar2 = ___modsi3(*(int *)(this + 0x40) + 1,*(undefined4 *)(this + 0x3c));
  *(short *)(iVar2 * 10 + *(int *)(this + 8) + 8) =
       (short)(int)((param_3 + *(float *)(*(int *)(param_4 + 200) + 0x1c)) * fVar6);
  pfVar3 = (float *)((uint)*(ushort *)(*(int *)(param_4 + 200) + 6) * 0xc + *(int *)(param_4 + 0xa4)
                    );
  fVar7 = *(float *)(param_1 + 4) + pfVar3[1];
  fVar9 = (*(float *)(param_1 + 8) + pfVar3[2]) - param_6;
  iVar2 = ___modsi3(*(int *)(this + 0x40) + 2,*(undefined4 *)(this + 0x3c));
  *(short *)(iVar2 * 10 + *(int *)(this + 8)) = (short)(int)((*(float *)param_1 + *pfVar3) * fVar6);
  iVar2 = ___modsi3(*(int *)(this + 0x40) + 2,*(undefined4 *)(this + 0x3c));
  *(short *)(iVar2 * 10 + *(int *)(this + 8) + 2) = (short)(int)(fVar7 * fVar6);
  iVar2 = ___modsi3(*(int *)(this + 0x40) + 2,*(undefined4 *)(this + 0x3c));
  *(short *)(iVar2 * 10 + *(int *)(this + 8) + 4) = (short)(int)(fVar9 * fVar6);
  iVar2 = ___modsi3(*(int *)(this + 0x40) + 2,*(undefined4 *)(this + 0x3c));
  *(short *)(iVar2 * 10 + *(int *)(this + 8) + 6) =
       (short)(int)((param_2 + *(float *)(*(int *)(param_4 + 200) + 0x20)) * fVar6);
  iVar2 = ___modsi3(*(int *)(this + 0x40) + 2,*(undefined4 *)(this + 0x3c));
  *(short *)(iVar2 * 10 + *(int *)(this + 8) + 8) =
       (short)(int)((param_3 + *(float *)(*(int *)(param_4 + 200) + 0x24)) * fVar6);
  pfVar3 = (float *)((uint)*(ushort *)(*(int *)(param_4 + 200) + 8) * 0xc + *(int *)(param_4 + 0xa4)
                    );
  fVar7 = *(float *)(param_1 + 4) + pfVar3[1];
  fVar9 = (*(float *)(param_1 + 8) + pfVar3[2]) - param_6;
  iVar2 = ___modsi3(*(int *)(this + 0x40) + 3,*(undefined4 *)(this + 0x3c));
  *(short *)(iVar2 * 10 + *(int *)(this + 8)) = (short)(int)((*(float *)param_1 + *pfVar3) * fVar6);
  iVar2 = ___modsi3(*(int *)(this + 0x40) + 3,*(undefined4 *)(this + 0x3c));
  *(short *)(iVar2 * 10 + *(int *)(this + 8) + 2) = (short)(int)(fVar7 * fVar6);
  iVar2 = ___modsi3(*(int *)(this + 0x40) + 3,*(undefined4 *)(this + 0x3c));
  *(short *)(iVar2 * 10 + *(int *)(this + 8) + 4) = (short)(int)(fVar9 * fVar6);
  iVar2 = ___modsi3(*(int *)(this + 0x40) + 3,*(undefined4 *)(this + 0x3c));
  *(short *)(iVar2 * 10 + *(int *)(this + 8) + 6) =
       (short)(int)((param_2 + *(float *)(*(int *)(param_4 + 200) + 0x28)) * fVar6);
  iVar2 = ___modsi3(*(int *)(this + 0x40) + 3,*(undefined4 *)(this + 0x3c));
  *(short *)(iVar2 * 10 + *(int *)(this + 8) + 8) =
       (short)(int)((param_3 + *(float *)(*(int *)(param_4 + 200) + 0x2c)) * fVar6);
  iVar4 = *(int *)(this + 0x24);
  iVar2 = ___modsi3(iVar4,*(undefined4 *)(this + 0x28));
  iVar5 = *(int *)(this + 0x20);
  uVar1 = ___modsi3(*(undefined4 *)(this + 0x40),*(undefined4 *)(this + 0x3c));
  *(undefined2 *)(iVar2 * 2 + iVar5) = uVar1;
  *(int *)(this + 0x24) = iVar4 + 1;
  iVar2 = ___modsi3(iVar4 + 1,*(undefined4 *)(this + 0x28));
  iVar5 = *(int *)(this + 0x20);
  uVar1 = ___modsi3(*(int *)(this + 0x40) + 1,*(undefined4 *)(this + 0x3c));
  *(undefined2 *)(iVar2 * 2 + iVar5) = uVar1;
  *(int *)(this + 0x24) = iVar4 + 2;
  iVar2 = ___modsi3(iVar4 + 2,*(undefined4 *)(this + 0x28));
  iVar5 = *(int *)(this + 0x20);
  uVar1 = ___modsi3(*(int *)(this + 0x40) + 2,*(undefined4 *)(this + 0x3c));
  *(undefined2 *)(iVar2 * 2 + iVar5) = uVar1;
  *(int *)(this + 0x24) = iVar4 + 3;
  iVar2 = ___modsi3(iVar4 + 3,*(undefined4 *)(this + 0x28));
  iVar5 = *(int *)(this + 0x20);
  uVar1 = ___modsi3(*(undefined4 *)(this + 0x40),*(undefined4 *)(this + 0x3c));
  *(undefined2 *)(iVar2 * 2 + iVar5) = uVar1;
  *(int *)(this + 0x24) = iVar4 + 4;
  iVar2 = ___modsi3(iVar4 + 4,*(undefined4 *)(this + 0x28));
  iVar5 = *(int *)(this + 0x20);
  uVar1 = ___modsi3(*(int *)(this + 0x40) + 2,*(undefined4 *)(this + 0x3c));
  *(undefined2 *)(iVar2 * 2 + iVar5) = uVar1;
  *(int *)(this + 0x24) = iVar4 + 5;
  iVar2 = ___modsi3(iVar4 + 5,*(undefined4 *)(this + 0x28));
  iVar5 = *(int *)(this + 0x20);
  uVar1 = ___modsi3(*(int *)(this + 0x40) + 3,*(undefined4 *)(this + 0x3c));
  *(undefined2 *)(iVar2 * 2 + iVar5) = uVar1;
  *(int *)(this + 0x24) = iVar4 + 6;
  *(int *)(this + 0x40) = *(int *)(this + 0x40) + 4;
  return;
}
