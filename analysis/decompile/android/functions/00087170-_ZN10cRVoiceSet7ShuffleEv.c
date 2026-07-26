/*
 * mangled: _ZN10cRVoiceSet7ShuffleEv
 * demangled: cRVoiceSet::Shuffle()
 * address: 00087170
 * size: 176
 */

/* cRVoiceSet::Shuffle() */

void __thiscall cRVoiceSet::Shuffle(cRVoiceSet *this)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  uint in_fpscr;
  float fVar4;
  float fVar5;
  int iVar6;
  int iVar7;

  iVar3 = 0;
  do {
    uVar1 = gRMathRand2();
    fVar5 = (float)VectorSignedToFloat(*(undefined4 *)this,(byte)(in_fpscr >> 0x16) & 3);
    iVar3 = iVar3 + 1;
    fVar4 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
    iVar6 = (int)(fVar4 * 3.0517578e-05 * fVar5);
    uVar1 = gRMathRand2();
    iVar2 = *(int *)this;
    fVar5 = (float)VectorSignedToFloat(iVar2,(byte)(in_fpscr >> 0x16) & 3);
    fVar4 = (float)VectorSignedToFloat(uVar1,(byte)(in_fpscr >> 0x16) & 3);
    iVar7 = (int)(fVar4 * 3.0517578e-05 * fVar5);
    if ((iVar2 <= iVar6) || (iVar2 <= iVar7)) {
      wprintf("RANDOM ERORR\n");
    }
    iVar2 = *(int *)(this + 8);
    uVar1 = *(undefined4 *)(iVar2 + iVar6 * 4);
    *(undefined4 *)(iVar2 + iVar6 * 4) = *(undefined4 *)(iVar2 + iVar7 * 4);
    *(undefined4 *)(iVar2 + iVar7 * 4) = uVar1;
  } while (iVar3 != 100);
  return;
}
