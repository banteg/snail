/*
 * mangled: _ZN7cRSnail14ReleaseWeaponsEv
 * demangled: cRSnail::ReleaseWeapons()
 * address: 00019110
 * size: 532
 */

/* cRSnail::ReleaseWeapons() */

void __thiscall cRSnail::ReleaseWeapons(cRSnail *this)

{
  undefined4 uVar1;
  float fVar2;
  int iVar3;
  uint in_fpscr;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;

  if (this[0x176c] == (cRSnail)0x0) {
    uVar1 = gRMathRand2();
    fVar4 = 0.3;
    fVar7 = 0.5;
    fVar6 = 16384.0;
    fVar5 = 6.1035156e-05;
    fVar2 = (float)RAND(1.0,(char *)0x0);
    *(float *)(this + 0x1414) = *(float *)(*(int *)(this + 0xf4) + 0x408) * fVar4;
    *(float *)(this + 0x1410) = (fVar2 + fVar7) * fVar4;
    fVar2 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(this + 0x140c) = (fVar2 - fVar6) * fVar5 * fVar4;
    uVar1 = gRMathRand2();
    fVar2 = (float)RAND(1.0,(char *)0x0);
    *(float *)(this + 0x958) = *(float *)(*(int *)(this + 0xf4) + 0x408) * fVar4;
    *(float *)(this + 0x954) = (fVar2 + fVar7) * fVar4;
    fVar2 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(this + 0x950) = (fVar2 - fVar6) * fVar5 * fVar4;
    uVar1 = gRMathRand2();
    fVar2 = (float)RAND(1.0,(char *)0x0);
    *(float *)(this + 0x1080) = *(float *)(*(int *)(this + 0xf4) + 0x408) * fVar4;
    *(float *)(this + 0x107c) = (fVar2 + fVar7) * fVar4;
    fVar2 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(this + 0x1078) = (fVar2 - fVar6) * fVar5 * fVar4;
    uVar1 = gRMathRand2();
    fVar2 = (float)RAND(1.0,(char *)0x0);
    iVar3 = *(int *)(this + 0xf4);
    *(float *)(this + 0xcec) = *(float *)(iVar3 + 0x408) * fVar4;
    *(float *)(this + 0xce8) = (fVar2 + fVar7) * fVar4;
    fVar2 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
    *(float *)(this + 0xce4) = (fVar2 - fVar6) * fVar5 * fVar4;
    if ((*(int *)(&DAT_000025d0 + iVar3) == 1) && (*(float *)(&DAT_000025c4 + iVar3) < 0.94)) {
      *(float *)(&DAT_000025c4 + iVar3) = 0.94;
    }
  }
  this[0x176c] = (cRSnail)0x1;
  return;
}
