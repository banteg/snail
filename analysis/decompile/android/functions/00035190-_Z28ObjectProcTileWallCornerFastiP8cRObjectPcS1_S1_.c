/*
 * mangled: _Z28ObjectProcTileWallCornerFastiP8cRObjectPcS1_S1_
 * demangled: ObjectProcTileWallCornerFast(int, cRObject*, char*, char*, char*)
 * address: 00035190
 * size: 544
 */

/* ObjectProcTileWallCornerFast(int, cRObject*, char*, char*, char*) */

void ObjectProcTileWallCornerFast
               (int param_1,cRObject *param_2,char *param_3,char *param_4,char *param_5)

{
  undefined2 uVar1;
  undefined2 uVar2;
  byte bVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  float *pfVar8;
  uint in_fpscr;
  uint uVar9;
  float fVar10;
  float fVar11;

  ObjectProcTileWallFast(param_2,param_3,param_4,param_5);
  iVar6 = *(int *)(param_2 + 0xa4);
  iVar7 = *(int *)(param_2 + 200);
  iVar4 = *(int *)(ObjectProcWallCornerFastData + param_1 * 0x10);
  pfVar8 = (float *)(iVar6 + iVar4 * 0xc);
  in_fpscr = in_fpscr & 0xfffffff;
  if (0.0 <= *pfVar8) {
    uVar9 = in_fpscr | (uint)(*pfVar8 == 0.0) << 0x1e;
    fVar11 = (float)VectorSignedToFloat((uint)!SUB41(uVar9 >> 0x1e,0),(byte)(uVar9 >> 0x16) & 3);
    fVar10 = pfVar8[2];
    in_fpscr = in_fpscr | (uint)(fVar10 < 0.0) << 0x1f;
    *(float *)(iVar6 + iVar4 * 0xc) = fVar11 * -0.3;
    bVar3 = (byte)(in_fpscr >> 0x18);
  }
  else {
    fVar10 = pfVar8[2];
    in_fpscr = in_fpscr | (uint)(fVar10 < 0.0) << 0x1f;
    *(undefined4 *)(iVar6 + iVar4 * 0xc) = 0x3e99999a;
    bVar3 = (byte)(in_fpscr >> 0x18);
  }
  if ((bool)(bVar3 >> 7)) {
    fVar10 = 0.3;
  }
  else {
    in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar10 == 0.0) << 0x1e;
    fVar10 = (float)VectorSignedToFloat((uint)!SUB41(in_fpscr >> 0x1e,0),
                                        (byte)(in_fpscr >> 0x16) & 3);
    fVar10 = fVar10 * -0.3;
  }
  pfVar8[2] = fVar10;
  pfVar8 = (float *)(iVar6 + *(int *)(ObjectProcWallCornerFastData + param_1 * 0x10 + 4) * 0xc);
  uVar9 = in_fpscr & 0xfffffff | (uint)(*pfVar8 < 0.0) << 0x1f;
  if (SUB41(uVar9 >> 0x1f,0)) {
    fVar10 = 0.3;
  }
  else {
    uVar9 = in_fpscr & 0xfffffff | (uint)(*pfVar8 == 0.0) << 0x1e;
    fVar10 = (float)VectorSignedToFloat((uint)!SUB41(uVar9 >> 0x1e,0),(byte)(uVar9 >> 0x16) & 3);
    fVar10 = fVar10 * -0.3;
  }
  fVar11 = pfVar8[2];
  *(float *)(iVar6 + *(int *)(ObjectProcWallCornerFastData + param_1 * 0x10 + 4) * 0xc) = fVar10;
  if (0.0 <= fVar11) {
    uVar9 = uVar9 & 0xfffffff | (uint)(fVar11 == 0.0) << 0x1e;
    fVar10 = (float)VectorSignedToFloat((uint)!SUB41(uVar9 >> 0x1e,0),(byte)(uVar9 >> 0x16) & 3);
    fVar10 = fVar10 * -0.3;
  }
  else {
    fVar10 = 0.3;
  }
  pfVar8[2] = fVar10;
  if ((param_1 & 1U) != 0) {
    uVar1 = *(undefined2 *)(iVar7 + 0x62);
    *(undefined2 *)(iVar7 + 0x62) = *(undefined2 *)(iVar7 + 100);
    *(undefined2 *)(iVar7 + 100) = *(undefined2 *)(iVar7 + 0x66);
    uVar2 = *(undefined2 *)(iVar7 + 0x68);
    *(undefined2 *)(iVar7 + 0x68) = uVar1;
    *(undefined2 *)(iVar7 + 0x66) = uVar2;
    iVar6 = *(int *)(ObjectProcWallCornerFastData + param_1 * 0x10 + 8);
    iVar4 = *(int *)(ObjectProcWallCornerFastData + param_1 * 0x10 + 0xc);
    uVar1 = *(undefined2 *)(iVar7 + 2);
    *(undefined2 *)(iVar7 + 2) = *(undefined2 *)(iVar7 + 4);
    uVar2 = *(undefined2 *)(iVar7 + 8);
    iVar6 = iVar7 + iVar6 * 0x30;
    *(undefined2 *)(iVar7 + 8) = uVar1;
    *(undefined2 *)(iVar7 + 4) = *(undefined2 *)(iVar7 + 6);
    *(undefined2 *)(iVar7 + 6) = uVar2;
    iVar7 = iVar7 + iVar4 * 0x30;
    uVar5 = *(undefined4 *)(iVar6 + 0xc);
    *(undefined4 *)(iVar6 + 0xc) = *(undefined4 *)(iVar7 + 0xc);
    *(undefined4 *)(iVar7 + 0xc) = uVar5;
    return;
  }
  iVar4 = iVar7 + *(int *)(ObjectProcWallCornerFastData + param_1 * 0x10 + 0xc) * 0x30;
  iVar7 = iVar7 + *(int *)(ObjectProcWallCornerFastData + param_1 * 0x10 + 8) * 0x30;
  uVar5 = *(undefined4 *)(iVar7 + 0xc);
  *(undefined4 *)(iVar7 + 0xc) = *(undefined4 *)(iVar4 + 0xc);
  *(undefined4 *)(iVar4 + 0xc) = uVar5;
  return;
}
