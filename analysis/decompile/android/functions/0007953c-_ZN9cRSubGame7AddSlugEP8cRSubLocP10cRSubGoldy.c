/*
 * mangled: _ZN9cRSubGame7AddSlugEP8cRSubLocP10cRSubGoldy
 * demangled: cRSubGame::AddSlug(cRSubLoc*, cRSubGoldy*)
 * address: 0007953c
 * size: 780
 */

/* cRSubGame::AddSlug(cRSubLoc*, cRSubGoldy*) */

void __thiscall cRSubGame::AddSlug(cRSubGame *this,cRSubLoc *param_1,cRSubGoldy *param_2)

{
  byte bVar1;
  cLinkedList<cRBod> *this_00;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  cRSubGame *pcVar6;
  int iVar7;
  int iVar8;
  uint in_fpscr;
  uint uVar9;
  uint uVar10;
  float fVar11;
  float fVar12;

  pcVar6 = this + 0x341c;
  iVar4 = 0;
  do {
    iVar8 = *(int *)pcVar6;
    pcVar6 = pcVar6 + 0xe0;
    if (iVar8 == 0) {
      iVar8 = iVar4 * 0xe0;
      *(undefined4 *)(this + iVar8 + 0x341c) = 1;
      *(cRSubGoldy **)(this + iVar8 + 0x345c) = param_2;
      tMatrix::Identity((tMatrix *)(this + iVar8 + 0x33d4));
      fVar11 = *(float *)(param_1 + 0x14);
      fVar12 = *(float *)(param_1 + 0x18);
      *(float *)(this + iVar8 + 0x3404) = *(float *)(param_1 + 0x10) + 0.0;
      *(float *)(this + iVar8 + 0x3408) = fVar11 + 1.7;
      *(float *)(this + iVar8 + 0x340c) = fVar12 + 0.0;
      CalcRealPos(this,(tVector *)(this + iVar8 + 0x3404),(float *)(this + iVar8 + 0x3434));
      this_00 = (cLinkedList<cRBod> *)(Game + 0x358);
      fVar11 = *(float *)(this + 0x54) * 0.0;
      *(float *)(this + iVar8 + 0x3430) = *(float *)(this + 0x54) * -0.2;
      *(float *)(this + iVar8 + 0x3428) = fVar11;
      *(float *)(this + iVar8 + 0x342c) = fVar11;
      cLinkedList<cRBod>::AddBefore
                (this_00,(cRBod *)(this + iVar8 + 0x33a8),(cRBod *)(this + 0xfac4));
      iVar2 = cRSpriteManager::New((int)&gRSpriteManager,*(int *)(param_2 + 0x370),0x6a,-1);
      *(int *)(this + iVar8 + 0x3448) = iVar2;
      *(uint *)(iVar2 + 4) = *(uint *)(iVar2 + 4) | 0x800;
      tColour::White();
      iVar2 = Game;
      iVar7 = *(int *)(this + iVar8 + 0x3448);
      *(undefined4 *)(iVar7 + 100) = 0x40000000;
      *(undefined4 *)(iVar7 + 0x60) = 0x40000000;
      *(undefined4 *)(iVar7 + 0x78) = 0;
      *(undefined4 *)(iVar7 + 0x68) = 0;
      *(undefined4 *)(iVar7 + 0x6c) = 0;
      uVar3 = *(undefined4 *)(this + iVar8 + 0x3408);
      uVar5 = *(undefined4 *)(this + iVar8 + 0x340c);
      *(undefined4 *)(iVar7 + 0x48) = *(undefined4 *)(this + iVar8 + 0x3404);
      *(undefined4 *)(iVar7 + 0x4c) = uVar3;
      *(undefined4 *)(iVar7 + 0x50) = uVar5;
      *(undefined4 *)(this + iVar8 + 0x346c) = 0;
      fVar11 = *(float *)(iVar2 + 0x718f4);
      *(undefined4 *)(this + iVar8 + 0x3478) = 0;
      *(undefined4 *)(this + iVar8 + 0x347c) = 0x3d088889;
      this[iVar8 + 0x3475] = (cRSubGame)0x0;
      *(uint *)(this + iVar8 + 0x33ac) = *(uint *)(this + iVar8 + 0x33ac) & 0xffffefff;
      this[iVar8 + 0x3474] = (cRSubGame)0x0;
      *(undefined4 *)(this + iVar8 + 0x3464) = 7;
      *(cRSubLoc **)(this + iVar8 + 0x344c) = param_1;
      this[iVar8 + 0x3450] = (cRSubGame)0x0;
      *(float *)(this + iVar8 + 0x3470) = fVar11 * 0.16666667;
      this[iVar8 + 0x3468] = (cRSubGame)0x0;
      fVar11 = *(float *)(param_1 + 0x18);
      fVar12 = *(float *)(this + 0x332da0);
      uVar10 = in_fpscr & 0xfffffff | (uint)(fVar11 < fVar12) << 0x1f |
               (uint)(fVar11 == fVar12) << 0x1e;
      uVar9 = uVar10 | (uint)(NAN(fVar11) || NAN(fVar12)) << 0x1c;
      bVar1 = (byte)(uVar10 >> 0x18);
      if (!(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(uVar9 >> 0x1c) & 1)) {
        fVar11 = *(float *)(this + 0x332da4);
        *(undefined4 *)(this + iVar8 + 0x3460) = 1;
        *(float *)(this + 0x332da0) = fVar12 + fVar11;
      }
      fVar12 = 0.0;
      *(undefined4 *)(this + iVar4 * 0xe0 + 0x3480) = 0;
      uVar3 = gRMathRand2();
      fVar11 = (float)VectorSignedToFloat(uVar3,(byte)(uVar9 >> 0x16) & 3);
      uVar10 = uVar9 & 0xfffffff | (uint)(fVar11 * 3.0517578e-05 + 1.0 == 0.0) << 0x1e;
      if (!SUB41(uVar10 >> 0x1e,0)) {
        uVar3 = gRMathRand2();
        fVar11 = (float)VectorSignedToFloat(uVar3,(byte)(uVar10 >> 0x16) & 3);
        fVar12 = 1.0 / ((fVar11 * 3.0517578e-05 + 1.0) * 60.0);
      }
      *(float *)(this + iVar4 * 0xe0 + 0x3484) = fVar12;
      return;
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 != 0x10);
  return;
}
