/*
 * mangled: _ZN6cRPath6GetPosER7tVectoriiS1_
 * demangled: cRPath::GetPos(tVector&, int, int, tVector&)
 * address: 0004f848
 * size: 172
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

  fVar5 = *(float *)param_4;
  fVar3 = *(float *)(param_4 + 4);
  pfVar1 = (float *)(param_2 * 0xa8 + *(int *)(this + 0x4c));
  fVar4 = pfVar1[0xd];
  fVar2 = pfVar1[2];
  fVar8 = pfVar1[1];
  fVar9 = pfVar1[5];
  fVar10 = pfVar1[0xe];
  fVar6 = pfVar1[6];
  fVar7 = (float)VectorSignedToFloat(param_3,(byte)(in_fpscr >> 0x16) & 3);
  *(float *)param_1 = pfVar1[0xc] + fVar5 * *pfVar1 + fVar3 * pfVar1[4];
  *(float *)(param_1 + 4) = fVar4 + fVar5 * fVar8 + fVar3 * fVar9;
  *(float *)(param_1 + 8) = fVar10 + fVar5 * fVar2 + fVar3 * fVar6 + fVar7;
  return;
}
