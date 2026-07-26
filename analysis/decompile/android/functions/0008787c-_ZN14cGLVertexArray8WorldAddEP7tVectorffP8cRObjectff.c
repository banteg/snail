/*
 * mangled: _ZN14cGLVertexArray8WorldAddEP7tVectorffP8cRObjectff
 * demangled: cGLVertexArray::WorldAdd(tVector*, float, float, cRObject*, float, float)
 * address: 0008787c
 * size: 1068
 */

/* cGLVertexArray::WorldAdd(tVector*, float, float, cRObject*, float, float) */

void __thiscall
cGLVertexArray::WorldAdd
          (cGLVertexArray *this,tVector *param_1,float param_2,float param_3,cRObject *param_4,
          float param_5,float param_6)

{
  ushort uVar1;
  undefined2 extraout_r1;
  undefined2 extraout_r1_00;
  undefined2 extraout_r1_01;
  undefined2 extraout_r1_02;
  int extraout_r1_03;
  int extraout_r1_04;
  int extraout_r1_05;
  int extraout_r1_06;
  undefined4 uVar2;
  int extraout_r1_07;
  int extraout_r1_08;
  int extraout_r1_09;
  int extraout_r1_10;
  int extraout_r1_11;
  int extraout_r1_12;
  float in_r3;
  float *pfVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  int in_stack_00000000;
  float in_stack_00000004;
  float in_stack_00000008;

  fVar11 = *(float *)(param_1 + 8);
  uVar6 = *(undefined4 *)(this + 0x3c);
  fVar13 = *(float *)param_1;
  iVar8 = *(int *)(this + 0x40);
  iVar5 = *(int *)(in_stack_00000000 + 200);
  iVar9 = *(int *)(in_stack_00000000 + 0xa4);
  iVar7 = *(int *)(this + 8);
  fVar12 = *(float *)(param_1 + 4);
  pfVar3 = (float *)(iVar9 + (uint)*(ushort *)(iVar5 + 2) * 0xc);
  fVar14 = pfVar3[2];
  fVar15 = *pfVar3;
  fVar16 = pfVar3[1];
  __aeabi_idivmod(iVar8,uVar6);
  iVar4 = iVar7 + extraout_r1_03 * 10;
  *(short *)(iVar7 + extraout_r1_03 * 10) = (short)(int)((fVar13 + fVar15 + 0.0) * 128.0);
  *(short *)(iVar4 + 2) = (short)(int)((in_stack_00000004 * 0.25 + fVar12 + fVar16) * 128.0);
  *(short *)(iVar4 + 4) =
       (short)(int)(((in_stack_00000004 + fVar11 + fVar14) - in_stack_00000008) * 128.0);
  *(short *)(iVar4 + 6) = (short)(int)(((float)param_4 + *(float *)(iVar5 + 0x10)) * 128.0);
  *(short *)(iVar4 + 8) = (short)(int)((in_r3 + *(float *)(iVar5 + 0x14)) * 128.0);
  pfVar3 = (float *)(iVar9 + (uint)*(ushort *)(iVar5 + 4) * 0xc);
  fVar14 = pfVar3[2];
  fVar15 = *pfVar3;
  fVar16 = pfVar3[1];
  __aeabi_idivmod(iVar8 + 1,uVar6);
  iVar4 = iVar7 + extraout_r1_04 * 10;
  *(short *)(iVar4 + 2) = (short)(int)((in_stack_00000004 * 0.25 + fVar12 + fVar16) * 128.0);
  *(short *)(iVar7 + extraout_r1_04 * 10) = (short)(int)((fVar13 + fVar15 + 0.0) * 128.0);
  *(short *)(iVar4 + 4) =
       (short)(int)(((in_stack_00000004 + fVar11 + fVar14) - in_stack_00000008) * 128.0);
  *(short *)(iVar4 + 6) = (short)(int)(((float)param_4 + *(float *)(iVar5 + 0x18)) * 128.0);
  *(short *)(iVar4 + 8) = (short)(int)((in_r3 + *(float *)(iVar5 + 0x1c)) * 128.0);
  uVar1 = *(ushort *)(iVar5 + 6);
  iVar4 = iVar9 + (uint)uVar1 * 0xc;
  fVar15 = *(float *)(iVar4 + 8);
  fVar14 = *(float *)(iVar4 + 4);
  __aeabi_idivmod(iVar8 + 2,uVar6);
  iVar4 = iVar7 + extraout_r1_05 * 10;
  *(short *)(iVar7 + extraout_r1_05 * 10) =
       (short)(int)((fVar13 + *(float *)(iVar9 + (uint)uVar1 * 0xc)) * 128.0);
  *(short *)(iVar4 + 2) = (short)(int)((fVar12 + fVar14) * 128.0);
  *(short *)(iVar4 + 4) = (short)(int)(((fVar11 + fVar15) - in_stack_00000008) * 128.0);
  *(short *)(iVar4 + 6) = (short)(int)(((float)param_4 + *(float *)(iVar5 + 0x20)) * 128.0);
  *(short *)(iVar4 + 8) = (short)(int)((in_r3 + *(float *)(iVar5 + 0x24)) * 128.0);
  uVar1 = *(ushort *)(iVar5 + 8);
  iVar4 = iVar9 + (uint)uVar1 * 0xc;
  fVar14 = *(float *)(iVar4 + 8);
  fVar15 = *(float *)(iVar4 + 4);
  __aeabi_idivmod(iVar8 + 3,uVar6);
  iVar10 = *(int *)(this + 0x24);
  uVar2 = *(undefined4 *)(this + 0x28);
  iVar4 = iVar7 + extraout_r1_06 * 10;
  *(short *)(iVar7 + extraout_r1_06 * 10) =
       (short)(int)((fVar13 + *(float *)(iVar9 + (uint)uVar1 * 0xc)) * 128.0);
  *(short *)(iVar4 + 2) = (short)(int)((fVar12 + fVar15) * 128.0);
  *(short *)(iVar4 + 4) = (short)(int)(((fVar11 + fVar14) - in_stack_00000008) * 128.0);
  *(short *)(iVar4 + 6) = (short)(int)(((float)param_4 + *(float *)(iVar5 + 0x28)) * 128.0);
  *(short *)(iVar4 + 8) = (short)(int)((in_r3 + *(float *)(iVar5 + 0x2c)) * 128.0);
  __aeabi_idivmod(iVar10,uVar2);
  iVar4 = *(int *)(this + 0x20);
  *(int *)(this + 0x24) = iVar10 + 1;
  uVar2 = *(undefined4 *)(this + 0x28);
  *(short *)(iVar4 + extraout_r1_07 * 2) = (short)extraout_r1_03;
  __aeabi_idivmod(iVar10 + 1,uVar2);
  __aeabi_idivmod(iVar8 + 1,uVar6);
  *(int *)(this + 0x24) = iVar10 + 2;
  *(undefined2 *)(iVar4 + extraout_r1_08 * 2) = extraout_r1;
  __aeabi_idivmod(iVar10 + 2,*(undefined4 *)(this + 0x28));
  __aeabi_idivmod(iVar8 + 2,uVar6);
  *(int *)(this + 0x24) = iVar10 + 3;
  *(undefined2 *)(iVar4 + extraout_r1_09 * 2) = extraout_r1_00;
  __aeabi_idivmod(iVar10 + 3,*(undefined4 *)(this + 0x28));
  __aeabi_idivmod(iVar8,uVar6);
  *(int *)(this + 0x24) = iVar10 + 4;
  *(undefined2 *)(iVar4 + extraout_r1_10 * 2) = extraout_r1_01;
  __aeabi_idivmod(iVar10 + 4,*(undefined4 *)(this + 0x28));
  *(int *)(this + 0x24) = iVar10 + 5;
  uVar2 = *(undefined4 *)(this + 0x28);
  *(undefined2 *)(iVar4 + extraout_r1_11 * 2) = extraout_r1_00;
  __aeabi_idivmod(iVar10 + 5,uVar2);
  __aeabi_idivmod(iVar8 + 3,uVar6);
  *(int *)(this + 0x24) = iVar10 + 6;
  *(int *)(this + 0x40) = iVar8 + 4;
  *(undefined2 *)(iVar4 + extraout_r1_12 * 2) = extraout_r1_02;
  return;
}
