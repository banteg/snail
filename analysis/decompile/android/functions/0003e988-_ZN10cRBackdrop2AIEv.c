/*
 * mangled: _ZN10cRBackdrop2AIEv
 * demangled: cRBackdrop::AI()
 * address: 0003e988
 * size: 468
 */

/* cRBackdrop::AI() */

void cRBackdrop::AI(void)

{
  int in_r0;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float in_s0;
  float extraout_s0;
  float extraout_s0_00;
  float fVar6;
  float fVar7;
  float fVar8;

  fVar6 = *(float *)(Game + 0x3c);
  if (((((fVar6 == 0.0) || (fVar6 == 180.0)) &&
       ((*(float *)(in_r0 + 0x38) == 90.0 || (*(float *)(in_r0 + 0x38) == 270.0)))) ||
      (((fVar6 == 90.0 || (fVar6 == 270.0)) &&
       ((*(float *)(in_r0 + 0x38) == 0.0 || (*(float *)(in_r0 + 0x38) == 180.0)))))) &&
     (gSegmentText[*(int *)(in_r0 + 0x60) * 0x1ac + Game + 0x4e4] != '\0')) {
    *(undefined1 *)(in_r0 + 100) = 1;
    *(undefined4 *)(in_r0 + 0x5c) = 0xffffffff;
  }
  *(float *)(in_r0 + 0x38) = fVar6;
  *(float *)(in_r0 + 0xf0) =
       *(float *)(in_r0 + 0xf0) + (*(float *)(in_r0 + 0xf4) - *(float *)(in_r0 + 0xf0)) * 0.3;
  if (*(char *)(in_r0 + 100) != '\0') {
    in_s0 = (float)ChangeReal();
    *(undefined1 *)(in_r0 + 100) = 0;
  }
  iVar1 = *(int *)(in_r0 + 0x3c);
  if (-1 < iVar1) {
    iVar5 = 0;
    do {
      iVar3 = 0;
      do {
        iVar2 = iVar1 * iVar3 + iVar3;
        iVar1 = *(int *)(in_r0 + 0x7c);
        iVar3 = iVar3 + 1;
        iVar2 = iVar2 + iVar5;
        iVar4 = iVar1 + iVar2 * 0x28;
        fVar6 = *(float *)(iVar1 + iVar2 * 0x28) + *(float *)(iVar4 + 4);
        fVar7 = *(float *)(iVar4 + 8);
        *(float *)(iVar1 + iVar2 * 0x28) = fVar6;
        if (6.2831855 < fVar6) {
          *(float *)(iVar1 + iVar2 * 0x28) = fVar6 - 6.2831855;
        }
        fVar6 = (float)Sin(in_s0);
        iVar2 = *(int *)(in_r0 + 0x7c) + iVar2 * 0x28;
        fVar8 = *(float *)(iVar2 + 0xc);
        *(float *)(iVar4 + 0x10) = fVar7 * fVar6;
        fVar6 = (float)Cos(extraout_s0);
        iVar1 = *(int *)(in_r0 + 0x3c);
        *(float *)(iVar2 + 0x14) = fVar8 * fVar6;
        in_s0 = extraout_s0_00;
      } while (iVar3 <= iVar1);
      iVar5 = iVar5 + 1;
    } while ((iVar5 <= iVar1) && (-1 < iVar1));
  }
  return;
}
