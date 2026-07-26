/*
 * mangled: _ZN10cRVoiceSet7ShuffleEv
 * demangled: cRVoiceSet::Shuffle()
 * address: 00087170
 * size: 176
 */

/* cRVoiceSet::Shuffle() */

void __thiscall cRVoiceSet::Shuffle(cRVoiceSet *this)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  uint in_fpscr;
  float fVar6;
  float fVar7;
  int iVar8;
  int iVar9;

  fVar1 = DAT_00087220;
  iVar4 = 0;
  pcVar5 = (char *)(DAT_00087224 + 0x8718c + DAT_00087228);
  do {
    uVar2 = gRMathRand2();
    fVar7 = (float)VectorSignedToFloat(*(undefined4 *)this,(byte)(in_fpscr >> 0x16) & 3);
    iVar4 = iVar4 + 1;
    fVar6 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
    iVar8 = (int)(fVar6 * fVar1 * fVar7);
    uVar2 = gRMathRand2();
    iVar3 = *(int *)this;
    fVar7 = (float)VectorSignedToFloat(iVar3,(byte)(in_fpscr >> 0x16) & 3);
    fVar6 = (float)VectorSignedToFloat(uVar2,(byte)(in_fpscr >> 0x16) & 3);
    iVar9 = (int)(fVar6 * fVar1 * fVar7);
    if ((iVar3 <= iVar8) || (iVar3 <= iVar9)) {
      wprintf(pcVar5);
    }
    iVar3 = *(int *)(this + 8);
    uVar2 = *(undefined4 *)(iVar3 + iVar8 * 4);
    *(undefined4 *)(iVar3 + iVar8 * 4) = *(undefined4 *)(iVar3 + iVar9 * 4);
    *(undefined4 *)(iVar3 + iVar9 * 4) = uVar2;
  } while (iVar4 != 100);
  return;
}
