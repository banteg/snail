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
  float fVar2;
  undefined2 extraout_r1;
  undefined2 extraout_r1_00;
  undefined2 extraout_r1_01;
  undefined2 extraout_r1_02;
  int extraout_r1_03;
  int extraout_r1_04;
  int extraout_r1_05;
  int extraout_r1_06;
  undefined4 uVar3;
  int extraout_r1_07;
  int extraout_r1_08;
  int extraout_r1_09;
  int extraout_r1_10;
  int extraout_r1_11;
  int extraout_r1_12;
  float in_r3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  int in_stack_00000000;
  float in_stack_00000004;
  float in_stack_00000008;

  fVar2 = DAT_00087cb0;
  fVar13 = DAT_00087cac;
  fVar14 = *(float *)(param_1 + 8);
  uVar7 = *(undefined4 *)(this + 0x3c);
  fVar16 = *(float *)param_1;
  iVar9 = *(int *)(this + 0x40);
  iVar6 = *(int *)(in_stack_00000000 + 200);
  iVar10 = *(int *)(in_stack_00000000 + 0xa4);
  iVar8 = *(int *)(this + 8);
  fVar15 = *(float *)(param_1 + 4);
  fVar12 = in_stack_00000004 * DAT_00087ca8;
  pfVar4 = (float *)(iVar10 + (uint)*(ushort *)(iVar6 + 2) * 0xc);
  fVar17 = pfVar4[2];
  fVar18 = *pfVar4;
  fVar19 = pfVar4[1];
  __aeabi_idivmod(iVar9,uVar7);
  iVar5 = iVar8 + extraout_r1_03 * 10;
  *(short *)(iVar8 + extraout_r1_03 * 10) = (short)(int)((fVar16 + fVar18 + fVar13) * fVar2);
  *(short *)(iVar5 + 2) = (short)(int)((fVar12 + fVar15 + fVar19) * fVar2);
  *(short *)(iVar5 + 4) =
       (short)(int)(((in_stack_00000004 + fVar14 + fVar17) - in_stack_00000008) * fVar2);
  *(short *)(iVar5 + 6) = (short)(int)(((float)param_4 + *(float *)(iVar6 + 0x10)) * fVar2);
  *(short *)(iVar5 + 8) = (short)(int)((in_r3 + *(float *)(iVar6 + 0x14)) * fVar2);
  pfVar4 = (float *)(iVar10 + (uint)*(ushort *)(iVar6 + 4) * 0xc);
  fVar17 = pfVar4[2];
  fVar18 = *pfVar4;
  fVar19 = pfVar4[1];
  __aeabi_idivmod(iVar9 + 1,uVar7);
  iVar5 = iVar8 + extraout_r1_04 * 10;
  *(short *)(iVar5 + 2) = (short)(int)((fVar12 + fVar15 + fVar19) * fVar2);
  *(short *)(iVar8 + extraout_r1_04 * 10) = (short)(int)((fVar16 + fVar18 + fVar13) * fVar2);
  *(short *)(iVar5 + 4) =
       (short)(int)(((in_stack_00000004 + fVar14 + fVar17) - in_stack_00000008) * fVar2);
  *(short *)(iVar5 + 6) = (short)(int)(((float)param_4 + *(float *)(iVar6 + 0x18)) * fVar2);
  *(short *)(iVar5 + 8) = (short)(int)((in_r3 + *(float *)(iVar6 + 0x1c)) * fVar2);
  uVar1 = *(ushort *)(iVar6 + 6);
  iVar5 = iVar10 + (uint)uVar1 * 0xc;
  fVar12 = *(float *)(iVar5 + 8);
  fVar13 = *(float *)(iVar5 + 4);
  __aeabi_idivmod(iVar9 + 2,uVar7);
  iVar5 = iVar8 + extraout_r1_05 * 10;
  *(short *)(iVar8 + extraout_r1_05 * 10) =
       (short)(int)((fVar16 + *(float *)(iVar10 + (uint)uVar1 * 0xc)) * fVar2);
  *(short *)(iVar5 + 2) = (short)(int)((fVar15 + fVar13) * fVar2);
  *(short *)(iVar5 + 4) = (short)(int)(((fVar14 + fVar12) - in_stack_00000008) * fVar2);
  *(short *)(iVar5 + 6) = (short)(int)(((float)param_4 + *(float *)(iVar6 + 0x20)) * fVar2);
  *(short *)(iVar5 + 8) = (short)(int)((in_r3 + *(float *)(iVar6 + 0x24)) * fVar2);
  uVar1 = *(ushort *)(iVar6 + 8);
  iVar5 = iVar10 + (uint)uVar1 * 0xc;
  fVar13 = *(float *)(iVar5 + 8);
  fVar12 = *(float *)(iVar5 + 4);
  __aeabi_idivmod(iVar9 + 3,uVar7);
  iVar11 = *(int *)(this + 0x24);
  uVar3 = *(undefined4 *)(this + 0x28);
  iVar5 = iVar8 + extraout_r1_06 * 10;
  *(short *)(iVar8 + extraout_r1_06 * 10) =
       (short)(int)((fVar16 + *(float *)(iVar10 + (uint)uVar1 * 0xc)) * fVar2);
  *(short *)(iVar5 + 2) = (short)(int)((fVar15 + fVar12) * fVar2);
  *(short *)(iVar5 + 4) = (short)(int)(((fVar14 + fVar13) - in_stack_00000008) * fVar2);
  *(short *)(iVar5 + 6) = (short)(int)(((float)param_4 + *(float *)(iVar6 + 0x28)) * fVar2);
  *(short *)(iVar5 + 8) = (short)(int)((in_r3 + *(float *)(iVar6 + 0x2c)) * fVar2);
  __aeabi_idivmod(iVar11,uVar3);
  iVar5 = *(int *)(this + 0x20);
  *(int *)(this + 0x24) = iVar11 + 1;
  uVar3 = *(undefined4 *)(this + 0x28);
  *(short *)(iVar5 + extraout_r1_07 * 2) = (short)extraout_r1_03;
  __aeabi_idivmod(iVar11 + 1,uVar3);
  __aeabi_idivmod(iVar9 + 1,uVar7);
  *(int *)(this + 0x24) = iVar11 + 2;
  *(undefined2 *)(iVar5 + extraout_r1_08 * 2) = extraout_r1;
  __aeabi_idivmod(iVar11 + 2,*(undefined4 *)(this + 0x28));
  __aeabi_idivmod(iVar9 + 2,uVar7);
  *(int *)(this + 0x24) = iVar11 + 3;
  *(undefined2 *)(iVar5 + extraout_r1_09 * 2) = extraout_r1_00;
  __aeabi_idivmod(iVar11 + 3,*(undefined4 *)(this + 0x28));
  __aeabi_idivmod(iVar9,uVar7);
  *(int *)(this + 0x24) = iVar11 + 4;
  *(undefined2 *)(iVar5 + extraout_r1_10 * 2) = extraout_r1_01;
  __aeabi_idivmod(iVar11 + 4,*(undefined4 *)(this + 0x28));
  *(int *)(this + 0x24) = iVar11 + 5;
  uVar3 = *(undefined4 *)(this + 0x28);
  *(undefined2 *)(iVar5 + extraout_r1_11 * 2) = extraout_r1_00;
  __aeabi_idivmod(iVar11 + 5,uVar3);
  __aeabi_idivmod(iVar9 + 3,uVar7);
  *(int *)(this + 0x24) = iVar11 + 6;
  *(int *)(this + 0x40) = iVar9 + 4;
  *(undefined2 *)(iVar5 + extraout_r1_12 * 2) = extraout_r1_02;
  return;
}
