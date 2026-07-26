/*
 * mangled: _Z12G0RenderToonP8cRObjectP7tMatrix
 * demangled: G0RenderToon(cRObject*, tMatrix*)
 * address: 0006f190
 * size: 856
 */

/* G0RenderToon(cRObject*, tMatrix*) */

void G0RenderToon(cRObject *param_1,tMatrix *param_2)

{
  ushort *puVar1;
  ushort uVar2;
  ushort *puVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  ushort *puVar7;
  tVector *ptVar8;
  int iVar9;
  int iVar10;
  bool bVar11;
  uint in_fpscr;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined4 local_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 local_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 local_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  undefined4 local_30;
  undefined4 local_2c;

  _glDisable(0xde1);
  G0SetBlend(0);
  tColourSmall::tColourSmall((tColourSmall *)&local_2c);
  tColourSmall::Set((tColourSmall *)&local_2c,0.0,0.0,0.0,1.0);
  if (_GLColour != local_2c) {
    _GLColour = local_2c;
    _glColor4ub(local_2c._2_1_,local_2c._1_1_,local_2c & 0xff,local_2c._3_1_);
  }
  _glDepthFunc(0x203);
  local_3c = *(float *)(_G0Camera + 0x30) - *(float *)(param_2 + 0x30);
  local_38 = *(float *)(_G0Camera + 0x34) - *(float *)(param_2 + 0x34);
  local_34 = *(float *)(_G0Camera + 0x38) - *(float *)(param_2 + 0x38);
  local_88 = *(undefined4 *)param_2;
  uStack_84 = *(undefined4 *)(param_2 + 4);
  uStack_80 = *(undefined4 *)(param_2 + 8);
  uStack_7c = *(undefined4 *)(param_2 + 0xc);
  local_78 = *(undefined4 *)(param_2 + 0x10);
  uStack_74 = *(undefined4 *)(param_2 + 0x14);
  uStack_70 = *(undefined4 *)(param_2 + 0x18);
  uStack_6c = *(undefined4 *)(param_2 + 0x1c);
  local_68 = *(undefined4 *)(param_2 + 0x20);
  uStack_64 = *(undefined4 *)(param_2 + 0x24);
  uStack_60 = *(undefined4 *)(param_2 + 0x28);
  uStack_5c = *(undefined4 *)(param_2 + 0x2c);
  local_58 = *(undefined4 *)(param_2 + 0x30);
  uStack_54 = *(undefined4 *)(param_2 + 0x34);
  uStack_50 = *(undefined4 *)(param_2 + 0x38);
  uStack_4c = *(undefined4 *)(param_2 + 0x3c);
  tMatrix::Invert((tMatrix *)&local_88);
  tVector::Rotate((tVector *)&local_3c,(tMatrix *)&local_88);
  tVector::Magnitude((tVector *)&local_3c);
  _glLineWidth(0x3f800000);
  puVar7 = *(ushort **)(param_1 + 0xe0);
  if (*(int *)(param_1 + 0xe4) < 1) {
    iVar5 = 0;
  }
  else {
    iVar5 = 0;
    iVar9 = 0;
    iVar6 = 0;
    do {
      if ((*(uint *)param_1 & 0x1000) == 0) {
        puVar1 = (ushort *)(iVar6 + *(int *)(param_1 + 0xe8));
        uVar2 = puVar1[1];
        pfVar4 = (float *)((uint)uVar2 * 0xc + *(int *)(param_1 + 0xa4));
        fVar12 = pfVar4[2];
        fVar13 = pfVar4[1];
        fVar14 = *pfVar4;
        puVar3 = puVar7;
        if ((*puVar1 & 1) != 0) goto LAB_0006f31c;
LAB_0006f390:
        local_48 = local_3c - fVar14;
        local_44 = local_38 - fVar13;
        ptVar8 = *(tVector **)(*(int *)(param_1 + 0xcc) + (uint)puVar1[4] * 4);
        local_40 = local_34 - fVar12;
        fVar13 = (float)tVector::Dot((tVector *)&local_48,
                                     *(tVector **)(*(int *)(param_1 + 0xcc) + (uint)puVar1[3] * 4));
        fVar14 = (float)tVector::Dot((tVector *)&local_48,ptVar8);
        in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar13 * fVar14 < 0.01) << 0x1f;
        if (SUB41(in_fpscr >> 0x1f,0)) {
          uVar2 = *(ushort *)(iVar6 + *(int *)(param_1 + 0xe8) + 2);
          puVar3 = puVar7;
          goto LAB_0006f31c;
        }
      }
      else {
        puVar1 = (ushort *)(iVar6 + *(int *)(param_1 + 0xe8));
        uVar2 = puVar1[1];
        iVar10 = (uint)uVar2 * 6 + *(int *)(param_1 + 0xa4);
        fVar14 = (float)VectorSignedToFloat((int)*(short *)((uint)uVar2 * 6 +
                                                           *(int *)(param_1 + 0xa4)),
                                            (byte)(in_fpscr >> 0x16) & 3);
        fVar14 = fVar14 * 0.0078125;
        fVar13 = (float)VectorSignedToFloat((int)*(short *)(iVar10 + 2),(byte)(in_fpscr >> 0x16) & 3
                                           );
        bVar11 = (*puVar1 & 1) == 0;
        puVar3 = (ushort *)(uint)*puVar1;
        if (!bVar11) {
          puVar3 = puVar7;
        }
        fVar13 = fVar13 * 0.0078125;
        fVar12 = (float)VectorSignedToFloat((int)*(short *)(iVar10 + 4),(byte)(in_fpscr >> 0x16) & 3
                                           );
        fVar12 = fVar12 * 0.0078125;
        if (bVar11) goto LAB_0006f390;
LAB_0006f31c:
        *puVar3 = uVar2;
        iVar5 = iVar5 + 1;
        puVar7[1] = *(ushort *)(iVar6 + *(int *)(param_1 + 0xe8) + 4);
        puVar7 = puVar3 + 2;
      }
      iVar9 = iVar9 + 1;
      iVar6 = iVar6 + 10;
    } while (iVar9 < *(int *)(param_1 + 0xe4));
    iVar5 = iVar5 << 1;
  }
  _glDepthRangef(0xbb83126f,0x3f7ef9db);
  _glEnableClientState(&DAT_00008074);
  _glDisableClientState(&DAT_00008078);
  if ((*(uint *)param_1 & 0x1000) == 0) {
    _glVertexPointer(3,0x1406,0,*(undefined4 *)(param_1 + 0xa4));
  }
  else {
    _glVertexPointer(3,0x1402,0,*(undefined4 *)(param_1 + 0xa4));
  }
  _glDrawElements(1,iVar5,0x1403,*(undefined4 *)(param_1 + 0xe0));
  _glDisableClientState(&DAT_00008074);
  _glEnableClientState(&DAT_00008078);
  _glDepthRangef(0,0x3f800000);
  tColourSmall::tColourSmall((tColourSmall *)&local_30);
  tColourSmall::White((tColourSmall *)&local_30);
  if (_GLColour != local_30) {
    _GLColour = local_30;
    _glColor4ub(local_30._2_1_,local_30._1_1_,local_30 & 0xff,local_30._3_1_);
  }
  _glEnable(0xde1);
  return;
}
