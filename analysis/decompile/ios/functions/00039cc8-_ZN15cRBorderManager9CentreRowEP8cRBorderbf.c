/*
 * mangled: _ZN15cRBorderManager9CentreRowEP8cRBorderbf
 * demangled: cRBorderManager::CentreRow(cRBorder*, bool, float)
 * address: 00039cc8
 * size: 708
 */

/* cRBorderManager::CentreRow(cRBorder*, bool, float) */

void __thiscall
cRBorderManager::CentreRow(cRBorderManager *this,cRBorder *param_1,bool param_2,float param_3)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  cRBorderManager *pcVar4;
  cRBorderManager *pcVar5;
  int iVar6;
  int iVar7;
  uint in_fpscr;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar13;
  ulonglong uVar12;
  float fVar14;

  fVar11 = 10000.0;
  uVar12 = (ulonglong)(uint)param_3;
  fVar13 = -10000.0;
  pcVar5 = this + 0x80c;
  iVar7 = 0;
  iVar6 = 0;
  pcVar4 = pcVar5;
  do {
    uVar2 = *(uint *)pcVar4;
    if ((((uVar2 == 0) || ((uVar2 & 0x600) != 0)) ||
        (in_fpscr = in_fpscr & 0xfffffff |
                    (uint)(*(float *)(pcVar4 + 0x55c) == *(float *)(param_1 + 0x6f0)) << 0x1e,
        !SUB41(in_fpscr >> 0x1e,0))) || ((uVar2 & 0x1000) != 0)) {
LAB_00039d04:
      fVar14 = (float)uVar12;
    }
    else {
      iVar7 = iVar7 + 1;
      cRBorder::RePosition((cRBorder *)(this + iVar6 * 0x71c + 0x678));
      fVar14 = (float)uVar12;
      iVar3 = *(int *)(pcVar4 + 0xc0);
      if (iVar3 == 2) {
        fVar8 = *(float *)(pcVar4 + 0xa8);
        fVar9 = *(float *)(pcVar4 + 0x78);
        fVar10 = (*(float *)(pcVar4 + 0xc4) + 320.0 + fVar8 * -0.5) - fVar9;
      }
      else {
        fVar9 = *(float *)(pcVar4 + 0x78);
        fVar8 = *(float *)(pcVar4 + 0xa8);
        fVar10 = *(float *)(pcVar4 + 0x558) - fVar9;
      }
      if (fVar11 <= fVar10) {
LAB_00039dc0:
        if (iVar3 == 2) goto LAB_00039f54;
        fVar10 = fVar8 + *(float *)(pcVar4 + 0x558);
      }
      else {
        if (iVar3 != 2) {
          fVar11 = *(float *)(pcVar4 + 0x558) - fVar9;
          goto LAB_00039dc0;
        }
        fVar11 = (*(float *)(pcVar4 + 0xc4) + 320.0 + fVar8 * -0.5) - fVar9;
LAB_00039f54:
        fVar10 = *(float *)(pcVar4 + 0xc4) + 320.0 + fVar8 * 0.5;
      }
      fVar10 = fVar10 + fVar9;
      uVar2 = in_fpscr & 0xfffffff | (uint)(fVar10 < fVar13) << 0x1f |
              (uint)(fVar10 == fVar13) << 0x1e;
      in_fpscr = uVar2 | (uint)(NAN(fVar10) || NAN(fVar13)) << 0x1c;
      bVar1 = (byte)(uVar2 >> 0x18);
      if ((bool)(bVar1 >> 6 & 1) || bVar1 >> 7 != ((byte)(in_fpscr >> 0x1c) & 1)) goto LAB_00039d04;
      if (iVar3 == 2) {
        fVar13 = *(float *)(pcVar4 + 0xc4) + 320.0 + fVar8 * 0.5 + fVar9;
        goto LAB_00039d04;
      }
      fVar13 = fVar8 + *(float *)(pcVar4 + 0x558) + fVar9;
    }
    pcVar4 = pcVar4 + 0x71c;
    iVar6 = iVar6 + 1;
    if (iVar6 == 0x96) {
      if (iVar7 != 0) {
        fVar11 = (float)VectorSignedToFloat((int)((fVar11 + ((fVar14 * 0.5 + 640.0) - fVar13)) * 0.5
                                                 - fVar11),(byte)(in_fpscr >> 0x16) & 3);
        uVar12 = (ulonglong)(uint)fVar11;
        if (fVar11 != 0.0) {
          iVar6 = 0;
          do {
            while (((uVar2 = *(uint *)pcVar5, uVar2 == 0 || ((uVar2 & 0x600) != 0)) ||
                   ((*(float *)(pcVar5 + 0x55c) != *(float *)(param_1 + 0x6f0) ||
                    ((uVar2 & 0x1000) != 0))))) {
              iVar6 = iVar6 + 1;
              pcVar5 = pcVar5 + 0x71c;
              if (iVar6 == 0x96) {
                return;
              }
            }
            fVar11 = (float)uVar12;
            iVar7 = iVar6 * 0x71c;
            iVar6 = iVar6 + 1;
            *(float *)(pcVar5 + 0x98) = *(float *)(pcVar5 + 0x98) + fVar11;
            *(float *)(pcVar5 + 0x558) = *(float *)(pcVar5 + 0x558) + fVar11;
            *(float *)(pcVar5 + 0xc4) = *(float *)(pcVar5 + 0xc4) + fVar11;
            cRBorder::RePosition((cRBorder *)(this + iVar7 + 0x678));
            pcVar5 = pcVar5 + 0x71c;
          } while (iVar6 != 0x96);
        }
      }
      return;
    }
  } while( true );
}
