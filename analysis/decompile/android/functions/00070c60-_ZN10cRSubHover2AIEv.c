/*
 * mangled: _ZN10cRSubHover2AIEv
 * demangled: cRSubHover::AI()
 * address: 00070c60
 * size: 572
 */

/* cRSubHover::AI() */

void cRSubHover::AI(void)

{
  uint uVar1;
  byte bVar2;
  tVector *in_r0;
  uint *puVar3;
  uint in_fpscr;
  float in_s0;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float fVar4;
  float fVar5;
  float fVar6;

  if (*(int *)(in_r0 + 0xc) == 1) {
    fVar5 = *(float *)in_r0 + *(float *)(in_r0 + 4);
    uVar1 = in_fpscr & 0xfffffff | (uint)(fVar5 < 1.0) << 0x1f | (uint)(fVar5 == 1.0) << 0x1e;
    *(float *)in_r0 = fVar5;
    bVar2 = (byte)(uVar1 >> 0x18);
    if (((bool)(bVar2 >> 6 & 1) || (bool)(bVar2 >> 7) != NAN(fVar5)) &&
       (fVar4 = (float)VectorSignedToFloat(*(int *)(*(int *)(in_r0 + 0x200) + 0x78) + -5,
                                           (byte)(uVar1 >> 0x16) & 3),
       *(float *)(*(int *)(in_r0 + 0x10) + 100) <= fVar4)) {
      if (fVar5 < 0.1) {
        *(float *)(in_r0 + 0x210) = fVar5 / 0.1;
      }
      else if (fVar5 <= 0.94) {
        *(undefined4 *)(in_r0 + 0x210) = 0x3f800000;
        puVar3 = (uint *)cRSubGame::RowFromPos
                                   (Game + 0x718a0,*(undefined4 *)(Game + 0x813c0),
                                    *(undefined4 *)(Game + 0x813c4),*(undefined4 *)(Game + 0x813c8))
        ;
        in_s0 = extraout_s0_02;
        if ((*puVar3 & 0x8000) != 0) {
          *(undefined4 *)in_r0 = 0x3f70a3d7;
          in_s0 = (float)wprintf("Auto Shutoff Jetpack\n");
        }
      }
      else {
        *(float *)(in_r0 + 0x210) = (1.0 - fVar5) / 0.06;
        if (fVar5 - *(float *)(in_r0 + 4) <= 0.94) {
          cRSnail::SetJetPack((cRSnail *)(Game + 0x83b64),0);
          in_s0 = (float)JetUnInit((cRSubHover *)in_r0);
        }
      }
      fVar5 = (float)Cos(in_s0);
      fVar4 = 1.0 - (fVar5 * 0.5 + 0.5);
      *(float *)(in_r0 + 0x210) = fVar4;
      fVar5 = (float)Sin(extraout_s0);
      fVar6 = *(float *)(in_r0 + 0x210);
      *(float *)(in_r0 + 0x14) = fVar4 * fVar5 * 0.25;
      fVar5 = (float)Sin(extraout_s0_00);
      *(undefined4 *)(in_r0 + 0x1c) = 0;
      *(undefined4 *)(in_r0 + 0x20c) = *(undefined4 *)(in_r0 + 0x210);
      *(float *)(in_r0 + 0x18) = fVar6 + fVar6 * fVar5 * 0.25;
      Hover(in_r0,extraout_s0_01);
      return;
    }
    End((cRSubHover *)in_r0);
    if (*(float *)in_r0 <= 0.94) {
      cRSnail::SetJetPack((cRSnail *)(Game + 0x83b64),0);
    }
    *(undefined4 *)(in_r0 + 0x14) = 0;
    *(undefined4 *)(in_r0 + 0x1c) = 0;
    *(undefined4 *)(in_r0 + 0x18) = 0;
    *(undefined4 *)(in_r0 + 0xc) = 0;
  }
  return;
}
