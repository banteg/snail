/*
 * mangled: _ZN9cRSubGame11CalcRealPosER7tVectorRf
 * demangled: cRSubGame::CalcRealPos(tVector&, float&)
 * address: 0001ea44
 * size: 432
 */

/* cRSubGame::CalcRealPos(tVector&, float&) */

void __thiscall cRSubGame::CalcRealPos(cRSubGame *this,tVector *param_1,float *param_2)

{
  cRPath *this_00;
  int iVar1;
  int iVar2;
  float *pfVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  tMatrix atStack_4c [48];
  undefined4 local_1c;
  undefined4 local_18;

  fVar8 = *(float *)(param_1 + 8);
  *param_2 = 0.0;
  if ((*(uint *)(this + (int)fVar8 * 0xdc + 0x1e41d8) & 0x40) != 0) {
    iVar1 = *(int *)(this + (int)fVar8 * 0xdc + 0x1e4270);
    this_00 = *(cRPath **)(iVar1 + 0x2c);
    iVar2 = ((int)(iVar1 - ((*(byte *)(iVar1 + 0x32) & 7) * 0x44 + 0x85fd0 +
                           *(int *)PTR__Game_001b60b8)) >> 2) * -0xf0f0f0f;
    if (iVar2 < 0) {
      iVar2 = iVar2 + 7;
    }
    pfVar3 = (float *)(((int)*(float *)(param_1 + 8) - (iVar2 >> 3)) * 0xa8 +
                      *(int *)(this_00 + 0x4c));
    if (*(int *)(this_00 + 0x2c) == 0x39) {
      cRPath::HalfPipePos(this_00,pfVar3[0x28],*(float *)param_1,*(float *)(param_1 + 4),atStack_4c,
                          param_2);
      *(undefined4 *)param_1 = local_1c;
      *(undefined4 *)(param_1 + 4) = local_18;
    }
    else if (*(int *)(this_00 + 0x2c) == 0x3a) {
      cRPath::HalfPolePos(this_00,pfVar3[0x28],*(float *)param_1,*(float *)(param_1 + 4),atStack_4c,
                          param_2);
      *(undefined4 *)param_1 = local_1c;
      *(undefined4 *)(param_1 + 4) = local_18;
    }
    else {
      fVar8 = *(float *)(param_1 + 4);
      fVar4 = *(float *)param_1 - pfVar3[0x24];
      fVar5 = pfVar3[0xd];
      fVar9 = *(float *)(iVar1 + 0x14);
      fVar10 = pfVar3[1];
      fVar6 = pfVar3[0xe];
      *(float *)param_1 =
           pfVar3[0xc] + *(float *)(iVar1 + 0x10) + fVar4 * *pfVar3 + fVar8 * pfVar3[4];
      fVar11 = *(float *)(iVar1 + 0x18);
      fVar7 = pfVar3[2];
      *(float *)(param_1 + 4) = fVar5 + fVar9 + fVar4 * fVar10 + fVar8 * pfVar3[5];
      *(float *)(param_1 + 8) = fVar6 + fVar11 + fVar4 * fVar7 + fVar8 * pfVar3[6];
    }
  }
  return;
}
