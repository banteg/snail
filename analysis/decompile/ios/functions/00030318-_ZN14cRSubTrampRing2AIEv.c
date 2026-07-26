/*
 * mangled: _ZN14cRSubTrampRing2AIEv
 * demangled: cRSubTrampRing::AI()
 * address: 00030318
 * size: 280
 */

/* cRSubTrampRing::AI() */

void __thiscall cRSubTrampRing::AI(cRSubTrampRing *this)

{
  int iVar1;
  int iVar2;
  float fVar3;
  float fVar4;

  if (*(int *)(this + 0x74) == 1) {
    fVar3 = *(float *)(this + 0x78);
    fVar4 = 1.0;
    *(float *)(this + 0x78) = fVar3 + *(float *)(this + 0x7c);
    if (fVar3 + *(float *)(this + 0x7c) <= 1.0) {
      tMatrix::RotIdentity((tMatrix *)(this + 0x2c));
      tMatrix::Scale((tMatrix *)(this + 0x2c),*(float *)(this + 0x78) * 12.0 + 2.5);
      this[0x2b] = SUB41((int)((fVar4 - *(float *)(this + 0x78)) * 250.0),0);
    }
    else {
      *(undefined4 *)(this + 0x78) = 0;
      *(undefined4 *)(this + 0x74) = 0;
      iVar1 = *(int *)PTR__Game_001b60b8;
      if ((*(uint *)(this + 4) & 0x200) == 0) {
        RShellError("List remove");
      }
      else if ((*(uint *)(this + 4) & 0x40) == 0) {
        iVar2 = *(int *)(this + 0xc);
        if (iVar2 != 0) {
          *(undefined4 *)(iVar2 + 8) = *(undefined4 *)(this + 8);
        }
        if (*(int *)(this + 8) == 0) {
          *(int *)(iVar1 + 0x35c) = iVar2;
        }
        else {
          *(int *)(*(int *)(this + 8) + 0xc) = iVar2;
        }
        *(undefined4 *)(this + 0xc) = *(undefined4 *)(iVar1 + 0x360);
        *(cRSubTrampRing **)(iVar1 + 0x360) = this;
        *(uint *)(this + 4) = *(uint *)(this + 4) & 0xfffffdff;
      }
      else {
        RShellError("List remove NEXTBOD");
      }
    }
  }
  return;
}
