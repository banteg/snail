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
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  cRSubGame *pcVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  uint in_fpscr;
  uint uVar10;
  uint uVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;

  fVar13 = DAT_00079848;
  pcVar6 = this + 0x341c;
  iVar4 = 0;
  iVar8 = DAT_0007986c + 0x7956c;
  do {
    iVar7 = *(int *)pcVar6;
    pcVar6 = pcVar6 + 0xe0;
    if (iVar7 == 0) {
      iVar7 = iVar4 * 0xe0;
      *(undefined4 *)(this + iVar7 + 0x341c) = 1;
      *(cRSubGoldy **)(this + iVar7 + 0x345c) = param_2;
      tMatrix::Identity((tMatrix *)(this + iVar7 + 0x33d4));
      fVar14 = *(float *)(param_1 + 0x18);
      fVar12 = DAT_0007984c + *(float *)(param_1 + 0x14);
      *(float *)(this + iVar7 + 0x3404) = fVar13 + *(float *)(param_1 + 0x10);
      *(float *)(this + iVar7 + 0x3408) = fVar12;
      *(float *)(this + iVar7 + 0x340c) = fVar14 + fVar13;
      CalcRealPos(this,(tVector *)(this + iVar7 + 0x3404),(float *)(this + iVar7 + 0x3434));
      piVar9 = *(int **)(iVar8 + DAT_00079870);
      iVar2 = *piVar9;
      fVar12 = *(float *)(this + 0x54) * fVar13;
      *(float *)(this + iVar7 + 0x3430) = *(float *)(this + 0x54) * DAT_00079850;
      *(float *)(this + iVar7 + 0x3428) = fVar12;
      *(float *)(this + iVar7 + 0x342c) = fVar12;
      cLinkedList<cRBod>::AddBefore
                ((cLinkedList<cRBod> *)(iVar2 + 0x358),(cRBod *)(this + iVar7 + 0x33a8),
                 (cRBod *)(this + 0xfac4));
      iVar8 = cRSpriteManager::New(*(int *)(iVar8 + DAT_00079874),*(int *)(param_2 + 0x370),0x6a,-1)
      ;
      *(int *)(this + iVar7 + 0x3448) = iVar8;
      *(uint *)(iVar8 + 4) = *(uint *)(iVar8 + 4) | 0x800;
      tColour::White();
      uVar3 = DAT_00079854;
      iVar2 = *piVar9;
      iVar8 = *(int *)(this + iVar7 + 0x3448);
      *(undefined4 *)(iVar8 + 100) = DAT_00079854;
      *(undefined4 *)(iVar8 + 0x60) = uVar3;
      *(float *)(iVar8 + 0x78) = fVar13;
      *(float *)(iVar8 + 0x68) = fVar13;
      *(float *)(iVar8 + 0x6c) = fVar13;
      fVar12 = DAT_00079858;
      uVar3 = *(undefined4 *)(this + iVar7 + 0x3408);
      uVar5 = *(undefined4 *)(this + iVar7 + 0x340c);
      *(undefined4 *)(iVar8 + 0x48) = *(undefined4 *)(this + iVar7 + 0x3404);
      *(undefined4 *)(iVar8 + 0x4c) = uVar3;
      *(undefined4 *)(iVar8 + 0x50) = uVar5;
      *(float *)(this + iVar7 + 0x346c) = fVar13;
      fVar14 = *(float *)(iVar2 + 0x718f4);
      *(float *)(this + iVar7 + 0x3478) = fVar13;
      *(undefined4 *)(this + iVar7 + 0x347c) = DAT_0007985c;
      this[iVar7 + 0x3475] = (cRSubGame)0x0;
      *(uint *)(this + iVar7 + 0x33ac) = *(uint *)(this + iVar7 + 0x33ac) & 0xffffefff;
      this[iVar7 + 0x3474] = (cRSubGame)0x0;
      *(undefined4 *)(this + iVar7 + 0x3464) = 7;
      *(cRSubLoc **)(this + iVar7 + 0x344c) = param_1;
      this[iVar7 + 0x3450] = (cRSubGame)0x0;
      *(float *)(this + iVar7 + 0x3470) = fVar14 * fVar12;
      this[iVar7 + 0x3468] = (cRSubGame)0x0;
      fVar13 = *(float *)(param_1 + 0x18);
      fVar12 = *(float *)(this + 0x332da0);
      uVar11 = in_fpscr & 0xfffffff | (uint)(fVar13 < fVar12) << 0x1f |
               (uint)(fVar13 == fVar12) << 0x1e;
      uVar10 = uVar11 | (uint)(NAN(fVar13) || NAN(fVar12)) << 0x1c;
      bVar1 = (byte)(uVar11 >> 0x18);
      if (!(bool)(bVar1 >> 6 & 1) && bVar1 >> 7 == ((byte)(uVar10 >> 0x1c) & 1)) {
        fVar13 = *(float *)(this + 0x332da4);
        *(undefined4 *)(this + iVar7 + 0x3460) = 1;
        *(float *)(this + 0x332da0) = fVar12 + fVar13;
      }
      fVar14 = DAT_00079864;
      fVar12 = DAT_00079860;
      fVar13 = DAT_00079848;
      *(float *)(this + iVar4 * 0xe0 + 0x3480) = DAT_00079848;
      uVar3 = gRMathRand2();
      fVar15 = (float)VectorSignedToFloat(uVar3,(byte)(uVar10 >> 0x16) & 3);
      uVar11 = uVar10 & 0xfffffff | (uint)(fVar12 + fVar15 * fVar14 == fVar13) << 0x1e;
      if (!SUB41(uVar11 >> 0x1e,0)) {
        uVar3 = gRMathRand2();
        fVar13 = (float)VectorSignedToFloat(uVar3,(byte)(uVar11 >> 0x16) & 3);
        fVar13 = fVar12 / ((fVar12 + fVar13 * fVar14) * DAT_00079868);
      }
      *(float *)(this + iVar4 * 0xe0 + 0x3484) = fVar13;
      return;
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 != 0x10);
  return;
}
