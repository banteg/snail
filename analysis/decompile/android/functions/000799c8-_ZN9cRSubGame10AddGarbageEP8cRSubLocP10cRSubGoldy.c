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
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 in_r2;
  undefined4 uVar5;
  cRSubLoc *pcVar6;
  int iVar7;
  uint in_fpscr;
  float in_s0;
  float fVar8;

  pcVar6 = param_1 + 0x657c;
  iVar3 = 0;
  do {
    iVar7 = *(int *)pcVar6;
    pcVar6 = pcVar6 + 0xb8;
    if (iVar7 == 0) {
      iVar3 = iVar3 * 0xb8;
      *(undefined4 *)(param_1 + iVar3 + 0x6578) = *(undefined4 *)(param_1 + 0x6500);
      *(undefined4 *)(param_1 + iVar3 + 0x65b8) = in_r2;
      *(cRBod **)(param_1 + 0x6500) = (cRBod *)(param_1 + iVar3 + 0x6504);
      fVar1 = (float)RAND(in_s0,(char *)0x3ecccccd);
      *(undefined4 *)(param_1 + iVar3 + 0x657c) = 1;
      *(float *)(param_1 + iVar3 + 0x6594) = (fVar1 + 1.0) * 0.6;
      tMatrix::Identity((tMatrix *)(param_1 + iVar3 + 0x6530));
      fVar1 = *(float *)(param_2 + 0x14);
      fVar8 = *(float *)(param_2 + 0x18);
      *(float *)(param_1 + iVar3 + 0x6560) = *(float *)(param_2 + 0x10) + 0.0;
      *(float *)(param_1 + iVar3 + 0x6564) = *(float *)(param_1 + iVar3 + 0x6594) + fVar1;
      *(float *)(param_1 + iVar3 + 0x6568) = fVar8 + 0.0;
      CalcRealPos((cRSubGame *)param_1,(tVector *)(param_1 + iVar3 + 0x6560),
                  (float *)(param_1 + iVar3 + 0x6598));
      cLinkedList<cRBod>::AddBefore
                ((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(param_1 + iVar3 + 0x6504),
                 (cRBod *)(param_1 + 0xfac4));
      iVar7 = *(int *)(*(int *)(param_1 + iVar3 + 0x65b8) + 0x370);
      uVar2 = gRMathRand2();
      fVar1 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
      iVar7 = cRSpriteManager::New
                        ((int)&gRSpriteManager,iVar7,(int)(fVar1 * 3.0517578e-05 * 4.0) + 0x66,-1);
      param_1[iVar3 + 0x65b4] = (cRSubLoc)0x0;
      *(undefined4 *)(iVar7 + 0x6c) = 0;
      *(undefined4 *)(iVar7 + 0x78) = 0;
      *(undefined4 *)(iVar7 + 0x68) = 0;
      uVar2 = *(undefined4 *)(param_1 + iVar3 + 0x6594);
      *(undefined4 *)(iVar7 + 100) = uVar2;
      *(undefined4 *)(iVar7 + 0x60) = uVar2;
      uVar2 = *(undefined4 *)(param_1 + iVar3 + 0x6560);
      uVar4 = *(undefined4 *)(param_1 + iVar3 + 0x6564);
      uVar5 = *(undefined4 *)(param_1 + iVar3 + 0x6568);
      *(uint *)(iVar7 + 4) = *(uint *)(iVar7 + 4) | 0x800;
      *(undefined4 *)(iVar7 + 0x48) = uVar2;
      *(undefined4 *)(iVar7 + 0x4c) = uVar4;
      *(undefined4 *)(iVar7 + 0x50) = uVar5;
      *(cRSubGoldy **)(param_1 + iVar3 + 0x65b0) = param_2;
      *(int *)(param_1 + iVar3 + 0x65ac) = iVar7;
      return;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0x32);
  RShellWarning("Run Out of Garbage Slots");
  return;
}
