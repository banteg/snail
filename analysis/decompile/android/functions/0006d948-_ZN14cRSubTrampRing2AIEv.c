/*
 * mangled: _ZN14cRSubTrampRing2AIEv
 * demangled: cRSubTrampRing::AI()
 * address: 0006d948
 * size: 192
 */

/* cRSubTrampRing::AI() */

void __thiscall cRSubTrampRing::AI(cRSubTrampRing *this)

{
  float fVar1;
  int iVar2;
  int iVar3;
  float fVar4;

  fVar1 = DAT_0006da08;
  iVar3 = DAT_0006da1c + 0x6d964;
  if (*(int *)(this + 0x74) == 1) {
    fVar4 = *(float *)(this + 0x78);
    *(float *)(this + 0x78) = fVar4 + *(float *)(this + 0x7c);
    if (fVar1 < fVar4 + *(float *)(this + 0x7c)) {
      *(undefined4 *)(this + 0x74) = 0;
      iVar2 = DAT_0006da20;
      *(undefined4 *)(this + 0x78) = DAT_0006da18;
      cLinkedList<cRBod>::Remove
                ((cLinkedList<cRBod> *)(**(int **)(iVar3 + iVar2) + 0x358),(cRBod *)this);
      return;
    }
    fVar4 = (float)tMatrix::RotIdentity((tMatrix *)(this + 0x2c));
    tMatrix::Scale((tMatrix *)(this + 0x2c),fVar4);
    this[0x2b] = SUB41((int)((fVar1 - *(float *)(this + 0x78)) * DAT_0006da14),0);
  }
  return;
}
