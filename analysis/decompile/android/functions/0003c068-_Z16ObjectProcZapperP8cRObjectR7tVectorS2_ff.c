/*
 * mangled: _Z16ObjectProcZapperP8cRObjectR7tVectorS2_ff
 * demangled: ObjectProcZapper(cRObject*, tVector&, tVector&, float, float)
 * address: 0003c068
 * size: 636
 */

/* ObjectProcZapper(cRObject*, tVector&, tVector&, float, float) */

void ObjectProcZapper(cRObject *param_1,tVector *param_2,tVector *param_3,float param_4,
                     float param_5)

{
  uint uVar1;
  byte bVar2;
  float fVar3;
  undefined4 uVar4;
  float in_r3;
  int iVar5;
  float *pfVar6;
  uint in_fpscr;
  uint uVar7;
  float fVar8;
  float fVar9;
  float in_stack_00000000;
  float local_70;
  float local_6c;
  float local_68;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  float local_50;
  float local_4c;
  float local_48;

  iVar5 = *(int *)(param_1 + 200);
  pfVar6 = *(float **)(param_1 + 0xa4);
  tMatrix::Identity((tMatrix *)&local_70);
  local_50 = *(float *)param_3 - *(float *)param_2;
  local_4c = *(float *)(param_3 + 4) - *(float *)(param_2 + 4);
  local_48 = *(float *)(param_3 + 8) - *(float *)(param_2 + 8);
  fVar3 = (float)tVector::Normalize((tVector *)&local_50);
  local_60 = 0;
  local_58 = 0;
  local_5c = 0x3f800000;
  tVector::Cross((tVector *)&local_70,(tVector *)&local_60,(tVector *)&local_50);
  tVector::Normalize((tVector *)&local_70);
  fVar8 = *(float *)(param_2 + 8);
  fVar9 = *(float *)(param_3 + 8);
  uVar1 = in_fpscr & 0xfffffff | (uint)(fVar8 < fVar9) << 0x1f | (uint)(fVar8 == fVar9) << 0x1e;
  uVar7 = uVar1 | (uint)(NAN(fVar8) || NAN(fVar9)) << 0x1c;
  bVar2 = (byte)(uVar1 >> 0x18);
  if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(uVar7 >> 0x1c) & 1)) {
    local_70 = -local_70;
    local_6c = -local_6c;
    local_68 = -local_68;
  }
  fVar8 = in_r3 * 0.5;
  pfVar6[1] = fVar3 * local_4c + fVar8 * local_6c;
  *pfVar6 = fVar3 * local_50 + fVar8 * local_70;
  fVar9 = in_r3 * -0.5;
  pfVar6[2] = fVar3 * local_48 + fVar8 * local_68;
  pfVar6[4] = fVar3 * local_4c + fVar9 * local_6c;
  pfVar6[5] = fVar3 * local_48 + fVar9 * local_68;
  pfVar6[3] = fVar3 * local_50 + fVar9 * local_70;
  pfVar6[8] = fVar8 * local_68;
  pfVar6[7] = fVar8 * local_6c;
  pfVar6[6] = fVar8 * local_70;
  pfVar6[0xb] = fVar9 * local_68;
  pfVar6[10] = fVar9 * local_6c;
  pfVar6[9] = fVar9 * local_70;
  uVar4 = gRMathRand2();
  fVar8 = (float)VectorSignedToFloat(uVar4,(byte)(uVar7 >> 0x16) & 3);
  fVar8 = fVar8 * 3.0517578e-05;
  *(float *)(iVar5 + 0x18) = fVar8;
  *(float *)(iVar5 + 0x20) = fVar8;
  fVar3 = fVar8 + 1.0 + fVar3 / in_stack_00000000;
  *(float *)(iVar5 + 0x28) = fVar3;
  *(float *)(iVar5 + 0x10) = fVar3;
  uVar4 = gRMathRand2();
  fVar3 = (float)VectorSignedToFloat(uVar4,(byte)(uVar7 >> 0x16) & 3);
  fVar3 = fVar3 * 3.0517578e-05;
  uVar1 = uVar7 & 0xfffffff | (uint)(fVar3 < 0.5) << 0x1f | (uint)(fVar3 == 0.5) << 0x1e;
  uVar7 = uVar1 | (uint)NAN(fVar3) << 0x1c;
  bVar2 = (byte)(uVar1 >> 0x18);
  if (!(bool)(bVar2 >> 6 & 1) && bVar2 >> 7 == ((byte)(uVar7 >> 0x1c) & 1)) {
    uVar4 = *(undefined4 *)(iVar5 + 0x20);
    *(undefined4 *)(iVar5 + 0x20) = *(undefined4 *)(iVar5 + 0x18);
    *(undefined4 *)(iVar5 + 0x18) = uVar4;
    uVar4 = *(undefined4 *)(iVar5 + 0x28);
    *(undefined4 *)(iVar5 + 0x28) = *(undefined4 *)(iVar5 + 0x10);
    *(undefined4 *)(iVar5 + 0x10) = uVar4;
  }
  uVar4 = gRMathRand2();
  fVar3 = (float)VectorSignedToFloat(uVar4,(byte)(uVar7 >> 0x16) & 3);
  if (0.5 < fVar3 * 3.0517578e-05) {
    uVar4 = *(undefined4 *)(iVar5 + 0x1c);
    *(undefined4 *)(iVar5 + 0x1c) = *(undefined4 *)(iVar5 + 0x14);
    *(undefined4 *)(iVar5 + 0x14) = uVar4;
    uVar4 = *(undefined4 *)(iVar5 + 0x2c);
    *(undefined4 *)(iVar5 + 0x2c) = *(undefined4 *)(iVar5 + 0x24);
    *(undefined4 *)(iVar5 + 0x24) = uVar4;
  }
  return;
}
