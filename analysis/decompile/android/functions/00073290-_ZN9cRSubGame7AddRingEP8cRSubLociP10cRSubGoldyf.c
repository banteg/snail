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
  int iVar1;
  float fVar2;
  undefined4 uVar3;
  cRBod *pcVar4;
  cRSubGame *pcVar5;
  int iVar6;
  bool bVar7;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float extraout_s0_03;
  float extraout_s0_04;
  float extraout_s0_05;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float in_stack_00000000;

  iVar6 = 0;
  if (*(int *)(this + 0x8968) != 0) {
    if (*(int *)(this + 0x8b14) != 0) {
      return param_4;
    }
    iVar6 = 1;
  }
  fVar10 = *(float *)(this + 0x68) * -0.3 + 2.0;
  fVar8 = (float)VectorSignedToFloat(*(undefined4 *)(param_3 + 0x2f0),(byte)(in_fpscr >> 0x16) & 3);
  if (fVar10 == 0.0) {
    fVar10 = 0.0;
  }
  else {
    fVar10 = 1.0 / (fVar10 * 60.0);
  }
  fVar10 = fVar10 * fVar8 * 0.125;
  fVar8 = (fVar10 + fVar10) * 3.1415927 * *(float *)(this + 0x54);
  fVar10 = (float)tMatrix::Identity((tMatrix *)(this + iVar6 * 0x1ac + 0x8920));
  *(cRSubGoldy **)(this + iVar6 * 0x1ac + 0x896c) = param_3;
  if (param_2 == 4) {
    fVar2 = (float)RAND(fVar10,(char *)0x3f800000);
    fVar10 = extraout_s0_00;
    if (fVar2 <= 0.93) goto LAB_0007362c;
LAB_00073748:
    fVar9 = *(float *)(param_1 + 0x14);
    fVar2 = *(float *)(param_1 + 0x18);
    pcVar5 = this + iVar6 * 0x1ac;
    param_2 = 3;
    *(float *)(pcVar5 + 0x8950) = *(float *)(param_1 + 0x10) + 0.0;
    *(float *)(pcVar5 + 0x8954) = fVar9 + 2.5;
    *(float *)(pcVar5 + 0x8958) = fVar2 + 6.0;
    fVar2 = (float)RAND(fVar10,(char *)0x3f800000);
    fVar10 = extraout_s0_02;
    goto LAB_00073694;
  }
  switch(param_2) {
  case 0:
    fVar9 = *(float *)(param_1 + 0x14);
    fVar2 = *(float *)(param_1 + 0x18);
    pcVar5 = this + iVar6 * 0x1ac;
    *(float *)(pcVar5 + 0x8950) = *(float *)(param_1 + 0x10) + 0.0;
    *(float *)(pcVar5 + 0x8954) = fVar9 + 2.5;
    *(float *)(pcVar5 + 0x8958) = fVar2 + 6.0;
    fVar2 = (float)RAND(fVar10,(char *)0x3f800000);
    fVar10 = extraout_s0_05;
    break;
  case 1:
    fVar9 = *(float *)(param_1 + 0x14);
    fVar2 = *(float *)(param_1 + 0x18);
    pcVar5 = this + iVar6 * 0x1ac;
    *(float *)(pcVar5 + 0x8950) = *(float *)(param_1 + 0x10) + 0.0;
    *(float *)(pcVar5 + 0x8954) = fVar9 + 2.5;
    *(float *)(pcVar5 + 0x8958) = fVar2 + 6.0;
    fVar2 = (float)RAND(fVar10,(char *)0x3f800000);
    fVar10 = extraout_s0_04;
    break;
  case 2:
    fVar9 = *(float *)(param_1 + 0x14);
    fVar2 = *(float *)(param_1 + 0x18);
    *(float *)(this + iVar6 * 0x1ac + 0x8950) = *(float *)(param_1 + 0x10) + 0.0;
    *(float *)(this + iVar6 * 0x1ac + 0x8954) = fVar9 + 3.5;
    *(float *)(this + iVar6 * 0x1ac + 0x8958) = fVar2 + 17.0;
    fVar10 = (float)RAND(fVar10,(char *)0x3f800000);
    *(float *)(this + iVar6 * 0x1ac + 0x8950) = ((fVar10 - 0.5) + (fVar10 - 0.5)) * 3.0;
    fVar10 = (float)RAND(extraout_s0_03,(char *)0x3f800000);
    *(float *)(this + iVar6 * 0x1ac + 0x8a8c) = fVar8;
    bVar7 = *(int *)(Game + 0x71900) == 7;
    if (bVar7) {
      *(undefined4 *)(this + iVar6 * 0x1ac + 0x8a8c) = 0;
      fVar8 = 0.0;
    }
    *(float *)(this + iVar6 * 0x1ac + 0x8a88) = fVar10 * 6.2831855;
    if (bVar7) {
      *(float *)(this + iVar6 * 0x1ac + 0x8a88) = fVar8;
    }
    goto switchD_00073364_default;
  case 3:
    goto LAB_00073748;
  case 4:
LAB_0007362c:
    fVar9 = *(float *)(param_1 + 0x14);
    fVar2 = *(float *)(param_1 + 0x18);
    pcVar5 = this + iVar6 * 0x1ac;
    param_2 = 4;
    *(float *)(pcVar5 + 0x8950) = *(float *)(param_1 + 0x10) + 0.0;
    *(float *)(pcVar5 + 0x8954) = fVar9 + 2.5;
    *(float *)(pcVar5 + 0x8958) = fVar2 + 6.0;
    fVar2 = (float)RAND(fVar10,(char *)0x3f800000);
    fVar10 = extraout_s0_01;
    break;
  case 5:
    fVar9 = *(float *)(param_1 + 0x18);
    fVar2 = *(float *)(param_1 + 0x14);
    fVar8 = *(float *)(param_1 + 0x10) + 0.0;
    pcVar5 = this + iVar6 * 0x1ac;
    goto LAB_000733b8;
  case 6:
    fVar9 = *(float *)(param_1 + 0x18);
    fVar2 = *(float *)(param_1 + 0x14);
    fVar8 = *(float *)(param_1 + 0x10) + 0.0;
    pcVar5 = this + iVar6 * 0x1ac;
    goto LAB_000733b8;
  case 7:
    fVar8 = 0.0;
    fVar9 = *(float *)(param_1 + 0x10);
    fVar2 = *(float *)(param_1 + 0x14);
    pcVar5 = this + iVar6 * 0x1ac;
    *(float *)(pcVar5 + 0x8958) = *(float *)(param_1 + 0x18) + 0.0;
    *(float *)(pcVar5 + 0x8954) = fVar2 + 2.5;
    *(float *)(pcVar5 + 0x8950) = fVar9 + 0.0;
    goto LAB_00073584;
  case 8:
    fVar8 = *(float *)(param_1 + 0x10) + 0.0;
    fVar9 = *(float *)(param_1 + 0x18);
    fVar2 = *(float *)(param_1 + 0x14);
    pcVar5 = this + iVar6 * 0x1ac;
LAB_000733b8:
    fVar11 = 0.0;
    *(float *)(pcVar5 + 0x8950) = fVar8;
    *(float *)(pcVar5 + 0x8954) = fVar2 + 2.5;
    *(float *)(pcVar5 + 0x8958) = fVar9 + 0.0;
    fVar8 = (float)RAND(fVar10,(char *)0x3f800000);
    *(float *)(pcVar5 + 0x8a88) = fVar8 * 6.2831855;
    if (in_stack_00000000 != 0.0) {
      fVar8 = 1.0 / (in_stack_00000000 * 60.0);
      fVar11 = (fVar8 + fVar8) * 3.1415927;
    }
    *(float *)(this + iVar6 * 0x1ac + 0x8a8c) = fVar11 * *(float *)(this + 0x54);
  default:
    goto switchD_00073364_default;
  }
