/*
 * mangled: _Z28ObjectProcTileWallEdgeCorneriP8cRObjectPcS1_S1_
 * demangled: ObjectProcTileWallEdgeCorner(int, cRObject*, char*, char*, char*)
 * address: 000380e0
 * size: 532
 */

/* ObjectProcTileWallEdgeCorner(int, cRObject*, char*, char*, char*) */

void ObjectProcTileWallEdgeCorner
               (int param_1,cRObject *param_2,char *param_3,char *param_4,char *param_5)

{
  byte bVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  uint in_fpscr;
  uint uVar5;
  uint uVar6;
  float fVar7;
  float fVar8;

  ObjectProcTileWall(param_2,param_3,param_4,param_5);
  iVar4 = *(int *)(param_2 + 0xa4);
  iVar3 = *(int *)(&ObjectProcWallCornerData + param_1 * 0x20);
  pfVar2 = (float *)(iVar4 + iVar3 * 0xc);
  in_fpscr = in_fpscr & 0xfffffff;
  if (0.0 <= *pfVar2) {
    uVar5 = in_fpscr | (uint)(*pfVar2 == 0.0) << 0x1e;
    fVar8 = (float)VectorSignedToFloat((uint)!SUB41(uVar5 >> 0x1e,0),(byte)(uVar5 >> 0x16) & 3);
    fVar7 = pfVar2[2];
    in_fpscr = in_fpscr | (uint)(fVar7 < 0.0) << 0x1f;
    *(float *)(iVar4 + iVar3 * 0xc) = fVar8 * 0.3;
    bVar1 = (byte)(in_fpscr >> 0x18);
  }
  else {
    fVar7 = pfVar2[2];
    in_fpscr = in_fpscr | (uint)(fVar7 < 0.0) << 0x1f;
    *(undefined4 *)(iVar4 + iVar3 * 0xc) = 0xbe99999a;
    bVar1 = (byte)(in_fpscr >> 0x18);
  }
  if ((bool)(bVar1 >> 7)) {
    fVar7 = -0.3;
  }
  else {
    in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar7 == 0.0) << 0x1e;
    fVar7 = (float)VectorSignedToFloat((uint)!SUB41(in_fpscr >> 0x1e,0),(byte)(in_fpscr >> 0x16) & 3
                                      );
    fVar7 = fVar7 * 0.3;
  }
  pfVar2[2] = fVar7;
  pfVar2 = (float *)(iVar4 + *(int *)(&DAT_0009b944 + param_1 * 0x20) * 0xc);
  uVar5 = in_fpscr & 0xfffffff | (uint)(*pfVar2 < 0.0) << 0x1f;
  if (SUB41(uVar5 >> 0x1f,0)) {
    fVar7 = -0.3;
  }
  else {
    uVar5 = in_fpscr & 0xfffffff | (uint)(*pfVar2 == 0.0) << 0x1e;
    fVar7 = (float)VectorSignedToFloat((uint)!SUB41(uVar5 >> 0x1e,0),(byte)(uVar5 >> 0x16) & 3);
    fVar7 = fVar7 * 0.3;
  }
  fVar8 = pfVar2[2];
  uVar6 = uVar5 & 0xfffffff | (uint)(fVar8 < 0.0) << 0x1f;
  *(float *)(iVar4 + *(int *)(&DAT_0009b944 + param_1 * 0x20) * 0xc) = fVar7;
  if (SUB41(uVar6 >> 0x1f,0)) {
    fVar7 = -0.3;
  }
  else {
    uVar6 = uVar5 & 0xfffffff | (uint)(fVar8 == 0.0) << 0x1e;
    fVar7 = (float)VectorSignedToFloat((uint)!SUB41(uVar6 >> 0x1e,0),(byte)(uVar6 >> 0x16) & 3);
    fVar7 = fVar7 * 0.3;
  }
  pfVar2[2] = fVar7;
  iVar3 = *(int *)(&DAT_0009b94c + param_1 * 0x20);
  pfVar2 = (float *)(iVar4 + iVar3 * 0xc);
  uVar6 = uVar6 & 0xfffffff;
  if (0.0 <= *pfVar2) {
    uVar5 = uVar6 | (uint)(*pfVar2 == 0.0) << 0x1e;
    fVar8 = (float)VectorSignedToFloat((uint)!SUB41(uVar5 >> 0x1e,0),(byte)(uVar5 >> 0x16) & 3);
    fVar7 = pfVar2[2];
    uVar6 = uVar6 | (uint)(fVar7 < 0.0) << 0x1f;
    *(float *)(iVar4 + iVar3 * 0xc) = fVar8 * 0.3;
    bVar1 = (byte)(uVar6 >> 0x18);
  }
  else {
    fVar7 = pfVar2[2];
    uVar6 = uVar6 | (uint)(fVar7 < 0.0) << 0x1f;
    *(undefined4 *)(iVar4 + iVar3 * 0xc) = 0xbe99999a;
    bVar1 = (byte)(uVar6 >> 0x18);
  }
  if ((bool)(bVar1 >> 7)) {
    pfVar2[2] = -0.3;
    return;
  }
  uVar5 = uVar6 & 0xfffffff | (uint)(fVar7 == 0.0) << 0x1e;
  fVar7 = (float)VectorSignedToFloat((uint)!SUB41(uVar5 >> 0x1e,0),(byte)(uVar5 >> 0x16) & 3);
  pfVar2[2] = fVar7 * 0.3;
  return;
}
