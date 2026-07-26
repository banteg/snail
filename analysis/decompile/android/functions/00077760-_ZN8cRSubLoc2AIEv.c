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
  float *pfVar5;
  uint in_fpscr;
  uint uVar6;
  float in_s0;
  float extraout_s0;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;

  if (((byte)in_r0[0x35] & 0x20) == 0) {
    return;
  }
  if (*(char *)(Game + 0x718b9) != '\0') {
    return;
  }
  cVar2 = in_r0[0x30];
  if (cVar2 == (cRSubLoc)0xe) {
    fVar7 = *(float *)(Game + 0x813c8);
    fVar8 = (float)VectorSignedToFloat(*(undefined4 *)(Game + 0x71910),(byte)(in_fpscr >> 0x16) & 3)
    ;
    uVar1 = in_fpscr & 0xfffffff | (uint)(fVar7 < fVar8) << 0x1f | (uint)(fVar7 == fVar8) << 0x1e;
    uVar6 = uVar1 | (uint)(NAN(fVar7) || NAN(fVar8)) << 0x1c;
    bVar3 = (byte)(uVar1 >> 0x18);
    if (!(bool)(bVar3 >> 6 & 1) && bVar3 >> 7 == ((byte)(uVar6 >> 0x1c) & 1)) {
      fVar7 = (float)RAND(in_s0,(char *)0x42c80000);
      iVar4 = Game;
      uVar1 = uVar6 & 0xfffffff |
              (uint)(fVar7 < (1.0 - *(float *)(gOFOData + Game + 0x1e70)) * -3.5 + 4.0) << 0x1f;
      if (SUB41(uVar1 >> 0x1f,0)) {
        fVar10 = *(float *)(in_r0 + 0x14);
        fVar9 = *(float *)(in_r0 + 0x18);
        pfVar5 = (float *)(Game + 0x813c8);
        fVar7 = (float)VectorUnsignedToFloat((byte)in_r0[0x35] & 0xf,(byte)(uVar1 >> 0x16) & 3);
        fVar8 = *(float *)(in_r0 + 0x10) + 0.0 + fVar7 * 0.5;
        fVar7 = (float)SRAND(extraout_s0,(char *)0x40400000);
        fVar10 = fVar10 + 8.0;
        fVar9 = fVar9 + 0.0;
        local_44 = (*(float *)(iVar4 + 0x813c4) + 0.0) - fVar10;
        local_40 = (fVar7 + 8.0 + *pfVar5) - fVar9;
        local_48 = (*(float *)(iVar4 + 0x813c0) + 0.0) - fVar8;
        if (local_40 < -4.0) {
          tVector::Normalize((tVector *)&local_48);
          local_48 = local_48 * 0.4;
          local_40 = local_40 * 0.4;
          local_44 = local_44 * 0.4;
          local_3c = fVar8;
          local_38 = fVar10;
          local_34 = fVar9;
          cRSubLazerManager::Shoot(Game + 0x75a48,fVar8,fVar10,fVar9,local_48,local_44,local_40);
        }
      }
    }
    if (*(float *)(Game + 0x83b60) <= *(float *)(in_r0 + 0x18)) {
      return;
    }
LAB_00077890:
    Remove(in_r0);
  }
  else {
    if (cVar2 == (cRSubLoc)0x16) {
      if (*(float *)(Game + 0x83b60) <= *(float *)(in_r0 + 0x18)) {
        return;
      }
    }
    else {
      if ((byte)((char)cVar2 - 0x1dU) < 2) {
        if (*(int *)(*(int *)(in_r0 + 0x2c) + 0x2c) == 0x1c) {
          fVar7 = *(float *)(in_r0 + 0x20) + *(float *)(Game + 0x718f4) * -0.033333335;
          in_fpscr = in_fpscr & 0xfffffff | (uint)(fVar7 < -1.0) << 0x1f;
          *(float *)(in_r0 + 0x20) = fVar7;
          if (SUB41(in_fpscr >> 0x1f,0)) {
            *(float *)(in_r0 + 0x20) = fVar7 + 1.0;
          }
          tColourSmall::Alpha((tColourSmall *)(in_r0 + 0x28),in_s0);
        }
        cRSubGame::GetSkirtColour((tColourSmall *)(Game + 0x718a0));
        fVar7 = (float)VectorSignedToFloat(*(undefined4 *)(*(int *)(in_r0 + 0x2c) + 0x3c),
                                           (byte)(in_fpscr >> 0x16) & 3);
        if (*(float *)(Game + 0x83b60) - (fVar7 + 5.0) <= *(float *)(in_r0 + 0x18)) {
          return;
        }
        goto LAB_00077890;
      }
      uVar1 = in_fpscr & 0xfffffff |
              (uint)(*(float *)(in_r0 + 0x18) < *(float *)(Game + 0x83b60)) << 0x1f;
      if (!SUB41(uVar1 >> 0x1f,0)) {
        return;
      }
      fVar7 = (float)VectorSignedToFloat(*(int *)(Game + 0x71918) + -5,(byte)(uVar1 >> 0x16) & 3);
      if (fVar7 <= *(float *)(in_r0 + 0x18)) {
        return;
      }
    }
    Remove(in_r0);
  }
  return;
}
