/*
 * mangled: _ZN15cRBorderManager9CentreRowEP8cRBorderbf
 * demangled: cRBorderManager::CentreRow(cRBorder*, bool, float)
 * address: 0005decc
 * size: 500
 */

/* cRBorderManager::CentreRow(cRBorder*, bool, float) */

float __thiscall
cRBorderManager::CentreRow(cRBorderManager *this,cRBorder *param_1,bool param_2,float param_3)

{
  byte bVar1;
  float fVar2;
  float fVar3;
  float in_r3;
  uint uVar4;
  int iVar5;
  cRBorderManager *pcVar6;
  cRBorderManager *pcVar7;
  int iVar8;
  cRBorder *this_00;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float fVar9;

  iVar5 = 0;
  pcVar6 = this + 0x80c;
  iVar8 = 0;
  pcVar7 = pcVar6;
  fVar9 = DAT_0005e0c4;
  fVar3 = DAT_0005e0c0;
  do {
    while ((((uVar4 = *(uint *)pcVar7, uVar4 == 0 || ((uVar4 & 0x600) != 0)) ||
            (in_fpscr = in_fpscr & 0xfffffff |
                        (uint)(*(float *)(pcVar7 + 0x55c) == *(float *)(param_1 + 0x6f0)) << 0x1e,
            !SUB41(in_fpscr >> 0x1e,0))) || ((uVar4 & 0x1000) != 0))) {
LAB_0005df04:
      iVar5 = iVar5 + 1;
      pcVar7 = pcVar7 + 0x71c;
      if (iVar5 == 0x96) goto LAB_0005dfc0;
    }
    iVar8 = iVar8 + 1;
    this_00 = (cRBorder *)(this + iVar5 * 0x71c + 0x678);
    cRBorder::RePosition(this_00);
    fVar2 = (float)cRBorder::XLeft(this_00);
    uVar4 = in_fpscr & 0xfffffff | (uint)(fVar2 < fVar9) << 0x1f;
    if (SUB41(uVar4 >> 0x1f,0)) {
      fVar9 = (float)cRBorder::XLeft(this_00);
    }
    fVar2 = (float)cRBorder::XRight(this_00);
    uVar4 = uVar4 & 0xfffffff | (uint)(fVar2 < fVar3) << 0x1f | (uint)(fVar2 == fVar3) << 0x1e;
    in_fpscr = uVar4 | (uint)(NAN(fVar2) || NAN(fVar3)) << 0x1c;
    bVar1 = (byte)(uVar4 >> 0x18);
    param_3 = extraout_s0;
    if ((bool)(bVar1 >> 6 & 1) || bVar1 >> 7 != ((byte)(in_fpscr >> 0x1c) & 1)) goto LAB_0005df04;
    iVar5 = iVar5 + 1;
    fVar3 = (float)cRBorder::XRight(this_00);
    pcVar7 = pcVar7 + 0x71c;
    param_3 = extraout_s0_00;
  } while (iVar5 != 0x96);
LAB_0005dfc0:
  if ((iVar8 != 0) &&
     (fVar9 = (float)VectorSignedToFloat((int)((((DAT_0005e0cc + in_r3 * DAT_0005e0c8) - fVar3) +
                                               fVar9) * DAT_0005e0c8 - fVar9),
                                         (byte)(in_fpscr >> 0x16) & 3), fVar9 != 0.0)) {
    iVar5 = 0;
    do {
      while (((uVar4 = *(uint *)pcVar6, uVar4 != 0 && ((uVar4 & 0x600) == 0)) &&
             ((*(float *)(pcVar6 + 0x55c) == *(float *)(param_1 + 0x6f0) && ((uVar4 & 0x1000) == 0))
             ))) {
        iVar8 = iVar5 * 0x71c;
        iVar5 = iVar5 + 1;
        *(float *)(pcVar6 + 0x98) = *(float *)(pcVar6 + 0x98) + fVar9;
        *(float *)(pcVar6 + 0x558) = *(float *)(pcVar6 + 0x558) + fVar9;
        *(float *)(pcVar6 + 0xc4) = *(float *)(pcVar6 + 0xc4) + fVar9;
        param_3 = (float)cRBorder::RePosition((cRBorder *)(this + iVar8 + 0x678));
        pcVar6 = pcVar6 + 0x71c;
        if (iVar5 == 0x96) {
          return param_3;
        }
      }
      iVar5 = iVar5 + 1;
      pcVar6 = pcVar6 + 0x71c;
    } while (iVar5 != 0x96);
  }
  return param_3;
}
