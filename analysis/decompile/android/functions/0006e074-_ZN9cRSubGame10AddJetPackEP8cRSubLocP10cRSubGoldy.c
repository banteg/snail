/*
 * mangled: _ZN9cRSubGame10AddJetPackEP8cRSubLocP10cRSubGoldy
 * demangled: cRSubGame::AddJetPack(cRSubLoc*, cRSubGoldy*)
 * address: 0006e074
 * size: 448
 */

/* cRSubGame::AddJetPack(cRSubLoc*, cRSubGoldy*) */

void __thiscall cRSubGame::AddJetPack(cRSubGame *this,cRSubLoc *param_1,cRSubGoldy *param_2)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  float fVar7;
  float fVar8;
  float fVar9;

  fVar2 = DAT_0006e238;
  fVar1 = DAT_0006e234;
  iVar6 = DAT_0006e244 + 0x6e09c;
  if (*(int *)(this + 0x2f1c) == 0) {
    fVar8 = *(float *)(param_1 + 0x14);
    fVar9 = DAT_0006e234 + *(float *)(param_1 + 0x10);
    fVar7 = *(float *)(param_1 + 0x18);
    *(cRSubGoldy **)(this + 0x2f20) = param_2;
    *(undefined4 *)(this + 0x2f1c) = 1;
    *(float *)(this + 0x2f00) = fVar9;
    *(float *)(this + 0x2f04) = fVar2 + fVar8;
    *(float *)(this + 0x2f08) = fVar7 + fVar1;
    if (((byte)param_1[0x34] & 7) == 3) {
      if ((param_1[-0x18] == (cRSubLoc)0xe) && (param_1[0xc0] == (cRSubLoc)0xe)) {
        *(float *)(this + 0x2f00) = fVar9 + DAT_0006e23c;
      }
    }
    else if (((((byte)param_1[0x34] & 7) == 4) && (param_1[-0x60] == (cRSubLoc)0xe)) &&
            (param_1[0x78] == (cRSubLoc)0xe)) {
      *(float *)(this + 0x2f00) = fVar9 - DAT_0006e23c;
    }
    cLinkedList<cRBod>::Add
              ((cLinkedList<cRBod> *)(**(int **)(iVar6 + DAT_0006e248) + 0x358),
               (cRBod *)(this + 0x2ef0));
    iVar6 = cRSpriteManager::New(*(int *)(iVar6 + DAT_0006e24c),*(int *)(param_2 + 0x370),0x70,-1);
    fVar2 = DAT_0006e238;
    fVar1 = DAT_0006e234;
    *(float *)(iVar6 + 0x78) = DAT_0006e234;
    *(float *)(iVar6 + 0x68) = fVar1;
    *(float *)(iVar6 + 0x6c) = fVar1;
    *(float *)(iVar6 + 100) = fVar2;
    *(float *)(iVar6 + 0x60) = fVar2;
    uVar3 = *(undefined4 *)(this + 0x2f00);
    uVar4 = *(undefined4 *)(this + 0x2f04);
    uVar5 = *(undefined4 *)(this + 0x2f08);
    *(uint *)(iVar6 + 4) = *(uint *)(iVar6 + 4) | 0x800;
    *(undefined4 *)(iVar6 + 0x48) = uVar3;
    *(undefined4 *)(iVar6 + 0x4c) = uVar4;
    *(undefined4 *)(iVar6 + 0x50) = uVar5;
    *(cRSubLoc **)(this + 0x2f4c) = param_1;
    *(int *)(this + 0x2f48) = iVar6;
    *(float *)(this + 0x2f50) = fVar1;
    uVar3 = DAT_0006e240;
    if (((int)*(float *)(this + 0x2f08) & 1U) == 0) {
      *(float *)(this + 0x2f50) = DAT_0006e23c;
    }
    *(undefined4 *)(this + 0x2f54) = uVar3;
  }
  return;
}
