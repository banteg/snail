/*
 * mangled: _ZN9cRSubGame10AddGarbageEP8cRSubLocP10cRSubGoldy
 * demangled: cRSubGame::AddGarbage(cRSubLoc*, cRSubGoldy*)
 * address: 000799c8
 * size: 540
 */

/* cRSubGame::AddGarbage(cRSubLoc*, cRSubGoldy*) */

void cRSubGame::AddGarbage(cRSubLoc *param_1,cRSubGoldy *param_2)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 in_r2;
  undefined4 uVar6;
  cRSubLoc *pcVar7;
  int iVar8;
  int iVar9;
  uint in_fpscr;
  float in_s0;
  float fVar10;

  fVar1 = DAT_00079be4;
  pcVar7 = param_1 + 0x657c;
  iVar4 = 0;
  iVar9 = DAT_00079bf8 + 0x799f4;
  do {
    iVar8 = *(int *)pcVar7;
    pcVar7 = pcVar7 + 0xb8;
    if (iVar8 == 0) {
      iVar4 = iVar4 * 0xb8;
      *(undefined4 *)(param_1 + iVar4 + 0x6578) = *(undefined4 *)(param_1 + 0x6500);
      *(undefined4 *)(param_1 + iVar4 + 0x65b8) = in_r2;
      *(cRBod **)(param_1 + 0x6500) = (cRBod *)(param_1 + iVar4 + 0x6504);
      fVar2 = (float)RAND(in_s0,(char *)0x3ecccccd);
      fVar10 = DAT_00079be8;
      *(undefined4 *)(param_1 + iVar4 + 0x657c) = 1;
      *(float *)(param_1 + iVar4 + 0x6594) = (fVar2 + fVar10) * DAT_00079bec;
      tMatrix::Identity((tMatrix *)(param_1 + iVar4 + 0x6530));
      fVar10 = *(float *)(param_2 + 0x14);
      fVar2 = *(float *)(param_2 + 0x18);
      *(float *)(param_1 + iVar4 + 0x6560) = fVar1 + *(float *)(param_2 + 0x10);
      *(float *)(param_1 + iVar4 + 0x6564) = *(float *)(param_1 + iVar4 + 0x6594) + fVar10;
      *(float *)(param_1 + iVar4 + 0x6568) = fVar2 + fVar1;
      CalcRealPos((cRSubGame *)param_1,(tVector *)(param_1 + iVar4 + 0x6560),
                  (float *)(param_1 + iVar4 + 0x6598));
      cLinkedList<cRBod>::AddBefore
                ((cLinkedList<cRBod> *)(**(int **)(iVar9 + DAT_00079c00) + 0x358),
                 (cRBod *)(param_1 + iVar4 + 0x6504),(cRBod *)(param_1 + 0xfac4));
      iVar8 = *(int *)(*(int *)(param_1 + iVar4 + 0x65b8) + 0x370);
      uVar3 = gRMathRand2();
      fVar10 = (float)VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
      iVar9 = cRSpriteManager::New
                        (*(int *)(iVar9 + DAT_00079c04),iVar8,
                         (int)(fVar10 * DAT_00079bf0 * DAT_00079bf4) + 0x66,-1);
      param_1[iVar4 + 0x65b4] = (cRSubLoc)0x0;
      *(float *)(iVar9 + 0x6c) = fVar1;
      *(float *)(iVar9 + 0x78) = fVar1;
      *(float *)(iVar9 + 0x68) = fVar1;
      uVar3 = *(undefined4 *)(param_1 + iVar4 + 0x6594);
      *(undefined4 *)(iVar9 + 100) = uVar3;
      *(undefined4 *)(iVar9 + 0x60) = uVar3;
      uVar3 = *(undefined4 *)(param_1 + iVar4 + 0x6560);
      uVar5 = *(undefined4 *)(param_1 + iVar4 + 0x6564);
      uVar6 = *(undefined4 *)(param_1 + iVar4 + 0x6568);
      *(uint *)(iVar9 + 4) = *(uint *)(iVar9 + 4) | 0x800;
      *(undefined4 *)(iVar9 + 0x48) = uVar3;
      *(undefined4 *)(iVar9 + 0x4c) = uVar5;
      *(undefined4 *)(iVar9 + 0x50) = uVar6;
      *(cRSubGoldy **)(param_1 + iVar4 + 0x65b0) = param_2;
      *(int *)(param_1 + iVar4 + 0x65ac) = iVar9;
      return;
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 != 0x32);
  RShellWarning((char *)(iVar9 + DAT_00079c08));
  return;
}
