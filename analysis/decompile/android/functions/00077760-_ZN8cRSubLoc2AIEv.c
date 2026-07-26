/*
 * mangled: _ZN8cRSubLoc2AIEv
 * demangled: cRSubLoc::AI()
 * address: 00077760
 * size: 876
 */

/* cRSubLoc::AI() */

void cRSubLoc::AI(void)

{
  uint uVar1;
  cRSubLoc cVar2;
  byte bVar3;
  int iVar4;
  cRSubLoc *in_r0;
  float fVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  uint in_fpscr;
  uint uVar9;
  float in_s0;
  float extraout_s0;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;

  iVar4 = DAT_00077afc;
  iVar7 = DAT_00077af8 + 0x77784;
  if (((byte)in_r0[0x35] & 0x20) == 0) {
    return;
  }
  piVar6 = *(int **)(iVar7 + DAT_00077afc);
  iVar8 = *piVar6;
  if (*(char *)(iVar8 + 0x718b9) != '\0') {
    return;
  }
  cVar2 = in_r0[0x30];
  if (cVar2 == (cRSubLoc)0xe) {
    fVar10 = *(float *)(iVar8 + 0x813c8);
    fVar11 = (float)VectorSignedToFloat(*(undefined4 *)(iVar8 + 0x71910),
                                        (byte)(in_fpscr >> 0x16) & 3);
    uVar1 = in_fpscr & 0xfffffff | (uint)(fVar10 < fVar11) << 0x1f |
            (uint)(fVar10 == fVar11) << 0x1e;
    uVar9 = uVar1 | (uint)(NAN(fVar10) || NAN(fVar11)) << 0x1c;
    bVar3 = (byte)(uVar1 >> 0x18);
    if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar9 >> 0x1c) & 1)) {
      fVar5 = (float)RAND(in_s0,(char *)0x42c80000);
      fVar11 = DAT_00077aec;
      fVar10 = DAT_00077ae4;
      iVar8 = *piVar6;
      uVar1 = uVar9 & 0xfffffff |
              (uint)(fVar5 < DAT_00077adc +
                             (DAT_00077ad8 - *(float *)(gOFOData + iVar8 + 0x1e70)) * DAT_00077ae0)
              << 0x1f;
      if (SUB41(uVar1 >> 0x1f,0)) {
        fVar14 = *(float *)(in_r0 + 0x14);
        fVar13 = *(float *)(in_r0 + 0x18);
        fVar5 = (float)VectorUnsignedToFloat((byte)in_r0[0x35] & 0xf,(byte)(uVar1 >> 0x16) & 3);
        fVar12 = DAT_00077ae4 + *(float *)(in_r0 + 0x10) + fVar5 * DAT_00077ae8;
        fVar5 = (float)SRAND(extraout_s0,(char *)0x40400000);
        fVar14 = fVar11 + fVar14;
        fVar13 = fVar10 + fVar13;
        local_44 = (fVar10 + *(float *)(iVar8 + 0x813c4)) - fVar14;
        local_40 = (fVar5 + fVar11 + *(float *)(iVar8 + 0x813c8)) - fVar13;
        local_48 = (fVar10 + *(float *)(iVar8 + 0x813c0)) - fVar12;
        if (DAT_00077af0 <= local_40) {
          iVar8 = *piVar6;
        }
        else {
          tVector::Normalize((tVector *)&local_48);
          local_48 = local_48 * DAT_00077af4;
          local_40 = local_40 * DAT_00077af4;
          local_44 = local_44 * DAT_00077af4;
          local_3c = fVar12;
          local_38 = fVar14;
          local_34 = fVar13;
          cRSubLazerManager::Shoot
                    (*piVar6 + 0x75a48,fVar12,fVar14,fVar13,local_48,local_44,local_40);
          iVar8 = *piVar6;
        }
      }
    }
    if (*(float *)(iVar8 + 0x83b60) <= *(float *)(in_r0 + 0x18)) {
      return;
    }
LAB_00077890:
    Remove(in_r0);
  }
  else {
    if (cVar2 == (cRSubLoc)0x16) {
      if (*(float *)(iVar8 + 0x83b60) <= *(float *)(in_r0 + 0x18)) {
        return;
      }
    }
    else {
      if ((byte)((char)cVar2 - 0x1dU) < 2) {
        if (*(int *)(*(int *)(in_r0 + 0x2c) + 0x2c) == 0x1c) {
          fVar10 = *(float *)(in_r0 + 0x20) + DAT_00077ad0 * *(float *)(iVar8 + 0x718f4);
          in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar10 < DAT_00077ad4) << 0x1f;
          *(float *)(in_r0 + 0x20) = fVar10;
          if (SUB41(in_fpscr >> 0x1f,0)) {
            *(float *)(in_r0 + 0x20) = fVar10 + DAT_00077ad8;
          }
          tColourSmall::Alpha((tColourSmall *)(in_r0 + 0x28),in_s0);
          iVar8 = **(int **)(iVar7 + iVar4);
        }
        cRSubGame::GetSkirtColour((tColourSmall *)(iVar8 + 0x718a0));
        fVar10 = (float)VectorSignedToFloat(*(undefined4 *)(*(int *)(in_r0 + 0x2c) + 0x3c),
                                            (byte)(in_fpscr >> 0x16) & 3);
        if (*(float *)(**(int **)(iVar7 + iVar4) + 0x83b60) - (fVar10 + DAT_00077acc) <=
            *(float *)(in_r0 + 0x18)) {
          return;
        }
        goto LAB_00077890;
      }
      uVar1 = in_fpscr & 0xfffffff |
              (uint)(*(float *)(in_r0 + 0x18) < *(float *)(iVar8 + 0x83b60)) << 0x1f;
      if (!SUB41(uVar1 >> 0x1f,0)) {
        return;
      }
      fVar10 = (float)VectorSignedToFloat(*(int *)(iVar8 + 0x71918) + -5,(byte)(uVar1 >> 0x16) & 3);
      if (fVar10 <= *(float *)(in_r0 + 0x18)) {
        return;
      }
    }
    Remove(in_r0);
  }
  return;
}
