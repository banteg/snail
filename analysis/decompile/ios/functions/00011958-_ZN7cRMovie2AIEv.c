/*
 * mangled: _ZN7cRMovie2AIEv
 * demangled: cRMovie::AI()
 * address: 00011958
 * size: 276
 */

/* cRMovie::AI() */

void __thiscall cRMovie::AI(cRMovie *this)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  float fVar4;

  iVar1 = *(int *)(this + 0x114);
  *(undefined4 *)(this + 0x120) = *(undefined4 *)(iVar1 * 0x30 + *(int *)(this + 200) + 0xc);
  uVar3 = *(uint *)(this + 0x110);
  if ((uVar3 & 1) != 0) {
    return;
  }
  if ((uVar3 & 0x10) == 0) {
    fVar4 = *(float *)(this + 0x118) + *(float *)(this + 0x11c);
    *(float *)(this + 0x118) = fVar4;
    iVar2 = iVar1;
    if (1.0 < fVar4) {
      *(float *)(this + 0x118) = fVar4 - 1.0;
      if ((uVar3 & 8) == 0) {
        iVar2 = iVar1 + 1;
        *(int *)(this + 0x114) = iVar2;
        if (iVar2 == *(int *)(this + 0xc0)) {
          if ((uVar3 & 4) == 0) {
            if ((uVar3 & 2) == 0) {
              *(uint *)(this + 0x110) = uVar3 | 1;
              *(undefined4 *)(this + 0x114) = 0;
            }
            else {
              *(undefined4 *)(this + 0x114) = 0;
            }
            iVar2 = 0;
          }
          else {
            iVar2 = iVar1 + -1;
            *(int *)(this + 0x114) = iVar2;
            *(uint *)(this + 0x110) = uVar3 | 8;
          }
        }
      }
      else {
        iVar2 = iVar1 + -1;
        *(int *)(this + 0x114) = iVar2;
        if (iVar2 == -1) {
          if ((uVar3 & 4) == 0) {
            if ((uVar3 & 2) == 0) {
              *(uint *)(this + 0x110) = uVar3 | 1;
              *(undefined4 *)(this + 0x114) = 0;
              iVar2 = 0;
            }
            else {
              iVar2 = *(int *)(this + 0xc0) + -1;
              *(int *)(this + 0x114) = iVar2;
            }
          }
          else {
            iVar2 = iVar1 + 1;
            *(int *)(this + 0x114) = iVar2;
            *(uint *)(this + 0x110) = uVar3 & 0xfffffff7;
          }
        }
      }
    }
    *(undefined4 *)(this + 0x120) = *(undefined4 *)(iVar2 * 0x30 + *(int *)(this + 200) + 0xc);
    return;
  }
  return;
}
