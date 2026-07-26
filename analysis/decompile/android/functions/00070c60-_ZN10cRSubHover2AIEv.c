/*
 * mangled: _ZN10cRSubHover2AIEv
 * demangled: cRSubHover::AI()
 * address: 00070c60
 * size: 572
 */

/* cRSubHover::AI() */

void cRSubHover::AI(void)

{
  bool bVar1;
  uint uVar2;
  byte bVar3;
  float fVar4;
  undefined4 uVar5;
  tVector *in_r0;
  int iVar6;
  uint *puVar7;
  int iVar8;
  uint in_fpscr;
  float in_s0;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float fVar9;
  float fVar10;
  float fVar11;

  fVar11 = DAT_00070e9c;
  iVar8 = DAT_00070ec4 + 0x70c80;
  if (*(int *)(in_r0 + 0xc) == 1) {
    fVar10 = *(float *)in_r0 + *(float *)(in_r0 + 4);
    bVar1 = NAN(DAT_00070e9c);
    uVar2 = in_fpscr & 0xfffffff | (uint)(fVar10 < DAT_00070e9c) << 0x1f |
            (uint)(fVar10 == DAT_00070e9c) << 0x1e;
    *(float *)in_r0 = fVar10;
    iVar6 = DAT_00070ec8;
    fVar4 = DAT_00070ea4;
    bVar3 = (byte)(uVar2 >> 0x18);
    if (((bool)(bVar3 >> 6 & 1) || (bool)(bVar3 >> 7) != (NAN(fVar10) || bVar1)) &&
       (fVar9 = (float)VectorSignedToFloat(*(int *)(*(int *)(in_r0 + 0x200) + 0x78) + -5,
                                           (byte)(uVar2 >> 0x16) & 3),
       *(float *)(*(int *)(in_r0 + 0x10) + 100) <= fVar9)) {
      if (fVar10 < DAT_00070ea0) {
        *(float *)(in_r0 + 0x210) = fVar10 / DAT_00070ea0;
      }
      else if (fVar10 <= DAT_00070ea4) {
        *(float *)(in_r0 + 0x210) = fVar11;
        iVar6 = **(int **)(iVar8 + iVar6);
        puVar7 = (uint *)cRSubGame::RowFromPos
                                   (iVar6 + 0x718a0,*(undefined4 *)(iVar6 + 0x813c0),
                                    *(undefined4 *)(iVar6 + 0x813c4),
                                    *(undefined4 *)(iVar6 + 0x813c8));
        iVar6 = DAT_00070ecc;
        in_s0 = extraout_s0_02;
        if ((*puVar7 & 0x8000) != 0) {
          *(float *)in_r0 = fVar4;
          in_s0 = (float)wprintf((char *)(iVar8 + iVar6));
        }
      }
      else {
        *(float *)(in_r0 + 0x210) = (fVar11 - fVar10) / DAT_00070ea8;
        if (fVar10 - *(float *)(in_r0 + 4) <= fVar4) {
          cRSnail::SetJetPack((cRSnail *)(**(int **)(iVar8 + DAT_00070ec8) + 0x83b64),0);
          in_s0 = (float)JetUnInit((cRSubHover *)in_r0);
        }
      }
      fVar4 = DAT_00070eb0;
      fVar11 = DAT_00070e9c;
      fVar10 = (float)Cos(in_s0);
      fVar11 = fVar11 - (DAT_00070eb8 + fVar10 * DAT_00070eb8);
      *(float *)(in_r0 + 0x210) = fVar11;
      fVar10 = (float)Sin(extraout_s0);
      fVar9 = *(float *)(in_r0 + 0x210);
      *(float *)(in_r0 + 0x14) = fVar11 * fVar10 * fVar4;
      fVar11 = (float)Sin(extraout_s0_00);
      *(undefined4 *)(in_r0 + 0x1c) = DAT_00070ec0;
      *(undefined4 *)(in_r0 + 0x20c) = *(undefined4 *)(in_r0 + 0x210);
      *(float *)(in_r0 + 0x18) = fVar9 + fVar9 * fVar11 * fVar4;
      Hover(in_r0,extraout_s0_01);
      return;
    }
    End((cRSubHover *)in_r0);
    if (*(float *)in_r0 <= DAT_00070ea4) {
      cRSnail::SetJetPack((cRSnail *)(**(int **)(iVar8 + DAT_00070ec8) + 0x83b64),0);
    }
    uVar5 = DAT_00070ec0;
    *(undefined4 *)(in_r0 + 0x14) = DAT_00070ec0;
    *(undefined4 *)(in_r0 + 0x1c) = uVar5;
    *(undefined4 *)(in_r0 + 0x18) = uVar5;
    *(undefined4 *)(in_r0 + 0xc) = 0;
  }
  return;
}
