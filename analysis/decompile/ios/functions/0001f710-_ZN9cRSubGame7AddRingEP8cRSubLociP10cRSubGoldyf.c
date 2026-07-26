/*
 * mangled: _ZN9cRSubGame7AddRingEP8cRSubLociP10cRSubGoldyf
 * demangled: cRSubGame::AddRing(cRSubLoc*, int, cRSubGoldy*, float)
 * address: 0001f710
 * size: 1864
 */

/* cRSubGame::AddRing(cRSubLoc*, int, cRSubGoldy*, float) */

void __thiscall
cRSubGame::AddRing(cRSubGame *this,cRSubLoc *param_1,int param_2,cRSubGoldy *param_3,float param_4)

{
  undefined *puVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  cRSubGame *pcVar6;
  int iVar7;
  cRSubGame *pcVar8;
  uint in_fpscr;
  float fVar9;
  float fVar10;
  float fVar11;
  uint uVar12;
  undefined4 uVar13;

  iVar3 = 0;
  if (*(int *)(this + 0x82f0) != 0) {
    if (*(int *)(this + 0x849c) != 0) {
      return;
    }
    iVar3 = 1;
  }
  fVar9 = *(float *)(this + 0x60) * -0.3 + 2.0;
  uVar12 = in_fpscr & 0xfffffff | (uint)(fVar9 == 0.0) << 0x1e;
  if (SUB41(uVar12 >> 0x1e,0)) {
    fVar9 = 0.0;
  }
  else {
    fVar9 = 1.0 / (fVar9 * 60.0);
  }
  fVar11 = (float)VectorSignedToFloat(*(undefined4 *)(param_3 + 0x2f0),(byte)(uVar12 >> 0x16) & 3);
  fVar9 = fVar9 * fVar11 * 0.125;
  fVar9 = (fVar9 + fVar9) * 3.1415927 * *(float *)(this + 0x4c);
  tMatrix::Identity((tMatrix *)(this + iVar3 * 0x1ac + 0x82a8));
  *(cRSubGoldy **)(this + iVar3 * 0x1ac + 0x82f4) = param_3;
  if (param_2 == 4) {
    fVar11 = (float)RAND(1.0,"RT");
    if (fVar11 <= 0.93) goto switchD_0001f7fc_caseD_4;
    param_2 = 3;
switchD_0001f7fc_caseD_3:
    fVar11 = *(float *)(param_1 + 0x14);
    pcVar8 = this + iVar3 * 0x1ac;
    fVar10 = *(float *)(param_1 + 0x18);
    pcVar6 = pcVar8 + 0x8000;
    *(float *)(pcVar8 + 0x82d8) = *(float *)(param_1 + 0x10) + 0.0;
    *(float *)(pcVar8 + 0x82dc) = fVar11 + 2.5;
    *(float *)(pcVar8 + 0x82e0) = fVar10 + 6.0;
    fVar11 = (float)RAND(1.0,"RR6");
    pcVar2 = "RR7";
    *(float *)(pcVar8 + 0x82d8) = ((fVar11 - 0.5) + (fVar11 - 0.5)) * 3.0;
    goto LAB_0001fb00;
  }
  switch(param_2) {
  case 0:
    fVar11 = *(float *)(param_1 + 0x14);
    pcVar8 = this + iVar3 * 0x1ac;
    fVar10 = *(float *)(param_1 + 0x18);
    pcVar6 = pcVar8 + 0x8000;
    *(float *)(pcVar8 + 0x82d8) = *(float *)(param_1 + 0x10) + 0.0;
    *(float *)(pcVar8 + 0x82dc) = fVar11 + 2.5;
    *(float *)(pcVar8 + 0x82e0) = fVar10 + 6.0;
    fVar11 = (float)RAND(1.0,"RR");
    pcVar2 = "RR1";
    *(float *)(pcVar8 + 0x82d8) = ((fVar11 - 0.5) + (fVar11 - 0.5)) * 3.0;
    goto LAB_0001fb00;
  case 1:
    fVar11 = *(float *)(param_1 + 0x14);
    pcVar8 = this + iVar3 * 0x1ac;
    fVar10 = *(float *)(param_1 + 0x18);
    pcVar6 = pcVar8 + 0x8000;
    *(float *)(pcVar8 + 0x82d8) = *(float *)(param_1 + 0x10) + 0.0;
    *(float *)(pcVar8 + 0x82dc) = fVar11 + 2.5;
    *(float *)(pcVar8 + 0x82e0) = fVar10 + 6.0;
    fVar11 = (float)RAND(1.0,"RR2");
    pcVar2 = "RR3";
    *(float *)(pcVar8 + 0x82d8) = ((fVar11 - 0.5) + (fVar11 - 0.5)) * 3.0;
LAB_0001fb00:
    fVar11 = (float)RAND(1.0,pcVar2);
    *(float *)(pcVar6 + 0x410) = fVar11 * 6.2831855;
    *(float *)(pcVar8 + 0x8414) = fVar9;
    break;
  case 2:
    uVar13 = 0;
    fVar11 = *(float *)(param_1 + 0x14);
    fVar10 = *(float *)(param_1 + 0x18);
    *(float *)(this + iVar3 * 0x1ac + 0x82d8) = *(float *)(param_1 + 0x10) + 0.0;
    *(float *)(this + iVar3 * 0x1ac + 0x82dc) = fVar11 + 3.5;
    *(float *)(this + iVar3 * 0x1ac + 0x82e0) = fVar10 + 17.0;
    fVar11 = (float)RAND(1.0,"RR4");
    *(float *)(this + iVar3 * 0x1ac + 0x82d8) = ((fVar11 - 0.5) + (fVar11 - 0.5)) * 3.0;
    fVar11 = (float)RAND(1.0,"RR5");
    puVar1 = PTR__Game_001b60b8;
    *(float *)(this + iVar3 * 0x1ac + 0x8414) = fVar9;
    *(float *)(this + iVar3 * 0x1ac + 0x8410) = fVar11 * 6.2831855;
    if (*(int *)(*(int *)puVar1 + 0x72bd0) == 7) {
      *(undefined4 *)(this + iVar3 * 0x1ac + 0x8410) = uVar13;
      *(undefined4 *)(this + iVar3 * 0x1ac + 0x8414) = uVar13;
    }
    break;
  case 3:
    goto switchD_0001f7fc_caseD_3;
  case 4:
switchD_0001f7fc_caseD_4:
    fVar11 = *(float *)(param_1 + 0x14);
    fVar10 = *(float *)(param_1 + 0x18);
    *(float *)(this + iVar3 * 0x1ac + 0x82d8) = *(float *)(param_1 + 0x10) + 0.0;
    *(float *)(this + iVar3 * 0x1ac + 0x82dc) = fVar11 + 2.5;
    *(float *)(this + iVar3 * 0x1ac + 0x82e0) = fVar10 + 6.0;
    fVar11 = (float)RAND(1.0,"RR8");
    *(float *)(this + iVar3 * 0x1ac + 0x82d8) = ((fVar11 - 0.5) + (fVar11 - 0.5)) * 3.0;
    fVar11 = (float)RAND(1.0,"RR9");
    *(float *)(this + iVar3 * 0x1ac + 0x8410) = fVar11 * 6.2831855;
    param_2 = 4;
    *(float *)(this + iVar3 * 0x1ac + 0x8414) = fVar9;
    break;
  case 5:
    fVar9 = *(float *)(param_1 + 0x14);
    pcVar2 = "RR10";
    fVar11 = *(float *)(param_1 + 0x18);
    pcVar6 = this + iVar3 * 0x1ac + 0x8000;
    *(float *)(this + iVar3 * 0x1ac + 0x82d8) = *(float *)(param_1 + 0x10) + 0.0;
    *(float *)(this + iVar3 * 0x1ac + 0x82dc) = fVar9 + 2.5;
    *(float *)(this + iVar3 * 0x1ac + 0x82e0) = fVar11 + 0.0;
    goto LAB_0001f870;
  case 6:
    fVar9 = *(float *)(param_1 + 0x14);
    fVar11 = *(float *)(param_1 + 0x18);
    pcVar2 = "RR12";
    pcVar6 = this + iVar3 * 0x1ac + 0x8000;
    *(float *)(this + iVar3 * 0x1ac + 0x82d8) = *(float *)(param_1 + 0x10) + 0.0;
    *(float *)(this + iVar3 * 0x1ac + 0x82dc) = fVar9 + 2.5;
    *(float *)(this + iVar3 * 0x1ac + 0x82e0) = fVar11 + 0.0;
    goto LAB_0001f870;
  case 7:
    uVar13 = 0;
    fVar9 = *(float *)(param_1 + 0x14);
    fVar11 = *(float *)(param_1 + 0x18);
    *(float *)(this + iVar3 * 0x1ac + 0x82d8) = *(float *)(param_1 + 0x10) + 0.0;
    *(float *)(this + iVar3 * 0x1ac + 0x82dc) = fVar9 + 2.5;
    *(float *)(this + iVar3 * 0x1ac + 0x82e0) = fVar11 + 0.0;
    fVar9 = (float)RAND(1.0,"RR13");
    *(float *)(this + iVar3 * 0x1ac + 0x8410) = fVar9 * 6.2831855;
    *(undefined4 *)(this + iVar3 * 0x1ac + 0x8414) = uVar13;
    break;
  case 8:
    fVar9 = *(float *)(param_1 + 0x14);
    fVar11 = *(float *)(param_1 + 0x18);
    pcVar2 = "RR11";
    pcVar6 = this + iVar3 * 0x1ac + 0x8000;
    *(float *)(this + iVar3 * 0x1ac + 0x82d8) = *(float *)(param_1 + 0x10) + 0.0;
    *(float *)(this + iVar3 * 0x1ac + 0x82dc) = fVar9 + 2.5;
    *(float *)(this + iVar3 * 0x1ac + 0x82e0) = fVar11 + 0.0;
LAB_0001f870:
    fVar11 = 1.0;
    fVar10 = 0.0;
    fVar9 = (float)RAND(1.0,pcVar2);
    *(float *)(pcVar6 + 0x410) = fVar9 * 6.2831855;
    if (param_4 != fVar10) {
      fVar11 = fVar11 / (param_4 * 60.0);
      fVar10 = (fVar11 + fVar11) * 3.1415927;
    }
    *(float *)(this + iVar3 * 0x1ac + 0x8414) = fVar10 * *(float *)(this + 0x4c);
  }
  iVar7 = iVar3 * 0x1ac;
  uVar12 = (uint)(*(float *)(this + iVar7 + 0x82d8) + 4.0);
  if (6 < (int)uVar12) {
    uVar12 = 7;
  }
  uVar4 = (int)*(float *)(this + iVar7 + 0x82e0);
  if (0xdaa < (int)*(float *)(this + iVar7 + 0x82e0)) {
    uVar4 = 0xdab;
  }
  if (this[(uVar12 & ~((int)uVar12 >> 0x1f)) * 0x44 + (uVar4 & ~((int)uVar4 >> 0x1f)) * 0x220 +
           0x13488] == (cRSubGame)0xe) {
    return;
  }
  *(int *)(this + iVar7 + 0x82f8) = param_2;
  *(undefined4 *)(this + iVar7 + 0x82fc) = *(undefined4 *)(param_3 + 0x3f4);
  *(undefined4 *)(this + iVar7 + 0x82f0) = 1;
  this[iVar7 + 0x840c] = (cRSubGame)0x1;
  fVar9 = (float)RAND(1.0,"RT1");
  if (0.5 < fVar9) {
    *(float *)(this + iVar7 + 0x8414) = -*(float *)(this + iVar7 + 0x8414);
  }
  iVar5 = *(int *)PTR__Game_001b60b8;
  if ((*(uint *)(this + iVar7 + 0x8280) & 0x200) == 0) {
    if (*(int *)(iVar5 + 0x35c) == 0) {
      *(cRSubGame **)(iVar5 + 0x35c) = this + iVar7 + 0x827c;
      *(undefined4 *)(this + iVar7 + 0x8284) = 0;
      *(undefined4 *)(*(int *)(iVar5 + 0x35c) + 0xc) = 0;
    }
    else {
      *(cRSubGame **)(*(int *)(iVar5 + 0x35c) + 8) = this + iVar7 + 0x827c;
      *(int *)(*(int *)(*(int *)(iVar5 + 0x35c) + 8) + 0xc) = *(int *)(iVar5 + 0x35c);
      iVar7 = *(int *)(*(int *)(iVar5 + 0x35c) + 8);
      *(int *)(iVar5 + 0x35c) = iVar7;
      *(undefined4 *)(iVar7 + 8) = 0;
    }
    *(uint *)(this + iVar3 * 0x1ac + 0x8280) = *(uint *)(this + iVar3 * 0x1ac + 0x8280) | 0x200;
  }
  else {
    RShellError("List ADD");
  }
  iVar7 = iVar3 * 0x1ac + 0x827c;
  cRSubRing::Init((int)(this + iVar7));
                    /* WARNING: Could not recover jumptable at 0x0001fa5c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)**(undefined4 **)(this + iVar3 * 0x1ac + 0x827c))(this + iVar7);
  return;
}
