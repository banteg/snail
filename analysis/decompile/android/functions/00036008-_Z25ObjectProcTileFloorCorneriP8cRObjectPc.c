/*
 * mangled: _Z25ObjectProcTileFloorCorneriP8cRObjectPc
 * demangled: ObjectProcTileFloorCorner(int, cRObject*, char*)
 * address: 00036008
 * size: 376
 */

/* ObjectProcTileFloorCorner(int, cRObject*, char*) */

void ObjectProcTileFloorCorner(int param_1,cRObject *param_2,char *param_3)

{
  uint uVar1;
  byte bVar2;
  float *pfVar3;
  int iVar4;
  int iVar5;
  uint in_fpscr;
  float fVar6;
  float fVar7;

  ObjectProcTileFloor(param_2,param_3);
  iVar5 = *(int *)(param_2 + 0xa4);
  iVar4 = *(int *)(ObjectProcFloorCornerData + param_1 * 0x10);
  pfVar3 = (float *)(iVar5 + iVar4 * 0xc);
  in_fpscr = in_fpscr & 0xfffffff;
  if (0.0 <= *pfVar3) {
    uVar1 = in_fpscr | (uint)(*pfVar3 == 0.0) << 0x1e;
    fVar6 = (float)VectorSignedToFloat((uint)!SUB41(uVar1 >> 0x1e,0),(byte)(uVar1 >> 0x16) & 3);
    fVar7 = pfVar3[2];
    in_fpscr = in_fpscr | (uint)(fVar7 < 0.0) << 0x1f;
    *(float *)(iVar5 + iVar4 * 0xc) = fVar6 * 0.1;
    bVar2 = (byte)(in_fpscr >> 0x18);
  }
  else {
    fVar7 = pfVar3[2];
    in_fpscr = in_fpscr | (uint)(fVar7 < 0.0) << 0x1f;
    *(undefined4 *)(iVar5 + iVar4 * 0xc) = 0xbdcccccd;
    bVar2 = (byte)(in_fpscr >> 0x18);
  }
  if ((bool)(bVar2 >> 7)) {
    fVar7 = -0.1;
  }
  else {
    in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar7 == 0.0) << 0x1e;
    fVar7 = (float)VectorSignedToFloat((uint)!SUB41(in_fpscr >> 0x1e,0),(byte)(in_fpscr >> 0x16) & 3
                                      );
    fVar7 = fVar7 * 0.1;
  }
  pfVar3[2] = fVar7;
  iVar4 = *(int *)(ObjectProcFloorCornerData + param_1 * 0x10 + 8);
  pfVar3 = (float *)(iVar5 + iVar4 * 0xc);
  in_fpscr = in_fpscr & 0xfffffff;
  if (0.0 <= *pfVar3) {
    uVar1 = in_fpscr | (uint)(*pfVar3 == 0.0) << 0x1e;
    fVar6 = (float)VectorSignedToFloat((uint)!SUB41(uVar1 >> 0x1e,0),(byte)(uVar1 >> 0x16) & 3);
    fVar7 = pfVar3[2];
    in_fpscr = in_fpscr | (uint)(fVar7 < 0.0) << 0x1f;
    *(float *)(iVar5 + iVar4 * 0xc) = fVar6 * 0.3;
    bVar2 = (byte)(in_fpscr >> 0x18);
  }
  else {
    fVar7 = pfVar3[2];
    in_fpscr = in_fpscr | (uint)(fVar7 < 0.0) << 0x1f;
    *(undefined4 *)(iVar5 + iVar4 * 0xc) = 0xbe99999a;
    bVar2 = (byte)(in_fpscr >> 0x18);
  }
  if ((bool)(bVar2 >> 7)) {
    pfVar3[2] = -0.3;
    return;
  }
  uVar1 = in_fpscr & 0xfffffff | (uint)(fVar7 == 0.0) << 0x1e;
  fVar7 = (float)VectorSignedToFloat((uint)!SUB41(uVar1 >> 0x1e,0),(byte)(uVar1 >> 0x16) & 3);
  pfVar3[2] = fVar7 * 0.3;
  return;
}
