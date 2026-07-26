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
  float in_r3;
  uint uVar3;
  int iVar4;
  cRBorderManager *pcVar5;
  cRBorderManager *pcVar6;
  int iVar7;
  cRBorder *this_00;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float fVar8;
  float fVar9;

  iVar4 = 0;
  pcVar5 = this + 0x80c;
  iVar7 = 0;
  fVar9 = -10000.0;
  fVar8 = 10000.0;
  pcVar6 = pcVar5;
  do {
    while ((((uVar3 = *(uint *)pcVar6, uVar3 == 0 || ((uVar3 & 0x600) != 0)) ||
            (in_fpscr = in_fpscr & 0xfffffff |
                        (uint)(*(float *)(pcVar6 + 0x55c) == *(float *)(param_1 + 0x6f0)) << 0x1e,
            !SUB41(in_fpscr >> 0x1e,0))) || ((uVar3 & 0x1000) != 0))) {
LAB_0005df04:
      iVar4 = iVar4 + 1;
      pcVar6 = pcVar6 + 0x71c;
      if (iVar4 == 0x96) goto LAB_0005dfc0;
    }
    iVar7 = iVar7 + 1;
    this_00 = (cRBorder *)(this + iVar4 * 0x71c + 0x678);
    cRBorder::RePosition(this_00);
    fVar2 = (float)cRBorder::XLeft(this_00);
    uVar3 = in_fpscr & 0xfffffff | (uint)(fVar2 < fVar8) << 0x1f;
    if (SUB41(uVar3 >> 0x1f,0)) {
      fVar8 = (float)cRBorder::XLeft(this_00);
    }
    fVar2 = (float)cRBorder::XRight(this_00);
    uVar3 = uVar3 & 0xfffffff | (uint)(fVar2 < fVar9) << 0x1f | (uint)(fVar2 == fVar9) << 0x1e;
    in_fpscr = uVar3 | (uint)(NAN(fVar2) || NAN(fVar9)) << 0x1c;
    bVar1 = (byte)(uVar3 >> 0x18);
    param_3 = extraout_s0;
    if ((bool)(bVar1 >> 6 & 1) || bVar1 >> 7 != ((byte)(in_fpscr >> 0x1c) & 1)) goto LAB_0005df04;
    iVar4 = iVar4 + 1;
    fVar9 = (float)cRBorder::XRight(this_00);
    pcVar6 = pcVar6 + 0x71c;
    param_3 = extraout_s0_00;
  } while (iVar4 != 0x96);
LAB_0005dfc0:
  if ((iVar7 != 0) &&
     (fVar9 = (float)VectorSignedToFloat((int)((((in_r3 * 0.5 + 640.0) - fVar9) + fVar8) * 0.5 -
                                              fVar8),(byte)(in_fpscr >> 0x16) & 3), fVar9 != 0.0)) {
    iVar4 = 0;
    do {
      while (((uVar3 = *(uint *)pcVar5, uVar3 != 0 && ((uVar3 & 0x600) == 0)) &&
             ((*(float *)(pcVar5 + 0x55c) == *(float *)(param_1 + 0x6f0) && ((uVar3 & 0x1000) == 0))
             ))) {
        iVar7 = iVar4 * 0x71c;
        iVar4 = iVar4 + 1;
        *(float *)(pcVar5 + 0x98) = *(float *)(pcVar5 + 0x98) + fVar9;
        *(float *)(pcVar5 + 0x558) = *(float *)(pcVar5 + 0x558) + fVar9;
        *(float *)(pcVar5 + 0xc4) = *(float *)(pcVar5 + 0xc4) + fVar9;
        param_3 = (float)cRBorder::RePosition((cRBorder *)(this + iVar7 + 0x678));
        pcVar5 = pcVar5 + 0x71c;
        if (iVar4 == 0x96) {
          return param_3;
        }
      }
      iVar4 = iVar4 + 1;
      pcVar5 = pcVar5 + 0x71c;
    } while (iVar4 != 0x96);
  }
  return param_3;
}
