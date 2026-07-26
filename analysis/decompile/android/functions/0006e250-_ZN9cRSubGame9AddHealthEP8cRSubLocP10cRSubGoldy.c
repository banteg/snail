/*
 * mangled: _ZN9cRSubGame9AddHealthEP8cRSubLocP10cRSubGoldy
 * demangled: cRSubGame::AddHealth(cRSubLoc*, cRSubGoldy*)
 * address: 0006e250
 * size: 384
 */

/* cRSubGame::AddHealth(cRSubLoc*, cRSubGoldy*) */

void __thiscall cRSubGame::AddHealth(cRSubGame *this,cRSubLoc *param_1,cRSubGoldy *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  cRSubGame *pcVar6;
  int iVar7;
  uint uVar8;
  float fVar9;
  float fVar10;
  float fVar11;

  iVar1 = Game;
  pcVar6 = this + 0x3094;
  iVar7 = 0;
  do {
    iVar4 = *(int *)pcVar6;
    pcVar6 = pcVar6 + 0x68;
    if (iVar4 == 0) {
      fVar9 = *(float *)(param_1 + 0x10);
      iVar4 = iVar7 * 0x68;
      fVar10 = *(float *)(param_1 + 0x14);
      fVar11 = *(float *)(param_1 + 0x18);
      *(undefined4 *)(this + iVar4 + 0x3094) = 1;
      *(float *)(this + iVar4 + 0x3078) = fVar9 + 0.0;
      *(cRSubGoldy **)(this + iVar4 + 0x3098) = param_2;
      *(float *)(this + iVar4 + 0x3080) = fVar11 + 0.0;
      *(float *)(this + iVar4 + 0x307c) = fVar10 + 0.6;
      cLinkedList<cRBod>::Add
                ((cLinkedList<cRBod> *)(iVar1 + 0x358),(cRBod *)(this + iVar4 + 0x3068));
      iVar1 = cRSpriteManager::New((int)&gRSpriteManager,*(int *)(param_2 + 0x370),0x2b,-1);
      *(undefined4 *)(iVar1 + 100) = 0x3f19999a;
      *(undefined4 *)(iVar1 + 0x78) = 0;
      *(undefined4 *)(iVar1 + 0x68) = 0;
      *(undefined4 *)(iVar1 + 0x6c) = 0;
      *(undefined4 *)(iVar1 + 0x60) = 0x3f19999a;
      uVar2 = *(undefined4 *)(this + iVar4 + 0x3078);
      uVar3 = *(undefined4 *)(this + iVar4 + 0x307c);
      uVar5 = *(undefined4 *)(this + iVar4 + 0x3080);
      uVar8 = *(uint *)(iVar1 + 4);
      *(int *)(this + iVar4 + 0x30c0) = iVar1;
      *(uint *)(iVar1 + 4) = uVar8 | 0x800;
      *(undefined4 *)(iVar1 + 0x48) = uVar2;
      *(undefined4 *)(iVar1 + 0x4c) = uVar3;
      *(undefined4 *)(iVar1 + 0x50) = uVar5;
      *(undefined4 *)(this + iVar4 + 0x30c8) = 0;
      *(cRSubLoc **)(this + iVar4 + 0x30c4) = param_1;
      if (((int)*(float *)(this + iVar4 + 0x3080) & 1U) == 0) {
        *(undefined4 *)(this + iVar4 + 0x30c8) = 0x3f000000;
      }
      *(undefined4 *)(this + iVar7 * 0x68 + 0x30cc) = 0x3c520d21;
      return;
    }
    iVar7 = iVar7 + 1;
  } while (iVar7 != 8);
  return;
}
