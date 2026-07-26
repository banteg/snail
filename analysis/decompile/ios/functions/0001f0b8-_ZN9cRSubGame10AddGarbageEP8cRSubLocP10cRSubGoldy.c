/*
 * mangled: _ZN9cRSubGame10AddGarbageEP8cRSubLocP10cRSubGoldy
 * demangled: cRSubGame::AddGarbage(cRSubLoc*, cRSubGoldy*)
 * address: 0001f0b8
 * size: 700
 */

/* cRSubGame::AddGarbage(cRSubLoc*, cRSubGoldy*) */

void __thiscall cRSubGame::AddGarbage(cRSubGame *this,cRSubLoc *param_1,cRSubGoldy *param_2)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  cRSubGame *pcVar5;
  int iVar6;
  int iVar7;
  uint in_fpscr;
  float fVar8;

  pcVar5 = this + 0x5f04;
  iVar6 = 0;
  do {
    if (*(int *)pcVar5 == 0) {
      iVar7 = iVar6 * 0xb8;
      *(undefined4 *)(this + iVar7 + 0x5f00) = *(undefined4 *)(this + 0x5e88);
      pcVar5 = this + iVar7 + 0x5e8c;
      *(cRSubGame **)(this + 0x5e88) = pcVar5;
      *(cRSubGoldy **)(this + iVar7 + 0x5f40) = param_2;
      fVar1 = (float)RAND(0.4,"Gadd");
      *(undefined4 *)(this + iVar7 + 0x5f04) = 1;
      *(float *)(this + iVar7 + 0x5f1c) = (fVar1 + 1.0) * 0.6;
      tMatrix::Identity((tMatrix *)(this + iVar7 + 0x5eb8));
      fVar8 = *(float *)(param_1 + 0x10);
      fVar1 = *(float *)(param_1 + 0x14);
      *(float *)(this + iVar7 + 0x5ef0) = *(float *)(param_1 + 0x18) + 0.0;
      *(float *)(this + iVar7 + 0x5eec) = *(float *)(this + iVar7 + 0x5f1c) + fVar1;
      *(float *)(this + iVar7 + 0x5ee8) = fVar8 + 0.0;
      CalcRealPos(this,(tVector *)(this + iVar7 + 0x5ee8),(float *)(this + iVar7 + 0x5f20));
      iVar3 = *(int *)PTR__Game_001b60b8;
      if ((*(uint *)(this + iVar7 + 0x5e90) & 0x200) == 0) {
        *(cRSubGame **)(this + iVar7 + 0x5e98) = this + 0xf448;
        if (*(cRSubGame **)(iVar3 + 0x35c) == this + 0xf448) {
          *(cRSubGame **)(this + 0xf450) = pcVar5;
          *(cRSubGame **)(iVar3 + 0x35c) = pcVar5;
          *(undefined4 *)(this + iVar7 + 0x5e94) = 0;
        }
        else {
          *(undefined4 *)(this + iVar7 + 0x5e94) = *(undefined4 *)(this + 0xf450);
          *(cRSubGame **)(this + 0xf450) = pcVar5;
          *(cRSubGame **)(*(int *)(this + iVar7 + 0x5e94) + 0xc) = pcVar5;
        }
        *(uint *)(this + iVar6 * 0xb8 + 0x5e90) = *(uint *)(this + iVar6 * 0xb8 + 0x5e90) | 0x200;
      }
      else {
        RShellError("List ADDbefore");
      }
      iVar7 = *(int *)(*(int *)(this + iVar6 * 0xb8 + 0x5f40) + 0x370);
      uVar2 = gRMathRand2();
      fVar1 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
      iVar7 = cRSpriteManager::New
                        ((int)PTR__gRSpriteManager_001b61e4,iVar7,
                         (int)(fVar1 * 3.0517578e-05 * 4.0) + 0x66,-1);
      *(int *)(this + iVar6 * 0xb8 + 0x5f34) = iVar7;
      *(uint *)(iVar7 + 4) = *(uint *)(iVar7 + 4) | 0x800;
      *(undefined4 *)(*(int *)(this + iVar6 * 0xb8 + 0x5f34) + 0x78) = 0;
      *(undefined4 *)(*(int *)(this + iVar6 * 0xb8 + 0x5f34) + 0x68) = 0;
      *(undefined4 *)(*(int *)(this + iVar6 * 0xb8 + 0x5f34) + 0x6c) = 0;
      *(undefined4 *)(*(int *)(this + iVar6 * 0xb8 + 0x5f34) + 0x60) =
           *(undefined4 *)(this + iVar6 * 0xb8 + 0x5f1c);
      *(undefined4 *)(*(int *)(this + iVar6 * 0xb8 + 0x5f34) + 100) =
           *(undefined4 *)(this + iVar6 * 0xb8 + 0x5f1c);
      iVar7 = *(int *)(this + iVar6 * 0xb8 + 0x5f34);
      uVar2 = *(undefined4 *)(this + iVar6 * 0xb8 + 0x5eec);
      uVar4 = *(undefined4 *)(this + iVar6 * 0xb8 + 0x5ef0);
      *(undefined4 *)(iVar7 + 0x48) = *(undefined4 *)(this + iVar6 * 0xb8 + 0x5ee8);
      *(undefined4 *)(iVar7 + 0x4c) = uVar2;
      *(undefined4 *)(iVar7 + 0x50) = uVar4;
      this[iVar6 * 0xb8 + 0x5f3c] = (cRSubGame)0x0;
      *(cRSubLoc **)(this + iVar6 * 0xb8 + 0x5f38) = param_1;
      return;
    }
    iVar6 = iVar6 + 1;
    pcVar5 = pcVar5 + 0xb8;
  } while (iVar6 != 0x32);
  RShellWarning("Run Out of Garbage Slots");
  return;
}
