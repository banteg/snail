/*
 * mangled: _Z9RstrfloatPPc
 * demangled: Rstrfloat(char**)
 * address: 0006a754
 * size: 304
 */

/* Rstrfloat(char**) */

float Rstrfloat(char **param_1)

{
  uint uVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte bVar4;
  uint uVar5;
  bool bVar6;
  uint in_fpscr;
  float fVar7;
  float in_s12;
  float fVar8;
  float fVar9;

  pbVar2 = (byte *)*param_1;
  bVar4 = *pbVar2;
  pbVar3 = pbVar2;
  if (bVar4 != 0x2b && bVar4 != 0x2d) {
    do {
      if (bVar4 == 0x2e) {
        uVar5 = 0x2e;
        fVar7 = 1.0;
        goto LAB_0006a814;
      }
      if ((byte)(bVar4 - 0x30) < 10) goto LAB_0006a7fc;
      pbVar2 = pbVar3 + 1;
      *param_1 = (char *)pbVar2;
      bVar4 = *pbVar2;
      pbVar3 = pbVar2;
    } while (bVar4 != 0x2b && bVar4 != 0x2d);
  }
  if (bVar4 == 0x2d) {
    pbVar3 = pbVar2 + 1;
    *param_1 = (char *)pbVar3;
    bVar4 = pbVar2[1];
    fVar7 = -1.0;
  }
  else {
    pbVar3 = (byte *)*param_1;
LAB_0006a7fc:
    fVar7 = 1.0;
    bVar4 = *pbVar3;
  }
  uVar5 = (uint)bVar4;
  uVar1 = uVar5 - 0x30 & 0xff;
  bVar6 = 0x2d < uVar5;
  if (uVar5 != 0x2e) {
    bVar6 = 8 < uVar1;
  }
  if (bVar6 && (uVar5 != 0x2e && uVar1 != 9)) {
    fVar8 = 0.0;
  }
  else {
LAB_0006a814:
    fVar8 = 0.0;
    fVar9 = fVar8;
    do {
      bVar6 = uVar5 == 0x2e;
      if (!bVar6) {
        in_s12 = (float)VectorSignedToFloat(uVar5 - 0x30,(byte)(in_fpscr >> 0x16) & 3);
      }
      pbVar3 = pbVar3 + 1;
      *param_1 = (char *)pbVar3;
      uVar5 = (uint)*pbVar3;
      if (bVar6) {
        fVar9 = 1.0;
      }
      uVar1 = uVar5 - 0x30 & 0xff;
      if (!bVar6) {
        fVar8 = in_s12 + fVar8 * 10.0;
        fVar9 = fVar9 / 10.0;
        in_s12 = fVar8;
      }
      bVar6 = 0x2d < uVar5;
      if (uVar5 != 0x2e) {
        bVar6 = 8 < uVar1;
      }
    } while (!bVar6 || (uVar5 == 0x2e || uVar1 == 9));
    if (fVar9 != 0.0) {
      return fVar7 * fVar8 * fVar9;
    }
  }
  return fVar7 * fVar8 * 1.0;
}
