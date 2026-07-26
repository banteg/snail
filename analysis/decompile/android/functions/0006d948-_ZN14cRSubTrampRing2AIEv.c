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

  if (*(int *)(this + 0x74) == 1) {
    fVar1 = *(float *)(this + 0x78);
    *(float *)(this + 0x78) = fVar1 + *(float *)(this + 0x7c);
    if (1.0 < fVar1 + *(float *)(this + 0x7c)) {
      *(undefined4 *)(this + 0x74) = 0;
      *(undefined4 *)(this + 0x78) = 0;
      cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)this);
      return;
    }
    fVar1 = (float)tMatrix::RotIdentity((tMatrix *)(this + 0x2c));
    tMatrix::Scale((tMatrix *)(this + 0x2c),fVar1);
    this[0x2b] = SUB41((int)((1.0 - *(float *)(this + 0x78)) * 250.0),0);
  }
  return;
}
