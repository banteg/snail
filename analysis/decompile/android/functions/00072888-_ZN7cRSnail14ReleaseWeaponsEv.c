/*
 * mangled: _ZN7cRSnail14ReleaseWeaponsEv
 * demangled: cRSnail::ReleaseWeapons()
 * address: 00072888
 * size: 452
 */

/* cRSnail::ReleaseWeapons() */

void __thiscall cRSnail::ReleaseWeapons(cRSnail *this)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 uVar5;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float fVar6;
  float fVar7;
  float fVar8;

  if (this[0x176c] == (cRSnail)0x0) {
    uVar5 = gRMathRand2();
    fVar4 = DAT_00072a58;
    fVar3 = DAT_00072a54;
    fVar2 = DAT_00072a50;
    fVar1 = DAT_00072a4c;
    fVar7 = (float)VectorSignedToFloat(uVar5,(byte)(in_fpscr >> 0x16) & 3);
    fVar8 = (fVar7 - DAT_00072a4c) * DAT_00072a50;
    fVar7 = (float)RAND(extraout_s0,(char *)0x3f800000);
    fVar6 = *(float *)(*(int *)(this + 0xf4) + 0x410);
    *(float *)(this + 0x140c) = fVar8 * fVar3;
    *(float *)(this + 0x1414) = fVar6 * fVar3;
    *(float *)(this + 0x1410) = (fVar7 + fVar4) * fVar3;
    uVar5 = gRMathRand2();
    fVar8 = (float)VectorSignedToFloat(uVar5,(byte)(in_fpscr >> 0x16) & 3);
    fVar7 = (float)RAND(extraout_s0_00,(char *)0x3f800000);
    fVar6 = *(float *)(*(int *)(this + 0xf4) + 0x410);
    *(float *)(this + 0x950) = (fVar8 - fVar1) * fVar2 * fVar3;
    *(float *)(this + 0x958) = fVar6 * fVar3;
    *(float *)(this + 0x954) = (fVar7 + fVar4) * fVar3;
    uVar5 = gRMathRand2();
    fVar8 = (float)VectorSignedToFloat(uVar5,(byte)(in_fpscr >> 0x16) & 3);
    fVar7 = (float)RAND(extraout_s0_01,(char *)0x3f800000);
    fVar6 = *(float *)(*(int *)(this + 0xf4) + 0x410);
    *(float *)(this + 0x1078) = (fVar8 - fVar1) * fVar2 * fVar3;
    *(float *)(this + 0x1080) = fVar6 * fVar3;
    *(float *)(this + 0x107c) = (fVar7 + fVar4) * fVar3;
    uVar5 = gRMathRand2();
    fVar6 = (float)VectorSignedToFloat(uVar5,(byte)(in_fpscr >> 0x16) & 3);
    fVar7 = (float)RAND(extraout_s0_02,(char *)0x3f800000);
    fVar8 = *(float *)(*(int *)(this + 0xf4) + 0x410);
    *(float *)(this + 0xce4) = (fVar6 - fVar1) * fVar2 * fVar3;
    *(float *)(this + 0xcec) = fVar8 * fVar3;
    *(float *)(this + 0xce8) = (fVar7 + fVar4) * fVar3;
    cRSubHover::End((cRSubHover *)(*(int *)(this + 0xf4) + 0x25cc));
  }
  this[0x176c] = (cRSnail)0x1;
  return;
}
