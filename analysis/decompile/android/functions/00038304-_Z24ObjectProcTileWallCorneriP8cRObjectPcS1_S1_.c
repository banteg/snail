/*
 * mangled: _Z24ObjectProcTileWallCorneriP8cRObjectPcS1_S1_
 * demangled: ObjectProcTileWallCorner(int, cRObject*, char*, char*, char*)
 * address: 00038304
 * size: 576
 */

/* ObjectProcTileWallCorner(int, cRObject*, char*, char*, char*) */

void ObjectProcTileWallCorner
               (int param_1,cRObject *param_2,char *param_3,char *param_4,char *param_5)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  float *pfVar6;
  uint in_fpscr;
  uint uVar7;
  uint uVar8;
  float fVar9;
  float fVar10;

  ObjectProcTileWall(param_2,param_3,param_4,param_5);
  iVar5 = *(int *)(param_2 + 0xa4);
  iVar3 = *(int *)(param_2 + 200);
  pfVar6 = (float *)(iVar5 + *(int *)(&ObjectProcWallCornerData + param_1 * 0x20) * 0xc);
  uVar8 = in_fpscr & 0xfffffff | (uint)(*pfVar6 < 0.0) << 0x1f;
  if (SUB41(uVar8 >> 0x1f,0)) {
    fVar9 = 0.3;
  }
  else {
    uVar8 = in_fpscr & 0xfffffff | (uint)(*pfVar6 == 0.0) << 0x1e;
    fVar9 = (float)VectorSignedToFloat((uint)!SUB41(uVar8 >> 0x1e,0),(byte)(uVar8 >> 0x16) & 3);
    fVar9 = fVar9 * -0.3;
  }
  fVar10 = pfVar6[2];
  uVar7 = uVar8 & 0xfffffff | (uint)(fVar10 < 0.0) << 0x1f;
  *(float *)(iVar5 + *(int *)(&ObjectProcWallCornerData + param_1 * 0x20) * 0xc) = fVar9;
  if (SUB41(uVar7 >> 0x1f,0)) {
    fVar9 = 0.3;
  }
  else {
    uVar7 = uVar8 & 0xfffffff | (uint)(fVar10 == 0.0) << 0x1e;
    fVar9 = (float)VectorSignedToFloat((uint)!SUB41(uVar7 >> 0x1e,0),(byte)(uVar7 >> 0x16) & 3);
    fVar9 = fVar9 * -0.3;
  }
  pfVar6[2] = fVar9;
  pfVar6 = (float *)(iVar5 + *(int *)(&DAT_0009b944 + param_1 * 0x20) * 0xc);
  uVar8 = uVar7 & 0xfffffff | (uint)(*pfVar6 < 0.0) << 0x1f;
  if (SUB41(uVar8 >> 0x1f,0)) {
    fVar9 = 0.3;
  }
  else {
    uVar8 = uVar7 & 0xfffffff | (uint)(*pfVar6 == 0.0) << 0x1e;
    fVar9 = (float)VectorSignedToFloat((uint)!SUB41(uVar8 >> 0x1e,0),(byte)(uVar8 >> 0x16) & 3);
    fVar9 = fVar9 * -0.3;
  }
  fVar10 = pfVar6[2];
  uVar7 = uVar8 & 0xfffffff | (uint)(fVar10 < 0.0) << 0x1f;
  *(float *)(iVar5 + *(int *)(&DAT_0009b944 + param_1 * 0x20) * 0xc) = fVar9;
  if (SUB41(uVar7 >> 0x1f,0)) {
    fVar9 = 0.3;
  }
  else {
    uVar7 = uVar8 & 0xfffffff | (uint)(fVar10 == 0.0) << 0x1e;
    fVar9 = (float)VectorSignedToFloat((uint)!SUB41(uVar7 >> 0x1e,0),(byte)(uVar7 >> 0x16) & 3);
    fVar9 = fVar9 * -0.3;
  }
  pfVar6[2] = fVar9;
  pfVar6 = (float *)(iVar5 + *(int *)(&DAT_0009b94c + param_1 * 0x20) * 0xc);
  uVar8 = uVar7 & 0xfffffff | (uint)(*pfVar6 < 0.0) << 0x1f;
  if (SUB41(uVar8 >> 0x1f,0)) {
    fVar9 = 0.3;
  }
  else {
    uVar8 = uVar7 & 0xfffffff | (uint)(*pfVar6 == 0.0) << 0x1e;
    fVar9 = (float)VectorSignedToFloat((uint)!SUB41(uVar8 >> 0x1e,0),(byte)(uVar8 >> 0x16) & 3);
    fVar9 = fVar9 * -0.3;
  }
  fVar10 = pfVar6[2];
  *(float *)(iVar5 + *(int *)(&DAT_0009b94c + param_1 * 0x20) * 0xc) = fVar9;
  if (0.0 <= fVar10) {
    uVar8 = uVar8 & 0xfffffff | (uint)(fVar10 == 0.0) << 0x1e;
    fVar9 = (float)VectorSignedToFloat((uint)!SUB41(uVar8 >> 0x1e,0),(byte)(uVar8 >> 0x16) & 3);
    fVar9 = fVar9 * -0.3;
  }
  else {
    fVar9 = 0.3;
  }
  pfVar6[2] = fVar9;
  if ((param_1 & 1U) != 0) {
    uVar1 = *(undefined2 *)(iVar3 + 0x62);
    *(undefined2 *)(iVar3 + 0x62) = *(undefined2 *)(iVar3 + 100);
    uVar2 = *(undefined2 *)(iVar3 + 0x68);
    *(undefined2 *)(iVar3 + 100) = *(undefined2 *)(iVar3 + 0x66);
    *(undefined2 *)(iVar3 + 0x68) = uVar1;
    *(undefined2 *)(iVar3 + 0x66) = uVar2;
  }
  iVar5 = iVar3 + *(int *)(&DAT_0009b958 + param_1 * 0x20) * 0x30;
  iVar3 = iVar3 + *(int *)(&DAT_0009b954 + param_1 * 0x20) * 0x30;
  uVar4 = *(undefined4 *)(iVar3 + 0xc);
  *(undefined4 *)(iVar3 + 0xc) = *(undefined4 *)(iVar5 + 0xc);
  *(undefined4 *)(iVar5 + 0xc) = uVar4;
  return;
}
