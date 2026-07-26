/*
 * mangled: _ZN9cRSubGame10AddJetPackEP8cRSubLocP10cRSubGoldy
 * demangled: cRSubGame::AddJetPack(cRSubLoc*, cRSubGoldy*)
 * address: 0006e074
 * size: 448
 */

/* cRSubGame::AddJetPack(cRSubLoc*, cRSubGoldy*) */

void __thiscall cRSubGame::AddJetPack(cRSubGame *this,cRSubLoc *param_1,cRSubGoldy *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  float fVar5;
  float fVar6;
  float fVar7;

  if (*(int *)(this + 0x2f1c) == 0) {
    fVar6 = *(float *)(param_1 + 0x14);
    fVar7 = *(float *)(param_1 + 0x10) + 0.0;
    fVar5 = *(float *)(param_1 + 0x18);
    *(cRSubGoldy **)(this + 0x2f20) = param_2;
    *(undefined4 *)(this + 0x2f1c) = 1;
    *(float *)(this + 0x2f00) = fVar7;
    *(float *)(this + 0x2f04) = fVar6 + 1.5;
    *(float *)(this + 0x2f08) = fVar5 + 0.0;
    if (((byte)param_1[0x34] & 7) == 3) {
      if ((param_1[-0x18] == (cRSubLoc)0xe) && (param_1[0xc0] == (cRSubLoc)0xe)) {
        *(float *)(this + 0x2f00) = fVar7 + 0.5;
      }
    }
    else if (((((byte)param_1[0x34] & 7) == 4) && (param_1[-0x60] == (cRSubLoc)0xe)) &&
            (param_1[0x78] == (cRSubLoc)0xe)) {
      *(float *)(this + 0x2f00) = fVar7 - 0.5;
    }
    cLinkedList<cRBod>::Add((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)(this + 0x2ef0));
    iVar1 = cRSpriteManager::New((int)&gRSpriteManager,*(int *)(param_2 + 0x370),0x70,-1);
    *(undefined4 *)(iVar1 + 0x78) = 0;
    *(undefined4 *)(iVar1 + 0x68) = 0;
    *(undefined4 *)(iVar1 + 0x6c) = 0;
    *(undefined4 *)(iVar1 + 100) = 0x3fc00000;
    *(undefined4 *)(iVar1 + 0x60) = 0x3fc00000;
    uVar2 = *(undefined4 *)(this + 0x2f00);
    uVar3 = *(undefined4 *)(this + 0x2f04);
    uVar4 = *(undefined4 *)(this + 0x2f08);
    *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 0x800;
    *(undefined4 *)(iVar1 + 0x48) = uVar2;
    *(undefined4 *)(iVar1 + 0x4c) = uVar3;
    *(undefined4 *)(iVar1 + 0x50) = uVar4;
    *(cRSubLoc **)(this + 0x2f4c) = param_1;
    *(int *)(this + 0x2f48) = iVar1;
    *(undefined4 *)(this + 0x2f50) = 0;
    if (((int)*(float *)(this + 0x2f08) & 1U) == 0) {
      *(undefined4 *)(this + 0x2f50) = 0x3f000000;
    }
    *(undefined4 *)(this + 0x2f54) = 0x3c520d21;
  }
  return;
}
