/*
 * mangled: _ZN6cRSalt2AIEv
 * demangled: cRSalt::AI()
 * address: 00030850
 * size: 296
 */

/* cRSalt::AI() */

void __thiscall cRSalt::AI(cRSalt *this)

{
  int iVar1;
  int iVar2;
  float fVar3;

  if (*(char *)(*(int *)(this + 0x7c) + 0x12) != '\0') {
    return;
  }
  if (*(int *)(this + 0x74) != 1) {
    if (*(int *)(this + 0x74) != 2) {
      return;
    }
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
      *(cRSalt **)(iVar1 + 0x360) = this;
      *(uint *)(this + 4) = *(uint *)(this + 4) & 0xfffffdff;
    }
    else {
      RShellError("List remove NEXTBOD");
    }
    *(undefined4 *)(this + 0x74) = 0;
    return;
  }
  fVar3 = (*(float *)(this + 100) - *(float *)(*(int *)(this + 0x7c) + 0xf4ac)) / -48.0 + 1.0;
  if (fVar3 < 0.0) {
    fVar3 = 0.0;
  }
  else if (1.0 < fVar3) {
    fVar3 = 1.0;
  }
  *(float *)(this + 0x80) = fVar3;
  tColourSmall::Alpha((tColourSmall *)(this + 0x28),0.9);
  if (*(float *)(this + 100) < *(float *)(*(int *)(this + 0x7c) + 0x11c3c)) {
    *(undefined4 *)(this + 0x74) = 2;
  }
  return;
}
