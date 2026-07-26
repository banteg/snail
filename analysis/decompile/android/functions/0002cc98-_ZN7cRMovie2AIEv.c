/*
 * mangled: _ZN7cRMovie2AIEv
 * demangled: cRMovie::AI()
 * address: 0002cc98
 * size: 300
 */

/* cRMovie::AI() */

void __thiscall cRMovie::AI(cRMovie *this)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  float fVar4;

  iVar2 = *(int *)(this + 0x114);
  uVar1 = *(uint *)(this + 0x110);
  iVar3 = iVar2 * 0x30;
  *(undefined4 *)(this + 0x120) = *(undefined4 *)(*(int *)(this + 200) + iVar3 + 0xc);
  if ((uVar1 & 0x11) == 0) {
    fVar4 = *(float *)(this + 0x118) + *(float *)(this + 0x11c);
    *(float *)(this + 0x118) = fVar4;
    if (1.0 < fVar4) {
      *(float *)(this + 0x118) = fVar4 - 1.0;
      if ((uVar1 & 8) == 0) {
        iVar3 = iVar2 + 1;
        *(int *)(this + 0x114) = iVar3;
        if (iVar3 == *(int *)(this + 0xc0)) {
          if ((uVar1 & 4) == 0) {
            if ((uVar1 & 2) == 0) {
              *(uint *)(this + 0x110) = uVar1 | 1;
              *(undefined4 *)(this + 0x114) = 0;
            }
            else {
              *(undefined4 *)(this + 0x114) = 0;
            }
            iVar3 = 0;
          }
          else {
            *(int *)(this + 0x114) = iVar2 + -1;
            *(uint *)(this + 0x110) = uVar1 | 8;
            iVar3 = (iVar2 + -1) * 0x30;
          }
        }
        else {
          iVar3 = iVar3 * 0x30;
        }
      }
      else {
        iVar2 = iVar2 + -1;
        *(int *)(this + 0x114) = iVar2;
        if (iVar2 == -1) {
          if ((uVar1 & 4) == 0) {
            if ((uVar1 & 2) == 0) {
              *(undefined4 *)(this + 0x114) = 0;
              *(uint *)(this + 0x110) = uVar1 | 1;
              iVar3 = 0;
            }
            else {
              *(int *)(this + 0x114) = *(int *)(this + 0xc0) + -1;
              iVar3 = (*(int *)(this + 0xc0) + -1) * 0x30;
            }
          }
          else {
            *(uint *)(this + 0x110) = uVar1 & 0xfffffff7;
            iVar3 = 0x30;
            *(undefined4 *)(this + 0x114) = 1;
          }
        }
        else {
          iVar3 = iVar2 * 0x30;
        }
      }
    }
    *(undefined4 *)(this + 0x120) = *(undefined4 *)(*(int *)(this + 200) + iVar3 + 0xc);
  }
  return;
}
