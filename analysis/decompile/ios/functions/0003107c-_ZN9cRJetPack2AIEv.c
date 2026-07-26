/*
 * mangled: _ZN9cRJetPack2AIEv
 * demangled: cRJetPack::AI()
 * address: 0003107c
 * size: 400
 */

/* cRJetPack::AI() */

void __thiscall cRJetPack::AI(cRJetPack *this)

{
  int iVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  float fVar5;

  if (*(char *)(*(int *)(this + 0x38) + 0x12) != '\0') {
    return;
  }
  iVar1 = *(int *)(this + 0x2c);
  if (iVar1 == 1) {
    if (*(float *)(this + 0x18) < *(float *)(&DAT_000027f4 + *(int *)(this + 0x30))) {
      *(undefined4 *)(this + 0x2c) = 0;
      goto LAB_00031188;
    }
  }
  else {
    if (iVar1 == 2) {
      *(undefined4 *)(this + 0x2c) = 0;
LAB_00031188:
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
        *(cRJetPack **)(iVar1 + 0x360) = this;
        *(uint *)(this + 4) = *(uint *)(this + 4) & 0xfffffdff;
      }
      else {
        RShellError("List remove NEXTBOD");
      }
      cRSprite::Kill(*(cRSprite **)(this + 0x58));
      return;
    }
    if (iVar1 == 0) {
      return;
    }
  }
  iVar1 = *(int *)(this + 0x58);
  fVar5 = *(float *)(this + 0x14);
  fVar3 = *(float *)(this + 0x60) + *(float *)(this + 100);
  *(float *)(this + 0x60) = fVar3;
  fVar4 = fVar3;
  if (1.0 < fVar3) {
    fVar4 = fVar3 - 1.0;
  }
  if (1.0 < fVar3) {
    *(float *)(this + 0x60) = fVar4;
  }
  fVar4 = (float)Sin((fVar4 + fVar4) * 3.1415927);
  *(float *)(iVar1 + 0x4c) = fVar5 + fVar4 * 0.3;
  *(float *)(*(int *)(this + 0x58) + 0x7c) =
       *(float *)(*(int *)(this + 0x30) + 0x360) + *(float *)(*(int *)(this + 0x30) + 0x34c);
  iVar1 = *(int *)(this + 0x30);
  if (*(char *)(iVar1 + 0x374) != '\0') {
    *(float *)(*(int *)(this + 0x58) + 0x7c) =
         *(float *)(*(int *)(this + 0x58) + 0x7c) +
         *(float *)(iVar1 + 0x390) + *(float *)(iVar1 + 0x38c);
  }
  return;
}
