/*
 * mangled: _ZN9cRSubGame11CalcRealPosER7tVectorRf
 * demangled: cRSubGame::CalcRealPos(tVector&, float&)
 * address: 00072704
 * size: 384
 */

/* cRSubGame::CalcRealPos(tVector&, float&) */

void __thiscall cRSubGame::CalcRealPos(cRSubGame *this,tVector *param_1,float *param_2)

{
  int iVar1;
  int iVar2;
  tMatrix *ptVar3;
  cRSubLoc *this_00;
  int iVar4;
  float extraout_s0;
  float extraout_s1;
  float extraout_s2;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined4 local_30;
  undefined4 local_2c;

  fVar12 = *(float *)(param_1 + 8);
  *param_2 = DAT_00072884;
  if ((*(uint *)(this + (int)fVar12 * 0xdc + 0x20dedc) & 0x40) != 0) {
    fVar14 = *(float *)(param_1 + 8);
    this_00 = *(cRSubLoc **)(this + (int)fVar12 * 0xdc + 0x20df74);
    iVar4 = *(int *)(*(int *)(this_00 + 0x2c) + 0x4c);
    iVar1 = cRSubLoc::Yi(this_00);
    ptVar3 = *(tMatrix **)(this_00 + 0x2c);
    iVar1 = ((int)fVar14 - iVar1) * 0xa8;
    iVar2 = iVar4 + iVar1;
    if (*(int *)(ptVar3 + 0x2c) == 0x39) {
      cRPath::HalfPipePos(extraout_s0,extraout_s1,extraout_s2,ptVar3,*(float **)(iVar2 + 0xa0));
      *(undefined4 *)param_1 = local_30;
      *(undefined4 *)(param_1 + 4) = local_2c;
    }
    else if (*(int *)(ptVar3 + 0x2c) == 0x3a) {
      cRPath::HalfPolePos(extraout_s0,extraout_s1,extraout_s2,ptVar3,*(float **)(iVar2 + 0xa0));
      *(undefined4 *)param_1 = local_30;
      *(undefined4 *)(param_1 + 4) = local_2c;
    }
    else {
      fVar11 = *(float *)(this_00 + 0x18);
      fVar12 = *(float *)(iVar2 + 0x34);
      fVar14 = *(float *)(iVar2 + 0x38);
      fVar13 = *(float *)(this_00 + 0x14);
      fVar6 = *(float *)(iVar2 + 4);
      fVar5 = *(float *)(iVar2 + 8);
      fVar10 = *(float *)(param_1 + 4);
      fVar7 = *(float *)(iVar2 + 0x18);
      fVar8 = *(float *)(iVar2 + 0x14);
      fVar9 = *(float *)param_1 - *(float *)(iVar2 + 0x90);
      *(float *)param_1 =
           *(float *)(iVar2 + 0x30) + *(float *)(this_00 + 0x10) + fVar9 * *(float *)(iVar1 + iVar4)
           + fVar10 * *(float *)(iVar2 + 0x10);
      *(float *)(param_1 + 8) = fVar14 + fVar11 + fVar9 * fVar5 + fVar10 * fVar7;
      *(float *)(param_1 + 4) = fVar12 + fVar13 + fVar9 * fVar6 + fVar10 * fVar8;
    }
  }
  return;
}
