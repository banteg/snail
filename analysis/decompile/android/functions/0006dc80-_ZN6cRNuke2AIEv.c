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
  int *in_r0;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  byte bVar6;
  bool bVar7;
  byte bVar8;
  uint in_fpscr;
  uint uVar9;
  float in_s0;
  float extraout_s0;
  float extraout_s0_00;
  float fVar10;
  float fVar11;

  if (*in_r0 == 1) {
    fVar11 = (float)in_r0[4] + (float)in_r0[5];
    iVar2 = 0;
    uVar1 = in_fpscr & 0xfffffff | (uint)(fVar11 < 6.2831855) << 0x1f |
            (uint)(fVar11 == 6.2831855) << 0x1e;
    uVar9 = uVar1 | (uint)NAN(fVar11) << 0x1c;
    in_r0[4] = (int)fVar11;
    bVar8 = (byte)(uVar1 >> 0x18);
    bVar6 = bVar8 >> 7;
    bVar7 = (bool)(bVar8 >> 6 & 1);
    bVar8 = (byte)(uVar9 >> 0x1c) & 1;
    fVar10 = (float)in_r0[3] + (float)in_r0[2];
    if (!bVar7 && bVar6 == bVar8) {
      fVar11 = fVar11 - 6.2831855;
    }
    in_r0[3] = (int)fVar10;
    piVar3 = in_r0;
    if (!bVar7 && bVar6 == bVar8) {
      in_r0[4] = (int)fVar11;
    }
    while( true ) {
      VectorSignedToFloat(iVar2,(byte)(uVar9 >> 0x16) & 3);
      iVar4 = piVar3[6];
      *(float *)(iVar4 + 0x50) = fVar10;
      iVar2 = iVar2 + 1;
      fVar10 = (float)Sin(in_s0);
      iVar5 = piVar3[6];
      *(float *)(iVar4 + 0x48) = fVar10 * 7.0;
      fVar10 = (float)Cos(extraout_s0);
      *(float *)(iVar5 + 0x4c) = fVar10 * 7.0;
      if (iVar2 == 0x19) break;
      fVar10 = (float)in_r0[3];
      piVar3 = piVar3 + 1;
      in_s0 = extraout_s0_00;
    }
  }
  return;
}
