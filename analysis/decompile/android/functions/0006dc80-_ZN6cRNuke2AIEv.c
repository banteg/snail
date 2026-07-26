/*
 * mangled: _ZN6cRNuke2AIEv
 * demangled: cRNuke::AI()
 * address: 0006dc80
 * size: 204
 */

/* cRNuke::AI() */

void cRNuke::AI(void)

{
  uint uVar1;
  float fVar2;
  int *in_r0;
  float fVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  byte bVar8;
  bool bVar9;
  byte bVar10;
  uint in_fpscr;
  uint uVar11;
  float in_s0;
  float extraout_s0;
  float extraout_s0_00;
  float fVar12;
  float fVar13;

  fVar2 = DAT_0006dd54;
  fVar3 = DAT_0006dd4c;
  if (*in_r0 == 1) {
    fVar13 = (float)in_r0[4] + (float)in_r0[5];
    iVar4 = 0;
    uVar1 = in_fpscr & 0xfffffff | (uint)(fVar13 < DAT_0006dd4c) << 0x1f |
            (uint)(fVar13 == DAT_0006dd4c) << 0x1e;
    uVar11 = uVar1 | (uint)(NAN(fVar13) || NAN(DAT_0006dd4c)) << 0x1c;
    in_r0[4] = (int)fVar13;
    bVar10 = (byte)(uVar1 >> 0x18);
    bVar8 = bVar10 >> 7;
    bVar9 = (bool)(bVar10 >> 6 & 1);
    bVar10 = (byte)(uVar11 >> 0x1c) & 1;
    fVar12 = (float)in_r0[3] + (float)in_r0[2];
    if (!bVar9 && bVar8 == bVar10) {
      fVar13 = fVar13 - fVar3;
    }
    in_r0[3] = (int)fVar12;
    piVar5 = in_r0;
    if (!bVar9 && bVar8 == bVar10) {
      in_r0[4] = (int)fVar13;
    }
    while( true ) {
      VectorSignedToFloat(iVar4,(byte)(uVar11 >> 0x16) & 3);
      iVar6 = piVar5[6];
      *(float *)(iVar6 + 0x50) = fVar12;
      iVar4 = iVar4 + 1;
      fVar3 = (float)Sin(in_s0);
      iVar7 = piVar5[6];
      *(float *)(iVar6 + 0x48) = fVar3 * fVar2;
      fVar3 = (float)Cos(extraout_s0);
      *(float *)(iVar7 + 0x4c) = fVar3 * fVar2;
      if (iVar4 == 0x19) break;
      fVar12 = (float)in_r0[3];
      piVar5 = piVar5 + 1;
      in_s0 = extraout_s0_00;
    }
  }
  return;
}
