/*
 * mangled: _ZN7cRSnail14ReleaseWeaponsEv
 * demangled: cRSnail::ReleaseWeapons()
 * address: 00072888
 * size: 452
 */

/* cRSnail::ReleaseWeapons() */

void __thiscall cRSnail::ReleaseWeapons(cRSnail *this)

{
  undefined4 uVar1;
  float fVar2;
  uint in_fpscr;
  float extraout_s0;
  float extraout_s0_00;
  float extraout_s0_01;
  float extraout_s0_02;
  float fVar3;
  float fVar4;

  if (this[0x176c] == (cRSnail)0x0) {
    uVar1 = gRMathRand2();
    fVar4 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
    fVar2 = (float)RAND(extraout_s0,(char *)0x3f800000);
    fVar3 = *(float *)(*(int *)(this + 0xf4) + 0x410);
    *(float *)(this + 0x140c) = (fVar4 - 16384.0) * 6.1035156e-05 * 0.3;
    *(float *)(this + 0x1414) = fVar3 * 0.3;
    *(float *)(this + 0x1410) = (fVar2 + 0.5) * 0.3;
    uVar1 = gRMathRand2();
    fVar4 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
    fVar2 = (float)RAND(extraout_s0_00,(char *)0x3f800000);
    fVar3 = *(float *)(*(int *)(this + 0xf4) + 0x410);
    *(float *)(this + 0x950) = (fVar4 - 16384.0) * 6.1035156e-05 * 0.3;
    *(float *)(this + 0x958) = fVar3 * 0.3;
    *(float *)(this + 0x954) = (fVar2 + 0.5) * 0.3;
    uVar1 = gRMathRand2();
    fVar4 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
    fVar2 = (float)RAND(extraout_s0_01,(char *)0x3f800000);
    fVar3 = *(float *)(*(int *)(this + 0xf4) + 0x410);
    *(float *)(this + 0x1078) = (fVar4 - 16384.0) * 6.1035156e-05 * 0.3;
    *(float *)(this + 0x1080) = fVar3 * 0.3;
    *(float *)(this + 0x107c) = (fVar2 + 0.5) * 0.3;
    uVar1 = gRMathRand2();
    fVar3 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
    fVar2 = (float)RAND(extraout_s0_02,(char *)0x3f800000);
    fVar4 = *(float *)(*(int *)(this + 0xf4) + 0x410);
    *(float *)(this + 0xce4) = (fVar3 - 16384.0) * 6.1035156e-05 * 0.3;
    *(float *)(this + 0xcec) = fVar4 * 0.3;
    *(float *)(this + 0xce8) = (fVar2 + 0.5) * 0.3;
    cRSubHover::End((cRSubHover *)(*(int *)(this + 0xf4) + 0x25cc));
  }
  this[0x176c] = (cRSnail)0x1;
  return;
}
