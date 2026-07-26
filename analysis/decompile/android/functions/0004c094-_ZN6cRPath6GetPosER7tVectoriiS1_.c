/*
 * mangled: _ZN6cRPath6GetPosER7tVectoriiS1_
 * demangled: cRPath::GetPos(tVector&, int, int, tVector&)
 * address: 0004c094
 * size: 168
 */

/* cRPath::GetPos(tVector&, int, int, tVector&) */

void __thiscall
cRPath::GetPos(cRPath *this,tVector *param_1,int param_2,int param_3,tVector *param_4)

{
  float *pfVar1;
  uint in_fpscr;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;

  fVar7 = *(float *)param_4;
  fVar8 = *(float *)(param_4 + 4);
  fVar6 = (float)VectorSignedToFloat(param_3,(byte)(in_fpscr >> 0x16) & 3);
  pfVar1 = (float *)(*(int *)(this + 0x4c) + param_2 * 0xa8);
  fVar2 = pfVar1[2];
  fVar9 = pfVar1[0xe];
  fVar3 = pfVar1[1];
  fVar10 = pfVar1[0xd];
  fVar4 = pfVar1[6];
  fVar5 = pfVar1[5];
  *(float *)param_1 = pfVar1[0xc] + fVar7 * *pfVar1 + fVar8 * pfVar1[4];
  *(float *)(param_1 + 4) = fVar10 + fVar7 * fVar3 + fVar8 * fVar5;
  *(float *)(param_1 + 8) = fVar9 + fVar7 * fVar2 + fVar8 * fVar4 + fVar6;
  return;
}