LAB_00073694:
  *(float *)(pcVar5 + 0x8950) = ((fVar2 - 0.5) + (fVar2 - 0.5)) * 3.0;
LAB_00073584:
  fVar10 = (float)RAND(fVar10,(char *)0x3f800000);
  *(float *)(pcVar5 + 0x8a8c) = fVar8;
  *(float *)(pcVar5 + 0x8a88) = fVar10 * 6.2831855;
switchD_00073364_default:
  iVar1 = LocFromPos(this,*(undefined4 *)(this + iVar6 * 0x1ac + 0x8950),
                     *(undefined4 *)(this + iVar6 * 0x1ac + 0x8954),
                     *(undefined4 *)(this + iVar6 * 0x1ac + 0x8958));
  fVar8 = extraout_s0;
  if (*(char *)(iVar1 + 0x30) != '\x0e') {
    *(int *)(this + iVar6 * 0x1ac + 0x8970) = param_2;
    uVar3 = *(undefined4 *)(param_3 + 0x3fc);
    this[iVar6 * 0x1ac + 0x8a84] = (cRSubGame)0x1;
    *(undefined4 *)(this + iVar6 * 0x1ac + 0x8974) = uVar3;
    *(undefined4 *)(this + iVar6 * 0x1ac + 0x8968) = 1;
    fVar8 = (float)RAND(extraout_s0,(char *)0x3f800000);
    if (0.5 < fVar8) {
      *(float *)(this + iVar6 * 0x1ac + 0x8a8c) = -*(float *)(this + iVar6 * 0x1ac + 0x8a8c);
    }
    pcVar4 = (cRBod *)(this + iVar6 * 0x1ac + 0x88f4);
    cLinkedList<cRBod>::Add((cLinkedList<cRBod> *)(Game + 0x358),pcVar4);
    cRSubRing::Init((int)pcVar4);
    fVar8 = (float)(*(code *)**(undefined4 **)(this + iVar6 * 0x1ac + 0x88f4))(pcVar4);
  }
  return fVar8;
}
