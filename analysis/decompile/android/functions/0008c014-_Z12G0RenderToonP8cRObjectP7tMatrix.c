/*
 * mangled: _Z12G0RenderToonP8cRObjectP7tMatrix
 * demangled: G0RenderToon(cRObject*, tMatrix*)
 * address: 0008c014
 * size: 828
 */

/* G0RenderToon(cRObject*, tMatrix*) */

void G0RenderToon(cRObject *param_1,tMatrix *param_2)

{
  int iVar1;
  ushort uVar2;
  int iVar3;
  ushort *puVar4;
  int iVar5;
  int iVar6;
  ushort *puVar7;
  int iVar8;
  tVector *ptVar9;
  float *pfVar10;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float extraout_s3;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined4 local_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 local_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 local_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 local_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  tColourSmall atStack_34 [4];

  glEnable(0xde1);
  iVar1 = cRSpriteManager::GetTextureRef((cRSpriteManager *)&gRSpriteManager,0x4f);
  G0BindTexture(iVar1);
  G0SetBlend(0);
  tColourSmall::tColourSmall(atStack_34);
  tColourSmall::Set(atStack_34,extraout_s0,extraout_s1,extraout_s2,extraout_s3);
  G0SetColour(atStack_34);
  glDepthFunc(0x203);
  local_8c = *(undefined4 *)param_2;
  uStack_88 = *(undefined4 *)(param_2 + 4);
  uStack_84 = *(undefined4 *)(param_2 + 8);
  uStack_80 = *(undefined4 *)(param_2 + 0xc);
  local_38 = *(float *)(G0Camera + 0x38) - *(float *)(param_2 + 0x38);
  local_7c = *(undefined4 *)(param_2 + 0x10);
  uStack_78 = *(undefined4 *)(param_2 + 0x14);
  uStack_74 = *(undefined4 *)(param_2 + 0x18);
  uStack_70 = *(undefined4 *)(param_2 + 0x1c);
  local_40 = *(float *)(G0Camera + 0x30) - *(float *)(param_2 + 0x30);
  local_6c = *(undefined4 *)(param_2 + 0x20);
  uStack_68 = *(undefined4 *)(param_2 + 0x24);
  uStack_64 = *(undefined4 *)(param_2 + 0x28);
  uStack_60 = *(undefined4 *)(param_2 + 0x2c);
  local_3c = *(float *)(G0Camera + 0x34) - *(float *)(param_2 + 0x34);
  local_5c = *(undefined4 *)(param_2 + 0x30);
  uStack_58 = *(undefined4 *)(param_2 + 0x34);
  uStack_54 = *(undefined4 *)(param_2 + 0x38);
  uStack_50 = *(undefined4 *)(param_2 + 0x3c);
  tMatrix::Invert((tMatrix *)&local_8c);
  tVector::Rotate((tVector *)&local_40,(tMatrix *)&local_8c);
  tVector::Magnitude((tVector *)&local_40);
  glLineWidth(0x3f800000);
  iVar1 = *(int *)(param_1 + 0xe4);
  puVar7 = *(ushort **)(param_1 + 0xe0);
  if (iVar1 < 1) {
    iVar5 = 0;
  }
  else {
    iVar6 = 0;
    iVar8 = 0;
    iVar5 = 0;
    do {
      while ((*(uint *)param_1 & 0x1000) != 0) {
        puVar4 = (ushort *)(*(int *)(param_1 + 0xe8) + iVar6);
        uVar2 = puVar4[1];
        iVar3 = *(int *)(param_1 + 0xa4) + (uint)uVar2 * 6;
        fVar11 = (float)VectorSignedToFloat((int)*(short *)(*(int *)(param_1 + 0xa4) +
                                                           (uint)uVar2 * 6),
                                            (byte)(in_fpscr >> 0x16) & 3);
        fVar12 = (float)VectorSignedToFloat((int)*(short *)(iVar3 + 2),(byte)(in_fpscr >> 0x16) & 3)
        ;
        fVar13 = (float)VectorSignedToFloat((int)*(short *)(iVar3 + 4),(byte)(in_fpscr >> 0x16) & 3)
        ;
        fVar11 = fVar11 * 0.0078125;
        fVar12 = fVar12 * 0.0078125;
        fVar13 = fVar13 * 0.0078125;
        if ((*puVar4 & 1) == 0) goto LAB_0008c214;
LAB_0008c1ac:
        *puVar7 = uVar2;
        iVar8 = iVar8 + 1;
        iVar5 = iVar5 + 1;
        iVar6 = iVar6 + 10;
        puVar7[1] = puVar4[2];
        puVar7 = puVar7 + 2;
        if (iVar1 <= iVar8) goto LAB_0008c2ac;
      }
      puVar4 = (ushort *)(*(int *)(param_1 + 0xe8) + iVar6);
      uVar2 = puVar4[1];
      pfVar10 = (float *)(*(int *)(param_1 + 0xa4) + (uint)uVar2 * 0xc);
      fVar11 = *pfVar10;
      fVar12 = pfVar10[1];
      fVar13 = pfVar10[2];
      if ((*puVar4 & 1) != 0) goto LAB_0008c1ac;
LAB_0008c214:
      local_4c = local_40 - fVar11;
      iVar8 = iVar8 + 1;
      ptVar9 = *(tVector **)(*(int *)(param_1 + 0xcc) + (uint)puVar4[4] * 4);
      local_48 = local_3c - fVar12;
      local_44 = local_38 - fVar13;
      fVar11 = (float)tVector::Dot((tVector *)&local_4c,
                                   *(tVector **)(*(int *)(param_1 + 0xcc) + (uint)puVar4[3] * 4));
      fVar12 = (float)tVector::Dot((tVector *)&local_4c,ptVar9);
      in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar11 * fVar12 < 0.01) << 0x1f;
      if (SUB41(in_fpscr >> 0x1f,0)) {
        iVar3 = *(int *)(param_1 + 0xe8);
        iVar5 = iVar5 + 1;
        iVar1 = *(int *)(param_1 + 0xe4);
        *puVar7 = *(ushort *)(iVar3 + iVar6 + 2);
        puVar7[1] = *(ushort *)(iVar3 + iVar6 + 4);
        puVar7 = puVar7 + 2;
      }
      else {
        iVar1 = *(int *)(param_1 + 0xe4);
      }
      iVar6 = iVar6 + 10;
    } while (iVar8 < iVar1);
LAB_0008c2ac:
    iVar5 = iVar5 << 1;
  }
  glDepthRangef(0xbb83126f,0x3f7ef9db);
  glEnableClientState(0x8074);
  glDisableClientState(0x8078);
  if ((*(uint *)param_1 & 0x1000) == 0) {
    glVertexPointer(3,0x1406,0,*(undefined4 *)(param_1 + 0xa4));
  }
  else {
    glVertexPointer(3,0x1402,0,*(undefined4 *)(param_1 + 0xa4));
  }
  glDrawElements(1,iVar5,0x1403,*(undefined4 *)(param_1 + 0xe0));
  glDisableClientState(0x8074);
  glEnableClientState(0x8078);
  glDepthRangef(0,0x3f800000);
  G0ResetColour();
  glEnable(0xde1);
  return;
}
