/*
 * mangled: _ZN9cRSubGame9AddHealthEP8cRSubLocP10cRSubGoldy
 * demangled: cRSubGame::AddHealth(cRSubLoc*, cRSubGoldy*)
 * address: 0006e250
 * size: 384
 */

/* cRSubGame::AddHealth(cRSubLoc*, cRSubGoldy*) */

void __thiscall cRSubGame::AddHealth(cRSubGame *this,cRSubLoc *param_1,cRSubGoldy *param_2)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  cRSubGame *pcVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  float fVar12;
  float fVar13;
  float fVar14;

  fVar2 = DAT_0006e3d4;
  fVar1 = DAT_0006e3d0;
  pcVar7 = this + 0x3094;
  iVar8 = 0;
  iVar9 = DAT_0006e3e0 + 0x6e280;
  do {
    iVar5 = *(int *)pcVar7;
    pcVar7 = pcVar7 + 0x68;
    if (iVar5 == 0) {
      fVar12 = DAT_0006e3d0 + *(float *)(param_1 + 0x10);
      iVar10 = iVar8 * 0x68;
      fVar13 = *(float *)(param_1 + 0x14);
      fVar14 = *(float *)(param_1 + 0x18);
      iVar5 = **(int **)(iVar9 + DAT_0006e3e4);
      *(undefined4 *)(this + iVar10 + 0x3094) = 1;
      *(float *)(this + iVar10 + 0x3078) = fVar12;
      *(cRSubGoldy **)(this + iVar10 + 0x3098) = param_2;
      *(float *)(this + iVar10 + 0x3080) = fVar14 + fVar1;
      *(float *)(this + iVar10 + 0x307c) = fVar2 + fVar13;
      cLinkedList<cRBod>::Add
                ((cLinkedList<cRBod> *)(iVar5 + 0x358),(cRBod *)(this + iVar10 + 0x3068));
      iVar9 = cRSpriteManager::New(*(int *)(iVar9 + DAT_0006e3e8),*(int *)(param_2 + 0x370),0x2b,-1)
      ;
      *(float *)(iVar9 + 100) = fVar2;
      *(float *)(iVar9 + 0x78) = fVar1;
      *(float *)(iVar9 + 0x68) = fVar1;
      *(float *)(iVar9 + 0x6c) = fVar1;
      *(float *)(iVar9 + 0x60) = fVar2;
      uVar3 = *(undefined4 *)(this + iVar10 + 0x3078);
      uVar4 = *(undefined4 *)(this + iVar10 + 0x307c);
      uVar6 = *(undefined4 *)(this + iVar10 + 0x3080);
      uVar11 = *(uint *)(iVar9 + 4);
      *(int *)(this + iVar10 + 0x30c0) = iVar9;
      *(uint *)(iVar9 + 4) = uVar11 | 0x800;
      *(undefined4 *)(iVar9 + 0x48) = uVar3;
      *(undefined4 *)(iVar9 + 0x4c) = uVar4;
      *(undefined4 *)(iVar9 + 0x50) = uVar6;
      *(float *)(this + iVar10 + 0x30c8) = fVar1;
      *(cRSubLoc **)(this + iVar10 + 0x30c4) = param_1;
      if (((int)*(float *)(this + iVar10 + 0x3080) & 1U) == 0) {
        *(undefined4 *)(this + iVar10 + 0x30c8) = DAT_0006e3d8;
      }
      *(undefined4 *)(this + iVar8 * 0x68 + 0x30cc) = DAT_0006e3dc;
      return;
    }
    iVar8 = iVar8 + 1;
  } while (iVar8 != 8);
  return;
}
