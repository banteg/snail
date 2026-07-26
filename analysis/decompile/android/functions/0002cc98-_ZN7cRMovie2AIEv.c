/*
 * mangled: _ZN7cRMovie2AIEv
 * demangled: cRMovie::AI()
 * address: 0002cc98
 * size: 300
 */

/* cRMovie::AI() */

void __thiscall cRMovie::AI(cRMovie *this)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  float fVar5;

  iVar3 = *(int *)(this + 0x114);
  uVar2 = *(uint *)(this + 0x110);
  iVar4 = iVar3 * 0x30;
  *(undefined4 *)(this + 0x120) = *(undefined4 *)(*(int *)(this + 200) + iVar4 + 0xc);
  fVar1 = DAT_0002cdc4;
  if ((uVar2 & 0x11) == 0) {
    fVar5 = *(float *)(this + 0x118) + *(float *)(this + 0x11c);
    *(float *)(this + 0x118) = fVar5;
    if (fVar1 < fVar5) {
      *(float *)(this + 0x118) = fVar5 - fVar1;
      if ((uVar2 & 8) == 0) {
        iVar4 = iVar3 + 1;
        *(int *)(this + 0x114) = iVar4;
        if (iVar4 == *(int *)(this + 0xc0)) {
          if ((uVar2 & 4) == 0) {
            if ((uVar2 & 2) == 0) {
              *(uint *)(this + 0x110) = uVar2 | 1;
              *(undefined4 *)(this + 0x114) = 0;
            }
            else {
              *(undefined4 *)(this + 0x114) = 0;
            }
            iVar4 = 0;
          }
          else {
            *(int *)(this + 0x114) = iVar3 + -1;
            *(uint *)(this + 0x110) = uVar2 | 8;
            iVar4 = (iVar3 + -1) * 0x30;
          }
        }
        else {
          iVar4 = iVar4 * 0x30;
        }
      }
      else {
        iVar3 = iVar3 + -1;
        *(int *)(this + 0x114) = iVar3;
        if (iVar3 == -1) {
          if ((uVar2 & 4) == 0) {
            if ((uVar2 & 2) == 0) {
              *(undefined4 *)(this + 0x114) = 0;
              *(uint *)(this + 0x110) = uVar2 | 1;
              iVar4 = 0;
            }
            else {
              *(int *)(this + 0x114) = *(int *)(this + 0xc0) + -1;
              iVar4 = (*(int *)(this + 0xc0) + -1) * 0x30;
            }
          }
          else {
            *(uint *)(this + 0x110) = uVar2 & 0xfffffff7;
            iVar4 = 0x30;
            *(undefined4 *)(this + 0x114) = 1;
          }
        }
        else {
          iVar4 = iVar3 * 0x30;
        }
      }
    }
    *(undefined4 *)(this + 0x120) = *(undefined4 *)(*(int *)(this + 200) + iVar4 + 0xc);
  }
  return;
}
