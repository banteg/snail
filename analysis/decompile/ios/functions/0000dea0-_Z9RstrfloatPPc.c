/*
 * mangled: _Z9RstrfloatPPc
 * demangled: Rstrfloat(char**)
 * address: 0000dea0
 * size: 332
 */

/* Rstrfloat(char**) */

float Rstrfloat(char **param_1)

{
  byte *pbVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  uint in_fpscr;
  int in_s10;
  float fVar8;
  float in_s12;
  float fVar9;
  float in_s14;
  float in_s15;

  pbVar1 = (byte *)*param_1;
  bVar3 = *pbVar1;
  if (bVar3 == 0x2d || bVar3 == 0x2b) {
LAB_0000df10:
    if (bVar3 == 0x2d) {
      pbVar1 = pbVar1 + 1;
      *param_1 = (char *)pbVar1;
      fVar8 = -1.0;
    }
    else {
      pbVar1 = (byte *)*param_1;
      fVar8 = 1.0;
    }
    bVar3 = *pbVar1;
    bVar5 = bVar3 != 0x2e;
    bVar2 = bVar3 - 0x30;
    bVar7 = 0x2d < bVar3;
    bVar6 = bVar3 != 0x2e;
    if (bVar6) {
      bVar7 = 8 < bVar2;
    }
    iVar4 = (int)(char)bVar3;
    if (bVar7 && (bVar6 && bVar2 != 9)) {
      in_s12 = 0.0;
    }
    if (!bVar7 || (!bVar6 || bVar2 == 9)) goto LAB_0000df54;
  }
  else {
    if (bVar3 == 0x2e) {
      bVar3 = 0x2e;
    }
    else {
      do {
        if ((byte)(bVar3 - 0x30) < 10) goto LAB_0000df10;
        pbVar1 = pbVar1 + 1;
        *param_1 = (char *)pbVar1;
        bVar3 = *pbVar1;
        if (bVar3 == 0x2d || bVar3 == 0x2b) goto LAB_0000df10;
      } while (bVar3 != 0x2e);
    }
    fVar8 = 1.0;
    iVar4 = (int)(char)bVar3;
    bVar5 = iVar4 != 0x2e;
LAB_0000df54:
    in_s12 = 0.0;
    fVar9 = in_s12;
    do {
      if (bVar5) {
        in_s10 = iVar4 + -0x30;
        in_s14 = 10.0;
      }
      pbVar1 = pbVar1 + 1;
      *param_1 = (char *)pbVar1;
      bVar3 = *pbVar1;
      if (bVar5) {
        in_s15 = (float)VectorSignedToFloat(in_s10,(byte)(in_fpscr >> 0x16) & 3);
        fVar9 = fVar9 / in_s14;
      }
      else {
        fVar9 = 1.0;
      }
      iVar4 = (int)(char)bVar3;
      if (bVar5) {
        in_s12 = in_s15 + in_s12 * in_s14;
        in_s15 = in_s12;
      }
      bVar5 = bVar3 != 0x2e;
      bVar7 = 0x2d < bVar3;
      if (bVar3 != 0x2e) {
        bVar7 = 8 < (byte)(bVar3 - 0x30);
      }
    } while (!bVar7 || (bVar3 == 0x2e || (byte)(bVar3 - 0x30) == 9));
    if (fVar9 != 0.0) goto LAB_0000dfc0;
  }
  fVar9 = 1.0;
LAB_0000dfc0:
  return fVar8 * in_s12 * fVar9;
}
