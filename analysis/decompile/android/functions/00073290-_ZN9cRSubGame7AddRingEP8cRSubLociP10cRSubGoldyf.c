/*
 * mangled: _ZN9cRSubGame7AddRingEP8cRSubLociP10cRSubGoldyf
 * demangled: cRSubGame::AddRing(cRSubLoc*, int, cRSubGoldy*, float)
 * address: 00073290
 * size: 1612
 */

/* cRSubGame::AddRing(cRSubLoc*, int, cRSubGoldy*, float) */

float __thiscall
cRSubGame::AddRing(cRSubGame *this,cRSubLoc *param_1,int param_2,cRSubGoldy *param_3,float param_4)

{
  char *pcVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  cRBod *pcVar5;
  cRSubGame *pcVar6;
  int iVar7;
  int *piVar8;
  bool bVar9;
  uint in_fpscr;
  float fVar10;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s0_03;
  float extraout_s0_04;
  float extraout_s0_05;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float in_stack_00000000;

  iVar4 = DAT_000736e0 + 0x732bc;
  iVar7 = 0;
  if (*(int *)(this + 0x8968) != 0) {
    if (*(int *)(this + 0x8b14) != 0) {
      return param_4;
    }
    iVar7 = 1;
  }
  fVar14 = DAT_000736c4 + DAT_000736c0 * *(float *)(this + 0x68);
  fVar11 = (float)VectorSignedToFloat(*(undefined4 *)(param_3 + 0x2f0),(byte)(in_fpscr >> 0x16) & 3)
  ;
  fVar15 = DAT_000736d0;
  if (fVar14 != 0.0) {
    fVar15 = (float)DAT_000736d4 / (fVar14 * DAT_000736cc);
  }
  fVar15 = fVar15 * fVar11 * DAT_000736c8;
  fVar15 = (fVar15 + fVar15) * DAT_000736d8 * *(float *)(this + 0x54);
  fVar10 = (float)tMatrix::Identity((tMatrix *)(this + iVar7 * 0x1ac + 0x8920));
  *(cRSubGoldy **)(this + iVar7 * 0x1ac + 0x896c) = param_3;
  fVar13 = DAT_00073744;
  fVar12 = DAT_0007373c;
  fVar14 = DAT_0007372c;
  pcVar1 = DAT_000736d4;
  fVar11 = DAT_000736d0;
  if (param_2 == 4) {
    fVar11 = (float)RAND(fVar10,(char *)0x3f800000);
    fVar10 = extraout_s0_00;
    if (fVar11 <= DAT_000736dc) goto LAB_0007362c;
LAB_00073748:
    fVar11 = DAT_00073744;
    fVar14 = *(float *)(param_1 + 0x18);
    pcVar6 = this + iVar7 * 0x1ac;
    param_2 = 3;
    fVar12 = DAT_00073740 + *(float *)(param_1 + 0x14);
    *(float *)(pcVar6 + 0x8950) = DAT_0007373c + *(float *)(param_1 + 0x10);
    *(float *)(pcVar6 + 0x8954) = fVar12;
    *(float *)(pcVar6 + 0x8958) = fVar14 + fVar11;
    fVar11 = (float)RAND(fVar10,(char *)0x3f800000);
    fVar10 = extraout_s0_02;
    goto LAB_00073694;
  }
  switch(param_2) {
  case 0:
    fVar11 = *(float *)(param_1 + 0x18);
    pcVar6 = this + iVar7 * 0x1ac;
    fVar14 = DAT_00073740 + *(float *)(param_1 + 0x14);
    *(float *)(pcVar6 + 0x8950) = DAT_0007373c + *(float *)(param_1 + 0x10);
    *(float *)(pcVar6 + 0x8954) = fVar14;
    *(float *)(pcVar6 + 0x8958) = fVar11 + fVar13;
    fVar11 = (float)RAND(fVar10,(char *)0x3f800000);
    fVar10 = extraout_s0_05;
    break;
  case 1:
    fVar11 = *(float *)(param_1 + 0x18);
    pcVar6 = this + iVar7 * 0x1ac;
    fVar14 = DAT_00073740 + *(float *)(param_1 + 0x14);
    *(float *)(pcVar6 + 0x8950) = DAT_0007373c + *(float *)(param_1 + 0x10);
    *(float *)(pcVar6 + 0x8954) = fVar14;
    *(float *)(pcVar6 + 0x8958) = fVar11 + fVar13;
    fVar11 = (float)RAND(fVar10,(char *)0x3f800000);
    fVar10 = extraout_s0_04;
    break;
  case 2:
    fVar11 = *(float *)(param_1 + 0x18);
    fVar13 = DAT_00073728 + *(float *)(param_1 + 0x14);
    *(float *)(this + iVar7 * 0x1ac + 0x8950) = DAT_0007373c + *(float *)(param_1 + 0x10);
    *(float *)(this + iVar7 * 0x1ac + 0x8954) = fVar13;
    *(float *)(this + iVar7 * 0x1ac + 0x8958) = fVar11 + fVar14;
    fVar11 = (float)RAND(fVar10,(char *)0x3f800000);
    *(float *)(this + iVar7 * 0x1ac + 0x8950) =
         ((fVar11 - DAT_00073730) + (fVar11 - DAT_00073730)) * DAT_00073734;
    fVar14 = (float)RAND(extraout_s0_03,(char *)0x3f800000);
    fVar11 = DAT_00073738;
    piVar8 = *(int **)(iVar4 + DAT_00073714);
    *(float *)(this + iVar7 * 0x1ac + 0x8a8c) = fVar15;
    bVar9 = *(int *)(*piVar8 + 0x71900) == 7;
    if (bVar9) {
      *(float *)(this + iVar7 * 0x1ac + 0x8a8c) = fVar12;
      fVar15 = fVar12;
    }
    *(float *)(this + iVar7 * 0x1ac + 0x8a88) = fVar14 * fVar11;
    if (bVar9) {
      *(float *)(this + iVar7 * 0x1ac + 0x8a88) = fVar15;
    }
    goto switchD_00073364_default;
  case 3:
    goto LAB_00073748;
  case 4:
LAB_0007362c:
    fVar11 = DAT_00073744;
    fVar14 = *(float *)(param_1 + 0x18);
    pcVar6 = this + iVar7 * 0x1ac;
    param_2 = 4;
    fVar12 = DAT_00073740 + *(float *)(param_1 + 0x14);
    *(float *)(pcVar6 + 0x8950) = DAT_000736d0 + *(float *)(param_1 + 0x10);
    *(float *)(pcVar6 + 0x8954) = fVar12;
    *(float *)(pcVar6 + 0x8958) = fVar14 + fVar11;
    fVar11 = (float)RAND(fVar10,(char *)0x3f800000);
    fVar10 = extraout_s0_01;
    break;
  case 5:
    fVar12 = *(float *)(param_1 + 0x18);
    fVar14 = *(float *)(param_1 + 0x14);
    fVar15 = DAT_000736d0 + *(float *)(param_1 + 0x10);
    pcVar6 = this + iVar7 * 0x1ac;
    goto LAB_000733b8;
  case 6:
    fVar12 = *(float *)(param_1 + 0x18);
    fVar14 = *(float *)(param_1 + 0x14);
    fVar15 = DAT_000736d0 + *(float *)(param_1 + 0x10);
    pcVar6 = this + iVar7 * 0x1ac;
    goto LAB_000733b8;
  case 7:
    fVar14 = *(float *)(param_1 + 0x10);
    pcVar6 = this + iVar7 * 0x1ac;
    fVar15 = DAT_00073740 + *(float *)(param_1 + 0x14);
    *(float *)(pcVar6 + 0x8958) = *(float *)(param_1 + 0x18) + DAT_000736d0;
    *(float *)(pcVar6 + 0x8954) = fVar15;
    *(float *)(pcVar6 + 0x8950) = fVar11 + fVar14;
    goto LAB_00073584;
  case 8:
    fVar15 = DAT_000736d0 + *(float *)(param_1 + 0x10);
    fVar12 = *(float *)(param_1 + 0x18);
    fVar14 = *(float *)(param_1 + 0x14);
    pcVar6 = this + iVar7 * 0x1ac;
LAB_000733b8:
    fVar14 = DAT_00073740 + fVar14;
    *(float *)(pcVar6 + 0x8950) = fVar15;
    *(float *)(pcVar6 + 0x8954) = fVar14;
    *(float *)(pcVar6 + 0x8958) = fVar12 + fVar11;
    fVar15 = (float)RAND(fVar10,pcVar1);
    *(float *)(pcVar6 + 0x8a88) = fVar15 * DAT_00073738;
    if (in_stack_00000000 != fVar11) {
      fVar15 = (float)pcVar1 / (in_stack_00000000 * DAT_000736cc);
      fVar11 = (fVar15 + fVar15) * DAT_000736d8;
    }
    *(float *)(this + iVar7 * 0x1ac + 0x8a8c) = fVar11 * *(float *)(this + 0x54);
  default:
    goto switchD_00073364_default;
  }
LAB_00073694:
  *(float *)(pcVar6 + 0x8950) = ((fVar11 - DAT_00073730) + (fVar11 - DAT_00073730)) * DAT_00073734;
  fVar11 = fVar15;
LAB_00073584:
  fVar14 = (float)RAND(fVar10,(char *)0x3f800000);
  fVar15 = DAT_00073738;
  *(float *)(pcVar6 + 0x8a8c) = fVar11;
  *(float *)(pcVar6 + 0x8a88) = fVar14 * fVar15;
switchD_00073364_default:
  iVar2 = LocFromPos(this,*(undefined4 *)(this + iVar7 * 0x1ac + 0x8950),
                     *(undefined4 *)(this + iVar7 * 0x1ac + 0x8954),
                     *(undefined4 *)(this + iVar7 * 0x1ac + 0x8958));
  fVar15 = extraout_s0;
  if (*(char *)(iVar2 + 0x30) != '\x0e') {
    *(int *)(this + iVar7 * 0x1ac + 0x8970) = param_2;
    uVar3 = *(undefined4 *)(param_3 + 0x3fc);
    this[iVar7 * 0x1ac + 0x8a84] = (cRSubGame)0x1;
    *(undefined4 *)(this + iVar7 * 0x1ac + 0x8974) = uVar3;
    *(undefined4 *)(this + iVar7 * 0x1ac + 0x8968) = 1;
    fVar15 = (float)RAND(extraout_s0,(char *)0x3f800000);
    if (DAT_00073730 < fVar15) {
      *(float *)(this + iVar7 * 0x1ac + 0x8a8c) = -*(float *)(this + iVar7 * 0x1ac + 0x8a8c);
    }
    pcVar5 = (cRBod *)(this + iVar7 * 0x1ac + 0x88f4);
    cLinkedList<cRBod>::Add((cLinkedList<cRBod> *)(**(int **)(iVar4 + DAT_00073714) + 0x358),pcVar5)
    ;
    cRSubRing::Init((int)pcVar5);
    fVar15 = (float)(*(code *)**(undefined4 **)(this + iVar7 * 0x1ac + 0x88f4))(pcVar5);
  }
  return fVar15;
}
