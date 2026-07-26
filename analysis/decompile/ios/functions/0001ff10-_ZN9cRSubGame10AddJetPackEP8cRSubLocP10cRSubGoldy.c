/*
 * mangled: _ZN9cRSubGame10AddJetPackEP8cRSubLocP10cRSubGoldy
 * demangled: cRSubGame::AddJetPack(cRSubLoc*, cRSubGoldy*)
 * address: 0001ff10
 * size: 504
 */

/* cRSubGame::AddJetPack(cRSubLoc*, cRSubGoldy*) */

void __thiscall cRSubGame::AddJetPack(cRSubGame *this,cRSubLoc *param_1,cRSubGoldy *param_2)

{
  undefined4 uVar1;
  cRSubGame *pcVar2;
  int iVar3;
  undefined4 uVar4;
  cRSubLoc cVar5;
  int iVar6;
  bool bVar7;
  bool bVar8;
  float fVar9;
  float fVar10;
  float fVar11;

  if (*(int *)(this + 0x28a4) == 0) {
    *(undefined4 *)(this + 0x28a4) = 1;
    *(cRSubGoldy **)(this + 0x28a8) = param_2;
    fVar10 = *(float *)(param_1 + 0x14);
    fVar9 = *(float *)(param_1 + 0x10) + 0.0;
    pcVar2 = this + 0x2888;
    fVar11 = *(float *)(param_1 + 0x18);
    *(float *)pcVar2 = fVar9;
    *(float *)(this + 0x2890) = fVar11 + 0.0;
    *(float *)(this + 0x288c) = fVar10 + 1.5;
    cVar5 = (cRSubLoc)((byte)param_1[0x32] & 7);
    if (cVar5 == (cRSubLoc)0x3) {
      if ((param_1[-0x14] == (cRSubLoc)0xe) && (param_1[0xb8] == (cRSubLoc)0xe)) {
        *(float *)pcVar2 = fVar9 + 0.5;
      }
    }
    else {
      bVar7 = cVar5 == (cRSubLoc)0x4;
      if (bVar7) {
        cVar5 = param_1[-0x58];
      }
      bVar8 = bVar7 && cVar5 == (cRSubLoc)0xe;
      if (bVar7 && cVar5 == (cRSubLoc)0xe) {
        bVar8 = param_1[0x74] == (cRSubLoc)0xe;
      }
      if (bVar8) {
        *(float *)pcVar2 = fVar9 - 0.5;
      }
    }
    iVar3 = *(int *)PTR__Game_001b60b8;
    if ((*(uint *)(this + 0x287c) & 0x200) == 0) {
      if (*(int *)(iVar3 + 0x35c) == 0) {
        *(cRSubGame **)(iVar3 + 0x35c) = this + 0x2878;
        *(undefined4 *)(this + 0x2880) = 0;
        *(undefined4 *)(*(int *)(iVar3 + 0x35c) + 0xc) = 0;
      }
      else {
        *(cRSubGame **)(*(int *)(iVar3 + 0x35c) + 8) = this + 0x2878;
        *(int *)(*(int *)(*(int *)(iVar3 + 0x35c) + 8) + 0xc) = *(int *)(iVar3 + 0x35c);
        iVar6 = *(int *)(*(int *)(iVar3 + 0x35c) + 8);
        *(int *)(iVar3 + 0x35c) = iVar6;
        *(undefined4 *)(iVar6 + 8) = 0;
      }
      *(uint *)(this + 0x287c) = *(uint *)(this + 0x287c) | 0x200;
    }
    else {
      RShellError("List ADD");
    }
    iVar3 = cRSpriteManager::New
                      ((int)PTR__gRSpriteManager_001b61e4,*(int *)(param_2 + 0x370),0x70,-1);
    *(int *)(this + 0x28d0) = iVar3;
    *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) | 0x800;
    *(undefined4 *)(*(int *)(this + 0x28d0) + 0x78) = 0;
    *(undefined4 *)(*(int *)(this + 0x28d0) + 0x68) = 0;
    *(undefined4 *)(*(int *)(this + 0x28d0) + 0x6c) = 0;
    *(undefined4 *)(*(int *)(this + 0x28d0) + 0x60) = 0x3fc00000;
    *(undefined4 *)(*(int *)(this + 0x28d0) + 100) = 0x3fc00000;
    iVar3 = *(int *)(this + 0x28d0);
    uVar1 = *(undefined4 *)(this + 0x288c);
    uVar4 = *(undefined4 *)(this + 0x2890);
    *(undefined4 *)(iVar3 + 0x48) = *(undefined4 *)(this + 0x2888);
    *(undefined4 *)(iVar3 + 0x4c) = uVar1;
    *(undefined4 *)(iVar3 + 0x50) = uVar4;
    *(cRSubLoc **)(this + 0x28d4) = param_1;
    *(undefined4 *)(this + 0x28d8) = 0;
    if (((int)*(float *)(this + 0x2890) & 1U) == 0) {
      *(undefined4 *)(this + 0x28d8) = 0x3f000000;
    }
    *(undefined4 *)(this + 0x28dc) = 0x3c520d21;
  }
  return;
}
